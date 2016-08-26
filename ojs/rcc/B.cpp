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
	int i, n, m, l, r;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		map<int, int> mp; mp[1] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &l, &r);
			if(l + r > n) continue;
			mp[l]++;
			mp[(n-r)+1]--;
		}
		int cur = 0, best = -1;
		int bl;
		for(pii p : mp) {
			cur += p.snd;
			if(cur > best) {
				best = cur;
				bl = p.fst;
			}
		}
		printf("%d %d\n", bl, n - bl);
	}
}
