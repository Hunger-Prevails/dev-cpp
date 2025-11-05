# include <iostream>
# include <fstream>
# include <cstdlib>
# include <vector>
# include <algorithm>
# include <cmath>
# include <cassert>
# include <memory>
# include <set>
# include <ctime>
# include <chrono>
# include <sstream>
# include <map>
# include <queue>
# include <conio.h>
# include <string>
# include <stack>
# include <unordered_set>
# include <unordered_map>
# include <ranges>
# include <stdexcept>
# include <nlohmann/json.hpp>

using namespace std;
using namespace std::chrono;
using json = nlohmann::json;

class Solution {
public:
    void bfs(vector<vector<char>>& grid, size_t i, size_t j, vector<vector<bool>>& visited) {
        std::queue<std::pair<size_t, size_t>> q;

        q.push({i, j});

        while(!q.empty()) {
            auto [i, j] = q.front();
            q.pop();

            visited[i][j] = true;

            if (i >= 1 and grid[i - 1][j] == '1' and !visited[i - 1][j]) {
                q.push({i - 1, j});
            }
            if (j >= 1 and grid[i][j - 1] == '1' and !visited[i][j - 1]) {
                q.push({i, j - 1});
            }
            if (i + 1 < grid.size() and grid[i + 1][j] == '1' and !visited[i + 1][j]) {
                q.push({i + 1, j});
            }
            if (j + 1 < grid[0].size() and grid[i][j + 1] == '1' and !visited[i][j + 1]) {
                q.push({i, j + 1});
            }
        }
    }

    int numIslands(vector<vector<char>>& grid) {
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

        int ret = 0;

        for (size_t i = 0; i < grid.size(); i ++) {
            for (size_t j = 0; j < grid[0].size(); j ++) {
                if (grid[i][j] == '0') continue;

                if (!visited[i][j]) {
                    ret ++;
                    bfs(grid, i, j, visited);
                }
            }
        }
        return ret;
    }
};

int main() {
    std::ifstream f("res/0049.json");
    json data = json::parse(f);

    Solution s;
}
