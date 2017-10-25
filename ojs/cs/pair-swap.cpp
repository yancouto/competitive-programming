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

int a[112345];

int main() {
	int i, n, k;
	scanf("%d %d", &n, &k);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	int r = 0;
	set<pii> s;
	for(i = 0; i < n; i++) {
		while(r < i + k + 1 && r < n)
			s.insert(pii(a[r], -r)), r++;
		if(s.begin()->fst < a[i]) {
			swap(a[i], a[-s.begin()->snd]);
			break;
		}
		s.erase(s.find(pii(a[i], i)));
	}
	for(i = 0; i < n; i++)
		printf("%d%c", a[i], " \n"[i == n - 1]);
}
