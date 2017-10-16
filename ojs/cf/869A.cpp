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
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

int main() {
	int i, j, x;
	scanf("%d", &n);
	set<int> s;
	for(i = 0; i < 2 * n; i++) {
		scanf("%d", &x);
		s.insert(x);
	}
	int ct = 0;
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			ct += s.count(i ^ j);
	if(ct & 1) puts("Koyomi");
	else puts("Karen");
}
