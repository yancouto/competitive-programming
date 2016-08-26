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
	int n, s, f;
	scanf("%d %d %d", &n, &s, &f);
	if(s == f) { puts("-1"); return 0; }
	int tot = 0;
	if(s > f) swap(s, f);
	if(s != 1) tot++, s++;
	if(f != n) tot++, f--;
	if(s > f) { puts("-1"); return 0; }
	tot += (f - s) / 3 + ((f - s) % 3);
	printf("%d\n", tot);
}
