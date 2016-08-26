#include <cstdio> 
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef pair<int, int> pii;
struct num {
	int i;
	int l, r;
	num() {}
	num(int a, int b, int c) : i(a), l(b), r(c) {}
} ll[100009], rr[100009];
bool cmp_l(const num &a, const num &b) {
	return a.l > b.l;
}
bool cmp_r(const num &a, const num &b) {
	return a.r > b.r;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int l, r, i, j, k = 0;
		scanf("%d %d", &l, &r);
		int maxh = 0; int big = 0;
		for(i = l; i <= r; i++) {
			int sz = 0, left = 0, right = 0;
			bool stp_left = false;
			for(j = 1; j <= i; j <<= 1) {
				sz++;
				right++;
				if(!(i & j)) {
					big = max(big, right - 1);
					right = 0;
					stp_left = true;
				}
				if(!stp_left) left++;
			}
			if(left == sz) maxh += sz;
			else {
				ll[k] = num(i, left, right);
				rr[k++] = num(i, left, right);
			}
		}
		ll[k] = num(-1, 0, 0);
		ll[k + 1] = num(-2, 0, 0);
		rr[k++] = num(-1, 0, 0);
		rr[k++] = num(-2, 0, 0);
		partial_sort(ll, ll + 2, ll + k, cmp_l);
		partial_sort(rr, rr + 2, rr + k, cmp_r);
		if(ll[0].i != rr[0].i) maxh += ll[0].l + rr[0].r;
		else maxh += max(ll[0].l + rr[1].r, rr[0].r + ll[1].l);
		printf("%d\n", max(big, maxh));
	}
	return 0;
}