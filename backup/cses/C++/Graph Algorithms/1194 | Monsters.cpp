/*
 * Submission ID: 12799425
 * Problem: Monsters
 * Link: https://cses.fi/problemset/task/1194
 */

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
 
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
const string mv = "UDLR";
 
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> visited(n + 2, vector<int>(m + 2, -1));
 
	queue<pair<int, int>> bfs;
	pair<int, int> start;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char c;
			cin >> c;
			if (c != '#') visited[i][j] = 0;
 
			if (c == 'M') {
				bfs.push(make_pair(i, j));
				visited[i][j] = 1;
			} else if (c == 'A') start = make_pair(i, j);
		}
	}
 
	while (!bfs.empty()) {
		auto [x, y] = bfs.front();
		bfs.pop();
 
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (visited[nx][ny] == 0) {
				visited[nx][ny] = visited[x][y] + 1;
				bfs.push(make_pair(nx, ny));
			}
		}
	}
 
	visited[start.first][start.second] = 1;
	bfs.push(start);
	vector<vector<int>> pa(n + 2, vector<int>(m + 2));
	pa[start.first][start.second] = -1;
	while (!bfs.empty()) {
		auto [x, y] = bfs.front();
		bfs.pop();
 
		if (x == 1 || x == n || y == 1 || y == m) {
			cout << "YES\n";
			string ans = "";
			while (pa[x][y] != -1) {
				ans += mv[pa[x][y]];
				int nx = x - dx[pa[x][y]];
				int ny = y - dy[pa[x][y]];
				x = nx, y = ny;
			}
			reverse(ans.begin(), ans.end());
			cout << ans.length() << '\n' << ans << '\n';
			return 0;
		}
 
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (visited[nx][ny] != 0 && visited[nx][ny] <= visited[x][y] + 1) continue;
 
			visited[nx][ny] = visited[x][y] + 1;
			pa[nx][ny] = i;
			bfs.push(make_pair(nx, ny));
		}
	}
 
	cout << "NO\n";
}