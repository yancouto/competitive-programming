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

int n, t;

map<vector<int>, ll> mp;

ll solve(const vector<int> &v, bool empty) {
	if(v.back() == 0) return 1;
	if(mp.count(v)) return mp[v];
	ll &r = mp[v];
	r = 0;
	for(int i = empty; i < 16; i++) {
		if(v[i] == t) continue;
		vector<int> v2 = v;
		v2.back()--;
		v2[i]++;
		r += solve(v2, false);
	}
	return r;
}

int main() {
	int i, j, k, g;
	rd(k); rd(t);
	for(i = 1; ; i++) {
		vector<int> v;
		for(j = 0; j < 16; j++) v.pb(0);
		v.pb(i);
		if(solve(v, true) < k) { k -= solve(v, true); continue; }
		for(j = 0; j < i; j++) {
			for(g = !j; ; g++) {
				assert(g < 16);
				if(v[g] == t) continue;
				vector<int> v2 = v;
				v2.back()--;
				v2[g]++;
				if(solve(v2, false) < k) k -= solve(v2, false);
				else {
					v = v2;
					break;
				}
			}
			putchar("0123456789abcdef"[g]);
		}
		putchar('\n');
		return 0;
	}
}
