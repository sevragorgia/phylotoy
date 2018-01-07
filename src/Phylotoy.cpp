/*
 * phylotoy
 * Main
 * a toy program to learn how phylogenetic reconstruction works...
 */

//include getopt
#include <unistd.h>
#include <stdlib.h>
#include "Controller.h"
#include <string>

int main(int argc, char* argv[]) {
  
  //Initialize a controller object
  
  Controller phylotoy_controller;
  
  /* Read the CLI options set the appropriate variables in the controller
   * Options are passsed as follows:
   * -r random seed
   * -i alignment path
   * -c chain name
   */
  
  int option;
  
  while ((option = getopt(argc, argv, "r:i:c:")) != -1) {
    
    switch (option){
      
      case 'r':
      {
        phylotoy_controller.SetRandomSeed(atoi(optarg));
        break;
      }
      case 'i':
      {
        std::string input (optarg);
        phylotoy_controller.SetAlignmentFilePath(input);
        break;
      }
      case 'c':
      {
        std::string name (optarg);
        phylotoy_controller.SetChainName(name);
        break;
      }
      default:
        abort();
    }
  }
  
  phylotoy_controller.Run();
  
  return 0;
}
