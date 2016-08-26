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

char s[112345], s2[112345];
int main() {
	int i, n;
	scanf("%d", &n);
	scanf("%s", s);
	int sz = strlen(s);
	int tot = 0;
	for(int j = 0; j < n; j++) {
		scanf("%s", s2);
		int sz2 = strlen(s2);
		if(sz2 < sz - 1 || sz2 > sz + 1) continue;
		if(sz2 == sz + 1) {
			int d = 0;
			for(i = 0; i < sz; i++) {
				if(s[i] != s2[i + d]) {
					if(!d && s[i] == s2[i + 1]) d = 1;
					else break;
				}
			}
			if(i == sz) tot++;
		} else if(sz2 == sz - 1) {
			int d = 0;
			for(i = 0; i < sz2; i++) {
				if(s2[i] != s[i + d]) {
					if(!d && s2[i] == s[i + 1]) d = 1;
					else break;
				}
			}
			if(i == sz2) tot++;
		} else if(sz2 == sz) {
			int dif = 0;
			for(i = 0; i < sz; i++)
				dif += (s[i] != s2[i]);
			if(dif <= 1) tot++;
		}
	}
	printf("%d\n", tot);
}
