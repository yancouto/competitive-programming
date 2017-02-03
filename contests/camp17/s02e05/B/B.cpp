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
#	define debug(args...) {}
#else
//#	define debug(args...) fprintf(stderr, args)
#	define debug(args...) {}
#endif

vector<short> pos[6][40];
int fat[10];
void gen(int sz, int sum, int bm, int mn) {
	pos[sz][sum].pb(bm);
	if(sz == 5) return;
	for(int i = mn; i <= 9; i++)
		gen(sz + 1, sum + i, bm | (1 << i), i + 1);
}

char g[10][10][10];
int sum[2][30], sz[2][30], n[2], si[2][30], sj[2][30];

int on, om;
char sol[10][10];

void prn() {
	for(int i = 0; i < on; i++)
		for(int j = 0; j < om; j++)
			printf("%c%c", (sol[i][j]? sol[i][j] : '_'), (j == om - 1? '\n' : ' '));
}

inline void reorder_perm(vector<string> &v) {
	sort(v.begin(), v.end(), [](const string &aa, const string &bb) {
		string a(aa); string b(bb);
		sort(a.begin(), a.end(), greater<char>());
		sort(b.begin(), b.end(), greater<char>());
		return a > b;
	});
}

bool can_do(vector<int> run[2], vector<vector<string>> rp[2], pii mn, int id, string pos) {
	int i = si[mn.fst][id], j = sj[mn.fst][id];
	vector<pii> undo;
	for(int g = 0; g < sz[mn.fst][id]; g++) {
		sol[i][j] = pos[g];
		undo.pb(pii(i, j));
		i = i + !mn.fst;
		j = j + mn.fst;
	}
	for(int k = 0; k < 2; k++)
		for(int l = 0; l < run[k].size(); l++) {
			int id2 = run[k][l];
			bool add = true;
			int np = 0;
			for(string p : rp[k][l]) {
				i = si[k][id2]; j = sj[k][id2];
				bool any = false, bad = false;
				for(int g = 0; g < sz[k][id2]; g++) {
					if(sol[i][j] && sol[i][j] != p[g]) { bad = true; break; }
					if(!sol[i][j]) any = true;
					i = i + !k;
					j = j + k;
				}
				if(bad == true) continue;
				if(any == false) { add = false; break; }
				np++;
			}
			if(!add) { continue; }
			if(np == 0) goto popop;
		}
	for(pii p : undo)
		sol[p.fst][p.snd] = 0;
	return true;
	popop:
	for(pii p : undo)
		sol[p.fst][p.snd] = 0;
	return false;
}

void go(vector<int> run[2], vector<vector<string>> rp[2]) {
	debug("(%d, %d) here\n", run[0].size(), run[1].size());
	debug("(%d, %d) here\n", rp[0].size(), rp[1].size());
	if(run[0].empty() && run[1].empty()) {
		prn();
		exit(0);
	}

	pii mn(0, 0);
	for(int k = 0; k < 2; k++)
		for(int i = 0; i < run[k].size(); i++)
			if(rp[k][i].size() < rp[mn.fst][mn.snd].size() || (rp[k][i].size() == rp[mn.fst][mn.snd].size() && sz[k][i] > sz[mn.fst][run[mn.fst][mn.snd]]))
				mn = pii(k, i);
	
	int id = run[mn.fst][mn.snd];
	debug("will use (%c) at (%d,%d) [%d]\n", "vh"[mn.fst], si[mn.fst][id], sj[mn.fst][id], id);
	debug("rp[%d][%d].size() = %d\n", mn.fst, mn.snd, rp[mn.fst][mn.snd].size());
	for(string pos : rp[mn.fst][mn.snd]) {
		debug("[%d,%d] trying %s\n", mn.fst, id, pos.c_str());
		int i = si[mn.fst][id], j = sj[mn.fst][id];
		debug("starting at ((%d,%d))\n", i, j);
		vector<pii> undo;
		for(int g = 0; g < sz[mn.fst][id]; g++) {
			debug("putting (%c) at (%d,%d)\n", pos[g], i, j);
			if(sol[i][j]) {
				if(sol[i][j] != pos[g]) debug("(%d, %d) not ok\n", i, j);
				assert(sol[i][j] == pos[g]);
			} else {
				sol[i][j] = pos[g];
				undo.pb(pii(i, j));
			}
			i = i + !mn.fst;
			j = j + mn.fst;
		}
		vector<int> nrun[2];
		vector<vector<string>> nrp[2];
		for(int k = 0; k < 2; k++)
			for(int l = 0; l < run[k].size(); l++) {
				int id2 = run[k][l];
				if(pii(k, l) == mn) continue;
				if(k == mn.fst) { nrun[k].pb(run[k][l]); nrp[k].pb(rp[k][l]); continue; }
				nrp[k].push_back(vector<string> ());
				vector<string> &np = nrp[k].back();
				bool add = true;
				for(string p : rp[k][l]) {
					i = si[k][id2]; j = sj[k][id2];
					bool any = false, bad = false;
					for(int g = 0; g < sz[k][id2]; g++) {
						if(sol[i][j] && sol[i][j] != p[g]) { bad = true; break; }
						if(!sol[i][j]) any = true;
						i = i + !k;
						j = j + k;
					}
					if(bad == true) continue;
					if(any == false) { add = false; break; }
					np.pb(p);
				}
				if(!add) { nrp[k].pop_back(); continue; }
				if(np.size() == 0) goto notpos;
				nrun[k].pb(id2);
			}
		go(nrun, nrp);
		notpos:
		for(pii p : undo)
			sol[p.fst][p.snd] = 0;
	}
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, j;
	scanf("%d %d", &on, &om);
	for(i = 0; i < on; i++)
		for(j = 0; j < om; j++)
			scanf("%s", g[i][j]);
	for(i = 0; i < on; i++)
		for(j = 0; j < om; j++)
			if(isdigit(g[i][j][0])) {
				sum[0][n[0]] = 10 * (g[i][j][0] - '0') + (g[i][j][1] - '0');
				for(int ii = i + 1; g[ii][j][0] == '.'; ii++)
					sz[0][n[0]]++;
				si[0][n[0]] = i + 1;
				sj[0][n[0]] = j;
				n[0]++;
			}
	for(i = 0; i < on; i++)
		for(j = 0; j < om; j++)
			if(isdigit(g[i][j][3])) {
				sum[1][n[1]] = 10 * (g[i][j][3] - '0') + (g[i][j][4] - '0');
				for(int jj = j + 1; g[i][jj][0] == '.'; jj++)
					sz[1][n[1]]++;
				si[1][n[1]] = i;
				sj[1][n[1]] = j + 1;
				n[1]++;
			}
	fat[0] = 1;
	for(i = 1; i <= 5; i++) fat[i] = i * fat[i - 1];
	gen(0, 0, 0, 1);
	//for(i = 1; i <= 5; i++)
	//	for(j = (i * (i + 1)) / 2; j <= ((9 + 9 - i + 1) * i) / 2; j++)
	//		printf("%d chars summing %d is equal %d * %d\n", i, j, (int) pos[i][j].size(), fat[i]);
	
	vector<int> run[2];
	vector<vector<string>> rp[2];
	for(int k = 0; k < 2; k++)
		for(i = 0; i < n[k]; i++) {
			run[k].pb(i);
			vector<string> p;
			//debug("guy (%d, %d) has (%d, %d) %d\n", k, i, sz[k][i], sum[k][i], pos[sz[k][i]][sum[k][i]].size());
			for(short bm : pos[sz[k][i]][sum[k][i]]) {
				string perm;
				for(j = 1; j <= 9; j++)
					if((bm >> j) & 1)
						perm += char('0' + j);
				do {
					p.pb(perm);
				} while(next_permutation(perm.begin(), perm.end()));
			}
			reorder_perm(p);
			rp[k].pb(p);
			debug("rp[%d].back().size() = %d\n", k, rp[k].back().size());
		}
	for(int k = 0; k < 2; k++)
		for(i = 0; i < n[k]; i++) {
			assert(run[k][i] == i);
			vector<string> p2;
			for(string p : rp[k][i])
				if(can_do(run, rp, pii(k, i), run[k][i], p))
					p2.pb(p);
			rp[k][i] = p2;
		}
	go(run, rp);
}
