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

const int N = 101;
char s[N], t[N];
int n;
int o[256];
char memo[N][N][N][N];
bitset<N> seen[N][N][N];
char solve(int i, int h1, int h2, int h3) {
	if(i == n) return 0;
	int d = (h1 + 2 * h2 + 3 * h3) % 4;
	char &r = memo[i][h1][h2][h3];
	if(seen[i][h1][h2][h3]) return r;
	seen[i][h1][h2][h3] = 1;
	r = CHAR_MAX;
	if(h1) r = min<char>(r, solve(i, h1 - 1, h2, h3));
	if(h2) r = min<char>(r, solve(i, h1, h2 - 1, h3));
	if(h3) r = min<char>(r, solve(i, h1, h2, h3 - 1));
	int dif = (t[i] - ((s[i] + d) % 4) + 20) % 4;
	assert(((s[i] + dif + d) % 4) == t[i]);
	if(dif == 0) r = min<char>(r, solve(i + 1, h1, h2, h3));
	if(dif == 1) r = min<char>(r, 1 + solve(i + 1, h1 + 1, h2, h3));
	if(dif == 2) r = min<char>(r, 1 + solve(i + 1, h1, h2 + 1, h3));
	if(dif == 3) r = min<char>(r, 1 + solve(i + 1, h1, h2, h3 + 1));
	return r;
}

int st[3][212];
int sn[3];
void build(int i, int h1, int h2, int h3) {
	if(i == n) {
		// pop all
		for(int g = 0; g <= 2; g++)
			while(sn[g])
				printf("%d %d %d\n", st[g][--sn[g]] + 1, i, g + 1);
		return;
	}
	int d = (h1 + 2 * h2 + 3 * h3) % 4;
	char r = memo[i][h1][h2][h3];
	if(h1 && r == solve(i, h1 - 1, h2, h3)) { printf("%d %d 1\n", st[0][--sn[0]] + 1, i); return build(i, h1 - 1, h2, h3); }
	if(h2 && r == solve(i, h1, h2 - 1, h3)) { printf("%d %d 2\n", st[1][--sn[1]] + 1, i); return build(i, h1, h2 - 1, h3); }
	if(h3 && r == solve(i, h1, h2, h3 - 1)) { printf("%d %d 3\n", st[2][--sn[2]] + 1, i); return build(i, h1, h2, h3 - 1); }
	int dif = (t[i] - ((s[i] + d) % 4) + 20) % 4;
	assert(((s[i] + dif + d) % 4) == t[i]);
	if(dif == 0 && r == solve(i + 1, h1, h2, h3)) return build(i + 1, h1, h2, h3);
	if(dif == 1 && r == 1 + solve(i + 1, h1 + 1, h2, h3)) { st[0][sn[0]++] = i; return build(i + 1, h1 + 1, h2, h3); }
	if(dif == 2 && r == 1 + solve(i + 1, h1, h2 + 1, h3)) { st[1][sn[1]++] = i; return build(i + 1, h1, h2 + 1, h3); }
	if(dif == 3 && r == 1 + solve(i + 1, h1, h2, h3 + 1)) { st[2][sn[2]++] = i; return build(i + 1, h1, h2, h3 + 1); }
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("transform.in", "r", stdin);
	freopen("transform.out", "w", stdout);
#endif
	int i = 0, j;
	scanf("%s %s", s, t);
	int cur = 0;
	for(char c : "ACGT")
		o[c] = i++;
	n = strlen(s);
	for(i = 0; i < n; i++)
		s[i] = o[s[i]], t[i] = o[t[i]];
	printf("%d\n", solve(0, 0, 0, 0));
	build(0, 0, 0, 0);
}
