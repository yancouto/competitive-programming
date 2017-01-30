#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef unsigned short us;
//typedef int us;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 400;
const int X[2] = {102, 1501};
const int K = 1500;
const int Q = 41234;
const us INF = USHRT_MAX;

us memo[Q][2*K];
bitset<2*K> visi[Q];
int n;
int v[N];
int ii;
int acc[2123];

inline us pd (int i, int x, int k) {
	int g = min(x-1, n - i - 1);
	if (i == n) {
		if (k == 0)
			return 0;
		else
			return INF;
	}
	//if (((2*(x-1) - g) * (g + 1)) / 2 > acc[i] + k)
		//printf("(%d, %d, %d) %d > %d + %d\n", i, x, k,((2*(x-1) - g) * (g + 1)) / 2,acc[i], k);
	if (x < 0 || ((2*(x-1) - g) * (g + 1)) / 2 > acc[i] + k || n * (x) >= Q) return INF;
	if (k + K < 0 || k + K >= 2*K) return INF;
	
	us & me = memo[i + n*x][k+K];
	if (visi[i + n*x][k+K]) return me;
	visi[i + n*x][k+K] = 1;
	me = INF;
	
	for (int sh = -1; sh <= 1; sh++) {
		int cs = k + v[i] - (x+sh);
		us loc = pd(i+1, x+sh, cs);

		if (loc == INF)
			continue;
		if (INF - loc <= abs(cs)) 
			continue;
		loc += abs(cs);
		
		me = min(me, loc);
	}

	return me;
}

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &v[i]);
	}
	acc[n - 1] = v[n - 1];
	for(int i = n - 2; i >= 0; i--)
		acc[i] = v[i] + acc[i + 1];
	us res = INF;
	/*
	for (int i = n-1; i > 0; i--) {
		ii = i;
		for (int x = 0; x < X[i<=20]; x++) {
			for (int k = -K; k < K; k++) {
				pd(i,x,k);
			}
		}
	}
	ii = 0;
	*/
	for (int x = 0; x < X[1]; x++)
		res = min(res, pd(0,x,0));

	printf("%d\n", res);
}
