#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, bool> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int main() {
	int n, f, b, i, ff, bb;
	for_tests(t, tt) {
		scanf("%d %d %d", &n, &f, &b);
		deque<pii> deliver;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &ff, &bb);
			if(bb) deliver.pb(pii(f - ff, true));
			else deliver.pb(pii(ff, false));
		}
		sort(deliver.begin(), deliver.end());
		int last_d;
		while(!deliver.empty()) {
			pii p = deliver.front();
			deliver.pop_front();
			if(p.snd) {
				last_d = p.fst;
				deliver.pb(pii(p.fst + f, false));
			} else if(b) {
				b--;
				deliver.pb(pii(p.fst + f, true));
			}
		}
		printf("%d\n", last_d);
	}
}
