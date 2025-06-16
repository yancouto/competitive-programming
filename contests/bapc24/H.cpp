#include <bits/stdc++.h>
using namespace std;
#define pb push_back
// #define debug printf
#define debug
#define gc _getchar_nolock

const int Q = 112345, NN = 3009;

int pq[Q], h[Q], w[Q];

vector<int> up[NN];

struct pii {
  int i, j;
};

int r, c;
int ans[Q];

int vec_count[9000009], suf_count[9000009];
int vec_sum[9000009], suf_sum[9000009];

vector<int> bit_count[NN], bit_sum[NN];
int tot_count[NN], tot_sum[NN];
vector<int> R[NN], L[NN];

// val[i] += x
void add(vector<int> &bit, int vec[], int &tot, int i, int x) {
  vec[i] += x;
  tot += x;
  for (int j = i + 1; j < bit.size(); j += j & -j) bit[j] += x;
}

int query(vector<int> &bit, int i) {
  int r = 0;
  for (int j = i; j; j -= j & -j) r += bit[j];
  return r;
}

void activate(int i, int j) {
  debug("activate(%d, %d)\n", i, j);
  assert(L[i][j] == -1);
  int nl = j, nr = j;
  if (j && L[i][j - 1] != -1) nl = L[i][j - 1];
  if (j + 1 < c && R[i][j + 1] != -1) nr = R[i][j + 1];
  L[i][j] = nl;
  R[i][j] = nr;
  if (j && L[i][j - 1] != -1) {
    debug("rem sizeL %d\n", j - L[i][j - 1]);
    add(bit_count[i], vec_count, tot_count[i], j - L[i][j - 1], -1);
    add(bit_sum[i], vec_sum, tot_sum[i], j - L[i][j - 1], -(j - L[i][j - 1]));
    R[i][L[i][j - 1]] = nr;
  }
  if (j + 1 < c && R[i][j + 1] != -1) {
    debug("rem sizeR %d\n", R[i][j + 1] - j);
    add(bit_count[i], vec_count, tot_count[i], R[i][j + 1] - j, -1);
    add(bit_sum[i], vec_sum, tot_sum[i], R[i][j + 1] - j, -(R[i][j + 1] - j));
    L[i][R[i][j + 1]] = nl;
  }
  int sz = nr - nl + 1;
  debug("Add size %d (%d, %d)\n", sz, nl, nr);
  add(bit_count[i], vec_count, tot_count[i], sz, 1);
  add(bit_sum[i], vec_sum, tot_sum[i], sz, sz);
}

int query(int i, int w) {}

inline void rd(int &x) {
  // scanf("%d", &x);
  char c;
  while (isspace(c = gc()));
  x = c - '0';
  while (isdigit(c = gc())) x = x * 10 + (c - '0');
}

int main() {
  int i, q, j;
  rd(r);
  rd(c);
  rd(q);
  bool sw = r > c;
  vector<vector<char>> s(r);
  for (i = 0; i < r; i++) {
    s[i].resize(c + 2);
    while (isspace(s[i][0] = gc()));
    for (j = 1; !isspace(s[i][j] = gc()); j++);
  }
  if (sw) swap(r, c);
  vector<pii> idx;
  for (i = 0; i < r; i++) {
    up[i].resize(c + 5, 0);
    L[i].resize(c + 5, 0);
    R[i].resize(c + 5, 0);
    bit_count[i].resize(c + 5, 0);
    bit_sum[i].resize(c + 5, 0);
    for (j = 0; j < c; j++) {
      L[i][j] = R[i][j] = -1;
      char mc = sw ? s[j][i] : s[i][j];
      up[i][j] = mc == '#' ? 0 : 1 + (i == 0 ? 0 : up[i - 1][j]);
      if (mc == '.') idx.pb({i, j});
    }
  }
  sort(idx.begin(), idx.end(),
       [](pii a, pii b) { return up[a.i][a.j] > up[b.i][b.j]; });
  for (i = 0; i < q; i++) {
    pq[i] = i;
    rd(h[i]);
    rd(w[i]);
    if (sw) swap(h[i], w[i]);
  }
  sort(pq, pq + q, [](int i, int j) { return h[i] > h[j]; });
  int to_activate = 0;
  for (int qi = 0; qi < q; qi++) {
    int hi = h[pq[qi]], wi = w[pq[qi]];
    bool any = false;
    while (to_activate < idx.size() &&
           up[idx[to_activate].i][idx[to_activate].j] >= hi) {
      auto [i, j] = idx[to_activate++];
      activate(i, j);
      any = true;
    }
    if (any) {
      suf_count[c] = vec_count[c];
      for (i = c - 1; i >= 0; i--)
        suf_count[i] = suf_count[i + 1] + vec_count[i];
      suf_sum[c] = vec_sum[c];
      for (i = c - 1; i >= 0; i--) suf_sum[i] = suf_sum[i + 1] + vec_sum[i];
    }
    ans[pq[qi]] = suf_sum[wi] - suf_count[wi] * (wi - 1);
    // for (i = 0; i < r; i++) ans[pq[qi]] += query(i, wi);
  }
  for (i = 0; i < q; i++) printf("%d\n", ans[i]);
}