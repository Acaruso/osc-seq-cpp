#include "osc.hpp"

#include <iostream>

#include <asio.hpp>
#include <oscpp/client.hpp>

void send_osc_packet(Grid_Cell& grid_cell)
{
    std::array<char, MAX_PACKET_SIZE> buffer;
    const size_t packetSize = make_osc_packet(
        grid_cell,
        buffer.data(),
        buffer.size()
    );
    send_udp_message(buffer, "127.0.0.1", 3333);
}

size_t make_osc_packet(
    Grid_Cell& grid_cell,
    void* buffer,
    size_t size
) {
    OSCPP::Client::Packet packet(buffer, size);
    std::string channel_str = "/" + std::to_string(grid_cell.channel);

    size_t osc_data_size = 0;

    grid_cell.for_each_field([&](Event_Field& field) {
        if (field.is_osc_data) {
            ++osc_data_size;
        }
    });

    // for (auto& field : fields) {
    //     if (field.is_osc_data) {
    //         ++osc_data_size;
    //     }
    // }

    packet.openMessage(channel_str.c_str(), osc_data_size);

    grid_cell.for_each_field([&](Event_Field& field) {
        if (field.is_osc_data) {
            packet.string(
                (field.key + " " + field.get_value_str()).c_str()
            );
        }
    });

    // for (auto& field : fields) {
    //     if (field.is_osc_data) {
    //         packet.string(
    //             (field.key + " " + field.get_value_str()).c_str()
    //         );
    //     }
    // }

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
