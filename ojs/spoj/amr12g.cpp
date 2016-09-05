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

int ct[100];
int main() {
	int i, j, n, m, k; char c;
	for_tests(t, tt) {
		scanf("%d %d %d", &n, &m, &k);
		int all = 0;
		for(i = 0; i < n; i++) {
			ct[i] = 0;
			for(j = 0; j < m; j++) scanf(" %c", &c), ct[i] += (c == '*');
			all += ct[i];
			ct[i] = m - 2*ct[i];
		}
		sort(ct, ct + n, greater<int>());
		for(i = 0; k > 0 && i < n && ct[i] > 0; i++)
			all += ct[i], k--, ct[i] = -ct[i];
		if(k > 0) {
			sort(ct, ct + n, greater<int>());
			k &= 1;
			if(k) all += ct[0];
		}
		printf("%d\n", all);
	}
}
