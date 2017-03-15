#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 112345;
char s[N], ch[N];
int st[N], sn;

int main() {
	int i, n, k, j;
	scanf("%d %d", &n, &k);
	scanf("%s", s);
	for(i = 0; i < n; i++) {
		if(sn > 0 && ch[sn - 1] == s[i]) st[sn - 1]++;
		else st[sn] = 1, ch[sn] = s[i], sn++;
		if(sn > 0 && st[sn - 1] == k) sn--;
	}
	for(i = 0; i < sn; i++)
		for(j = 0; j < st[i]; j++)
			putchar(ch[i]);
	putchar('\n');
}
