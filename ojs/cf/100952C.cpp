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

char s[112345];
int main() {
	int n, p, i;
	for_tests(t, tt) {
		scanf("%d %d %s", &n, &p, s); p--;
		if(n - 1 - p < p) p = n - 1 - p;
		int lst = INT_MIN, fst = INT_MAX;
		int tot = 0;
		for(i = 0; n-1-i > i; i++) {
			if(s[i] != s[n - i - 1]) {
				fst = min(fst, i);
				lst = i;
				tot += min(abs(s[i] - s[n - 1 - i]), 26 - abs(s[i] - s[n - i - 1]));
			}
		}
		if(fst == INT_MAX) puts("0");
		else {
			if(p < fst) tot += lst - p;
			else if(p > lst) tot += p - fst;
			else tot += (lst - fst) + min(lst - p, p - fst);
			printf("%d\n", tot);
		}
	}
}
