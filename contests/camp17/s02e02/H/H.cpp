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

const int N = 5e5+7;

int n, m, k, t;

int bit[N];


void add (int i, int x) {
	for (i += 2; i < N; i+=(i&-i))
		bit[i] += x;
}

int get (int i) {
	int x = 0;
	for (i += 2; i > 0; i-=(i&-i))
		x += bit[i];
	return x;
}

int solve (int k, int z) {
	int x = -get(k);
	if (k + z > n) {
		x += get(n);
		x += get((k+z-1)%n + 1);
	} else {
		x += get(k+z);
	}
	return z - x;
}

int getnext (int k) {
	int jmp = (m-1)%t + 1;
	int lo = jmp;
	int hi = n;

	while (lo < hi) {
		int mid = (lo+hi)/2;
		if (solve(k,mid) >= jmp)
			hi = mid;
		else
			lo = mid+1;
	}
	return (k + lo - 1)%n + 1;
}

int main() {
	scanf("%d %d %d", &n, &m, &k);
	t = n;
	
	int p = 0;
	int r = 1;
	while ((p = getnext(p)) != k) {
		add(p, 1);
		t--;
		r++;
	}

	printf("%d\n", r);
}
