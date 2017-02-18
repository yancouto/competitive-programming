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

const int N = 512345;
int a[N];
vector<int> adj[N];

struct cmp {
	bool operator() (int i, int j) {
		if(a[i] != a[j]) return a[i] > a[j];
		return i < j;
	}
};

int main() {
	int i, n, u, v;
	for_tests(t, tt) {
		scanf("%d", &n);
		set<int, cmp> s;
		for(i = 0; i < n; i++) scanf("%d", &a[i]), adj[i].clear(), s.insert(i);
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &u, &v); u--; v--;
			adj[u].pb(v); adj[v].pb(u);
		}
		for(i = 0; i < n; i++) {
			s.erase(i);
			for(int x : adj[i]) s.erase(x);
			printf("%d ", *s.begin() + 1);
			s.insert(i);
			for(int x : adj[i]) s.insert(x);
		}
		putchar('\n');
	}
}
