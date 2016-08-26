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
const int E = 150009, N = 50009;
int es[N], en, to[E], nx[E], M[N << 1];

int qu[N], n, m, dist[N];
int cur[N];
inline bool bfs() {
	int a = 0, b = 0, i;
	for(i = 0; i < n; i++) {
		dist[i] = -1;
		if(M[i] == i)
			qu[b++] = i, dist[i] = 0;
	}
	bool ok = false;
	while(a < b) {
		int v = qu[a++];
		cur[v] = es[v];
		for(int e = es[v]; e != -1; e = nx[e]) {
			if(M[to[e]] == to[e]) ok = true;
			else if(dist[M[to[e]]] == -1) {
				qu[b++] = M[to[e]];
				dist[M[to[e]]] = dist[v] + 1;
			}
		}
	}
	return ok;
}

bool dfs(int u) {
	for(int &e = cur[u]; e != -1; e = nx[e]) {
		if(M[to[e]] == to[e]) {
			M[to[e]] = u;
			M[u] = to[e];
			return true;
		} else if(dist[M[to[e]]] == dist[u] + 1 && dfs(M[to[e]])) {
			M[to[e]] = u;
			M[u] = to[e];
			return true;
		}
	}
	return false;
}

inline int max_match() {
	int m = 0, i;
	while(bfs()) {
		for(i = 0; i < n; i++)
			if(M[i] == i && dfs(i))
				m++;
	}
	return m;
}

inline void add_edge(int a, int b) {
	nx[en] = es[a]; to[en] = b; es[a] = en++;
}

//tryhard
inline int get() {
	char c;
	while(isspace(c = getchar_unlocked()));
	int num = c - '0';
	while(isdigit(c = getchar_unlocked()))
		num = (num << 3) + (num << 1) + c - '0';
	return num;
}

int main() {
	int i, p, a, b;
	n = get(); m = get(); p = get();
	//scanf("%d %d %d", &n, &m, &p);
	for(i = 0; i < n; i++) es[i] = -1;
	for(i = 0; i < n + m; i++) M[i] = i;
	for(i = 0; i < p; i++) {
		a = get() - 1;
		b = get() - 1 + n;
		//scanf("%d %d", &a, &b); a--; b = b - 1 + n;
		add_edge(a, b);
	}
	printf("%d\n", max_match());
	return 0;
}
