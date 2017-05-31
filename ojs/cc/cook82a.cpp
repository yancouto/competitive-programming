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
	int i;
	for_tests(tn, tt) {
		map<string, int> mp;
		string s; int g;
		for(i = 0; i < 4; i++) {
			cin >> s >> g;
			mp[s] = g;
		}
		if(mp["RealMadrid"] < mp["Malaga"] && mp["Barcelona"] > mp["Eibar"]) puts("Barcelona");
		else puts("RealMadrid");
	}
}
