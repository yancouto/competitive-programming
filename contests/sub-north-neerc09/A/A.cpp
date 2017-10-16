#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

char s[11234];

int main () {
#ifdef ONLINE_JUDGE
	freopen("auxiliary.in", "r", stdin);
	freopen("auxiliary.out", "w", stdout);
#endif
	scanf("%s", s);
	deque<char> d(s, s + strlen(s));
	deque<char> d2;
	for(int i = 0; i < d.size(); i++) {
		if(d[i] == ')') d2.push_back('(');
		d2.pb(d[i]);
		if(d[i] == '(') d2.push_back(')');
	}
	d = d2; d2.clear();
	for(int i = 0; i < d.size(); i++) {
		if(d[i] == '(' && i && d2.back() != '(' && d2.back() != '+') d2.push_back('+');
		if(d[i] == ')' && d2.back() != ')' && !isdigit(d2.back())) d2.push_back('1');
		if(isdigit(d[i]) && i && d2.back() != '(' && !isdigit(d2.back()) && d2.back() != '+') d2.push_back('+');
		if(d[i] == '+' && (!i || (!isdigit(d2.back()) && d2.back() != ')'))) d2.push_back('1');
		d2.push_back(d[i]);
	}
	if(d2.back() == '+') d2.push_back('1');
	string s2(d2.begin(), d2.end());
	printf("%s\n", s2.c_str());
}

