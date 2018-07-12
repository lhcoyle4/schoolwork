/*****************************************************************************/
/*!
* \file   AVLTree.h
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: CS280
* \par    Assignment #4
* \date   10/21/14
*
* \brief
* This file contains the implementation of the header file for the
* AVLTree C++ assignment.
*/
/*****************************************************************************/

//---------------------------------------------------------------------------
#ifndef AVLTREE_H
#define AVLTREE_H
//---------------------------------------------------------------------------
#include <stack>
#include "BSTree.h"

template <typename T>
class AVLTree : public BSTree<T>
{
  public:
    AVLTree(ObjectAllocator *OA = 0, bool ShareOA = false);
    virtual ~AVLTree();
    virtual void insert(const T& value);
    virtual void remove(const T& value);

      // Returns true if efficiency implemented
    static bool ImplementedBalanceFactor(void);
    
  private:
    void insert_node_avl(typename BSTree<T>::BinTree &tree, const T& value);
    void insert_node_avl_helper(typename BSTree<T>::BinTree &tree, const T& value, 
                                std::stack<typename BSTree<T>::BinTree*> &nodes);

    void remove_node_avl(typename BSTree<T>::BinTree &tree, const T& value);
    void remove_node_avl_helper(typename BSTree<T>::BinTree &tree, const T& value, 
                                std::stack<typename BSTree<T>::BinTree*> &nodes);
    
    void balance_tree(std::stack<typename BSTree<T>::BinTree*> &nodes);
    void rotate_right(typename BSTree<T>::BinTree &tree);
    void rotate_left(typename BSTree<T>::BinTree &tree);
};

#include "AVLTree.cpp"

#endif
//---------------------------------------------------------------------------
