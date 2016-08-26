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

int g(int a) {
	return (24 + 240 + 2400 + 24000 + 240000) * a;
}

int main() {
	int k, a, b, c, d, e;
	for_tests(t, tt) {
		scanf("%d", &k);
		bool any = false;
		for(a = 0; a <= 9; a++)
			for(b = a + 1; b <= 9; b++)
				for(c = b + 1; c <= 9; c++)
					for(d = c + 1; d <= 9; d++)
						for(e = d + 1; e <= 9; e++)
							if(g(a) + g(b) + g(c) + g(d) + g(e) == k)
								printf("{%d,%d,%d,%d,%d}\n", a, b, c, d, e), any = true;
		if(!any) puts("impossivel");
		putchar('\n');
	}
}
