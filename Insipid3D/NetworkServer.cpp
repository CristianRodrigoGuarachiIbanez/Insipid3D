#include "NetworkServer.h"
#include "engine.h"
#include "Server_TCP.h"
#include "Session_TCP.h"
#include "Server_UDP.h"

#include "Util.h"
#include "camera.h";

#include <boost/filesystem.hpp>
#include <thread>

NetworkServer::NetworkServer(Engine* engine)
	:engine(engine)
{
    active = 0;
    port = 32500;
    server_tcp_ = nullptr;
}

void NetworkServer::startServer()
{
    *engine->console << "Trying to start server..." << std::endl;

    std::thread netThread([&] {
        try
        {
            /*server_tcp_ = new server_tcp(io_context, port, engine);
            active = 1;
            io_context.run();
            active = 0;
            *engine->console << "Server Stopped." << std::endl;*/

            server_udp_ = new Server_UDP(io_context, port, engine);
            active = 1;
            io_context.run();
            active = 0;
            *engine->console << "Server Stopped." << std::endl;
        }
        catch (std::exception& e)
        {
            //std::cerr << "Exception: " << e.what() << "\n";
            *engine->console << "Server Exception: " << e.what() << std::endl;
        }
        active = 0;
    });
    
    netThread.detach();
}

void NetworkServer::stopServer()
{
    io_context.stop();
}

void NetworkServer::tick(float deltaTime)
{
    updateTimer += deltaTime;

    if (updateTimer > 1.f / 16.f) //64 ticks a second
    {
        serverTicks++;
        updateTimer = 0;
        if (active)
        {
            //for (auto& i : server_tcp_->sessions)
            //{
            //    //i->send({ {"type", "tick"}, {"data", serverTicks} });
            //    
            //    EntityList l;
            //    engine->entityManger->getAllEntities(&l);

            //    nlohmann::json j;

            //    for (auto& i : l)
            //    {
            //        if(i->active)
            //            j.push_back(nlohmann::json::parse(i->serialize()));
            //    }

            //    i->send({ {"type", "entityUpdate"}, {"data", j} });
            //    std::cout << "sent " << serverTicks << std::endl;
            //    //i->sendPeers();
            //}
        }
    }
}
