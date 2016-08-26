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

char s[100009];
int main() {
	for_tests(t, tt) {
		int d, i;
		scanf("%s", s);
		scanf("%d", &d);
		int n = strlen(s);
		if(((n - d) & 1) == 0)
			for(i = 0; i < (d - 1) / 2; i++)
				swap(s[i], s[(d - 1)  - 1 - i]);
		for(i = d - 1; i < n; i++)
			putchar(s[i]);
		for(i = 0; i < d - 1; i++)
			putchar(s[i]);
		putchar('\n');
	}
}
