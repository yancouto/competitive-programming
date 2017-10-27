#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define fst first
#define snd second

const int NS = 2;
const int N = 212345 * 2;

int cn, cd, ns, en = 1, lst;
string S[NS]; int si = -1;
/* sufn[si][i] no do sufixo S[si][i...] */
vector<int> sufn[N];

struct node {
	int l, r, si;
	int p, suf;
	map<char, int> adj;
	node() : l(0), r(-1), suf(0), p(0) {}
	node(int L, int R, int S, int P) : l(L), r(R), si(S), p(P) {}
	inline int len() { return r - l + 1; }
	inline int operator[](int i) { return S[si][l + i]; }
	inline int& operator()(char c) { return adj[c]; }
} t[N];

inline int new_node(int L, int R, int S, int P) {
	t[en] = node(L, R, S, P);
	return en++;
}

void add_string(string s) {
	S[++si] = s;
	sufn[si].resize(s.size() + 1);
	cn = cd = 0;
	int i = 0; const int n = s.size();
	for(int j = 0; j < n; j++)
		for(; i <= j; i++) {
			if(cd == t[cn].len() && t[cn](s[j]))
				cn = t[cn](s[j]), cd = 0;
			if(cd < t[cn].len() && t[cn][cd] == s[j]) {
				cd++;
				if(j < s.size() - 1) break;
				else {
					if(i) t[lst].suf = cn;
					for(; i <= j; i++) {
						sufn[si][i] = cn;
						cn = t[cn].suf;
					}
				}
			} else if(cd == t[cn].len()) {
				sufn[si][i] = en;
				if(i) t[lst].suf = en; lst = en;
				t[cn](s[j]) = new_node(j, n - 1, si, cn);
				cn = t[cn].suf;
				cd = t[cn].len();
			} else {
				int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].si, t[cn].p);
				t[t[cn].p](t[cn][0]) = mid;
				if(ns) t[ns].suf = mid;
				if(i) t[lst].suf = en; lst = en;
				sufn[si][i] = en;
				t[mid](s[j]) = new_node(j, n - 1, si, mid);
				t[mid](t[cn][cd]) = cn;
				t[cn].p = mid; t[cn].l += cd;
				cn = t[mid].p;
				int g = cn? j - cd : i + 1;
				cn = t[cn].suf;
				while(g < j && g + t[t[cn](S[si][g])].len() <= j)
					cn = t[cn](S[si][g]), g += t[cn].len();
				if(g == j)
					ns = 0, t[mid].suf = cn, cd = t[cn].len();
				else
					ns = mid, cn = t[cn](S[si][g]), cd = j - g;
			}
		}
}
int mx[N], mn[N];
int h[N];
int lc[N][19];

void dfs(int u, int h, int p) {
	h -= t[u].adj.empty();
	::h[u] = h;
	lc[u][0] = p;
	for(int i = 1; i < 19; i++)
		lc[u][i] = lc[lc[u][i - 1]][i - 1];
	for(auto e : t[u].adj) {
		dfs(e.snd, h + t[e.snd].len(), u);
		mx[u] = max(mx[e.snd], mx[u]);
		mn[u] = min(mn[e.snd], mn[u]);
	}
}

int M[N];
int n;

int ANSL;
int get(int l, int r) {
	l = n - l - 1;
	int u = sufn[1][l];
	if(mx[u] < r) {
		for(int i = 18; i >= 0; i--)
			if(mx[lc[u][i]] < r)
				u = lc[u][i];
		u = lc[u][0];
	}
	ANSL = mx[u];
	return h[u];
}

int ANSR;
int get2(int l, int r) {
	int u = sufn[0][r];
	if(mn[u] > l) {
		for(int i = 18; i >= 0; i--)
			if(mn[lc[u][i]] > l)
				u = lc[u][i];
		u = lc[u][0];
	}
	ANSR = mn[u];
	return h[u];
}

int main () {
	int i;
	string s;
	cin >> s;
	n = s.size();
	string os = s;
	s += '$';
	add_string(s);
	s.pop_back();
	reverse(s.begin(), s.end());
	s += '!';
	add_string(s);
	for(i = 0; i < en; i++) mx[i] = 0;
	for(i = 0; i < en; i++) mn[i] = N;
	for(i = 0; i < n; i++)
		mx[sufn[0][i]] = i;
	for(i = 0; i < n; i++)
		mn[sufn[1][n - i - 1]] = i;
	dfs(0, 0, 0);
	string ss;
	for(i = 0; i < os.size(); i++) {
		ss.pb(os[i]);
		if(i < os.size() - 1) ss.pb('$');
	}
	int m =-1;
	for(i = 0; i < ss.size(); i++) {
		if(m == -1 || i > m + M[m]) {
			m = i;
			for(; i - M[i] - 1 >= 0 && i + M[i] + 1 < ss.size() && ss[i + M[i] + 1] == ss[i - M[i] - 1]; M[i]++);
			continue;
		}
		M[i] = min(m + M[m] -i, M[m - (i - m)]);
		for(; i - M[i] - 1 >= 0 && i + M[i] + 1 < ss.size() && ss[i + M[i] + 1] == ss[i - M[i] - 1]; M[i]++);
		if(i + M[i] > m + M[m]) m = i;
	}
	//cout << ss << endl;
	//for(i = 0; i < ss.size(); i++)
	//	cout << ss[i] << ' ';
	//cout << endl;
	//for(i = 0; i < ss.size(); i++)
	//	cout << M[i] << ' ';
	//cout << endl;
	int best = 0;
	int br = -1, bl = -1;
	int szb = 0, szd = 0;
	for(i = 0; i < os.size(); i++) {
		int m = (M[2 * i]) / 2;
		if(2 * m + 1 > best) {
			best = 2 * m + 1;
			br = i + m;
			szb = 2 * m + 1;
			bl = -1;
			szd = 0;
		}
		if(i == m || i + m == os.size() - 1) continue;
		int ans = get(i - m - 1, i + m + 1);
		if(2 * ans + 2 * m + 1 > best) {
			best = 2 * ans + 2 * m + 1;
			szb = 2 * m + 1 + ans;
			szd = ans;
			br = i + m;
			bl = ANSL;
		}
		ans = get2(i - m - 1, i + m + 1);
		if(2 * ans + 2 * m + 1 > best) {
			best = 2 * ans + 2 * m + 1;
			szb = ans;
			br = ANSR;
			szd = 2 * m + 1 + ans;
			bl = i - m;
		}
	}
	for(i = 0; i < os.size() - 1; i++) {
		int m = (M[2 * i + 1] + 1) / 2;
		if(!m) continue;
		if(2 * m > best) {
			best = 2 * m;
			szb = 2* m;
			br = i + m;
			szd = 0;
			bl = -1;
		}
		if(i - m < 0 || i + m == os.size() - 1) continue;
		int ans = get(i - m, i + m + 1);
		if(2 * ans + 2 * m > best) {
			best = 2 * ans + 2 * m;
			szb = 2 * m + ans;
			szd = ans;
			br = i + m;
			bl = ANSL;
		}
		ans = get2(i - m, i + m + 1);
		if(2 * ans + 2 * m > best) {
			best = 2 * ans + 2 * m;
			szb = ans;
			br = ANSR;
			szd = 2 * m + ans;
			bl = i - m + 1;
		}
	}
	printf("%d\n", best);
	if(szb) printf("%d %d\n", br - szb + 1 + 1, br + 1);
	else puts("-1 -1");
	if(szd) printf("%d %d\n", bl + 1, bl + szd - 1 + 1);
	else puts("-1 -1");
}
