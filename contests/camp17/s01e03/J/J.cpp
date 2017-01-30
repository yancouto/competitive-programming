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

const int N = 20;

char v[2][N];
ll s[2];
ll a[2];

void go (int k) {
	bool ok = 0;
	for (int i = 0; v[k][i]; i++) {
		if (v[k][i] == '.') {
			ok = 1;
		} else {
			if (ok)
				s[k] *= 10;
			a[k] *= 10;
			a[k] += v[k][i] - '0';
		}
	}
}

int main () {
	scanf(" %s %s", v[0], v[1]);

	s[0] = s[1] = 1;
	a[0] = a[1] = 0;

	go(0);
	go(1);

	//printf("%lld*%lld / %lld*%lld\n", a[0], s[1], a[1], s[0]);
	printf("%lld\n", (a[0]*s[1])/(a[1]*s[0]));
}
