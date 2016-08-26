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

#include <message.h>
#include "rps.h"

bool beat(char a, char b) {
	if(a == b) return true;
	if(a == 'R') return b == 'S';
	if(a == 'S') return b == 'P';
	if(a == 'P') return b == 'R';
}
char s[5123456];
int p[5123456];
int solve(int l, int r) {
	if(l == r) return l;
	int m = (l + r) / 2;
	int L = solve(l, m), R = solve(m + 1, r);
	if(beat(s[L], s[R])) return L;
	else return R;
}

int main() {
	ll id = MyNodeId(), no = NumberOfNodes(), n = GetN();
	int b = 0;
	while((1 << (b + 1)) <= no) b++;
	if(n < b) {
		if(id) return 0;
		for(int i = 0; i < (1 << n); i++)
			s[i] = GetFavoriteMove(i);
		printf("%d\n", solve(0, (1 << n) - 1));
		return 0;
	}
	if(id >= (1 << b)) return 0;
	ll tot = (1ll << (n - b));
	for(ll i = id * tot; i < (id + 1ll) * tot; i++)
		s[i - id * tot] = GetFavoriteMove(i);
	PutLL(0, id * tot + ll(solve(0, tot - 1)));
	Send(0);
	if(id) return 0;
	for(int i = 0; i < (1 << b); i++) {
		Receive(i);
		p[i] = GetLL(i);
		s[i] = GetFavoriteMove(p[i]);
	}
	printf("%lld\n", p[solve(0, (1 << b) - 1)]);
}
