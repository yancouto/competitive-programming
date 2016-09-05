#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int p[5] = {1, 5, 10, 20, 50};
int m[5];

int main() {
	int i, j, n, f, x;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &f);
		int tot = 0;
		for(j = 0; j < 5; j++) {
			scanf("%d", &x);
			m[j] += x;
			tot += x * p[j];
		}
		int ch = tot - f;
		for(j = 4; j >= 0; j--)
			while(p[j] <= ch && m[j]) {
				ch -= p[j];
				m[j]--;
			}
		if(ch) { puts("no"); return 0; }
	}
	puts("yes");
}
