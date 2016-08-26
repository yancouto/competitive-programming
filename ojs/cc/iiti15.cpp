#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX = 20009;
int n, q, sq_n;
int a[MAX];
int b[MAX];
int ql[MAX], qr[MAX], qs[MAX];


bool cmp_r(int i, int j) {
	return qr[i] < qr[j];
}
bool cmp_block(int i, int j) {
	return ((int) (ql[i] / sq_n)) < ((int) ql[j] / sq_n);
}

int bit[MAX];
int get(int i) {
	int sum = 0; i+= 2;
	for(; i > 0; i -= (i & -i)) sum += bit[i];
	return sum;
}
int get(int i, int j) { return get(j) - get(i - 1); }
void add(int i, int x) {
	i += 2;
	for(; i < MAX; i += (i & -i)) bit[i] += x;
}

int l, r;
int resp;
void right_l() {
	// printf("right_l (%d) [%d]\n", l, a[l]);
	int loc = (lower_bound(b, b + n, a[l++]) - b);
	// printf("loc %d [%d]\n", loc, b[loc]);
	// printf("resp %d to ", resp);
	resp -= get(0, loc - 1);
	// printf("%d\n", resp);
	add(loc, -1);
}
void left_l() {
	// printf("left_l (%d) [%d]\n", l, a[l - 1]);
	int loc = (lower_bound(b, b + n, a[--l]) - b);
	// printf("loc %d [%d]\n", loc, b[loc]);
	// printf("resp %d to ", resp);
	resp += get(0, loc - 1);
	// printf("%d\n", resp);
	add(loc, 1);
}
void right_r() {
	// printf("right_r (%d) [%d]\n", r, a[r + 1]);
	int loc = (upper_bound(b, b + n, a[++r]) - b);
	// printf("loc %d [%d]\n", loc, b[loc]);
	// printf("resp %d to ", resp);
	resp += get(loc, n);
	// printf("%d\n", resp);
	add(loc - 1, 1);
}
void left_r() {
	// printf("left_r (%d) [%d]\n", r, a[r]);
	int loc = (upper_bound(b, b + n, a[r--]) - b);
	// printf("loc %d [%d]\n", loc, b[loc]);
	// printf("resp %d to ", resp);
	resp -= get(loc, n);
	// printf("%d\n", resp);
	add(loc - 1, -1);
}

int main() {
	int i;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &ql[i], &qr[i]); ql[i]--; qr[i]--;
		qs[i] = i;
	}
	sq_n = ceil(sqrt(n));
	sort(qs, qs + q, cmp_r);
	stable_sort(qs, qs + q, cmp_block);
	sort(b, b + n);
	// for(i = 0; i < n; i++) printf("%d ", a[i]);
	// printf("\n");
	// for(i = 0; i < n; i++) printf("%d ", b[i]);
	// printf("\n");
	r = -1; l = 0; resp = 0;
	for(i = 0; i < q; i++) {
		while(l < ql[qs[i]]) right_l();
		while(l > ql[qs[i]]) left_l();
		while(r < qr[qs[i]]) right_r();
		while(r > qr[qs[i]]) left_r();
		ql[qs[i]] = resp;
	}
	for(i = 0; i < q; i++)
		printf("%d\n", ql[i]);
	return 0;
}