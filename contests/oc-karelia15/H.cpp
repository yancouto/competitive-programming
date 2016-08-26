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
const int N = 512345;


int n;
int seen[N], tempo;
int he[N], nx[N], cp[N], fl[N], done[N], val[N], to[N], en;
bool dfs0(int u, int t) {
	if(u == t) return true;
	if(seen[u] == tempo) return false;
	seen[u] = tempo;
	for(int e = he[u]; e != -1; e = nx[e])
		if(cp[e] - fl[e] && dfs0(to[e], t)) {
			fl[e]++;
			fl[e ^ 1]--;
			return true;
		}
	return false;
}

void add_edge(int a, int b, int c) {
	cp[en] = c; to[en] = b; nx[en] = he[a]; he[a] = en++;
	cp[en] = 0; to[en] = a; nx[en] = he[b]; he[b] = en++;
}

bool dfs(int u, int mn) {
	if(seen[u] == tempo) return false;
	seen[u] = tempo;
	if(u < n && val[u] > mn) { val[u]--; return true; }
	for(int e = he[u]; e != -1; e = nx[e]) {
		if(to[e] >= N - 2) continue;
		if(cp[e] - fl[e] && dfs(to[e], mn)) {
			fl[e]++;
			fl[e ^ 1]--;
			return true;
		}
	}
	return false;
}

int main() {
	int i, j, m; char c;
	memset(he, -1, sizeof he);
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			scanf(" %c", &c);
			if(c == '1') add_edge(i, j + n, 1);
		}
	for(i = 0; i < n; i++)
		add_edge(N - 1, i, 10000);
	for(j = 0; j < m; j++)
		add_edge(j + n, N - 2, 1);
	tempo++;
	while(dfs0(N - 1, N - 2)) tempo++;
	for(i = 0; i < n; i++)
		for(int e = he[i]; e != -1; e = nx[e])
			if(to[e] == N - 1)
				val[i] = fl[e ^ 1];
	while(true) {
		int j = -1;
		for(i = 0; i < n; i++)
			if(!done[i] && (j == -1 || val[i] < val[j]))
				j = i;
		if(j == -1) break;
		tempo++;
		if(dfs(j, val[j] + 1)) val[j]++;
		else done[j] = true;
	}
	for(i = 0; i < n; i++) {
		printf("%d", val[i]);
		//for(int e = he[i]; e != -1; e = nx[e])
		//	printf("fl[%d] to %d = %d\n", e, to[e], fl[e]);
		for(int e = he[i]; e != -1; e = nx[e])
			if(to[e] != N - 1 && fl[e] > 0)
				printf(" %d", to[e] - n + 1);
		putchar('\n');
	}
}
