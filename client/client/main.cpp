#include "client.hpp"

int main(int argc, const char* argv[]){
   Client cli(argv);
   cli.Connection();
   
   return 0;
}
