#include <cstdio>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;
const int QMAX = 200009, NMAX = 30009;
multimap<int, int> mp;
int n, q, sq_n;
int a[NMAX], bit[NMAX];
int ql[QMAX], qr[QMAX], qk[QMAX], qs[QMAX];
int get(int i) {
	int sum = 0; i += 2;
	for(; i > 0; i -= (i & -i))
		sum += bit[i];
	return sum;
}
inline int get(int i, int j) {
	return get(j) - get(i - 1);
}
void add(int i, int x) {
	i += 2;
	for(; i < n + 9; i += (i & -i))
		bit[i] += x;
}
bool cmp_k(int i, int j) { return qk[i] < qk[j]; }

int main() {
	int i;
	scanf("%d", &n); sq_n = ceil(sqrt(n));
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		mp.insert(make_pair(a[i], i));
		bit[i] = (i & -i);
	}
	for(i = n; i < n + 4; i++)
		bit[i] = (i & -i);
	
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d %d %d", &ql[i], &qr[i], &qk[i]);
		ql[i]--; qr[i]--;
		qs[i] = i;
	}
	sort(qs, qs + q, cmp_k);
	auto it = mp.begin();
	for(i = 0; i < q; i++) {
		for(; it != mp.end() && it->first <= qk[qs[i]]; ++it)
			add(it->second, -1);
		ql[qs[i]] = get(ql[qs[i]], qr[qs[i]]);
	}
	for(i = 0; i < q; i++)
		printf("%d\n", ql[i]);
	return 0;
}