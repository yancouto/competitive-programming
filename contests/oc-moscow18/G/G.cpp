#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

string mrk;
string pr;
int p[1123];

int main() {
	int i, j, n;
	memset(p, -1, sizeof p);
	cin >> n;
	for(i = 0; i < n; i++) mrk.pb('0'), pr.pb('0');
	for(i = 0; i < n; i++) {
		mrk[i] = '1';
		cout << "? " << mrk << endl; cout.flush();
		string ans;
		cin >> ans;
		for(j = 0; j < i; j++)
			if(ans[j] != pr[j])
				p[i] = j;
		pr = ans;
	}
	for(i = 0; i < n; i++) mrk[i] = '0', pr[i] = '0';
	for(i = n - 1;  i >= 0; i--) {
		mrk[i] = '1';
		cout << "? " << mrk << endl; cout.flush();
		string ans;
		cin >> ans;
		for(j = i + 1; j < n; j++)
			if(ans[j] != pr[j])
				p[i] = j;
		pr = ans;
	}
	for(i = 0; i < n; i++)
		if(p[i] == -1)
			p[i] = i;
	cout << "!";
	for(i = 0; i < n; i++)
		cout << ' ' << p[i] + 1;
	cout << endl;
	cout.flush();
}
