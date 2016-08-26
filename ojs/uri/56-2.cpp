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

int a[300];
int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		int i, mi = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			if(a[i] < a[mi]) mi = i;
		}
		printf("%d\n", mi + 1);
	}
	return 0;
}
