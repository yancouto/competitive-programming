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

char s[112];
int main() {
	scanf("%s", s);
	int a = 0;
	for(int i = 0; s[i]; i++)
		a = (a * 10 + s[i] - '0') % 7;
	printf("%d\n", a);
}
