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

map<vector<int>, bool> mp;
bool can_win(vector<int> v) {
	if(mp.count(v)) return mp[v];
	bool &r = mp[v];
	for(int i = 0; i < v.size(); i++)
		for(int j = (i? v[i - 1] : 0); j < v[i]; j++) {
			vector<int> v2 = v;
			v2[i] = j;
			if(!can_win(v2)) return r = true;
		}
	return r = false;
}

int mx = 10;
int mmm;
void go(vector<int> v) {
	if(v.size() == mmm) {
		if(can_win(v)) return;
		for(int x : v) printf("%2d ", x); putchar('\n');
		return;
	}
	for(int i = (v.empty()? 1 : v.back()); i <= mx; i++) {
		vector<int> v2 = v;
		v2.pb(i);
		go(v2);
	}
}

int main() {
	int a, b, c, d, e;
	int mx = 10;
	rd(mmm);
	go({});
}
