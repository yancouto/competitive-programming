#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int S[1000], sz[1000];
char s[1000];
int g[30][30];

int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

int main() {
	int i, j, n, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i <= 200; i++) S[i] = i, sz[i] = 1;
	for(i = 0; i <= n; i++)
		for(j = 0; j <= m; j++) {
			scanf("%d", &g[i][j]);
			if(!i || !j) continue;
			if(g[i][j] == max(g[i][j-1], g[i-1][j])) continue;
			join(i, j + 100);
		}
	int l = 0;
	for(i = 1; i <= n; i++)
		if(find(i) == i)
			s[i] = 'a' + (l++);
	for(i = 1; i <= n; i++)
		putchar(s[find(i)]);
	putchar('\n');
	for(i = 1; i <= m; i++)
		if(s[find(i + 100)]) putchar(s[find(i + 100)]);
		else putchar('a' + l);
	putchar('\n');
}
