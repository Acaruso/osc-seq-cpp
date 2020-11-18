#include "osc.hpp"

#include <iostream>

#include <asio.hpp>
#include <oscpp/client.hpp>

void send_osc_packet(int channel)
{
    std::array<char, MAX_PACKET_SIZE> buffer;
    const size_t packetSize = make_osc_packet(channel, buffer.data(), buffer.size());
    send_udp_message(buffer, "127.0.0.1", 3333);
}

void send_osc_packet(int channel, std::vector<Grid_Cell_Data> data)
{
    std::array<char, MAX_PACKET_SIZE> buffer;
    const size_t packetSize = make_osc_packet(
        channel,
        buffer.data(),
        buffer.size(),
        data
    );
    send_udp_message(buffer, "127.0.0.1", 3333);
}

size_t make_osc_packet(int channel, void* buffer, size_t size)
{
    std::string channel_str = "/" + std::to_string(channel);

    OSCPP::Client::Packet packet(buffer, size);
    packet
        .openMessage(channel_str.c_str(), 1)
        .closeMessage();

    return packet.size();
}

size_t make_osc_packet(
    int channel,
    void* buffer,
    size_t size,
    std::vector<Grid_Cell_Data> data
) {
    OSCPP::Client::Packet packet(buffer, size);
    std::string channel_str = "/" + std::to_string(channel);

    std::vector<Grid_Cell_Data> osc_data;

    for (auto& row : data) {
        if (row.options & Op_Osc_Data) {
            osc_data.push_back(row);
        }
    }

    packet.openMessage(channel_str.c_str(), osc_data.size());

    for (auto& row : osc_data) {
        std::string str = row.key + " " + row.get_value_str();
        packet.string(str.c_str());
    }

    packet.closeMessage();

    return packet.size();
}

void send_udp_message(
    const std::array<char, MAX_PACKET_SIZE>& message,
    const std::string& destination_ip,
    const unsigned short port
) {
    asio::io_service io_service;
    asio::ip::udp::socket socket(io_service);
    auto remote = asio::ip::udp::endpoint(asio::ip::address::from_string(destination_ip), port);
    socket.open(asio::ip::udp::v4());
    socket.send_to(asio::buffer(message), remote);
}

void send_udp_message(
    const std::string& message,
    const std::string& destination_ip,
    const unsigned short port
) {
    asio::io_service io_service;
    asio::ip::udp::socket socket(io_service);
    auto remote = asio::ip::udp::endpoint(asio::ip::address::from_string(destination_ip), port);
    socket.open(asio::ip::udp::v4());
    socket.send_to(asio::buffer(message), remote);
}
