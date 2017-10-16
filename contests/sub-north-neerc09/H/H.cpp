#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n;
map<int,int> mp;
int qt, cn;
char str[30];
int x;

int main () {
#ifdef ONLINE_JUDGE
	freopen("homo.in", "r", stdin);
	freopen("homo.out", "w", stdout);
#endif

	scanf("%d", &n);
	qt = cn = 0;
	for (int i = 0; i < n; i++) {
		scanf(" %s %d", str, &x);

		if (str[0] == 'i') {
			mp[x]++;
			if (mp[x] == 2)
				qt++;
			else if (mp[x] == 1)
				cn++;
		} else if (mp[x]) {
			mp[x]--;
			if (mp[x] == 1)
				qt--;
			else if (mp[x] == 0)
				cn--;
		}

		if (qt && cn > 1)
			printf("both\n");
		else if (cn > 1)
			printf("hetero\n");
		else if (qt)
			printf("homo\n");
		else
			printf("neither\n");
	}
}

