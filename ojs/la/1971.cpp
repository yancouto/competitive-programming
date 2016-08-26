#include <cstdio>
#include <unordered_set>
#include <algorithm>
using namespace std;
#define x(a) a[0]
#define y(a) a[1]
#define z(a) a[2]
typedef unsigned long long ull;
int ps[53][3];
ull rs[2502];
int r_n;
unordered_set<ull> rrs;

bool coll(int a[3], int b[3]) {
	return  y(a) * z(b) == z(a) * y(b) &&
			x(a) * z(b) == z(a) * x(b) &&
			x(a) * y(b) == y(a) * x(b);
}

void sub(int a[3], int b[3], int c[3]) {
	//c = a - b
	for(int i = 0; i < 3; i++)
		c[i] = a[i] - b[i];
}

ull all;
int count_0(ull a) {
	int cn = 0;
	for(ull u = 1; u < all; u <<= 1)
		if(!(u & a))
			cn++;
	return cn;
	
}

int solve(int i, ull total) {
	if(total == all) return 0;
	if(i == r_n) return (count_0(total) + 1) / 2;
	ull new_total = total | rs[i];
	if(count_0(new_total) < count_0(total) - 2) return min(solve(i + 1, new_total) + 1, solve(i + 1, total));
	return solve(i + 1, total);
}

int main() {
	int n, i, j, k;
	for(int t = 1; ; t++) {
		rrs.clear();
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 0; i < n; i++)
			scanf("%d %d %d", &x(ps[i]), &y(ps[i]), &z(ps[i]));
		for(i = 0; i < n; i++)
			for(j = i + 1; j < n; j++) {
				int r1[3]; sub(ps[j], ps[i], r1);
				ull r = (1ull << i) | (1ull << j);
				int count = 2;
				for(k = 0; k < n; k++) {
					if(k == i || k == j) continue;
					int r2[3]; sub(ps[k], ps[i], r2);
					if(coll(r1, r2)) {
						r |= (1ull << k);
						count++;
					}
				}
				if(count > 2) rrs.insert(r); 
			}
		r_n = 0;
		for(ull r : rrs)
			rs[r_n++] = r;
		all = (1ull << n) - 1ull;
		printf("Target set %d can be cleared using only %d shots.\n", t, solve(0, 0));
	}
}