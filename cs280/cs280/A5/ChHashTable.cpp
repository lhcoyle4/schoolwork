/*****************************************************************************/
/*!
* \file   ChHashTable.cpp
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: CS280
* \par    Assignment #5
* \date   11/12/14
* 
* \brief
* This file contains the implementation of the following functions for the
* ChHashTable C++ assignment.
* 
* Hours spent on this assignment: 3
* 
* Specific portions that gave you the most trouble: 
*/
/*****************************************************************************/

/*****************************************************************************/
/*!
* Returns true if efficiency implemented.
*
* \author	louis.coyleii
* \date	3/11/2014
*
* \param Config
* \param allocator Allocator to use for the 
*
* \return bool Whether or not efficiency was implemented.
*
*/
/*****************************************************************************/
template <typename T>
ChHashTable<T>::ChHashTable(const HTConfig& Config, ObjectAllocator* allocator) : config_(Config), oa_(allocator){
  head_ = new ChHTHeadNode[Config.InitialTableSize_];
  stats_.HashFunc_ = Config.HashFunc_;
  stats_.TableSize_ = Config.InitialTableSize_;
}

/*****************************************************************************/
/*!
* Destructor for a ChHashTable.
*
* \author	louis.coyleii
* \date	11/12/14
*
*/
/*****************************************************************************/
template <typename T>
ChHashTable<T>::~ChHashTable(){
  clear();
  delete [] head_;
}

/*****************************************************************************/
/*!
* Inserts a key/data pair into table. Throws an exception if unsuccessful.
*
* \author	louis.coyleii
* \date	11/12/14
*
* \param Key The key part of the pair to be inserted into table.
* \param Data The data part of the pair to be inserted into table.
*
*/
/*****************************************************************************/
template <typename T>
void ChHashTable<T>::insert(const char *Key, const T& Data){
  stats_.Probes_++;
  // this calculation of loadfactor was provided by Benjamin Henning,
  // and was posted on the CS280 forum in Spring 2014
  double loadFactor = static_cast<double>(stats_.Count_ + 1)
                    / static_cast<double>(stats_.TableSize_);

  // before inserting, check whether we need to expand the table
  if (loadFactor > config_.MaxLoadFactor_)
  {
    grow();
  }

  // insert, now that there is space for the new item
  push_front(Data, Key, head_[config_.HashFunc_(Key, stats_.TableSize_)]);
}

/*****************************************************************************/
/*!
* Delete an item by key. Throws an exception if the key doesn't exist.
* Compacts the table by moving key/data pairs, if necessary
*
* \author	louis.coyleii
* \date	11/12/14
*
* \param Key The key of the item to remove.
*
*/
/*****************************************************************************/
template <typename T>
void ChHashTable<T>::remove(const char *Key){
  ChHTHeadNode & slot = head_[config_.HashFunc_(Key, stats_.TableSize_)];
  ChHTNode * tosearch = slot.Nodes;
  ChHTNode * prev = 0;

  while (tosearch)
  {
    stats_.Probes_++;
    if (!strcmp(Key, tosearch->Key))
    {
      if (config_.FreeProc_)
        config_.FreeProc_(tosearch->Data);
      if (!prev)
        pop_front(slot);
      else
        remove_node(prev);
      return;
    }
    prev = tosearch;
    tosearch = tosearch->Next;
  }

  throw(HashTableException(HashTableException::E_ITEM_NOT_FOUND, "remove: the item was not found."));
}

/*****************************************************************************/
/*!
* Find and return data by key (returns 0 if not found).
*
* \author	louis.coyleii
* \date	11/12/14
*
* \param Key The key to find an item for.
*
* \return T& The item that was found by key.
*
*/
/*****************************************************************************/
template <typename T>
const T& ChHashTable<T>::find(const char *Key) const{
  ChHTNode * tosearch = head_[config_.HashFunc_(Key, stats_.TableSize_)].Nodes;
  while (tosearch)
  {
    stats_.Probes_++;
    if (!strcmp(tosearch->Key, Key))
      return tosearch->Data;

    tosearch = tosearch->Next;
  }

  throw(HashTableException(HashTableException::E_ITEM_NOT_FOUND, "find: the item was not found."));
}

/*****************************************************************************/
/*!
* Removes all items from the table (Doesn't deallocate table).
*
* \author	louis.coyleii
* \date	11/12/14
*
*/
/*****************************************************************************/
  // 
template <typename T>
void ChHashTable<T>::clear(void){
  for (unsigned int i = 0; i < stats_.TableSize_; ++i)
  {
    while (head_[i].Nodes)
    {
      if (config_.FreeProc_)
        config_.FreeProc_(head_[i].Nodes->Data);
      pop_front(head_[i]);
    }
  }
}

/*****************************************************************************/
/*!
* Allow the client to peer into the data.
*
* \author	louis.coyleii
* \date	11/12/14
*
* \return HTStats The stats for the table.
*
*/
/*****************************************************************************/
template <typename T>
HTStats ChHashTable<T>::GetStats(void) const{
  return stats_;
}

/*****************************************************************************/
/*!
* Returns the head of the table.
*
* \author	louis.coyleii
* \date	11/12/14
*
* \return ChHTHeadNode* The head of the table.
*
*/
/*****************************************************************************/
template <typename T>
const typename ChHashTable<T>::ChHTHeadNode * ChHashTable<T>::GetTable(void) const{
  return head_;
}

 // Private fields and methods...

/*****************************************************************************/
/*!
* Grows the table.
*
* \author	louis.coyleii
* \date	11/12/14
*
*/
/*****************************************************************************/
template <typename T>
void ChHashTable<T>::grow(void){
  stats_.Expansions_++;
  double factor = std::ceil(stats_.TableSize_ * config_.GrowthFactor_);
  unsigned growntablesize = GetClosestPrime(static_cast<unsigned>(factor));
  unsigned oldtablesize = stats_.TableSize_;
  ChHTHeadNode * grown = new ChHTHeadNode[growntablesize];
  stats_.TableSize_ = growntablesize;
  for (unsigned i = 0; i < oldtablesize; ++i)
  {

    while(head_[i].Nodes)
    {
      stats_.Probes_++;
      //grown->insert(head_[i].Nodes->Key, head_[i].Nodes->Data);
       push_front(head_[i].Nodes->Data, head_[i].Nodes->Key, 
         grown[config_.HashFunc_(head_[i].Nodes->Key, stats_.TableSize_)]);
       pop_front(head_[i]);

    }
  }

  stats_.TableSize_ = growntablesize;
  delete [] head_;

  head_ = grown;
}

/*****************************************************************************/
/*!
* Pushes a node with Data to the front of the list.
*
* \author	louis.coyleii
* \date	11/12/14
*
* \param Data The data to be pushed to the front.
* \param Key The key to be pushed to the front.
* \param list The head of the list to add to.
*
*/
/*****************************************************************************/
template <typename T>
void ChHashTable<T>::push_front(const T& Data, const char * Key, ChHTHeadNode &list){
  ChHTNode * topush;
  ChHTNode * trav = list.Nodes;

  while(trav)
  {
    stats_.Probes_++;
    if (!strcmp(trav->Key, Key))
    {
      throw(HashTableException(HashTableException::E_DUPLICATE, "push_front: the item to insert was a duplicate."));
    }
    trav = trav->Next;
  }
  try
  {
    if (oa_)
      topush = new (oa_->Allocate()) ChHTNode(Data);
    else
      topush = new ChHTNode(Data);
  }
  catch (const std::exception)
  {
    throw(HashTableException(HashTableException::E_NO_MEMORY, "push_front: out of memory"));
  }

  strcpy(topush->Key, Key);

  topush->Next = list.Nodes;
  list.Nodes = topush;
  stats_.Count_++;
}

/*****************************************************************************/
/*!
* Pops the front of the list.
*
* \author	louis.coyleii
* \date	11/12/14
*
* \param list The head of the list pop.
*
*/
/*****************************************************************************/
template <typename T>
void ChHashTable<T>::pop_front(ChHTHeadNode &list){
  ChHTNode * temp = list.Nodes;

  list.Nodes = list.Nodes->Next;

  if (oa_)
    oa_->Free(temp);
  else
    delete temp;

  stats_.Count_--;
}

/*****************************************************************************/
/*!
* Removes a node from the list.
*
* \author	louis.coyleii
* \date	11/12/14
*
* \param prev The node before the node to remove.
*
*/
/*****************************************************************************/
template <typename T>
void ChHashTable<T>::remove_node(ChHTNode * &prev){
  ChHTNode * toremove = prev->Next;

  // unlink the node to remove
  prev->Next = prev->Next->Next;
  // delete the node to remove
  if (oa_)
    oa_->Free(toremove);
  else
    delete toremove;

  // decrement node count
  stats_.Count_--;
}