#include <bits/stdc++.h>
using namespace std;

#define lower_bound lb
const int N = 212345;
int L[N], R[N], p[N], val[N], sz[N], en = 1;

void calc(int x) {
	sz[x] = 1 + sz[L[x]] + sz[R[x]];
}

int lst;
void rotate(int x) {
	int y = p[x];
	p[x] = p[y];
	if(y == R[p[y]]) R[p[y]] = x;
	else if(y == L[p[y]]) L[p[y]] = x;
	p[y] = x;
	if(L[y] == x) {
		L[y] = R[x]; p[L[y]] = y;
		R[x] = y;
	} else {
		R[y] = L[x]; p[R[y]] = y;
		L[x] = y;
	}
	calc(y); calc(x);
}

void splay(int x) {
	while(x && p[x]) {
		if(!p[p[x]]) rotate(x);
		else if((x == L[p[x]]) != (p[x] == L[p[p[x]]])) rotate(x), rotate(x);
		else rotate(p[x]), rotate(x);
	}
}

int lower_bound(int root, int x) {
	int v = 0;
	while(root) {
		lst = root;
		if(val[root] >= x) v = root, root = L[root];
		else root = R[root];
	}
	return v;
}

int kth(int v, int k) {
	assert(v);
	if(sz[L[v]] >= k) return kth(L[v], k);
	if(sz[L[v]] == k - 1) return v;
	return kth(R[v], k - sz[L[v]] - 1);
}

int count(int v, int k) {
	if(!v) return 0;
	lst = v;
	if(val[v] >= k) return count(L[v], k);
	return sz[L[v]] + 1 + count(R[v], k);
}

void go(int x) {
	if(!x) return;
	printf("%d (%d) -- L %d -- R %d\n", x, val[x], L[x], R[x]);
	go(L[x]);
	go(R[x]);
}

int main() {
	int root = 0, q, x; char op;
	scanf("%d", &q);
	while(q--) {
		scanf(" %c %d", &op, &x);
		if(op == 'I') {
			int v = lower_bound(root, x);
			if(v && val[v] == x) continue;
			val[en] = x;
			if(!v) {
				splay(root = lst);
				L[en] = root;
			} else {
				splay(root = v);
				swap(L[en], L[root]);
				R[en] = root;
				calc(root);
			}
			p[L[en]] = p[R[en]] = en; p[0] = 0;
			root = en++;
			calc(root);
		} else if(op == 'D') {
			int v = lower_bound(root, x);
			if(v) splay(root = v);
			else splay(root = lst);
			if(!v || val[v] != x) continue;
			if(!R[v]) {
				root = L[v];
				p[root] = 0;
				continue;
			}
			p[R[v]] = 0;
			splay(R[v] = lower_bound(R[v], INT_MIN));
			L[R[v]] = L[v];
			p[L[v]] = R[v];
			root = R[v];
			calc(root);
		} else if(op == 'K') {
			if(x > sz[root]) { puts("invalid"); continue; }
			int v = kth(root, x);
			printf("%d\n", val[v]);
			splay(root = v);
		} else {
			printf("%d\n", count(root, x));
			splay(root = lst);
		}
		//go(root); puts("-----");
	}
}
