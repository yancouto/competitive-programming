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
#define i first
#define j second

int mat[31][31][31][31];
int tot[32][32], n, m;
char g[32][32];
const long double eps = 1e-7;


long double val[34][34];
struct cmp {
	bool operator()(pii a, pii b) {
		return val[a.i][a.j] < val[b.i][b.j] - eps;
	}
};

int x(int i, int j) { return j; }
int y(int i, int j) { return n - i; }
int l, c;

long double aval(pii p) { return val[p.i][p.j]; }


void calc_mat(int l, int c) {
	::l = l; ::c = c;
	int i, j;
	multiset<pii, cmp> s;
	vector<pair<int, pii>> O;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			if(i != l || j != c)
				O.pb(make_pair((i - l) * (l - i) + (j - c) * (c - j), pii(i, j)));
	sort(O.begin(), O.end());
	//printf("at (%d, %d)\n", l, c);
	for(int i2 = 0; i2 < O.size(); i2++) {
		i = O[i2].snd.fst; j = O[i2].snd.snd;
		//printf("processing (%d, %d)\n", i, j);
		if(g[i][j] == '.') {
			val[i][j] = atan2((long double) (y(i, j) - y(l, c)), (long double) (x(i, j) - x(l, c)));
			//printf("(%d, %d) ang %.10Lf\n", i, j, val[i][j]);
			s.insert(pii(i, j));
			continue;
		}
		long double mn = 1/0., mx = -1/0.;
		for(int k = 0; k < 4; k++) {
			long double x1 = (x(i, j) - x(l, c)), y1 = (y(i, j) - y(l, c));
			if(i == l && j < c && !(k & 1)) continue;
			if(k & 1) x1 += .5;
			else x1 -= .5;
			if(k & 2) y1 += .5;
			else y1 -= .5;
			long double a = atan2(y1, x1);
			mn = min(mn, a);
			mx = max(mx, a);
		}
		val[32][32] = mx;
		auto itmx = s.upper_bound(pii(32, 32));
		if(itmx != s.end() && abs(aval(*itmx) - mx) <= eps) ++itmx;
		val[33][33] = mn;
		auto itmn = s.lower_bound(pii(33, 33));
		if(itmn != s.begin() && abs(aval(*prev(itmn)) - mn) <= eps) --itmn;
		//printf("want to rem (%.10Lf, %.10Lf)\n", mn, mx);
		if(i == l && j < c) {
			// TRATAR SEPARADO
			while(!s.empty() && aval(*s.begin()) <= mn + eps) {
				//printf("removing (%d, %d)\n", s.begin()->i, s.begin()->j);
				s.erase(s.begin());
			}
			while(!s.empty() && aval(*s.rbegin()) >= mx - eps) {
				//printf("removing (%d, %d)\n", s.rbegin()->i, s.rbegin()->j);
				s.erase(prev(s.end()));
			}
		} else {
			//for(auto it = itmn; it != itmx; ++it)
				//printf("removing (%d, %d)\n", it->i, it->j);
			s.erase(itmn, itmx);
		}
	}
	for(pii e : s) {
		mat[l][c][e.i][e.j]++;
		tot[e.i][e.j]++;
		//printf("(%d, %d) reach (%d, %d)\n", l, c, e.i, e.j);
	}
	mat[l][c][l][c]++;
}

bool ok(int l, int c) {
	//printf("anal(%d, %d)\n", l, c);
	//for(int i = 0; i < n; i++) {
	//	for(int j = 0; j < m; j++)
	//		printf("%d ", mat[l][c][i][j]);
	//	putchar('\n');
	//}
	vector<pii> O;
	for(int i = l; i < n && g[i][c] != '#'; i++)
		O.pb(pii(i, c));
	for(int i = l - 1; i >= 0 && g[i][c] != '#'; i--)
		O.pb(pii(i, c));
	for(int j = c + 1; j < m && g[l][j] != '#'; j++)
		O.pb(pii(l, j));
	for(int j = c - 1; j >= 0 && g[l][j] != '#'; j--)
		O.pb(pii(l, j));
	//for(pii e : O)
	//	printf("hit (%d, %d)\n", e.i, e.j);
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			if(g[i][j] == '.' && (i != l || j != c)) {
				bool ok = true;
				for(pii e : O)
					if(!mat[i][j][e.i][e.j]) {
						ok = false;
						//printf("(%d, %d) not hits (%d, %d)\n", i, j, e.i, e.j);
						break;
					}
				//if(ok) printf("(%d, %d) kills\n", i, j);
				if(ok) return false;
			}
	return true;
}

int main() {
	freopen("jealous.in", "r", stdin);
	freopen("jealous.out", "w", stdin);
	int i, j;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf(" %c", &g[i][j]);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			if(g[i][j] == '.')
				calc_mat(i, j);
	vector<pii> v;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			if(g[i][j] == '.' && ok(i, j))
				v.pb(pii(i, j));
	printf("%d\n", (int) v.size());
	for(pii e : v)
		printf("%d %d\n", e.fst + 1, e.snd + 1);
}
