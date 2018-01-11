/*
 * phylotoy
 * Class Controller
 * objects of this class interact with the user via CLI and coordinate the work done by other objects
 * 
 */

#include "InputReader.h"
#include "OutputPrinter.h"
#include "Tree.h"
#include "DistributionSampler.h"
#include <string>
#include <vector>

class Controller {
  
  //CLI arguments
  int random_seed = -1;
  std::string alignment_file_path;
  std::string chain_name;
  int number_of_generations = -1;
  double bl_uniform_min = 0;
  double bl_uniform_max = 100;
  double bl_exponential_mean = 10;
  
  //my servants
  InputReader input_reader;
  OutputPrinter output_printer;
  DistributionSampler distribution_sampler;
  
  //my objects
  Tree phylo_tree;
  
  public:
    Controller();
    
    void SetRandomSeed(int seed);
    int GetRandomSeed();
    int CheckRandomSeed();
    
    void SetNumberOfGenerations(int ngens);
    int CheckNumberOfGenerations();
    
    void SetAlignmentFilePath(std::string path);
    std::string GetAlignmentFilePath();
    std::string CheckAlignmentFilePath();
    
    void SetChainName(std::string name);
    std::string GetChainName();
    std::string CheckChainName();
    
    void SetBLUniformMin(double u_min);
    double GetBLUniformMin();
    
    void SetBLUniformMax(double u_max);
    double GetBLUniformMax();
    
    void SetBLExponentialMean(double e_mean);
    double GetBLExponentialMean();
    
    void CheckCLIOptions();
    
    void Run();
    
};
