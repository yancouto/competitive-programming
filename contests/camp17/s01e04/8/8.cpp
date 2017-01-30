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

const int N = 1003;

int n;
int c;
int tp[N];
int qt[N];
int pr[N];
char str[4];

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d", &n);

	int res = 0;
	int ev = 0;

	for (int i = 0; i < n; i++) {
		scanf("%d", &c);
		tp[i] = -1;
		int fs = -1;
		pr[i] == 0;
		for (int j = 0; j < c; j++) {
			scanf(" %s", str);
			bool cr = (str[0] == 'c');
			if (!cr)
				pr[i]++;
			if (fs == -1)
				fs = cr;

			if (cr == tp[i]) continue;

			qt[i]++;
			tp[i] = cr;
		}
		tp[i] = fs;
		
		if (!tp[i]) {
			res++;
			tp[i] = 1;
			qt[i]--;
		}

		if (pr[i])
			ev++;
		//if ((qt[i] >= 2 && qt[i]%2 == 0) || (qt[i] == 0 && c > 0)) { // qt[i] > 0 ?
			//ev++;
		//}
	}

	if (n == 1) {
		if (qt[0] == 0)
			printf("%d\n", res);
		else if (qt[0] == 3)
			printf("%d\n", res + 2);
		else if (qt[0] <= 2)
			printf("%d\n", res + 1);
		else 
			printf("-1\n");
		return 0;
	}

	int loc = 7;
	for (int i = 0; i < n; i++) {
		res += qt[i];

		if (qt[i] <= 1)
			loc = min(loc, 0);
		else if (qt[i] <= 3)
			loc = min(loc, -1);
		else if (pr[i])
			loc = min(loc, -(ev>1));
		else
			loc = min(loc, -(ev>0));
	}

	printf("%d\n", res+loc);
}
