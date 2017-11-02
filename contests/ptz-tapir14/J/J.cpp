#include <bits/stdc++.h>
#define cout if (0)

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 212345;
int p[N], pw[N], bk[N];

int main () {
#ifdef ONLINE_JUDGE
	freopen("joy.in", "r", stdin);
	freopen("joy.out", "w", stdout);
#endif
	int i, n, m, a, b, c;
	scanf("%d %d", &n, &m);
	ll tot = 0;
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		if(a == b) {
			printf("%lld\n", tot);
			continue;
		}
		deque<int> ca, cb;
		for(int aa = a; aa; aa = p[aa]) ca.push_front(aa);
		for(int bb = b; bb; bb = p[bb]) cb.push_front(bb);
		if(ca.front() != cb.front()) {
			for(int j = 0; j < int(cb.size()) - 1; j++)
				p[cb[j]] = cb[j + 1], pw[cb[j]] = pw[cb[j + 1]];
			p[b] = a;
			pw[b] = c;
			tot += c;
			printf("%lld\n", tot);
			continue;
		}
		while(ca.size() > 1u && cb.size() > 1u && ca.front() == cb.front() && ca[1] == cb[1])
			ca.pop_front(), cb.pop_front();
		int mx = -10;
		int mxi;
		bool ina = true;
		for(int j = 1; j < int(ca.size()); j++) {
			if(pw[ca[j]] > mx) {
				mxi = ca[j];
				mx = pw[ca[j]];
				ina = true;
			}
		}
		for(int j = 1; j < int(cb.size()); j++) {
			if(pw[cb[j]] > mx) {
				mxi = cb[j];
				mx = pw[cb[j]];
				ina = false;
			}
		}
		assert(mx != -10);
		if(c < mx) {
			tot += c - mx;
			if(!ina) {
				swap(a, b);
				ca.swap(cb);
			}
			bk[a] = pw[a];
			if(mxi != a) {
				for(int j = int(ca.size()) - 1; j > 0; j--) {
					p[ca[j - 1]] = ca[j];
					bk[ca[j - 1]] = pw[ca[j - 1]];
					pw[ca[j - 1]] = bk[ca[j]];
					if(ca[j - 1] == mxi)
						break;
				}
			}
			p[a] = b;
			pw[a] = c;
		}
		printf("%lld\n", tot);
	}
}
