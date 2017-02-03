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

const int N = 3e4+7;

int n;
int x[N];
int a[N][2], r[N], p[N], c[N];
map<int, int> uf;

int cmp_t (int i, int j) {
	if (r[i] != r[j]) return r[i] < r[j];
	return c[i] < c[j];
}

void create (int u) {
	if (uf.find(u) == uf.end())
		uf[u] = u;
}

int find (int u) {
	if (uf[u] == u) return u;
	return uf[u] = find(uf[u]);
}

int join (int u, int v) {
	if ((u = find(u)) == (v = find(v)))
		return 0;
	uf[u] = v;
	return 1;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &a[i][0], &a[i][1], &r[i], &c[i]);
		p[i] = i;
	}

	sort(p, p+n, cmp_t);

	ll res = 0;

	for (int _i = n-1; _i >= 0; _i--) {
		int i = p[_i];
		create(a[i][0]); create(a[i][1]);
		
		if (join(a[i][0], a[i][1])) {
			x[i] = 1;
			res += c[i];
		}
	}

	printf("%lld\n", res);
	for (int _i = 0; _i < n; _i++) {
		int i = p[_i];

		printf("%d ", i+1);
	}
	printf("\n");
}
