#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
typedef unsigned long long ull;

ull minimax(vector<vector<int>>& g, vector<int>& a, int bandit) {

}

int main() {
    int n, pi,ai;
    cin>>n;
    vector<vector<int>> g(n+1);
    vector<int> a(n+1);
    for(int i = 2; i <= n; i++) {
        cin>>pi;
        g[pi].push_back(i);
    }

    for(int i = 0; i < n; i++) {
        cin>>ai;
        a[i+1] = ai;
    }

    ull ans = minimax(g, a, 1);
    cout<<ans<<endl;

}
