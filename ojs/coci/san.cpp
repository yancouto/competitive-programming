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

int pr10[1000003];
int rev[1000003];
ll acc[1000003];
vector<int> adj[1000009];
ll dfs(int u) {
	if(acc[u]) return acc[u];
	acc[u] = 1;
	for(int v : adj[u])
		acc[u] += dfs(v);
	return acc[u];
}

int main() {
	int i, a, b;
	for(i = 1; i <= 1000000; i *= 10)
		pr10[i] = i;
	for(i = 1; i <= 1000000; i++) {
		if(!pr10[i]) pr10[i] = pr10[i - 1];
		rev[i] = pr10[i] * (i % 10) + rev[i / 10];
		if(i + rev[i] <= 1000000)
			adj[i + rev[i]].pb(i);
		dfs(i);
	}
	for(i = 1; i <= 1000000; i++)
		acc[i] += acc[i - 1];
	for_tests(t, tt) {
		scanf("%d %d", &a, &b);
		printf("%lld\n", acc[b] - acc[a - 1]);
	}
}
