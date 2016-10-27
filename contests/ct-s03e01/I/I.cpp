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

int n, en;
char s[1123456], c[1123456];
int L[1123456], R[1123456];

int main() {
	int i, j;
	scanf("%*d");
	while(scanf("%s", s) != EOF) {
		en = 1;
		int cur = 0;
		for(i = 0; s[i]; i++)
			if(s[i] == '-' && cur) {
				int nx = L[cur];
				L[R[cur]] = L[cur];
				R[L[cur]] = R[cur];
				cur = nx;
			} else if(s[i] == '<' && cur)
				cur = L[cur];
			else if(s[i] == '>' && R[cur])
				cur = R[cur];
			else if(isalnum(s[i])) {
				int nx = en++;
				c[nx] = s[i];
				L[nx] = cur;
				R[nx] = R[cur];
				R[L[nx]] = L[R[nx]] = nx;
				cur = nx;
			}
		cur = R[0];
		while(cur) { putchar(c[cur]); cur = R[cur]; }
		putchar('\n');
		for(i = 0; i <= en; i++)
			L[i] = R[i] = 0;
	}
}
