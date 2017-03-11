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

int n;
int a[212345];

int main() {
	int i, j;
	rd(n);
	for(i = 0; i < n; i++) rd(a[i]);
	int mn = a[0], best = 0;
	for(i = 1; i < n; i++) {
		best = max(best, a[i] - mn);
		mn = min(mn, a[i]);
	}
	map<int, vector<int>> mp;
	map<int, int> s;
	mn = a[0]; mp[mn].pb(0);
	for(i = 1; i < n; i++) {
		if(a[i] - mn == best) mp[mn].pb(1), s[mn]++;
		mn = min(mn, a[i]);
		if(mn == a[i]) mp[mn].pb(0);
	}
	int res = 0;
	for(auto p : s) {
		int x = p.fst, ct1 = p.snd;
		int cur1 = 0;
		vector<int> &v = mp[x];
		int ans = min(ct1, int(v.size()) - ct1);
		for(i = 0; i < v.size(); i++) {
			cur1 += v[i];
			int l0 = i + 1 - cur1, r1 = ct1 - cur1;
			ans = min(ans, l0 + r1);
		}
		res += ans;
	}
	printf("%d\n", res);
}
