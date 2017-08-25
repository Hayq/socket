#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <map>

struct ClientInfo
{
   int socket;
   int id;
   std::string name;
};

template <class T>
static T CharToCliInfo(const char* p, const char* type){
   std::string _type(type);
   ClientInfo* ob = (ClientInfo*)p;
   
   if(_type == "id"){ return ob->id; }else
   if(_type == "socket"){ return ob->socket; }else
   
   return 0;
}

class Server
{
public:
   Server(const char*[]);
   void AcceptSockets();
   
private:
   static void* readTask(void* n);
   static std::string readStr(const int socket);
   static void SendMessage(std::string);
   static void acceptCliThread(const int, sockaddr_in, socklen_t);
   static bool FindId(const char*);
   static void CreateId(const int);
   static void error(const char*);
   
private:
   int sockfd;
   socklen_t clilen;
   sockaddr_in server_addr;
   sockaddr_in client_addr;
   static std::map<int, std::string> cli_info;
};
