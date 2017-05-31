#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

int S[11234], sz[11234];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

inline void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

char g[10][111234];

int main() {
	int i, j, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < 2 * n; i++) S[i] = i, sz[i] = 1;
		int any = -1;
		for(i = 0; i < 2; i++)
			for(j = 0; j < n; j++) {
				scanf(" %c", &g[i][j]);
				if(g[i][j] == '#' && (any == -1 || (any % n) < j)) any = i * n + j;
				if(g[i][j] == '#' && i && g[i - 1][j] == '#')
					join(i * n + j, (i - 1) * n + j);
				if(g[i][j] == '#' && j && g[i][j - 1] == '#')
					join(i * n + j, i * n + j - 1);
			}
		bool bad = false;
		for(i = 0; i < 2; i++)
			for(j = 0; j < n; j++)
				if(g[i][j] == '#' && find(i * n + j) != find(any))
					bad = true;
		bool s = any / n;
		bool has = false;
		for(i = (any % n); !bad && i >= 0; i--) {
			if(g[s][i] != '#' && g[!s][i] != '#') break;
			if(g[s][i] != '#' && g[!s][i] == '#') {
				if(has) bad = true;
				else s = !s;
			}
			if(g[!s][i] == '#') {
				s = !s;
			} else {
				has = true;
			}
		}
		if(bad) puts("no");
		else puts("yes");
	}
}
