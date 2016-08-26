#include <bits/stdc++.h>
using namespace std;
const int N = 4009;
int x[N], y[N];

int cross(int a, int b, int c) {
	return (x[b] - x[a]) * (y[c] - y[a]) - (y[b] - y[a]) * (x[c] - x[a]);
}

int dist(int i, int j) {
	return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

bool lex_less(int i, int j) {
	if(x[i] != x[j]) return x[i] < x[j];
	return y[i] < y[j];
}

int bi;
bool cross_cmp(int i, int j) {
	int c = cross(bi, i, j);
	if(c != 0) return c > 0;
	if(x[i] != x[j]) return x[i] < x[j];
	return y[i] > y[j];
}

int st[N], sn;
int p1[N], p2[N];
int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d %d", &x[i], &y[i]), p1[i] = i;
	int ct = 0; int *p = p2, *pp = p1;
	while(n > 2) {
		swap(p, pp);
		swap(p[0], *min_element(p, p + n, lex_less));
		bi = p[0];
		sort(p + 1, p + n, cross_cmp);
		sn = 0;
		st[sn++] = p[0];
		int k = 0;
		for(i = 1; i < n; i++) {
			while(sn >= 3 && cross(st[sn - 2], p[i], st[sn - 1]) > 0)
				pp[k++] = st[--sn];
			st[sn++] = p[i];
		}
		for(i = 2; i < sn; i++)
			if(cross(st[i], st[i - 1], st[i - 2]) != 0)
				break;
		ct += (i < sn);
		n = k;
	}
	printf("%d\n", ct);
}
