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
int n, en, k;
char s[1000];
int p[1000];
int L[1000], R[1000];

void go(int u) {
	L[u] = R[u] = 0;
	if(s[++n] == '(') { L[u] = en++; go(L[u]); }
	if(s[n] == ')') { n++; return; }
	assert(s[n] == ',');
	if(s[++n] == '(') { R[u] = en++; go(R[u]); }
	assert(s[n++] == ')');
}

int dfs(int u) {
	if(!u) return 0;
	dfs(L[u]);
	p[u] = ++k;
	dfs(R[u]);
}


int main() {
	while(scanf("%s", s) != EOF && strlen(s) > 2) {
		n = k = 0; en = 2;
		go(1);
		dfs(1);
		for(int i = 1; i < en; i++)
			printf("%d%c", p[i], " \n"[i == en - 1]);
	}
}
