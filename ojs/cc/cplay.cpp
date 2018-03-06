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

char s[100];
int a[100], b[100];

int main() {
	int i;
	while(scanf("%s", s) != EOF) {
		for(i = 0; i < 10; i++)
			a[i] = s[2 * i] - '0',
			b[i] = s[2 * i + 1] - '0';
		if(accumulate(a, a + 5, 0) == accumulate(b, b + 5, 0)) {
			for(i = 0; i < 5; i++) {
				if(a[5 + i] && !b[5 + i]) {
					printf("TEAM-A %d\n", 10 + 2 * i + 2);
					break;
				} else if(!a[5 + i] && b[5 + i]) {
					printf("TEAM-B %d\n", 10 + 2 * i + 2);
					break;
				}
			}
			if(i == 5)
				printf("TIE\n");
		} else {
			int pa = 0, pb = 0;
			for(i = 0; i < 5; i++) {
				pa += a[i];
				if(pb + (5 - i) < pa) {
					printf("TEAM-A %d\n", 2 * i + 1);
					break;
				}
				if(pa + (4 - i) < pb) {
					printf("TEAM-B %d\n", 2 * i + 1);
					break;
				}
				pb += b[i];
				if(pa + (4 - i) < pb) {
					printf("TEAM-B %d\n", 2 * i + 2);
					break;
				}
				if(pb + (4 - i) < pa) {
					printf("TEAM-A %d\n", 2 * i + 2);
					break;
				}
			}
		}
	}
}
