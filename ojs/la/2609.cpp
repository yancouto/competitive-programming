#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000;
inline ll mod(ll x) { return x % modn; }

struct piece {
	bool up;
	int le, ri;
	piece() {}
	piece(bool a, int b, int c) : up(a), le(b), ri(c) {}
} ps[5];

int n, m;
ll memo[502][1025];
ll aux(int left, int b, int bm, int bm2);
ll solve(int left, int bm) {
	if(left == 0) return bm == 0;
	if(memo[left][bm] != -1) return memo[left][bm];
	return memo[left][bm] = aux(left, 0, bm, 0);
}

ll aux(int left, int b, int bm, int bm2) {
	if(__builtin_popcount(bm) == n) return solve(left - 1, bm2); 
	while(b < n && (bm & (1 << b))) b++;
	ll ret = 0;
	if(b > 0 && !(bm2 & (ps[0].ri << (b - 1)))) ret = mod(ret + aux(left, b + 1, bm | (1 << b), bm2 | (3 << (b - 1))));
	for(int i = 1; i < 5; i++)
		if(!(bm & (ps[i].le << b)) && (bm | (ps[i].le << b)) < (1 << n) && !(bm2 & (ps[i].ri << b)) && (bm2 | (ps[i].ri << b)) < (1 << n))
			ret = mod(ret + aux(left, b + 1, bm | (ps[i].le << b), bm2 | (ps[i].ri << b)));
	return ret;
}


int main() {
	ps[0] = piece(true,  1, 5);
	ps[1] = piece(false, 3, 3);
	ps[2] = piece(false, 1, 3);
	ps[3] = piece(false, 3, 2);
	ps[4] = piece(false, 3, 1);
	while(true) {
		scanf("%d %d", &n, &m);
		if(!n) return 0;
		memset(memo, -1, sizeof memo);
		printf("%d\n", (int)solve(m, 0));
	}
}
