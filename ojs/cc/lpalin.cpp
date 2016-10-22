#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

char s[11234];
int n;
int main() {
	int i;
	for_tests(t, tt) {
		scanf(" %d %s", &n, s);
		for(i = 0; i < n && s[i] == s[n - 1 - i]; i++);
		if(i == n) puts("0");
		else puts("1");
	}
}
