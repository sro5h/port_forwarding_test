#include <iostream>
#include <enet/enet.h>

int main()
{
        if (enet_initialize() != 0)
        {
                std::cerr << "Could not initialize ENet" << std::endl;
                return EXIT_FAILURE;
        }

        std::string ip;
        std::uint16_t port;

        std::cout << "Enter ip: ";
        std::cin >> ip;
        std::cout << "Enter port: ";
        std::cin >> port;

        ENetHost* host;

        host = enet_host_create(NULL, 1, 2, 0, 0);

        if (host == NULL)
        {
                std::cerr << "Could not create host" << std::endl;
                enet_deinitialize();
                return EXIT_FAILURE;
        }

        ENetAddress address;
        enet_address_set_host(&address, ip.c_str());
        address.port = port;

        ENetPeer* peer = enet_host_connect(host, &address, 2, 0);

        if (peer == NULL)
        {
                std::cerr << "Could not attempt a connection" << std::endl;
                enet_host_destroy(host);
                enet_deinitialize();
                return EXIT_FAILURE;
        }

        std::cout << "Trying to connect" << std::endl;

        while (true)
        {
                ENetEvent event;
                while (enet_host_service(host, &event, 0) > 0)
                {
                        if (event.type == ENET_EVENT_TYPE_CONNECT)
                        {
                                char address[64];
                                enet_address_get_host_ip(&event.peer->address,
                                                address, sizeof(address));
                                std::cout << "Connection from " << address;
                                std::cout << ":" << event.peer->address.port;
                                std::cout << std::endl;
                        }
                }
        }

        enet_peer_reset(peer);
        enet_host_destroy(host);
        enet_deinitialize();
}
