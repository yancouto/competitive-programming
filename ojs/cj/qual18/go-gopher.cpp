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

int mrk[209][5];

int main() {
	for_tests(tn, tt) {
		memset(mrk, 0, sizeof mrk);
		scanf("%*d");
		for(int i = 0; ; i++) {
			int ct = 0;
			while(true) {
				printf("%d 2\n", 2 + i * 3); fflush(stdout);
				int a, b;
				scanf("%d %d", &a, &b);
				if(a == 0 && b == 0) goto out;
				if(a == -1 && b == -1) return 0;
				if(!mrk[a][b]) mrk[a][b] = 1, ct++;
				if(ct == 9) break;
			}
		}

out: ;
	}
}
