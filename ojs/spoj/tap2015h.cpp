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

char s[112];
int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		int ct = 0;
		while(n > 0) {
			ct++;
			sprintf(s, "%d", n);
			sort(s, s + strlen(s));
			n -= atoi(s);
		}
		printf("%d\n", ct);

	}
}
