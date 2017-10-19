   
#include <bits/stdc++.h>
using namespace std;


int findDuplicate(const vector<int>& v) {
    int n = v.size() - 1;
    int p = n + 1;
    for(int i = 0; i < n + 1; i++)
        p = v[p - 1];
    int op = p, sz = 0;
    do {
        sz++;
        p = v[p - 1];
    } while(p != op);
    p = op = n + 1;
    while(sz--) p = v[p - 1];
    while(p != op) {
        p = v[p - 1];
        op = v[op - 1];
    }
    return p;
}

int main() {
    int N;
    cin >> N;
    
    vector<int> v;
    for (int i = 0; i <= N; ++i) {
        int val;
        cin >> val;
        v.push_back(val);
    }
    
    cout << findDuplicate(v) << "\n";
    return 0;
}
