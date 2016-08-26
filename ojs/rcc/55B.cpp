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

int a[112345], b[112345];
int main() {
	int i, n; char c;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) { scanf(" %c", &c); a[i] = (c == '1'); }
		for(i = 0; i < n; i++) { scanf(" %c", &c); b[i] = (c == '1'); }
		int tot = 0;
		for(i = 0; i < n - 1; i++)
			if(a[i] != b[i])
				a[i] = !a[i], a[i + 1] = !a[i + 1], tot++;
		if(a[n - 1] == b[n - 1]) printf("%d\n", tot);
		else puts("-1");
	}
}
