/*
 * phylotoy
 * Class Node
 * objects of this class are nodes on a phylotree
 * 
 */

#include <vector>
#include <string>
#include "Node.h"

#include <iostream>

Node::Node(void){}
    
void Node::SetSequence(std::string species_sequence){
  
  std::cerr << "setting sequence\n";
  sequence = species_sequence;
  
}

std::string Node::GetSequence(){
  
  return sequence;  
  
}
    
void Node::SetSpeciesName(std::string name){
  
  std::cerr << "setting species name " << name <<"\n";
  species_name = name;
  
}

std::string Node::GetSpeciesName(){
  
  return species_name;
  
}
    
void Node::SetIsTip(bool tip){
  
  is_tip = tip;
  
}

bool Node::GetIsTip(){
  
  return is_tip;
  
}

void Node::SetIndex(int node_index){
  
  index = node_index;
  
}

int Node::GetIndex(){
  
  return index;
  
}


void Node::SetLengthSubtendingBranch(double branch_length) {
  
  length_of_subtending_branch = branch_length;
  
}

double Node::GetLengthSubtendingBranch() {
  
  return length_of_subtending_branch;
  
}

void Node::SetParentNode(Node* parent){
  
  parent_node = parent;
  
}

Node* Node::GetParentNode(){
  
  return parent_node;
  
}
 
    
void Node::AddNodeToChildVector(Node* child){
  
  child_nodes.push_back(child);
  
}

void Node::SetChildVector(std::vector<Node*> childs){
  
  child_nodes = childs;
  
}

std::vector<Node*> Node::GetChildVector(){
  
  return child_nodes;
  
}

/** 
 * We create the tree as follows:
 * the current node has no children, i.e. the size of the vector child_nodes is 0.
 * We insert the tip node as a child of this node, sending a reference of it to the child node for it to have a pointer to its 
 * parent node.
 * Once this is done, we create a new internode, set this node as its parent and add it to the child_nodes vector of the current node.
 * Then we recursively call this method on the new internode but only if we still have more than 1 tip nodes left. If not, we add 
 * the last tip node to the current internode.
 * 
 * After this happens the vector of tip nodes should be empty and the method returns.
 * 
 * @param tip_nodes: a std::vector of Node pointers containing the tip nodes
 * @param current_node_index: an int pointer to be used to allocate each node with an index.
 * @param tree_nodes: a pointer to a std:vector of Node pointers that contains all nodes in a tree.
 * 
 * 
 */

void Node::CreateBifurcatingNode(std::vector<Node*> tip_nodes, int& current_node_index, std::vector<Node*>& tree_nodes){
  
  std::cerr << "creating bifurcating node " << tip_nodes.size() << "\n";
 
  if(!tip_nodes.empty()){
    
    Node* tip_node_to_insert = tip_nodes.back();
    tip_nodes.pop_back();//this deletes the last element of the array
    
    std::cerr << "inserting tip: " << tip_node_to_insert->GetSpeciesName() << "\n";
    tip_node_to_insert->SetParentNode(this);
    this->AddNodeToChildVector(tip_node_to_insert);
    tree_nodes.push_back(tip_node_to_insert);
    
    if(tip_nodes.size() == 1){
      
      /** 
       * if only one last tip node is left. We can add it to the current internode. This internode should only have
       * 1 descendent tip.
       * 
       */
      
      tip_node_to_insert = tip_nodes.back();
      tip_nodes.pop_back();//this deletes the last element of the array
      
      std::cerr << "inserting last tip: " << tip_node_to_insert->GetSpeciesName() << "\n";
      
      tip_node_to_insert->SetParentNode(this);
      this->AddNodeToChildVector(tip_node_to_insert);
      tree_nodes.push_back(tip_node_to_insert);
      
    }else{
      
      std::cerr << "inserting new internode " << current_node_index << "\n";
      
      Node* internode = new Node();
      internode->SetIsTip(false);
      internode->SetParentNode(this);
      internode->SetIndex(current_node_index);
      this->AddNodeToChildVector(internode);
      tree_nodes.push_back(internode);
      
      current_node_index = current_node_index + 1;//increase the index counter
      internode->CreateBifurcatingNode(tip_nodes, current_node_index, tree_nodes);
      
    }
  }
}


void Node::GetNodePointer(std::vector<Node*>* tree_nodes){
  
  if(child_nodes.empty()) {
    
    std::cerr << "empty child node vector\n";
    
    std::cerr << "adding node " << index << " to node ref vector\n";
    
    tree_nodes->push_back(this);
    
  }else {
    
    std::cerr << "recursively calling nodes" << child_nodes.size() << "\n";
    //for each child node, call this function.
    for(auto child : child_nodes) {
      
      std::cerr << "in for\n"; 
      child->GetNodePointer(tree_nodes);
      
    }
    
    std::cerr << "back at internode \n";
    
    std::cerr << "adding node " << index << " to node ref vector\n";
    
    tree_nodes->push_back(this);
    
  }
  
}


std::vector<std::string>* Node::GetNodeInfo(std::vector<std::string>* collected_node_info){
  
  if(child_nodes.empty()) {
    
    std::cerr << "empty child node vector\n";
    
    //add the tip node index, species name and sequence to the vector collecting the node information
    std::string node_info = std::to_string(index) + ' ' + species_name + ' ' + sequence;
    
    std::cerr << "adding " << node_info << " to info vector\n";
    
    collected_node_info->push_back(node_info);
    
    
  }else {
    
    std::cerr << "recursively calling nodes " << child_nodes.size() << "\n";
    //for each child node, call this function.
    for(auto child : child_nodes) {
      
      std::cerr << "in for\n"; 
      child->GetNodeInfo(collected_node_info);
      
    }
    
    std::cerr << "back at internode \n";
    
    //add internode index to the vector collecting the node information
    std::string node_info = std::to_string(index);
    
    std::cerr << "adding " << node_info << " to info vector\n";
    
    collected_node_info->push_back(node_info);
    
    
  }
  
  return collected_node_info;
  
}

/**
 * This method modifies a 
 * 
 * @param newick_tree: a reference to std::string for the Node currently executing the method to store his information in newick 
 * before calling the method on its children Nodes.
 * 
 * @return void: the method directly modifies the string.
 */
void Node::GetNodeInfoInNewickFormat(std::string& newick_tree){
  
  if(child_nodes.empty()){
    
    std::string child_node_info = species_name + ":" + std::to_string(length_of_subtending_branch);
    newick_tree.append(child_node_info);
    
  }else {
    
    newick_tree.append("(");
    
    /**
     * for each child node, call this function. Note that because we do not have left and right child nodes but a vector of Node objects, 
     * and we want this to be able to implemente polytomies later, we need to check whether the node object at hand is the last of the
     * iterator to write a , or not.
     * 
     */
    
    for(auto child : child_nodes) {
      
      child->GetNodeInfoInNewickFormat(newick_tree);
      
      if(child->GetIsTip() && child != child_nodes.back()){
      
        newick_tree.append(",");
        
      }else {
        
        std::string internode_info = "):" + std::to_string(length_of_subtending_branch);
        newick_tree.append(internode_info);
        
      }
    }
  }
}
