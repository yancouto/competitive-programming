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

const int N = 70007;

struct info {
	int a, b;
	pair<int, int> v;
	
	bool operator < (const info & ot) const {
		if (a != ot.a) return a < ot.a;
		return v < ot.v;
	}
};

struct evt {
	int a, b, id;
	pair<int, int> v;

	bool operator < (const evt & ot) const {
		if (a != ot.a) return a < ot.a;
		return v < ot.v;
	}
};

map<pair<int, int>, info> mp;
int n, m;
evt x[N];
info v[N];

int res[N][7];
int p[N];

bool cmp_t (int i, int j) {
	for (int k = 0; k < 7; k++)
		if (res[i][k] != res[j][k])
			return res[i][k] < res[j][k];
	return 0;
}

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)
		scanf("%d %d %d %d", &v[i].v.first, &v[i].v.second, &v[i].a, &v[i].b);
	
	for (int i = 0; i < m; i++)
		scanf("%d %d %d %d %d", &x[i].v.first, &x[i].v.second, &x[i].id, &x[i].a, &x[i].b);

	sort(v, v+n);
	sort(x, x+m);

	int i = 0;
	int j = 0;
	int rs = 0;
	while (i < n || j < m) {
		if (i == n || (j < m && x[j].a <= v[i].a)) {
			//printf("%d: que %d %d %d %d %d\n", x[j].a, x[j].v.first, x[j].v.second, x[j].a, x[j].id, x[j].b);
			if (mp.find(x[j].v) != mp.end()) {
				info att = mp[x[j].v];
				res[rs][0] = att.b;
				res[rs][1] = x[j].v.first;
				res[rs][2] = x[j].v.second;
				res[rs][3] = att.a;
				res[rs][4] = x[j].id;
				res[rs][5] = x[j].a;
				res[rs][6] = x[j].b;
				p[rs] = rs;
				rs++;
			}
			j++;
		} else {
			//printf("%d: add %d %d %d %d\n", v[i].a, v[i].v.first, v[i].v.second, v[i].a, v[i].b);
			mp[v[i].v] = v[i];
			i++;
		}
	}

	sort(p, p+rs, cmp_t);

	printf("%d\n", rs);
	for (int i = 0; i < rs; i++)
		printf("%d %d %d %d %d %d %d\n", res[p[i]][1], res[p[i]][2], res[p[i]][3], res[p[i]][0], res[p[i]][4], res[p[i]][5], res[p[i]][6]);
}
