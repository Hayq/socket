#include "client.hpp"

int main(int argc, const char* argv[]){
   Client cli(argv, argc);
   cli.Connection();
   
   return 0;
}
