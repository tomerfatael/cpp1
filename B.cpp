#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

void dfs(map<int, vector<int>>& g, vector<int>& visible, int cur, bool& hasCycle, int depth) {
    visible[cur] = depth;
    for(int s: g.find(cur)->second) {
        if(!visible[s]) {
            dfs(g, visible, s, hasCycle, depth+1);
        }
        else if (cur != s && abs(visible[cur] - visible[s]) >= 2) {
            hasCycle = true;
            return;
        }
    }
}

int main() {
    int K, x1, y1, z1, x2, y2, z2;
    cin >> K;
    vector<int> visible(2 * K, 0);
    map<vector<int>, int> m1;
    map<int, vector<int>> g1;
    map<vector<int>, int> m2;
    map<int, vector<int>> g2;

    for (int i = 0; i < K; i++) {
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        vector<int> v1 = {x1, y1, z1};
        vector<int> v2 = {x2, y2, z2};
        vector<int> u1 = {x1,y1};
        vector<int> u2 = {x2,y2};

        /*creating maps for 3d vectors*/
        if (m1.find(v1) == m1.end()) {
            m1.insert({v1, 2 * i});
        }

        if (m1.find(v2) == m1.end()) {
            m1.insert({v2, 2 * i + 1});
        }

        if (g1.find(m1.find(v1)->second) != g1.end()) {
            if (m1.find(m1.find(v2)->first) != m1.end()) {
                g1.find(m1.find(v1)->second)->second.push_back(m1.find(v2)->second);
            } else {
                g1.find(m1.find(v1)->second)->second.push_back(2 * i + 1);
            }
        } else {
            vector<int> v;
            if (m1.find(v2) != m1.end()) {
                v.push_back(m1.find(v2)->second);
                g1.insert({m1.find(v1)->second, v});
            } else {
                v.push_back(2 * i + 1);
                g1.insert({m1.find(v1)->second, v});
            }
        }

        if (g1.find(m1.find(v2)->second) != g1.end()) {
            if (m1.find(v1) != m1.end()) {
                g1.find(m1.find(v2)->second)->second.push_back(m1.find(v1)->second);
            } else {
                g1.find(m1.find(v2)->second)->second.push_back(2 * i);
            }
        } else {
            vector<int> v;
            if (m1.find(v1) != m1.end()) {
                v.push_back(m1.find(v1)->second);
                g1.insert({m1.find(v2)->second, v});
            } else {
                v.push_back(2 * i);
                g1.insert({m1.find(v2)->second, v});
            }
        }

        /*creating maps for 2d vectors*/
        if (m2.find(u1) == m2.end()) {
            m2.insert({u1, 2 * i});
        }

        if (m2.find(u2) == m2.end()) {
            m2.insert({u2, 2 * i + 1});
        }

        if (g2.find(m2.find(u1)->second) != g2.end()) {
            if (m2.find(m2.find(u2)->first) != m2.end()) {
                g2.find(m2.find(u1)->second)->second.push_back(m2.find(u2)->second);
            } else {
                g2.find(m2.find(u1)->second)->second.push_back(2 * i + 1);
            }
        } else {
            vector<int> v;
            if (m2.find(u2) != m2.end()) {
                v.push_back(m2.find(u2)->second);
                g2.insert({m2.find(u1)->second, v});
            } else {
                v.push_back(2 * i + 1);
                g2.insert({m2.find(u1)->second, v});
            }
        }

        if (g2.find(m2.find(u2)->second) != g2.end()) {
            if (m2.find(u1) != m2.end()) {
                g2.find(m2.find(u2)->second)->second.push_back(m2.find(u1)->second);
            } else {
                g2.find(m2.find(u2)->second)->second.push_back(2 * i);
            }
        } else {
            vector<int> v;
            if (m2.find(u1) != m2.end()) {
                v.push_back(m2.find(u1)->second);
                g2.insert({m2.find(u2)->second, v});
            } else {
                v.push_back(2 * i);
                g2.insert({m2.find(u2)->second, v});
            }
        }

    }

    bool trueClosed = false;
    bool floorClosed = false;
    dfs(g1, visible, 0, trueClosed, 0);
    vector<int> visible2(2*K, 0);
    dfs(g2, visible2, 0, floorClosed, 0);
    if(trueClosed) {
        cout<<"True closed chains\n";
    }
    else {
        cout<<"No true closed chains\n";
    }

    if(floorClosed) {
        cout<<"Floor closed chains\n";
    }
    else {
        cout<<"No floor closed chains\n";
    }
}

