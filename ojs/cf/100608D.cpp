#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
char s[100];
int adj[70][26], ct[256];

void print(int n, int fim) {
	printf("%d\n1\n%d\n", n, fim);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < 26; j++)
			printf("%d%c", adj[i][j]? adj[i][j] : n, " \n"[j == 25]);
}

void go() {
	int i, j;
	char c;
	puts("YES");
	memset(adj, 0, sizeof adj);
	if(s[0] == s[1]) {
		adj[1][s[0] - 'a'] = 1;
		for(i = 0; i < n && s[i] == s[0]; i++);
		for(j = 0; i + j < n; j++)
			adj[j + 1][s[i + j] - 'a'] = j + 2;
		print(j + 2, j + 1);
		c = s[0];
	} else {
		adj[1][s[0] - 'a'] = 2;
		adj[2][s[1] - 'a'] = 1;
		for(i = 0; i < n && s[i] == s[i & 1]; i++);
		c = s[i & 1];
		if(i == n) print(3, (n & 1) + 1);
		else {
			adj[(i & 1) + 1][s[i] - 'a'] = 3;
			for(j = 1; i + j < n; j++)
				adj[j + 2][s[i + j] - 'a'] = j + 3;
			print(j + 3, j + 2);
		}
	}
	int ct = 0;
	for(int i = 0; i < n; i++) ct += (s[i] == c);
	memset(adj, 0, sizeof adj);
	for(int i = 1; i <= ct + 1; i++) {
		for(int j = 0; j < 26; j++)
			adj[i][j] = i;
		adj[i][c - 'a'] = i + 1;
	}
	print(ct + 2, ct + 1);
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("decomposable.in", "r", stdin);
	freopen("decomposable.out", "w", stdout);
#endif
	int i, j;
	while(scanf("%s", s) != EOF) {
		n = strlen(s);
		for(i = 'a'; i <= 'z'; i++) ct[i] = -1;
		for(i = 1; i < n && s[i] == s[i - 1]; i++);
		if(i == n) { puts("NO"); continue; }
		go();
		if(!s[i]) puts("NO");
	}
}
