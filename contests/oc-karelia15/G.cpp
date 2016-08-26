#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

string ms(string a, string b) {
	if(a.size() < b.size()) return a;
	if(b.size() < a.size()) return b;
	return min(a, b);
}
char st[3009]; int sn;

void add(char c) { st[sn++] = c; }

void pop() {
	if(st[sn - 1] == '(') add('$');
	int ct = 0;
	while(true) {
		char c = st[--sn];
		if(c == ')') ct++;
		if(c == '(') ct--;
		if(ct == 0) break;
	}
}

int o[3009];
string evalor(int, int);

string evalexpr(int l, int r) {
	if(l == r) {
		if(st[l] == '$') return "";
		string e; e += st[l];
		return e;
	}
	assert(st[l] == '(' && st[r] == ')');
	return evalor(l + 1, r - 1);
}

string evalconc(int l, int r) {
	string ans;
	int ol = l;
	while(l <= r) {
		ans += evalexpr(l, o[l]);
		l = o[l] + 1;
	}
	return ans;
}

string evalor(int l, int r) {
	int ol = l;
	while(l <= r) {
		if(st[l] == '|') return ms(evalconc(ol, l - 1), evalor(l + 1, r));
		l = o[l] + 1;
	}
	return evalconc(ol, r);
}

char s[3009];
int main() {
	int i;
	for_tests(t, tt) {
		for(i = 0; i < 303; i++) s[i] = i;
		s[303] = 0;
		string ans = s;
		sn = 0;
		scanf("%s", s);
		add('$');
		for(i = 0; s[i]; i++) {
			if(s[i] == '*') { pop(); add('$'); continue; }
			add(s[i]);
		}
		vector<int> v;
		st[sn] = 0;
		for(i = 0; st[i]; i++) {
			if(st[i] == '(') v.pb(i);
			else if(st[i] == ')') o[i] = v.back(), o[v.back()] = i, v.pop_back();
			else o[i] = i;
		}
		string x = evalor(0, sn - 1);
		if(x.empty()) puts("$");
		else printf("%s\n", x.c_str());
	}
}
