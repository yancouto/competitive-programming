#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)


int m[10];
int main() {
	int i, n, p, g;
	for_tests(tn, tt) {
		for(i = 0; i < 4; i++) m[i] = 0;
		scanf("%d %d", &n, &p);
		for(i = 0; i < n; i++) {
			scanf("%d", &g);
			m[g % p]++;
		}
		int tot = m[0];
		while(((p & 1) == 0) && m[p/2] > 1) {
			tot++;
			m[p/2] -= 2;
		}
		while(p > 2 && m[1] > 0 && m[p - 1] > 0) {
			tot++;
			m[1]--;
			m[p - 1]--;
		}
		while(p == 4 && m[2] && m[1] + m[3] > 1) {
			tot++;
			m[2]--;
			if(m[1]) m[1] -= 2;
			else m[3] -= 2;
		}
		while(p > 2 && m[1] >= p) {
			tot++;
			m[1] -= p;
		}
		while(p > 2 && m[p - 1] >= p) {
			tot++;
			m[p - 1] -= p;
		}
		tot += (m[1] + m[2] + m[3] > 0);
		printf("Case #%d: %d\n", tt, tot);
	}
}
