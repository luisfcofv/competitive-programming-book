#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int main() {
  int V, E, total_neighbors, id, weight, a, b;
  int AdjMat[100][100];
  vector<vii> AdjList;
  priority_queue< pair<int, ii> > EdgeList;   // one way to store Edge List

  // Try this input for Adjacency Matrix/List/EdgeList
  // Adj Matrix
  //   for each line: |V| entries, 0 or the weight
  // Adj List
  //   for each line: num neighbors, list of neighbors + weight pairs
  // Edge List
  //   for each line: a-b of edge(a,b) and weight
  /*
  6
    0  10   0   0 100   0
   10   0   7   0   8   0
    0   7   0   9   0   0
    0   0   9   0  20   5
  100   8   0  20   0   0
    0   0   0   5   0   0
  6
  2 2 10 5 100
  3 1 10 3 7 5 8
  2 2 7 4 9
  3 3 9 5 20 6 5
  3 1 100 2 8 4 20
  1 4 5
  7
  1 2 10
  1 5 100
  2 3 7
  2 5 8
  3 4 9
  4 5 20
  4 6 5
  */
  freopen("in_07.txt", "r", stdin);

  scanf("%d", &V);                         // we must know this size first!
                     // remember that if V is > 100, try NOT to use AdjMat!
  for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++)
      scanf("%d", &AdjMat[i][j]);

  printf("Neighbors of vertex 0:\n");
  for (int j = 0; j < V; j++)                                     // O(|V|)
    if (AdjMat[0][j])
      printf("Edge 0-%d (weight = %d)\n", j, AdjMat[0][j]);

  scanf("%d", &V);
  AdjList.assign(V, vii()); // quick way to initialize AdjList with V entries of vii
  for (int i = 0; i < V; i++) {
    scanf("%d", &total_neighbors);
    for (int j = 0; j < total_neighbors; j++) {
      scanf("%d %d", &id, &weight);
      AdjList[i].push_back(ii(id - 1, weight));    // some index adjustment
    }
  }

  printf("Neighbors of vertex 0:\n");
  for (vii::iterator j = AdjList[0].begin(); j != AdjList[0].end(); j++)
    // AdjList[0] contains the required information
    // O(k), where k is the number of neighbors
    printf("Edge 0-%d (weight = %d)\n", j->first, j->second);

  scanf("%d", &E);
  for (int i = 0; i < E; i++) {
    scanf("%d %d %d", &a, &b, &weight);
    EdgeList.push(make_pair(-weight, ii(a, b))); // trick to reverse sort order
  }

  // edges sorted by weight (smallest->largest)
  for (int i = 0; i < E; i++) {
    pair<int, ii> edge = EdgeList.top(); EdgeList.pop();
    // negate the weight again
    printf("weight: %d (%d-%d)\n", -edge.first, edge.second.first, edge.second.second);
  }

  return 0;
}
