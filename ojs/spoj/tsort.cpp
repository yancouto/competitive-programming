#include <bits/stdc++.h>
using namespace std;

const int N = 1123456;
int L[N], R[N], p[N], val[N], en = 1;

void rotate(int x) {
	int y = p[x];
	p[x] = p[y];
	if(L[p[x]] == y) L[p[x]] = x;
	else if(R[p[x]] == y) R[p[x]] = x;
	p[y] = x;
	if(x == L[y]) {
		L[y] = R[x]; p[L[y]] = y;
		R[x] = y;
	} else {
		R[y] = L[x]; p[R[y]] = y;
		L[x] = y;
	}
}

// roots at the lower bound (first >=) x
int splay(int root, int x) {
	int v = root;
	int lb = 0;
	while(true) {
		int nx = 0;
		if(val[v] == x) lb = v;
		else if(x > val[v]) nx = R[v];
		else nx = L[v], lb = v;
		if(nx == 0) break;
		v = nx;
	}
	v = lb;
	while(v && p[v]) {
		if(!p[p[v]]) rotate(v);
		else if((v == L[p[v]]) != (p[v] == L[p[p[v]]]))
			rotate(v), rotate(v);
		else
			rotate(p[v]), rotate(v);
	}
	return v;
}

int add(int root, int x) {
	val[en] = x;
	if(!root) return en++;
	int nr = splay(root, x);
	if(nr) {
		R[en] = nr;
		swap(L[nr], L[en]);
	} else L[en] = root;
	p[L[en]] = p[R[en]] = en;
	return en++;
}

void go(int x) {
	if(!x) return;
	go(L[x]);
	printf("%d\n", val[x]);
	go(R[x]);
}

int main() {
	int i, n, x;
	scanf("%d", &n);
	int root = 0;
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		root = add(root, x);
	}
	go(root);
}
