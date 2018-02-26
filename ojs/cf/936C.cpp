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

const int N = 2123;
int n;
string s, t;

int p[N];

void imp() {
	puts("-1");
	exit(0);
}

char tmp[N];

vector<int> ans;
void apply(int x) {
	//cout << "from " << s;
	ans.pb(x);
	string bet = s.substr(n - x, x);
	string alp = s.substr(0, n - x);
	reverse(bet.begin(), bet.end());
	s = bet + alp;
	//cout << " to " << s << endl;
}

int main() {
	int i, j;
	string t_;
	cin >> n >> s >> t_;
	for(i = 1; i < n; i++) {
		//for(j = 0; j < i; j++) printf("%d ", p[j]);
		//putchar('\n');
		reverse(p, p + i);
		p[i] = i;
	}
	//for(i = 0; i < n; i++) printf("%d ", p[i]);
	//putchar('\n');
	t.resize(n, '0');
	for(i = 0; i < n; i++)
		t[p[i]] = t_[i];
	//cout << "need " << t << endl;
	for(i = 0; i < n; i++) {
		//cout << "at " << i << " placing " << t[i] << endl;
		for(j = i; j < n && s[j] != t[i]; j++);
		if(j == n) imp();
		if(j == i) {
			apply(n - i);
			apply(i + 1);
		} else {
			int nA = i, nC = j - i - 1, nE = n - j - 1;
			apply(nE + 1);
			apply(nC + 1);
			apply(nA + 1);
		}
	}
	//cout << s << " -- " << t_ << endl;
	assert(s == t_);
	assert(ans.size() <= 6100);
	printf("%d\n", int(ans.size()));
	for(int x : ans)
		printf("%d ", x);
	putchar('\n');
}
