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
    vector<vector<int>> threeSum(vector<int>& nums) {
        auto len = nums.size();
        vector<vector<int>> res;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < len; i ++) {
            size_t low = i + 1;
            size_t high = len - 1;

            while (low < high) {
                auto sum = nums[i] +  nums[low] + nums[high];

                if (sum == 0) {
                    res.push_back({nums[i], nums[low], nums[high]});

                    while (low < high && nums[low] == nums[low + 1]) low ++;
                    while (low < high && nums[high] == nums[high - 1]) high --;

                    low ++;
                    high --;
                } else if (sum < 0) {
                    low ++;
                } else {
                    high --;
                }
            }
            while (i + 1 < len && nums[i] == nums[i + 1]) i ++;
        }
        return res;
    }
};

int main() {
    vector<int> v = {-1,0,1,2,-1,-4};

    Solution s;
    auto ret = s.threeSum(v);

    for (const auto& vec : ret) {
        for (const auto& num : vec) {
            cout << num << " ";
        }
        cout << endl;
    }
}
