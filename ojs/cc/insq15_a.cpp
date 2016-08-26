#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

char s[5000009];
int z[5000009];

int main() {
	int i, q, p;
	scanf("%s %d", s, &q);
	int n = strlen(s);
	int l = 0, r = 0;
	for(i = 1; i < n; i++) {
		if(r < i) {
			l = r = i;
			while(r < n && s[r] == s[r - l]) r++;
			z[i] = (r--) - l;
			continue;
		}
		int k = i - l;
		if(z[k] < r - i + 1) { z[i] = z[k]; continue; }
		l = i;
		while(r < n && s[r] == s[r - l]) r++;
		z[i] = (r--) - l;
	}
	for(i = 0; i < q; i++) {
		scanf("%d", &p);
		printf("%d\n", min(z[p], p));
	}
}
