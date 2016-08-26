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

char s[1123456];
int main() {
	fgets(s, sizeof s, stdin);
	int ct = 0;
	for(int i = 0; s[i]; i++)
		if(s[i] == '!')
			ct++;
	if(ct == 0) puts("Pfff");
	else {
		putchar('W');
		for(int i = 0; i < ct; i++) putchar('o');
		printf("w\n");
	}
}
