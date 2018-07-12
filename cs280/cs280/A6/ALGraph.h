/*****************************************************************************/
/*!
* \file   ALGraph.h
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: CS280
* \par    Assignment #6
* \date   11/23/14
*
* \brief
* This file contains the header file for the ALGraph C++ assignment.
*
*/
/*****************************************************************************/
//---------------------------------------------------------------------------
#ifndef ALGRAPH_H
#define ALGRAPH_H
//---------------------------------------------------------------------------
#include <vector>     /* vector */
#include <queue>      /* priority_queue */
#include <functional> /* greater */

struct DijkstraInfo
{
  unsigned cost;
  std::vector<unsigned> path;
};

struct AdjacencyInfo
{
  unsigned id;
  unsigned weight;
};

typedef std::vector<std::vector<AdjacencyInfo> > ALIST;

class ALGraph
{
  public:
    enum TRAVERSAL_METHOD {DEPTH_FIRST, BREADTH_FIRST};

    ALGraph(unsigned size);
    ~ALGraph();
    void AddDEdge(unsigned source, unsigned destination, unsigned weight);
    void AddUEdge(unsigned node1, unsigned node2, unsigned weight);

    std::vector<unsigned> SearchFrom(unsigned start_node, TRAVERSAL_METHOD method) const;
    std::vector<DijkstraInfo> Dijkstra(unsigned start_node) const;
    ALIST GetAList() const;
    static bool ImplementedSearches();
        
  private:
    struct GNode
    {
      unsigned id;
      bool evaluated;
    };
    struct AdjInfo
    {
      GNode *node;
      unsigned cost;
      DijkstraInfo dInfo;
      bool operator<(const AdjInfo& rhs) const;
      bool operator>(const AdjInfo& rhs) const;
    };

    ALIST alist;
};

#endif
