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

const int N = 52;
const int M = 11;

int n, d, c;
int v[2][N];
double fat[N];

double memo[M][M][M];
int visi[M][M][M];
double ch[N][N];
int vs[N][N];

inline double choose (int n, int k) {
	if (k > n || k < 0) return 0.;
	if (n == 0) return 1.;

	double & me = ch[n][k];
	if (vs[n][k]) return me;
	vs[n][k] = 1;

	return me = choose(n-1, k) + choose(n-1,k-1);
}

double pd (int x, int y, int z) {
	if ((x == 0 || y == 0) && z == 0)
		return 0.;
	double & me = memo[x][y][z];
	if (visi[x][y][z])
		return me;
	visi[x][y][z] = 1;
	double di = choose(n,d) - choose(n-x-y-z,d);
	me = choose(n-x-y-z,d)/di;

	for (int a = 0; a <= x; a++) {
		for (int b = 0; b <= y; b++) {
			for (int c = 0; c <= z; c++) {
				if (!a && !b && !c) continue;
				if (a + b + c > d) continue;
				
				me += choose(x,a) * choose(y,b) * choose(z,c) * choose(n-x-y-z,d-a-b-c) * (pd(x-a, y-b, z-c) + 1.) / di;
			}
		}
	}

	return me;
}

int main () {
	scanf("%d %d %d", &n, &d, &c);

	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < c; i++) {
			int x;
			scanf("%d", &x);
			v[k][x]++;
		}
	}

	int x, y, z;
	x = y = z = 0;

	for (int i = 1; i <= n; i++) {
		if (v[0][i] && v[1][i])
			z++;
		else if (v[0][i])
			x++;
		else if (v[1][i])
			y++;
	}

	printf("%.20f\n", pd(x,y,z));
}
