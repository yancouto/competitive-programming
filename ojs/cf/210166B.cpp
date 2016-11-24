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

int n, m;
char g[100][100];

void imp() {
	puts("Wrong Answer");
	exit(0);
}

int main() {
	int i, j;
	rd(n); rd(m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf(" %c", &g[i][j]);
	if(g[0][0] != '#') imp();
	i = 0, j = 0;
	g[0][0] = '.';
	while(i != n - 1 || j != m - 1) {
		if(i < n && g[i + 1][j] == '#') g[++i][j] = '.';
		else if(j < m && g[i][j + 1] == '#') g[i][++j] = '.';
		else imp();
	}
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			if(g[i][j] == '#')
				imp();
	puts("Accepted");
}
