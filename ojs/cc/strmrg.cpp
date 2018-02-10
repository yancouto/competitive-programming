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

char S[2][5009];

int tempo;
int memo[5009][5009][2];
int seen[5009][5009][2];
int go(int i, int j, bool l) {
	int &r = memo[i][j][l];
	if(seen[i][j][l] == tempo) return r;
	seen[i][j][l] = tempo;
	if(!S[0][i] && !S[1][j]) return 0;
	char c = l? S[1][j - 1] : S[0][i - 1];
	r = INT_MAX;
	if(S[0][i]) r = min(r, (c != S[0][i]) + go(i + 1, j, 0));
	if(S[1][j]) r = min(r, (c != S[1][j]) + go(i, j + 1, 1));
	return r;
}

int main() {
	int n, m;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		scanf("%s %s", S[0] + 1, S[1] + 1);
		S[0][0] = S[1][0] = 'A';
		tempo++;
		printf("%d\n", go(1, 1, 0));
	}
}
