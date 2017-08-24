#include "client.hpp"
#include <thread>

Client::Client(const char* argv[]){   
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0)
      error("ERROR: socket do not created");
   
   server = gethostbyname("192.168.88.23");
   
   if ( server == NULL )
      error("ERROR: no such host");
   
   bzero((char*) &server_addr, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   bcopy((char*) server->h_addr,
         (char*)&server_addr.sin_addr.s_addr,
         server->h_length);
   int host_port = atoi(argv[1]);
   server_addr.sin_port = htons(host_port);
}

void Client::Connection(){
   if ( connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 )
      error("ERROR: can't connecting");
   
   std::thread write_thread(writeThread, sockfd);
   std::thread read_thread(readThread, sockfd);
   
   write_thread.join();
   read_thread.join();
}

void Client::writeThread(const int sockfd){
   char buffer[256];
   
   while(true){
      bzero(buffer, 256);
      fgets(buffer, 255, stdin);
      std::string str(buffer);
      ssize_t size = str.size() - 1;
      std::cout << size;
      
      //send text size
      ssize_t n = write(sockfd, std::to_string(size).c_str(), 1);

      if(n < 0)
         error("no write");
      
      //send text
      n = write(sockfd, buffer, strlen(buffer));

      if(n < 0)
         error("no write");
   }
}

void Client::readThread(const int sockfd){
   char buffer[256];
   
   while(true){
      bzero(buffer, 256);
      ssize_t n = read(sockfd, buffer, sizeof(buffer));
      if(n <= -1)
         error("read");
      else if(n == 0)
         continue;
      else if(n > 0)
         std::cout << "mess " << sockfd << ": " << buffer << std::endl;
   }
}

void Client::error(const char* mess){
   std::cout << mess << std::endl;
   exit(1);
}
