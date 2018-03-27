#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 40123;
const int K = 60;

bool adj[K][K];
int visi[K];
char str[10];
int n;

int conv (char * c) {
	if (c[0] == '0') return -1;
	return 2*(c[0]-'A') + (c[1] == '+');
}

bool dfs (int u) {
	if (visi[u] == 2) return 0;
	if (visi[u] == 1) return 1;
	visi[u] = 1;
	for (int v = 0; v < K; v++) if (adj[u][v])
		if (dfs(v)) return 1;
	visi[u] = 2;
	return 0;
}

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf(" %s", str);
		for (int a = 0; a < 4; a++) if (conv(str+a+a) != -1)
			for (int b = 0; b < 4; b++) if (a != b && conv(str+b+b) != -1)
				adj[conv(str+a+a)][conv(str+b+b)^1] = 1;
	}

	for (int i = 0; i < K; i++) {
		if (dfs(i)) {
			printf("unbounded\n");
			exit(0);
		}
	}
	printf("bounded\n");
}
