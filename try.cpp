#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;



int main() {
    string a = "/a/./b/../../c/";
    string b = a.substr(a.size()-3,a.size()-2);
    cout<<b;

}

