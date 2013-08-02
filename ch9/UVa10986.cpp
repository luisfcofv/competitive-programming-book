// Sending email
// standard SSSP problem
// demo using Dijkstra's and SPFA

#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#define INF 2000000000

int i, j, t, n, m, S, T, a, b, w, caseNo = 1;
vector<vii> AdjList;

int main() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
#endif

  scanf("%d", &t);
  while (t--) {
    scanf("%d %d %d %d", &n, &m, &S, &T);

    // build graph
    AdjList.assign(n, vii());
    while (m--) {
      scanf("%d %d %d", &a, &b, &w);
      AdjList[a].push_back(ii(b, w)); // bidirectional
      AdjList[b].push_back(ii(a, w));
    }

/*
    // Dijkstra from source S
    vi dist(n, INF); dist[S] = 0;
    priority_queue< ii, vii, greater<ii> > pq; pq.push(ii(0, S)); // sort based on increasing distance

    while (!pq.empty()) { // main loop
      ii top = pq.top(); pq.pop(); // greedy: pick shortest unvisited vertex
      int d = top.first, u = top.second;
      if (d != dist[u]) continue;
      for (j = 0; j < (int)AdjList[u].size(); j++) { // all outgoing edges from u
        int v = AdjList[u][j].first, weight_u_v = AdjList[u][j].second;
        if (dist[u] + weight_u_v < dist[v]) { // if can relax
          dist[v] = dist[u] + weight_u_v; // relax
          pq.push(ii(dist[v], v)); // enqueue this neighbor
        }                          // regardless it is already in pq or not
      }
    }
*/

    // SPFA from source S
    // initially, only S has dist = 0 and in the queue
    vi dist(n, INF); dist[S] = 0;
    queue<int> q; q.push(S);
    vi in_queue(n, 0); in_queue[S] = 1;

    while (!q.empty()) {
      int u = q.front(); q.pop(); in_queue[u] = 0;
      for (j = 0; j < (int)AdjList[u].size(); j++) { // all outgoing edges from u
        int v = AdjList[u][j].first, weight_u_v = AdjList[u][j].second;
        if (dist[u] + weight_u_v < dist[v]) { // if can relax
          dist[v] = dist[u] + weight_u_v; // relax
          if (!in_queue[v]) { // add to the queue only if it's not in the queue
            q.push(v);
            in_queue[v] = 1;
          }
        }
      }
    }

    printf("Case #%d: ", caseNo++);
    if (dist[T] != INF) printf("%d\n", dist[T]);
    else                printf("unreachable\n");
  }

  return 0;
}
