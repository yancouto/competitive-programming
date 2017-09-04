#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back

void imp() {
	puts("NO");
	exit(0);
}

const int N = 5123;

char adj[N][N];
int p[N], po[N], din[N], dout[N], in[N], out[N];


int main () {
#ifdef ONLINE_JUDGE
	freopen("powersum.in", "r", stdin);
	freopen("powersum.out", "w", stdout);
#endif
	int i, n, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%s", adj[i]);
	for(i = 0; i < n; i++) {
		p[i] = i;
		po[i] = i;
		for(j = 0; j < n; j++)
			din[i] += (adj[j][i] == '1'),
			dout[i] += (adj[i][j] == '1');
	}
	sort(p, p + n, [](int i, int j) { return din[i] < din[j]; });
	for(i = 1; i < n; i++)
		for(j = 0; j < n; j++)
			if(adj[j][p[i - 1]] == '1' && adj[j][p[i]] == '0')
				imp();
	sort(po, po + n, [](int i, int j) { return dout[i] < dout[j]; });
	for(i = 1; i < n; i++)
		for(j = 0; j < n; j++)
			if(adj[po[i - 1]][j] == '1' && adj[po[i]][j] == '0')
				imp();
	for(i = 0; i < n; i++) in[p[i]] = i;
	for(i = 0; i < n; i++) {
		int mn = 1000000000 - 12;
		for(j = 0; j < n; j++)
			if(adj[i][j] == '1')
				mn = min(mn, in[j]);
		out[i] = -mn;
	}
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			assert((adj[i][j] == '1') == (out[i] + in[j] >= 0));
	puts("YES");
	for(i = 0; i < n; i++)
		printf("%d %d\n", out[i], in[i]);
	puts("0");
}
