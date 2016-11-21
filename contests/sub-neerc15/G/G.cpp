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

template<class num> inline void read(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int n;
ll p[2][2][2];
ll s[2];

void yep () {
	printf("Yes\n");
	exit(0);
}

int main() {
	 #ifdef ONLINE_JUDGE
		freopen("grave.in", "r", stdin);
		freopen("grave.out", "w", stdout);
	#endif

	for (int k = 0; k < 2; k++)
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				scanf("%lld", &p[k][i][j]);

	for (int i = 0; i < 2; i++) {
		scanf("%lld", &s[i]);
	}
	
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (abs(p[0][i][j] - p[1][i][j]) >= s[j] 
			&&  abs(p[0][0][!j] - p[0][1][!j]) >= s[!j]) {
				yep();
			}
	printf("No\n");
}
