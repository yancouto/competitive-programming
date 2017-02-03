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

const int N = 1e2+7;

int b[N], pr[N], v[N];
int n, f;

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d %d", &n, &f);

	for (int i = 0; i < n; i++) {
		scanf("%d", &v[i]);
		pr[v[i]] = 1;
	}
	
	for (int i = 0; i < n; i++) {
		if (b[v[i]]) continue;
		while (f != v[i]) {
			b[f] = 1;
			if (v[i] < f) f--;
			else f++;
			if (pr[f] && !b[f])
				printf("%d ", f);
		}
	}
	printf("\n");
}
