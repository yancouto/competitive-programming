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

vector<int> adj[1009];
char str[1009][25];
map<string, int> mp;
int get(char *s) {
	string st(s);
	if(!mp.count(st)) { mp[st] = mp.size() - 1; strcpy(str[mp[st]], s); }
	return mp[st];
}
int dist[1009];
char s1[100], s2[100];
int main() {
	int i, n, g;
	scanf("%d %d", &n, &g);
	get("Rerisson");
	for(i = 0; i < n; i++) {
		scanf("%s %s", s1, s2);
		int a = get(s1), b = get(s2);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	memset(dist, -1, sizeof dist);
	queue<int> q;
	q.push(0); dist[0] = 0;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(int y : adj[x])
			if(dist[y] == -1) {
				dist[y] = dist[x] + 1;
				q.push(y);
			}
	}
	set<string> st;
	for(i = 1; i < mp.size(); i++) {
		if(dist[i] <= g && dist[i] != -1)
			st.insert(str[i]);
	}
	printf("%d\n", st.size());
	for(string ss : st)
		printf("%s\n", ss.c_str());
}
