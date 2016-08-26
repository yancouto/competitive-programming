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
const int N = 110;
int a[N], b[N];

int main() {
	int i, j, n, x;
	for_tests(t, tt) {
		scanf("%d", &n);
		int *v = a, *w = b;
		int tot = 0;
		for(i = 0; i < n; i++) {
			swap(v, w);
			scanf("%d", &x);
			j = 0;
			if(x) {
				do
					w[j] = v[j];
				while(v[j++] != x);
				tot += min(j, i - j);
			}
			w[j++] = i + 1;
			for(; j < i + 1; j++)
				w[j] = v[j - 1];
		}
		printf("%d\n", tot);
	}
}
