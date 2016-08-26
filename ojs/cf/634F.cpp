#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 40000;
ll sum[N], lz[N], val[N];
int st[N], L[N], R[N], sz[N], y[N];

inline int acc(int u) {
	if(!u) return 0;
	if(st[u]) { sum[u] = val[u] = 0; st[L[u]] = st[R[u]] = 1; lz[L[u]] = lz[R[u]] = st[u] = 0; }
	if(lz[u]) {
		sum[u] += ll(sz[u]) * lz[u];
		val[u] += lz[u]; lz[L[u]] += lz[u]; lz[R[u]] += lz[u];
		lz[u] = 0;
	}
	return u;
}

inline int calc(int u) {
	if(!u) return 0;
	acc(u); acc(L[u]); acc(R[u]);
	sz[u] = sz[L[u]] + 1 + sz[R[u]];
	sum[u] = sum[L[u]] + val[u] + sum[R[u]];
	return u;
}

void split(int u, int s, int &l, int &r) {
	if(!acc(u)) return (void) (l = r = 0);
	if(s > sz[L[u]]) split(R[u], s - sz[L[u]] - 1, l, r), R[u] = l, l = u;
	else split(L[u], s, l, r), L[u] = r, r = u;
	calc(u);
}

int join(int l, int r) {
	acc(l); acc(r);
	if(!l || !r) return l + r;
	int u;
	if(y[l] > y[r]) u = l, R[l] = join(R[l], r);
	else u = r, L[r] = join(l, L[r]);
	return calc(u);
}

int ti[11], to[11];
int bs[11];
int bnk[10][12];
ll all, tot; int tn;
vector<int> s[3005];
vector<int>::iterator it[3005];

int main() {
	srand(time(NULL));
	int i, j, h, g, r, c, n, k;
	scanf("%d %d %d %d", &r, &c, &n, &k);
	for(i = 0; i < 3000; i++) s[i].pb(r);
	for(i = 0; i < N; i++) y[i] = i, sz[i] = !!i;
	random_shuffle(y, y + N);
	int x, y;
	for(i = 0; i < n; i++) {
		scanf("%d %d", &x, &y); x--; y--;
		s[y].pb(x);
	}
	for(i = 0; i < 3000; i++) sort(s[i].begin(), s[i].end());
	for(i = 0; i < 3000; i++) it[i] = prev(s[i].end());
	for(i = 0; i < r; i++)
		for(j = 0; j < c; j++)
			all += ll(r - i) * ll(c - j);
	for(i = r - 1; i >= 0; i--) {
		ll sm = 0;
		for(g = 0; g < k; g++) {
			st[ti[g] = join(++tn, ti[g])] = 1;
			acc(ti[g]);
		}
		for(j = c - 1; j >= 0; j--) {
			if(it[j] != s[j].begin() && *prev(it[j]) >= i) --it[j];
			if(*it[j] == r) {
				lz[ti[0]]++; acc(ti[0]);
				sm += (r - i);
				tot += sm;
				continue;
			}
			auto b = it[j];
			int mh;
			for(g = k - 1; g >= 0; g--) {
				auto c = b; int cur = i; int tr = ti[g]; ti[g] = 0;
				for(h = 0; h < k && c != s[j].end(); h++, ++c) {
					int t1, t2;
					split(tr, (*c) - cur, t1, t2);
					if(t1 && g == 0) { 
						lz[t1] = 1; acc(t1);
					}
					if(g + h < k)
						ti[g + h] = join(ti[g + h], t1);
					else
						bnk[h][bs[h]++] = t1;
					tr = t2;
					cur = *c;
				}
				to[g] = tr;
				mh = h;
			}
			sm = 0;
			for(g = 0; g < k; g++) {
				for(h = g + 1; h < mh; h++) {
					st[bnk[h][bs[h] - 1]] = 1;
					ti[g] = join(ti[g], bnk[h][--bs[h]]);
				}
				st[to[g]] = 1;
				ti[g] = join(ti[g], to[g]);
				tot += sum[ti[g]];
				sm += sum[ti[g]];
				//printf("[%d] at (%d, %d) with %d\n", g, i, j, sum[ti[g]]);
			}
		}
	}
	printf("%I64d\n", all - tot);

}
