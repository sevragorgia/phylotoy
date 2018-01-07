/*
 * phylotoy
 * Class Controller
 * objects of this class interact with the user via CLI and coordinate the work done by other objects
 * 
 */

#include "InputReader.h"
#include "OutputPrinter.h"
#include "Tree.h"
#include <string>
#include <vector>

class Controller {
  
  //CLI arguments
  int random_seed = -1;
  std::string alignment_file_path;
  std::string chain_name;
  
  //my servants
  InputReader input_reader;
  OutputPrinter output_printer;
  
  //my objects
  Tree phylo_tree;
  
  public:
    Controller();
    
    void SetRandomSeed(int seed);
    int GetRandomSeed();
    int CheckRandomSeed();
    
    void SetAlignmentFilePath(std::string path);
    std::string GetAlignmentFilePath();
    std::string CheckAlignmentFilePath();
    
    void SetChainName(std::string name);
    std::string GetChainName();
    std::string CheckChainName();
    
    void CheckCLIOptions();
    
    void Run();
    
};
