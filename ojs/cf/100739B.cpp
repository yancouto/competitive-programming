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
int a[112345];
int b[320][320];

int main() {
	int i, j, q;
	rd(n);
	rd(q);
	for(i = 0; i < n; i++) rd(a[i]);
	for(i = 1; i < 320; i++)
		for(j = 0; j < n; j++)
			b[i][j % i] += a[j];
	while(q--) {
		pii q;
		scanf("%d %d", &q.snd, &q.fst);
		int x = 0;
		if(q.fst < 320) x = b[q.fst][q.snd];
		else
			for(i = q.snd; i < n; i += q.fst)
				x += a[i];
		printf("%d\n", x);
	}
}
