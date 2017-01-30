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
#	define debug(args...) {}
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

int n;

ll acc[1123];
const int N = 112345;
int l[N], r[N];

main() {
	int i, j, m, s, a, b;
	rd(n); rd(m);
	ll res = LLONG_MAX;
	rd(a); rd(b);
	for(i = 0; i < n; i++) rd(l[i]), rd(r[i]), l[i]--, r[i]--;
	for(s = 0; s < a; s++) {
		memset(acc, 0, sizeof acc);
		for(i = -s; i < n; i += a) {
			int mn = INT_MAX, mx = -1;
			for(j = 0; j < a; j++) {
				int li = j + i;
				if(li < 0) continue;
				if(li >= n) continue;
				mn = min(mn, l[li]);
				mx = max(mx, r[li]);
			}
			int k = (mx / b) - (mn / b) + 1;
			acc[0] += k;
			acc[(mn % b) + 1]++;
			acc[(mx % b) + 1]--;
		}
		ll bad = 0;
		for(i = 0; i < b; i++) {
			bad += acc[i];
			res = min(res, bad);
		}
	}
	printf("%lld\n", res);
}
