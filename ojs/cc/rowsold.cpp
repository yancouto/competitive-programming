#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

char s[112345];

int main() {
	int i;
	for_tests(t, tt) {
		scanf("%s", s);
		int one = 0;
		ll tot = 0;
		for(i = 0; s[i]; i++) {
			if(s[i] == '0') {
				tot += one;
			} else {
				if(i > 0 && s[i - 1] != '1') tot += one;
				one++;
			}
		}
		if(s[i - 1] != '1') tot += one;
		printf("%lld\n", tot);
	}
}
