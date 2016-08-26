// AC - Nao meu codigo de SA
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
const int MAXN = 100009;

int n,t;  //n es el tamano de la cadena
int p[MAXN],r[MAXN],h[MAXN];  
//p es el inverso del suffix array, no usa indices del suffix array ordenado,
//p[i] eh a ordem do sufixo que comeca na posicao i
//h el el tamano del lcp entre el i-esimo y el i+1-esimo elemento de
//suffix array ordenado
//r eh o vetor inverso
char s[MAXN];  

void fix_index(int *b, int *e) {  
    int pkm1, pk, np, i, d, m;  
    pkm1 = p[*b + t];  
    m = e - b; d = 0;  
    np = b - r;  
    for(i = 0; i < m; i++) {  
        if (((pk = p[*b+t]) != pkm1) && !(np <= pkm1 && pk < np+m)) {  
            pkm1 = pk;  
            d = i;  
        }  
        p[*(b++)] = np + d;  
    }  
}  
bool comp(int i, int j) {  
    return p[i + t] < p[j + t];  
}  
void suff_arr() {  
    int i, j, bc[256];  
    t = 1;  
    for(i = 0; i < 256; i++) bc[i] = 0;  //alfabeto

    for(i = 0; i < n; i++) ++bc[int(s[i])]; //counting sort inicial del alfabeto  

    for(i = 1; i < 256; i++) bc[i] += bc[i - 1];  
    for(i = 0; i < n; i++) r[--bc[int(s[i])]] = i;  
    for(i = n - 1; i >= 0; i--) p[i] = bc[int(s[i])];  
    for(t = 1; t < n; t *= 2) {  
        for(i = 0, j = 1; i < n; i = j++) {  
            while(j < n && p[r[j]] == p[r[i]]) ++j;  
            if (j - i > 1) {  
                sort(r + i, r + j, comp);  
                fix_index(r + i, r + j);  
            }  
        }  
    }  
}  
void lcp() {  
    int tam = 0, i, j;  
    for(i = 0; i < n; i++) if (p[i] > 0) {  
        j = r[p[i] - 1];  
        while(s[i + tam] == s[j + tam]) ++tam;  
        h[p[i] - 1] = tam;  
        if (tam > 0) --tam;  
    }  
    h[n - 1] = 0;
}  

int main() {
	int i, j;
	while(true) {
		scanf("%s", s); n = strlen(s);
		s[n++] = '$';
		if(s[0] == '*') return 0;
		suff_arr();
		lcp();
		int tot = h[0], last = h[0];
		for(i = 1; i < n - 1; i++)
			if(h[i] > h[i-1])
				tot += h[i] - h[i-1];
		printf("%d\n", tot);
	}
}
