
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

const int N = 3e5+7;

int n, m;
ll o[N]; int a[N], b[N], d[N];
double y[N];

struct edge {
	int a, b; double w;
};

void rd (ll & x) {
	char c;
	bool ng = 0; x = 0;
	while (isspace((c = getchar())));
	if (c == '-') ng = 1;
	else if (c == '?') { x = INT_MIN; return; }
	else x = c - '0';
	while (isdigit(c = getchar())) { x *= 10; x += c - '0'; }
	if (ng) x = -x;
}

bool solve (double T) {
	y[0] = 0;
	double lim = 1e9;
	vector<edge> ed;
	for (int i = 1; i <= n; i++) {
		y[i] = 0;
		ed.pb({ 0, i, lim });
		ed.pb({ i, 0, lim });
	}

	for (int i = 1; i <= n; i++) if (o[i] != INT_MIN) {
		ed.pb({ 0, i, o[i] });
		ed.pb({ i, 0, -o[i] });
	}
	for (int i = 0; i < m; i++)
		ed.pb({ b[i], a[i], T - d[i] });

	bool chg = 0;
	for (int i = 0; i < n + 4; i++) {
		chg = 0;
		for (edge e : ed) {
			if(y[e.a] + e.w < y[e.b] - 1e-8) {
				y[e.b] =  y[e.a] + e.w;
				chg = 1;
			}
		}
	}
	return chg == false;
}

int main () {
	while (scanf("%d %d", &n, &m) != EOF) {
		for (int i = 1; i <= n; i++) {
			rd(o[i]);
		}
		for (int i = 0; i < m; i++)
			scanf("%d %d %d", &a[i], &b[i], &d[i]);

		double lo = 0, hi = 5e6+3;
		int ts = 60;
		while (ts--) {
			double md = (lo+hi)/2;
			if (solve(md)) hi = md;
			else lo = md;
		}
		solve(lo);
		//for(int i = 0; i < m; i++)
		//	assert(y[a[i]] + d[i] <= y[b[i]] + lo);
		//for(int i = 1; i <= n; i++) if (o[i] != INT_MIN)
		//	assert(y[i] - y[0] == o[i]);
		printf("%.10f\n", lo);
		for (int i = 1; i <= n; i++) {
			printf("%.10f ", y[i] - y[0]);
			//assert(y[i]-y[0] >= -1e9 && y[i]-y[0] <= 1e9);
		}
		printf("\n");
	}
}
