#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
char expr[300], dig[300];
int en;
struct pos {
	int i, p;
	int sign;
	pos() {}
	pos(int a, int b, int s) : i(a), p(b), sign(s) {}
	bool operator < (const pos &o) const {
		if(sign != o.sign) return sign > 0;
		if(p == o.p) return i > o.i;
		return (sign > 0)? p > o.p : p < o.p;
	}
};

int main() {
	int i, j, x, t;
	fgets(expr, sizeof expr, stdin);
	sscanf(expr, "%d", &t);
	for(int tt = 1; tt <= t; tt++) {
		fgets(expr + 1, sizeof expr, stdin); expr[0] = '+';
		fgets(dig, sizeof dig, stdin);
		en = strlen(expr); 
		i = 0;
		vector<pos> s;
		vector<int> sign; int cur = 1;
		vector<pii> st;
		//puts("here1");
		while(true) {
			//printf("here i %d\n", i);
			while(i < en && expr[i] != '#' && expr[i] != ')' && expr[i] != '(' && !isdigit(expr[i])) i++;
			if(i == en) break;
			//printf("here2 i %d\n", i);
			if(expr[i] == '#' || isdigit(expr[i])) {
				int cr = ((expr[i - 1] == '-')? -cur : cur);
				for(j = i + 1; expr[j] == '#' || isdigit(expr[j]); j++);
				st.pb(pii(i, cr));
				for(; i < j; i++)
					if(expr[i] == '#')
						s.pb(pos(i, j - i, cr));
			} else if(expr[i] == ')') {
				cur *= sign.back();
				sign.pop_back(); i++;
			} else {
				int a = ((expr[i - 1] == '-')? -1 : 1);
				sign.pb(a);
				cur *= a; i++;
			}
		}
		//puts("here");
		sort(s.begin(), s.end());
		sort(dig, dig + s.size()); reverse(dig, dig + s.size());
		for(i = 0; i < s.size(); i++)
			expr[s[i].i] = dig[i];
		printf("Case %d:\n%s", tt, expr + 1);
		int tot = 0;
		for(i = 0; i < st.size(); i++) {
			sscanf(expr + st[i].fst, "%d", &x);
			tot += st[i].snd * x;
		}
		printf("%d\n", tot);
	}
	return 0;
}
