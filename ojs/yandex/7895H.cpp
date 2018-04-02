#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 212345;
char s[N];
int z[N]; // z[i] = |lcp(s, s[i...])|

void Z(int n) {
	int m = -1;
	for(int i = 1; i < n; i++) {
		z[i] = 0;
		if(m != -1 && m + z[m] >= i)
			z[i] = min(m + z[m] - i, z[i - m]);
		while(i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
		if(m == -1 || i + z[i] > m + z[m])
			m = i;
	}
}

int memo[30][N];
vector<int> v[2][N];

int main() {
	scanf("%s", s);
	int n = strlen(s);
	Z(n);
	for(int i = 1; i <= n; i++) {
		memo[1][i] = i;
		if(z[i + 1-1] == 0) continue;
		v[2&1][i + 1].pb(i);
		v[2&1][i + 1 + min(z[i + 1-1], i)].pb(-i);
	}
	for(int k = 2; k <= 26; k++) {
		set<int> cur;
		for(int i = 1; i <= n; i++) {
			for(int x : v[k&1][i]) {
				if(x > 0) cur.insert(x);
				else cur.erase(-x);
			}
			v[k&1][i].clear();
			if(cur.empty()) memo[k][i] = INT_MAX;
			else {
				memo[k][i] = *cur.begin();
				if(memo[k][i] > min(z[i + 1-1], i)) continue;
				v[!(k&1)][i + memo[k][i]].pb(i);
				v[!(k&1)][i + 1 + min(z[i + 1-1], i)].pb(-i);
			}
		}
	}
	for(int i = 26; i >= 0; i--)
		if(memo[i][n] != INT_MAX) {
			printf("%d\n", i);
			return 0;
		}
}
