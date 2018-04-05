#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

int n, t;
const int N = (1<<20);
int v[N];

int main () {
	scanf("%d %d", &n, &t);
	for (int i = 0; i < (1<<n); i++)
		scanf("%d", &v[i]);
	for (int i = 0; i < (1<<n); i++) {
		if (t%2) printf("%d ", v[(1<<n)-1-i]);
		else printf("%d ", v[i]);
	}
	printf("\n");
}

