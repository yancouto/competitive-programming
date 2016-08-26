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

int n;
char s[1123];
char s2[111];
bool ok(int x) {
	sprintf(s2, "%d", x);
	int sz = strlen(s2);
	for(int i = 0; i < n - sz + 1; i++) {
		int j;
		for(j = 0; j < sz && s[i + j] == s2[j]; j++);
		if(j == sz) return true;
	}
	return false;
}

int main() {
	int i;
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; i++) scanf(" %c", &s[i]);
		for(i = 0; ok(i); i++);
		printf("%d\n", i);
	}
}
