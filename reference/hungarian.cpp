const int N = ;
typedef int num;
const num inf = 100000000;
int n, MA[N], MB[N], PB[N], mn[N];
num c[N][N], d[N];

bool S[N], T[N];
int st[N], sn;
num y[N], z[N];

void reset_all() {
	// need to be changed for costs < 0
	for(int i = 0; i < N; i++)
		y[i] = z[i] = num(0);
	int i;
	for(i = 0; i < n; i++)
		MA[i] = MB[i] = -1;
}

bool increase(int b) {
	int a = PB[b];
	while(true) {
		int n_b = MA[a];
		MB[b] = a;
		MA[a] = b;
		if(n_b == -1) break;
		b = n_b;
		a = PB[b];
	}
	return true;
}

// O(n)
bool visit(int a) {
	S[a] = true;
	for(int b = 0; b < n; b++) {
		if(T[b]) continue;
		if(c[a][b] - y[a] - z[b] < d[b]) {
			d[b] = c[a][b] - y[a] - z[b];
			mn[b] = a;
		}
		if(c[a][b] == y[a] + z[b]) {
			T[b] = true;
			PB[b] = a;
			st[sn++] = b;
			if(MB[b] == -1)
				return increase(b);
		}
	}
	return false;
}

// O(n)
bool update_dual() {
	int mb = -1, b;
	for(b = 0; b < n; b++)
		if(!T[b] && (mb == -1 || d[b] < d[mb]))
			mb = b;
	num e = d[mb];
	for(b = 0; b < n; b++)
		if(T[b]) z[b] -= e;
		else d[b] -= e;
	for(int a = 0; a < n; a++)
		if(S[a]) y[a] += e;
	PB[mb] = mn[mb];
	if(MB[mb] == -1) return increase(mb);
	st[sn++] = mb;
	T[mb] = true;
	return false;
}

// O(n^2)
void find_path() {
	int i, a;
	for(a = 0; MA[a] != -1; a++);
	memset(S, 0, sizeof S);
	memset(T, 0, sizeof T);
	for(int i = 0; i < N; i++) d[i] = inf;
	sn = 0;
	if(visit(a)) return;
	while(true) {
		if(sn) { if(visit(MB[st[--sn]])) break; }
		else if(update_dual()) break;
	}
}

num min_match() {
	reset_all();
	for(int i = 0; i < n; i++)
		find_path();
	num all = 0;
	for(int a = 0; a < n; a++)
		all += c[a][MA[a]];
	return all;
}

int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &c[i][j]);
	printf("%d\n", min_match());
}
