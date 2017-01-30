#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000003;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

int tr[1123][26], go[1123][26];
int mrk[1123], mp[1123], f[1123];
int en = 1;

ll memo[1123][25][2][2][2];
ll solve(int u, int n, bool up, bool low, bool num) {
	//printf("%d, %d, %d, %d, %d\n", u, n, up, low, num);
	if(mrk[u]) return 0;
	if(n == 0) return up && low && num;
	ll &r = memo[u][n][up][low][num];
	if(r != -1) return r;
	r = 0;
	for(int i = 0; i < 26; i++) {
		r = r + solve(go[u][i], n - 1, true, low, num);
		r = r + solve(go[u][i], n - 1, up, true, num);
	}
	for(int i = 0; i < 10; i++) {
		if(mp[i]) r = r + solve(go[u][mp[i] - 'a'], n - 1, up, low, true);
		else r = r + solve(0, n - 1, up, low, true);
	}
	r = mod(r);
	return r;
}

char s[1123];
int main() {
	int a, b;
	memset(memo, -1, sizeof memo);
	int i, j;
	scanf("%d %d %d", &a, &b, &n);
	for(i = 0; i < n; i++) {
		scanf(" %s", s);
		int v = 0;
		for(j = 0; s[j]; j++) {
			if(!tr[v][s[j] - 'a'])
				tr[v][s[j] - 'a'] = en++;
			v = tr[v][s[j] - 'a'];
		}
		mrk[v] = 1;
	}
	queue<int> q;
	for(i = 0; i < 26; i++)
		if(tr[0][i])
			q.push(tr[0][i]), f[tr[0][i]] = 0;
	for(i = 0; i < 26; i++) go[0][i] = tr[0][i];
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(i = 0; i < 26; i++) {
			if(tr[x][i]) {
				int y = tr[x][i];
				f[y] = f[x];
				while(f[y] && !tr[f[y]][i])
					f[y] = f[f[y]];
				if(tr[f[y]][i]) f[y] = tr[f[y]][i];
				mrk[y] |= mrk[f[y]];
				q.push(y);
			}
			if(tr[x][i]) go[x][i] = tr[x][i];
			else go[x][i] = go[f[x]][i];
		}
	}
	mp[0] = 'o';
	mp[1] = 'i';
	mp[3] = 'e';
	mp[5] = 's';
	mp[7] = 't';
	ll ans = 0;
	for(i = a; i <= b; i++)
		ans += solve(0, i, false, false, false);
	ans = mod(ans);
	printf("%lld\n", ans);
}
