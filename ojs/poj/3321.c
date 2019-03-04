#include <stdio.h>
#define true 1
#define false 0

int n;
struct Node {
	struct Node *next;
	int v;
} bak[200004];
struct Node *adj[100002];
char apple[100002];
int vec[100002];
int num[100002];

int time;
void dfs(int u, int from) {
	int v; struct Node *it;
	num[u] = 1;
	apple[u] = true;
	for(it = adj[u]; it; it = it->next) {
		v = it->v;
		if(!num[v])
			dfs(v, u);
		if(v != from) num[u] += num[v];
	}
	vec[u] = ++time;
}

int bit[100003];
int get(int i) {
	int sum = 0;
	while(i > 0) {
		sum += bit[i];
		i -= (i & -i);
	}
	return sum;
}

void update(int i, int v) {
	while(i <= n) {
		bit[i] += v;
		i += (i & -i);
	}
}

int main() {
	int i;
	int u, v;
	scanf("%d", &n);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &u, &v); u--; v--;
		struct Node *no1 = &bak[i * 2];
		struct Node *no2 = &bak[i * 2 + 1];
		no1->v = v; no2->v = u;
		no1->next = adj[u];
		no2->next = adj[v];
		adj[u] = no1;
		adj[v] = no2;
	}
	dfs(0, -1);
	for(i = 1; i <= n; i++) bit[i] = (i & -i);
	int m; char op;
	scanf("%d", &m);
	for(i = 0; i < m; i++) {
		scanf(" %c %d", &op, &u); u--;
		if(op == 'Q' && num[u] == 1) printf("%d\n", apple[u]);
		else if(op == 'Q') printf("%d\n", get(vec[u]) - get(vec[u] - num[u]));
		else {
			if(apple[u]) update(vec[u], -1);
			else update(vec[u], 1);
			apple[u] = !apple[u];
		}
	}
	return 0;
}
