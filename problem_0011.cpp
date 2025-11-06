# include <iostream>
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

using namespace std;
using namespace std::chrono;

class Solution {
public:
    int maxArea(vector<int>& height) {
        size_t l_p = 0;
        size_t r_p = height.size() - 1;

        size_t max_area = 0;

        while(l_p < r_p) {
            max_area = std::max(max_area, (r_p - l_p) * std::min(height[l_p], height[r_p]));

            if (height[l_p] < height[r_p]) {
                auto curr_h = height[l_p];
                while (height[l_p] <= curr_h and l_p < r_p) l_p ++;
            } else {
                auto curr_h = height[r_p];
                while (height[r_p] <= curr_h and l_p < r_p) r_p --;
            }
        }
        return max_area;
    }
};

int main() {
    std::vector<int> heights = {1, 8, 6, 2, 5, 4, 8, 3, 7};

    Solution s;

    std::cout << s.maxArea(heights);
}
