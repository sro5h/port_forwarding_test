#include <iostream>
#include <enet/enet.h>

int main()
{
        if (enet_initialize() != 0)
        {
                std::cerr << "Could not initialize ENet" << std::endl;
                return EXIT_FAILURE;
        }

        ENetAddress address;
        ENetHost* host;

        address.host = ENET_HOST_ANY;
        address.port = 1123;

        host = enet_host_create(&address, 5, 2, 0, 0);

        if (host == NULL)
        {
                std::cerr << "Could not create host" << std::endl;
                enet_deinitialize();
                return EXIT_FAILURE;
        }

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

        enet_host_destroy(host);
        enet_deinitialize();
}
