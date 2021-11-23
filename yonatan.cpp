#include <iostream>
#include <vector>
#include <map>
#include <bits/stdc++.h>
using namespace std;


void dfs(int a, vector<int>& v, vector<vector<int>>& g, vector<int>& od, int& p, int& flag) {
    if(v[a]==1) flag = 1;
    if(v[a]) return;
    v[a] = 1;
    for(int i : g[a]){ dfs(i, v, g, od, p, flag);}
    v[a] = 2;
    od[p] = a; p--;
}

int main() {
    int B, N;
    cin >> B >> N;
    vector<vector<int>> g(10000);
    vector<pair<int,int>> updatedVec(10000);
    map<string, int> dishes;
    map<pair<int,int>,pair<int,int>> edges;
    vector<int> od(10000,-1);
    vector<int> v(10000,0);
    int flag, p;
    int dishesN=0;

    string derived_dish, base_dish, added_ingredient;
    int price, prestige, x, y;

    //getting input to a map
    for(int i=0; i< N;i++){
        cin >> derived_dish >> base_dish >> added_ingredient >> price >> prestige;
        pair<int,int> pp = {price,prestige};
        if(dishes.find(derived_dish) == dishes.end()){
            dishes.insert({derived_dish, dishesN});
            dishesN++;
        }
        if (dishes.find(base_dish) == dishes.end()){
            dishes[base_dish] = dishesN;
            dishesN ++;
        }

        //updating the map so that each dish will appear once with its lowes cost
        x = dishes.find(derived_dish)->second;
        y = dishes.find(base_dish)->second;
        g[x].push_back(y);

        if(edges.find({x,y})!= edges.end()){
            if(edges.find({x,y})->second.first < pp.first){
                pp.first = edges.find({x,y})->second.first;
                pp.second = edges.find({x,y})->second.second;
            }
            else if(edges.find({x,y})->second.first == pp.first){
                if(edges.find({x,y})->second.second > pp.second){
                    pp.first = edges.find({x,y})->second.first;
                    pp.second = edges.find({x,y})->second.second;
                }
            }
        }

        edges[{x,y}] = pp;
    }

    flag=0; p=dishesN-1;
    for(int i=0; i<dishesN; i++) if(!v[i])
            dfs(i,v,g,od,p, flag);

    vector<int> TO;
    for(int i=0; i<dishesN;i++){
        if(od[i] != -1){
            TO.push_back(od[i]);
        }
    }

    for(int i=TO.size() -1; i>=0;i--){
        long long minPrice = INT_MAX;
        long long maxPrestige = 0;
        int chosen_son=0;
        int current = TO[i];

        if(g[current].size() == 0){
            updatedVec[current] = {0,0};
            continue;
        }

        for(int son : g[current]){
            if(updatedVec[son].first + edges.find({current,son})->second.first < minPrice){
                minPrice = updatedVec[son].first + edges.find({current, son})->second.first;
                maxPrestige = updatedVec[son].second + edges.find({current, son})->second.second;

            }
            else if(updatedVec[son].first + edges.find({current,son})->second.first == minPrice){
                if(updatedVec[son].second + edges.find({current,son})->second.second > maxPrestige){
                    maxPrestige = updatedVec[son].second + edges.find({current, son})->second.second;
                }
            }
        }
        updatedVec[current] = {minPrice, maxPrestige};
    }

    vector<long long> prev(B+1);
    for(int i=0; i<=B; i++){
        if(updatedVec[0].first > i)
            prev[i] = 0;
        else
            prev[i] = updatedVec[0].second;
    }
    vector<long long> curr(B+1);
    for(int i=1; i<updatedVec.size(); i++){
        for(int j=0;j<=B; j++){
            if(j - updatedVec[i].first >= 0 && prev[j - updatedVec[i].first] +
                                                                   updatedVec[i].second > prev[j])
                curr[j] = prev[j - updatedVec[i].first] + updatedVec[i].second;
            else
                curr[j] = prev[j];
        }
        prev = curr;
    }
    cout << curr[B]<< endl;

    int prevNum=B;
    for(int i=B-1; i>=0;i--){
        if(curr[i] == curr[prevNum])
            prevNum = i;
        else{
            cout << prevNum<<endl;
            return 0;}
    }
    cout << prevNum;
}
