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

char s[1123456];

int main() {
	int i, j;
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	for(i = 2; i <= n; i++) {
		F[i] = F[i - 1];
		while(F[i] && s[F[i] + 1] != s[i])
			F[i] = F[F[i]];
		if(s[F[i] + 1] == s[i])
			F[i]++;
	}
}
