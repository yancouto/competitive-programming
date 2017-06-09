#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;

int a[11234], p[11234];

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]), p[i] = i;
	sort(p, p + n, [](int i, int j) { return a[i] > a[j]; });
	if(a[p[0]] > accumulate(a, a + n, 0) - a[p[0]]) puts("impossible");
	else {
		for(i = 0; i < n; i++) printf("%d ", p[i] + 1);
		putchar('\n');
	}
}
