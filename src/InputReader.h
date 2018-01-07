/*
 * phylotoy
 * Class InputReader
 * generic input reader capable of opening/closing files
 * 
 */

#include <vector>
#include <string>

class InputReader {
  private:
    std::string input_file_path;
    
  public:
    InputReader();
    
    InputReader(std::string path);
    
    void SetPath(std::string path);
    std::string GetPath();
    
    std::vector<std::string>* ReadInputFile(std::string path);
};
