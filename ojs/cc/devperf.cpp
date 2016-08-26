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
	int i, j, n, m; char c;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		int mni = INT_MAX, mxi = INT_MIN;
		int mnj = INT_MAX, mxj = INT_MIN;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				scanf(" %c", &c);
				if(c != '*') continue;
				mni = min(mni, i); mnj = min(mnj, j);
				mxi = max(mxi, i); mxj = max(mxj, j);
			}
		if(mni == INT_MAX) { puts("0"); continue; }
		printf("%d\n", (max(mxi - mni, mxj - mnj) + 1) / 2 + 1);
	}
}
