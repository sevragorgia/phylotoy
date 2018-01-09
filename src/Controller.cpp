/*
 * phylotoy
 * Class Controller
 * objects of this class interact with the user via CLI and coordinate the work done by other objects
 * 
 */

#include "Controller.h"
#include <string>
#include <exception>
#include <assert.h>
#include <vector>

#include <iostream>

Controller::Controller(){
  
}

void Controller::SetRandomSeed(int seed) {
  
  random_seed = seed;
  distribution_sampler.SetRandomNumberGeneratorSeed(seed);
  
}

int Controller::GetRandomSeed() {
  
  return random_seed;
  
}

int Controller::CheckRandomSeed() {
  
  //if the user forgot to set the random seed this int will be null and we need to throw an exception
  if (random_seed <= 0){
    
    throw "Random seed (option -r) was not set but is required";
    
  }else{
  
    return random_seed;
  }
  
}

void Controller::SetNumberOfGenerations(int ngens){
  
  number_of_generations = ngens;
  
}

int Controller::CheckNumberOfGenerations(){
  //if the user forgot to set the random seed this int will be null and we need to throw an exception
  if (number_of_generations <= 0){
    
    throw "Number of generations (option -g) was not set but is required";
    
  }else{
  
    return number_of_generations;
  }
  
}


void Controller::SetAlignmentFilePath(std::string path) {
  
  alignment_file_path = path;
  
}

std::string Controller::GetAlignmentFilePath() {
  
    return alignment_file_path;
  
}

std::string Controller::CheckAlignmentFilePath() {
  
  //if the user forgot to set the ali path this char* will be null and we need to throw an exception
  if (!alignment_file_path.length()){
    
    throw "Alignment file path (option -i) was not set but is required";
    
  }else{
  
    return alignment_file_path;
  }
  
}
 
 
void Controller::SetChainName(std::string name) {
  
  chain_name = name;
  
}

std::string Controller::GetChainName() {
  
    return chain_name;
  
}

std::string Controller::CheckChainName() {
  
  //if the user forgot to set the chain name this char* will be null and we need to throw an exception
  if (!chain_name.length()){
    
    throw "Chain name (option -c) was not set but is required";
    
  }else{
  
    return chain_name;
    
  }
  
}

void Controller::CheckCLIOptions() {
  
  /*We need to check whether the necessary options were set*/
  
  try {
    
    this->CheckAlignmentFilePath();
    this->CheckChainName();
    this->CheckRandomSeed();
    this->CheckNumberOfGenerations();
        
  } catch (const char* exception) {
    
    std::string what_exception(exception);
    std::string error = "Error: " + what_exception + "\n";
    output_printer.PrintMessage2Out(error);
    
    exit(1);
    
  }
  
}


void Controller::Run() {
  
  this->CheckCLIOptions();
  
  //if all option are set, we tell the user how the program was invoked.
  std::string program_call = "phylotoy was invoked with the following options:\n\n\tRandom seed = " + std::to_string(random_seed) + "\n\tAlingment path = " + alignment_file_path + "\n\tChain name = " + chain_name + "\n\n";
  
  output_printer.PrintMessage2Out(program_call);  
  
  //tmp vector of strings
  std::vector<std::string>* alignment;
  
  output_printer.PrintMessage2Out("reading alignment\n");
  //now we need to open and store the Alignment in a string vector
  alignment = input_reader.ReadInputFile(alignment_file_path);
  
  
  output_printer.PrintMessage2Out("initializing tree\n");
  
  int number_of_nodes = phylo_tree.CreateBifurcatingTree(alignment);
  
  for(int i=0; i < number_of_generations; i++){
    
    std::cerr << "Select Node " << distribution_sampler.SampleRandomNode(number_of_nodes) << "\n";
    std::cerr << "Sample BL  " << distribution_sampler.SampleBLFromUniform(0, 100) << "\n";//need to implement this for the command line.
  }
}
