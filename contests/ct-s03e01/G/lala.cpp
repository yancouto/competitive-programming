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
int ty;
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
		ty = 0;
		pl = 0;
		lf = 0;
		rdl = 15;
		for (int k = 2; k <= 7; k++)
			lf += k;

		for (i = 0; min(s[0], s[1]) + lf + rd + 7*rdl >= max(s[0], s[1]); i++) {
			assert(i < n);
			scanf("%d", &a);

			s[pl] += a;

			rdl = rd;
			if (a == 1) {
				rd--;
			}

			if (!a) pl = !pl;

			if (ty == 2)
				lf = max(0, lf-a);
			else if (ty == 1){
				ty = 2;
			} else if (!rd)
				ty = 1;

		}

		printf("%d\n", i);

		while (i < n) {
			scanf("%d", &a);
			i++;
		}
	}
}
