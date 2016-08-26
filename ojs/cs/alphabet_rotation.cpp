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

string S[112345];
multiset<string> mp;

char s[112345];
int main() {
	int i, j, k, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%s", s);
		S[i] = s;
		mp.insert(S[i]);
	}
	for(i = 0; i < n; i++) {
		mp.erase(mp.find(S[i]));
		for(j = 0; j < 26; j++) {
			for(k = 0; k < S[i].size(); k++)
				s[k] = 'a' + (((S[i][k] - 'a') + j) % 26);
			s[k] = 0;
			if(mp.find(s) != mp.end()) { puts("1"); break; }
		}
		if(j == 26) puts("0");
		mp.insert(S[i]);
	}
}
