/**
 * Class DistributionSampler
 * 
 */

#include "DistributionSampler.h"
#include <string>
#include <vector>

#include <iostream>

DistributionSampler::DistributionSampler(){}


void DistributionSampler::SetRandomNumberGeneratorSeed(int seed){
  
  std::cerr << "setting random seed = " << seed <<" for pseudo_random_number_gen\n";
  pseudo_random_number_gen.seed(seed);
  
}

/**
 * This method samples from a uniform distribution a real number that will be use to set the branch lenghts of the tree
 * 
 */
double DistributionSampler::SampleBLFromUniform(double min, double max){
  
  std::uniform_real_distribution<double> uniform_bl_sampler(min, max);
  
  std::cerr << "sampling branch length from real uniform distribution (" << min << "," << max << ")\n";
  
  return uniform_bl_sampler(pseudo_random_number_gen);
  
}

/**
 * This method creates a lightweight uniform int distribution object and passes the total number of nodes in the tree as its upper bound
 * 
 * We use this to select nodes at random 
 */
int DistributionSampler::SampleRandomNode(int max){
  
  std::uniform_int_distribution<int> node_index_sampler (0, max);
  
  std::cerr << "sampling random node\n";
  return node_index_sampler(pseudo_random_number_gen);
  
}




