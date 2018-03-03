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
#	define debug(args...) ((void) 0)
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

int n;
const int N = 2123456;

int c[N * 2], cn;
int bl[2][N * 2];

int walk(int, int);
int t;

int memo[2][N * 2];
int solve(int i, int j) {
	if(j == 0) return i? -2 : 0;
	int &r = memo[i][j];
	if(r != -1) return r;
	if(walk(i, j - 1) == -2) r = -2;
	else if(bl[i][j] && walk(i, j - 1) < t) r = -2;
	else r = walk(i, j - 1) + 1 - bl[i][j] * t;
	//printf("solve(%d, %d) = %d\n", i, j, r);
	return r;
}

int walk(int i, int j) {
	int r = solve(i, j);
	if(!bl[i][j]) r = max(r, min(solve(!i, j), t));
	//printf("walk(%d, %d) = %d\n", i, j, r);
	return r;
}
int a[2][N];

deque<int> mv;
deque<int> shs;
int ts = 0;

void buildw(int, int, int);

void build(int i, int j, int sh) {
	if(j == 0) return;
	//printf("build(%d, %d)\n", i, j);
	//if(bl[i][j]) printf("shot (%d, %d)\n", i, c[j]);
	if(bl[i][j]) ts++;
	return buildw(i, j - 1, sh + bl[i][j]);
}

void buildw(int i, int j, int sh) {
	if(j == 0) {
		if(walk(i, j) != solve(i, j)) {
			mv.push_front(0);
			shs.push_front(sh);
			sh = 0;
		}
		shs.push_front(sh);
		return;
	}
	if(walk(i, j) == solve(i, j)) return build(i, j, sh);
	mv.push_front(c[j]);
	shs.push_front(sh);
	return build(!i, j, 0);
}

int main() {
	int m[2];
	int i, j;
	rd(n); rd(m[0]); rd(m[1]); rd(t);
	for(i = 0; i < 2; i++)
		for(j = 0; j < m[i]; j++) {
			rd(a[i][j]);
			c[cn++] = a[i][j];
			c[cn++] = a[i][j] + 1;
			c[cn++] = a[i][j] - 1;
		}
	c[cn++] = 0;
	c[cn++] = n + 1;
	sort(c, c + cn);
	cn = unique(c, c + cn) - c;
	for(i = 0; i < 2; i++)
		for(j = 0; j < m[i]; j++) {
			a[i][j] = lower_bound(c, c + cn, a[i][j]) - c;
			bl[i][a[i][j]] = 1;
			//printf("bl[%d][%d] = 1\n", i, c[a[i][j]]);
		}
	memset(memo, -1, sizeof memo);
	if(walk(0, cn - 1) != -2) {
		puts("Yes");
		buildw(0, cn - 1, 0);
		printf("%d\n", int(mv.size()));
		for(int x : mv)
			printf("%d ", x);
		putchar('\n');
		printf("%d\n", ts);
		for(int i = 0; i < shs[0]; i++)
			printf("%d 1\n", t * (i + 1));
		int cur = 0;
		for(int i = 0; i < int(mv.size()); i++) {
			cur = !cur;
			int dt = t - walk(cur, mv[i]);
			for(int j = 0; j < shs[i + 1]; j++)
				printf("%d %d\n", dt + j * t + mv[i], cur + 1);
		}
	} else {
		puts("No");
	}
}
