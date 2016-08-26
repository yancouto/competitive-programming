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

char s[2009]; int z[2009];
void manacher() {
	int L, R = -1, i;
	for(i = 0; s[i]; i++) {
		if(i > R) {
			for(L = R = i; s[R] && 2*i >= R && s[R] == s[2*i-R]; R++);
			z[i] = (--R) - i;
		} else if(z[2*L-i] < R - i) z[i] = z[2*L-i];
		else {
			for(L = i, R++; s[R] && 2*i >= R && s[R] == s[2*i-R]; R++);
			z[i] = (--R) - i;
		}
	}
}

int main() {
	int i, j;
	scanf("%s", s);
	int n = strlen(s);
	for(i = n - 1; i >= 0; i--)
		s[2*i] = s[i], s[2*i + 1] = '$';
	manacher();
	int tot = 0;
	for(i = 0; i < n; i++)
		tot += ((z[2*i] / 2) + 1) + (z[2*i+1]? (z[2*i+1] - 1) / 2 + 1 : 0);
	printf("%d\n", tot);
}
