#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

const int N = 212345;

int a[N], l[N], r[N], t[N], b[N];

int main() {
	int i, j;
	int n, m, q;
	rd(n); rd(q); rd(m);
	for(i = 0; i < n; i++) rd(a[i]);
	for(i = 0; i < q; i++) {
		rd(t[i]); rd(l[i]); rd(r[i]);
	}
	for(i = 0; i < m; i++) rd(b[i]);
	while(q--) {
		for(i = 0; i < m; i++) {
			if(b[i] < l[q] || b[i] > r[q]) continue;
			if(t[q] == 1) {
				if(b[i] == l[q]) b[i] = r[q];
				else b[i]--;
			} else {
				b[i] = r[q] - (b[i] - l[q]);
			}
		}
	}
	for(i = 0; i < m; i++) printf("%d ", a[b[i] - 1]);
	putchar('\n');
}
