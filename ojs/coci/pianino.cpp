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

inline int sign(int x) { return (x > 0) - (x < 0); }

unordered_map<int, int> mp;
int main() {
	int i, n, a0, a, any = 1;
	scanf("%d", &n);
	scanf("%d", &a0);
	int lst = a0, cur = 0;
	for(i = 1; i < n; i++) {
		scanf("%d", &a);
		if(a > lst) cur++;
		else if(a < lst) cur--;
		lst = a;
		if(sign(cur) != sign(a - a0)) continue;
		if(cur == 0) { any++; continue; }
		if((abs(a - a0) % abs(cur)) == 0) mp[(a - a0) / cur]++;
	}
	if(mp.empty()) { printf("%d\n1\n", any); return 0; }
	pii b(-1, -1);
	for(pii p : mp)
		if(p.snd > b.snd)
			b = p;
	printf("%d\n%d\n", any + b.snd, b.fst);
}
