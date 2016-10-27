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

const int N = 1e3+7;

int a;
int n;
int ts;
int lf;
int rd;
int s[2];
int pl;
int i;
int rdl;

int main() {
	scanf("%d", &ts);
	while (ts--) {
		scanf("%d", &n);

		s[0] = s[1] = 0;
		rd = 15;
		pl = 0;
		lf = 0;
		rdl = 15;
		for (int k = 2; k <= 7; k++)
			lf += k;

		for (i = 0; min(s[0], s[1]) + lf + 8*rd + 7*((rdl!=rd)&&(min(s[0], s[1]) == s[pl])) >= max(s[0], s[1]); i++) {
			assert(i < n);
			scanf("%d", &a);

			if (!rdl)
				lf = max(0, lf-a);

			s[pl] += a;

			rdl = rd;
			if (a == 1) {
				rd--;
			}

			if (!a) pl = !pl;
		}

		printf("%d\n", i);

		while (i < n) {
			scanf("%d", &a);
			i++;
		}
	}
}
