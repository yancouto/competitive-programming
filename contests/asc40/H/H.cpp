#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

char *ans[] = {
	"1",
	"2",
	"5",
	"14",
	"42",
	"165",
	"714",
	"3094",
	"14858",
	"79534",
	"447051",
	"2714690",
	"17395070",
	"114371070",
	"783152070",
	"5708587335",
	"43848093003",
	"342444658094",
	"2803119896185",
	"23619540863730",
	"201813981102615",
	"1793779293633437",
	"16342050964565645",
	"154170926013430326",
	"1518409177581024365",
	"15259825120722837478",
	"154870329715038713659",
	"1601991088154989174258",
	"16725278985898957454695",
	"177792163538134124432895"
};

int main() {
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(...) fprintf(stderr, ...)
	freopen("handsome.in", "r", stdin);
	freopen("handsome.out", "w", stdout);
#else
#	define LLD "%lld"
#	define debug(...) {}
#endif
	int i = 0, j, n;
	while(scanf("%d", &n) != EOF && n)
		printf("Case #%d: %s\n", ++i, ans[n-1]);
}
