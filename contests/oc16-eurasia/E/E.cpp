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
const int N = 2123;
bool M[N][N], seen[N];
double d[N], ans;
int p[N], n;
int x[N], y[N];

double vr, vf;
inline int sqr(int x) { return x * x; }
inline double dist(int i, int j) {
	return sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
}

inline double walk(int i, int j) {
	return dist(i, j) / vf;
}

inline double bike(int i, int j) {
	return dist(i, j) / vr;
}


vector<int> path;
void go(int a, int b) {
	for(int i = 0; i < n; i++) d[i] = 1/0., seen[i] = false;
	d[a] = 0; p[a] = -1;
	for(int j = 0; j < n; j++) {
		int cur = -1;
		for(int i = 0; i < n; i++)
			if(!seen[i] && (cur == -1 || d[i] < d[cur]))
				cur = i;
		assert(cur != -1);
		assert(d[cur] != 1/0.);
		seen[cur] = true;
		for(int i = 0; i < n; i++) {
			if(seen[i]) continue;
			if(M[cur][i] && bike(cur, i) + d[cur] < d[i]) d[i] = bike(cur, i) + d[cur], p[i] = cur;
			else if(walk(cur, i) + d[cur] < d[i]) d[i] = walk(cur, i) + d[cur], p[i] = cur;
		}
	}
	ans += d[b];
	vector<int> P;
	while(b != -1) {
		P.pb(b);
		b = p[b];
	}
	reverse(P.begin(), P.end());
	for(int x : P) path.pb(x);
}

int main() {
	int m, k, a, b, i;
	scanf("%d %d %d %lf %lf", &n, &m, &k, &vr, &vf);
	for(i = 0; i < n; i++)
		scanf("%d %d", &x[i], &y[i]);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		M[a][b] = M[b][a] = 1;
	}
	int prev = 0;
	for(i = 0; i < k; i++) {
		scanf("%d", &a); a--;
		go(prev, a);
		prev = a;
		path.pop_back();
	}
	go(prev, n - 1);
	printf("%.10f\n", ans);
	for(int x : path)
		printf("%d ", x + 1);
	putchar('\n');
}
