#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 2e5+7;

int x[N];
int w[N];
int p[N];
int n, d;

int get (pii a) {
	if (a.first == -1) return 0;
	return w[a.first] + w[a.second];
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	scanf("%d %d", &n, &d);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &x[i], &w[i]);
		p[i] = i;
	}

	sort(p, p+n, [] (int i, int j) {
		return x[i] < x[j];
	});

	int i = -1;
	pii sol(-1,-1);
	int bst = -1;
	for (int j = 0; j < n; j++) {
		while (i < j-1 && x[p[j]] - x[p[i+1]] >= d) {
			i++;
			if (bst == -1 || w[p[i]] >= w[bst])
				bst = p[i];
		}
		if (get(pii(bst, p[j])) > get(sol))
			sol = pii(bst, p[j]);
	}

	if (sol.first == -1) {
		sol.first--;
		sol.second--;
	}
	printf("%lld %lld\n", sol.first+1, sol.second+1);
}
