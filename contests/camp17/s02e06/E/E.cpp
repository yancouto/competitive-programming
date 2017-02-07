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

struct st {
	int a, b;
	int c;
};

const int N = 412;
int seen[N][N][30], t;
int dist[N][N][30];
st p[N][N][30];

vector<pii> adj[N];
vector<int> rev[N][30];

void build(st x) {
	if(seen[x.a][x.b][x.c] != t) {
		puts("-1");
		return;
	}
	string s;
	//printf("(%d, %d, %d)\n", x.a, x.b, x.c);
	printf("%d ", dist[x.a][x.b][x.c]);
	for(int i = dist[x.a][x.b][x.c]; i > 1; i--) {
		x = p[x.a][x.b][x.c];
		if(x.c < 26) s += char('a' + x.c);
	}
	x = p[x.a][x.b][x.c];
	string t = s;
	reverse(t.begin(), t.end());
	if(x.c + 'a' <= 'z') s += char('a' + x.c);
	s += t;
	printf("%s\n", s.c_str());
}

void go() {
	queue<st> q;
	++t;
	for(int i = 0; i < n; i++)
		for(int k = 0; k <= 26; k++)
			if(k == 26 || !rev[i][k].empty())
				q.push({i, i, k}),
				dist[i][i][k] = 0,
				seen[i][i][k] = t;
	while(!q.empty()) {
		st x = q.front(); q.pop();
		//printf("dist[%d, %d, %d] = %d\n", x.a, x.b, x.c, dist[x.a][x.b][x.c]);
		if(x.c == 26) {
			for(pii p : adj[x.b])
				if(seen[x.a][p.fst][p.snd] != t) {
					st y = {x.a, p.fst, p.snd};
					seen[y.a][y.b][y.c] = t;
					dist[y.a][y.b][y.c] = dist[x.a][x.b][x.c] + 1;
					::p[y.a][y.b][y.c] = x;
					q.push(y);
				}
		} else {
			for(int z : rev[x.a][x.c])
				if(seen[z][x.b][26] != t) {
					st y = {z, x.b, 26};
					seen[y.a][y.b][y.c] = t;
					dist[y.a][y.b][y.c] = dist[x.a][x.b][x.c] + 1;
					p[y.a][y.b][y.c] = x;
					q.push(y);
				}
		}
	}
}

int main() {
	int i, j, a, b, m; char c;
	rd(n); rd(m);
	for(i = 0; i < m; i++) {
		rd(a); rd(b); scanf(" %c", &c); a--; b--;
		adj[a].pb(pii(b, c - 'a'));
		rev[b][c - 'a'].pb(a);
	}
	go();
	int d; rd(d); a = -1;
	for(i = 0; i < d; i++) {
		rd(b); b--;
		if(a != -1) build({a, b, 26});
		swap(a, b);
	}
}
