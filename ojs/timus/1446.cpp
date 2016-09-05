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

map<string, vector<string>> mp;
char s[1123], h[1123];
int main() {
	int i, n;
	scanf("%d", &n); getchar();
	for(i = 0; i < n; i++) {
		fgets(s, sizeof s, stdin);
		fgets(h, sizeof h, stdin);
		h[strlen(h)-1] = 0;
		mp[h].pb(s);
	}
	for(string h : {"Slytherin", "Hufflepuff", "Gryffindor", "Ravenclaw"}) {
		printf("%s:\n", h.c_str());
		for(string s : mp[h])
			printf("%s", s.c_str());
		if(h[0] != 'R') putchar('\n');
	}
}
