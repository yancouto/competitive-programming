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
	for_tests(t, tt) {
		int n, m;
		scanf("%d %d", &n, &m);
		scanf("%s", s);
		int mni = 0, mxi = 0, mnj = 0, mxj = 0;
		int i = 0, j = 0;
		for(int k = 0; s[k]; k++) {
			if(s[k] == 'U') i--;
			else if(s[k] == 'D') i++;
			else if(s[k] == 'L') j--;
			else j++;
			mni = min(mni, i);
			mxi = max(mxi, i);
			mnj = min(mnj, j);
			mxj = max(mxj, j);
		}
		if(mxi - mni + 1 <= n && mxj - mnj + 1 <= m) puts("safe");
		else puts("unsafe");
	}
}
