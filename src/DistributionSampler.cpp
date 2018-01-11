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
 * This method samples from a uniform distribution an integer number
 * 
 */
int DistributionSampler::SampleFromIntUniform(int min, int max){
  
  std::uniform_int_distribution<int> uniform_int_sampler(min, max);
  
  std::cerr << "sampling branch length from real uniform distribution (" << min << "," << max << ")\n";
  
  return uniform_int_sampler(pseudo_random_number_gen);
  
}

/**
 * This method samples from a uniform distribution a real number
 * 
 */
double DistributionSampler::SampleFromRealUniform(double min, double max){
  
  std::uniform_real_distribution<double> uniform_real_sampler(min, max);
  
  std::cerr << "sampling branch length from real uniform distribution (" << min << "," << max << ")\n";
  
  return uniform_real_sampler(pseudo_random_number_gen);
  
}

/**
 * This method samples from an exponential distribution a real number
 */
double DistributionSampler::SampleFromExponential(double mean){
  
  std::exponential_distribution<double> exponential_sampler(mean);
  
  std::cerr << "sampling branch length from exponential distribution (" << mean << ")\n";
  
  return exponential_sampler(pseudo_random_number_gen);
  
}


/**
 * This method samples from a gamma distribution a real number
 */
double DistributionSampler::SampleFromGamma(double alpha, double beta){
  
  std::gamma_distribution<double> gamma_sampler(alpha, beta);
  
  std::cerr << "sampling branch length from exponential distribution (" << alpha << "," << beta << ")\n";
  
  return gamma_sampler(pseudo_random_number_gen);
  
}
