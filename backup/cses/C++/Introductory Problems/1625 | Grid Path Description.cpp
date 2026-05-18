#include <iostream>
#include <string>
using namespace std;

const int N = 7;
string s;
int ans = 0;
bool visited[N][N];

void dfs(int r, int c, int step) {
    // When we reach the target cell, only count if path length is exactly 48.
    if(r == N - 1 && c == 0) {
        if(step == 48) ans++;
        return;
    }
    if(step == 48) return; // reached maximum steps without arriving at destination

    // Prune paths that are forced to a dead end:
    // If moving horizontally is blocked while vertical moves remain free (or vice versa)
    if((c == 0 || visited[r][c-1]) && (c == N-1 || visited[r][c+1])) {
        if(r > 0 && r < N-1 && !visited[r-1][c] && !visited[r+1][c])
            return;
    }
    if((r == 0 || visited[r-1][c]) && (r == N-1 || visited[r+1][c])) {
        if(c > 0 && c < N-1 && !visited[r][c-1] && !visited[r][c+1])
            return;
    }
    
    char ch = s[step];
    // If the move is predetermined, use only that direction.
    if(ch != '?') {
        int dr = 0, dc = 0;
        if(ch == 'U') dr = -1;
        else if(ch == 'D') dr = 1;
        else if(ch == 'L') dc = -1;
        else if(ch == 'R') dc = 1;
        int nr = r + dr, nc = c + dc;
        if(nr < 0 || nr >= N || nc < 0 || nc >= N || visited[nr][nc])
            return;
        visited[nr][nc] = true;
        dfs(nr, nc, step + 1);
        visited[nr][nc] = false;
    } else {
        // Otherwise, try all 4 possible directions.
        // Order of moves does not matter.
        if(r > 0 && !visited[r-1][c]) {
            visited[r-1][c] = true;
            dfs(r-1, c, step + 1);
            visited[r-1][c] = false;
        }
        if(r < N-1 && !visited[r+1][c]) {
            visited[r+1][c] = true;
            dfs(r+1, c, step + 1);
            visited[r+1][c] = false;
        }
        if(c > 0 && !visited[r][c-1]) {
            visited[r][c-1] = true;
            dfs(r, c-1, step + 1);
            visited[r][c-1] = false;
        }
        if(c < N-1 && !visited[r][c+1]) {
            visited[r][c+1] = true;
            dfs(r, c+1, step + 1);
            visited[r][c+1] = false;
        }
    }
}

int main(){
    cin >> s;
    // Start at the top-left cell (0,0)
    visited[0][0] = true;
    dfs(0, 0, 0);
    cout << ans << "\n";
    return 0;
}
