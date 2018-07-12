/*****************************************************************************/
/*!
* \file   BSTree.cpp
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: CS280
* \par    Assignment #4
* \date   10/21/14
* 
* \brief
* This file contains the implementation of the following functions for the
* BSTree C++ assignment.
* 
* Hours spent on this assignment: 3
* 
* Specific portions that gave you the most trouble: subscript operator
*/
/*****************************************************************************/

/*****************************************************************************/
/*!
* Constructor for a BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param OA The allocator to use for all of the BSTree's allocations.
* \param ShareOA If the BSTree object is to share an allocator.
*
*/
/*****************************************************************************/
template <typename T>
BSTree<T>::BSTree(ObjectAllocator *OA, bool ShareOA){
  if (ShareOA) // if the tree is to share an allocator
  {
    oa_ = OA; // use the supplied allocator
    freeoa_ = false; // allocator is not to be freed by this tree
    shareoa_ = true; // share this allocator on copying this tree
  }
  else // otherwise, tree must create its own allocator
  {
    OAConfig config(true); // set UseCPPMemManager to true, default others
    oa_ = new ObjectAllocator(sizeof(BinTreeNode), config);

    freeoa_ = true; // allocator is to be freed by this tree
    shareoa_ = false; // do not share this allocator with any other tree
  }
  root_ = 0;
  size_ = 0;
}

/*****************************************************************************/
/*!
* Copy constructor for a BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param rhs The BStree to copy construct from.
*
*/
/*****************************************************************************/
template <typename T>
BSTree<T>::BSTree(const BSTree& rhs){
  if (rhs.shareoa_) // if the tree is to share an allocator
  {
    oa_ = rhs.oa_; // use the supplied allocator
    freeoa_ = false; // allocator is not to be freed by this tree
    shareoa_ = true; // share this allocator on copying this tree
  }
  else // otherwise, tree must create its own allocator
  {
    OAConfig config(true); // set UseCPPMemManager to true, default others
    oa_ = new ObjectAllocator(sizeof(BinTreeNode), config);

    freeoa_ = true; // allocator is to be freed by this tree
    shareoa_ = false; // do not share this allocator with any other tree
  }
  
  copy_tree(root_, rhs.root_);
  size_ = rhs.size_;
  // finish the copy construction
}

/*****************************************************************************/
/*!
* Destructor for a BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
*/
/*****************************************************************************/
template <typename T>
BSTree<T>::~BSTree(){
  clear();
  if (freeoa_) // if the allocator is to be freed by this tree
  {
    delete oa_;
  }
  // else, we are done, deleting the allocator will be handled elsewhere
}

/*****************************************************************************/
/*!
* Assignment operator for a BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param rhs The BSTree to assign from.
*
* \return BSTree<T>& The new BSTree, assigned from the rhs.
*
*/
/*****************************************************************************/
template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree& rhs){
  // check for self-assignment
  if (this == &rhs)
    return *this;

  // clear the tree to assign to before assigning
  clear();

  if (rhs.shareoa_) // if the tree is to share an allocator
  {
    oa_ = rhs.oa_; // use the supplied allocator
    freeoa_ = false; // allocator is not to be freed by this tree
    shareoa_ = true; // share this allocator on copying this tree
  }
  else // otherwise, tree must create its own allocator
  {
    OAConfig config(true); // set UseCPPMemManager to true, default others
    oa_ = new ObjectAllocator(sizeof(BinTreeNode), config);

    freeoa_ = true; // allocator is to be freed by this tree
    shareoa_ = false; // do not share this allocator with any other tree
  }

  // do the assignment
  copy_tree(root_, rhs.root_);
  size_ = rhs.size_;
  
  return *this;
}

/*****************************************************************************/
/*!
* Subscript operator for a BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param index The index of the node to access.
*
* \return BinTree Pointer to the node at index.
*
*/
/*****************************************************************************/
template <typename T>
const typename BSTree<T>::BinTreeNode* BSTree<T>::operator[](int index) const{
  // if root is null, the index is out of bounds, or negative
  // then return null
  if (root_ == 0 || index > static_cast<int>(size_) || index < 0)
    return 0;
  // recursively search the root subtrees looking for index
  const BinTreeNode* indexnode = find_index(root_, index);
  
  return indexnode;
}

/*****************************************************************************/
/*!
* Helper function for subscript operator.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree Initially the root of the tree to search in.
* \param index The index to find node for.
*
* \return BinTreeNode* The node at index.
*
*/
/*****************************************************************************/
template <typename T>
const typename BSTree<T>::BinTreeNode* BSTree<T>::find_index(BinTree tree, int index) const{
  if (tree == 0)
  {
    return 0;
  }

  // Assume that L is the number of nodes in the left subtree.
  int nodesinleft = 0;

  if (tree->left)  
    nodesinleft = static_cast<int>(tree->left->count);

  // If the left subtree has more than i nodes (L > i), then it's in the left subtree.
  if (nodesinleft > index)
  {
    // Recursively call the method with the left node and the index.
    return find_index(tree->left, index);
  }

  // If the left subtree has less than i nodes (L < i), then it's in the right subtree.
  else if (nodesinleft < index)
  {
    //Recursively call the method with the right node and i - L - 1.
    return find_index(tree->right, index - nodesinleft - 1);
  }

  // Else the left subtree has exactly i nodes so it's in the current node.
  return tree;
}

/*****************************************************************************/
/*!
* To insert a node into the BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param value The value to be inserted.
*
*/
/*****************************************************************************/
template <typename T>
void BSTree<T>::insert(const T& value){
  insert_node(root_, value);
}

/*****************************************************************************/
/*!
* To remove a node from the BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param value The value to be removed.
*
*/
/*****************************************************************************/
template <typename T>
void BSTree<T>::remove(const T& value){
  delete_node(root_, value);
}

/*****************************************************************************/
/*!
* Clears all nodes from the BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
*/
/*****************************************************************************/
template <typename T>
void BSTree<T>::clear(void){
  if (root_ == 0)
    return;
  free_all_nodes(root_);
}

/*****************************************************************************/
/*!
* Clears all nodes from the BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree Initially the root of the tree to clear.
*
*/
/*****************************************************************************/
template <typename T>
void BSTree<T>::free_all_nodes(BinTree &tree){
  if (tree)
  {
    free_all_nodes(tree->left);
    free_all_nodes(tree->right);
    free_node(tree);
    tree = 0;
  }
}

/*****************************************************************************/
/*!
* Finds a node in the BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param value The value to find in the BSTree.
* \param compares Reference to the number of compares needed to find node.
*
* \return bool Whether or not the node was found.
*
*/
/*****************************************************************************/
template <typename T>
bool BSTree<T>::find(const T& value, unsigned &compares) const{
  return find_node(root_, value, compares);
}

/*****************************************************************************/
/*!
* Returns if the BSTree is empty.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \return bool Whether or not the BSTree is empty.
*
*/
/*****************************************************************************/
template <typename T>
bool BSTree<T>::empty(void) const{
  if (root_ == 0)
    return true;
  else
    return false;
}

/*****************************************************************************/
/*!
* Returns the number of nodes in the BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \return unsigned int The number of nodes in the BSTree.
*
*/
/*****************************************************************************/
template <typename T>
unsigned int BSTree<T>::size(void) const{
  return size_;
}

/*****************************************************************************/
/*!
* Returns the height of the BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \return int The maximum depth of the BSTree.
*
*/
/*****************************************************************************/
template <typename T>
int BSTree<T>::height(void) const{
  return tree_height(root_);
}

/*****************************************************************************/
/*!
* Returns the root of the BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \return BinTree Pointer to the root node of the BSTree.
*
*/
/*****************************************************************************/
template <typename T>
typename BSTree<T>::BinTree BSTree<T>::root(void) const{
  return root_;
}

/*****************************************************************************/
/*!
* Gettor for the root of a BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \return BinTree& The root of the BSTree.
*
*/
/*****************************************************************************/
template <typename T>
typename BSTree<T>::BinTree& BSTree<T>::get_root(void){
  return root_;
}

/*****************************************************************************/
/*!
* Constructor for a node.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param value The value to create the node with.
*
* \return BinTree Pointer to the created node.
*
*/
/*****************************************************************************/
template <typename T>
typename BSTree<T>::BinTree BSTree<T>::make_node(const T& value){
  try
  {
    return new (oa_->Allocate())BinTreeNode(value);
  }
  catch (const OAException &e)
  {
    throw(BSTException(BSTException::E_NO_MEMORY, e.what()));
  }
}

/*****************************************************************************/
/*!
* Destructor for a node.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param node The node to be freed.
*
*/
/*****************************************************************************/
template <typename T>
void BSTree<T>::free_node(BinTree node){
  node->~BinTreeNode();
  oa_->Free(node); 
  size_--;
}

/*****************************************************************************/
/*!
* Gettor for the height of a BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree The tree to get the height of.
*
* \return int The height of the BSTree.
*
*/
/*****************************************************************************/
template <typename T>
int BSTree<T>::tree_height(BinTree tree) const{
  if (tree == 0)
    return -1;
  else
    return (1 + max(tree_height(tree->left), tree_height(tree->right)));
}

/*****************************************************************************/
/*!
* Finds the predecessor of the node.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree The node to get the predecessor of.
* \param predecessor The predecessor of the supplied node.
*
*/
/*****************************************************************************/
template <typename T>
void BSTree<T>::find_predecessor(BinTree tree, BinTree &predecessor) const{
  predecessor = tree->left;
  while (predecessor->right != 0)
    predecessor = predecessor->right;
}

/*****************************************************************************/
/*!
* Finds the node with value.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree Pointer to the root of tree to find in.
* \param value The data to search for.
* \param compares Counter for the number of times fn is called.
*
*/
/*****************************************************************************/
template <typename T>
bool BSTree<T>::find_node(BinTree tree, const T& value, unsigned &compares) const{
  ++compares;
  if (tree == 0)
    return false;
  else if (value == tree->data)
    return true;
  else if (value < tree->data)
    return find_node(tree->left, value, compares);
  else
    return find_node(tree->right, value, compares);
}

/*****************************************************************************/
/*!
* Deletes the node with value from tree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree Pointer to root of tree to delete from.
* \param value The value of node to be deleted.
*
*/
/*****************************************************************************/
template <typename T>
void BSTree<T>::delete_node(BinTree &tree, const T& value){
  if (tree == 0)
    return;
  else if (value < tree->data)
  {
    tree->count--;
    delete_node(tree->left, value);
  }
  else if (value > tree->data)
  {
    tree->count--;
    delete_node(tree->right, value);
  }
  else // (value == tree->data)
  {
    tree->count--;
    if (tree->left == 0)
    {
      BinTree temp = tree;
      tree = tree->right;
      free_node(temp);
    }
    else if (tree->right == 0)
    {
      BinTree temp = tree;
      tree = tree->left;
      free_node(temp);
    }
    else
    {
      BinTree pred = 0;
      find_predecessor(tree, pred);
      tree->data = pred->data;
      delete_node(tree->left, tree->data);
    }
  }
}

/*****************************************************************************/
/*!
* Inserts a node with value into tree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree Pointer to root of tree to insert into.
* \param value The data for the node to be inserted.
*
*/
/*****************************************************************************/
template <typename T>
void BSTree<T>::insert_node(BinTree &tree, const T& value){
  if (tree == 0)
  {
    tree = make_node(value);
    tree->count++;
    size_++;
  }
  else if (value < tree->data)
  {
    tree->count++;
    insert_node(tree->left, value);
  }
  else
  {
    tree->count++;
    insert_node(tree->right, value);
  }
}

/*****************************************************************************/
/*!
* Determines which parameter is the max.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param first The first value to compare.
* \param second The second value to compare.
*
* \return int The value of the max of the two inputs.
*
*/
/*****************************************************************************/
template <typename T>
int BSTree<T>::max(const int first, const int second) const{
  if (first > second)
    return first;
  else
    return second;
}

/*****************************************************************************/
/*!
* Copies the BSTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree The tree to copy to.
*
*/
/*****************************************************************************/
template <typename T>
void BSTree<T>::copy_tree(BinTree &copy, BinTree tree){
  if (tree == 0)
    return;

  copy = make_node(tree->data);
  copy->count = tree->count;
    
  copy_tree(copy->left, tree->left);
  copy_tree(copy->right, tree->right);
}