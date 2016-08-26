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

int used[100009], tempo;
int main() {
	int i, n, k, x;
	while(scanf("%d %d", &k, &n) != EOF) {
		tempo++;
		scanf("%d", &x);
		printf("%d", x);
		used[x] = tempo;
		for(i = 1; i < k; i++) {
			scanf("%d", &x);
			if(used[x] != tempo) printf(" %d", x);
			used[x] = tempo;
		}
		putchar('\n');
	}
	return 0;
}
