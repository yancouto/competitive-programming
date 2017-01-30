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

int v[300];

int solve (vector<int> a) {
	int r = 0;
	int s = 0;
	int cnt = 0;
	for (int x : a) {
		if (x == 0) continue;
		int loc = 0;
		loc -= r;
		for (int i = 0; i < 52; i++) {
			loc += (!v[i+r+s+1]);
		}
		r += x;
		s++;
		cnt += loc*x;
	}
	return cnt;
}

int printa (vector<int> a) {
	int x = 1;
	for (int v : a) {
		if (v == 0) continue;
		for (int i = 0; i < v; i++)
			printf("%d ", x+i);
		x += v + 1;
	}
	printf("\n");
}

int main() {
	for (int i = 0; i < 4; i++) {
		int a;
		scanf("%d", &a);
		v[a]++;
	}

	int r = 53*4;
	for (int a = 0; a <= 4; a++)
		for (int b = 0; b < 4; b++)
			for (int c = 0; c < 4; c++)
				for (int d = 0; d < 4; d++) {
					if (a+b+c+d != 4) continue;
					r = min(r, solve({a,b,c,d}));
				}
	for (int a = 0; a <= 4; a++)
		for (int b = 0; b < 4; b++)
			for (int c = 0; c < 4; c++)
				for (int d = 0; d < 4; d++) {
					if (a+b+c+d != 4) continue;
					if (r == solve({a,b,c,d})) {
						printa({a,b,c,d});
						return 0;
					}
				}

				
}
