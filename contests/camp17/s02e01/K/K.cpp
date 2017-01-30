#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
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


const ll MOD = 99990001;

const int N = 4e5+7;
int n;
ll x[N], y[N], w[N];
int cor[N], nc;
ll lz[N];
int b[N], es;
ll vs[N], hd[N], nx[N], to[N], idx[N], turn;

ll get (ll & ed) {
	if (!ed || !b[ed]) return ed;
	return ed = get(nx[ed]);
}

void paint (int u, int c, ll mm) {
	cor[u] = c;
	for (ll ed = get(hd[u]); ed; ed = get(nx[ed])) {
		if (cor[to[ed]] == c) continue;
		w[idx[ed]] = (((w[idx[ed]] + lz[cor[to[ed]]])%MOD)*mm)%MOD;
		paint(to[ed], c, mm);
	}
}

void sep (int k) {
	b[2*k+2] = b[2*k+3] = 1;
	int tr = 0;
	queue<int> qu[2];

	qu[0].push(get(hd[x[k]]));
	qu[1].push(get(hd[y[k]]));
	ll mn[2] = {x[k], y[k]};

	turn++;
	vs[x[k]] = vs[y[k]] = turn;

	while (qu[tr].size()) {
		int ed = qu[tr].front();
		qu[tr].pop();

		if (!ed) continue;
		qu[tr].push(get(nx[ed]));

		if (vs[to[ed]] == turn) continue;
		mn[tr] = min(to[ed], mn[tr]);
		vs[to[ed]] = turn;
		qu[tr].push(get(hd[to[ed]]));
		
		tr = !tr;
	}

	int ok = 1;
	while (ok && qu[!tr].size()) {
		int ed = qu[!tr].front();
		qu[!tr].pop();

		if (!ed) continue;
		qu[!tr].push(get(nx[ed]));
		if (vs[to[ed]] == turn) continue;
		ok = 0;
	}

	if (ok && !tr) {
		if (mn[0] > mn[1])
			tr = 1;
	}
	if (tr) {
		swap(x[k], y[k]);
	}
	w[k] = (w[k] + lz[cor[x[k]]])%MOD;
	paint(x[k], nc++, w[k]);
	lz[cor[y[k]]] = (lz[cor[y[k]]] + w[k])%MOD;
}

int main() {
	int i, j;
	rd(n);

	es = 2;
	for (int i = 0; i < n-1; i++) {
		scanf("%lld %lld %lld", &x[i], &y[i], &w[i]);
		x[i]--; y[i]--;
		to[es] = y[i]; idx[es] = i; nx[es] = hd[x[i]]; hd[x[i]] = es++;
		to[es] = x[i]; idx[es] = i; nx[es] = hd[y[i]]; hd[y[i]] = es++;
	}

	nc = 1;
	for (int i = 0; i < n-1; i++) {
		int p;
		scanf("%d", &p);
		p--;
		printf("%lld\n", (w[p]+lz[cor[x[p]]])%MOD);
		fflush(stdout);
		sep(p);
	}
}
