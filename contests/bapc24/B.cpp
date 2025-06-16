#include <bits/stdc++.h>
using namespace std;

using node = tuple<int, int, int, int>;

int dist[5123][22][3][4];
bool seen[5123][22][3][4];

int adj[5123][4];

int find_rev(int u, int j) {
  int v = adj[u][j];
  assert(v != -1);
  for (int i = 0; i < 4; i++)
    if (adj[v][i] == u) return i;
  assert(false);
}

int main() {
  int i, j, n, k;
  cin >> n >> k;
  for (i = 0; i < n; i++)
    for (j = 0; j < 4; j++) {
      cin >> adj[i][j];
      adj[i][j]--;
    }
  if (n == 1) {
    cout << 0 << endl;
    return 0;
  }
  deque<node> q;
  memset(dist, 0x7f, sizeof(dist));
  for (int j = 0; j < 4; j++) {
    if (adj[0][j] != -1) {
      dist[adj[0][j]][0][0][find_rev(0, j)] = 1;
      q.push_back({adj[0][j], 0, 0, find_rev(0, j)});
    }
  }

  while (!q.empty()) {
    auto [u, used, blink, entry_dir] = q.front();
    q.pop_front();
    if (seen[u][used][blink][entry_dir]) continue;
    if (u == n - 1) {
      cout << dist[u][used][blink][entry_dir] << endl;
      return 0;
    }
    seen[u][used][blink][entry_dir] = true;
    for (int j = 0; j < 3; j++) {
      if (used == k && j) continue;
      if (dist[u][used][blink][entry_dir] < dist[u][used + !!j][j][entry_dir]) {
        dist[u][used + !!j][j][entry_dir] = dist[u][used][blink][entry_dir];
        q.push_front({u, used + !!j, j, entry_dir});
      }
    }
    int nx;
    // straight
    if (blink == 0) {
      nx = (entry_dir + 2) % 4;
    } else if (blink == 1) {  // left
      nx = (entry_dir + 1) % 4;
    } else {  // right
      nx = (entry_dir + 3) % 4;
    }
    if (adj[u][nx] != -1 &&
        dist[u][used][blink][entry_dir] + 1 <
            dist[adj[u][nx]][used][blink][find_rev(u, nx)]) {
      dist[adj[u][nx]][used][blink][find_rev(u, nx)] =
          dist[u][used][blink][entry_dir] + 1;
      q.push_back({adj[u][nx], used, blink, find_rev(u, nx)});
    }
  }
  cout << "impossible" << endl;
}
