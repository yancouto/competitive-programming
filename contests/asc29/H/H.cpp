#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

#define pb push_back

const int N = 2e5+7;

int n;
int c[N][2];
int totf;
int qt[N][2];
int ex[N];
int v[N];
char res[N];
char cr[N];
int p[N];

int main() {
#ifdef ONLINE_JUDGE
	freopen("truth.in", "r", stdin);
	freopen("truth.out", "w", stdout);
#endif

	scanf("%d", &n);

	int nmr = -1;
	for (int i = 0; i < n; i++) {
		scanf(" %c", &cr[i]);

		if (cr[i] == '$') {
			nmr = i;
			scanf("%d", &v[i]);
		}
	}

	if (nmr == -1) {
		for (int k = 0; k < 2; k++) {
			int nx = k;
			for (int i = 0; i < n; i++) {
				if (nx == 0)
					res[i] = 'f';
				else
					res[i] = 't';

				nx = !((cr[i] == '+')^(nx == 1));
			}
			
			if (nx == k) {
				printf("consistent\n");
				printf("%s\n", res);
				return 0;
			}
		}

		printf("inconsistent\n");
		return 0;
	}

	int ls = 0;
	for (int _i = 0; _i < n; _i++) {
		int i = (_i + nmr + 1 + n)%n;
		if (ls) {
			c[i][0] = c[(i+n-1)%n][ls==-1];
			c[i][1] = c[(i+n-1)%n][ls==1]+1;
		} else {
			c[i][0] = 0;
			c[i][1] = 1;
		}

		if (cr[i] == '$') {
			qt[v[i]][1] += c[i][1];
			qt[v[i]][0] += c[i][0];
			totf += c[i][0];
		} else {
			v[i] = -1;
		}

		if (cr[i] == '$')
			ls = 0;
		else if (cr[i] == '+')
			ls = 1;
		else
			ls = -1;
	}


	for (int rs = 0; rs < N; rs++) {
		if (totf - qt[rs][0] + qt[rs][1] == rs) { 
			printf("consistent\n");

			res[n] = 0;
			int nxt = 0;
			for (int _i = n-1; _i >= 0; _i--) {
				int j = (_i + nmr + 1 + n)%n;
				if (cr[j] == '$') {
					if (v[j] == rs)
						nxt = 1;
					else
						nxt = 0;
				} else if (cr[j] == '-') {
					nxt = !nxt;
				}
				
				if (nxt == 1)
					res[j] = 't';
				else
					res[j] = 'f';
			}
			printf("%s\n", res);
			return 0;
		}
	}

	printf("inconsistent\n");
}
