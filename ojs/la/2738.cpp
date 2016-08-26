// WA???
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
char str[20000]; int g[200], n;
bool ok() {
	int i = 0;
	while(i < n && g[i] == 0) i++;
	while(i < n && g[i]) i++;
	while(i < n && g[i] == 0) i++;
	return i == n;
}
void fl(int i) { g[i] = !g[i]; }

int mx = INT_MAX;
void solve(int fi, int mv) {
	if(mv >= mx) return;
	if(ok()) mx = mv;
	if(mv == 9) return;
	if(fi > 0) { solve(fi - 1, mv + 1); }
	if(fi < n) { solve(fi + 1, mv + 1); }
	if(fi > 1) { fl(fi); solve(fi - 2, mv + 1); fl(fi); }
	if(fi < n - 1) { fl(fi + 1); solve(fi + 2, mv + 1); fl(fi + 1); }
}

int main() {
	int t = 0;
	while(true) {
		int i, j = 0, f;
		scanf("%s", str);
		if(str[0] == '-') return 0;
		for(i = 0; str[i]; i++) {
			if(str[i] == 'F') { f = i; continue; }
			g[j++] = (str[i] == 'B');
		}
		n = j;
		mx = INT_MAX; solve(f, 0);
		if(mx == INT_MAX) printf("%d. -1\n", ++t);
		else printf("%d. %d\n", ++t, mx);
	}
}
