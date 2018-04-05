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

char s[1123456];
int nx[30][1123456];

int main() {
	int i, j;
	scanf("%s", s);
	int n = strlen(s);
	for(j = 0; j < 26; j++) {
		nx[j][n] = n;
		for(i = n - 1; i >= 0; i--)
			if(s[i] == ('a' + j))
				nx[j][i] = i;
			else
				nx[j][i] = nx[j][i + 1];
	}
	int ct;
	i = 1;
	for(ct = 1; i < n; ct++) {
		int fst = i - 1;
		int cur = nx[s[i] - 'a'][0];
		if(cur > fst) { i++; continue; }
		while(i < n && cur <= fst)
			if(++i < n)
				cur = nx[s[i] - 'a'][cur + 1];
	}
	printf("%d\n", ct);
}
