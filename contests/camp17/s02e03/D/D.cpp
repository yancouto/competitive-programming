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

int n, m;
const int N = 1e3+7;

int hd[N], to[2*N], nx[2*N], es;
int memo[N][N];
int dist[N];

int pd (int i, int u) {
	if (dist[u] < i) return 0;
	
	int & me = memo[i][u];
	if (me != -1) return me;

	me = 0;
	for (int ed = hd[u]; ed; ed = nx[ed]) {
		if (dist[to[ed]] <= i) continue;
		if (!pd(i+1, to[ed])) me = 1;
	}
	return me;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	memset(memo, -1, sizeof memo);
	scanf("%d %d", &n, &m);
	es = 2;
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		nx[es] = hd[a]; to[es] = b; hd[a] = es++;
		nx[es] = hd[b]; to[es] = a; hd[b] = es++;
	}

	for (int i = 0; i < n; i++)
		dist[i] = n+2;

	queue<int> qu;
	qu.push(0);
	dist[0] = 0;

	while (!qu.empty()) {
		int u = qu.front();
		qu.pop();

		for (int ed = hd[u]; ed; ed = nx[ed]) {
			if (dist[to[ed]] > dist[u] + 1) {
				dist[to[ed]] = dist[u] + 1;
				qu.push(to[ed]);
			}
		}
	}

	if (!pd(0,0))
		printf("Nikolay\n");
	else
		printf("Vladimir\n");
	
}
