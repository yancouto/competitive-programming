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
const int MAX = 1509;
int tr[MAX][256], ba[MAX], pr[MAX];
char em[100], ln[1000];

int main() {
	int i, j, n, m;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		memset(tr, -1, sizeof tr);
		memset(ba, 0, sizeof ba);
		ba[0] = 0;
		int tn = 0;
		for(i = 0; i < n; i++) {
			scanf("%s", em);
			int v = 0;
			for(j = 0; em[j]; j++) {
				if(tr[v][em[j]] == -1)
					tr[v][em[j]] = ++tn;
				v = tr[v][em[j]];
			}
			ba[v] = 1;
		}
		queue<int> q;
		for(i = 0; i < 256; i++)
			if(tr[0][i] != -1)
				q.push(tr[0][i]), pr[tr[0][i]] = 0;
		while(!q.empty()) {
			int x = q.front(); q.pop();
			for(i = 0; i < 256; i++) {
				if(tr[x][i] == -1) continue;
				int &p = pr[tr[x][i]];
				p = pr[x];
				while(p && tr[p][i] == -1)
					p = pr[p];
				if(tr[p][i] != -1)
					p = tr[p][i];
				if(ba[p]) ba[tr[x][i]] = 1;
				q.push(tr[x][i]);
			}
		}
		fgets(ln, sizeof ln, stdin);
		int tot = 0;
		for(i = 0; i < m; i++) {
			fgets(ln, sizeof ln, stdin);
			int v = 0;
			for(j = 0; ln[j]; j++) {
				while(v && tr[v][ln[j]] == -1)
					v = pr[v];
				if(tr[v][ln[j]] != -1)
					v = tr[v][ln[j]];
				if(ba[v]) tot++, v = 0;
			}
		}
		printf("%d\n", tot);
	}
}
