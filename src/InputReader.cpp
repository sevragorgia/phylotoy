/*
 * phylotoy
 * Class InputReader
 * generic input reader capable of opening/closing files
 * 
 */

#include "InputReader.h"
#include <fstream>
#include <vector>
#include <iostream>

InputReader::InputReader() {}

InputReader::InputReader(std::string path) {
  
  input_file_path = path;
  
}

void InputReader::SetPath(std::string path) {
  
  input_file_path = path;
  
}

std::string InputReader::GetPath() {
  
  return input_file_path;
  
}

std::vector<std::string>* InputReader::ReadInputFile(std::string path){
  
  /* create and open the input stream. This will always be done, we need to control later if the stream 
   * is good or not...  
  */
  
  std::ifstream input_stream(path);
  
  //create a vector of strings to store the data
  std::vector<std::string>* lines = new std::vector<std::string>;
  
  if(input_stream.good()) {
    
    //dummy string to store the first line
    std::string first_line;
  
    //read the first line
    std::getline(input_stream, first_line);
    
    //string to store the lines.
    std::string input_line;
    
    //now read the file line by line and push the line into the vector
    while(std::getline(input_stream, input_line)) {
      
      //add the lines to the string vector
      lines->push_back(input_line);
       
    }
    
    //input_stream.close();
    
  }else {
    
    std::cerr << "Something went wrong reading the alignment file: " << path << "\n";
    exit(1);
    
  }
  
  
  return lines;
  
}

