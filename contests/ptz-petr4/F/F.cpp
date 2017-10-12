#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int main () {
#ifdef ONLINE_JUDGE
	freopen("rebus.in", "r", stdin);
	freopen("rebus.out", "w", stdout);
#endif
	int ct = 0;
	for(int sz = 0; ; sz++) {
		for(int bm = 0; bm < (1 << sz); bm++) {
			string a = "CBAAE";
			string b = "BBAAD";
			string c = "BCBDB";
			for(int i = 0; i < sz; i++) {
				if((bm >> i) & 1) {
					a.pb('A');
					b.pb('A');
					c.pb('D');
				} else {
					a.pb('E');
					b.pb('D');
					c.pb('B');
				}
			}
			reverse(a.begin(), a.end());
			reverse(b.begin(), b.end());
			reverse(c.begin(), c.end());
			printf("%s+%s=%s\n", a.c_str(), b.c_str(), c.c_str());
			if(++ct == 1000) return 0;
		}
	}

}

