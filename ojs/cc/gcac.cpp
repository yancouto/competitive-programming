#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 2123;

int mn[N], sal[N], of[N], oof[N];
string a[N];

int main() {
	int i, n, m, t, j;
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	while(t--) {
		cin >> n >> m;
		for(i = 0; i < n; i++) cin >> mn[i];
		for(i = 0; i < m; i++) cin >> sal[i] >> of[i], oof[i] = of[i];
		for(i = 0; i < n; i++) cin >> a[i];
		ll tot_sal = 0;
		int has_job = 0, no_cd = 0;
		for(i = 0; i < n; i++) {
			int k = -1;
			for(j = 0; j < m; j++)
				if(a[i][j] == '1' && of[j] && sal[j] >= mn[i] && (k == -1 || sal[j] > sal[k]))
					k = j;
			if(k != -1) {
				has_job++;
				tot_sal += sal[k];
				of[k]--;
			}
		}
		for(i = 0; i < m; i++)
			if(of[i] == oof[i])
				no_cd++;
		cout << has_job << ' ' << tot_sal << ' ' << no_cd << '\n';
	}
}
