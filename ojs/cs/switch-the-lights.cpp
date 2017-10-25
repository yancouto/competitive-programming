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

char on[112345];

int main() {
	int i, n, R, c;
	scanf("%d %s", &n, on);
	priority_queue<int> pq;
	for(i = 0; i < n; i++) {
		scanf("%d", &R);
		while(!pq.empty() && -pq.top() < i) pq.pop();
		if((on[i] == '1') ^ (pq.size() & 1)) {
			on[i] = '1';
			pq.push(-(R-1));
		} else
			on[i] = '0';
	}
	ll tot = 0;
	for(i = 0; i < n; i++) {
		scanf("%d", &c);
		if(on[i] == '1') tot += c;
	}
	printf("%lld\n", tot);
}
