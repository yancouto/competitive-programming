#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;

int n;

ll value(vector<int> &v) {
	ll p = 1;
	ll va = 0;
	for(int i = 0; i < n; i++) {
		va += p * v[i];
		p *= 10ll;
	}
	return va;
}

void minimize(vector<int> &v) {
	vector<int> seen(10, 0);
	int tempo = 0;
	for(int i = 0; i < n; i++) {
		if(seen[v[i]] == 0) seen[v[i]] = ++tempo;
		v[i] = seen[v[i]] - 1;
	}
}

unordered_map<ll, int> mp;

const int N = 11;
int adj2[123456][N][N];

int build(vector<int> &v) {
	minimize(v);
	ll va = value(v);
	if(mp.count(va)) return mp[va];
	int vvv = mp[va] = mp.size();
	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++) {
			if(v[i] == v[j]) continue;
			vector<int> v2 = v;
			int x = v[i];
			for(int k = 0; k < n; k++)
				if(v2[k] == x)
					v2[k] = v[j];
			adj2[vvv][i][j] = build(v2);
		}
	}
	return vvv;
}

int adj[N][N];
double dp[60][123456];
vector<pii> es;

int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &adj[i][j]);
	vector<int> v;
	for(i = 0; i < n; i++) v.pb(i);
	build(v);
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			es.pb(pii(i, j));
	sort(es.begin(), es.end(), [](pii a, pii b) { return adj[a.fst][a.snd] < adj[b.fst][b.snd]; });
	int en = es.size();
	int mps = mp.size(), s;
	for(i = en - 1; i >= 0; i--)
		for(s = 1; s <= mps; s++) {
			if(adj2[s][es[i].fst][es[i].snd] == 0) dp[i][s] = dp[i + 1][s];
			else {
				dp[i][s] = (dp[i + 1][s] + dp[i + 1][adj2[s][es[i].fst][es[i].snd]] + adj[es[i].fst][es[i].snd]) / 2.;
			}
		}
	printf("%.20f\n", dp[0][1]);
}
