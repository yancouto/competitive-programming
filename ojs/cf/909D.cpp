#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

char s[1123456];

int main() {
	int i, j;
	scanf("%s", s);
	int lst = s[0];
	int ct = 1;
	vector<pii> v;
	for(i = 1; s[i]; i++) {
		if(s[i] != lst) {
			v.pb(pii(lst, ct));
			lst = s[i];
			ct = 0;
		}
		ct++;
	}
	v.pb(pii(lst, ct));
	ct = 0;
	while(v.size() > 1) {
		ct++;
		for(i = 1; i < int(v.size()) - 1; i++)
			v[i].snd -= 2;
		v.front().snd--;
		v.back().snd--;
		vector<pii> v2;
		for(i = 0; i < v.size() && v[i].fst <= 0; i++);
		if(i == v.size()) break;
		v2.pb(v[i]);
		for(i++; i < v.size(); i++) {
			if(v[i].snd <= 0) continue;
			if(v2.back().fst == v[i].fst)
				v2.back().snd += v[i].snd;
			else
				v2.pb(v[i]);
		}
		v.swap(v2);
	}
	printf("%d\n", ct);
}
