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

void send_osc_packet(Grid_Cell& grid_cell)
{
    std::array<char, MAX_PACKET_SIZE> buffer;
    const size_t packetSize = make_osc_packet(
        grid_cell.channel,
        buffer.data(),
        buffer.size(),
        grid_cell.fields
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
    std::vector<Event_Field>& fields
) {
    OSCPP::Client::Packet packet(buffer, size);
    std::string channel_str = "/" + std::to_string(channel);

    size_t osc_data_size = 0;

    for (auto& field : fields) {
        if (field.is_osc_data) {
            ++osc_data_size;
        }
    }

    packet.openMessage(channel_str.c_str(), osc_data_size);

    for (auto& field : fields) {
        if (field.is_osc_data) {
            packet.string(
                (field.key + " " + field.get_value_str()).c_str()
            );
        }
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
