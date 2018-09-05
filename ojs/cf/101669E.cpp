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

inline int get_note() {
	char a;
	while(isspace(a = getchar()));
	char b = getchar();
	char c = getchar();
	if(a == 'D') return 0 + (c == '#');
	if(a == 'R') return 2 + (c == '#');
	if(a == 'M') return 4;
	if(a == 'F') return 5 + (c == '#');
	if(a == 'L') return 9 + (c == '#');
	if(b == 'o') return 7 + (getchar() == '#');
	return 11;
}

int n;

int ok[12][12];
const int N = 10000001;
char a[N];

int nx[12][N];
int best[N];

int solve(int l, int r) {
	int ct = 0;
	while(l <= r) {
		ct++;
		l = best[l];
	}
	return ct;
}

int main() {
	int i, j;
	rd(n);
	for(i = 0; i < n; i++) {
		a[i] = get_note(), best[i] = i;
	}
	for(i = 0; i < 12; i++)
		for(int j : {0, 2, 4, 5, 7, 9, 11})
			ok[i][(i + j) % 12] = 1;
	for(j = 0; j < 12; j++) {
		nx[j][n] = n;
		for(i = n - 1; i >= 0; i--) {
			if(!ok[j][a[i]])
				nx[j][i] = i;
			else
				nx[j][i] = nx[j][i + 1];
			best[i] = max(best[i], nx[j][i]);
		}
	}
	int best = INT_MAX;
	for(j = 0; j < 12; j++) {
		int r = n - 1;
		while(r >= 0 && nx[j][r] == n) r--;
		best = min(best, 1 + solve(nx[j][0], r));
	}
	printf("%d\n", best);
}
