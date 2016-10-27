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

int n;
typedef long double ld;
char s[112345];


vector<int> l, r;
double memo[4009][4009];
bool seen[4009][4009];
double solve(int i, int j) {
	if(i == j) return sqrt(r[i] - l.back());
	double &ret = memo[i][j];
	if(seen[i][j]) return ret;
	seen[i][j] = true;
	int x = i + (r.size() - 1 - j);
	return ret = min(solve(i + 1, j) + sqrt(r[i] - l[x]), solve(i, j - 1) + sqrt(r[j] - l[x]));

}

int main() {
	int i, j = 0;
	scanf("%s", s);
	for(i = 0; s[i]; i++) j += (s[i] == '0');
	if(j == i || j == 0) { puts("0"); return 0; }
	int ct = j;
	ld ans = 0;
	for(i = 0; i < ct; i++)
		if(s[i] == '1')
			l.pb(i);
	for(i = ct; s[i]; i++)
		if(s[i] == '0')
			r.pb(i);
	if(l.empty()) { puts("0"); return 0; }
	assert(l.size() == r.size());
	printf("%.20f\n", (double) solve(0, r.size() - 1));
}
