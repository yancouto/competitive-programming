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
#define set asjoajsdoijsad

int d, b;
int pot[30];

int get(int n, int i) {
	return (n / pot[i]) % (b + 1);
}

int unset(int);
int set(int n, int i, int v) {
	int s = n - pot[i] * (b - v);
	//printf("set(%d, %d, %d) = %d\n", n, i, v, s);
	assert(unset(s) == unset(n) - 1);
	return s;
}

int mun[3008];
int unset(int n) {
	int &r = mun[n];
	if(r != -1) return r;
	r = 0;
	for(int i = 0; i < d; i++, n /= (b + 1))
		if((n % (b + 1)) == b)
			r++;
	return r;
}

double maxd(double a, double b) { return std::max(a, b); }
double mind(double a, double b) { return std::min(a, b); }

int t;
int seen1[3003][3003][2];
double memo1[3003][3003][2];
double game1(int p, int q, bool fst) {
	double &r = memo1[p][q][fst];
	if(seen1[p][q][fst] == t) return r;
	seen1[p][q][fst] = t;
	assert(unset(p) >= unset(q) && unset(p) <= unset(q) + 1);
	if(unset(p) == 0 && unset(q) == 0) return r = p > q;
	r = 0;
	auto fun = fst? maxd : mind;
	for(int i = 0; i < b; i++) {
		int P = p;
		double mx = fst? -1/0. : 1/0.;
		for(int j = 0; j < d; j++, P /= (b + 1)) {
			if((P % (b + 1)) != b) continue;
			mx = fun(mx, game1(q, set(p, j, i), !fst));
		}
		r += mx;
	}
	r /= b;
	return r;
}

int seen2[3003][3003];
double memo2[3003][3003];
double game2(int p, int q) {
	double &r = memo2[p][q];
	if(seen2[p][q] == t) return r;
	seen2[p][q] = t;
	if(unset(p) == 0 && unset(q) == 0) return r = p > q;
	r = 0;
	auto fun = unset(p)? maxd : mind;
	if(unset(p)) {
		for(int i = 0; i < b; i++) {
			int P = p;
			double mx = unset(p)? -1/0. : 1/0.;
			for(int j = 0; j < d; j++, P /= (b + 1)) {
				if((P % (b + 1)) != b) continue;
				mx = fun(mx, game2(set(p, j, i), q));
			}
			r += mx;
		}
		r /= b;
	} else {
		for(int i = 0; i < b; i++) {
			int P = q;
			double mx = unset(p)? -1/0. : 1/0.;
			for(int j = 0; j < d; j++, P /= (b + 1)) {
				if((P % (b + 1)) != b) continue;
				mx = fun(mx, game2(p, set(q, j, i)));
			}
			r += mx;
		}
		r /= b;
	}
	return r;
}


int main() {
	//freopen("greater.in", "r", stdin);
	//freopen("greater.out", "w", stdout);
	int i;
	pot[0] = 1;
	for(int B = 2; B <= 10; B++) {
		int kb = B + 1;
		for(int D = 1; kb <= 3000 && D <= 10; D++, kb *= (B + 1)) {
			t++;
			d = D; b = B;
			memset(mun, -1, sizeof mun);
			for(i = 1; i < 20; i++)
				pot[i] = pot[i - 1] * (b + 1);
			int all = 0;
			for(i = 0; i < d; i++)
				all = all * (b + 1) + b;
			assert(unset(all) == d);
			printf("(%d, %d) = ", d, b);
			printf("%.10f %.10f\n", game1(all, all, true), game2(all, all));
		}
	}
}
