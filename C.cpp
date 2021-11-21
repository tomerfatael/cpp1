#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

void topologicalSort(int cur, vector<int>& v, vector<int>& od, vector<vector<int>>& g, int& p) {
    if(v[cur]) return;
    v[cur] = 1;
    for(int s: g[cur]) {
        topologicalSort(s, v, od, g, p);
    }

    v[cur] = 2;
    od[p] = cur;
    p--;
}


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
    vector<int> v(E,0);
    vector<int> od(E);
    int idx = E - 1;
    for(int i = 0; i < E; i++) {
        if(!v[i]) topologicalSort(i, v, od, g, idx);
    }
    map<int, int> levels;
    int promotedIfA = 0;
    for(int s: od) {
        if(gT[s].empty()) {
            levels[s] = 0;
            promotedIfA += 1;
        }

        for(int u: gT[s]){
            if(levels.find(s) == levels.end()) {
                levels[s] = levels[u] + 1;
            }
            else if(levels[s] > levels[u] + 1){
                levels[s] = levels[u] + 1;
            }
        }
    }

    vector<int> levelsT(P,0);
    for(auto it = levels.begin(); it != levels.end(); it++) {
        levelsT[it->second]++;
    }

    int promotedIfB = promotedIfA + levelsT[1];
    int j = 2;
    while(j < P && promotedIfB < B) {
        promotedIfB += levelsT[j];
        j++;
    }

    int noPossibility;

    if(promotedIfA > A) {
        cout<<0<<endl;
    }
    else{
        cout<<promotedIfA<<endl;
    }
    
    if(promotedIfB > B) {
        if(promotedIfA > B) {
            cout<<0<<endl;
        }
        else{
            cout<<promotedIfA<<endl;
        }
    }

    else{
        cout<<promotedIfB<<endl;
    }
    cout<<E-B;
}



