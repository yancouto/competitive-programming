   
#include <bits/stdc++.h>
using namespace std;

int mex(vector<int>& v) {
    int n = v.size();
    for(int i = 0; i < n; i++)
        if(v[i] < n)
            swap(v[i], v[v[i]]);
    for(int i = 0; i < n; i++)
        if(v[i] != i)
            return i;
    return n;
}
int main() {
    int N;
    cin >> N;
    
    vector<int> v;
    for (int i = 0; i < N; ++i) {
        int val;
        cin >> val;
        v.push_back(val);
    }
    
    cout << mex(v) << "\n";
    return 0;
}
