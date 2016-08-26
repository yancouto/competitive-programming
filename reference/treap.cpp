const int N = ;

int en = 1, root = 0;
int Y[N], X[N], sz[N], L[N], R[N];

int mx(int u) { while(R[u]) u = R[u]; return u; }

// atualize os valores associados aos nos que podem ser calculados a partir dos filhos
void calc(int u) {
	sz[u] = sz[L[u]] + 1 + sz[R[u]];
}

// divida a treap entre (valores <= x, valores > x)
void split_val(int u, int x, int &l, int &r) {
	if(!u) return (void) (l = r = 0);
	if(X[u] <= x) split_val(R[u], x, l, r), R[u] = l, l = u;
	else split_val(L[u], x, l, r), L[u] = r, r = u;
	calc(u);
}

// divida a treap entre (primeiros s elementos, resto)
void split_sz(int u, int s, int &l, int &r) {
	if(!u) return (void) (l = r = 0);
	if(sz[L[u]] < s) split_sz(R[u], s - sz[L[u]] - 1, l, r), R[u] = l, l = u;
	else split_sz(L[u], s, l, r), L[u] = r, r = u;
	calc(u);
}

// junte duas treaps, sendo que elementos l <= elementos r
int merge(int l, int r) {
	if(!l || !r) return l + r;
	int u;
	if(Y[l] > Y[r]) R[l] = merge(R[l], r), u = l;
	else L[r] = merge(l, L[r]), u = r;
	calc(u);
	return u;
}

// chame isso 1 vez no inicio. Para implicita e so nao usar o X
void init() {
	for(int i = 1; i < N; i++) Y[i] = i, sz[i] = 1;
	random_shuffle(Y, Y + N);
}
