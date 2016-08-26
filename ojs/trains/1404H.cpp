#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
#define pb push_back
const int N = 41234;
map<char, int> adj[N];
int l[N], f[N], ls, en = 1;

void add(char c, int root) {
	int n = en++;
	l[n] = l[ls] + 1;
	for(; ls != -1 && !adj[ls].count(c); ls = f[ls])
		adj[ls][c] = n;
	if(ls == -1) f[n] = root;
	else if(l[adj[ls][c]] == l[ls] + 1) f[n] = adj[ls][c];
	else {
		int x = en++, q = adj[ls][c];
		l[x] = l[ls] + 1;
		adj[x] = adj[q];
		f[x] = f[q];
		f[q] = f[n] = x;
		for(; ls != -1 && adj[ls].count(c) && adj[ls][c] == q; ls = f[ls])
			adj[ls][c] = x;
	}
	ls = n;
}

int tot, k;
int w[N], d[N], v[N];
string S;
int dfs(int a, int b) {
	if(b && w[b] == k) tot++;
	for(auto e : adj[a])
		if(adj[b].count(e.fst)) {
			S += e.fst;
			dfs(e.snd, adj[b][e.fst]);
			S.pop_back();
		}
}

char s[N], s1[N], s2[N];
int main() {
	freopen("strings.in", "r", stdin);
	freopen("strings.out", "w", stdout);
	int i;
	scanf("%s %s %d", s1, s2, &k);
	strcpy(s, s2);
	f[0] = -1;
	for(i = 0; s[i]; i++) add(s[i], 0);
	for(i = 0; i < en; i++)
		for(auto e : adj[i])
			d[e.snd]++;
	int j = 0;
	v[j++] = 0;
	for(i = 0; i < en; i++)
		for(auto e : adj[v[i]])
			if(--d[e.snd] == 0)
				v[j++] = e.snd;
	i = ls;
	while(i != -1) w[i] = 1, i = f[i];
	for(i = en - 1; i >= 0; i--)
		for(auto e : adj[v[i]])
			w[v[i]] += w[e.snd];
	strcpy(s, s1);
	int r = en++; ls = r; f[r] = -1;
	for(i = 0; s[i]; i++) add(s[i], r);
	dfs(r, 0);
	printf("%d\n", tot);
}
