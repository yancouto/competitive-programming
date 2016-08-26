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

char gc() {
	char c;
	while(isspace(c = getchar()));
	return c;
}

char s[112345];
string read_until(char x) {
	int i;
	for(i = 0; (s[i] = getchar()) != x; i++);
	s[i] = '\0';
	return string(s);
}

struct obj {
	bool isleaf = false;
	string leaf;
	map<string, obj*> mp;
	obj() {}
	obj(string s) : leaf(s) {isleaf = true;}
};

obj* go() {
	obj *o = new obj;
	while(gc() == '"') {
		string s = read_until('"'); gc();
		if(gc() == '"') o->mp[s] = new obj(read_until('"'));
		else o->mp[s] = go();
		if(gc() == '}') break;
	}
	return o;
}

void dfs(obj *o, string s) {
	if(!o->leaf.empty()) { printf("%s = \"%s\"\n", s.c_str() + 1, o->leaf.c_str()); return; }
	for(auto e : o->mp)
		dfs(e.snd, s + "." + e.fst);
}

obj* find(obj *root, char *s) {
	int i;
	for(i = 0; s[i] && s[i] != '.'; i++);
	if(!s[i]) {
		while(isspace(s[--i]));
		if(root->mp.count(string(s, i+1))) {
			obj *a = root->mp[string(s, i+1)];
			if(!a->isleaf) return NULL;
			return a;
		}
		else return NULL;
	} else {
		if(root->mp.count(string(s, i))) return find(root->mp[string(s, i)], s + i + 1);
		else return NULL;
	}
}

const int N = 50000;

string m[100009];
int mx[N];
deque<string> st[N];
int n; obj *root;
void col(int c) {
	int i, j, k;
	int &mx = ::mx[c];
	for(k = 1; k < n; k += 2) {
		int fst = -1;
		for(i = c; m[0][i] != '+'; i++) {
			s[i - c] = m[k][i];
			if(fst == -1 && !isspace(m[k][i])) fst = i - c;
		}
		int sz = i - c;
		s[sz] = 0;
		if(fst == -1) { mx = max(mx, sz); st[k].pb(string(s)); continue; }
		if(strncmp(s + fst, "Value:", 6) != 0) { mx = max(mx, sz); st[k].pb(s); continue; }
		obj *o = find(root, s + fst + 6);
		if(o == NULL) { mx = max(mx, sz); st[k].pb(s); continue; }
		st[k].pb(o->leaf);
		mx = max(mx, int(o->leaf.size()));
	}
}

int main() {
	gc();
	root = go();
	ungetc(gc(), stdin);
	n = 0; int i, j;
	while(true) {
		fgets(s, sizeof s, stdin);
		if(feof(stdin)) break;
		m[n++] = s;
	}
	for(i = 0; i < m[0].size() - 2; i++)
		if(m[0][i] == '+')
			col(i + 1);
	for(i = 0; i < n; i++) {
		if(!(i & 1)) {
			for(j = 0; j < m[0].size() - 2; j++) {
				if(m[0][j] != '+') continue;
				putchar(m[i][j]);
				for(int k = 0; k < mx[j + 1]; k++) putchar('-');
			}
			puts("+");
			continue;
		}
		for(j = 0; j < m[0].size() - 2; j++) {
			if(m[0][j] != '+') continue;
			putchar(m[i][j]);
			printf("%s", st[i].front().c_str());
			for(int k = st[i].front().size(); k < mx[j + 1]; k++)
				putchar(' ');
			st[i].pop_front();
		}
		puts("|");
	}
	//dfs(root, "");
	//for(i = 0; i < n; i++)
	//	for(j = 0; j < m[i].size(); j++)
	//		printf("%c", m[i][j]);
}
