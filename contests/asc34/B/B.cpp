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
char s[11234];

void def(int n) {
	n /= 2;
	putchar('1');
	for(int i = 1; i < n; i++)
		putchar('0');
	for(int i = n; i < 2 * n - 1; i++)
		putchar('1');
	putchar('0');
	putchar('\n');
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("anti.in", "r", stdin);
	freopen("anti.out", "w", stdout);
#endif
	int i, j;
	while(scanf("%s", s) != EOF) {
		n = strlen(s);
		assert(s[0] != '0' || n == 1);
		if(s[0] == '0') return 0;
		if(n & 1) { def(n + 1); continue; }
		n /= 2;
		for(i = 0; i < 2*n && s[i] == '9'; i++);
		if(i > n) { def(2*n + 2); continue; }
		if(n == 1 && s[0] == '9' && s[1] == '8') { def(4); continue; }
		for(i = 2 * n - 1; i >= 0 && s[i] == '9'; s[i--] = '0');
		assert(i >= 0);
		s[i]++;
		for(i = n; i < 2 * n && s[i] != s[n - 1 - (i - n)]; i++);
		if(i == 2 * n) { puts(s); continue; }
		while(i >= n && s[i] == s[n - 1 - (i - n)]) {
			for(; i >= 0 && s[i] == '9'; s[i--] = '0');
			assert(i >= 0);
			s[i]++;
		}
		for(i = max(i + 1, n); i < 2 * n; i++)
			if(s[n - 1 - (i - n)] == '0') s[i] = '1';
			else s[i] = '0';
		puts(s);
	}
}
