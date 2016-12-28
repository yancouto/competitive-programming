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

const int N = 1000009;
bitset<1001> b[N];
bool any[N];
int a[1123];

int main() {
	int i, j, k;
	rd(n); rd(k);
	for(i = 0; i < n; i++) rd(a[i]);
	sort(a, a + n);
	n = unique(a, a + n) - a;
	b[0][0] = 1;
	any[0] = true;
	for(i = 1; i <= a[n - 1] * k; i++) {
		for(j = 0; j < n; j++)
			if(i - a[j] >= 0 && any[i - a[j]])
				b[i] |= (b[i - a[j]] << 1);
		any[i] = b[i].any();
		if(b[i][k]) printf("%d ", i);
	}
	putchar('\n');
}
