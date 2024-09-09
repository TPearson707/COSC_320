/*
 * Name of Author: Thomas Pearson
 * Date of Creation: 05/06/2024
 * Date of Last Update: 05/06/2024
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <string>

#include "WGraph.h"
#include "Graph.h"

using namespace std;
using namespace std::chrono;

template <class T, class W> WGraph<T, W> JarnikPrimAlgorithm(WGraph<T, W> &);
template <class T, class W> W totalWeight(WGraph<T, W> &);
template <class T, class W> WGraph<T, W> KruskalAlgorithm(WGraph<T, W> &);
template <class T, class W> bool detectCycles(WGraph<T, W> &);
template <class T, class W> void CycleDFS(WGraph<T, W> &, vector<int> &, vector<T> &, int, int &, vector<pair<T, T>> &, bool &);

template <class T, class W> bool connected(WGraph<T, W> &);
template <class T, class W> void ConnDFS(WGraph<T, W> &, vector<int> &, vector<T> &, int, int &);

template <class T> bool connected(Graph<T> &);
template <class T> void ConnDFS(Graph<T> &, vector<int> &, vector<T> &, int, int &);

void div() { cout << "\n---------------------------------\n\n"; }

int main() {

  int numVertices;
  int numEdges;
  srand(time(0));

  cout << "Input the max number of vertices for the graph: ";
  cin >> numVertices;

  cout << "Input the number of edges for the graph: ";
  cin >> numEdges;

  WGraph<int, int> graph;

  for (int i = 0; i < 14; i++) {

    graph.clear();

    switch(i) {
      case 0:
        numVertices = 10;
        numEdges = 10;
        break;
      case 1:
        numVertices = 10;
        numEdges = 20;
        break;
      case 2:
        numVertices = 10;
        numEdges = 30;
        break;
      case 3:
        numVertices = 10;
        numEdges = 40;
        break;
      case 4:
        numVertices = 10;
        numEdges = 50;
        break;
      case 5:
        numVertices = 10;
        numEdges = 60;
        break;
      case 6:
        numVertices = 10;
        numEdges = 70;
        break;
      case 7:
        numVertices = 10;
        numEdges = 10;
        break;
      case 8:
        numVertices = 20;
        numEdges = 10;
        break;
      case 9:
        numVertices = 30;
        numEdges = 10;
        break;
      case 10:
        numVertices = 40;
        numEdges = 10;
        break;
      case 11:
        numVertices = 50;
        numEdges = 10;
        break;
      case 12:
        numVertices = 60;
        numEdges = 10;
        break;
      case 13:
        numVertices = 70;
        numEdges = 10;
        break;
    }

    do {

      for (int j = 0; j < numEdges; j++) {
        int v1 = rand() % numVertices + 1;
        int v2 = rand() % numVertices + 1;

        while (v2 == v1)
          v2 = rand() % numVertices + 1;

        int weight = rand() % 100 + 1;

        graph.addEdge(v1, v2, weight);
      }

    } while(!connected(graph));


    cout << "Testing with max vertices: " << numVertices << endl;
    cout << "Testing with edges: " << numEdges << endl;

    auto start = high_resolution_clock::now();

      WGraph<int, int> MSTK = KruskalAlgorithm(graph);

    auto stop = high_resolution_clock::now();
    auto elapsed = duration_cast<microseconds>(stop - start);
    cout << "Time to MST with Kruskal: " << elapsed.count() << " seconds" << endl;

    start = high_resolution_clock::now();

      WGraph<int, int> MSTP = JarnikPrimAlgorithm(graph);

    stop = high_resolution_clock::now();
    elapsed = duration_cast<microseconds>(stop - start);
    cout << "Time to MST with Prim: " << elapsed.count() << " seconds " << endl;

    if (i != 13)
      cout << endl;

    string gml1 = "KruMST" + to_string(i);
    string gml2 = "PriMST" + to_string(i);

    MSTK.sortVertexList();
    MSTK.saveGraphFileGML(gml1);

    MSTP.sortVertexList();
    MSTP.saveGraphFileGML(gml2);

  }
  return 0;
}


template <class T, class W> WGraph<T, W> JarnikPrimAlgorithm(WGraph<T, W> &G) {
  WGraph<T, W> MST;

  vector<pair<T, pair<T, W>>> edges = G.getEdgeList();

  sort(edges.begin(), edges.end(),
       [](auto &a, auto &b) { return a.second.second < b.second.second; });

  int Gvertcount = G.size();

  MST.addEdge(edges[0]);

  for (int i = 1; i < Gvertcount - 1; i++) {
    for (size_t j = 1; j < edges.size(); j++) {

      WGraph<T, W> TestMST = MST;
      TestMST.addEdge(edges[j]);

      if (!detectCycles(TestMST) && MST.getEdgePos(edges[j].first, edges[j].second.first) == -1) {

        MST.addEdge(edges[j]);
        break;
      }
    }
  }

  return MST;
}

template <class T, class W> W totalWeight(WGraph<T, W> &G) {
  W total = 0;
  vector<pair<T, pair<T, W>>> edges = G.getEdgeList();

    for (size_t i = 0; i < edges.size(); i++) {
      if (G.isDirected() || edges[i].first < edges[i].second.first)
        total += edges[i].second.second;
    }

  return total;
}

/*
Kruskal's Algorithm for finding a minimal spanning tree for a weighted,
connected, undirected graph.  The algorithm does not check that the graph is
connected, it is assumed that this is the case.

Parameter: Weighted Connected Undirected Graph G.
*/
template <class T, class W> WGraph<T, W> KruskalAlgorithm(WGraph<T, W> &G) {
  WGraph<T, W> MST;
  vector<pair<T, pair<T, W>>> edges = G.getEdgeList();

  sort(edges.begin(), edges.end(),
       [](auto &a, auto &b) { return a.second.second < b.second.second; });

  int MSTedgecount = 0;
  int Gvertcount = G.size();
  for (size_t i = 0; i < edges.size() && MSTedgecount < Gvertcount - 1; i++) {
    // If the edge is already in the graph move to the next one.
    if (MST.getEdgePos(edges[i].first, edges[i].second.first) != -1)
      continue;

    WGraph<T, W> TestMST = MST;
    TestMST.addEdge(edges[i]);
    if (!detectCycles(TestMST)) {
      MST.addEdge(edges[i]);
      MSTedgecount++;
    }
  }

  return MST;
}

/*
Cycle detection algorithm for an undirected weighted graph.  This portion
sets up the counting array and edge tracker and then calls the recursive
depth first search algorithm to cycle check.

Parameter: Weighted Graph G.
*/
template <class T, class W> bool detectCycles(WGraph<T, W> &G) {
  vector<T> vlist = G.getVertexList();
  vector<int> num(vlist.size());
  vector<pair<T, T>> Edges;
  int count = 1;
  bool cycle;

  while (find(num.begin(), num.end(), 0) < num.end()) {
    int pos = find(num.begin(), num.end(), 0) - num.begin();
    CycleDFS(G, num, vlist, pos, count, Edges, cycle);
  }

  return cycle;
}

/*
Recursive depth first search algorithm to cycle check, for an undirected
weighted graph.

Parameters:
 - Weighted Graph G
 - num: vector of integer counts to track visitation
 - vlist: vector of vertex names, used to determine positions of the
     vector/edge data in the graph.
 - pos: position of the vertex being processed/visited by the algorithm.
 - count: The current visit count.
 - Edges: vector of edge data for the sequence of the Depth First Search
     visits and edges traversed.
 - cycle: boolean output parameter that results in true if a cycle exists.
     Should be set to false on the call.
*/
template <class T, class W>
void CycleDFS(WGraph<T, W> &G, vector<int> &num, vector<T> &vlist, int pos,
              int &count, vector<pair<T, T>> &Edges, bool &cycle) {
  vector<pair<T, W>> Adj = G.getAdjacentList(vlist[pos]);
  num[pos] = count++;

  for (size_t i = 0; i < Adj.size(); i++) {
    T vert = Adj[i].first;

    size_t vPos = find(vlist.begin(), vlist.end(), vert) - vlist.begin();
    if (vPos < vlist.size() && num[vPos] == 0) {
      Edges.push_back({vlist[pos], vert});
      CycleDFS(G, num, vlist, vPos, count, Edges, cycle);
    } else if (find(Edges.begin(), Edges.end(), make_pair(vert, vlist[pos])) ==
               Edges.end()) {
      cycle = true;
      return;
    }
  }
}

/*
Connected algorithm for our graph class.  Simply calls the DFS recursive
helper function.  If the recursion visits all the nodes then the count
will be the graph size + 1.  Otherwise the graph is not connected.

Parameter: WGraph G.

Notes: If the graph is directed this will check strong connectedness.
 */
template <class T, class W> bool connected(WGraph<T, W> &G) {
  vector<T> vlist = G.getVertexList();
  vector<int> num(vlist.size());
  int count = 1;
  ConnDFS(G, num, vlist, 0, count);
  return (static_cast<size_t>(count) == G.getVertexList().size() + 1);
}

/*
ConnDFS recursive helper function for the connected algorithm.

Parameters:
 - WGraph G
 - num: vector of integer counts to track visitation
 - vlist: vector of vertex names, used to determine positions of the
     vector/edge data in the graph.
 - pos: position of the vertex being processed/visited by the algorithm.
 - count: The current visit count.
 */
template <class T, class W>
void ConnDFS(WGraph<T, W> &G, vector<int> &num, vector<T> &vlist, int pos,
             int &count) {
  vector<pair<T, W>> Adj = G.getAdjacentList(vlist[pos]);
  num[pos] = count++;

  for (size_t i = 0; i < Adj.size(); i++) {
    T vert = Adj[i].first;
    size_t vPos = find(vlist.begin(), vlist.end(), vert) - vlist.begin();
    if (vPos < vlist.size() && num[vPos] == 0)
      ConnDFS(G, num, vlist, vPos, count);
  }
}

/*
Connected algorithm for our graph class.  Simply calls the DFS recursive
helper function.  If the recursion visits all the nodes then the count
will be the graph size + 1.  Otherwise the graph is not connected.

Parameter: Graph G.

Notes: If the graph is directed this will check strong connectedness.
 */
template <class T> bool connected(Graph<T> &G) {
  vector<T> vlist = G.getVertexList();
  vector<int> num(vlist.size());
  int count = 1;
  ConnDFS(G, num, vlist, 0, count);
  return (static_cast<size_t>(count) == G.getVertexList().size() + 1);
}

/*
ConnDFS recursive helper function for the connected algorithm.

Parameters:
 - Graph G
 - num: vector of integer counts to track visitation
 - vlist: vector of vertex names, used to determine positions of the
     vector/edge data in the graph.
 - pos: position of the vertex being processed/visited by the algorithm.
 - count: The current visit count.
 */
template <class T>
void ConnDFS(Graph<T> &G, vector<int> &num, vector<T> &vlist, int pos,
             int &count) {
  vector<T> Adj = G.getAdjacentList(vlist[pos]);
  num[pos] = count++;

  for (size_t i = 0; i < Adj.size(); i++) {
    T vert = Adj[i];
    size_t vPos = find(vlist.begin(), vlist.end(), vert) - vlist.begin();
    if (vPos < vlist.size() && num[vPos] == 0)
      ConnDFS(G, num, vlist, vPos, count);
  }
}
