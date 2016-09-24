#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 40;
double d[N][N];
char s[N][10000];
char a[10000], b[10000];
map<string, int> mp;

int main() {
	int i, j, k, n, t = 0, m; double x;
	while(scanf("%d", &n) != EOF && n) {
		printf("Case %d: ", ++t);
		mp.clear();
		for(i = 0; i < n; i++) {
			scanf("%s", s[i]);
			mp[s[i]] = i;
		}
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				d[i][j] = 0;
		for(i = 0; i < n; i++) d[i][i] = 1;
		scanf("%d", &m);
		for(i = 0; i < m; i++) {
			scanf("%s %lf %s", a, &x, b);
			d[mp[a]][mp[b]] = x;
		}
		for(k = 0; k < n; k++)
			for(i = 0; i < n; i++)
				for(j = 0; j < n; j++)
					d[i][j] = max(d[i][j], d[i][k] * d[k][j]);
		for(i = 0; i < n && d[i][i] <= 1; i++);
		if(i < n) puts("Yes");
		else puts("No");
	}
}
