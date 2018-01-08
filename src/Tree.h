#include <vector>
#include <string>
#include "Node.h"

/**
 * Objects of the class Tree represent phylogenetic trees.
 * These trees are (1) unrooted (the root node used in the code is just an internode of the tree,
 * (2) can be initialized as start trees, (3) can contain polytomies, or (4) can be bifurcating.
 * 
 * This class provide a number of methods to manipulate the tree. For instance, re-rooting the tree.
 * It also provides methods to alter the tree topology using Nearest-neighbor interchange (NNI) or subtree pruning and regraphting (SPR).
 * 
 * A number of attributes of the tree provide short-cuts to make modifying the tree topology or the length of the tree's branches easy.
 * For instance, Tree objects store pointers to all of their nodes and to the current root. This makes easy to rearrange the tree during MCMC.
 * 
 * The Tree Class is also in charge of proposing all modifications to tree topology and branch length.
 * 
 */

class Tree {

private:
  /** 
   * Objects of class Tree store some information that may come handy to manipulate them without necessarily recursing over the nodes of the
   * tree.
   */
  
  Node* current_root;
  float length;

  //this is a vector containing all the nodes in the tree
  std::vector<Node*> tree_nodes; 
  
  //private methods
  
  std::vector<Node*> InitializeTipNodes(std::vector<std::string>* alignment);
  
public:
    Tree();
    
    void SetLength(float length);
    float GetLength();
    
    void SetRoot(Node* root_node);
    Node* GetRoot();
    
    void SetTreeNodes(std::vector<Node*> nodes);
    std::vector<Node*> GetTreeNodes();
    void AddToNodeVector(Node* node);
    
    void GetTreeNodeVector();
    
    void CreateStarTree(std::vector<std::string>* alignment);
    
    void CreateBifurcatingTree(std::vector<std::string>* alignment);
    
    std::vector<std::string>* CollectTreeNodesInfoRecursively();

    std::vector<std::string>* CollectTreeNodesInfoIteratively();
    
    std::string GetTreeInNewickFormat();
};
