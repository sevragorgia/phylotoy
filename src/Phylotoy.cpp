/**
 * phylotoy
 * 
 * @author Sergio Vargas
 * 
 * A toy program to learn how bayesian phylogenetic reconstruction works...
 */

#include <getopt.h>
#include <stdlib.h>
#include "Controller.h"
#include <string.h>

#include <iostream>

int main(int argc, char* argv[]) {
  
  //Initialize a controller object
  
  Controller phylotoy_controller;
  
  /**
   * Read the CLI options set the appropriate variables in the controller
   * Options are passsed as follows:
   * --random_seed expects an integer that will be used as the random seed for the run
   * --input_file expect a path to the alignment file
   * --chain_name expects the user to provide a name for the chain
   * --generations expects an integer especifying the number of generations
   * --uniform_branches Branch lengths will be sampled from a Uniform distribution. Expects two floats separated by a , 
   *   and especifying the min and max values for the uniform branch length distribution.
   * --exponential_branches expects a float especifying the mean value of the exponential distribution
   * --uniform_dirichlet_branches Branch lengths will be sampled from a uniform Dirichlet distribution. No argument expected. 
   * --non_uniform_dirichlet_branches Branch lengths will be sampled from a non-uniform Dirichlet distribution. No argument expected. 
   * --verbose activate verbosity
   */
  
  int option;
  
  static struct option long_options[] = {{ "random_seed",  required_argument, 0, 'r'},
                                         { "input_file", required_argument, 0, 'i'},
                                         { "chain_name", required_argument, 0, 'c'},
                                         { "generations", required_argument, 0, 'g'},
                                         { "uniform_branches", required_argument, 0, 'u'},
                                         { "exponential_branches", required_argument, 0, 'e'},
                                         { "uniform_dirichlet_branches", required_argument, 0, 'f'},
                                         { "non_uniform_dirichlet_branches", required_argument, 0, 'o'},
                                         { "verbose", no_argument, 0, 'v'},
                                         {0, 0, 0, 0}
  };
  
  while ((option = getopt(argc, argv, "r:i:c:g:u:e:ud:nd:v")) != -1) {
    
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
      case 'g':
      {
        phylotoy_controller.SetNumberOfGenerations(atoi(optarg));
        break; 
      }
      case 'u':
      {
        char* min = strtok(optarg, ",");
        char* max = strtok(NULL, ",");
        phylotoy_controller.SetBLUniformMin(atoi(min));
        phylotoy_controller.SetBLUniformMax(atoi(max));
        break;
      }
      case 'e':
      {
        phylotoy_controller.SetBLExponentialMean(atoi(optarg));
        break;
        
      }
      case 'f':
      {
        break;
        
      }
      case 'o':
      {
        break;
        
      }
      default:
        abort();
    }
  }
  
  phylotoy_controller.Run();
  
  return 0;
}
