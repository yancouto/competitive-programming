#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef unsigned short us;
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

const int N = 1e4+7;
const int M = 1e6+8;
int n;
int w;

string s[N];
int pr[N];
int curr, lvl;
int hd[N], to[N], nx[N], es;
us sz[N];
char str[M];
us ch[N], acc[N], qt[N];
int fr[N];

us memo[N][N];
bitset<N> visi[N];

void dfs (int ed) {
	if (ed == 0) return;

	dfs(hd[to[ed]]);
	dfs(nx[ed]);
	
	sz[pr[to[ed]]] += sz[to[ed]] + 1;
	qt[ed] = qt[nx[ed]] + 1;
	acc[ed] = acc[nx[ed]] + 1 + sz[to[ed]];
}

us pd (int ed, us x) {
	if (x < 0) return n+1;
	if (!ed) return 0;

	us & me = memo[ed][x];
	if (visi[ed][x])
		return me;
	visi[ed][x] = 1;

	int u = to[ed];

	me = pd(hd[u], w-1-ch[to[ed]]) + pd(nx[ed], x) + 1;

	for (us y = max(int(ch[to[ed]]), int(qt[nx[ed]]) - acc[nx[ed]] + x); y <= sz[to[ed]]; y++) {
		us loc = pd(hd[to[ed]], int(y)-ch[to[ed]]) + pd(nx[ed], x-y);
		if (loc < me) {
			me = loc;
		}
	}
	
	return me;
}

int cl[N];

build (int ed, us x) {
	if (x < 0) return;
	if (!ed) return;

	me = pd(ed, x);
	if (me == pd(hd[u], w-1-ch[to[ed]]) + pd(nx[ed], x) + 1) {
	
	}

	for (us y = max(int(ch[to[ed]]), int(qt[nx[ed]]) - acc[nx[ed]] + x); y <= sz[to[ed]]; y++) { 
		us loc = pd(hd[to[ed]], int(y)-ch[to[ed]]) + pd(nx[ed], x-y);
		if (me == loc)
	}
}

int main() {
	scanf("%d ", &w);

	n = 0;
	while(fgets(str, sizeof str, stdin) && !feof(stdin)) { 
		s[n++] = str;
	}
	
	curr = -1;
	es = 2;
	for (int i = 0; i < n; i++) {
		if (s[i].size() > lvl*2 && (s[i][lvl*2] == '-' || s[i][lvl*2] == '.')) {
			pr[i] = curr;
			if (curr >= 0) {
				nx[es] = hd[curr]; to[es] = i; hd[curr] = es++;
				ch[curr]++;
			}
			bool b = (s[i][lvl*2] == '-');
			s[i] = s[i].substr(lvl*2+1, s[i].size() - (lvl*2+2));
			if (b) {
				lvl++;
				curr = i;
			}
		} else {
			lvl--;
			curr = pr[curr];
			i--;
		}
	}

	to[1] = 0;
	nx[1] = 0;
	dfs(1);
	for (int i = 0; i < n; i++) {
		sz[i]++;
	}

	for (int ed = 1; ed < es; ed++) {
		printf("%s : qt=%d acc=%d\n", s[to[ed]].c_str(), qt[ed], acc[ed]);
	}

	printf("%d\n", (int) pd(1,w-1)+1);
}
