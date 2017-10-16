#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int n;
int a[N][2];
char str[30];
int b[N];

int main () {
#ifdef ONLINE_JUDGE
	freopen("bureau.in", "r", stdin);
	freopen("bureau.out", "w", stdout);
#endif
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf(" %s", str);
		if (str[0] == 'c') {
			a[i][0] = 1;
			scanf("%d", &a[i][1]);
		} else {
			a[i][0] = 0;
		}
	}

	int qt = 0;
	for (int i = n-1; i >= 0; i--) {
		if (b[i]) continue;
		qt++;
		if (a[i][0] == 1)
			b[a[i][1]-1] = 1;
	}

	printf("%d\n", qt);
	for (int i = 0; i < n; i++) {
		if (!b[i])
			printf("%d ", i+1);
	}
	printf("\n");
}

