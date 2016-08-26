#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define u first
#define v second
pii e[100009];
int s[100009], v[100009];
int S[100009], sz[100009];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}
void join(int a, int b) {
	a = find(a); b = find(b);
	if(a == b) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}
int main() {
	int i, n, m, q, x;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++)
		scanf("%d %d", &e[i].u, &e[i].v);
	for(i = 0; i < n; i++)
		S[i] = i, sz[i] = 1;
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d", &x);
		v[i] = --x;
		s[x] = 1;
	}
	reverse(v, v + q);
	int c = n;
	for(i = 0; i < m; i++) {
		if(s[i]) continue;
		if(find(e[i].u) != find(e[i].v))
			c--;
		join(e[i].u, e[i].v);
	}
	int st[100009], sn = 0;
	st[sn++] = c;
	for(i = 0; i < q - 1; i++) {
		if(find(e[v[i]].u) != find(e[v[i]].v))
			c--;
		join(e[v[i]].u, e[v[i]].v);
		st[sn++] = c;
	}
	printf("%d", st[--sn]);
	while(sn)
		printf(" %d", st[--sn]);
	putchar('\n');
}
