#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

void Z (int n, const char * s, int * z) {
	int m = -1;
	for (int i = 1; i < n; i++) {
		z[i] = 0;
		if (m != -1 && m + z[m] >= i)
			z[i] = min(m + z[m] - i, z[i-m]);
		while (i + z[i] < n && s[i+z[i]] == s[z[i]]) z[i]++;
		if (m == -1 || i + z[i] > m + z[m])
			m = i;
	}
}

int z[112345];

string grande(string a, string b) {
	string c = b + a;
	Z(c.size(), c.c_str(), z);
	for(int i = b.size(); i < b.size() + a.size(); i++)
		if(i + z[i] == a.size() + b.size())
			return a + b.substr(z[i], 100000);
	return a + b;
}

string ming(string a, string b) {
	if(a.empty()) return b;
	if(b.empty()) return a;
	if(a.size() > b.size())
		return b;
	return a;
}

bool tile(string &a, int *z, int i) {
	for(int j = i + 1; j < a.size(); j += i + 1) {
		if(z[j] < min<int>(a.size() - j + 1, i + 1))
			return false;
	}
	return true;
}

bool rot(string &a, string &b, int i) {
	int sz = i + 1;
	//printf("sz %d\n", sz);
	string c = a.substr(0, i + 1) + "?" + b.substr(0, i + 1) + b.substr(0, i + 1);
	Z(c.size(), c.c_str(), z);
	//cout << c << endl;
	for(i = sz; i < c.size(); i++) {
		//printf("z[%d] = %d\n", i, z[i]);
		if(z[i] >= sz)
			return true;
	}
	return false;
}

int za[112345];
int zb[112345];

string peq(string a, string b) {
	Z(a.size(), a.c_str(), za);
	Z(b.size(), b.c_str(), zb);
	for(int i = 0; i < a.size() && i < b.size(); i++) {
		if(tile(a, za, i) && tile(b, zb, i)) {
			if(rot(a, b, i))
				return a.substr(0, i + 1);
			else return "";
		}
	}
	return "";
}

string med(string a, string b) {
	return "";
}

char a[112345], b[112345];
int main () {
	int t;
	scanf("%d", &t);
	bool first = true;
	while(t--) {
		if(first) first = false;
		else putchar('\n');
		scanf("%s %s", a, b);
		string x;
		x = ming(x, grande(a, b));
		x = ming(x, grande(b, a));
		x = ming(x, peq(a, b));
		//x = ming(x, med(a, b));
		printf("%d\n%s\n", int(x.size()), x.c_str());
	}
}
