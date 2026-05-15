/*
 * Submission ID: 12293635
 * Problem: Grid Path Description
 * Link: https://cses.fi/problemset/task/1625
 */

// Problem: Grid Paths
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1625
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
#pragma GCC optimize("Ofast")
 
#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
 
#define AC ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
#define pb emplace_back
 
int rec[48];
bool visited[9][9];
 
ll dfs (int x, int y, int k) {
    if (x == 0 || y == 0 || x == 8 || y == 8 || (x == 1 && y == 7 && k != 48)) return 0;
    if (x == 1 && y == 7 && k == 48) return 1;
    if (visited[y][x]) return 0;
    int &cur = rec[k];
    if (visited[y][x-1] && visited[y][x+1]
                          && !visited[y-1][x] && !visited[y+1][x])
        return 0;
    if (visited[y-1][x] && visited[y+1][x]
                          && !visited[y][x-1] && !visited[y][x+1])
        return 0;
    ll ans = 0;
    int delta[5][2] = {{0, 0}, {1, 0}, {-1, 0}, {0, -1}, {0, 1}};
    visited[y][x] = 1;
    if (cur == -1) {
        for (int i = 1; i <= 4; i++) {
            cur = i;
            ans += dfs(x+delta[cur][1], y+delta[cur][0], k+1);
        }
        cur = -1;
    } else {
        // cerr << x << " " << y << " " << rec[k] << endl;
        ans += dfs(x+delta[cur][1], y+delta[cur][0], k+1);
    }
    visited[y][x] = 0;
    return ans;
}
 
int main () {
    AC
    memset(visited, 1, sizeof(visited));
    for (int i = 1; i <= 7; i++) {
        for (int j = 1; j <= 7; j++) {
            visited[i][j] = 0;
        }
    }
 
    for (int i = 0; i < 48; i++) {
        char a;
        cin >> a;
        switch (a) {
        case '?':
            rec[i] = -1;
            break;
        case 'D':
            rec[i] = 1;
            break;
        case 'U':
            rec[i] = 2;
            break;
        case 'L':
            rec[i] = 3;
            break;
        case 'R':
            rec[i] = 4;
            break;
        }
    }
    cout << dfs(1, 1, 0);
    return 0;
}