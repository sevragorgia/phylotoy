/*
 * phylotoy
 * Class Node
 * objects of this class are nodes on a phylotree
 * 
 */

#include <vector>
#include <string>

class Node {
  
private:
  //some information on the node
  bool is_tip;
  std::string sequence;
  std::string species_name;
  int index;
  float length_of_subtending_branch;
  
  //descendants of this nodes, pointers to them. may need only left right
  std::vector<Node*> child_nodes;
  
  //parent of node
  Node* parent_node;
  
public:
    Node();
    
    void SetSequence(std::string species_sequence);
    std::string GetSequence();
    
    void SetSpeciesName(std::string name);
    std::string GetSpeciesName();
    
    void SetIndex(int node_index);
    int GetIndex();
    
    void SetIsTip(bool tip);
    bool GetIsTip();
    
    void SetParentNode(Node* parent);
    Node* GetParentNode();
    
    void SetLengthSubtendingBranch(float branch_length);
    float GetLengthSubtendingBranch();
    
    void AddNodeToChildVector(Node* child);
    void SetChildVector(std::vector<Node*> childs);
    std::vector<Node*> GetChildVector();
    
    void CreateBifurcatingNode(std::vector<Node*>, int* calls, std::vector<Node*>* tree_nodes);
    
    void GetNodePointer(std::vector<Node*>* tree_nodes);
    
    std::vector<std::string>* GetNodeInfo(std::vector<std::string>* collected_node_info);
    
};
