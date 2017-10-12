#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

bool win(int a) { return a > 0; }
bool win(int a, int b) { return a != b; }
bool win(int a, int b, int c) { return a != c || (a == b && a == c); }
bool win(int a, int b, int c, int d) {
	if(b == c)
		return a != d;
	else {
		if((a == c) || (b == d)) return true;
		a -= (a >= c);
		d -= (d >= b);
		return a != d;
	}
}

bool win(int a, int b, int c, int d, int e) {
	if(!win(a, b, c, d) || !win(b, c, d, e)) return true;
	for(int i = a - 1; i >= 0; i--)
		if(!win(i, b, c, d))
			a--;
	for(int i = e - 1; i >= 0; i--)
		if(!win(b, c, d, i))
			e--;
	return a != e;
}

int a[10];

char *ans[] = {"SERGEY", "FEDOR"};

void go(bool b) {
	puts(ans[b]);
	exit(0);
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("stacks.in", "r", stdin);
	freopen("stacks.out", "w", stdout);
#endif
	int n, i;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	if(n == 1) go(win(a[0]));
	else if(n == 2) go(win(a[0], a[1]));
	else if(n == 3) go(win(a[0], a[1], a[2]));
	else if(n == 4) go(win(a[0], a[1], a[2], a[3]));
	else go(win(a[0], a[1], a[2], a[3], a[4]));
}

