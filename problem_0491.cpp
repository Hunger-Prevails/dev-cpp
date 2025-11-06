#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {

public:
    set<vector<int> > ret;
    
    vector<vector<int> > findSubsequences(vector<int>& nums) {

    	vector<vector<int> > dest;

        if (nums.empty() or nums.size() == 1) return dest;
        
        vector<int> cur;
        
        findSubseq(cur, nums, 0);
        
        dest.assign(ret.begin(), ret.end());

        return dest;
    }
    
    void findSubseq(vector<int> &cur, vector<int>& nums, size_t index) {

        if (index == nums.size()) {
            if (2 <= cur.size()) ret.emplace(cur);
            return;
        }
        
        if (cur.empty() or cur.back() <= nums[index]) {
            
            cur.push_back(nums[index]);
            findSubseq(cur, nums, index + 1);
            cur.pop_back();
        }
        findSubseq(cur, nums, index + 1);
    }
};

int main() {

	vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1, 1, 1};

	Solution sol;

	auto ret = sol.findSubsequences(nums);

	for (auto subseq: ret) {
		for (auto k: subseq) {
			cout << k << " ";
		}
		cout << endl;
	}
	cout << "total_size:" << ret.size();
	return 0;
}
