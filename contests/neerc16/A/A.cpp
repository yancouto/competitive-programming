#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 1e3+7;
char str[N];
int st, en, n;
int cnt;

inline bool upp (char c)
{ return (c >= 'A' && c <= 'Z'); }
inline bool low (char c)
{ return (c >= 'a' && c <= 'z'); }
inline bool ischar (char c)
{ return upp(c) || low(c); }
inline bool white (char c)
{ return (c == ' ' || c == '.' || c == ',' || c == '\n'); }

void flusha (int curr) {
	if (cnt >= 2) {
		for (int i = st; i < en; i++)
			if (upp(str[i]))
				putchar(str[i]);
		putchar(' ');
		putchar('(');

		for (int i = st; i < en; i++)
			putchar(str[i]);

		putchar(')');
		for (int i = en; i <= curr; i++)
			putchar(str[i]);
	} else {
		for (int i = st; i <= curr; i++)
			putchar(str[i]);
	}
}

int main () {
	freopen("abbreviation.in", "r", stdin);
	freopen("abbreviation.out", "w", stdout);
	while (fgets(str, N, stdin) != NULL) {
		n = 0;
		while (str[n] != '\n') n++;

		st = -1, en = -1;
		cnt = 0;
		for (int i = 0; i <= n; i++) {
			//printf("%c [(%d)-(%d)] %d\n", str[i], st, en, cnt);
			if (st != -1) {
				if ((!i || white(str[i-1])) && upp(str[i])) {
					continue;
				} else if (i && ischar(str[i-1]) && low(str[i])) {
					continue;
				} else if (i && low(str[i-1]) && white(str[i])) {
					cnt++;
					en = i;
					if (str[i] != ' ') {
						flusha(i);
						st = en = -1;
					}
				} else {
					flusha(i);
					st = en = -1;
					cnt = 0;
				}
			} else {
				if ((!i || white(str[i-1])) && upp(str[i])) {
					st = en = i;
					cnt = 0;
				} else {
					putchar(str[i]);
				}
			}
		}
		if (st != -1)
			flusha(n);
	}
}
