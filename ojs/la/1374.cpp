#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, string> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

char ln[100009], str[300];
inline void gl() { return; fgets(ln, sizeof ln, stdin); }
int s[1009][1009];
vector<int> adj[1009];
map<string, int> mp;
char inv[1009][100];
int get() {
	string st(str);
	if(!mp.count(st)) { mp[st] = mp.size() - 1; strcpy(inv[mp.size()-1], str); }
	return mp[st];
}

int solve(int i, int d) {
	if(d == 0) return 1;
	if(s[i][d] != -1) return s[i][d];
	s[i][d] = 0;
	for(int v : adj[i])
		s[i][d] += solve(v, d - 1);
	return s[i][d];
}

pii v[1009];
int main() {
	int i, n, d, j, t, k;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; tt++) {
		if(tt > 1) putchar('\n');
		mp.clear();
		scanf("%d %d", &n, &d);
		memset(s, -1, sizeof s);
		for(i = 0; i < 1009; i++) adj[i].clear();
		for(i = 0; i < n; i++) {
			scanf("%s %d", str, &k); int f = get();
			while(k--) {
				scanf("%s", str);
				adj[f].pb(get());
			}
		}
		for(i = 0; i < mp.size(); i++)
			v[i] = pii(-solve(i, d), string(inv[i]));
		sort(v, v + mp.size());
		printf("Tree %d:\n", tt);
		for(i = 0; i < 3 && i < mp.size() && v[i].fst; i++)
			printf("%s %d\n", v[i].snd.c_str(), -v[i].fst);
		while(i > 0 && i < mp.size() && v[i].fst && v[i].fst == v[i-1].fst)
			printf("%s %d\n", v[i].snd.c_str(), -v[i].fst), i++;
	}
	return 0;
}
