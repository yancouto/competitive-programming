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

typedef long double dbl;
const dbl eps = 1e-7;
const int N = 112, M = 412;

struct simplex {
	int X[N], Y[M];
	dbl A[M][N], b[M], c[N];
	dbl ans;
	int n, m;
	dbl sol[N];

	void pivot(int x,int y){
		swap(X[y], Y[x]);
		b[x] /= A[x][y];
		for(int i = 0; i < n; i++)
			if(i != y)
				A[x][i] /= A[x][y];
		A[x][y] = 1. / A[x][y];
		for(int i = 0; i < m; i++)
			if(i != x && abs(A[i][y]) > eps) {
				b[i] -= A[i][y] * b[x];
				for(int j = 0; j < n; j++)
					if(j != y)
						A[i][j] -= A[i][y] * A[x][j];
				A[i][y] = -A[i][y] * A[x][y];
			}
		ans += c[y] * b[x];
		for(int i = 0; i < n; i++)
			if(i != y)
				c[i] -= c[y] * A[x][i];
		c[y] = -c[y] * A[x][y];
	}

	// maximiza sum(x[i] * c[i])
	// sujeito a
	//    sum(a[i][j] * x[j]) <= b[i] para 0 <= i < m (Ax <= b)
	//    x[i] >= 0 para 0 <= i < n (x >= 0)
	// (n variaveis, m restricoes)
	// guarda a resposta em ans e retorna o valor otimo
	dbl solve(int n, int m) {
		this->n = n; this->m = m;
		ans = 0.;
		for(int i = 0; i < n; i++) X[i] = i;
		for(int i = 0; i < m; i++) Y[i] = i + n;
		while(true) {
			int x = min_element(b, b + m) - b;
			if(b[x] >= -eps)
				break;
			int y = find_if(A[x], A[x] + n, [](dbl d) { return d < -eps; }) - A[x];
			if(y == n) ; // no solution
			pivot(x, y);
		}
		while(true) {
			int y = max_element(c, c + n) - c;
			if(c[y] <= eps) break;
			int x = -1;
			dbl mn = 1. / 0.;
			for(int i = 0; i < m; i++)
				if(A[i][y] > eps && b[i] / A[i][y] < mn)
					mn = b[i] / A[i][y], x = i;
			if(x == -1) ; // unbounded
			pivot(x, y);
		}
		memset(sol, 0, sizeof(dbl) * n);
		for(int i = 0; i < m; i++)
			if(Y[i] < n)
				sol[Y[i]] = b[i];
		return ans;
	}
};

struct no {
	int u, d, p;
	bool operator < (no o) const { return d > o.d; }
};

int en = 0;

dbl A_[M][N], b_[M];
int seen[N], tempo;
int to[N], we[N], from[N], pai[N];
vector<int> adj[N];

simplex si;

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			int x;
			scanf("%d", &x);
			if(x <= 0) continue;
			from[en] = i; to[en] = j; we[en] = x;
			A_[2 * en][en] = 1;
			b_[2 * en] = 2 * x; // <= 2x
			A_[2 * en + 1][en] = -1;
			b_[2 * en + 1] = -x; // >= x
			adj[i].pb(en++);
		}
	int oen = en;
	en <<= 1;
	int r;
	scanf("%d", &r);
	for(i = 0; i < r; i++) {
		tempo++;
		int s, d; int t;
		scanf("%d %d %d", &s, &d, &t);
		priority_queue<no> pq;
		pq.push(no{s, 0, -1});
		while(!pq.empty()) {
			no x = pq.top(); pq.pop();
			if(seen[x.u] == tempo) continue;
			seen[x.u] = tempo;
			pai[x.u] = x.p;
			for(int e : adj[x.u])
				pq.push(no{to[e], x.d + we[e], e});
		}
		for(; pai[d] != -1; d = from[pai[d]]) {
			A_[en][pai[d]] = 1;
			A_[en + 1][pai[d]] = -1;
		}
		b_[en] = t; // arriscado sem eps?
		b_[en + 1] = -t;
		en += 2;
	}
	int q;
	scanf("%d", &q);
	while(q--) {
		tempo++;
		int s, d;
		scanf("%d %d", &s, &d);
		priority_queue<no> pq;
		pq.push(no{s, 0, -1});
		while(!pq.empty()) {
			no x = pq.top(); pq.pop();
			if(seen[x.u] == tempo) continue;
			seen[x.u] = tempo;
			pai[x.u] = x.p;
			for(int e : adj[x.u])
				pq.push(no{to[e], x.d + we[e], e});
		}
		memset(si.c, 0, sizeof si.c);
		for(int od = d; pai[od] != -1; od = from[pai[od]])
			si.c[pai[od]] = 1;
		for(i = 0; i < en; i++) {
			si.b[i] = b_[i];
			for(j = 0; j < oen; j++)
				si.A[i][j] = A_[i][j];
		}
		dbl high;
		high = si.solve(oen, en);
		memset(si.c, 0, sizeof si.c);
		for(int od = d; pai[od] != -1; od = from[pai[od]])
			si.c[pai[od]] = -1;
		for(i = 0; i < en; i++) {
			si.b[i] = b_[i];
			for(j = 0; j < oen; j++)
				si.A[i][j] = A_[i][j];
		}
		dbl low = -si.solve(oen, en);
		printf("%d %d %.10f %.10f\n", s, d, (double) low, (double) high);
	}
}
