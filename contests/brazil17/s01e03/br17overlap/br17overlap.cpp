#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

vector<int> Ds[112];
const int N = 512345;
int l[N], r[N];

int main() {
	int i, n, d, dd, j;
	scanf("%d %d", &n, &d);
	for(i = 0; i < n; i++) {
		scanf("%d %d %d", &l[i], &r[i], &dd);
		Ds[dd].pb(i);
	}
	for(i = 1; i <= d; i++) {
		vector<int> Ds = ::Ds[i];
		if(Ds.size() < 2) {
			puts("NIE");
			continue;
		}
		sort(Ds.begin(), Ds.end(), [](int i, int j) { return r[i] < r[j]; });
		for(j = 1; j < int(Ds.size()); j++)
			if(l[Ds[j]] > r[Ds[0]]) {
				printf("ANO %d %d\n", Ds[0] + 1, Ds[j] + 1);
				break;
			}
		if(j == int(Ds.size())) puts("NIE");
	}
}
