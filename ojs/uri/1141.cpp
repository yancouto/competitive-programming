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
const int MAX = 1000100;
int tr[MAX][26];
int mt[MAX], pr[MAX];
int st[MAX];
char s[10003][1003];
int p[10009], sz[10009], memo[10009];

int main() {
	int i, j, k, m;
	while(scanf("%d", &m) == 1 && m) {
		for(i = 0; i < m; i++) {
			scanf("%s", s[i]);
			sz[i] = strlen(s[i]);
			p[i] = i;
		}
		sort(p, p + m, [](int i, int j) { return sz[i] < sz[j]; });
		memset(tr[0], 0, sizeof(int)*26);
		int tn = 0;
		for(i = 0; i < m; i++) {
			char *c = s[i];
			int v = 0;
			for(j = 0; c[j]; j++) {
				if(!tr[v][c[j]-'a']) {
					tr[v][c[j]-'a'] = ++tn;
					memset(tr[tn], 0, sizeof(int)*26);
					mt[tn] = 0;
				}
				v = tr[v][c[j]-'a'];
			}
			mt[v] = 1;
			st[v] = i;
		}
		queue<int> q;
		for(i = 0; i < 26; i++)
			if(tr[0][i])
				q.push(tr[0][i]), pr[tr[0][i]] = 0;
		while(!q.empty()) {
			int x = q.front(); q.pop();
			for(i = 0; i < 26; i++) {
				if(!tr[x][i]) continue;
				int &p = pr[tr[x][i]];
				p = pr[x];
				while(p && !tr[p][i]) p = pr[p];
				p = tr[p][i];
				if(mt[p]) mt[tr[x][i]] |= 2;
				q.push(tr[x][i]);
			}
		}
		int mx = 0;
		for(i = 0; i < m; i++) {
			k = p[i];
			char *c = s[k]; int n = sz[k];
			int v = 0;
			memo[k] = 1;
			for(j = 0; j < n; j++) {
				v = tr[v][c[j]-'a'];
				int x = v;
				if(j == n - 1) x = pr[x];
				while(mt[x]) {
					if(mt[x] & 1) memo[k] = max(memo[k], 1 + memo[st[x]]);
					x = pr[x];
				}
			}
			mx = max(mx, memo[k]);
		}
		printf("%d\n", mx);
	}
}
