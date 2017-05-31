#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 31623;
int comp[N], a[N];

int main() {
	int i, n, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	vector<int> ps;
	for(i = 2; i < N; i++)
		if(!comp[i]) {
			ps.pb(i);
			for(j = i + i; j < N; j += i)
				comp[j] = 1;
		}
	map<int, int> f;
	for(i = 0; i < n; i++) {
		for(int p : ps) {
			if(a[i] == 1) break;
			while(!(a[i] % p)) {
				f[p]++;
				a[i] /= p;
			}
		}
		if(a[i] > 1) f[a[i]]++;
	}
	f.erase(1);
	bool all = true;
	for(pii p : f)
		if(p.snd % n)
			all = false;
	if(all) puts("justdoit");
	else {
		ll val = 1;
		for(pii p : f) {
			while(p.snd % (n + 1)) {
				p.snd++;
				val = mod(val * ll(p.fst));
			}
		}
		printf("%d\n", (int) val);
	}
}
