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

int n;
const int N = 100009, K = 101;

int z[K][N];
char s[K][N];
char b[K][N];
int sz[K]; int pai[N], acc[N];


void calc(char s[], int z[], int n) {
	int l = -1;
	for(int i = 1; i < n; i++) {
		if(l == -1 || l + z[l] <= i) { for(; i + z[i] < n && s[i + z[i]] == s[z[i]]; z[i]++); l = i; }
		else if(z[i - l] >= l + z[l] - i) {
			z[i] = l + z[l] - i;
			for(; i + z[i] < n && s[i + z[i]] == s[z[i]]; z[i]++);
			l = i;
		} else z[i] = z[i - l];
	}
}


short seen[50009][103];
bool memo[50009][103];
int solve(int p, int i) {
	bool &r = memo[p][i];
	if(seen[p][i] == 2) return r;
	if(seen[p][i] == 1) return 0;
	seen[p][i] = 1;
	if(i == n) {
		for(i = 0; i < n; i++)
			if(solve(p, i))
				return r = 1;
		return r = 0;
	}
	int k = z[i][p + sz[i]];
	//printf("%d, %d [%d]\n", p, i, k);
	int sp = acc[pai[p]] - p;
	if(sz[i] == sp) {
		//printf("=\n");
		if(k >= sp) r = 1;
		else r = 0;
	} else if(sz[i] < sp) {
		//printf("<\n");
		if(k >= sz[i]) r = solve(p + sz[i], n);
		else r = 0;
	} else {
		//printf(">\n");
		if(k >= sp) r = solve((i? acc[i - 1] : 0) + sp, n);
		else r = 0;
	}
	seen[p][i] = 2;
	return r;
}

int main() {
	int i, j;
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%s", s[i]);
	for(i = 0; i < n; i++) {
		strcpy(b[i], s[i]);
		sz[i] = strlen(s[i]);
		for(j = 0; j < n; j++) {
			strcpy(b[i] + sz[i], s[j]);
			sz[i] += strlen(s[j]);
		}
		calc(b[i], z[i], sz[i]);
	}
	for(i = 0; i < n; i++) sz[i] = strlen(s[i]);
	acc[0] = sz[0];
	for(i = 1; i < n; i++) acc[i] = sz[i] + acc[i - 1];
	//for(i = 0; i < n; i++) strcpy(all + (i? acc[i - 1] : 0), s[i]);
	int k = 0;
	for(i = 0; i < n; i++)
		for(j =  i? acc[i-1] : 0; j < acc[i]; j++)
			pai[j] = i;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			if(solve(i? acc[i - 1] : 0, j)) {
				puts("YES");
				return 0;
			}
	puts("NO");
}
