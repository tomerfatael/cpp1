#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

void dfs(int cur, vector<vector<int>>& g, vector<int>& visited, )

int main() {
    int A,B,E,P,x,y;
    cin>>A>>B>>E>>P;
    vector<vector<int>> g(E);
    vector<vector<int>> gT(E);
    for(int i = 0; i < P; i++) {
        cin>>x>>y;
        g[x].push_back(y);
        gT[y].push_back(x);
    }



}


