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
int a[112345];

void lose() {
	puts("Lose");
	exit(0);
}

void win() {
	puts("Win");
	exit(0);
}

int main() {
	int i, j;
	scanf("%d", &n);
	int ct1 = 0, ct2 = 0, cto = 0;
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		if(a[i] == 1) ct1++;
		else if(a[i] == 2) ct2++;
		else cto++;
	}
	if(n == 1) win();
	if(cto + ct2 <= 1 && ((n - 1) % 3) != 2) win();
	if(cto + ct2 == 1 && ((n % 3) != 2)) win();
	if(ct2 >= 1 && cto + ct2 <= 2 && ((n - 1) % 3) == 0) win();
	if(ct2 >= 1 && cto + ct2 == 2 && ((n % 3) == 0)) win();
	if(cto == 1 && ct2 == 0 && ((n % 3) == 0)) win();
	lose();
}
