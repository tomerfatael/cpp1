#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

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
    int B, N, price, prestige;
    while(cin >> B >> N) {
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

        vector<ll> prices;
        vector<ll> prestigeV;
        auto it1 = dishPrice.begin();
        auto it2 = dishPrestige.begin();
        for (; it1 != dishPrice.end() && it2 != dishPrestige.end(); ++it1, ++it2) {
            if (it1->second != 0) {
                prices.push_back(it1->second);
                prestigeV.push_back(it2->second);
            }
        }
        pair<ll, ll> ans = knapSack(B, prices, prestigeV, N);
        cout << ans.second << endl << ans.first<<endl;
    }
}

