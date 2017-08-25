#include "server.hpp"

Server::Server(const char* asd[]){
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if(!sockfd)
      error("ERROR: socket not created");
   
   bzero((char*)&server_addr, sizeof(server_addr));
   
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(8888);
   server_addr.sin_addr.s_addr = INADDR_ANY;
}

void Server::AcceptSockets(){
   if( bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0 )
      error("ERROR: not correct binding");
   
   listen(sockfd, 5);
   clilen = sizeof(client_addr);
   std::thread accepet_thread(acceptCliThread, sockfd, client_addr, clilen);
   accepet_thread.join();
}

void Server::acceptCliThread(int sockfd, sockaddr_in client_addr, socklen_t clilen){
   std::cout << "Server is listening" << std::endl;
   while(true){
      long socket = accept(sockfd, (struct sockaddr*) &client_addr, &clilen);
      if( socket < 0 ){
         error("ERROR: can not accept");
      }
      std::cout << socket << " is connectied" << std::endl;
      
      ClientInfo info;
      info.socket = (int)socket;
      char* info_ptr = (char*)&info;
      
      if(!FindId((info_ptr))){
         CreateId((int)socket);
      }
      
      pthread_t readThread;
      pthread_create(&readThread, NULL, readTask, (void*)info_ptr);
   }
}

bool Server::FindId(const char* info){
   bool isfind = false;
   int Id = (CharToCliInfo<int>(info, "sock"));
   
   for(auto& x: cli_info){
      if(x.first == Id){
         std::cout << "Find cli: " << Id << std::endl;
         isfind = true;
         break;
      }
   }
   return isfind;
}

void Server::CreateId(const int id){
   write((int)id, "Enter your name(without spaces): ", 32);
   std::string size = readStr(id);
   int _size = atoi(size.c_str());
   
   std::string name = readStr(id);
   std::string _name;
   
   for(int i = 0; i < _size; ++i)
      _name += name[i];
   cli_info.insert(std::pair<int, std::string>((int)id, _name));
   
   for(auto& x: cli_info)
      std::cout << "info: " << x.second << std::endl;
}

//Read and terun writed from cli
std::string Server::readStr(const int socket){
   std::string str;
   char buffer[256];
   bzero(buffer, 256);
   
   ssize_t n = read(socket, buffer, sizeof(buffer));
   if(n < 0)
      error("readStr");
   
   return buffer;
}

//Server Read Thread
void* Server::readTask(void* n){
   char* p = (char*)n;
   int sock = CharToCliInfo<int>(p, "socket");
   std::cout << "Thread: " << sock << std::endl;
   
   int count = 0;
   
   while(true){
      std::string str = Server::readStr(sock);
      
      if(str.empty()){
         ++count;
         if(count > 13){
            break;
         }
         continue;
      }
      
      if( str[0] == '>'){
         Server::SendMessage(str);
      }else
         std::cout << str[0] << "|" << str << std::endl;
      
   }
   
   return 0;
}

void Server::SendMessage(std::string str){
   std::string name, message;
   int i = 0;
   for(i = 1; str[i] != ' '; ++i ){
      name += str[i];
   }
   
   for(; i < str.size(); ++i ){
      message += str[i];
   }

   cli_info.
   
   for(auto& x: cli_info){
      if (x.second == name){
         int n = write(x.first, message.c_str(), message.size());
         if(n < 0)
            error("write to");
      }
   }
}

//ERRORS
void Server::error(const char *mess){
   std::cout << mess << std::endl;
   exit(1);
}
