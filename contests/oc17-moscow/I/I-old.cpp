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


const int N = 50000009;
unsigned v[N / 5];
unsigned h1[N];
unsigned hr[N];
bool cg[N];

int main () {
	int n, q, i;
	scanf("%d %d %u %u %u %u %u", &n, &q, &x0, &x1, &a, &b, &c);
	int hrn = 0, h1n = 0;
	h1n = n;
	unsigned ans = 0;
	unsigned b = 1;
	auto comp = greater<unsigned>();
	unsigned el = (1u << 32);
	for(i = 0; i < q; i++) {
		unsigned i = (next() % n);
		unsigned x = next();
		if(!cg[i]) {
			cg[i] = true;
		} else {
			hr[hrn++] = v[i];
			push_heap(hr, hr + hrn, comp);
		}
		h1[h1n++] = x;
		push_heap(h1, h1 + h1n, comp);
		v[i] = x;
		while(hrn && h1n && hr[0] == h1[0]) {
			pop_heap(hr, hr + hrn, comp); hrn--;
			pop_heap(h1, h1 + h1n, comp); h1n--;
		}
		b = b * 10099u;
		ans = ans + b * (h1n? h1[0] : el);
	}
	printf("%u\n", ans);
}
