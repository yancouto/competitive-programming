#include <bits/stdc++.h>
using namespace std;

struct seg {
	int l, r, i;
	bool operator < (seg o) { return (r - l + 1) < (o.r - o.l + 1); }
} s[1000];
int p[1000], o[1000];
int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		s[i].i = i + 1;
		scanf("%d %d", &s[i].l, &s[i].r);
	}
	sort(s, s + n);
	for(i = 0; i < n; i++) {
		p[i] = 0; o[i] = -1;
		for(j = 0; j < i; j++)
			if(s[j].l > s[i].l && s[j].r < s[i].r && p[j] > p[i]) {
				p[i] = p[j];
				o[i] = j;
			}
		p[i]++;
	}
	int mi = max_element(p, p + n) - p;
	int st[1000], sn = 0;
	printf("%d\n", p[mi]);
	while(mi != -1) {
		st[sn++] = s[mi].i;
		mi = o[mi];
	}
	printf("%d", st[--sn]);
	while(sn)
		printf(" %d", st[--sn]);
	putchar('\n');
}
