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

char s[1123], s2[1123];
int pr[300];
int main() {
	int i, j, n, m, c;
	scanf("%d %d", &n, &m);
	scanf("%s", s);
	for(i = 0; i < 256; i++)
		pr[i] = INT_MAX;
	for(i = 0; i < m; i++) {
		scanf("%*d %d", &c);
		scanf("%s", s2);
		for(j = 0; s2[j]; j++)
			pr[s2[j]] = min(pr[s2[j]], c);
	}
	int tot = 0;
	for(i = 0; i < n; i++) {
		if(pr[s[i]] == INT_MAX) { puts("-1"); return 0; }
		tot += pr[s[i]];
	}
	printf("%d\n", tot);
}
