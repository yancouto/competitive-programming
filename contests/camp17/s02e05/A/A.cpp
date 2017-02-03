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


const int N = 104;

char str[N][N];
bool ps[N][N];
int n, m;
char mvv[5*N];

int get (int l, int c) {
	if (l < 0 || l >= n) return 0;
	if (c < 0 || c >= m) return 0;

	int res = str[l][c] - '0';
	if (ps[l][c])
		res /= 2;
	ps[l][c] = 1;
	return res;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)
		scanf(" %s", str[i]);

	int dr = 0;
	

	scanf(" %s", mvv);
	int l = 0, c = 0;
	int tot = 0;

	for (int i = 0; mvv[i]; i++) {
		if (mvv[i] == 'R')
			dr = (dr+1)%4;
		else if (mvv[i] == 'L')
			dr = (dr+3)%4;
		else {
			if (dr == 0) {
				tot += get(l,c) + get(l-1, c);
				c++;
			} else if (dr == 1) {
				tot += get(l,c) + get(l,c-1);
				l++;
			} else if (dr == 2) {
				tot += get(l, c-1) + get(l-1,c-1);
				c--;
			} else {
				tot += get(l-1,c-1) + get(l-1,c);
				l--;
			}
		}
	}

	printf("%d\n", tot);
}
