#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back

vector<int> ot, g;

const int N = 512;

int num[N], mn[N], mx[N];

int memo[512][16];
int seen[512][16], tempo;
int solve(int i, int j) {
	if(i == ot.size() && j == g.size()) return 0;
	int &r = memo[i][j];
	if(seen[i][j] == tempo) return r;
	seen[i][j] = tempo;
	r = 1e8;
	if(i < ot.size()) r = 1 + solve(i + 1, j);
	if(j < g.size()) r = min(r, solve(i, j + 1));
	if(i < ot.size() && mn[ot[i]] >= j && mx[ot[i]] < j) r = min(r, solve(i + 1, j));
	return r;
}

vector<int> add_back;

void build(int i, int j) {
	if(i == ot.size() && j == g.size()) return;
	int r = solve(i, j);
	if(i < ot.size() && r == 1 + solve(i + 1, j)) {
		add_back.pb(ot[i]);
		return build(i + 1, j);
	}
	if(j < g.size() && r == solve(i, j + 1)) return build(i, j + 1);
	return build(i + 1, j);
}

int deg[512];
char A[N][N];

vector<int> ord_top(const vector<int> &g) {
	memset(deg, 0, sizeof deg);
	for(int x : g)
		for(int y : g)
			deg[x] += (A[x][y] == '1');
	vector<int> f = g;
	sort(f.begin(), f.end(), [](int i, int j) { return deg[i] > deg[j]; });
	vector<int> wa;
	for(int i = 0; i < g.size(); i++)
		for(int j = i + 1; j < g.size(); j++)
			if(A[f[i]][f[j]] != '1')
				return wa;
	return f;
}

int a[N];
int main () {
#ifdef ONLINE_JUDGE
	freopen("simplicity.in", "r", stdin);
	freopen("simplicity.out", "w", stdout);
#endif
	int i, n, j, k;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf(" %c", &A[i][j]);
	scanf("%d", &k);
	for(i = 0; i < k; i++) scanf("%d", &a[i]), a[i]--;
	for(i = 0; i < n; i++) {
		for(j = 0; j < k && i != a[j]; j++);
		if(j == k) ot.pb(i);
	}
	ot = ord_top(ot);
	int ans = k, mnb = 0;
	for(int bm = 1; bm < (1 << k); bm++) {
		g.clear();
		for(j = 0; j < k; j++)
			if((bm >> j) & 1)
				g.pb(a[j]);
		g = ord_top(g);
		if(g.empty()) continue;
		for(j = 0; j < g.size(); j++)
			num[g[j]] = j;
		for(int i : ot) {
			mn[i] = INT_MAX;
			mx[i] = INT_MIN;
			for(int x : g)
				if(A[i][x] == '1')
					mn[i] = min(mn[i], num[x]);
				else
					mx[i] = max(mx[i], num[x]);
		}
		tempo++;
		int x = solve(0, 0);
		if(k - g.size() + x < ans) {
			ans = k - g.size() + x;
			mnb = bm;
		}
	}
	g.clear();
	for(j = 0; j < k; j++)
		if((mnb >> j) & 1)
			g.pb(a[j]);
		else
			add_back.pb(a[j]);
	g = ord_top(g);
	for(j = 0; j < g.size(); j++)
		num[g[j]] = j;
	for(int i : ot) {
		mn[i] = INT_MAX;
		mx[i] = INT_MIN;
		for(int x : g)
			if(A[i][x] == '1')
				mn[i] = min(mn[i], num[x]);
			else
				mx[i] = max(mx[i], num[x]);
	}
	tempo++;
	build(0, 0);
	printf("%d\n", ans);
	for(int y : add_back)
		printf("%d ", y + 1);
	putchar('\n');
}
