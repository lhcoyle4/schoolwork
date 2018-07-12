/*****************************************************************************/
/*!
* \file   BList.h
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: CS280
* \par    Assignment #2
* \date   09/20/14
* 
* \brief
* This file contains the implementation of the header file for the BList
* assignment.
*/
/*****************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef BLIST_H
#define BLIST_H
////////////////////////////////////////////////////////////////////////////////

// MS isn't C++11 compliant yet
#if (_MSC_VER || __BORLANDC__)
  #define NOEXCEPT(X)
#else
  #define NOEXCEPT(X) noexcept(X)
#endif

#include <string>     // error strings

class BListException : public std::exception
{
  private:  
    int m_ErrCode;
    std::string m_Description;

  public:
    BListException(int ErrCode, const std::string& Description) :
    m_ErrCode(ErrCode), m_Description(Description) {};

    virtual int code(void) const { 
      return m_ErrCode; 
    }

    virtual const char *what(void) const throw() {
      return m_Description.c_str();
    }

    virtual ~BListException() throw() {
    }

    enum BLIST_EXCEPTION {E_NO_MEMORY, E_BAD_INDEX, E_DATA_ERROR};
};

struct BListStats
{

  BListStats() : NodeSize(0), NodeCount(0), ArraySize(0), ItemCount(0)  {};
  BListStats(size_t nsize, int ncount, int asize, int count) : 
     NodeSize(nsize), NodeCount(ncount), ArraySize(asize), ItemCount(count)  {};

  size_t NodeSize; // Size of a node
  int NodeCount;   // Number of nodes in the list
  int ArraySize;   // Max number of items in each node
  int ItemCount;   // Number of items in the entire list
};  

template <typename T, int Size = 1>
class BList
{
 
  public:
    struct BNode
    {
      BNode *next;
      BNode *prev;
      int count; // number of items currently in the node
      T values[Size];
      BNode() : next(0), prev(0), count(0) {}
    };

    BList();                 // default constructor                        
    BList(const BList &rhs); // copy constructor
    ~BList() NOEXCEPT(true); // destructor                         

    BList& operator=(const BList &rhs) NOEXCEPT(false);

      // arrays will be unsorted
    void push_back(const T& value) NOEXCEPT(false);
    void push_front(const T& value) NOEXCEPT(false);

      // arrays will be sorted
    void insert(const T& value) NOEXCEPT(false);

    void remove(int index) NOEXCEPT(false);
    void remove_by_value(const T& value); 

    int find(const T& value) const;       // returns index, -1 if not found

    T& operator[](int index) NOEXCEPT(false);             // for l-values
    const T& operator[](int index) const NOEXCEPT(false); // for r-values

    size_t size(void) const;   // total number of items (not nodes)
    void clear(void);          // delete all nodes 

    static size_t nodesize(void); // so the driver knows the size

      // For debugging
    const BNode *GetHead() const;
    BListStats GetStats() const;

  private:
    BNode *head_;           // points to the first node
    BNode *tail_;           // points to the last node
    BListStats stats;
    void pop_front(void);
    bool empty(void);
    BNode* new_node(const T& value);
    void remove_node(BNode* todelete);
    bool full(BNode* isfull);
    void insert_after(BNode* insertafter, const T& value);
    void split_node(BNode* tosplit, const T& value);
    void insert_before(BNode* insertbefore, const T& value);
    BNode* copy_node(BNode* tocopy);
    void insert_into(BNode* insertinto, const T& value);

    // Other private methods you may need
    // copy node X
    // new node(T,T) X
    // split node X
    // is node full X
    // empty X
    // insert into node X
    // delete node X

};

#include "BList.cpp"

#endif // BLIST_H
