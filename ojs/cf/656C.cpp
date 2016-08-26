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

int b(bool c) {
	return c;
}

int ind(char c) {
	return c;
}

int f(char c) {
	return
	(ind(c) * b(('@' < c) && ('[' > c))) - 
	(ind(c) * b(('`' < c) && ('{' > c)));
}

char s[1009];

int main() {
	int i, val = 0;
	scanf("%s", s);
	for(i = 0; s[i]; i++)
		val += f(s[i]);
	printf("%d\n", val);
}
