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

char s1[200], s2[200], c;
int main() {
	int x, y;
	for_tests(t, tt) {
		scanf("%s %c%*s %s %*s %d %d", s1, &c, s2, &x, &y);
		if(((x + y) & 1) == (c == 'I')) puts(s1);
		else puts(s2);
	}
}
