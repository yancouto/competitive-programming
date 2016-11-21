#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 17;

int n;
vector<int> v[N];

void printa (int k, int i) {
	printf("%d ", k);
	int s = i;
	while (i) {
		if (i&1)
			putchar('1');
		else
			putchar('0');
		i >>= 1;
	}
	printf(" : %d\n", s);
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < (1<<n); i++) {
		bool ok = 1;
		int k;
		for (k = 0; ok; k++) {
			ok = 0;
			for (int j : v[k]) {
				if (__builtin_popcount(j^i) <= 2) {
					ok = 1;
					break;
				}
			}
		}
		v[--k].push_back(i);
		printa(k, i);
	}
}
