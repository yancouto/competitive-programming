#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

unsigned x0, x1, a, b, c;
unsigned next() {
	unsigned t = x0 * a + x1 * b + c;
	x0 = x1;
	x1 = t;
	return x0 >> 2;
}


const int N = 10000009;
unsigned v[N];

int main () {
	int n, q, i;
	scanf("%d %d %u %u %u %u %u", &n, &q, &x0, &x1, &a, &b, &c);
	int mni = 0;
	unsigned b = 1, ans = 0;
	for(i = 0; i < n; i++) v[i] = (1u << 31) - 1u;
	for(i = 0; i < q; i++) {
		unsigned i = (next() % n);
		unsigned x = next();
		v[i] = x;
		if(i == mni) {
			mni = 0;
			for(int g = 1; g < n; g++)
				if(v[g] < v[mni])
					mni = g;
		} else if(x < v[mni]) mni = i;
		b = b * 10099u;
		ans = ans + b * v[mni];
	}
	printf("%u\n", ans);
}
