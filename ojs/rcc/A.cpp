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

int main() {
	int i, j, n, t, t0, m, x;
	scanf("%d %d %d" , &n, &t, &t0);
	for(i = 0; i < n; i++) {
		scanf("%d", &m);
		int gt = 0, tot = 0, us = 0;
		for(j = 0; j < m; j++) {
			scanf("%d", &x);
			if(tot > t) continue;
			gt = max(x, gt);
			if(x + tot <= t) tot += x;
			else if(!us && x + tot - gt + t0 <= t) tot += x - gt + t0, us = 1;
			else { tot = INT_MAX; printf("%d\n", j); }
		}
		if(tot <= t) printf("%d\n", m);
	}
}
