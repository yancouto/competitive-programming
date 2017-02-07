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

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

const int N = 1e3+7;
int n;
int u;
int a[N];

int main() {
	scanf("%d", &u);

	while (u--) {
		scanf("%d", &n);

		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);

		int nm = a[n-1];
		for (int i = n-2; i >= 0; i--) {
			if (a[i] < nm)
				nm = nm - a[i];
			else if (a[i] > nm)
				nm = nm + a[i];
			else
				nm = 0;
		}

		if (!nm) 
			printf("NIE\n");
		else
			printf("TAK\n");
	}
}
