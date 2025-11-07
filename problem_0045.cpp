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
# include <numeric>

using namespace std;
using json = nlohmann::json;

class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> ret(nums.size(), std::numeric_limits<int>::max());
        ret[0] = 0;

        for (size_t i = 0; i < nums.size(); i ++) {
            for (
                auto j: std::views::iota(1, nums[i] + 1)
                | std::views::filter([&](auto j) { return i + j < nums.size(); } )
            ) {
                ret[i + j] = std::min(ret[i + j], ret[i] + 1);
            }
        }
        return ret.back();
    }
};

int main() {
    vector<int> v = {2,3,1,1,4};

    Solution s;
    cout << s.jump(v) << endl;
}
