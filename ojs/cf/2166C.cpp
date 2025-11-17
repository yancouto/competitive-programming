#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 998244353;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#define debug
#else
#define debug printf
#endif

int n, q;
ll x[512345], c;

int ct[100];
int mx[100], nct[100];
int mrk[512345], tempo = 0;;

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}
int p[512345];
vector<int> smidx[100];

void go() {
  ll all = 0;
  rd(n); rd(q);
  for(int j = 0; j < 31; j++) ct[j] = mx[j] = 0, smidx[j].clear();
  for(int i = 0; i < n; i++) { 
    p[i] = i;
    rd(x[i]);
    all ^= x[i];
    for(int j = 0; j < 30; j++)
      ct[j] += ((x[i] >> j) & 1);
  }
  for(int j = 0; j < 30; j++) {
    ll msk = (1ll << (j + 1)) - 1;
    partial_sort(p, p + min(32, n), p + n, [&](int i, int j) {
      return (x[i]&msk) > (x[j]&msk);
    });
    for(int k = 0; k < 32 && k < n; k++) smidx[j].pb(p[k]);
    // for(int i = 0; i < n; i++) ms[j].insert(pii(x[i]&msk,i));
    // mx[j] = ((*max_element(x, x + n, [=](int a, int b) {return (a&msk) < (b&msk);}))&msk);
    // debug("mx[%d] = %lld\n", j, mx[j]);
  }
  while(q--) {
    rd(c);
    if(c == all) {
      puts("0");
      continue;
    }
    ll ans = 0;
    bool prefeq = true;
    ll nall = all;
    tempo++;
    for(int j = 30; j >= 0; j--) nct[j] = ct[j];
    for(int j = 30; j >= 0; j--) {
      debug("j = %d\n", j);
      if(((c >> j) & 1) != ((nall >> j) & 1)) prefeq = false;
      if(prefeq && nct[j] > 1) break;
      if(prefeq) continue;
      if(nct[j] > 0) break;
      if(j == 0) {ans+=1; break;}
      // assert(mx[j] == mx[j-1]);
      int k = 0;
      for(; k < smidx[j].size(); k++)
        if(mrk[smidx[j][k]] != tempo)
          break;
      int val, idx;
      if(k == smidx[j].size()) idx = 0, val = 0;
      else idx = smidx[j][k], val = (x[smidx[j][k]]&((1<<(j+1))-1));
      // debug("fst %d snd %d\n", idx, it->second);
      // todo it empty
      mrk[idx] = tempo;
      ans += (1 << j) - val;
      // debug("ans += (%lld - %d) = %d\n", (1<<j), it->first, (1<<j)-it->first);
      nall ^= val;
      debug("nall %lld\n", nall);
      for(int k = j - 1; k >= 0; k--) nct[k] -= ((val >> k) & 1);
      prefeq = true;
    }
    printf("%lld\n", ans);
  }
  
}

int main() {
  int t;
  rd(t);
  while(t--) go();
}