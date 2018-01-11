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

/**
 * Set the random seed used for the number generator
 * @param seed, an integer especifying the random seed
 */
void Controller::SetRandomSeed(int seed) {
  
  random_seed = seed;
  distribution_sampler.SetRandomNumberGeneratorSeed(seed);
  
}

/**
 * Get the random seed
 * @returns int the random seed
 */ 
int Controller::GetRandomSeed() {
  
  return random_seed;
  
}

/**
 * Checks the user provided random see is valid
 * @returns int rando_seed or raises an exception
 */
int Controller::CheckRandomSeed() {
  
  //if the user forgot to set the random seed this int will be null and we need to throw an exception
  if (random_seed <= 0){
    
    throw "Random seed (option -r) was not set but is required";
    
  }else{
  
    return random_seed;
  }
  
}

/**
 * Set the number of generations
 * @param ngens an integer providing the desired number of generations for the chain to run
 */
void Controller::SetNumberOfGenerations(int ngens){
  
  number_of_generations = ngens;
  
}

/**
 * Checks the user provided a valid number of generations
 * @returns the number of generations or raises and exception
 */
int Controller::CheckNumberOfGenerations(){
  //if the user forgot to set the random seed this int will be null and we need to throw an exception
  if (number_of_generations <= 0){
    
    throw "Number of generations (option -g) was not set but is required";
    
  }else{
  
    return number_of_generations;
  }
  
}

/**
 * Set the alignment file path
 * @param path an std::string object with the user provided path to the alignment
 */
void Controller::SetAlignmentFilePath(std::string path) {
  
  alignment_file_path = path;
  
}

/**
 * Get the alignment path
 * @returns a std::string with the user provided alignment path
 */
std::string Controller::GetAlignmentFilePath() {
  
    return alignment_file_path;
  
}

/**
 * Checks that the user provided alignment path is not empty
 * @returns a std::string with the alignment path or raises an exception
 */
std::string Controller::CheckAlignmentFilePath() {
  
  //if the user forgot to set the ali path this char* will be null and we need to throw an exception
  if (!alignment_file_path.length()){
    
    throw "Alignment file path (option -i) was not set but is required";
    
  }else{
  
    return alignment_file_path;
  }
  
}
 
/**
 * Set the name of the name
 * @param name a std::string provided by the user
 */
void Controller::SetChainName(std::string name) {
  
  chain_name = name;
  
}

/**
 * Get the user provided chain name
 * @returns std::string with the chain name
 */
std::string Controller::GetChainName() {
  
    return chain_name;
  
}

/**
 * Check the user provided chain name is not empty
 * @returns a std::string with the chain name or raises an exception 
 */
std::string Controller::CheckChainName() {
  
  //if the user forgot to set the chain name this char* will be null and we need to throw an exception
  if (!chain_name.length()){
    
    throw "Chain name (option -c) was not set but is required";
    
  }else{
  
    return chain_name;
    
  }
  
}

/**
 * Set the min value for the uniform distribution used to get the branch lengths
 * @param double with the user provided value
 */
void Controller::SetBLUniformMin(double u_min){
  
  bl_uniform_min = u_min;
  
}

/**
 * Get the min value of the uniform distribution used to get the branch lengths
 * @returns double with the user provided min value
 */
double Controller::GetBLUniformMin(){
  
  return bl_uniform_min;
  
}

/**
 * Set the max value for the uniform distribution used to get the branch lengths
 * @param double with the user provided value
 */
void Controller::SetBLUniformMax(double u_max){
  
  bl_uniform_max = u_max;
  
}

/**
 * Get the max value of the uniform distribution used to get the branch lengths
 * @returns double with the user provided max value
 */
double Controller::GetBLUniformMax(){
  
  return bl_uniform_max;
  
}

/**
 * Set the mean value of the exponential distribution used to get the branch lengths
 * @param e_mean a double with the user provided mean value
 */
void Controller::SetBLExponentialMean(double e_mean){
  
  bl_exponential_mean = e_mean;
  
}

/**
 * Get the mean value of the exponential distribution used to get the branch lengths
 * @returns double with the user provided mean value
 */
double Controller::GetBLExponentialMean(){
  
  return bl_exponential_mean;

}


/**
 * Checks that all options are fine
 */
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

/**
 * This method initiliases the tree object and starts the run.
 * 
 */

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
    
    std::cerr << "Select Node " << distribution_sampler.SampleFromIntUniform(0,number_of_nodes) << "\n";
    //std::cerr << "Sample BL  " << distribution_sampler.SampleBLFromUniform(bl_uniform_min, bl_uniform_max) << "\n";
    std::cerr << "Sample BL  " << distribution_sampler.SampleFromExponential(bl_exponential_mean) << "\n";
  }
}
