#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
using namespace std;
#define MAXN 10000

vector<vector<int>> g(MAXN);
vector<pair<int,int>> price_and_perstige_for_vertex(MAXN);
map<string, int> dishes;
map<pair<int,int>,pair<int,int>> weighted_edges;
vector<int> od(MAXN,-1);
int flag, v[MAXN];
int p; // the final order
int num_of_dishes=0;

//struct to hold each input row
struct Recipe {
    string name, baseDish, extra;
    long long price, prestige;
};

typedef long long ll;

void dfs(int a) {
    if(v[a]==1) flag = 1;
    if(v[a]) return;
    v[a] = 1; // gray
    for(int i : g[a]){ dfs(i);}
    v[a] = 2; // black
    od[p] = a; p--;
}

//build dp table like knapsack problem
pair<ll,ll> knapSack(int B, vector<ll>& prices, vector<ll>& prestigeV, int N) {
    ll prestige, price;
    vector<vector<pair<ll,ll>>> dp(prices.size() + 1, vector<pair<ll,ll>>(B + 1));
    // Build table dp[][] in bottom up manner
    for(int i = 0; i <= prices.size(); i++) {
        for(int b = 0; b <= B; b++) {
            if(i == 0 || b == 0) {
                dp[i][b] = {0,0};
            }
            else if(prices[i-1] <= b) {
                if(prestigeV[i-1] + dp[i-1][b-prices[i-1]].second < dp[i-1][b].second) {
                    dp[i][b] = dp[i-1][b];
                }
                else{
                    dp[i][b] = { prices[i-1] +dp[i-1][b-prices[i-1]].first , prestigeV[i-1] + dp[i-1][b-prices[i-1]].second};
                }
            }
            else{
                dp[i][b] = dp[i-1][b];
            }
        }
    }
    return dp[prices.size()][B];
}

int main() {
    int B, n, price, prestige,x ,y;
    cin >> B >> n;
    string derived_dish, base_dish, added_ingredient;

    /* initializing a dictionary that maps a dish to its price and prestige */
    for(int i=0; i< n;i++){

        cin >> derived_dish >> base_dish >> added_ingredient >> price >> prestige;

        pair<int,int> price_and_prestige = {price,prestige};

        // if the derived dish is a new dish -> map it to a number that will
        //be the representing vertex of this dish
        if(dishes.find(derived_dish) == dishes.end()){

            dishes.insert({derived_dish, num_of_dishes});
            num_of_dishes++;
        }

        // same for the base dish
        if (dishes.find(base_dish) == dishes.end()){ /*item not found(i.e it is a new base dish) */
            dishes[base_dish] = num_of_dishes;
            num_of_dishes ++;
        }

        // inserting the vertex number of the base and derived dishes
        // into the adjacency matrix
        x = dishes.find(derived_dish)->second;
        y = dishes.find(base_dish)->second;
        g[x].push_back(y);

        // if the derived dish was already givven as an improvement for
        //the base dish,  cheaper option will be chosen
        //if the prices are equal, the more prestigious one will be chosen
        if(weighted_edges.find({x,y})!= weighted_edges.end()){
            if(weighted_edges.find({x,y})->second.first < price_and_prestige.first){
                price_and_prestige.first = weighted_edges.find({x,y})->second.first;
                price_and_prestige.second = weighted_edges.find({x,y})->second.second;
            }
            else if(weighted_edges.find({x,y})->second.first == price_and_prestige.first){
                if(weighted_edges.find({x,y})->second.second > price_and_prestige.second){
                    price_and_prestige.first = weighted_edges.find({x,y})->second.first;
                    price_and_prestige.second = weighted_edges.find({x,y})->second.second;
                }
            }
        }
        // remembering the price and prestige for each couple {derived_dish, base_dish}
        weighted_edges[{x,y}] = price_and_prestige;
    }


    //using DFS to get the nodes in topological order
    flag=0; p=num_of_dishes-1;
    for(int i=0; i<num_of_dishes; i++) if(!v[i])
            dfs(i);

    vector<int> topologic_order;
    for(int i=0; i<num_of_dishes;i++){
        if(od[i] != -1){
            topologic_order.push_back(od[i]);
        }
    }

    // for each dish, going in reverse topological order
    for(int i=topologic_order.size() -1; i>=0;i--){

        long long min_price = 10001;
        long long max_prestige = 0;
        int chosen_son=0;
        int current = topologic_order[i];

        // if the dish is a base dish, set its price and prestige to 0
        if(g[current].size() == 0){
            price_and_perstige_for_vertex[current] = {0,0};
            continue;
        }

        //iterate over all the dishes that the current dish is upgrading
        //the cheapest dish to upgrade will be chosen.
        //in case of equality, the most prestigious one will be chosen
        for(int son : g[current]){

            // if the new son(base_dish) is the cheapest option so far
            if(price_and_perstige_for_vertex[son].first + weighted_edges.find({current,son})->second.first < min_price){
                min_price = price_and_perstige_for_vertex[son].first + weighted_edges.find({current,son})->second.first;
                max_prestige = price_and_perstige_for_vertex[son].second +  weighted_edges.find({current,son})->second.second;

            }

                //if the new son(base_dish) is the same price and better prestige than the current option
            else if(price_and_perstige_for_vertex[son].first + weighted_edges.find({current,son})->second.first == min_price){
                if(price_and_perstige_for_vertex[son].second + weighted_edges.find({current,son})->second.second> max_prestige){
                    max_prestige = price_and_perstige_for_vertex[son].second + weighted_edges.find({current,son})->second.second;

                }
            }
        }

        price_and_perstige_for_vertex[current] = {min_price  , max_prestige };

    }

    vector<ll> prices, prestigeV;
    for(auto it = price_and_perstige_for_vertex.begin(); it != price_and_perstige_for_vertex.end(); it++) {
        if(it->first != 0) {
            prices.push_back(it->first);
            prestigeV.push_back(it->second);
        }
    }

        pair<ll, ll> ans = knapSack(B, prices, prestigeV, n);
        cout << ans.second << endl << ans.first<<endl;
}



