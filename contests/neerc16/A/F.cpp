

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
char s[1123456];

int main() {
#ifdef ONLINE_JUDGE
	freopen("foreign.in", "r", stdin);
	freopen("foreign.out", "w", stdout);
#endif
	int i, j;
	scanf("%s", s + 1);
	n = strlen(s + 1);
	reverse(s + 1, s + 1 + n);
	double sum = 0, ok = 0, nok = 0, cur;
	for(i = 1; i <= n; i++) {
		if(s[i] == 'C') ok = ok + i;
		else nok = nok + i;
		cur = sum / double(i) + (s[i] == 'C'? nok : ok) / double(i);
		sum += cur;
	}
	printf("%.20f\n", cur);
}
