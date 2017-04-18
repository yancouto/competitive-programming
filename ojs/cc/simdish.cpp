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

int main() {
	string a;
	int i;
	for_tests(t, tt) {
		set<string> s1;
		for(i = 0; i < 4; i++) {
			cin >> a;
			s1.insert(a);
		}
		int ct = 0;
		for(i = 0; i < 4; i++) {
			cin >> a;
			ct += s1.count(a);
		}
		if(ct >= 2) puts("similar");
		else puts("dissimilar");
	}
}
