#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int in[11234], inn;
ll w[1123], sz[1123];
int seen[1123], p[1123];
int cn;

int main() {
	int i, j;
	while(scanf("%d", &in[inn++]) != EOF);
	int n = inn / 2;
	for(i = 0; i < n; i++) w[i] = in[i];
	for(i = 0; i < n; i++) p[i] = in[i + n];
	ll mn = *min_element(w, w + n);
	ll tot = 0;
	for(i = 0; i < n; i++) {
		if(seen[i]) continue;
		ll sum = w[i];
		ll mnt = w[i];
		sz[++cn] = 1;
		seen[i] = cn;
		for(j = p[i]; j != i; j = p[j], sz[cn]++) {
			mnt = min(mnt, w[j]);
			sum += w[j];
			seen[j] = cn;
		}
		if(sz[cn] == 1) continue;
		tot += min(sum - mnt + mnt * ll(sz[cn] - 1), mnt + mn + sum + mn * ll(sz[cn]));
	}
	printf("%lld\n", tot);
}
