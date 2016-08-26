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
const int N = 209;
int l[N], r[N], n;


double f(int i, int x) {
	if(l[i] >= x + 1) return 0;
	if(r[i] <= x) return 1;
	return double(x - l[i]) / (x + 1 - l[i]);
}

double memo3[51][201][52][51];
bool seen3[51][201][52][51];
double emax(int k, int x, int cant, int i) {
	if(i == n) return k == 0;
	if(i == cant) return emax(k, x, n, i + 1);
	double &m = memo3[k][x][cant][i];
	if(seen3[k][x][cant][i]) return m;
	seen3[k][x][cant][i] = true;
	m = emax(k, x, cant, i + 1) * f(i, x - 1);
	if(k > 0) m += emax(k - 1, x, cant, i + 1) * (1. - f(i, x - 1));
	return m;
}


double memo2[N][N]; int seen2[N][N];
double dmax(int x, int i) {
	if(x == 0) return 0;
	double &m = memo2[x][i];
	if(seen2[x][i]) return m;
	seen2[x][i] = true;
	m = 1;
	for(int j = 0; j < n; j++) if(i != j) m *= f(j, x - 1);
	if(m > 0) m *= dmax(x - 1, i);
	for(int k = 1; k <= n; k++) m += emax(k, x, i, 0) * (x - 1. + double(k) / (k + 1));
	//printf("dmax(%d, %d) = %.5f\n", x, i, m);
	return m;
}

int mx;

double memo[N]; int seen[N];
double dsec(int x) {
	if(mx >= x) return 0.;
	if(x == 0) return 0;
	double &m = memo[x];
	if(seen[x]) return m;
	seen[x] = true;
	double p = 1;
	for(int i = 0; i < n; i++) p *= f(i, x - 1);
	//printf("dsec(%d) go back %.5f\n", x, p);
	m = p * dsec(x - 1);
	for(int i = 0; i < n; i++) {
		p = (1. - f(i, x - 1));
		for(int j = 0; j < n; j++)
			if(j != i)
				p *= f(j, x - 1);
		//printf("dsec(%d) blow %d = %.5f * %.5f\n", x, i, p, dmax(x - 1, i));
		m += p * dmax(x - 1, i);
	}
	for(int k = 2; k <= n; k++) {
		//printf("dsec(%d) blow %d guys = %.5f * %.5f\n", x, k, emax(k, x, n, 0), (x - 1. + double(k - 1) / (k + 1)));
		m += emax(k, x, n, 0) * (x - 1. + double(k - 1) / (k + 1));
	}
	//printf("dsec(%d) = %.6f\n", x, m);
	return m;
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d %d", &l[i], &r[i]), l[i] += 100, r[i] += 100;
	mx = *max_element(l, l + n);
	printf("%.15f\n", dsec(200) - 100.);
}
