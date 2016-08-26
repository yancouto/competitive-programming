#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

map<string, int> ass;
set<string> died;
char s1[100], s2[100];
int main() {
	while(scanf(" %s %s", s1, s2) != EOF) {
		string ss1(s1), ss2(s2);
		ass[s1]++;
		died.insert(s2);
	}
	puts("HALL OF MURDERERS");
	for(auto &e : ass) {
		if(died.count(e.fst)) continue;
		printf("%s %d\n", e.fst.c_str(), e.snd);
	}
	return 0;
}
