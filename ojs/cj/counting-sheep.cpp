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
const int N = 10000009;
int ans[N], g[N];

int get(int i) {
	if(i == 0) return 1;
	int k = 0;
	while(i) k |= (1 << (i % 10)), i /= 10;
	return k;
}
int all = (1 << 10) - 1;

int main() {
	int i, j, n;
	for(i = 0; i < N; i++)
		g[i] = get(i);
	for(i = 1; i < N; i++) {
		int q = 0;
		for(j = i; j < N; j += i) {
			q |= g[j];
			if(q == all) { ans[i] = j; break; }
		}
		if(i <= 1000000) assert(q == all);
	}
	for_tests(t, tt) {
		scanf("%d", &n);
		printf("Case #%d: ", tt);
		if(n == 0) puts("INSOMNIA");
		else printf("%d\n", ans[n]);
	}

}
