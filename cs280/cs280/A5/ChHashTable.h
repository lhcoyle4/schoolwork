/*****************************************************************************/
/*!
* \file   ChHashTable.h
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: CS280
* \par    Assignment #5
* \date   11/12/14
*
* \brief
* This file contains the implementation of the header file for the
* ChHashTable C++ assignment.
*/
/*****************************************************************************/

//---------------------------------------------------------------------------
#ifndef OAHASHTABLEH
#define OAHASHTABLEH
//---------------------------------------------------------------------------

#include <string>
#include <cmath> // ceil
#include "ObjectAllocator.h"
#include "support.h"

// client-provided hash function: takes a key and table size,
// returns an index in the table.
typedef unsigned (*HASHFUNC)(const char *, unsigned);

// Max length of our "string" keys
const unsigned MAX_KEYLEN = 10;

class HashTableException
{
  private:  
    int error_code_;
    std::string message_;

  public:
    HashTableException(int ErrCode, const std::string& Message) :
        error_code_(ErrCode), message_(Message) {};

    virtual ~HashTableException() {
    }

    virtual int code(void) const { 
      return error_code_; 
    }

    virtual const char *what(void) const {
      return message_.c_str();
    }
    enum HASHTABLE_EXCEPTION {E_ITEM_NOT_FOUND, E_DUPLICATE, E_NO_MEMORY};
};


// HashTable statistical info
struct HTStats
{
  HTStats(void) : Count_(0), TableSize_(0), Probes_(0), Expansions_(0),
                    HashFunc_(0) {};
  unsigned Count_;      // Number of elements in the table
  unsigned TableSize_;  // Size of the table (total slots)
  unsigned Probes_;     // Number of probes performed
  unsigned Expansions_; // Number of times the table grew
  HASHFUNC HashFunc_;   // Pointer to primary hash function
};

template <typename T>
class ChHashTable
{
  public:

    typedef void (*FREEPROC)(T); // client-provided free proc (we own the data)

    struct HTConfig
    {
        HTConfig(unsigned InitialTableSize, 
                 HASHFUNC HashFunc, 
                 double MaxLoadFactor = 3.0,
                 double GrowthFactor = 2.0, 
                 FREEPROC FreeProc = 0) :

        InitialTableSize_(InitialTableSize), 
        HashFunc_(HashFunc), 
        MaxLoadFactor_(MaxLoadFactor), 
        GrowthFactor_(GrowthFactor),
        FreeProc_(FreeProc) {}

      unsigned InitialTableSize_;
      HASHFUNC HashFunc_; 
      double MaxLoadFactor_;
      double GrowthFactor_;
      FREEPROC FreeProc_;
    };
      
      // Nodes that will hold the key/data pairs
    struct ChHTNode
    {
      char Key[MAX_KEYLEN]; // Key is a string
      T Data;               // Client data
      ChHTNode *Next;
      ChHTNode(const T& data) : Data(data) {}; // constructor
    };

      // Each list has a special head pointer
    struct ChHTHeadNode
    {
      ChHTNode *Nodes;
      ChHTHeadNode(void) : Nodes(0), Count(0) {};
      int Count; // For testing
    };

    ChHashTable(const HTConfig& Config, ObjectAllocator* allocator = 0);
    ~ChHashTable();

      // Insert a key/data pair into table. Throws an exception if the
      // insertion is unsuccessful.
    void insert(const char *Key, const T& Data);

      // Delete an item by key. Throws an exception if the key doesn't exist.
      // Compacts the table by moving key/data pairs, if necessary
    void remove(const char *Key);

      // Find and return data by key. Throws an exception if the
      // key doesn't exist.  
    const T& find(const char *Key) const;

      // Removes all items from the table (Doesn't deallocate table)
    void clear(void);

      // Allow the client to peer into the data
    HTStats GetStats(void) const;
    const ChHTHeadNode *GetTable(void) const;

  private:
     mutable HTStats stats_;
     ChHTHeadNode * head_;
     HTConfig config_;
     ObjectAllocator * oa_;
     void grow(void);
     void push_front(const T& Data, const char * Key, ChHTHeadNode &list);
     void remove_node(ChHTNode * &prev);
     void pop_front(ChHTHeadNode &list);

};

#include "ChHashTable.cpp"

#endif

