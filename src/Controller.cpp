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

Controller::Controller(){
  
  
  
}

void Controller::SetRandomSeed(int seed) {
  
  random_seed = seed;
  
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
  
  phylo_tree.CreateBifurcatingTree(alignment);
  
  //phylo_tree.CreateStarTree(alignment);
  
  output_printer.PrintMessage2Out("collecting node info recursively\n");
  std::vector<std::string>* nodes_info_recursively = phylo_tree.CollectTreeNodesInfoRecursively();
  
  while(!nodes_info_recursively->empty()) {
    
    output_printer.PrintMessage2Out("in while\n");
    output_printer.PrintMessage2Out(nodes_info_recursively->back());
    output_printer.PrintMessage2Out("\n");
    
    nodes_info_recursively->pop_back();
  }
  
  output_printer.PrintMessage2Out("collecting node info iteratively\n");
  std::vector<std::string>* nodes_info_iteratively = phylo_tree.CollectTreeNodesInfoIteratively();
  
  while(!nodes_info_iteratively->empty()) {
    
    output_printer.PrintMessage2Out("in while\n");
    output_printer.PrintMessage2Out(nodes_info_iteratively->back());
    output_printer.PrintMessage2Out("\n");
    
    nodes_info_iteratively->pop_back();
  }
  
}
