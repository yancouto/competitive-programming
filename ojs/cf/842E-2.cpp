#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

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

int n, p;

const int N = 312345;
int lc[N][20], h[N];

int dist(int a, int b) {
	int d = h[a] + h[b];
	if(h[a] < h[b]) swap(a, b);
	for(int i = 19; i >= 0; i--)
		if(h[lc[a][i]] >= h[b])
			a = lc[a][i];
	if(a != b) {
		for(int i = 19; i >= 0; i--)
			if(lc[a][i] != lc[b][i])
				a = lc[a][i], b = lc[b][i];
		a = lc[a][0];
	}
	return d - 2 * h[a];
}

int main() {
	int i, j;
	rd(n);
	int a = 0, b = 0;
	int mxd = 0;
	vector<int> nds;
	nds.pb(0);
	for(i = 1; i <= n; i++) {
		rd(p); p--;
		h[i] = h[p] + 1;
		lc[i][0] = p;
		for(int b = 1; b < 20; b++)
			lc[i][b] = lc[lc[i][b-1]][b-1];
		int da = dist(i, a);
		int db = dist(i, b);
		printf("[%d] a %d[%d] b %d[%d]\n", i, a, da, b, db);
		if(da < mxd && db < mxd) {
			// nada
		} else if(da <= mxd && db <= mxd) {
			nds.pb(i);
		} else {
			mxd = max(da, db);
			if(da >= db) {
				b = i;
			} else {
				a = i;
			}
			vector<int> nnds;
			nnds.pb(i);
			for(int u : nds)
				if(dist(u, i) == mxd)
					nnds.pb(u);
			nds = nnds;
		}
		for(int x : nds) printf("%d ", x); printf(" == %d\n", mxd);
		printf("%d\n", int(nds.size()));
	}
}
