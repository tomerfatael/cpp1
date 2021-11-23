#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;

int main() {
    vector<int> v; // v will hold the input x
    int n, x, a, b, min; //a and b are indicators for first min and first max of the wooden arrows, n and x will hold the input
    min = a = b = 1;
    cin>>n;
    vector<pair<ll,ll>> dp(n+1); //dp table
    for(int i = 0; i < n+1; i++){
        cin>>x;
        v.push_back(x);
    }

    pair<ll,ll> first = {0,1}; //initial value of the dp table
    dp[1] = first;
    //for every input wooden arrow from the third one to the last we will search for the first who is lower from the current one and the first who is greater
    for(int i = 2; i < n+1; i++){
        if(v[i] < v[0]){
            min = 0;
        }
        for(int j = i-1; 0 < j && (a || b); j--){
            if(v[j] > v[i] && a){
                a = 0;
                dp[i].first += (dp[j].second + dp[j].first)%2147483647;
            }
            if(v[j] < v[i] && b){
                b =0;
                dp[i].second += (dp[j].first + dp[j].second)%2147483647;
            }
        }
        if(min && b) {dp[i].second++;}
        a = 1;
        b = 1;
    }
    cout << dp[n].first + dp[n].second<<endl;
}