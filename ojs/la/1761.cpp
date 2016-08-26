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
const int N = 1123456;
int p[N], dv[N];

int main() {
	int i, j, l, r;
	for(i = 2; i < N; i++)
		if(!dv[i])
			for(j = i; j < N; j += i)
				dv[j] = i;
	for(i = 2; i < N; i++) {
		if(dv[i] == i) { p[i] = -1; continue; }
		int x = i;
		while(x != 1)
			p[i]++, x /= dv[x];
	}
	for(i = 1; i < N; i++) p[i]--;
	int tt = 0;
	while(scanf("%d %d", &l, &r) != EOF && l != -1) {
		int mx = INT_MIN, cur = 0;
		for(i = l; i <= r; i++) {
			cur += p[i];
			mx = max(mx, cur);
			if(cur < 0) cur = 0;
		}
		printf("%d. %d\n", ++tt, mx);
	}
}
