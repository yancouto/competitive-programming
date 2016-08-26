#include <bits/stdc++.h>
using namespace std;

int bit[33000];
int get(int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}
void add(int i) {
	for(i += 2; i < 33000; i += (i & -i))
		bit[i]++;
}

int lv[15009];
int main() {
	int i, n, x;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %*d", &x);
		lv[get(x)]++;
		add(x);
	}
	for(i = 0; i < n; i++)
		printf("%d\n", lv[i]);
	return 0;
}
