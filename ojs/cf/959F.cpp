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
#	define debug(args...) ((void) 0)
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

int n;

const int N = 1 << 20;

int a[N];

int mrk[N], tot = 0;
int p2[N];
vector<pii> qs[N];
int ans[N];

int main() {
	int i;
	int q;
	rd(n); rd(q);
	p2[0] = 1;
	for(i = 1; i < N; i++)
		p2[i] = mod(2ll * p2[i - 1]);
	for(i = 0; i < n; i++)
		rd(a[i]);
	for(i = 0; i < q; i++) {
		int l, x;
		rd(l); rd(x);
		qs[l].pb(pii(i, x));
	}
	vector<int> all;
	all.pb(0); mrk[0] = 1; tot = 0;
	for(i = 0; i < n; i++) {
		if(!mrk[a[i]]) {
			vector<int> y;
			for(int x : all)
				mrk[a[i] ^ x] = 1, y.pb(a[i] ^ x);
			for(int yy : y) all.pb(yy);
			tot++;
		}
		for(pii p : qs[i + 1]) {
			if(mrk[p.snd])
				ans[p.fst] = p2[i + 1 - tot];
		}
	}
	for(i = 0; i < q; i++)
		printf("%d\n", ans[i]);
}
