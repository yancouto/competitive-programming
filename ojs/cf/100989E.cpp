#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

char s1[200], s2[200];
int main() {
	int i, j, n;
	scanf("%s %s", s1, s2);
	bool ok;
	if(strlen(s1) < 8) ok = (strcmp(s1, s2) == 0);
	else if(strlen(s1) == strlen(s2)) {
		int ct = 0;
		for(i = 0; s1[i]; i++)
			ct += (s1[i] != s2[i]);
		ok = (ct <= 1);
	} else if(strlen(s1) != strlen(s2) + 1) ok = false;
	else {
		bool dif = false;
		for(i = 0; s1[i]; i++)
			if(s1[i + dif] != s2[i]) {
				if(dif) { ok = false; break; }
				else { dif = true; i--; }
			}
		if(!s1[i]) ok = true;
	}
	if(ok) puts("yes");
	else puts("no");
}
