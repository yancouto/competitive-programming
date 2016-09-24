#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const int N = 1123;
const int p6 = 1000000;

vector<pii> adj[N];
int D[N][N], seen[N], p[N];

vector<int> all;
void find(int i) {
	if(seen[i]) return;
	all.pb(i);
	seen[i] = 1;
	for(pii e : adj[i])
		find(e.fst);
}

int S[N], sz[N];
void go(int a, int b, int right) {
	//printf("p[%d] = %d\n", b, p[S[b]]);
	for(pii e : adj[b]) {
		int c = e.fst;
		if(seen[S[c]] == 2) continue;
		int p0 = p[S[b]] - (p6 - D[b][c]),
		    p1 = p[S[b]] + (p6 - D[b][c]),
		    q0 = p[S[a]] - (p6 - D[a][c]),
		    q1 = p[S[a]] + (p6 - D[a][c]);
		if(D[a][c] == 0 && right) p[S[c]] = p1;
		else if(D[a][c] == 0) p[S[c]] = p0;
		else if(p0 == q0) p[S[c]] = p0;
		else if(p0 == q1) p[S[c]] = p0;
		else if(p1 == q0) p[S[c]] = p1;
		else if(p1 == q1) p[S[c]] = p1;
		else {
			puts("No");
			exit(0);
		}
		seen[S[c]] = 2;
		//printf("%d->%d->%d\n", a, b, c);
		if(p[S[c]] < p[S[b]]) go(b, c, 0);
		else if(p[S[b]] < p[S[c]]) go(b, c, 1);
		else go(a, c, right);
	}
}

int f(int i) {
	if(S[S[i]] != S[i]) S[i] = f(S[i]);
	return S[i];
}

int n;
void check(int a, int b) {
	if((a = f(a)) == (b = f(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	for(int i = 0; i < n; i++)
		if(D[a][i] != D[b][i]) {
			puts("No");
			exit(0);
		}
}

int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			scanf("%d", &D[i][j]);
			if(i != j && D[i][j] > 0) adj[i].pb(pii(j, D[i][j]));
		}
	for(i = 0; i < n; i++) S[i] = i, sz[i] = 1;
	for(i = 0; i < n; i++)
		if(!seen[i]) {
			//puts("========");
			if(adj[i].empty()) continue;
			all.clear();
			find(i);
			int a = -1, b = -1;
			bool zero = false;
			for(int na = 0; na < all.size(); na++)
				for(int nb = 0; nb < all.size(); nb++) {
					if(D[all[na]][all[nb]] == p6) { check(all[na], all[nb]); continue; }
					if(D[all[na]][all[nb]] == 0) zero = true;
					if(D[all[na]][all[nb]] == 0) continue;
					a = all[na]; b = all[nb];
				}
			for(int na = 0; na < all.size(); na++) f(all[na]);
			if(a == -1 && zero) {
				puts("No");
				return 0;
			}
			if(a == -1) continue;
			//printf("(%d -> %d) = %d\n", a, b, D[a][b]);
			p[S[a]] = 0;
			p[S[b]] = p6 - D[a][b];
			seen[S[a]] = seen[S[b]] = 2;
			go(a, b, 1);
			go(b, a, 0);
			for(a = 0; a < all.size(); a++)
				for(b = 0; b < all.size(); b++) {
					int in = abs(p[S[all[a]]] - p[S[all[b]]]);
					if(in > p6) in = 0;
					else in = p6 - in;
					//printf("[%d][%d] got %d vs %d\n", all[a], all[b], in, D[all[a]][all[b]]);
					if(D[all[a]][all[b]] != in) {
						puts("No");
						return 0;
					}
				}
		}
	puts("Yes");
}
