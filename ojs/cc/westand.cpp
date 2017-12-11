#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 1123;

int n;
int D[N], M[N];

typedef double ld;

struct req {
	ld lf;
	int ct;
	req(){}
	req(ld a, int x) : lf(a), ct(x) {}
	bool operator < (req o) const { return lf > o.lf; }
};

bool near(ld a, ld b) {
	return abs(a - b) <= 1e-8;
}

int qt[N], tot[N];

bool ok(vector<int> ch) {
	sort(ch.begin(), ch.end(), greater<int>());
	//printf("Trying:");
	//for(int x : ch) printf(" %d", x);
	//putchar('\n');
	int i;
	vector<req> rs;
	for(int t = 100; t >= 1; t--) {
		for(i = 0; i < n; i++)
			if(t == M[i])
				rs.pb(req(D[i], 1));
		ld sec = 1;
		while(sec > 1e-9) {
			ld dur = sec;
			sort(rs.begin(), rs.end());
			while(!rs.empty() && rs.back().lf < 1e-9) rs.pop_back();
			int j = 0;
			for(i = 1; i < rs.size(); i++)
				if(near(rs[i].lf, rs[j].lf))
					rs[j].ct += rs[i].ct;
				else
					rs[++j] = rs[i];
			while(rs.size() > j + 1) rs.pop_back();
			j = 0;
			for(i = 0; i < rs.size(); i++) {
				qt[i] = tot[i] = 0;
				while(qt[i] < rs[i].ct && j < ch.size())
					qt[i]++, tot[i] += ch[j++];
				//printf("have lf %.3f with ct %d and tot %d\n", rs[i].lf, rs[i].ct, tot[i]);
				if(i == 0) continue;
				if(qt[i] == 0) {
					if(qt[i - 1])
						dur = min(dur, (rs[i - 1].lf - rs[i].lf) / (ld(tot[i - 1]) / rs[i - 1].ct));
				} else {
					if(tot[i - 1] * rs[i].ct != tot[i] * rs[i - 1].ct)
						dur = min(dur, (rs[i - 1].lf - rs[i].lf) / (ld(tot[i - 1]) / rs[i - 1].ct - ld(tot[i]) / rs[i].ct));
				}
			}
			for(i = 0; i < rs.size(); i++)
				if(qt[i])
					rs[i].lf -= (ld(tot[i]) / rs[i].ct) * dur;
			sec -= dur;
		}
	}
	while(!rs.empty() && rs.back().lf < 1e-9) rs.pop_back();
	//printf("ok: %d\n\n\n", rs.empty());
	return rs.empty();
}

int P[N], S[N];
int main() {
	int i, k, j;
	for_tests(tn, tt) {
		scanf("%d", &k);
		for(i = 0; i < k; i++)
			scanf("%d %d", &P[i], &S[i]);
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d %d", &D[i], &M[i]);
		int best = INT_MAX;
		for(i = 1; i < (1 << k); i++) {
			vector<int> ch;
			int tot = 0;
			for(j = 0; j < k; j++)
				if((i >> j) & 1)
					ch.pb(P[j]), tot += S[j];
			if(tot < best && ok(ch)) {
				best = tot;
			}
		}
		if(best == INT_MAX) best = -1;
		printf("%d\n", best);
	}
}
