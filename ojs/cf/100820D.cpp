#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif

int main() {
	int i, j, n;
	int a[100], b[100];
	for(i = 0; i < 3; i++) scanf("%d", &a[i]);
	for(i = 0; i < 3; i++) scanf("%d", &b[i]);
	sort(a, a + 3);
	sort(b, b + 3);
	for(i = 0; i < 3 && a[i] == b[i]; i++);
	if(i == 3 && a[0] * a[0] + a[1] * a[1] == a[2] * a[2]) puts("YES");
	else puts("NO");
}
