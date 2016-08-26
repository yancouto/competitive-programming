#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 102;

int s[N], b[N];
// ter um provavel multiset com as pri dos resources lockados
deque<pii> ins[N];
int ans[N], pri[N], seen[N], cur[N], run[N], has[N], bl[N];
multiset<int> loc[N];


int main() {
	int i, t, r, x, a; char op;
	memset(seen, -1, sizeof seen);
	memset(run, -1, sizeof run);
	scanf("%d %d", &t, &r);
	for(i = 0; i < t; i++) {
		scanf("%d %d %d", &s[i], &b[i], &a);
		while(a--) {
			scanf(" %c %d", &op, &x);
			if(op != 'C') ins[i].pb(pii(op, x)), pri[x] = max(pri[x], b[i]);
			else while(x--) ins[i].pb(pii(op, 0));
		}
	}
	int cl = 0, open = t;
	for(; open; cl++) {
		deque<int> tas;
		for(i = 0; i < t; i++) {
			if(s[i] <= cl && !ins[i].empty())
				tas.pb(i), cur[i] = b[i], run[i] = cl, bl[i] = 0;
			else run[i] = -1;
			seen[i] = -1;
		}
		sort(tas.begin(), tas.end(), [](int i, int j) { return cur[i] > cur[j]; });
		int ind = -1;
		while(!tas.empty()) {
			x = tas.front(); tas.pop_front();
			if(seen[x] == cl) continue;
			seen[x] = cl;
			if(ins[x].front().fst == 'L')
				for(i = 0; i < t; i++)
					if(i != x && run[i] == cl) {
						bool b = ((has[i] >> ins[x].front().snd) & 1);
						if(!loc[i].empty()) b |= (*loc[i].rbegin()) >= cur[x];
						if(!b) continue;
						bl[x] = true;
						if(cur[i] < cur[x]) { cur[i] = cur[x]; tas.push_front(i); }
					}
			if(!bl[x] && ind == -1) ind = x;
		}
		if(ind == -1) continue;
		pii it = ins[ind].front(); ins[ind].pop_front();
		if(ins[ind].empty()) ans[ind] = cl + (it.fst == 'C'), open--;
		if(it.fst == 'C') continue;
		cl--;
		if(it.fst == 'L') { has[ind] |= (1 << it.snd); loc[ind].insert(pri[it.snd]); }
		else { has[ind] ^= (1 << it.snd); loc[ind].erase(loc[ind].find(pri[it.snd])); }
	}
	for(i = 0; i < t; i++)
		printf("%d\n", ans[i]);
}
