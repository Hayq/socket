#include "server.hpp"

std::map<std::string, std::string> Server::cli_info;

int main(int argc, const char* argv[]){
   Server server(argv);
   server.AcceptSockets();
   
   pthread_exit(NULL);
   return 0;
}
