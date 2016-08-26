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

int X, B;
int memo[30][2];
int solve(int i, bool pre) {
	if(i < 0) return 1;
	int &r = memo[i][pre];
	if(r != -1) return r;
	if(i == B) {
		if(!pre || ((X >> i) & 1)) r = solve(i - 1, pre && ((X >> i) & 1));
		else r = 0;
	} else {
		r = solve(i - 1, pre && !((X >> i) & 1));
		if(!pre || ((X >> i) & 1)) r += solve(i - 1, pre && ((X >> i) & 1));
	}
	return r;
}

int count(int x, int bit) {
	if(x == -1) return 0;
	if((1 << bit) > x) return 0;
	X = x; B = bit;
	memset(memo, -1, sizeof memo);
	return solve(29, true);
}

int main() {
	int l, r, i;
	scanf("%d %d", &l, &r);
	int num = 0;
	for(i = 0; i < 30; i++)
		if(2*(count(r, i) - count(l - 1, i)) > r - l + 1)
			num ^= (1 << i);
	printf("%d\n", num);
}
