/*****************************************************************************/
/*!
* \file   AVLTree.cpp
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: CS280
* \par    Assignment #4
* \date   10/21/14
* 
* \brief
* This file contains the implementation of the following functions for the
* AVLTree C++ assignment.
* 
* Hours spent on this assignment: 3
* 
* Specific portions that gave you the most trouble:
*/
/*****************************************************************************/

/*****************************************************************************/
/*!
* Constructor for a AVLTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param OA The allocator to use for all of the AVLTree's allocations.
* \param ShareOA If the BSTree object must create its own allocator.
*
*/
/*****************************************************************************/
template <typename T>
AVLTree<T>::AVLTree(ObjectAllocator *OA, bool ShareOA) : BSTree<T>(OA, ShareOA){
  // handled by BSTree constructor
}

/*****************************************************************************/
/*!
* Destructor for an AVLTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
*/
/*****************************************************************************/
template <typename T>
AVLTree<T>::~AVLTree(){
  // BSTree destructor handles this
}

/*****************************************************************************/
/*!
* To insert a node into the AVLTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param value The value to be inserted.
*
*/
/*****************************************************************************/
template <typename T>
void AVLTree<T>::insert(const T& value){
  insert_node_avl(BSTree<T>::root_, value);
}

/*****************************************************************************/
/*!
* To remove a node from the AVLTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param value The value to be removed.
*
*/
/*****************************************************************************/
template <typename T>
void AVLTree<T>::remove(const T& value){
  remove_node_avl(BSTree<T>::root_, value);
}

/*****************************************************************************/
/*!
* Returns true if efficiency implemented.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \return bool Whether or not efficiency was implemented.
*
*/
/*****************************************************************************/
template <typename T>
bool AVLTree<T>::ImplementedBalanceFactor(void){
  return false;
}

/*****************************************************************************/
/*!
* To insert a node into the AVLTree, calls helper inserter.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree The root of the tree to insert into.
* \param value The value to be inserted into the tree.
*
*/
/*****************************************************************************/
template <typename T>
void AVLTree<T>::insert_node_avl(typename BSTree<T>::BinTree &tree, const T& value){
  std::stack<typename BSTree<T>::BinTree*> nodes;
  insert_node_avl_helper(tree, value, nodes);
}

/*****************************************************************************/
/*!
* To insert a node into the AVLTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree Initially the root of the tree to insert into.
* \param value The value to insert into the tree.
* \param nodes A stack of visited nodes.
*
*/
/*****************************************************************************/
template <typename T>
void AVLTree<T>::insert_node_avl_helper(typename BSTree<T>::BinTree &tree, const T& value, 
  std::stack<typename BSTree<T>::BinTree*> &nodes){
  // perform insertion the same as a BSTree
  if (tree == 0)
  {
    tree = this->make_node(value);
    tree->count++;
    BSTree<T>::size_++;
    balance_tree(nodes);
  }
  else if (value < tree->data)
  {
    nodes.push(&tree); //push visited node
    tree->count++;
    insert_node_avl_helper(tree->left, value, nodes);
  }
  else
  {
    nodes.push(&tree); //push visited node
    tree->count++;
    insert_node_avl_helper(tree->right, value, nodes);
  }
}

/*****************************************************************************/
/*!
* Recursive helper to remove a node from the AVLTree
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree The root of the tree to remove from.
* \param value The value to be removed from the tree.
*
*/
/*****************************************************************************/
template <typename T>
void AVLTree<T>::remove_node_avl(typename BSTree<T>::BinTree &tree, const T& value){
  std::stack<typename BSTree<T>::BinTree*> nodes;
  remove_node_avl_helper(tree, value, nodes);
}

/*****************************************************************************/
/*!
* To help in removing a node recursively from the AVLTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree Initially the root of the tree to remove from.
* \param value The value to be removed from the tree.
* \param nodes A stack of visited nodes.
*
*/
/*****************************************************************************/
template <typename T>
void AVLTree<T>::remove_node_avl_helper(typename BSTree<T>::BinTree &tree, const T& value, 
  std::stack<typename BSTree<T>::BinTree*> &nodes){
  if (tree == 0)
  {
    return;
  }
  else if (value < tree->data)
  {
    nodes.push(&tree); //push visited node
    tree->count--;
    remove_node_avl_helper(tree->left, value, nodes);
  }
  else if (value > tree->data)
  {
    nodes.push(&tree); //push visited node
    tree->count--;
    remove_node_avl_helper(tree->right, value, nodes);
  }
  else // tree->data == value
  {
    if (tree->left == 0)
    {
      typename BSTree<T>::BinTree temp = tree;
      tree = tree->right;
      this->free_node(temp);
      balance_tree(nodes); //balance after remove
    }
    else if (tree->right == 0)
    {
      typename BSTree<T>::BinTree temp = tree;
      tree = tree->left;
      this->free_node(temp);
      balance_tree(nodes); //balance after remove
    }
    else
    {
      typename BSTree<T>::BinTree pred = 0;
      this->find_predecessor(tree, pred);
      tree->data = pred->data;
      tree->count--;
      remove_node_avl_helper(tree->left, tree->data, nodes);
    }
  }
}

/*****************************************************************************/
/*!
* To balance the AVLTree.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param nodes A stack of nodes that were visited.
*
*/
/*****************************************************************************/
template <typename T>
void AVLTree<T>::balance_tree(std::stack<typename BSTree<T>::BinTree*> &nodes){
  while (!nodes.empty())
  {
    typename BSTree<T>::BinTree &node = *(nodes.top());
    nodes.pop();
    int leftheight = BSTree<T>::tree_height(node->left);
    int rightheight = BSTree<T>::tree_height(node->right);
    if (std::abs(rightheight - leftheight) > 1)
    {
      // if unbalanced on the right
      if (rightheight > leftheight)
      {
        typename BSTree<T>::BinTree &right = node->right;
        // if right child is unbalanced on left
        if (BSTree<T>::tree_height(right->left) > BSTree<T>::tree_height(right->right))
        {
          // perform a right rotation about right child
          rotate_right(right);
          // and a left rotation about node
          rotate_left(node);
        }
        else // right child is unbalanced on right
        {
          rotate_left(node);
        }
      
      }
      else //unbalanced on left
      {
        typename BSTree<T>::BinTree &left = node->left;
        // if left child is unbalanced to right
        if (BSTree<T>::tree_height(left->left) < BSTree<T>::tree_height(left->right))
        {
          // perform a left rotation about left child
          rotate_left(left);
          // and a right rotation about node
          rotate_right(node);
        }
        else // left child is unbalanced to left
        {
          rotate_right(node);
        }
      }
    }
  }
}

/*****************************************************************************/
/*!
* To rotate the AVLTree right.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree The node of the tree to rotate about.
*
*/
/*****************************************************************************/
template <typename T>
void AVLTree<T>::rotate_right(typename BSTree<T>::BinTree &tree){
  typename BSTree<T>::BinTree temp = tree;

  unsigned tempcount = temp->count;
  unsigned rightcount = 0;
  unsigned leftchildcount = 0;

  if (tree->right) rightcount = tree->right->count;
  if (tree->left && tree->left->right)
     leftchildcount = tree->left->right->count;

  tree = tree->left;
  temp->left = tree->right;
  tree->right = temp;

  temp->count = rightcount + leftchildcount + 1;
  tree->count = tempcount;
}

/*****************************************************************************/
/*!
* To rotate the AVLTree left.
*
* \author	louis.coyleii
* \date 10/21/14
*
* \param tree The node of the tree to rotate about
*
*/
/*****************************************************************************/
template <typename T>
void AVLTree<T>::rotate_left(typename BSTree<T>::BinTree &tree){
  typename BSTree<T>::BinTree temp = tree;

  unsigned tempcount = temp->count;
  unsigned leftcount = 0;
  unsigned rightchildcount = 0;

  if (tree->left) leftcount = tree->left->count;
  if (tree->right && tree->right->left)
    rightchildcount = tree->right->left->count;

  tree = tree->right;
  temp->right = tree->left;
  tree->left = temp;

  temp->count = leftcount + rightchildcount + 1;
  tree->count = tempcount;
}