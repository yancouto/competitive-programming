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
int fs[100009][2], fn;

int main() {
	int n, i, j, x, y, t = 0; char s1[20], s2[20];
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		fn = 0;
		scanf("%d", &x);
		fs[fn][0] = fs[fn++][1] = x;
		for(i = 1; i < n; i++) {
			scanf("%d", &x);
			if(x == fs[fn - 1][1] + 1) fs[fn - 1][1]++;
			else fs[fn][0] = fs[fn++][1] = x;
		}
		printf("Case %d:\n", ++t);
		for(i = 0; i < fn; i++) {
			x = fs[i][0]; y = fs[i][1];
			if(x == y) printf("0%d\n", x);
			else {
				sprintf(s1, "%d", x);
				sprintf(s2, "%d", y);
				for(j = 0; s1[j] == s2[j]; j++);
				printf("0%d-%s\n", x, s2 + j);
			}
		}
		putchar('\n');
	}
}
