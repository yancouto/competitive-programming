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

template<class num> inline void read(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int get (int i) {
	if (i == 0)
		return 6;
	if (i == 1)
		return 2;
	if (i == 2)
		return 5;
	if (i == 3)
		return 5;
	if (i == 4)
		return 4;
	if (i == 5)
		return 5;
	if (i == 6)
		return 6;
	if (i == 7)
		return 3;
	if (i == 8)
		return 7;
	if (i == 9)
		return 6;
	assert(false);
}

int n;

int main() {
	freopen("alarm.in", "r", stdin);
	freopen("alarm.out", "w", stdout);
	scanf("%d", &n);

	int curr = 0;
	for (int i = 0; i < 24; i++)
		for (int j = 0; j < 60; j++)
			if(get(i/10) + get(i%10) + get(j/10) + get(j%10) == n) {
				printf("%02d:%02d\n", i, j);
				return 0;
			}

	printf("Impossible\n");
}
