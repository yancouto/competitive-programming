#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
typedef long long int ll;

const ll modn = 1000000007;
const ll B = 261;
inline ll mod(ll x) { return x % modn; }
const int N = 512345, D = 30;

ll H[N];
int a[N], n;
char s[N];
ll h[D][D];
vector<int> p[D];
int mrk[D];
ll pot[N];

int main () {
	int i, c, d;
	scanf("%s", s);
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	int m = strlen(s);
	for(i = m - 1; i >= 0; i--)
		H[i] = mod(H[i + 1] * B + s[i]);
	pot[0] = 1;
	for(i = 1; i < N; i++)
		pot[i] = mod(pot[i - 1] * B);
	for(c = 0; c < 26; c++) {
		for(i = 0; i < n; i++)
			if(a[i] == c + 1)
				p[c].pb(i);
		for(d = 0; d < 26; d++)
			for(int i : p[c])
				h[c][d] = mod(h[c][d] + pot[i] * ll(d + 'a'));
	}
	int oc = 0;
	for(i = 0; i <= m - n; i++) {
		ll cur = 0;
		for(c = 0; c < 26; c++) mrk[c] = 0;
		for(c = 0; c < 26; c++)
			if(!p[c].empty()) {
				int t = s[i + p[c].front()] - 'a';
				if(mrk[t]) break;
				mrk[t] = 1;
				cur = mod(cur + h[c][t]);
			}
		if(c == 26 && cur == mod(H[i] - mod(H[i + n] * pot[n]) + modn))
			oc++;
	}
	printf("%d\n", oc);
}
