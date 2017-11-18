#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef pair<ll, ll> pii;

int n, m;

int main() {
	scanf("%d %d", &n, &m);

	printf("+ 0 1\n");
	int q = 2;
	for (int i = 1; i < n; i++) {
		printf("swap_rows 0 1 %d\n", i+1);
		q++;
		q++;
		printf("+ %d %d\n", q-2, q-1);
	}

	printf("swap_columns 1 1 2\n");
	printf("+ %d %d\n", q, q+1);
	q += 2;
	printf("answer %d\n", q);
}
