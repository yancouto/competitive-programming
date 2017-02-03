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

const int N = 1123456;
char t[N], p[N];

vector<int> z(string &s) {
	vector<int> Z(s.size());
	int l = -1;
	Z[0] = 0;
	for(int i = 1; i < s.size(); i++) {
		if(l != -1 && l + Z[l] - 1 >= i)
			Z[i] = min(l + Z[l] - i, Z[i - l]);
		while(i + Z[i] < s.size() && s[Z[i]] == s[i + Z[i]]) Z[i]++;
		if(l == -1 || i + Z[i] > l + Z[l])
			l = i;
	}
	return Z;
}

int main() {
	int i, j, k;
	scanf("%s %s %d", t, p, &k);
	string p1 = p;
	p1 += t;
	reverse(t, t + strlen(t));
	reverse(p, p + strlen(p));
	string p2 = p;
	p2 += t;
	vector<int> z1 = z(p1), z2 = z(p2);
	int np = strlen(p);
	int nt = strlen(t);
	vector<int> oc;
	for(i = 0; i < nt - np + 1; i++) {
		if(z1[np + i] + z2[np + nt - 1 - (i + np - 1)] >= np - k)
			oc.pb(i + 1);
	}
	printf("%d\n", (int) oc.size());
	for(int x : oc) printf("%d ", x); putchar('\n');
}
