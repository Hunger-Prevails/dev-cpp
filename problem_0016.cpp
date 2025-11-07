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
    int threeSumClosest(vector<int>& nums, int target) {
        auto len = nums.size();
        auto diff = std::numeric_limits<int>::max();

        int answer;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < len; i ++) {
            size_t low = i + 1;
            size_t high = len - 1;

            while (low < high) {
                auto sum = nums[i] + nums[low] + nums[high];

                if (sum == target) return target;

                if (abs(sum - target) < diff) {
                    diff = abs(sum - target);
                    answer = sum;
                }

                if (sum < target) {
                    while (low < high && nums[low] == nums[low + 1]) low ++;
                    low ++;
                } else {
                    while (low < high && nums[high] == nums[high - 1]) high --;
                    high --;
                }
            }
            while (i + 1 < len && nums[i] == nums[i + 1]) i ++;
        }
        return answer;
    }
};

int main() {
    vector<int> v = {-1,2,1,-4};

    Solution s;
    cout << s.threeSumClosest(v, 1) << endl;
}
