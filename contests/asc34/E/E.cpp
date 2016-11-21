#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const int N = 23;

int res[] = {1,
2,
3,
5,
8,
14,
25,
45,
85,
162,
310,
595,
1165,
2285,
4485,
8808,
17306,
34302,
68009,
134853};

int main () {
	freopen("chipmunks.in", "r", stdin);
	freopen("chipmunks.out", "w", stdout);
	int n;
	scanf("%d", &n);
	printf("%d\n", res[n-1]);
}
