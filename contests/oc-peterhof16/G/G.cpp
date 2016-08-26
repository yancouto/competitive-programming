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

int seen[1123456];

char s[100];
bool ok() {
	scanf("%s", s);
	return s[0] == 'y';
}

int main() {
	int i, cur = 0;
	while(true) {
		puts("1"); fflush(stdout);
		if(ok()) return 0;
		for(i = 2; ; i++)
			if(!seen[i] && i != cur) {
				printf("%d\n", i); fflush(stdout);
				if(ok()) { cur = i; seen[i] = 1; break; }
			}
	}
}
