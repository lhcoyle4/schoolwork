/*****************************************************************************/
/*!
* \file   BList.cpp
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: CS280
* \par    Assignment #2
* \date   09/20/14
* 
* \brief
* This file contains the implementation of the necessary functions for the
* BList C++ assignment.
* 
* Hours spent on this assignment: 8
* 
* Specific portions that gave you the most trouble: Edge cases.
*/
/*****************************************************************************/

/*****************************************************************************/
/*!
* Default constructor.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node.
*/
/*****************************************************************************/

template <typename T, int Size>
BList<T, Size>::BList(){
  // initialize head and tail
  head_ = 0;
  tail_ = 0;
  // construct the stats
  stats = BListStats();
  // set the array size using the int paramater
  stats.ArraySize = Size;
  // and the nodesize by using the size of the template parameter * size
  stats.NodeSize = Size * sizeof(T);
}

/*****************************************************************************/
/*!
* Copy Constructor.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node.
* \param	rhs	    The right hand side.
*/
/*****************************************************************************/

template <typename T, int Size>
BList<T, Size>::BList(const BList &rhs){
  // reset the list, because it will be getting all its new elements from rhs
  head_ = 0;
  tail_ = 0;
  
  // start the copy at the head
  BNode* tocopy = rhs.head_;
  
  // copy over the stats from the rhs
  stats.NodeSize = rhs.stats.NodeSize;
  stats.ArraySize = rhs.stats.ArraySize;

  // copy over the head
  if (!head_)
    head_ = copy_node(tocopy);
  // and at this point the head is also tail, because there is only one node
  if (!tail_)
    tail_ = head_;

  // prepare to copy the next node from rhs
  tocopy = tocopy->next;

  // copy over all nodes in rhs, until tocopy points at null
  while (tocopy){
    // make a copy of the current node in rhs
    BNode* copy = copy_node(tocopy);

    // and add the node to the end of the list, using tail pointer
    tail_->next = copy;
    copy->prev = tail_;

    // update the tail pointer
    tail_ = copy;

    // move to the next node in rhs
    tocopy = tocopy->next;
  }

}

/*****************************************************************************/
/*!
* Destructor.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node.
*/
/*****************************************************************************/

template <typename T, int Size>
BList<T, Size>::~BList() NOEXCEPT(true){
  // delete all the data for the BList
  clear();
}

/*****************************************************************************/
/*!
* Assignment operator.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \exception	BListException	Thrown when a B List error condition occurs.
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node.
* \param	rhs   	The right hand side.
*
* \return	The result of the operation.
*/
/*****************************************************************************/

template <typename T, int Size>
BList<T, Size>& BList<T, Size>::operator=(const BList<T, Size> &rhs) NOEXCEPT(false){
  // initialize the node to copy to the head of rhs
  BNode* tocopy = rhs.head_;
  
  // check for self-assignment 
  if (this == &rhs)
    return *this;

  // clear the list that will be assigned to
  clear();

  // assign the stats of rhs to this list
  BListStats(rhs.stats.NodeSize, rhs.stats.NodeCount, rhs.stats.ArraySize, 
             rhs.stats.ItemCount);

  // copy the head node from rhs into this
  if (!head_)
    head_ = copy_node(tocopy);
  // and because there is only one node, the tail is also the head
  if (!tail_)
    tail_ = head_;

  // increment rhs to the next node
  tocopy = tocopy->next;

  // copy over all nodes in rhs
  while (tocopy){
    // make a copy of the current node in rhs
    BNode* copy = copy_node(tocopy);

    // use the tail pointer to add it to end of this
    tail_->next = copy;
    // and update the prev pointer of the copied node to the old tail
    copy->prev = tail_;

    // update the tail pointer to the new node
    tail_ = copy;

    // look at the next node in rhs
    tocopy = tocopy->next;
  }

   // return the updated list
   return *this;
}

/*****************************************************************************/
/*!
* Pushes value onto back of the list, arrays will be unsorted.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \exception	BListException	Thrown when a B List error condition occurs.
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node.
* \param	value	The value.
*/
/*****************************************************************************/

template <typename T, int Size>
void BList<T, Size>::push_back(const T& value) NOEXCEPT(false){
  // make a copy of the tail of the list 
  BNode* oldtail = tail_;
  
  // if there is no tail (the list is empty)
  if (!tail_)
  {
    // then make a new node with the provided value
    BNode* newtail = new_node(value);
    // and assign it to the tail
    tail_ = newtail;
  }
  else
  {
    // otherwise, insert it after or into the tail node, with value
    insert_after(oldtail, value);
  }
  
  // if there is no head (the list was empty) then the tail is also the head
  if (!head_)
    head_ = tail_;
}

/*****************************************************************************/
/*! 
* Pushes value onto front of the list, arrays will be unsorted.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \exception	BListException	Thrown when a B List error condition occurs.
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node.
* \param	value	The value.
*/
/*****************************************************************************/

template <typename T, int Size>
void BList<T, Size>::push_front(const T& value) NOEXCEPT(false){
  // make a copy of the old head of the list
  BNode* oldhead = head_;

  // if there is no head (the list is empty)
  if (!head_)
  {
    // then make a new node with value
    BNode* newhead = new_node(value);
    // and assign it to the head
    head_ = newhead;
  }
  else
  {
    // shift values over to make room for new value at front
    insert_before(oldhead, value);
  }

  // if there is no tail (the list was empty) then the tail is also the head
  if (!tail_)
    tail_ = head_; 
}

/*****************************************************************************/
/*!
* Inserts values into the list, arrays will be sorted.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \exception	BListException	Thrown when a B List error condition occurs.
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node.
* \param	value	The value.
*/
/*****************************************************************************/

template <typename T, int Size>
void BList<T, Size>::insert(const T& value) NOEXCEPT(false){

  //if the list is empty just push the new value into a new node as head
  if (!head_)
  {
    push_front(value);
    return;
  }
  //if the value is smaller than the value in the head node
  if (value < head_->values[0])
  {
    // and if the array size is 1, or the head is full
    if (stats.ArraySize == 1 || !full(head_))
    {
      // then just push the value into a new node as the head
      push_front(value);
      return;
    }
    else
    {
      // otherwise, try to put the node into the head node
      split_node(head_, value);
    }
  }
  //if the value is larger than the value in the last element
  //and the tail is not full, then push back
  if (tail_->values[tail_->count - 1] < value && !full(tail_))
  {
    push_back(value);
    return;
  }

  // otherwise, we have to loop over the list, looking for the node that the value
  // fits into, so create a copy of the head
  BNode * currentnode = head_;

  // loop over the list
  while (currentnode)
  {
    // if there is a next node
    if (currentnode->next)
    {
      // then make a copy of it
      BNode* nextnode = currentnode->next;

      //if the first value in the next node is bigger
      //then must place in the currentnode
      if (value < nextnode->values[0])
      {
        // so if the current node is not full
        if (!full(currentnode))
        {
          // then insert the value into the current node
          insert_into(currentnode, value);
          return;
        }
        // otherwise, the current node is full
        else
        {
          // so if the number of elements in each node is more than one
          if (stats.ArraySize > 1)
          {
            // then if the next node is not full, and the value is more than
            // the max element of the current node
            if (!full(nextnode) && 
                currentnode->values[currentnode->count - 1] < value)
            {
              // then insert the value into the next node
              insert_into(nextnode, value);
              return;
            }
            // otherwise, split the current node and put the value in one of the halves
            else
            {
              split_node(currentnode, value);
              return;
            }
          }
          // otherwise, each node only has one element,
          else
          {
            // so insert the value before the next node
            insert_before(nextnode, value);
            return;
          }
        }
      }
    }
    //if there is no next node
    else
    {
      // then if the current node isn't full,
      if (!full(currentnode))
      {
        // put the value into the current node
        insert_into(currentnode, value);
        return;
      }
      // if the current node is full
      else
      {
        // then if there are more than one element in each node
        if (stats.ArraySize > 1)
        {
          // split the current node, and put the value in one of the halves
          split_node(currentnode, value);
          return;
        }
        // otherwise, there is more than one element in each node
        else
        {
          // so we can insert after the current node
          insert_after(currentnode, value);
          return;
        }
      }
    }
    // keep looking through the nodes
    currentnode = currentnode->next;
  }
}

/*****************************************************************************/
/*!
* Removes the element by the given index.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \exception	BListException	Thrown when a B List error condition occurs.
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node.
* \param	index	Zero-based index of the list.
*/
/*****************************************************************************/

template <typename T, int Size>
void BList<T, Size>::remove(int index) NOEXCEPT(false){
  // make copy of head node, for looping over list
  BNode* currentnode = head_;
  // count of items looked at to 0
  int count = 0;

  // loop over the list
  while (currentnode)
  {
    // and over the items in the node
    for (int i = 0; i < currentnode->count; ++i)
    {
        // if the element in node is at the index
        if (count == index)
        {
          // and the current node only has this element
          if (currentnode->count == 1)
          {
            // then if the current node is the head
            if (currentnode == head_)
              // the new head is the next node
              head_ = currentnode->next;
            // and if the current node is the tail
            if (currentnode == tail_)
              // the new tail is the previous node
              tail_ = currentnode->prev;
            // now remove the node with the element at index
            remove_node(currentnode);
            return;
          }
          // otherwise, the current node has more than one element
          else
          {
            // so overwrite the element by shifting over the others
            for (int j = i; j < currentnode->count - 1; ++j)
              currentnode->values[j] = currentnode->values[j + 1];
            // and update the item count for the list
            stats.ItemCount--;
            // and for the node
            currentnode->count--;
          }
        }
        // keep looking for the index
        ++count;
    }
    // keep looking in the nodes
    currentnode = currentnode->next;
  }
}

/*****************************************************************************/
/*!
* Removes the element by the given value.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node.
* \param	value	The value to remove.
*/
/*****************************************************************************/

template <typename T, int Size>
void BList<T, Size>::remove_by_value(const T& value){
  // temp copy of head, to iterate
  BNode* currentnode = head_;

  // loop over the list
  while (currentnode){
    // loop over the items in the node
    for (int i = 0; i < currentnode->count; ++i)
    {
      // if the current element in current node has the value
      if (currentnode->values[i] == value)
      { 
        // then if the node only has this element
        if (currentnode->count == 1)
        {
          // check if it is the head
          if (currentnode == head_)
            // if so, the next node will be the new head
            head_ = currentnode->next;
          // check if it is the tail
          if (currentnode == tail_)
            // then the previous node will be the new tail
            tail_ = currentnode->prev;
          // now remove this node, because it has the value
          remove_node(currentnode);
          // and end
          return;
        }
        // if the current node has more than one element
        else
        {
          // then overwrite this element by shifting the other elements on top of it
          for (int j = i; j < currentnode->count - 1; ++j)
            currentnode->values[j] = currentnode->values[j + 1];
          // then decrement item count for the list
          stats.ItemCount--;
          // and for the node
          currentnode->count--;
        }
      }
    }
    // keep looking through nodes
    currentnode = currentnode->next;
  }

}

/*****************************************************************************/
/*! 
* Searches for the first match for the given constant.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node.
* \param	value	The value to search for.
*
* \return	An int, being the index of the element containing value.
*/
/*****************************************************************************/

template <typename T, int Size>
int BList<T, Size>::find(const T& value) const{
  // make a copy of the head node, so we can iterate over the list
  BNode* currentnode = head_;
  // start count at 0, to be updated to the index of the node with value
  int count = 0;

  // loop over the list
  while (currentnode){
    // loop over items in node
    for (int i = 0; i < currentnode->count; ++i)
    {
      // if the current item in current node has the value
      if (currentnode->values[i] == value)
        // then return current count
        return count;
      else
        // otherwise, increment count and keep looking
        ++count;
    }
    // if the value wasn't in this node, look in the next one
    currentnode = currentnode->next;
  }
  // if the value wasn't found, return -1
  return -1;
}

/*****************************************************************************/
/*!
* Subscript operator for l-values.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \exception	BListException	Thrown when a B List error condition occurs.
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node.
* \param	index	Zero-based index of the.
*
* \return	The value of the element at the index.
*/
/*****************************************************************************/

template <typename T, int Size>
T& BList<T, Size>::operator[](int index) NOEXCEPT(false){
  // make a copy of the head node, so we can iterate over the list
  BNode* currentnode = head_;
  // count of items looked at starts at 0
  int count = 0;
  // arrayindex to save where we found the index starts at 0
  int arrayindex = 0;
  // a flag to determine when we've found the index
  bool found = 0;
  // try to find the index
  try
  {
    // by looping over the list until it points at null
    while (currentnode)
    {
      // and looping over all the items in each node
      for (int i = 0; i < currentnode->count; ++i)
      {
        // if the count of items looked at is the index
        if (count == index)
        {
          // then we have found the index
          found = 1;
          // and it is at i, the element in the current node
          arrayindex = i;
          // so break
          break;
        }
        // otherwise, increment count and keep looking through the list
        ++count;
      }
      // if the index was found, then end the loop
      if (found)
        break;
      // otherwise, look at the next node
      currentnode = currentnode->next;
    }
  }
  // if the index wasn't found, it is a bad one, so throw an exception
  catch (const std::exception)
  {
    throw(BListException(BListException::E_BAD_INDEX, 
      "const operator[]: Bad index."));
  }
  
  // return the value at index
  return currentnode->values[arrayindex];
}

/*****************************************************************************/
/*!
* Subscript operator for r-values.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \exception	BListException	Thrown when a B List error condition occurs.
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node..
* \param	index	Zero-based index of the.
*
* \return	The value of the element at the index.
*/
/*****************************************************************************/

template <typename T, int Size>
const T& BList<T, Size>::operator[](int index) const NOEXCEPT(false){
  // make a copy of the head node, so we can iterate over the list
  BNode* currentnode = head_;
  // count of items looked at starts at 0
  int count = 0;
  // arrayindex to save where we found the index starts at 0
  int arrayindex = 0;
  // a flag to determine when we've found the index
  bool found = 0;
  // try to find the index
  try
  {
    // by looping over the list until it points at null
    while (currentnode)
    {
      // and looping over all the items in each node
      for (int i = 0; i < currentnode->count; ++i)
      {
        // if the count of items looked at is the index
        if (count == index)
        {
          // then we have found the index
          found = 1;
          // and it is at i, the element in the current node
          arrayindex = i;
          // so break
          break;
        }
        // otherwise, increment count and keep looking through the list
        ++count;
      }
      // if the index was found, then end the loop
      if (found)
        break;
      // otherwise, look at the next node
      currentnode = currentnode->next;
    }
  }
  // if the index wasn't found, it is a bad one, so throw an exception
  catch (const std::exception)
  {
    throw(BListException(BListException::E_BAD_INDEX, 
      "const operator[]: Bad index."));
  }
  
  // return the value at index
  return currentnode->values[arrayindex];
}

/*****************************************************************************/
/*!
* Total number of items (not nodes).
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node..
*
* \return	An unsigned, being the size of the list.
*/
/*****************************************************************************/

template <typename T, int Size>
size_t BList<T, Size>::size(void) const{
  return static_cast<size_t>(stats.ItemCount);
}

/*****************************************************************************/
/*!
* Delete all nodes.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node..
*/
/*****************************************************************************/

template <typename T, int Size>
void BList<T, Size>::clear(void){
  while(!empty()){
    pop_front();
  }
}

/*****************************************************************************/
/*!
* Gets the nodesize.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter.
* \tparam	Size	The number of array elements per node..
*
* \return			An unsigned, being size of the node.
*/
/*****************************************************************************/

template <typename T, int Size>
size_t BList<T, Size>::nodesize(void)
{
  return sizeof(BNode);
}

/*****************************************************************************/
/*!
* Gets the head node of the list. 
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter, data stored in node.
* \tparam	Size	The number of array elements per node..
*
* \return  BNode*  Pointer to the head node of the list.
*/
/*****************************************************************************/

template <typename T, int Size>
const typename BList<T, Size>::BNode* BList<T, Size>::GetHead() const
{
  return head_; 
}

/*****************************************************************************/
/*!
* Returns the stats for the list.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter, data stored in node.
* \tparam	Size	The number of array elements per node..
*
* \return  BListStats  The stats for the list.
*/
/*****************************************************************************/

template <typename T, int Size>
BListStats BList<T, Size>::GetStats() const{
  return stats;
}

/*****************************************************************************/
/*!
* Pops the front of the list.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter, data stored in node.
* \tparam	Size	The number of array elements per node..
*
*/
/*****************************************************************************/

template <typename T, int Size>
void BList<T,Size>::pop_front(void){
  // if there is a head (the list is not empty)
  if (head_)
  {
    // then make a copy of the head
    BNode* nodetodel = head_;

    // unlink the old head
    head_ = head_->next;
    
    // decrement the item count by the number of items in the node to delete
    stats.ItemCount -= nodetodel->count;
    // decrement the node count for the list
    stats.NodeCount--;
    // and delete the node
    delete nodetodel;
  }
  
  // otherwise, the list is empty, so just return
  else return;
}

/*****************************************************************************/
/*!
* Returns whether or not the list is empty.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter, data stored in node.
* \tparam	Size	The number of array elements per node.
*
* \return  bool   Whether or not the array is empty.
*/
/*****************************************************************************/

template <typename T, int Size>
bool BList<T, Size>::empty(void){
  if (!head_)
    return true;
  else
    return false;
}


/*****************************************************************************/
/*!
* Returns a new node with specified value.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter, data stored in node.
* \tparam	Size	The number of array elements per node.
*
* \return  BNode*  The new node with specified value.
*/
/*****************************************************************************/

template <typename T, int Size>
typename BList<T, Size>::BNode* BList<T, Size>::new_node(const T& value){
  // try to make a new node
  BNode* node = 0;
  try
  {
    node = new BNode; 
  }
  // throw out of memory if it fails
  catch (const std::exception)
  {
    throw(BListException(BListException::E_NO_MEMORY, 
      "new_node: Out of memory."));
  }
  
  // set the value in the first element of the node to the provided one
  node->values[0] = value;
  // increment the node count and item count for the list
  stats.NodeCount++;
  stats.ItemCount++;
  // increment the item count for the node
  node->count++;
  // return the new node
  return node;
}

/*****************************************************************************/
/*!
* Removes the node that is pointed to by todelete.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter, data stored in node.
* \tparam	Size	The number of array elements per node.
*
* \param todelete The node to be removed from the list.
*/
/*****************************************************************************/

template <typename T, int Size>
void BList<T, Size>::remove_node(BNode* todelete){
  // make copies of the node before
  BNode* todeleteprev = todelete->prev;
  // and the node after the node to be deleted
  BNode* nextnode = todelete->next;
  
  // then unlink the node, check if there is a node before it
  if (todeleteprev)
    // then the node before it now points to the node after it
    todeleteprev->next = nextnode;
  // if there was a node after it
  if (nextnode)
    // then the node after it now points to the node before it
    nextnode->prev = todeleteprev;

  // decrement number of nodes in the list
  stats.NodeCount--;
  // and number of items in the list, by subtracting number of items in the node
  stats.ItemCount -= todelete->count;
  // then delete the node
  delete todelete;
}

/*****************************************************************************/
/*!
* Checks if the node's array is full.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter, data stored in node.
* \tparam	Size	The number of array elements per node.
*
* \param isfull The node to check fullness of.
*
* \return bool  Whether or not the node is full.
*/
/*****************************************************************************/

template <typename T, int Size>
bool BList<T, Size>::full(BNode* isfull){
  if (isfull->count == stats.ArraySize)
    return true;
  else
    return false;
}

/*****************************************************************************/
/*!
* Inserts a value after insertafter.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter, data stored in node.
* \tparam	Size	The number of array elements per node.
*
* \param insertafter  The node to insert a value after.
* \param value  The value to be inserted.
*/
/*****************************************************************************/

template <typename T, int Size>
void BList<T, Size>::insert_after(BNode* insertafter, const T& value){
  // if the node to insert in is full
  if (full(insertafter))
  {
    // then make a copy of the next node
    BNode* nextnode = insertafter->next;
    // make a new node with the provided value
    BNode* toinsert = new_node(value);
    // and link the new node with the node that we tried to insert into
    insertafter->next = toinsert;
    toinsert->prev = insertafter;
    // if there is a next node
    if (nextnode)
    {
      // then link the new node with this one as well
      toinsert->next = nextnode;
      nextnode->prev = toinsert;
    }
    // if the node we tried to insert into was the tail
    if (insertafter == tail_)
      // then the node we created is the new tail
      tail_ = toinsert;
  }
  // if the node to insert in is not full
  else
  {
    // then insert the value at the unused element in the node
    insertafter->values[insertafter->count] = value;
    // increment the item count for the list
    stats.ItemCount++;
    // and for the node
    insertafter->count++;
  }
}


/*****************************************************************************/
/*!
* Splits a node, placing half of the elements into each of the new nodes.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter, data stored in node.
* \tparam	Size	The number of array elements per node.
*
* \param tosplit  The node to split.
* \param value  The value to add to one of the new nodes.
* 
* \return BNode*  Pointer to the first of the two new nodes.
*/
/*****************************************************************************/

template <typename T, int Size>
void BList<T, Size>::split_node(BNode* tosplit, const T& value){
  // create a new node for the first part of the split, with the first value
  // from the node to be split
  BNode* firstnew = new_node(tosplit->values[0]);
  // and another new node with the last value from the node to be split
  BNode* secondnew = new_node(tosplit->values[(stats.ArraySize/2)]);

  // update the new nodes with half of the split node's values each
  for (int i = 1; i < stats.ArraySize / 2; ++i)
  {
    firstnew->values[i] = tosplit->values[i];
    stats.ItemCount++;
    firstnew->count++;
  }
  for (int i = 1; i < (stats.ArraySize / 2); ++i)
  {
    secondnew->values[i] = tosplit->values[i + (stats.ArraySize / 2)];
    stats.ItemCount++;
    secondnew->count++;
  }

  // after the nodes have been updated with half of the values each,
  // determine where to put the provided value

  //if the value is less than the first element of the second half
  if (value < secondnew->values[0])
    // then put the value in the first half
    insert_into(firstnew, value);
  else
    // otherwise, put it in the second half
    insert_into(secondnew, value);

  // link the two nodes together
  firstnew->next = secondnew;
  secondnew->prev = firstnew;

  // save the nodes before and after the split node, for linking
  BNode* tosplitprev = tosplit->prev;
  BNode* tosplitnext = tosplit->next;

  // link the new nodes into the list
  if (tosplitprev)
    tosplitprev->next = firstnew;
  firstnew->prev = tosplitprev;
  secondnew->next = tosplitnext;
  if (tosplitnext)
    tosplitnext->prev = secondnew;

  // if the node to be split was the head
  if (tosplit == head_)
    // then the first half is the new head
    head_ = firstnew;

  // if the node to be split was the tail
  if (tosplit == tail_)
    // then the second half is the new tail
    tail_ = secondnew;

  // decrment the node count for the list
  stats.NodeCount--;
  // and subtract the item count of the node split node from the item count for the list
  stats.ItemCount -= tosplit->count;
  // then delete the node
  delete tosplit;
}

/*****************************************************************************/
/*!
* Inserts a value before insertbefore.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter, data stored in node.
* \tparam	Size	The number of array elements per node.
*
* \param insertbefore  The node to insert a value before.
* \param value  The value to be inserted.
*/
/*****************************************************************************/

template <typename T, int Size>
void BList<T, Size>::insert_before(BNode* insertbefore, const T& value){
  // if the node to insert a value into is full
  if (full(insertbefore))
  {
    // make a copy of the node before the node to insert into
    BNode* prevnode = insertbefore->prev;
    // make a new node with value to insert into the list
    BNode* toinsert = new_node(value);  
    // link the new node to the node we tried to insert into
    toinsert->next = insertbefore;
    insertbefore->prev = toinsert;
    // if there is a node before the to insert into
    if (prevnode)
    { 
      // then link the new node to the prevnode
      toinsert->prev = prevnode;
      prevnode->next = toinsert;
    }
    // if the node we tried to insert into was the head
    if (insertbefore == head_)
      // then the new node is now the head
      head_ = toinsert;
  }
  // otherwise, the node to insert into is not full
  else
  {
    // shift values over to make room for new value at front
    for (int i = stats.ArraySize - 1; i > 0; --i)
    {
      insertbefore->values[i] = insertbefore->values[i - 1];
    }
    // then insert the value at the front
    insertbefore->values[0] = value;
    // increment the number of items in the node
    insertbefore->count++;
    // and number of items in the list
    stats.ItemCount++;
  }
}

/*****************************************************************************/
/*!
* Creates a copy of tocopy.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter, data stored in node.
* \tparam	Size	The number of array elements per node.
*
* \param tocopy The node to be copied.
*
* \return BNode*  The copied node.
*/
/*****************************************************************************/

template <typename T, int Size>
typename BList<T, Size>::BNode* BList<T, Size>::copy_node(BNode* tocopy){
  // create a new node with value of the first element of the node to copy
  BNode* copy = new_node(tocopy->values[0]);

  // copy over all values from the node to copy, and increment counts
  for (int i = 1; i < tocopy->count; ++i)
  {
    copy->values[i] = tocopy->values[i];
    copy->count++;
    stats.ItemCount++;
  }

  return copy;
}

/*****************************************************************************/
/*!
* Inserts a value into insertinto.
*
* \author	Louis.coyleii
* \date 09/20/14
*
* \tparam	T   	Generic type parameter, data stored in node.
* \tparam	Size	The number of array elements per node.
*
* \param insertinto  The node to insert a value into.
* \param value  The value to be inserted.
*/
/*****************************************************************************/

template <typename T, int Size>
void BList<T, Size>::insert_into(BNode* insertinto, const T& value){
  // if the value is greater than the last element in the node to insert into
  if (insertinto->values[insertinto->count - 1] < value)
  {
    // then insert the value after the elements of the node
    insert_after(insertinto, value);
    // and end function
    return;
  }
  // if the value is less than the first element in the node to insert into
  if (value < insertinto->values[0])
  {
    // then insert the value before the elements of the node
    insert_before(insertinto, value);
    // and end function
    return;
  }
  // otherwise, the value should fit somewhere inside the node
  // so iterate over the elements in the node
  for (int i = 0; i < insertinto->count - 1; ++i)
  {
    // if the node fits in between two elements in the node
    if (insertinto->values[i] < value && value < insertinto->values[i+1])
    {
      // then save the position to insert the value into
      int pos = i + 1;
      // and shift over all the elements after this position
      for (int j = stats.ArraySize - 1; j > i; --j)
      {
        insertinto->values[j] = insertinto->values[j - 1];
      }
      // then insert the value into this element
      insertinto->values[pos] = value;
      // and increment the item counts for the list
      stats.ItemCount++;
      // and the node
      insertinto->count++;
      return;
    }
  }
}
