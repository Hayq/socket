#ifndef client_hpp
#define client_hpp

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class Client
{
public:
   Client(const char*[], const int);
   void Connection();
   static void writeThread(int);
   static void readThread(int);
   
private:
   int sockfd;
   struct sockaddr_in server_addr;
   struct hostent* server;

private:
   static void error(const char*);
};

#endif /* client_hpp */
