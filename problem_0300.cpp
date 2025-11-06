#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		vector<int> lens(nums.size(), 1);

		for (size_t i = 0; i < nums.size(); i ++) {

			for (size_t j = 0; j < i; j ++) {

				if (nums[j] < nums[i] and lens[j] + 1 > lens[i]) lens[i] = lens[j] + 1;
			}
		}
		auto iter = std::max_element(lens.begin(), lens.end());

		return *iter;
	}
};

int main() {

	vector<int> nums{10, 9, 2, 5, 3, 7, 101, 18};

	Solution sol;

	cout << sol.lengthOfLIS(nums);
	return 0;
}
