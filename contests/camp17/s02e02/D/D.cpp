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

const int N = 5e4+7;
char str[2][N];
int n;
char s[2*N];
int z[2*N];

void calc() {
	int l = -1;
	for(int i = 1; i < 2*n+1; i++) {
		if(l != -1 && l + z[l] - 1 >= i)
			z[i] = min(l + z[l] - i, z[i - l]);
		while(i + z[i] < 2*n+1 && s[i + z[i]] == s[z[i]]) { z[i]++; }
		if(l == -1 || i + z[i] > l + z[l])
			l = i;
	}
}

int main() {
	scanf(" %s %s", str[0], str[1]);
	n = strlen(str[0]);
	
	if (n != strlen(str[1])) {
		printf("No\n");
		return 0;
	}

	int b = 0;
	for (int i = 0; i < n && str[0][i] == str[1][n-i-1]; i++, b++);
	
	for (int i = 0; i < n; i++)
		s[i] = str[1][i];
	s[n] = '#';
	for (int i = 0; i < n; i++)
		s[i+n+1] = str[0][i];

	calc();

	for (int i = 0; i <= b; i++) {
		if (z[n+1+i] >= n-i) {
			printf("Yes\n%d\n", i);
			return 0;
		}
	}

	printf("No\n");
}
