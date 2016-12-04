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

char s[212345], p[112345];
int M[212345];

int main() {
	int i, k;
	scanf("%*d %s", p + 1);
	int n = strlen(p + 1);
	for(i = 1; i <= n; i++) s[2 * i - 1] = p[i];
	for(i = 2; i < 2 * n - 1; i += 2) s[i] = '$';
	k = -1;
	for(i = 1; s[i]; i++) {
		if(k != -1 && k + M[k] > i && M[2 * k - i] < k + M[k] - i)
			M[i] = M[2 * k - i];
		else {
			if(k != -1 && k + M[k] > i)
				M[i] = k + M[k] - i;
			else
				M[i] = 0;
			k = i;
			while(i - M[i] > 1 && s[i - M[i] - 1] == s[i + M[i] + 1])
				M[i]++;
		}
	}
	//for(i = 1; s[i]; i++) printf("%c ", s[i]); putchar('\n');
	//for(i = 1; s[i]; i++) printf("%d ", M[i]); putchar('\n');
	int lg = 1;
	for(i = 1; i <= n; i++)
		lg = max(lg, (M[2 * i - 1] / 2) * 2 + 1);
	for(i = 1; i < n; i++)
		lg = max(lg, ((M[2 * i] + 1) / 2) * 2);
	printf("%d\n", lg);
}
