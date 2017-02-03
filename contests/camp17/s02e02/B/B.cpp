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
int z[212345];

int main() {
	int i, j, p;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &p);
		if(p) z[i - p + 1] = max(z[i - p + 1], p);
	}
	int l = -1;
	for(i = 1; i < n; i++) {
		if(l != -1 && l + z[l] - 1 >= i)
			z[i] = max(min(l + z[l] - i, z[i - l]), z[i]);
		if(l == -1 || i + z[i] > l + z[l])
			l = i;
	}
	for(i = 0; i < n; i++) printf("%d ", z[i]);
	putchar('\n');
}
