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
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int a, b;
int s[112];
int oc[112], no[112];

int gen(int i) {
	i = i % (2 * (a + b));
	return s[i];
}

int main() {
	int l, r, i;
	scanf("%d %d %d %d", &a, &b, &l, &r); l--; r--;
	int sn = 0;
	for(i = 0; i < a; i++) s[sn++] = i;
	int c = s[sn - 1];
	for(i = 0; i < b; i++) s[sn++] = c;
	for(i = sn - a; i < sn; i++) no[s[i]] = 1;
	int nx = -1;
	for(i = 0; i < a; i++) {
		nx++;
		while(no[nx]) nx++;
		s[sn++] = nx;
	}
	c = s[sn - 1];
	for(i = 0; i < b; i++) s[sn++] = c;
	if(r - l + 1 <= 100) {
		for(i = l; i <= r; i++)
			oc[gen(i)] = 1;
	} else {
		for(i = 0; i < sn; i++)
			oc[s[i]] = 1;
	}
	printf("%d\n", accumulate(oc, oc + 100, 0));
}
