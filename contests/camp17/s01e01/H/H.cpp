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

template<class num> inline void read(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

const int N = 2e5 + 7;

int n;
int br[2*N];
map<pii, int> mp;
int gr[N];
int hd[N], nx[N], to[N], es;
int visi[N], turn;
int sz[2*N];

int get (int ed) {
	if (!ed || !br[ed]) return ed;
	return nx[ed] = get(nx[ed]);
}

void paint (int u, int c) {
	if (visi[u] == turn)
		return;
	visi[u] = turn;
	sz[gr[u]]--;
	sz[c]++;
	gr[u] = c;

	for (int ed = get(hd[u]); ed; ed = get(nx[ed]))
		paint(to[ed], c);
}

struct node {
	int u, ed;

	node (int x, int e) : u(x), ed(e) {}
};

int main () {
	scanf("%d", &n);

	int nc = 0;

	for (int i = 0; i < n; i++) {
		sz[nc] = 1;
		gr[i] = nc++;
	}
	
	es = 2;
	while (true) {
		char c;
		int a, b;
		scanf(" %c", &c);

		if (c == 'E') return 0;

		scanf("%d %d", &a, &b);
		a--;b--;
		if (a > b) swap(a,b);
		if (c == 'C') {
			mp[pii(a,b)] = es;

			if (sz[gr[a]] > sz[gr[b]])
				swap(a, b);

			turn++;
			paint(a, gr[b]);

			nx[es] = hd[a]; to[es] = b; hd[a] = es++;
			nx[es] = hd[b]; to[es] = a; hd[b] = es++;
		} else if (c == 'T') {
			if (gr[a] == gr[b])
				printf("YES\n");
			else
				printf("NO\n");
			fflush(stdout);
		} else {
			int cr = mp[pii(a,b)];
			br[cr] = br[cr+1] = 1;

			queue<node> qu[2];
			int k = 0;

			qu[0].push(node(a, hd[a]));
			qu[1].push(node(b, hd[b]));

			turn++;
			while (!qu[k].empty()) {
				node att = qu[k].front();
				qu[k].pop();

				visi[att.u] = turn;

				int ed = get(att.ed);
				if (ed == 0) continue;
				int u = to[ed];

				if (visi[u] != turn)
					qu[k].push(node(u, hd[u]));
				qu[k].push(node(att.u, nx[ed]));

				k = !k;
			}

			turn++;
			if (k) swap(a,b); // a é sempre menor
			paint(a, nc++);
		}
	}
}
