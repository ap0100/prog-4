#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int B=31, M=101;

void compute_hash(string &s, vector<ll> &h, vector<int> &p){
    int c_i, len=s.length();
    h.resize(len,0); p.resize(len,1);

    h[0]=(s[0]-'a'+1)%M; //hash of first char
    p[0]=1;

    for (int i=1; i<len; i++){
        c_i=static_cast<int>(s[i])-96; //char value, a=1, b=2,...
        h[i]=(h[i-1]*B+c_i)%M; //hash of the ith char
        p[i]=(p[i-1]*B)%M;
    }
}

ll get_pref_hash(vector<ll> &h, vector<int> &p, int l, int r){
    if(l==0) return h[r];
    ll res=(h[r]-h[l-1]*p[r-l+1])%M;
    return res<0 ? res+M : res;
}

int collision_detection(string &s, string &pattern){
    int n=s.length(), m=pattern.length();
    if(n<m) return -1;

    vector<ll> H, pattern_H;
    vector<int> P, pattern_P;

    compute_hash(s,H,P);
    compute_hash(pattern, pattern_H, pattern_P);

    ll target=pattern_H[m-1]; //the hash of the whole substring, i.e. the pattern string

    for(int i=0; (i+m)<=n; i++){
        ll h_i=get_pref_hash(H, P, i, i+m-1);

        if(h_i==target){
            string sub=s.substr(i,m);
            if(pattern==sub) return i;
        }
    }
}


int main(){
    string s="abekabcugf", pattern="abc";

    cout << collision_detection(s, pattern);

    return 0;
}