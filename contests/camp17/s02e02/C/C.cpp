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
char s[212345];
int z[212345];

void calc() {
	int l = -1;
	for(int i = 1; i < n; i++) {
		if(l != -1 && l + z[l] - 1 >= i)
			z[i] = min(l + z[l] - i, z[i - l]);
		while(i + z[i] < n && s[i + z[i]] == s[z[i]]) { z[i]++; }
		if(l == -1 || i + z[i] > l + z[l])
			l = i;
	}
}

int main() {
	int i, j;
	scanf("%s", s);
	n = strlen(s);
	for(i = 0; i < n; i++)
		s[2 * n - 1 - i] = s[i];
	n = 2 * n;
	calc();
	for(i = n / 2; i < n; i++)
		if(i + z[i] >= n) {
			printf("%d\n", n - i);
			return 0;
		}
}
