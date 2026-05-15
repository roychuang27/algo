/*
 * Submission ID: 348599526
 * Problem: Potions (Hard Version)
 * Link: https://codeforces.com/contest/1526/problem/C2
 */

 
#include<bits/stdc++.h>
using namespace std;
 
int main(){
    priority_queue<long long,vector<long long>,greater<long long>> pq;
    //pq維護代價最大的藥水
    int n;
    cin >> n;
    long long hp = 0, cnt = 0;
    while(n--) {
        int k;
        cin >> k;
        hp += k;
        cnt++;
        pq.push(k);
        while(hp < 0){//生命少於 0 開始反悔
            cnt--;
            hp -= pq.top();
            pq.pop();
        }
    }
    cout << cnt << endl;
}