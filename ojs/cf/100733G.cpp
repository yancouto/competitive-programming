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

inline char sw(char c) { return islower(c)? toupper(c) : tolower(c); }
inline char ot(char c) { return c == '+'? '*' : '+'; }
char str[300];
int mtch[300];
set<int> opn;
int pre() {
	int st[300], sn = 0;
	for(int i = 0; str[i]; i++) {
		if(str[i] == '(' || str[i] == '[') {
			st[sn++] = i;
			if(str[i] == '[') opn.insert(i);
		} else if(str[i] == ')' || str[i] == ']') {
			mtch[st[sn-1]] = i;
			mtch[i] = st[--sn];
		}
	}
}
int main() {
	int i;
	scanf("%s", str);
	pre();
	while(!opn.empty()) {
		int x = *opn.begin(); opn.erase(opn.begin());
		for(i = x + 1; i < mtch[x]; i++) {
			if(isalpha(str[i])) str[i] = sw(str[i]);
			else if(str[i] == '+' || str[i] == '*') str[i] = ot(str[i]);
			else {
				if(str[i] == '(') {
					opn.insert(i);
					str[i] = '[';
					str[mtch[i]] = ']';
				} else {
					opn.erase(i);
					str[i] = '(';
					str[mtch[i]] = ')';
				}
				i = mtch[i];
			}
		}
		str[x] = '('; str[mtch[x]] = ')';
	}
	puts(str);
	return 0;
}
