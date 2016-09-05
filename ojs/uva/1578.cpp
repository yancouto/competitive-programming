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
const int N = 112;
vector<int> adj[N];

int v[N], n;
void go(int s, int i, int pr) {
	if(i == n) {
		if(s != 0) return;
		printf("%d", v[0]);
		for(int i = 1; i < n; i++) printf(" %d", v[i]);
		putchar('\n');
		return;
	}
	for(int x = pr; x <= s; x++) {
		int j;
		for(j = 0; j < i && __gcd(x, v[j]) == 1; j++);
		if(j == i) {
			v[i] = x;
			go(s - x, i + 1, x);
		}
	}
}

int main() {
	int i, j, s;
	for(i = 1; i < N; i++)
		for(j = i; j < N; j++)
			if(__gcd(i, j) == 1)
				adj[i].pb(j);
	for_tests(t, tt) {
		scanf("%d %d", &s, &n);
		printf("Case %d:\n", tt);
		go(s, 0, 1);
	}
}
