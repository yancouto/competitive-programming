#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 512345;

char s[N]; int ps[N], n, sz[N];

int go(int x) {
	int ct = -1;
	for(int i = 0; i < n; i += x)
		i = ps[i], ct += sz[i] + 1;
	return ct;
}

int main() {
	int i, a, b;
	while(true) {
		fgets(s, sizeof s, stdin);
		if(feof(stdin)) return 0;
		ps[0] = 0;
		for(i = 1; s[i]; i++)
			if(s[i] == ' ') ps[i] = i + 1;
			else ps[i] = ps[i - 1];
		n = i - 1; sz[n] = 0;
		for(i = n - 1; i >= 0; i--)
			if(s[i] == ' ') sz[i] = 0;
			else sz[i] = 1 + sz[i + 1];
		scanf("%d %d ", &a, &b);
		for(i = a; i <= b; i++)
			printf("%d\n", go(i));
	}
}
