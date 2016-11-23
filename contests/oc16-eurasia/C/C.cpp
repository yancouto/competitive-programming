#include <bits/stdc++.h>
using namespace std;
#define val first
#define i second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 112345;

vector<int> st[N], ig[N], pig[N], pst[N];
int seen[N], low[N], d[N], sta[N], sn, mn[N], mx[N], comp[N], deg[N], tempo;

void imp() {
	puts("NO");
	exit(0);
}

void dfs(int a) {
	seen[a] = true;
	sta[sn++] = a;
	d[a] = low[a] = tempo++;
	for(int b : ig[a])
		if(seen[b]) low[a] = min(low[a], d[b]);
		else {
			dfs(b);
			low[a] = min(low[a], low[b]);
		}
	if(low[a] == d[a]) {
		int x = -1;
		while(x != a) {
			x = sta[--sn];
			d[x] = INT_MAX;
			comp[x] = a;
			//printf("comp[%d] = %d\n", x, a);
			mn[a] = max(mn[a], mn[x]);
			mx[a] = min(mx[a], mx[x]);
		}
	}
}

void dfs2(int a) {
	seen[a] = 1;
	for(int b : pst[a])
		if(seen[b] == 1) imp();
		else if(seen[b] != 2) dfs2(b);
	for(int b : pig[a])
		if(seen[b] == 1) imp();
		else if(seen[b] != 2) dfs2(b);
	seen[a] = 2;
}

int p[N], t[N], va[N], ia[N], vb[N], ib[N], val[N], done[N], cant[N];
int main() {
	int i, j, n, k;
	scanf("%d %d", &n, &k);
	for(i = 1; i <= k; i++) mn[i] = -2e9, mx[i] = 2e9, cant[i] = mn[i]-2; // com igualdade
	for(i = 1; i <= n; i++) {
		scanf("%d %d %d %d %d", &t[i], &va[i], &ia[i], &vb[i], &ib[i]);
		if(va[i] == 1 && vb[i] == 1) { if(!(ia[i] <= ib[i] - t[i])) imp(); }
		else if(va[i] == 1 && vb[i] == 0) mn[ib[i]] = max(mn[ib[i]], ia[i] + t[i]);
		else if(va[i] == 0 && vb[i] == 1) mx[ia[i]] = min(mx[ia[i]], ib[i] - t[i]);
		else if(t[i]) st[ib[i]].pb(ia[i]);
		else ig[ib[i]].pb(ia[i]);
	}
	//for(i = 1; i <= k; i++)
	//	printf("x%d [%d, %d]\n", i, mn[i], mx[i]);
	for(i = 1; i <= k; i++)
		if(!seen[i])
			dfs(i);
	for(i = 1; i <= k; i++) {
		for(int x : ig[i])
			if(comp[i] != comp[x])
				pig[comp[x]].pb(comp[i]), deg[comp[i]]++;
		for(int x : st[i])
			if(comp[i] == comp[x]) imp();
			else pst[comp[x]].pb(comp[i]), deg[comp[i]]++;
		seen[i] = 0;
	}
	//puts("dfs2 ready");
	for(i = 1; i <= k; i++)
		if(comp[i] == i && !seen[i])
			dfs2(i);
	int pn = 0;
	for(i = 1; i <= k; i++)
		if(comp[i] == i)
			p[pn++] = i;
	sort(p, p + pn, [](int i, int j) { return mn[i] < mn[j]; });
	//puts("dfs2 done");
	//for(i = 1; i <= k; i++) printf("deg(%d) = %d\n", i, deg[i]);
	for(j = 0; j < pn; j++) {
		i = p[j];
		//printf("processing x%d [%d, %d]\n", i, mn[i], mx[i]);
		//for(int x : pig[i]) printf("x%d <= x%d\n", i, x);
		//for(int x : pst[i]) printf("x%d < x%d\n", i, x);
		done[i] = true;
		priority_queue<pii> proc;
		if(deg[i] == 0) proc.push(pii(mn[i], i));
		while(!proc.empty()) {
			pii p = proc.top(); proc.pop();
			//printf("x[%d] = %d\n", p.i, p.val);
			val[p.i] = p.val;
			for(int x : pig[p.i]) {
				mn[x] = max(mn[x], p.val);
				if(--deg[x] == 0 && done[x]) proc.push(pii(mn[x], x));
			}
			for(int x : pst[p.i]) {
				mn[x] = max(mn[x], p.val + 1);
				if(--deg[x] == 0 && done[x]) proc.push(pii(mn[x], x));
			}
		}
	}
	for(i = 1; i <= k; i++)
		if(comp[i] == i && (val[i] < mn[i] || val[i] > mx[i]))
			imp();
	puts("YES");
	for(i = 1; i <= k; i++)
		printf("%d\n", val[comp[i]]);
}
