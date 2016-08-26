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

int memo[9][9][9][9];

int di[8] = {1, 1, -1, -1, 2, 2, -2, -2};
int dj[8] = {2, -2, 2, -2, 1, -1, 1, -1};

int B(int, int, int, int);
int W(int lw, int cw, int lb, int cb) {
	if(cb == 0) return 1;
	int &r = memo[lw][cw][lb][cb];
	if(r != -1) return r;
	r = 1;
	for(int d = 0; d < 8; d++) {
		int l = lw + di[d], c = cw + dj[d];
		if(!(l >= 0 && l < 8 && c >= 0 && c < 8)) continue;
		if(lb == l && cb == c) return r = 0;
		if(!B(l, c, lb, cb)) return r = 0;
	}
	return r;
}

int B(int lw, int cw, int lb, int cb) {
	int &r = memo[lw][cw][lb][cb];
	if(r != -1) return r;
	r = 0;
	for(int i = -1; i <= 1; i += 2) {
		if(lb + i < 0 || lb + i >= 8) continue;
		if(cw == cb - 1 && lw == lb + i) {
			if(cb >= 2 && lb + 2*i >= 0 && lb + 2*i < 8)
				return r = 1;
		} else if(W(lw, cw, lb + i, cb - 1)) return r = 1;
	}
	return r;
}


char s[100], wi[100], bl[100];
char *name[] = {"White", "Black"};
int main() {
	memset(memo, -1, sizeof memo);
	scanf("%s %s %s", s, wi, bl);
	int lw = wi[0] -'a', cw = wi[1] - '1';
	int lb = bl[0] -'a', cb = bl[1] - '1';
	printf("%s\n", name[(s[0] == 'w'? W : B)(lw, cw, lb, cb)]);
}
