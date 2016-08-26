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

int mat[1123][1123], n;

void prn() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			printf("%d ", mat[i][j]);
		putchar('\n');
	}
	puts("-----------------");
}

bool ok(int i, int j) {
	for(int k = i - 1; k >= 0; k--) {
		if(mat[k][j])
			return false;
	}
	for(int k = i - 1; k >= 0; k--) {
		int v = i - k;
		int nj = (j - v + n) % n;
		if(mat[k][nj]) return false;
		nj = (j + v) % n;
		if(mat[k][nj]) return false;
	}
	return true;
}

void solve(int i) {
	if(i == n) {
		printf("SUCCESS\n");
		prn();
		exit(0);
	}
	for(int j = 0; j < n; j++) {
		mat[i][j] = 1;
		if(ok(i, j))
			solve(i + 1);
		mat[i][j] = 0;
	}
}

int main() {
	scanf("%d", &n);
	solve(0);
}
