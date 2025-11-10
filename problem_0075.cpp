# include <iostream>
# include <fstream>
# include <vector>
# include <algorithm>
# include <memory>
# include <set>
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
    void sortColors(vector<int>& nums) {
        if (nums.empty()) return;

        int low = 0;
        int high = nums.size() - 1;

        auto mid = low;

        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[low ++], nums[mid ++]);
            } else if (nums[mid] == 2) {
                swap(nums[mid], nums[high --]);
            } else {
                mid ++;
            }
        }
    }
};

int main() {
    vector<int> v = {2,0,2,1,1,0};

    Solution s;
    s.sortColors(v);
    for (auto i : v) {
        cout << i << " ";
    }
}
