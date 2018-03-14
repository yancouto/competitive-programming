#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

string operator * (string a, int b) {
	string t;
	while(b--)
		t += a;
	return t;
}

int main() {
	int n; cin >> n;
	string s;
	cin >> s;
	string t = s;
	reverse(t.begin(), t.end());
	if(t != s) puts("1");
	else {
		int i;
		for(i = 1; i < int(s.size()) && s[i] == s[0]; i++);
		char a = s[0];
		if(i == s.size()) puts("-1");
		else {
			char b = s[i];
			for(i = 0; i < n && s[i] == (i % 2? b : a); i++);
			if(s == string(n / 2, a) + string(1, b) + string(n / 2, a)) puts("-1");
			else if(i == n) puts("-1");
			else puts("2");
		}
	}
}
