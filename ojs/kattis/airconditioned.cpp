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

vector<int> rm[1000];
int l[1000];
int main() {
	int i, n, r;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &l[i], &r);
		rm[r].pb(i);
	}
	int last = -1, nu = 0;
	for(i = 0; i <= 2*n; i++) {
		bool buy = false;
		for(int j : rm[i])
			buy |= last < l[j];
		if(buy) nu++, last = i;
	}
	printf("%d\n", nu);
}
