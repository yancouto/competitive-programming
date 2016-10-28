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

char p[112345];
int main() {
	int i, n, s, j, d;
	while(scanf("%d %d %d %d", &n, &s, &j, &d) != EOF) {
		scanf("%s", p);
		int cura = 0, curb = 0, a = 0, b = 0;
		for(i = 0; i < n; i++) {
			if(p[i] == 'A') cura++;
			else curb++;
			if(cura >= j && cura >= curb + d) cura = curb = 0, a++;
			else if(curb >= j && curb >= cura + d) cura = curb = 0, b++;
		}
		printf("%d %d\n", a, b);
	}
}
