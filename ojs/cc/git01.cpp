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

int main() {
	for_tests(tn, tt) {
		int i, j, n, m; char c;
		scanf("%d %d" , &n, &m);
		int c1 = 0, c2 = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				scanf(" %c", &c);
				if(((i + j) & 1) && c == 'R') c1 += 5;
				if(!((i + j) & 1) && c != 'R') c1 += 3;
				if(((i + j) & 1) && c != 'R') c2 += 3;
				if(!((i + j) & 1) && c == 'R') c2 += 5;
			}
		printf("%d\n", min(c1, c2));
	}
}
