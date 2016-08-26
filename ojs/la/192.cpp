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
const int MAX = 200009;
int n, a[MAX], bit[MAX];
int get(int i) {
	int sum = 0; i += 2;
	while(i) {
		sum += bit[i];
		i -= (i & -i);
	}
	return sum;
}
void add(int i, int x) {
	i += 2;
	while(i < MAX) {
		bit[i] += x;
		i += (i & -i);
	}
}

int main() {
	int i, t = 0, x, y; char op;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		if(t > 0) putchar('\n');
		memset(bit, 0, sizeof bit);
		for(i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			add(i, a[i]);
		}
		printf("Case %d:\n", ++t);
		while(true) {
			scanf(" %c", &op);
			if(op == 'E') { scanf("%*s "); break; }
			scanf(" %d %d", &x, &y);
			if(op == 'S') { add(x, y - a[x]); a[x] = y; }
			else printf("%d\n", get(y) - get(x - 1));
		}
	}
}
