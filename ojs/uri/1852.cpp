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
map<string, int> mp;
int n;
int get(char *str) {
	string s(str);
	return mp[s];
}
vector<int> adj[500];
int M[500];

bool w_unstable(int u, int v) {
	if(M[v] == -1) return true;
	int a = (search_n(adj[v].begin(), adj[v].end(), 1, u) - adj[v].begin());
	assert(u == adj[v][a]);
	if(M[v] > a) return true;
	return false;
}
string inv[500];


int main() {
	int i, j;
	char str[20];
	while(scanf("%d", &n) != EOF) {
		mp.clear();
		scanf(" %s", str);
		string s(str);
		mp[s] = 0; inv[0] = s; adj[0].clear();
		for(i = 0; i < n; i++) {
			scanf(" %s", str);
			s = str;
			mp[s] = n + i;
			inv[n + i] = s;
			adj[0].pb(n + i);
		}
		for(i = 1; i < n; i++) {
			scanf(" %s", str);
			s = str;
			mp[s] = i; inv[i] = s;
			for(j = 0; j < n; j++) {
				scanf(" %s", str);
				adj[i].pb(get(str));
			}
		}
		for(i = 0; i < n; i++) {
			scanf(" %s", str);
			int w = get(str);
			for(j = 0; j < n; j++) {
				scanf(" %s", str);
				adj[w].pb(get(str));
			}
		}
		vector<int> S;
		for(i = 0; i < n; i++) { S.pb(i); }
		memset(M, -1, sizeof M);
		while(!S.empty()) {
			int u = S.back(); S.pop_back();
			for(i = 0; i < adj[u].size(); i++) {
				int v = adj[u][i];
				if(!w_unstable(u, v)) continue;
				if(M[v] != -1) {
					S.pb(adj[v][M[v]]);
					M[adj[v][M[v]]] = -1;
					M[v] = -1;
				}
				M[u] = i; M[v] = search_n(adj[v].begin(), adj[v].end(), 1, u) - adj[v].begin();
				break;
			}
		}
		for(i = 0; i < n; i++) {
			printf("%s %s\n", inv[i].c_str(), inv[adj[i][M[i]]].c_str());
		}

	}
}
