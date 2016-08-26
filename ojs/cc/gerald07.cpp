// código bem feio mesmo, deve ter um jeito melhor
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 200009;
int n, m, q;
#define u first
#define v second
pair<int, int> es[MAX];
#define l first
#define r second
pair<int, int> qs[MAX];
int qi[MAX];
int sq_m;
inline int bl(int i) { return i / sq_m; }
inline int mx_bl(int b) { return sq_m * (b + 1) - 1; }
bool cmp_r(int i, int j) { return qs[i].r < qs[j].r; }
bool cmp_block(int i, int j) { return bl(qs[i].l) < bl(qs[j].l); }

int *S, *Sdef;
int *size, *sizedef;
int SS[3][MAX];
int Ssize[3][MAX];
int seen[MAX];
int tempo;
inline void unlaze(int i) { if(seen[i] < tempo) { seen[i] = tempo; S[i] = Sdef[i]; size[i] = sizedef[i]; } }
int get(int i) {
	if(Sdef) { unlaze(i); unlaze(S[i]); }
	if(S[S[i]] != S[i]) S[i] = get(S[i]);
	return S[i];
}
void join(int a, int b) {
	if(a == b) return;
	if(size[a] < size[b]) swap(a, b);
	size[a] += size[b];
	S[b] = a;
}


int add(int i) {

	int a = get(es[i].u), b = get(es[i].v);
	if(a != b)
		join(a, b);
	// printf("adding e%d (%d)\n", i, a != b);
	return a != b;
}


int main() {
	int t, i, j, k;
	scanf("%d", &t); tempo = 0;
	for(i = 0; i < MAX; i++) {
		SS[0][i] = i;	
		Ssize[0][i] = 1;
	}
	while(t--) {
		// puts("-----------");
		scanf("%d %d %d", &n, &m, &q);
		for(i = 0; i < m; i++) {
			scanf("%d %d", &es[i].u, &es[i].v);
			es[i].u--; es[i].v--;
		}
		for(i = 0; i < q; i++) {
			scanf("%d %d", &qs[i].l, &qs[i].r);
			qs[i].l--; qs[i].r--; qi[i] = i;
		}
		for(sq_m = 1; sq_m * sq_m <= m; sq_m++); sq_m--;
		sort(qi, qi + q, cmp_r);
		stable_sort(qi, qi + q, cmp_block);
		for(i = j = 0; j < q; i++) {
			S = SS[2]; size = Ssize[2];
			Sdef = SS[0]; sizedef = Ssize[0];
			for(; j < q && bl(qs[qi[j]].r) == i; j++) {
				// printf("raça (%d, %d)\n", qs[qi[j]].l + 1, qs[qi[j]].r + 1);
				int sum = n; tempo++;
				for(k = qs[qi[j]].l; k <= qs[qi[j]].r; k++)
					sum -= add(k);
				qs[qi[j]].l = sum;
				// printf("res %d\n", sum);
			}
			for(k = 0; k < n; k++) { SS[1][k] = k; Ssize[1][k] = 1; }
			int r = mx_bl(i);// printf("\nstarting r at %d\n", r);
			int resp = n;// printf("j %d is (%d, %d) -- bl(%d) -- %d\n", j, qs[qi[j]].l + 1, qs[qi[j]].r + 1, i, bl(qs[qi[j]].l));
			for(; j < q && bl(qs[qi[j]].l) == i; j++) {
				Sdef = NULL; S = SS[1]; size = Ssize[1];
				// printf("adjustin r for (%d, %d)\n", qs[qi[j]].l + 1, qs[qi[j]].r + 1);
				while(r < qs[qi[j]].r) resp -= add(++r);
				// printf("new_resp = %d\n", resp);
				Sdef = SS[1]; sizedef = Ssize[1];
				S = SS[2]; size = Ssize[2];
				tempo++;
				int r2 = 0;
				for(int l = mx_bl(i); l >= qs[qi[j]].l; l--) r2 += add(l);
				// printf("adjusting l\nr2 = %d\nfinal -> %d\n\n", r2, resp - r2);
				qs[qi[j]].l = resp - r2;
			}
		}
		for(i = 0; i < q; i++)
			printf("%d\n", qs[i].l);
	}
	return 0;
}