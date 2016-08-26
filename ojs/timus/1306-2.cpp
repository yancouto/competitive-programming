#include <bits/stdc++.h>
using namespace std;

int a[125004], n, sz = 0;
void push_heap(int x) {
	a[++sz] = x; x = sz;
	while(x != 1) {
		if(a[x] > a[x/2]) {
			swap(a[x], a[x/2]);
			x >>= 1;
		} else break;
	}
}

void pop_heap() {
	int x = 1;
	while(2*x <= sz) {
		if(2*x+1 > sz) a[2*x+1] = -1;
		int i = 2*x;
		if(a[i] < a[i+1]) i++;
		a[x] =  a[i];
		x = i;
	}
	swap(a[sz--], a[x]);
	while(x != 1) {
		if(a[x] > a[x/2]) {
			swap(a[x], a[x/2]);
			x >>= 1;
		} else break;
	}
}
void deb() {
	for(int i = 1; i <= sz; i++)
		printf("%d ", a[i]);
	putchar('\n');
}

int main() {
	int i, x;
	scanf("%d", &n);
	for(i = 0; i <= n/2; i++) {
		scanf("%d", &x);
		push_heap(x);
	}
	for(i = (n/2) + 1; i < n; i++) {
		scanf("%d", &x);
		if(x > a[1]) continue;
		pop_heap();
		push_heap(x);
	}
	int aa = a[1];
	pop_heap();
	int bb = a[1];
	if(n & 1) bb = aa;
	printf("%.1f\n", aa + (bb - aa) / 2.);
	return 0;
}
