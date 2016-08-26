#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<double, double> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif

vector<pii> go(vector<pii> v, double s) {
	if(v.size() <= 1) return v;
	vector<pii> v1, v2, v3, v4;
	for(int i = 0; i < v.size(); i++)
		if(v[i].x <= s/2. && v[i].y <= s/2.) v1.pb(v[i]);
		else if(v[i].x <= s/2.) v2.pb(v[i]);
		else if(v[i].y >= s/2.) v3.pb(v[i]);
		else v4.pb(v[i]);
	vector<pii> ans;
	// PT 1
	for(pii &p : v1) p = pii(p.y, p.x);
	v1 = go(v1, s / 2.);
	for(pii &p : v1) ans.pb(pii(p.y, p.x));
	// PT 2
	for(pii &p : v2) p = pii(p.x, p.y - s/2.);
	v2 = go(v2, s / 2.);
	for(pii &p : v2) ans.pb(pii(p.x, p.y + s/2.));
	// PT 3
	for(pii &p : v3) p = pii(p.x - s/2., p.y - s/2.);
	v3 = go(v3, s / 2.);
	for(pii &p : v3) ans.pb(pii(p.x + s/2., p.y + s/2.));
	// PT 4
	for(pii &p : v4) p = pii(s/2. - p.y, s - p.x);
	v4 = go(v4, s / 2.);
	for(pii &p : v4) ans.pb(pii(s - p.y, s/2. - p.x));
	return ans;
}

typedef pair<int, int> pi;
char name[100];
int main() {
	int i, j, n, s, x, y;
	scanf("%d %d", &n, &s);
	vector<pii> v;
	map<pi, string> mp;
	for(i = 0; i < n; i++) {
		scanf("%d %d %s", &x, &y, &name);
		v.pb(pii(x, y));
		mp[pi(x, y)] = name;
	}
	v = go(v, s);
	for(pii p : v)
		printf("%s\n", mp[pi(round(p.x), round(p.y))].c_str());
}
