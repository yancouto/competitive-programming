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

char a[112345], b[112345];
int nx[30][112345];

int main() {
	int i, j;
	scanf("%s %s", a, b);
	int na = strlen(a), nb = strlen(b);
	for(i = 0; i < 26; i++)
		nx[i][na] = na;
	for(j = 0; j < 26; j++)
		for(i = na - 1; i >= 0; i--)
			if(a[i] == 'a' + j)
				nx[j][i] = i;
			else
				nx[j][i] = nx[j][i + 1];
	for(j = 0; b[j]; j++)
		if(nx[b[j] - 'a'][0] == na) {
			puts("-1");
			return 0;
		}
	i = 0;
	int ans = 1;
	for(j = 0; b[j]; j++) {
		i = nx[b[j] - 'a'][i];
		if(i == na) {
			ans++;
			i = nx[b[j] - 'a'][0];
		}
		i++;
	}
	printf("%d\n", ans);
}
