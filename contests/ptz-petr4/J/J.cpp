#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6;
const int T = 4;
const string words[] = {
	"can",
	"may",
	"must",
	"should",
	"is",
	"are",
	"a",
	"the"
};

char str[N];
int n;
vector<string> res;

bool match(int i, int j) {
	if (i + (int)words[j].size() > n) return 0;
	for (int k = 0; k < (int)words[j].size(); k++)
		if (words[j][k] != tolower(str[i+k]))
			return 0;

	if (i > 0 && str[i-1] != ' ')
		return 0;
	if (i + words[j].size() < n && str[i+words[j].size()] != ' ' && str[i+words[j].size()] != '.')
		return 0;
	return 1;
}

void try_match (int i, int j) {
	if (!match(i,j)) return;

	string nw;
	for (int k = 0; k < i +(int) words[j].size(); k++)
		nw.pb(str[k]);
	nw.pb(' ');
	nw.pb('n');
	nw.pb('o');
	int sh = 0;
	if (j < T)
		nw.pb('t');
	else if (match(i+words[j].size()+1,6))
		sh += 2;
	else if (match(i+words[j].size()+1,7))
		sh += 4;
	for (int k = i + words[j].size() + sh; k < n; k++)
		nw.pb(str[k]);
	res.pb(nw);
}

void go () {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 6; j++)
			try_match(i,j);
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("xyzx2009.in", "r", stdin);
	freopen("xyzx2009.out", "w", stdout);
#endif
	while ((str[n++] = getchar())) {
		if (str[n-1] == EOF) break;
		if (str[n-1] == '.') {
			char c = getchar();
			go();
			n = 0;
		}
	}

	printf("%d\n", int(res.size()));
	for (string s : res)
		printf("%s\n", s.c_str());
	
}
