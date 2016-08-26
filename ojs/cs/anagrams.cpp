#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

char S[112345];

int main() {
	int i, n;
	map<string, int> mp;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%s", S);
		string s = S;
		sort(s.begin(), s.end());
		mp[s]++;
	}
	int mx = 0;
	for(auto p : mp)
		mx = max(mx, p.snd);
	printf("%d\n", mx);
}
