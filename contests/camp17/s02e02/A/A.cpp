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
const int N = 212345;
int p[N];

int main() {
	int i, j, z;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &z);
		if(z) p[i + z - 1] = max(p[i + z - 1], z);
	}
	for(i = n - 2; i > 0; i--)
		if(p[i + 1] > p[i])
			p[i] = p[i + 1] - 1;
	for(i = 0; i < n; i++)
		printf("%d ", p[i]);
	putchar('\n');
}
