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

char s[10009];
int main() {
	int i;
	for_tests(t, tt) {
		printf("Case #%d: ", tt);
		scanf("%s", s);
		int tot = 0;
		for(i = 1; s[i]; i++)
			if(s[i] != s[i - 1])
				tot++;
		if(s[i - 1] != '+') tot++;
		printf("%d\n", tot);
	}
}
