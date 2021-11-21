#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
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

//comparator by prices (returns the min price) and if prices are equal compare by prestige (return the max prestige)
bool isBetter(const pair<ll, ll>& p1, const pair<ll, ll>& p2) {
    if (p1.first == p2.first) {
        return p1.second > p2.second;
    }
    return p1.first < p2.first;
}

//function to build the map that holds for each dish what is the min price and the corresponding prestige
void updateDish(map<string,ll>& dishPrice, map<string,ll>& dishPrestige, vector<Recipe>& v, string& dish) {
    if(dishPrice.find(dish) != dishPrice.end()) {
        return;
    }

    for(auto it = v.begin(); it != v.end(); ++it){
        if(it->name != dish) {
            continue;
        }

        // update realPrice & realPrestige of base dishes
        updateDish(dishPrice, dishPrestige, v, it->baseDish);

        // calculate realPrice & realPrestige of this dish
        ll realPrice = it->price + dishPrice[it->baseDish];
        ll realPrestige = it->prestige + dishPrestige[it->baseDish];

        // update realPrice & realPrestige of this dish
        if(dishPrice.find(dish) == dishPrice.end() || isBetter({realPrice, realPrestige}, {dishPrice[dish], dishPrestige[dish]})) {
            dishPrice[dish] = realPrice;
            dishPrestige[dish] = realPrestige;
        }
    }
}


int main() {
    int B, N, price, prestige;
    cin >> B >> N;
    vector<Recipe> v;
    map<string, ll> dishPrice;
    map<string, ll> dishPrestige;
    string s1, s2, s3;
    ll n1, n2;
    for (int i = 0; i < N; i++) {
        cin >> s1 >> s2 >> s3;
        cin >> n1 >> n2;
        Recipe elem = {s1, s2, s3, n1, n2};
        v.push_back(elem);
    }

    for (auto it = v.begin(); it != v.end(); it++) {
        updateDish(dishPrice, dishPrestige, v, it->name);
    }

    auto it1 = dishPrice.begin();
    auto it2 = dishPrestige.begin();
    int i = 0;
    for (; it1 != dishPrice.end() && it2 != dishPrestige.end(); ++it1, ++it2) {
        price_and_perstige_for_vertex[i] = {it1->second, it2->second};
        i++;
    }


    vector<long long> previous_row(B+1);
    for(int i=0; i<=B; i++){
        if(price_and_perstige_for_vertex[0].first > i)
            previous_row[i] = 0;
        else
            previous_row[i] = price_and_perstige_for_vertex[0].second;
    }

    /* continuing knapsack algorithm, using the rest of the dishes */
    /* using only O(n) memory because every cell can be filled based on the previous row */
    vector<long long> current_row(B+1);
    for(int i=1; i<price_and_perstige_for_vertex.size(); i++){
        for(int j=0;j<=B; j++){
            if(j - price_and_perstige_for_vertex[i].first >= 0 and previous_row[j - price_and_perstige_for_vertex[i].first] +
                                                                   price_and_perstige_for_vertex[i].second > previous_row[j])
                current_row[j] = previous_row[j - price_and_perstige_for_vertex[i].first] + price_and_perstige_for_vertex[i].second;
            else
                current_row[j] = previous_row[j];
            //cout << previous_row[j] << " ";
        }
        // cout << endl;
        previous_row = current_row;

    }

    /* the last cell represents the maximum prestige using at most B euros */
    cout << current_row[B]<< endl;
    int prev=B;

    /* finding the minimal cost that led to the maximal prestige */
    for(int i=B-1; i>=0;i--){
        if(current_row[i] == current_row[prev])
            prev = i;
        else{
            cout << prev<<endl;
            return 0;}
    }
    cout << prev;
    return 0;


}


