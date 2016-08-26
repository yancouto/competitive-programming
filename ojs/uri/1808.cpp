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

char s[1002];
int main() {
	scanf("%s", s);
	int n = 0, tot = 0;
	for(int i = 0; s[i]; i++) {
		if(s[i] == '1') {
			if(s[i + 1] == '0') tot += 10, i++;
			else tot++;
		} else tot += s[i] - '0';
		n++;
	}
	printf("%.2f\n", double(tot)/n);
}
