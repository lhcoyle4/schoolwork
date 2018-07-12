#include "ObjectAllocator.h"
#include <cstring> /* memset, strlen, memcpy */
/******************************************************************************/
/*!
\file   ObjectAllocator.cpp
\author Louis Coyle II
\par    email: louis.coyleii\@digipen.edu
\par    DigiPen login: louis.coyleii
\par    Course: CS280
\par    Assignment #1
\date   09/07/14

\brief
This file contains the implementation of the following functions for the
Memory Manager C++ assignment.

Hours spent on this assignment: 10

Specific portions that gave you the most trouble: Pointer arithmetic, casting,
edge cases.
*/
/******************************************************************************/


/******************************************************************************/
/*!
\fn ObjectAllocator::ObjectAllocator(size_t ObjectSize, const OAConfig& config)

\brief
Creates the ObjectManager per the specified values.
Throws an exception if the construction fails. (Memory allocation problem)

\param ObjectSize
The size of the objects to be managed.

\param config
The configuration paramaters for the manager to be constructed.

*/
/******************************************************************************/

ObjectAllocator::ObjectAllocator(size_t ObjectSize, const OAConfig& config) 
  NOEXCEPT(false) : oaconfig(config), oastats(){

  // set up stats struct for the manager
  oastats.ObjectSize_ = ObjectSize;

  // set the size of node based on provided configs
  node_size = static_cast<unsigned>(oastats.ObjectSize_) 
              + (oaconfig.PadBytes_ << 1) 
              + static_cast<unsigned>(oaconfig.HBlockInfo_.size_);

  // set the size of a page based on provided configs
  oastats.PageSize_ = node_size * config.ObjectsPerPage_ + sizeof(void*);

  // set the size of offset ""
  offset = oaconfig.PadBytes_ + 
    static_cast<unsigned>(oaconfig.HBlockInfo_.size_);

  // init the pagelist and freelist to point at null
  PageList = 0;
  FreeList = 0;
 
  // setup the first page and header
  ExpandPages();
  setup_header();
}

/******************************************************************************/
/*!
\fn ObjectAllocator::~ObjectAllocator()

\brief
Destroys the ObjectManager. (never throws)

*/
/******************************************************************************/
ObjectAllocator::~ObjectAllocator() NOEXCEPT(true){
  if (oaconfig.HBlockInfo_.type_ == OAConfig::hbExternal)
  {
    // need to iterate over every block, not just freelist
    byte_t* page_it = PageList;

    while(page_it)
    {
      byte_t* block_it = page_it + sizeof(void*);
      // now we're pointing at start of first block
      // (before the header and padbytes)
      // and can iterate over each block, deleting their label string and them
      while(block_it < page_it + oastats.PageSize_)
      {
        // delete each memblock, including header string
        delete_memblock(block_it + offset);

        block_it += node_size;
      }
      // continue iterating over each page, to access blocks inside
      page_it = increment_head(page_it);
    }
  }

  // iterate over and delete each page
	while(PageList)
	{
    byte_t *todelete = PageList;
		PageList = increment_head(PageList);
		delete [] todelete;
	}
}

/******************************************************************************/
/*!
\fn void* ObjectAllocator::Allocate(const char *label = 0)

\brief
Take an object from the free list and give it to the client. (simulates new)
Throws an exception if the object can't be allocated. (Memory allocation 
problem)

\param label
The name of the block of memory to be allocated.

\return void*
The allocated block of memory.

*/
/******************************************************************************/
void* ObjectAllocator::Allocate(const char *label) NOEXCEPT(false){
  // just use new to allocate if configured to do so
  if(oaconfig.UseCPPMemManager_)
  {
    byte_t* newobj;
    try
    {
      newobj = new byte_t[oastats.ObjectSize_];
    }
    catch (std::bad_alloc &)
    {
      throw OAException(OAException::E_NO_MEMORY, 
        "ExpandPages: No system memory available.");
    }

    // update the stats
    oastats.Allocations_++;
    oastats.ObjectsInUse_++;
    oastats.FreeObjects_--;
    if (oastats.ObjectsInUse_ > oastats.MostObjects_)
      oastats.MostObjects_ = oastats.ObjectsInUse_;

    return newobj;
  }
  // otherwise, uses the custom ObjectAllocator

  // first checking to see if there is free space in the current pages
  if (FreeList == 0)
  {
    // creates a new page (checking if > maxpages done in ExpandPages())
    ExpandPages();
    // and sets up the correct type of header
    setup_header();
  }

  // update the stats
  oastats.ObjectsInUse_++;
  oastats.Allocations_++;
  oastats.FreeObjects_--;
  if (oastats.ObjectsInUse_ > oastats.MostObjects_)
    oastats.MostObjects_ = oastats.ObjectsInUse_;

  // grab the first unallocated block from the free list
  byte_t* ret = FreeList;
  // and increment the free list to point at the next available block (or null)
  FreeList = increment_head(FreeList);
  // if debug is on, set the block to allocated pattern
  if(oaconfig.DebugOn_) 
    std::memset(ret, ALLOCATED_PATTERN, oastats.ObjectSize_);
  //set inuse flag in the header, as necessary for the header type
  update_header(true, ret, label);
  // give the block to the user
  return ret;
}

/******************************************************************************/
/*!
\fn void ObjectAllocator::Free(void *Object)

\brief
Returns an object to the free list for the client. (simulates delete)
Throws an exception if the the object can't be freed. (Invalid object)

\param Object
The object to be freed.

*/
/******************************************************************************/

void ObjectAllocator::Free(void *Object) NOEXCEPT(false){
  // just use delete if bypassing the custom manager
  if (oaconfig.UseCPPMemManager_)
  {
    delete [] reinterpret_cast<byte_t*>(Object);
    // still, update the stats
    oastats.ObjectsInUse_--;
    oastats.Deallocations_++;
    oastats.FreeObjects_++;
    return;
  }
  // if debug is on, perform checks against user error
  if(oaconfig.DebugOn_)
  {
    // check bad boundary
    byte_t* findpage = PageList;
    while (findpage)
    {
      // first the object must be found, by comparing addresses
      if (reinterpret_cast<byte_t*>(Object) >= findpage &&
          reinterpret_cast<byte_t*>(Object) < findpage + oastats.PageSize_)
      {
        // if the address given to be freed from the client is not what was
        // given to them, throw out of boundary error
        if (((reinterpret_cast<std::size_t>(Object) - offset - 
              reinterpret_cast<std::size_t>(findpage) - 
              sizeof(void*)) % node_size) != 0)
          throw OAException(OAException::E_BAD_BOUNDARY, 
            "Free: Object out of boundary.");
      }
      // keep looking through all the pages until the object is found
      findpage = increment_head(findpage);
    }
    // check double free
    if (CheckIfFree(Object))
      throw OAException(OAException::E_MULTIPLE_FREE, 
        "Free: Object already freed.");
    // check corrupted block
    if (!validate_object(reinterpret_cast<byte_t const*>(Object)))
      throw OAException(OAException::E_CORRUPTED_BLOCK, 
        "Free: Block is corrupted.");
  }
  // update the stats to reflect the newly freed block
  oastats.ObjectsInUse_--;
  oastats.Deallocations_++;
  oastats.FreeObjects_++;
  // casting the object for use in helper functions
  byte_t* freed = reinterpret_cast<byte_t*>(Object);
  // if debug is on, then set the entire block to the freed pattern
  if(oaconfig.DebugOn_) 
    std::memset(Object, FREED_PATTERN, oastats.ObjectSize_);
  //clear in use flag
  update_header(false, freed);
  // push the freed block onto front of the freelist
  push_front(FreeList, freed);
}

/******************************************************************************/
/*!
\fn unsigned ObjectAllocator::DumpMemoryInUse(DUMPCALLBACK fn) const

\brief
Calls the callback fn for each block still in use.

\param fn
A pointer to the callback fn for the block still in use.

\return unsigned
The number of blocks that are in use by the client.

*/
/******************************************************************************/
unsigned ObjectAllocator::DumpMemoryInUse(DUMPCALLBACK fn) const {
  //if the block is in use, callback fn on that block
  //give the callback the object itself that's in use and it's size
  byte_t* page_it = PageList;
  unsigned count = 0;

  while(page_it)
  {
    byte_t* block_it = page_it + sizeof(void*);
    //now we're pointing at first block
    while(block_it < page_it + oastats.PageSize_)
    {
      // if the block is in use
      if(!CheckIfFree(block_it + offset))
      {
        // then supply its information to callback
        fn(block_it + offset, oastats.ObjectSize_);
        // and increment the count of in use blocks
        ++count;
      }
      // continue iterating over each block in the page
      block_it += node_size;
    }
    // continue iterating over each page in the pagelist
    page_it = increment_head(page_it);
  }
  // supply the number of in use blocks
  return count;
}

/******************************************************************************/
/*!
\fn unsigned ObjectAllocator::ValidatePages(VALIDATECALLBACK fn) const

\brief
Calls the callback fn for each block that is potentially corrupted.

\param fn
A pointer to the callback fn for the block that is potentially corrupted.

\return unsigned
The number of blocks that are corrupted.

*/
/******************************************************************************/

unsigned ObjectAllocator::ValidatePages(VALIDATECALLBACK fn) const {
  //if the block is corrupted callback fn on that block
  //exactly the same as dumpmemory except calls validateobject instead of 
  //checkiffree
  byte_t* page_it = PageList;
  unsigned count = 0;

  while(page_it)
  {
    byte_t* block_it = page_it + sizeof(void*);
    //now we're pointing at first block
    while(block_it < page_it + oastats.PageSize_)
    {
      // if the block is corrupted
      if(!validate_object(block_it + offset))
      {
        // then supply its information to the callback
        fn(block_it + offset, oastats.ObjectSize_);
        // and increment count of corrupted blocks
        ++count;
      }
      // continue iterating over all blocks in the page
      block_it += node_size;
    }
    // continue iterating over all pages in the pagelist
    page_it = increment_head(page_it);
  }
  // supply the number of corrupted blocks
  return count;
}

/******************************************************************************/
/*!
\fn unsigned ObjectAllocator::FreeEmptyPages(void)

\brief
Frees all empty pages. (extra credit)

\return unsigned
The number of pages that were freed.

*/
/******************************************************************************/
unsigned ObjectAllocator::FreeEmptyPages(void){
  return 0;
}

/******************************************************************************/
/*!
\fn static bool ObjectAllocator::ImplementedExtraCredit(void)

\brief
Returns true if FreeEmptyPages and alignments are implemented.

\return static bool
A boolean, indicating whether or not the extra credit has been implemented.

*/
/******************************************************************************/
bool ObjectAllocator::ImplementedExtraCredit(void){
  return false;
}

  // Testing/Debugging/Statistic methods

/******************************************************************************/
/*!
\fn void ObjectAllocator::SetDebugState(bool State)

\brief
Sets the debug state, true=enable, false=disable.

\param State
A boolean, indicating whether or not to set debug state on.

*/
/******************************************************************************/

void ObjectAllocator::SetDebugState(bool State){
  oaconfig.DebugOn_ = State;
}

/******************************************************************************/
/*!
\fn const void * ObjectAllocator::GetFreeList(void) const

\brief
Returns a pointer to the internal free list.

\return const void *
A pointer to the internal free list.

*/
/******************************************************************************/
const void * ObjectAllocator::GetFreeList(void) const {
  return FreeList;
}

/******************************************************************************/
/*!
\fn const void * ObjectAllocator::GetPageList(void) const

\brief
Returns a pointer to the internal page list.

\return const void *
A pointer to the internal page list.

*/
/******************************************************************************/
const void * ObjectAllocator::GetPageList(void) const {
  return PageList;
}

/******************************************************************************/
/*!
\fn OAConfig ObjectAllocator::GetConfig(void) const

\brief
Returns the configuration parameters.

\return OAConfig
The configuration paramaters struct.

*/
/******************************************************************************/
OAConfig ObjectAllocator::GetConfig(void) const {
  return oaconfig;
}

/******************************************************************************/
/*!
\fn OAStats ObjectAllocator::GetStats(void) const

\brief
Returns the statistics for the allocator.

\return OAStats
The statistics for the allocator.

*/
/******************************************************************************/
OAStats ObjectAllocator::GetStats(void) const {
  return oastats;
}

/******************************************************************************/
/*!
\fn void ObjectAllocator::ExpandPages(void)

\brief
Helper function to create a new page when freelist is empty.

*/
/******************************************************************************/
void ObjectAllocator::ExpandPages(void) NOEXCEPT(false){
  if (oastats.PagesInUse_ >= oaconfig.MaxPages_)
  {
    throw OAException(OAException::E_NO_PAGES, 
      "ExpandPages: Max pages has been reached.");
  }
  oastats.PagesInUse_++;
  //must allocate a block of memory to fit number of objects in the page with 
  //room for a pagelist pointer
  byte_t* newpage;
  try
  {
    // this is done by using the given pagesize
    newpage = new byte_t[oastats.PageSize_];
  }
  catch (std::bad_alloc &)
  {
    throw OAException(OAException::E_NO_MEMORY, 
      "ExpandPages: No system memory available.");
  }

  if(oaconfig.DebugOn_) 
    std::memset(newpage, UNALLOCATED_PATTERN, oastats.PageSize_);
  //must cast the page of memory as a generic object in order to add it to 
  //the pagelist, this is done in push_front
  push_front(PageList, newpage);
  // increment the number of freeobjects to reflect the new page being added
  oastats.FreeObjects_ += oaconfig.ObjectsPerPage_;


  // loop to create linked list to keep track of free memory objects
  for (size_t i = sizeof(void*); i < oastats.PageSize_; i += node_size){
    // sets the pad bytes in front of the block to the padpattern
    std::memset(newpage + i + oaconfig.HBlockInfo_.size_, PAD_PATTERN, oaconfig.PadBytes_);
    // sets the pad bytes in back of the block to the padpattern
    std::memset(newpage + i + offset + oastats.ObjectSize_, PAD_PATTERN, oaconfig.PadBytes_);
    // adds each block to the freelist
    push_front(FreeList, newpage + i + offset);
  }
}

/******************************************************************************/
/*!
\fn void ObjectAllocator::CheckIfFree(void* Object) const

\brief
Helper function to check for free blocks.

\param Object
The object to check if free.

\return bool
Whether or not the supplied block was on freelist.

*/
/******************************************************************************/
bool ObjectAllocator::CheckIfFree(void* Object) const{
  switch (oaconfig.HBlockInfo_.type_) {
    // hbNone
    case OAConfig::hbNone:
    {   
      // gets head of the freelist
      byte_t* current = FreeList;
      // iterates through the freelist
      while(current)
      {
        // and directly compares addresses
        if(current == reinterpret_cast<byte_t*>(Object))
          // returning true if the address was found on freelist
          return true;
        // otherwise, continues looking through freelist
        current = increment_head(current);
      }
      break;
    }    
    // hbExtended - same check as hbBasic, so it falls through
    case OAConfig::hbExtended:
    // hbBasic
    case OAConfig::hbBasic:
    {
      byte_t* current = reinterpret_cast<byte_t*>(Object);
      // just looks at the free bit of the block
      if(!*(current -1 - oaconfig.PadBytes_))
        // returning true if free bit was 0
        return true;
      break;
    }
    // hbExternal
    case OAConfig::hbExternal:
    { 
      byte_t* current = reinterpret_cast<byte_t*>(Object);
      // looks at the external header for the block
      MemBlockInfo** extheader = 
        reinterpret_cast<MemBlockInfo**>(current - offset);
      // and checks the in_use parameter
      if(!((*extheader)->in_use))
        // returning true if in_use was 0
        return true;
      break;
    }
  }
  // if the block wasn't found to be free in above switch stament, it isn't
  // so return that it is in use
  return false;
}

/******************************************************************************/
/*!
\fn void ObjectAllocator::increment_head(byte_t* head) const

\brief
Increments a linked list.

\param head
The head of the list to increment.

\return ObjectAllocator::byte_t*
The next node in the list.

*/
/******************************************************************************/
ObjectAllocator::byte_t* ObjectAllocator::increment_head(byte_t* head) const{
  // increments the provided node and returns the next node
	GenericObject* list = reinterpret_cast<GenericObject*>(head);
	list = list->Next;
	return reinterpret_cast<byte_t*>(list);
}

/******************************************************************************/
/*!
\fn void ObjectAllocator::push_front(byte_t* &head, byte_t* newhead)

\brief
Pushes a node to the front of the linked list.

\param head
The head of the list to push onto.

\param newhead
The new head to push onto the list.

*/
/******************************************************************************/
void ObjectAllocator::push_front(byte_t* &head, byte_t* newhead){
  // just pushes the provided node to the front of the provided list
	GenericObject* oldhead = reinterpret_cast<GenericObject*>(head);
	GenericObject* newlist = reinterpret_cast<GenericObject*>(newhead);
	newlist->Next = oldhead;
	head = newhead;
}

/******************************************************************************/
/*!
\fn void ObjectAllocator::setup_header(void)

\brief
Initializes the headers appropriately based on their type.

*/
/******************************************************************************/
void ObjectAllocator::setup_header(void){
  /* note that the cases for the basic, extended and external header blocks 
  all just increment through each block in the freelist, initializing the 
  memory for the header blocks. this doesn't overwrite any current header block
  data because setup_header is only called when a new page is created, so the
  only blocks on the freelist are those in the new page. */

  switch (oaconfig.HBlockInfo_.type_)
  {
    // hbNone - no header block so do nothing
    case OAConfig::hbNone:
    {
      break;
    }
    // hbExtended - same implementation as hbBasic, so falls through
    case OAConfig::hbExtended:
    // hbBasic - sets up the headerblock by setting its memory to 0
    case OAConfig::hbBasic:
    {
      // handles an edge case i was having where the first block's
      // header wasn't initialized to 0
      byte_t* edgecase = PageList + sizeof(void*);
      std::memset(edgecase, 0x00, oaconfig.HBlockInfo_.size_);

      byte_t* current = FreeList;
      while(current)
      {
        // sets the current block's header to 0
        std::memset(current - offset, 0x00, oaconfig.HBlockInfo_.size_);
        // continues iterating over the freelist
        current = increment_head(current);
      }
      break;
    }
    case OAConfig::hbExternal:
    {
      byte_t* current = FreeList;
      while (current)
      {
        // prepare the pointer to the external header block
        MemBlockInfo** extheader = 
          reinterpret_cast<MemBlockInfo**>(current - offset);
        // create memory for the external header block
        *extheader = new MemBlockInfo;
        // and initialize its parameters
        (*extheader)->label = 0;
        (*extheader)->in_use = false;
        (*extheader)->alloc_num = 0;
        // continue iterating over the freelist
        current = increment_head(current);
      }
      break;
    }
  }
}

/******************************************************************************/
/*!
\fn void ObjectAllocator::update_header(bool inuse, byte_t* Object, 
    const char* label)

\brief
Updates the header based on the header type.

\param inuse
Whether or not the object is in use

\param Object
The object to update header for.

\param label
Label for the object, for use in external header blocks.

*/
/******************************************************************************/
void ObjectAllocator::update_header(bool inuse, byte_t* Object, 
  const char* label){

  switch (oaconfig.HBlockInfo_.type_)
  {
    case OAConfig::hbNone:
    {
      break;
    }
    case OAConfig::hbExtended:
    {
     // accesses and updates the inuse bit in the header block
     *(Object -1 - oaconfig.PadBytes_) = inuse;
     // if the block is in use
     if (inuse)
     {
       // access the alloc_num parameter in the header block 
       // and update it with the number of allocations that have occurred
       *(Object - offset + 3) = static_cast<byte_t>(oastats.Allocations_);
       // also update the number of times this block has been used
       (*(Object - offset + 1))++;
     }
     else
       // otherwise the block is freed, so clear the alloc_num parameter
       *(Object - offset + 3) = 0;
     break;
    }
    case OAConfig::hbBasic:
    {
      // clear the whole header block, because we are updating it anyway
      std::memset(Object - offset, 0x00, oaconfig.HBlockInfo_.size_);
      // if the block is in use
      if (inuse)
        // then update its alloc_num parametr with number of allocs
        *(Object - offset) = static_cast<byte_t>(oastats.Allocations_);
        // and update the inuse bit with the given information
        *(Object -1 - oaconfig.PadBytes_) = inuse;
        break;
    }
    case OAConfig::hbExternal:
    {
      // set up the pointer to the external header
      MemBlockInfo** extheader = 
        reinterpret_cast<MemBlockInfo**>(Object - offset);
      // udpate the inuse parameter of the external header
      (*extheader)->in_use = inuse;
      // if the block is now in use
      if (inuse)
      {
        // then update its alloc_num with the number of allocations
        // that have occurred so far
        (*extheader)->alloc_num = oastats.Allocations_;
        // if a label was supplied
        if(label)
        {
          // get the length of the supplied label
          unsigned len = static_cast<unsigned>(std::strlen(label) + 1);
          try
          {
            // and try to allocate memory for the string
            (*extheader)->label = new char [len];
          }
          catch (std::bad_alloc &)
          {
            throw OAException(OAException::E_NO_MEMORY, 
              "update_header: No system memory available.");
          }
          // copy the label into the new character array
          std::memcpy((*extheader)->label, label, len*sizeof(char));
        }
      }
      // otherwise the block has been freed
      else
      {
        // so delete the character array
        delete [] (*extheader)->label;
        // and clear the other parameters
        (*extheader)->label = 0;
        (*extheader)->alloc_num = 0;
      }
      break;
    }
  }
}

/******************************************************************************/
/*!
\fn bool ObjectAllocator::validate_object(byte_t const* Object) const

\brief
Validates that the page is not corrupted.

\param Object
The object to validate.

\return bool
Returns false if object was corrupted.

*/
/******************************************************************************/
bool ObjectAllocator::validate_object(byte_t const* Object) const{
  /* this validates by looking at the pad bytes to make sure that they still 
     match the padpattern and haven't been scribbled into so if there is no 
     padding, then the object is valid as far as this function is concerned */
  if (oaconfig.PadBytes_ == 0) 
    return true;

  unsigned i = 0;
  /* starts two pointers, one at the end of the padding on the left and the 
     other at the beginning of the padding on the right. decrements the
     pad_left address and increments the pad_right address until all of the
     padbytes have been looked at */
  for (byte_t const *pad_left = Object - 1, 
       *pad_right = Object + oastats.ObjectSize_;
       i < oaconfig.PadBytes_;
       ++i, --pad_left, ++pad_right) 
  {
    // if the padbytes have been scribbled into, return false
    if (*pad_left != PAD_PATTERN || *pad_right != PAD_PATTERN) 
      return false;
  }
  // if padbytes weren't scribbled into, the object is valid
  return true;
}

/******************************************************************************/
/*!
\fn void ObjectAllocator::delete_memblock(void* Object)

\brief
Deletes the external header block associated with the object.

\param Object
The object to validate.

*/
/******************************************************************************/
void ObjectAllocator::delete_memblock(void* Object){
  // access the provided block
  byte_t* current = reinterpret_cast<byte_t*>(Object);
  // access the block's header
  MemBlockInfo** extheader = reinterpret_cast<MemBlockInfo**>(current - offset);

  // delete the label string
  delete [] (*extheader)->label;
  // and the header block
  delete *extheader;
}
