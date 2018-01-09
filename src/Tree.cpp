#include <vector>
#include <string>
#include "Tree.h"
#include <sstream>

#include <iostream>


//public methods


Tree::Tree(){}
  
void Tree::SetLength(float length){

    length = length;
  
}

float Tree::GetLength(){
  
  return length;
  
}
    
void Tree::SetRoot(Node* root_node){
  
  current_root = root_node;
  
}


Node* Tree::GetRoot(){
  
  return current_root;
  
}

void Tree::SetTreeNodes(std::vector<Node*> nodes){
  
  tree_nodes = nodes;
  
}

std::vector<Node*> Tree::GetTreeNodes(){
  
  return tree_nodes;
  
}


void Tree::AddToNodeVector(Node* node){
  
  std::cerr << "here\n";
  tree_nodes.push_back(node);
  
}

/**
 * This method creates a star tree. This tree adds all the tip nodes in one alignment to the root node.
 * 
 * @param alignment is a sequence alignment with species names and sequences separated by an empty space.
 */
int Tree::CreateStarTree(std::vector<std::string>* alignment){
  
  std::cerr << "Creating star tree\n";
  
  //initialize the root node
  Node* current_root = new Node();
  current_root->SetIsTip(false);
  current_root->SetIndex(alignment->size());
  
  //send the alignment to our private tip node initializer
  current_root->SetChildVector(this->InitializeTipNodes(alignment));

  //once all tips have been added as childs to the root, the root sends a pointer to himself to each of the child nodes.
  for(auto child : current_root->GetChildVector()){
    
    child->SetParentNode(current_root);
    //we also need to set the length of the subtending branch leading to the parent
    
    //finally we need to add this child to the tree list of nodes
    this->AddToNodeVector(child);
  }

  //set current_root node as the root of the tree object
  this->SetRoot(current_root);
  
  //add root to the node vector  
  this->AddToNodeVector(current_root);
  
  return current_root->GetIndex();
  
}
    
/**
* This method creates a bifurcating tree. This method creates as many internodes as required to yield a bifurcating tree.
* 
* @param alignment is a sequence alignment stored on a vector of strings containing species names and sequencesseparated by an empty space.
*/
int Tree::CreateBifurcatingTree(std::vector<std::string>* alignment){
  
  int current_node_index = alignment->size();
  
  //we need to initialize the root node
  Node* current_root = new Node();
  current_root->SetIsTip(false);
  current_root->SetIndex(current_node_index);
  
  //once the root node has been initialized we add it as the tree root and to the list of tree nodes
  this->SetRoot(current_root);
  this->AddToNodeVector(current_root);
  
  std::cerr << "Creating bifurcating tree with " << current_node_index << " species\n";

  current_node_index = current_node_index + 1;
  
  //we initialize the tip nodes using the alignment provided by the user
  current_root->CreateBifurcatingNode(this->InitializeTipNodes(alignment), current_node_index, tree_nodes);
  
  //return the total number of nodes in the tree
  return current_node_index;
  
}
  
/**
 * This method returns information on the nodes currently included in the tree.
 * It recursively traverses the tree starting from the root node and asks each node for its info as a string that is stored on a vector of 
 * strings.
 * 
 * @returns a vector of strings
 */
std::vector<std::string>* Tree::CollectTreeNodesInfoRecursively(){
  
  std::vector<std::string>* tree_nodes_info = new std::vector<std::string>;
  
  std::cerr << "at tree root\n";
  tree_nodes_info = current_root->GetNodeInfo(tree_nodes_info);
  
  return tree_nodes_info;
}

/**
 * This method returns information on the nodes currently included in the tree.
 * It used the tree_nodes vector of Node pointer to iteratively retrieve the Node information 
 * 
 * @returns a vector of strings
 */
std::vector<std::string>* Tree::CollectTreeNodesInfoIteratively(){
  
  std::vector<std::string>* tree_nodes_info = new std::vector<std::string>;
  
  std::cerr << "iterating over " << tree_nodes.size() << " tree nodes to get their information\n";
  
  for (auto node : tree_nodes){
    
    if(node->GetIsTip()){
      
      //node is a tip, get the species name and sequence
      std::string node_info = std::to_string(node->GetIndex()) + ' ' + node->GetSpeciesName() + ' ' + node->GetSequence();
      tree_nodes_info->push_back(node_info);
      std::cerr << "adding tip: " << node_info << " to information vector\n";
      
    }else{
      //node is an internode get the index only
      std::string node_info = std::to_string(node->GetIndex());
      tree_nodes_info->push_back(node_info);
      std::cerr << "adding internode: " << node_info << " to information vector\n";
      
    }
    
  }
  
  return tree_nodes_info;
}

/**
 * In case we need to update the list of Nodes in the tree_nodes list, this method should provide a way to get pointers to all the nodes
 * in the tree recursively
 * 
 */

void Tree::GetTreeNodeVector(){
   
  std::cerr << "at tree root\n";
  current_root->GetNodePointer(&tree_nodes);
  
}

/**
 * This methods recursively calls every Node in the tree and produces a string with the tree in newick format.
 * 
 * @returns a string object with the tree in newick format.
 */

std::string Tree::GetTreeInNewickFormat(){
  
  std::string newick_tree;
  
  current_root->GetNodeInfoInNewickFormat(newick_tree);
  
  newick_tree.append(";");
  
  return newick_tree;
  
}

//private methods

/**
 * This method initializes the tip nodes of the phylogenetic tree based on the passed alignment.
 * 
 * @param alignment is a sequence alignment stored on a vector of strings containing species names and sequencesseparated by an empty space.
 * 
 * @returns a vector of Node*
 */

std::vector<Node*> Tree::InitializeTipNodes(std::vector<std::string>* alignment){
  
  /**
   * Before we can create a tree object we need to initialize the tip nodes based on the alignment provided by the user.
   * For this we need to extract the species name and the sequence and create an object Node for each of the species in the tree.
   * These Nodes are stored in a vector of Nodes that is returned to the calling method.
   */
  
  std::vector<Node*> tip_nodes;
  int node_index = 0;
  
  for(auto line : *alignment) {
    
    /**
     * Each line of the alignment contains a species name and a sequence, and we want this to be stored in a Node object.
     * In addition for each node we set an arbitrary integer index. This will make easier to select nodes at random later.
     * If the number of species in the alignment is N, the tip nodes will have indices = {0->N}. The internodes will have 
     * indices {N+1->2N-1} (need to check this though.)
     *
     */
    Node* node = new Node;
    node->SetIsTip(true);
    node->SetIndex(node_index);
    
    /**
     * The code used to tokenize the string containing species name and sequence was modified
     * from https://stackoverflow.com/questions/5757721/use-getline-and-while-loop-to-split-a-string
     * 
     * First we create a delimiter char,
     * second we create a stream out of the string we already have extracted from the alignment,
     * third we create a string to store the components of the alignment string and 
     * fourth we read the string in the same way we read files and store the components of the line (i.e. species and sequence) in
     * a new object Node.
     * 
     * Each new object Node is added to a vector of Nodes that is returned.
     */
     
    char delimiter = ' ';
    
    std::istringstream species_sequence(line);
    std::string elements;
    
    /** 
     * Since the alignment always comes in pairs and starts with a species name, in order to create the object node we need to know
     * what are we setting. This boolean helps us here.
     */
     
    bool sequence = false;
    
    while(std::getline(species_sequence, elements, delimiter)){
      
      if(sequence){
        
        //std::string* node_sequence = new std::string(elements);
        node->SetSequence(elements);
        //output_printer.PrintMessage2Out("Creating new node with sequence: " + elements + "\n");
        sequence = false;
        
      }else{
        
        //std::string* node_species_name = new std::string(elements);
        node->SetSpeciesName(elements);
        //output_printer.PrintMessage2Out("Creating new node with species name: " + elements + "\n");
        sequence = true;
      }
    }
    
    tip_nodes.push_back(node);
    node_index++;
  }
  
  return tip_nodes;
}
