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

char s[1123456];
int ans[1123456];
int z[1123456];
int main() {
	int i, j, n;
	for_tests(t, tt) {
		scanf("%d %s", &n, s);
		int l = 0, r = 0;
		for(i = 1; i < n; i++) {
			if(i > r) {
				for(l = i, r = i - 1; r + 1 < n && s[r + 1] == s[r + 1 - l]; r++);
				z[i] = r - l + 1;
				continue;
			}
			int k = i - l;
			if(i + z[k] - 1 < r) z[i] = z[k];
			else {
				for(l = i; r + 1 < n && s[r + 1] == s[r + 1 - l]; r++);
				z[i] = r - l + 1;
			}
		}
		for(i = 1; i <= n; i++) ans[i] = 1;
		for(i = 1; i <= n; i++)
			for(j = i; j < n && z[j] >= i; j += i)
				ans[j+i] = max(ans[j+i], (j+i) / i);
		printf("Test case #%d\n", tt);
		for(i = 1; i <= n; i++)
			if(ans[i] > 1)
				printf("%d %d\n", i, ans[i]);
		printf("\n");
	}
}
