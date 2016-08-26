const int N = ;
/* pode tirar o path se nao precisar */
int p[N], path[N][N], seen[N], t;
/* se seen[i] == t entao i esta do lado de s do s,t-corte */


void solve(int n) {
	for(int i = 0; i < n; i++) path[i][i] = 1e9, p[i] = 0;
	for(int i = 1; i < n; i++) {
		/* retorna fluxo maximo de i a p[i] e calcula corretamente seen */
		int v = flow(i, p[i]);
		for(j = i + 1; j < n; j++)
			if(seen[j] == t && p[j] == p[i])
				p[j] = i;
		for(j = 0; j < i; j++)
			path[i][j] = path[j][i] = min(path[j][p[i]], v);
	}
}
