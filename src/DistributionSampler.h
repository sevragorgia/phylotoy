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
    
    int SampleFromIntUniform(int min, int max);
    
    double SampleFromRealUniform(double min, double max);
    
    double SampleFromExponential(double mean);
    
    std::vector<double> SampleFromExponential(int vector_size, double mean);
/*    
    double SampleFromUniformDirichlet(double mean);
    
    double SampleFromNonUniform(double mean);
*/    
    double SampleFromGamma(double alpha, double beta);
  
  
    
};
