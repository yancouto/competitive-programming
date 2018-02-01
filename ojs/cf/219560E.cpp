#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

enum {
	NCS,
	CS,
	SET,
	TEST
};

struct instr {
	int name;
	vector<int> args;
};
vector<instr> code[2];

struct node {
	int l[2];
	int vars;
	operator int () { return l[0] * 81 + l[1] * 9 + vars; }
	node exec(int i);
	void prn() { cout << l[0] << ' ' << l[1] << ' ' << vars << '\n'; }
};

node node::exec(int i) {
	instr in = code[i][l[i]];
	node nx = *this;
	if(in.name == NCS || in.name == CS)
		nx.l[i] = in.args[0] - 1;
	else if(in.name == TEST) {
		if((vars >> in.args[0]) & 1)
			nx.l[i] = in.args[2] - 1;
		else
			nx.l[i] = in.args[1] - 1;
	} else {
		nx.l[i] = in.args[2] - 1;
		nx.vars &= (7 ^ (1 << in.args[0]));
		nx.vars |= (in.args[1] << in.args[0]);
	}
	return nx;
}

int seen[1000];

bool find_path(node n) {
	if(code[0][n.l[0]].name == CS && code[1][n.l[1]].name == CS) {
		//n.prn();
		return true;
	}
	if(seen[n]) return false;
	seen[n] = true;
	if(find_path(n.exec(0)) || find_path(n.exec(1))) {
		//n.prn();
		return true;
	}
	return false;
}

int seen3[1000][3];

node fst;
bool find_cyc(node n, bool execl, bool execr, int from) {
	if(code[0][n.l[0]].name == CS || code[1][n.l[1]].name == CS) return false;
	if(seen[n] && int(n) == int(fst) && (execl || code[0][n.l[0]].name == NCS) && (execr || code[1][n.l[1]].name == NCS)) {
		//n.prn();
		return true;
	}
	if(seen3[n][from]) return false;
	seen[n] = 1;
	seen3[n][from] = 1;
	if(find_cyc(n.exec(0), true, execr, 0) || find_cyc(n.exec(1), execl, true, 1)) {
		//n.prn();
		return true;
	}
	return false;
}

int seen2[1000][3];

bool find_cyc_from(node n, int from) {
	if(seen2[n][from]) return false;
	seen2[n][from] = true;
	//printf(">>"); n.prn();
	memset(seen, 0, sizeof seen);
	memset(seen3, 0, sizeof seen3);
	fst = n;
	if(find_cyc(n, 0, 0, 2)) return true;
	if(find_cyc_from(n.exec(0), 0) || find_cyc_from(n.exec(1), 1)) return true;
	//printf("<<\n");
	return false;
}

int seen4[1000][2][2][3];

bool find_cyc2(node n, bool execl, bool execr, bool csl, bool csr, int from) {
	if(csl && csr) return false;
	if(int(n) == int(fst) && execl && execr) {
		//n.prn();
		return true;
	}
	if(seen4[n][csl][csr][from]) return false;
	seen4[n][csl][csr][from] = 1;
	if(find_cyc2(n.exec(0), true, execr, csl | (code[0][n.l[0]].name == CS), csr, 0) || find_cyc2(n.exec(1), execl, true, csl, csr | (code[1][n.l[1]].name == CS), 1)) {
		//n.prn();
		return true;
	}
	return false;
}

bool find_cyc_from2(node n, int from) {
	if(seen2[n][from]) return false;
	seen2[n][from] = true;
	//printf(">>"); n.prn();
	memset(seen, 0, sizeof seen);
	memset(seen4, 0, sizeof seen4);
	fst = n;
	if(find_cyc2(n, 0, 0, 0, 0, 2)) return true;
	if(find_cyc_from2(n.exec(0), 0) || find_cyc_from2(n.exec(1), 1)) return true;
	//printf("<<\n");
	return false;
}
int main() {
#ifdef ONLINE_JUDGE
	freopen("exclusive.in", "r", stdin);
	freopen("exclusive.out", "w", stdout);
#endif
	int m[2], i, j;
	cin >> m[0] >> m[1];
	for(j = 0; j < 2; j++) {
		for(i = 0; i < m[j]; i++) {
			instr in;
			int x; cin >> x;
			string name; cin >> name;
			int arg_count = 1;
			if(name == "NCS") in.name = NCS;
			else if(name == "CS") in.name = CS;
			else {
				char var; cin >> var;
				in.args.pb(var - 'A');
				arg_count = 2;
				if(name == "TEST") in.name = TEST;
				else in.name = SET;
			}
			while(arg_count--) {
				int x; cin >> x;
				in.args.pb(x);
			}
			code[j].pb(in);
		}
	}
	node root = node{0, 0, 0};
	if(find_path(root)) putchar('N');
	else putchar('Y');
	bool dd;
	if(dd = find_cyc_from(root, 2)) putchar('N');
	else putchar('Y');
	memset(seen2, 0, sizeof seen2);
	if(dd || find_cyc_from2(root, 2)) putchar('N');
	else putchar('Y');
	putchar('\n');
}
