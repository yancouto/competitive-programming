#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int K = 13;
const int ME = 1594323+7;
const int N = (1<<K);

int p[K];
char adj[K+2][K+2];
int n, s, t;

int memo[ME];
bitset<ME> visi;

int to_3[N];
int pop[N];
int neigh[N];
vector<int> av_masks[N];

int pd (int ma, int mb) {
	int mem_p = to_3[ma] + 2*to_3[mb];
	int & me = memo[mem_p];
	if (visi[mem_p])
		return me;
	visi[mem_p] = 1;

	int used = (ma|mb);
	bool can_he = 0;
	me = INT_MIN;
	
	for (int mc : av_masks[used]) {
		if (pop[ma&neigh[mc]] > pop[mc] + pop[mb&neigh[mc]])
			me = max(-pd(mb, ma|mc), me);
		can_he |= pop[mb&neigh[mc]] > pop[mc] + pop[ma&neigh[mc]];
	}

	if (me == INT_MIN) { // nao consegui jogar, ele consegue?
		if (!can_he)
			me = pop[ma] - pop[mb];
		else
			me = -pd(mb, ma);
	}

	return me;
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("battle.in", "r", stdin);
	freopen("battle.out", "w", stdout);
#endif

	scanf("%d %d %d", &n, &s, &t);
	s--; t--;
	for (int i = 0; i < n; i++)
		scanf(" %s", adj[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &p[i]);

	pop[0] = 0;
	for (int mask = 1; mask < N; mask++) {
		for (int ava = 1; ava < N; ava++) {
			if (mask&ava) continue;
			av_masks[mask].pb(ava);
		}

		for (int i = 0; i < n; i++) {
			if (mask&(1<<i)) {
				pop[mask] = pop[mask - (1<<i)] + p[i];
				neigh[mask] = neigh[mask - (1<<i)];

				for (int j = 0; j < n; j++)
					if (adj[i][j] == '1')
						neigh[mask] |= (1<<j);
				break;
			}
		}

		int cur = 1;
		for (int i = 0; i < n; i++) {
			if (mask&(1<<i))
				to_3[mask] += cur;
			cur *= 3;
		}
	}

	printf("%d\n", pd((1<<s),(1<<t)));
}

