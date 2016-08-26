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
int adj[52][52];
ll w[52];

int main() {
	int i, j, b; ll m;
	for_tests(t, tt) {
		scanf("%d %lld", &b, &m);
		ll om = m;
		memset(adj, 0, sizeof adj);
		memset(w, 0, sizeof w);
		w[0] = 1;
		for(i = 1; i < b - 1; i++) {
			for(j = 0; j < i; j++)
				adj[j][i] = 1, w[i] += w[j];
			assert(w[i] == (1ll << (i - 1)));
		}
		for(j = b - 2; j >= 0; j--)
			if(w[j] <= m)
				m -= w[j], adj[j][b - 1] = 1;
		printf("Case #%d: ", tt);
		if(m > 0) { puts("IMPOSSIBLE"); continue; }
		puts("POSSIBLE");
		for(i = 0; i < b; i++) {
			for(j = 0; j < b; j++)
				putchar('0' + adj[i][j]);
			putchar('\n');
		}
		for(i = 0; i < b; i++) w[i] = 0;
		w[0] = 1;
		for(i = 1; i < b; i++)
			for(j = 0; j < i; j++)
				if(adj[j][i])
					w[i] += w[j];
		assert(w[b - 1] == om);
	}
}
