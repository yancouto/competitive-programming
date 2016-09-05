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
	int k;
	ll cur = 0, sz = 1;
	set<int> s;
	while(true) {
		if(cur + 1ll > INT_MAX) break;
		s.insert(cur + 1ll);
		cur += sz;
		sz++;
	}
	for_tests(t, tt) {
		scanf("%d", &k);
		if(s.count(k)) puts("1");
		else puts("0");
	}
}
