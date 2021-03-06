/** Main program for the footprint security website **/

#include <iostream>
#include <signal.h>

#include <wittyPlus/Server.hpp>

#include "App.hpp"

int main(int argc, char** argv) {
    try {
        wittyPlus::Server server(argc, argv);
        server.addEntryPoint(Wt::Application, [](const Wt::WEnvironment& env){ return new footprint::App(env); });
        if (server.start()) {
            int sig = Wt::WServer::waitForShutdown(argv[0]);
            std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
            server.stop();
            if (sig == SIGHUP)
                Wt::WServer::restart(argc, argv, environ);
        }
    } catch (Wt::WServer::Exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 2;
    }
    return 0;
}
