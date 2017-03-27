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

const int N = 1123;
int n, m, ka, kb;
string A[N], B[N];
map<string, set<string>> adj, bdj;
set<string> ga, gb, ma, mb;

char s[122];
string get() {
	scanf("%s", s);
	return string(s);
}

int main() {
	int i, j;
	string a, b;
	scanf("%d %d %d %d", &n, &m, &ka, &kb);
	for(i = 0; i < n; i++) A[i] = get();
	for(i = 0; i < m; i++) {
		a = get(); b = get();
		adj[a].insert(b);
		adj[b].insert(a);
	}
	for(i = 0; i < ka; i++)
		if(n - int(adj[A[i]].size()) - 1 >= kb - 1)
			ga.insert(A[i]);
	for(i = 0; i < n; i++) B[i] = get();
	for(i = 0; i < m; i++) {
		a = get(); b = get();
		bdj[a].insert(b);
		bdj[b].insert(a);
	}
	for(i = 0; i < kb; i++)
		if(int(bdj[B[i]].size()) >= ka - 1)
			gb.insert(B[i]);
	for(j = 0; j < 10 && !ga.empty() && !gb.empty(); j++) {
		if(j & 1) {
			printf("B %s\n", gb.begin()->c_str()); fflush(stdout);
			gb.erase(gb.begin());
			a = get();
			if(ga.count(a)) { printf("C Yes\n"); fflush(stdout); return 0; }
			for(auto it = ga.begin(); it != ga.end(); ) {
				if(adj[a].count(*it)) it = ga.erase(it);
				else ++it;
			}
		} else {
			printf("A %s\n", ga.begin()->c_str()); fflush(stdout);
			ga.erase(ga.begin());
			b = get();
			if(gb.count(b)) { printf("C Yes\n"); fflush(stdout); return 0; }
			for(auto it = gb.begin(); it != gb.end(); ) {
				if(!bdj[b].count(*it)) it = gb.erase(it);
				else ++it;
			}
		}
	}
	printf("C No\n"); fflush(stdout);
	return 0;
}
