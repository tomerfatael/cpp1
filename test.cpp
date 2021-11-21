#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;


void dfs(int cur, vector<vector<int>>& g, vector<int>& visited, ll& span){
    visited[cur] = 1;
    for(int s: g[cur]){
        if(visited[s]) continue;
        span++;
        dfs(s, g, visited, span);
    }
}

int main() {
    //E number of employees, P number of rules
    int A,B,E,P,x,y;
    cin>>A>>B>>E>>P;
    vector<vector<int>> g(E);
    vector<vector<int>> gT(E);
    for(int i = 0; i < P; i++) {
        cin>>x>>y;
        g[x].push_back(y);
        gT[y].push_back(x);
    }

    ll ifA, ifB, definitelyNot, span;
    ifA = ifB = definitelyNot = span = 0;
    for(int i = 0; i < E; i++) {
        vector<int> visited(E, 0);
        span = 0;
        dfs(i, g, visited, span);
        if(E - span <= A) {ifA++;}
        if(E - span <= B) {ifB++;}
        for(int j = 0; j < E; j++) visited[j] = 0;
        span = 0;
        dfs(i, gT, visited,span);
        if(span >= B) {definitelyNot++;}
    }
    cout<<ifA<<endl<<ifB<<endl<<definitelyNot;
}


