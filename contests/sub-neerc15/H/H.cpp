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
#	define debug(args...) fprintf(stderr, args)
#endif

int sign(ll x) { return (x > 0) - (x < 0); }

struct pt {
	ll x, y, z;
};

pt operator - (pt a, pt b) { return pt{a.x - b.x, a.y - b.y, a.z - b.z}; }
ll operator ^ (pt a, pt b) { return a.x * b.y - a.y * b.x; }
bool operator == (pt a, pt b) { return a.x == b.x && a.y == b.y && a.z == b.z; }


bool inside(pt A, pt t[3]) {
	int s1 = sign((t[1] - t[0]) ^ (A - t[0]));
	int s2 = sign((t[2] - t[1]) ^ (A - t[1]));
	int s3 = sign((t[0] - t[2]) ^ (A - t[2]));
	if(s1 * s2 >= 0 && s1 * s3 >= 0 && s2 * s3 >= 0) return true;
	return false;
}

const int N = 11234;
pt t[N][3];
int d[N], seen[N], p[N];

int n;

pt T(int i) {
	return t[i / 3][i % 3];
}
vector<int> adj[N];

int main() {
	freopen("hiking.in", "r", stdin);
	freopen("hiking.out", "w", stdout);
	int i, j, ai = -100, bi = -100;
	pt A, B;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < 3; j++)
			scanf("%lld %lld %lld", &t[i][j].x, &t[i][j].y, &t[i][j].z);
	scanf("%lld %lld %lld", &A.x, &A.y, &A.z);
	scanf("%lld %lld %lld", &B.x, &B.y, &B.z);
	for(i = 0; i < n; i++)
		if(inside(A, t[i]))
			ai = i;
	for(i = 0; i < n; i++)
		if(inside(B, t[i]))
			bi = i;
	//if(ai == bi) {
	//	printf("2\n%lld %lld %lld\n%lld %lld %lld\n", A.x, A.y, A.z, B.x, B.y, B.z);
	//	return 0;
	//}
	int aib = 0;
	for(j = 1; j < 3; j++)
		if(t[ai][j].z < t[ai][aib].z)
			aib = j;
	int bib = 0;
	for(j = 1; j < 3; j++)
		if(t[bi][j].z < t[bi][bib].z)
			bib = j;
	int s = 3 * ai + aib;
	int tt = 3 * bi + bib;
	priority_queue<pii> pq;
	pq.push(pii(-T(s).z, s));
	for(i = 0; i < 3 * n; i++) d[i] = INT_MAX;
	int k, z;
	for(i = 0; i < n; i++)
		for(j = 0; j < 3; j++) {
			for(k = 0; k < n; k++)
				for(z = 0; z < 3; z++)
					if(k != i && t[i][j] == t[k][z])
						adj[3 * i + j].pb(3 * k + z);
		}
	while(!pq.empty()) {
		pii x = pq.top(); pq.pop();
		if(seen[x.snd] == 1) continue;
		seen[x.snd] = 1;
		if(x.snd == tt) break;
		int id = x.snd / 3;
		for(int k : adj[x.snd]) {
			int id = k / 3; int j = k % 3;
			pii nx = pii(-max<ll>(-x.fst, t[id][j].z), 3 * id + j);
			if(-nx.fst < d[nx.snd]) {
				d[nx.snd] = -nx.fst;
				p[nx.snd] = x.snd;
				pq.push(nx);
			}
		}
		for(j = 0; j < 3; j++) {
			pii nx = pii(-max<ll>(-x.fst, t[id][j].z), 3 * id + j);
			if(-nx.fst < d[nx.snd]) {
				d[nx.snd] = -nx.fst;
				p[nx.snd] = x.snd;
				pq.push(nx);
			}
		}
	}
	p[s] = -1;
	deque<pt> D;
	do {
		D.push_front(T(tt));
		tt = p[tt];
	} while(tt != -1);
	D.push_front(A);
	D.push_back(B);
	printf("%d\n", (int) D.size());
	for(pt p : D) {
		printf("%lld %lld %lld\n", p.x, p.y, p.z);
	}
}
