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
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int, size_t> us;

        for (size_t i = 0; i < nums.size(); i ++) {
            auto found = us.find(nums[i]);
            if (found != us.end())
                return vector<int>{static_cast<int>(found->second), static_cast<int>(i)};
            else
                us.emplace(target - nums[i], i);
        }
        throw std::invalid_argument("Cannot find two numbers that sum up to target");
    }
};

int main() {
    auto v = std::vector<int>{1, 2, 4, 6, 9, 13};

    Solution s;

    std::ranges::for_each(s.twoSum(v, 15), [](auto x){ std::cout << x << ' '; });    
}
