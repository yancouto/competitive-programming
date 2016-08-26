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

int main() {
	int nx, ny, i; double w, x;
	while(true) {
		scanf("%d %d %lf", &nx, &ny, &w);
		if(nx == 0) return 0;
		map<double, int> mp;
		mp[0] = mp[75] = 0;
		for(i = 0; i < nx; i++) {
			scanf("%lf", &x);
			mp[x - w/2]++;
			mp[x + w/2]--;
		}
		double last = -1; int tot = 0;
		bool bad = false;
		for(auto &e : mp) {
			if(last != -1 && tot == 0) bad = true;
			last = e.fst;
			tot += e.snd;
		}
		mp.clear();
		mp[0] = mp[100] = 0;
		for(i = 0; i < ny; i++) {
			scanf("%lf", &x);
			mp[x - w/2]++;
			mp[x + w/2]--;
		}
		last = -1; tot = 0;
		for(auto &e : mp) {
			if(last != -1 && tot == 0) bad = true;
			last = e.fst;
			tot += e.snd;
		}
		if(bad) puts("NO");
		else puts("YES");
	}
}
