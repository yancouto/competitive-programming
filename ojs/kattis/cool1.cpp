#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 203;
int seen[N][N][N];
char s[N];
char g[N][N];
int main() {
	int i, j, n;
	scanf("%d", &n);
	scanf("%s", s);
	int ri, rj;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			scanf(" %c", &g[i][j]);
			if(g[i][j] == 'R') g[i][j] = '.', ri = i, rj = j;
		}
	i = ri, j = rj;
	int cur = 0;
	while(!seen[i][j][cur]) {
		seen[i][j][cur] = 1;
		ri = i; rj = j;
		if(s[cur] == '<' && g[i][j - 1] == '.') rj = j - 1;
		if(s[cur] == '>' && g[i][j + 1] == '.') rj = j + 1;
		if(s[cur] == '^' && g[i - 1][j] == '.') ri = i - 1;
		if(s[cur] == 'v' && g[i + 1][j] == '.') ri = i + 1;
		i = ri; j = rj;
		if(!s[++cur]) cur = 0;
	}
	int trail = 0;
	int ai = i; int aj = j; int acur = cur;
	vector<char> v;
	do {
		ri = i; rj = j;
		if(s[cur] == '<' && g[i][j - 1] == '.') rj = j - 1;
		if(s[cur] == '>' && g[i][j + 1] == '.') rj = j + 1;
		if(s[cur] == '^' && g[i - 1][j] == '.') ri = i - 1;
		if(s[cur] == 'v' && g[i + 1][j] == '.') ri = i + 1;
		if((i != ri) || (j != rj)) v.pb(s[cur]);
		trail += (i != ri) || (j != rj);
		i = ri; j = rj;
		if(!s[++cur]) cur = 0;
	} while(ai != i || aj != j || acur != cur);
	if(trail == 0) { puts("1"); return 0; }
	for(i = 1; i <= trail; i++)
		if(!(trail % i)) {
			for(j = i; j < trail && v[j] == v[j % i]; j++);
			if(j == trail) break;
		}
	printf("%d\n", i);
}
