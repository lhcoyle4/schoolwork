/*****************************************************************************/
/*!
* \file   ALGraph.cpp
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: CS280
* \par    Assignment #6
* \date   11/23/14
*
* \brief
* This file contains the implementation of the following functions for the
* ALGraph C++ assignment.
*
* Hours spent on this assignment: 5
*
* Specific portions that gave you the most trouble: Figuring out Dijkstra
*/
/*****************************************************************************/

#include "ALGraph.h"

const unsigned INFINITY_ = static_cast<unsigned>(-1);

/*****************************************************************************/
/*!
* Constructor for an ALGraph
*
* \author	louis.coyleii
* \date	11/23/14
*
* \param size The number of nodes for the graph to construct.
*
*/
/*****************************************************************************/
ALGraph::ALGraph(unsigned size)
{
  alist.reserve(size);
  for (unsigned i = 0; i < size; ++i)
  {
    // push back a vector of AdjacencyInfos for each node
    alist.push_back(ALIST::value_type());
  }
}

/*****************************************************************************/
/*!
* Destructor for an ALGraph
*
* \author	louis.coyleii
* \date	11/23/14
*
*/
/*****************************************************************************/
ALGraph::~ALGraph(void)
{
  alist.clear();
}

/*****************************************************************************/
/*!
* Adds a directed edge to the graph.
*
* \author	louis.coyleii
* \date	11/23/14
*
* \param source Where the edge starts from.
* \param destination Where the edge ends up.
* \param weight The cost of the edge.
*
*/
/*****************************************************************************/
void ALGraph::AddDEdge(unsigned source, unsigned destination, unsigned weight)
{
  // create adjacency info element for this edge
  AdjacencyInfo adjInfo = { destination, weight };
  // and create iterate in order to insert into the vector
  std::vector<AdjacencyInfo>::iterator it;

  for (it = alist[source - 1].begin(); it < alist[source - 1].end(); ++it)
  {
    // if the weight is less than the weight of the current node in alist
    if (weight < it->weight)
    {
      // then insert it here and return
      alist[source - 1].insert(it, adjInfo);
      return;
    }
    // if the weight is equal, sort by id
    if (weight == it->weight)
    {
      if (destination < it->id)
      {
        alist[source - 1].insert(it, adjInfo);
        return;
      }
    }
  }
  // if a spot cannot be found to insert the edge before other edges in the 
  // adjacency list, then just push it to the back of the list.
  alist[source - 1].push_back(adjInfo);
}

/*****************************************************************************/
/*!
* Adds an undirected edge to the graph.
*
* \author	louis.coyleii
* \date	11/23/14
*
* \param node1 One endpoint of the edge.
* \param node2 The other endpoint of the edge.
* \param weight The cost of the edge.
*
*/
/*****************************************************************************/
void ALGraph::AddUEdge(unsigned node1, unsigned node2, unsigned weight)
{
  // in order to make the edge undirected, add two directed edges
  // one in each direction
  AddDEdge(node1, node2, weight);
  AddDEdge(node2, node1, weight);
}

/*****************************************************************************/
/*!
* Searches the graph, constructing a list of paths and costs.
*
* \author	louis.coyleii
* \date	11/23/14
*
* \param start_node The node to start the search from.
* \param method How the graph should be traversed.
*
* \return std::vector<unsigned> The list of paths and costs.
*
*/
/*****************************************************************************/
std::vector<unsigned> ALGraph::SearchFrom(unsigned start_node, TRAVERSAL_METHOD method) const
{
  // probably won't implement this, so return an empty vector
  std::vector<unsigned> empty;
  if (method)
    empty.push_back(start_node);
  empty.clear();
  return empty;
}

/*****************************************************************************/
/*!
* Searches the graph, constructing a list of paths and costs, using Dijkstra.
*
* \author	louis.coyleii
* \date	11/23/14
*
* \param start_node The node to start the search from.
*
* \return std::vector<DijkstraInfo> The list of paths and costs.
*
*/
/*****************************************************************************/
std::vector<DijkstraInfo> ALGraph::Dijkstra(unsigned start_node) const
{
  // the return vector of least cost paths to each node from the start_node
  std::vector<DijkstraInfo> dInfo;

  // override the default behavior of priority_queue to allow the use of pop
  // to get the node from the PQ with lowest total cost, rather than greatest
  //std::greater<AdjInfo> cmp;
  //std::priority_queue<AdjInfo, std::vector<AdjInfo>, std::greater<AdjInfo> > pq(cmp);
  std::priority_queue<AdjInfo> pq;

  std::vector<AdjInfo> nodes;
  nodes.reserve(alist.size());

  // make list of nodes to keep track of paths and evaluations
  for (unsigned i = 0; i < alist.size(); ++i)
  {
    // Initialize all nodes to infinite cost from the source.
    AdjInfo topush;
    nodes.push_back(topush);
    GNode *node = new GNode;
    (*node).id = i + 1;
    (*node).evaluated = false;
    nodes[i].node = node;
    nodes[i].cost = INFINITY_;
    nodes[i].dInfo.cost = INFINITY_;
  }

    // Choose a node to be the source or starting point.
    // Initialize start node to 0 cost and mark as evaluated.
    nodes[start_node - 1].dInfo.cost = 0;
    nodes[start_node - 1].node->evaluated = true;
    nodes[start_node - 1].dInfo.path.push_back(start_node);

    // For each node, y, adjacent to start node
    for (unsigned i = 0; i < alist[start_node - 1].size(); ++i)
    {
      // save current id to reduce typing...
      unsigned y_id = alist[start_node - 1][i].id - 1;
      //  1. Relax the node. That is, set y's cost to the cost of all edges from source to y.
      //  in this case, the cost to reach the node from source is just the weight of edge
      nodes[y_id].dInfo.cost = alist[start_node - 1][i].weight;
      //  2. Place y into a priority queue based on its total cost. (Lower is better)
      pq.push(nodes[y_id]);
      //  3. Add source node as predecessor of y.
      nodes[y_id].dInfo.path.push_back(start_node);
      nodes[y_id].dInfo.path.push_back(nodes[y_id].node->id);
    }

    // While there are nodes in the graph that haven't been evaluated
    while (!pq.empty())
    {
      // Remove a node, x, from the PQ (lowest total cost)
      AdjInfo x = pq.top();
      pq.pop();
      // Mark x as evaluated.
      x.node->evaluated = true;
      // For each neighbor, y, of x
      for (unsigned i = 0; i < alist[x.node->id - 1].size(); ++i)
      {
        unsigned y_id = alist[x.node->id - 1][i].id - 1;
        // Relax y, that is set cost to cost of all edges from source to y
        nodes[y_id].cost = nodes[x.node->id - 1].dInfo.cost + alist[x.node->id - 1][i].weight;
        // If new cost to reach y is less
        if (nodes[y_id].cost < nodes[y_id].dInfo.cost)
        {
          nodes[y_id].dInfo.cost = nodes[y_id].cost;
          // Update list of nodes (path) to y from source.
          nodes[y_id].dInfo.path = nodes[x.node->id - 1].dInfo.path;
          nodes[y_id].dInfo.path.push_back(nodes[y_id].node->id);
          // Place y in the PQ.
          pq.push(nodes[y_id]);
        }
      }
    }

  // grab all of the dInfo's from the nodes vector
  for (unsigned i = 0; i < nodes.size(); ++i)
  {
    dInfo.push_back(nodes[i].dInfo);
    delete nodes[i].node;
  }

  // return the completed dInfo vector
  return dInfo;
}

/*****************************************************************************/
/*!
* Gets an adjacency list for the graph.
*
* \author	louis.coyleii
* \date	11/23/14
*
* \return ALIST The adjacency list.
*
*/
/*****************************************************************************/
ALIST ALGraph::GetAList(void) const
{
  return alist;
}

/*****************************************************************************/
/*!
* Returns true if searches were implemented.
*
* \author	louis.coyleii
* \date	11/23/14
*
* \return bool Whether or not searches were implemented.
*
*/
/*****************************************************************************/
bool ALGraph::ImplementedSearches(void)
{
  return false;
}

/*****************************************************************************/
/*!
* Returns true if lhs < rhs.
*
* \author	louis.coyleii
* \date	11/23/14
*
* \return bool Whether or not the cost of the lhs is < cost of rhs.
*
*/
/*****************************************************************************/
bool ALGraph::AdjInfo::operator<(const AdjInfo& rhs) const
{
  return this->cost < rhs.cost;
}

/*****************************************************************************/
/*!
* Returns true if lhs > rhs.
*
* \author	louis.coyleii
* \date	11/23/14
*
* \return bool Whether or not the cost of the lhs is > cost of rhs.
*
*/
/*****************************************************************************/
bool ALGraph::AdjInfo::operator>(const AdjInfo& rhs) const
{
  return this->cost > rhs.cost;
}