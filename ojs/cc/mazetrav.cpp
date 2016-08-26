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
#define last aslkdhaksdih

int r, c;
inline int id(int i, int j) { return i * c + j; }

int di[4] = {0, -1, 0, 1};
int dj[4] = {-1, 0, 1, 0};
int o[256];
char g[2123456];


const int maxn = 2123456;
int T[maxn];

void update(int idx,int val){
	idx++;
	while(idx < maxn){
		T[idx] += val;
		idx += idx&-idx;
	}
}

int sum(int idx){
	idx++;
	int ret = 0;
	while(idx){
		ret += T[idx];
		idx -= idx&-idx;
	}
	return ret;
}

int last[maxn];

struct query {
	int l, r, idx;
	query(int l=0,int r=0,int idx=0): l(l), r(r), idx(idx) {} 
	bool operator<(query comp)const{
		return r < comp.r;
	}
};

int ans[maxn];

vector<int> dif (int n, vector<int> v, vector<pii> q){


	vector<query> Q;

	for(int i=0;i<q.size();i++)
		Q.pb(query(q[i].first,q[i].second,i));

	sort(Q.begin(), Q.end());

	int pos = 0;

	memset(last,-1,sizeof(last));

	for(int i=0;i<Q.size();i++){
		int l = Q[i].l;
		int r = Q[i].r;
		while(pos <= r){
			update(pos,1);
			if(last[v[pos]] != -1){
				update(last[v[pos]],-1);
			}
			last[v[pos]] = pos;
			pos++;
		}
		ans[Q[i].idx] = sum(pos) - sum(l-1);
	}

	vector<int> ret;
	for(int i=0;i<q.size();i++)
		ret.pb(ans[i]);
	return ret;

}



vector<int> v;
vector<int> v2;
vector<int> vi;
vector<pii> Q;
map<int, int> pos;
map<pii, int> pos2;

void go(int i, int j, int d) {
	v.pb(id(i, j));
	if(!pos.count(id(i, j))) pos[id(i, j)] = v.size() - 1;
	pos2[pii(id(i, j), d)] = v.size() - 1;

	if(i == 1 && j == 1 && d == 0) { return; }
	int nd = (d + 1) % 4;
	if(g[id(i + di[nd], j + dj[nd])] == '.') return go(i + di[nd], j + dj[nd], nd);
	if(g[id(i + di[d], j + dj[d])] == '.') return go(i + di[d], j + dj[d], d);
	go(i, j, (d + 3) % 4);
}

int main() {
	int i = 0, j, q; char C;
	for(char c : "LURD") o[c] = i++;
	scanf("%d %d %d", &r, &c, &q); r = 2*r + 1; c = 2*c + 1;
	for(i = 0; i < r; i++)
		for(j = 0; j < c; j++)
			scanf(" %c", &g[id(i, j)]);
	go(1, 1, 3);
	for(i = 0; i < v.size(); i++) v2.pb(v[i]);
	for(i = 0; i < v.size(); i++) v2.pb(v[i]);
	vi = v2;
	reverse(vi.begin(), vi.end());
	while(q--) {
		int i1, j1, i2, j2;
		scanf("%d %d %d %d %c", &i1, &j1, &i2, &j2, &C);
		i = 2 * i1 - 1; j = 2 * j1 - 1;
		int p = pos[id(i, j)];
		i2 = 2 * i2 - 1; j2 = 2 * j2 - 1;
		int d = o[C];
		int nd = (d + 1) % 4;
		if(g[id(i + di[d], j + dj[d])] == '.'){
			if(g[id(i + di[nd], j + dj[nd])] != '.') d = (d + 3) % 4;
		} else d = (d + 3) % 4;
		if(pos2.count(pii(id(i, j), d)))
			Q.pb(pii(pos2[pii(id(i, j), d)], pos[id(i2, j2)]));
		else {
			assert(pos2.count(pii(id(i, j), (d + 2) % 4)));
			d = (d + 2) % 4;
			//Qi.pb(pii(pos2[pii(id(i, j), d)], pos[id(i2, j2)]));
			Q.pb(pii(1, 1));
		}
	}
	vector<int> ans = dif(v2.size(), v2, Q);
	for(int x : ans) printf("%d\n", x);
}
