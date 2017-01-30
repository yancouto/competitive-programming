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

int n, k;

vector<int> M[5555];
int p[5555];

int main() {
	int i, j;
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	rd(n); rd(k);
	for(i = 0; i < n; i++) {
		int m, c;
		rd(m); rd(c);
		M[m].pb(c);
	}
	for(i = 0; i <= 4009; i++) p[i] = i;
	sort(p, p + 4007, [](int i, int j) { return M[i].size() > M[j].size(); });
	int sz = M[p[k - 1]].size();
	if(sz == 0) { puts("0 0"); return 0; }
	vector<int> vals;
	for(i = 0; i <= 4003; i++) {
		if(M[i].size() < sz) continue;
		sort(M[i].begin(), M[i].end(), greater<int>());
		int cur = 0;
		for(j = 0; j < sz; j++) cur += M[i][j];
		vals.pb(cur);
	}
	sort(vals.begin(), vals.end(), greater<int>());
	int best = 0;
	for(i = 0; i < k; i++) best += vals[i];
	printf("%d %d\n", sz, best);

}

