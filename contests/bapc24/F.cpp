#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define all(x) x.begin(), x.end()
#define int ll
#define pb push_back

void dbg_out() { cerr << endl; }
template <typename H, typename... T>
void dbg_out(H h, T... t) {
  cerr << ' ' << h;
  dbg_out(t...);
}
#define dbg(...)                 \
  {                              \
    cerr << #__VA_ARGS__ << ':'; \
    dbg_out(__VA_ARGS__);        \
  }

struct SCC {
  vector<bool> bridge;
  vector<int> comp;

  int ncomp;
  vector<int> sz;
  vector<vector<pair<int, int>>> gc;

  SCC(int n, int m, vector<pair<int, int>> g[])
      : bridge(m), comp(n, -1), ncomp(0) {
    vector<bool> vis(n);
    vector<int> low(n), prof(n);

    function<void(int, int)> dfs = [&](int v, int dad) {
      vis[v] = 1;
      for (auto [p, e] : g[v])
        if (e != dad) {
          if (!vis[p]) {
            low[p] = prof[p] = prof[v] + 1;
            dfs(p, e);
            low[v] = min(low[v], low[p]);
          } else {
            low[v] = min(low[v], prof[p]);
          }
        }
      if (low[v] == prof[v]) ncomp++;
    };
    for (int i = 0; i < n; i++) {
      if (!vis[i]) dfs(i, -1);
    }
    sz.resize(ncomp);
    gc.resize(ncomp);

    int cnt = 0;
    function<void(int, int)> build = [&](int v, int c) {
      if (low[v] == prof[v]) c = cnt++;
      comp[v] = c;
      sz[c] += 1;
      for (auto [p, e] : g[v])
        if (comp[p] == -1) {
          build(p, c);
          int pc = comp[p];
          if (c == pc) continue;
          bridge[e] = true;
          gc[c].emplace_back(pc, e);
          gc[pc].emplace_back(c, e);
        }
    };
    for (int i = 0; i < n; i++) {
      if (comp[i] == -1) build(i, -1);
    }
  }
};

// value = d * 10^-p
// d <= 10 usually
struct my_d {
  double d;
  int p;
  void print() {
    if (d == 0)
      cout << "0";
    else {
      cout << setprecision(20) << d;
      assert(p >= 0);
      if (p > 0) cout << "e-" << p;
    }
  }
  my_d mult(my_d o) { return my_d{d * o.d, p + o.p}.fix(); }
  my_d fix() {
    while (d >= 10) d /= 10, p--;
    if (d > 0) {
      while (d < 1) d *= 10, p++;
    }
    return *this;
  }
  bool operator<(my_d &o) {
    if (d == 0 && o.d != 0) return true;
    if (d != 0 && o.d == 0) return false;
    if (o.p != p) return p > o.p;
    return d < o.d;
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  vector<double> p(n);
  vector<my_d> succ(n);
  for (int i = 0; i < n; i++) {
    string num;
    cin >> num;
    p[i] = log10(1.0 - stod(num));
    // succ[i] = my_d{1 - p[i], 0}.fix();
  }
  vector<vector<pair<int, int>>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u -= 1, v -= 1;
    adj[v].emplace_back(u, i);
  }

  SCC scc(n, m, adj.data());
  vector<int> in_deg(scc.ncomp);
  for (int u = 0; u < n; u++) {
    for (auto [v, i] : adj[u]) {
      if (scc.comp[u] == scc.comp[v]) continue;
      in_deg[scc.comp[v]] += 1;
    }
  }

  // vector<my_d> res(scc.ncomp, my_d{1, 0});
  vector<ld> res(scc.ncomp, log10(1));
  for (int i = 0; i < n; i++) {
    int curr = scc.comp[i];
    if (in_deg[curr]) {
      res[curr] = -1. / 0.;
      continue;
    }
    res[curr] += p[i];
    // res[curr] = res[curr].mult(succ[i]);
  }
  cout << fixed << setprecision(20);
  ld best = *max_element(all(res));
  if (best < -10000000) {
    cout << 0 << endl;
    return;
  }
  ld e = floor(best);
  ld d = pow(10, best - e);
  cout << d;
  if (e < 0) cout << "e" << setprecision(0) << e;
  cout << '\n';
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();
}
