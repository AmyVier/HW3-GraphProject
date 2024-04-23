// Amy Vier and Elaine Hsu
#include "graph.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

// Vertex constructor
Vertex::Vertex(string value)
{
  this->value = value;
}

// Edge constructor
Edge::Edge(int distance, Vertex *destination)
{
  this->distance = distance;
  this->destination = destination;
}

// constructor, empty graph
// directionalEdges defaults to true
Graph::Graph(bool directionalEdges) {}

// destructor
Graph::~Graph() {}

// @return total number of vertices
int Graph::verticesSize() const { return 0; }

// @return total number of edges
int Graph::edgesSize() const { return 0; }

// @return number of edges from given vertex, -1 if vertex not found
int Graph::vertexDegree(const string &label) const { return 0; }

// @return true if vertex added, false if it already is in the graph
bool Graph::add(const string &label)
{
  if (vertices.count(label))
  {
    return false;
  }
  else
  {
    vertices.insert({label, new Vertex(label)});
  }

  return true;
}

/** return true if vertex already in graph */
bool Graph::contains(const string &label) const { return true; }

// @return string representing edges and weights, "" if vertex not found
// A-3->B, A-5->C should return B(3),C(5)
string Graph::getEdgesAsString(const string &label) const { return ""; }

// @return true if successfully connected
bool Graph::connect(const string &from, const string &to, int weight)
{
  Vertex *fromVertex;
  Vertex *toVertex;

  // get vertices if found, return false if not found
  if (vertices.count(from) && vertices.count(to))
  {
    fromVertex = vertices[from];
    toVertex = vertices[to];
  }
  else
  {
    return false;
  }

  // if edge already exists, return false
  if (fromVertex->edges.count(to))
  {
    return false;
  }

  // connect
  fromVertex->edges.insert({to, new Edge(weight, toVertex)});

  // if not directional, add one more connection of opposite direction
  if (!(directionalEdges))
  {
    toVertex->edges.insert({from, new Edge(weight, fromVertex)});
  }

  return true;
}

bool Graph::disconnect(const string &from, const string &to)
{
  Vertex *fromVertex;
  Vertex *toVertex;

  // get vertices if found, return false if not found
  if (vertices.count(from) && vertices.count(to))
  {
    fromVertex = vertices[from];
    toVertex = vertices[to];
  }
  else
  {
    return false;
  }

  // if connection does not exist, return false, if exists, disconnect
  if (fromVertex->edges.count(to))
  {
    fromVertex->edges.erase(to);
  }
  else
  {
    return false;
  }

  // if not directional get rid of connection of opposite direction
  if (!(directionalEdges))
  {
    toVertex->edges.erase(from);
  }

  return true;
}

// depth-first traversal starting from given startLabel
void Graph::dfs(const string &startLabel, void visit(const string &label)) {}

// breadth-first traversal starting from startLabel
void Graph::bfs(const string &startLabel, void visit(const string &label)) {}

// store the weights in a map
// store the previous label in a map
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string &startLabel) const
{
  map<string, int> weights;
  map<string, string> previous;
  // TODO(student) Your code here
  return make_pair(weights, previous);
}

// minimum spanning tree using Prim's algorithm
int Graph::mstPrim(const string &startLabel,
                   void visit(const string &from, const string &to,
                              int weight)) const
{
  return -1;
}

// minimum spanning tree using Prim's algorithm
int Graph::mstKruskal(const string &startLabel,
                      void visit(const string &from, const string &to,
                                 int weight)) const
{
  return -1;
}

// read a text file and create the graph
bool Graph::readFile(const string &filename)
{
  ifstream myfile(filename);
  if (!myfile.is_open())
  {
    cerr << "Failed to open " << filename << endl;
    return false;
  }
  int edges = 0;
  int weight = 0;
  string fromVertex;
  string toVertex;
  myfile >> edges;
  for (int i = 0; i < edges; ++i)
  {
    myfile >> fromVertex >> toVertex >> weight;
    connect(fromVertex, toVertex, weight);
  }
  myfile.close();
  return true;
}
