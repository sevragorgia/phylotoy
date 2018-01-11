/**
 * phylotoy
 * Class DistributionSampler
 * objects of this class provide access to different probabily distributions.
 * 
 */

#include <string>
#include <vector>
#include <random>

class DistributionSampler {
  
  std::mt19937 pseudo_random_number_gen;

  public:
    
    DistributionSampler();
    
    void SetRandomNumberGeneratorSeed(int seed);
    
    double SampleBLFromUniform(double min, double max);
    
    int SampleRandomNode(int total_nodes);
  
  
  
    
};
