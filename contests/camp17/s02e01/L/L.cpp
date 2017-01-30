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

int n, t1, t2;
int eval(int t) {
	return (t / t1) + (t / t2);
}

int main() {
	int i, j;
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d %d %d", &n, &t1, &t2);
	int l = 1, r = 1000000000;
	while(l < r) {
		int m = (l + r) / 2;
		if(eval(m) >= n) r = m;
		else l = m + 1;
	}
	int val = eval(l);
	if(l % t1) l = ((l / t1) + 1) * t1, val++;
	else if(l % t2) l = ((l / t2) + 1) * t2, val++;
	printf("%d", val);
	printf(" %d\n", l);
}
