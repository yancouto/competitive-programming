#include <bits/stdc++.h>
using namespace std;
#define i first
#define j second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 312;

pii q[N * N];
vector<int> v[N];
int a[N][N];

inline int dif(int a, int b, int c, int d) { return (a - c) * (a - c) + (b - d) * (b - d); }

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &a[i][j]), q[a[i][j]] = pii(i, j);
	for(i = 1; i <= n * n; i++) {
		int b = 0;
		while(v[b].size() == n) b++;
		for(j = 1; j < n; j++)
			if(v[j].size() < n && dif(q[i].i, q[i].j, j, v[j].size()) < dif(q[i].i, q[i].j, b, v[b].size()))
				b = j;
		v[b].pb(i);
	}
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++)
			printf("%d ", v[i][j]);
		putchar('\n');
	}
}
