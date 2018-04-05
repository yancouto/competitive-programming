#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

typedef double dbl;

const int N = 1123;
dbl p[N], q[N][N], E[N];
int k[N];
int pi[N];

int n;

int main() {
	int i, j;
	rd(n);
	for(i = 0; i < n; i++) {
		rd(k[i]);
		p[i] = 1;
		for(j = 0; j < k[i]; j++) {
			int x;
			rd(x);
			q[i][j] = x / 1000.;
		}
		sort(q[i], q[i] + k[i]);
		E[i] = 0;
		for(j = 0; j < k[i]; j++) {
			E[i] += (j + 1) * p[i] * (1. - q[i][j]);
			p[i] *= q[i][j];
		}
		E[i] = E[i] / (1 - p[i]);
		pi[i] = i;
		//printf("[%d] n %d p %.3f E %.3f\n", i, k[i], p[i], E[i]);
	}
	sort(pi, pi + n, [](int i, int j) {
		return p[i] * k[i] + (1. - p[i]) * (E[i] + p[j] * k[j]) + (1. - p[i]) * (1. - p[j]) * E[j] < p[j] * k[j] + (1. - p[j]) * (E[j] + p[i] * k[i]) + (1. - p[i]) * (1 - p[j]) * E[i];
	});
	dbl sE = 0;
	dbl ans = 0;
	dbl acc = 1;
	for(int i_ = 0; i_ < n; i_++) {
		i = pi[i_];
		//printf("do %d\n", i);
		//printf("+= %.2f * %.2f\n", sE + k[i], acc * p[i]);
		ans += (sE + k[i]) * (acc * p[i]);
		acc *= (1. - p[i]);
		sE += E[i];
	}
	ans += acc * sE;
	//printf("+= %.2f * %.2f\n", acc, sE);
	printf("%.15f\n", ans);
}
