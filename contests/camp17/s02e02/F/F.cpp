#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const int modn = 1000000009;
inline int mod(int x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
char s[1123];
int p[1123];
int K[10009][1009];
int G[10009][1009];
int go[1009][2];

int main() {
	int i, j, k;
	scanf("%s %d", s, &k);
	n = strlen(s);
	s[n++] = '$';
	for(i = 2; i <= n; i++) {
		p[i] = p[i - 1];
		while(p[i] && s[p[i]] != s[i - 1])
			p[i] = p[p[i]];
		if(s[p[i]] == s[i - 1]) p[i]++;
	}
	go[0][0] = (s[0] == 'a');
	go[0][1] = (s[0] == 'b');
	for(i = 1; i < n; i++) {
		if(s[i] == 'a') go[i][0] = i + 1, go[i][1] = go[p[i]][1];
		else if(s[i] == 'b') go[i][0] = go[p[i]][0], go[i][1] = i + 1;
		else go[i][0] = go[p[i]][0], go[i][1] = go[p[i]][1];
	}
	for(i = 0; i < n; i++) G[1][i] = go[i][0];
	for(i = 0; i < n; i++) G[2][i] = go[i][1];
	for(j = 3; j <= k; j++)
		for(i = 0; i < n; i++)
			G[j][i] = G[j - 1][G[j - 2][i]];
	for(i = 0; i < n; i++) K[1][i] = (go[i][0] == n - 1);
	for(i = 0; i < n; i++) K[2][i] = (go[i][1] == n - 1);
	for(j = 3; j <= k; j++)
		for(i = 0; i < n; i++) {
			K[j][i] = mod(K[j - 2][i] + K[j - 1][G[j - 2][i]]);
		}
	printf("%d\n", K[k][0]);
}
