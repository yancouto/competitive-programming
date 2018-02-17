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

int mrk[112];

int main() {
	int i, x;
	for(i = 0; i < 10; i++) {
		scanf("%d", &x);
		mrk[x] = 1;
	}
	for_tests(tn, tt) {
		int ok = 0;
		for(i = 0; i < 6; i++) {
			scanf("%d", &x);
			ok += mrk[x];
		}
		if(ok >= 3) puts("Lucky");
		else puts("Unlucky");
	}
}
