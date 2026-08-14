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

using namespace std;
using namespace std::chrono;

class Solution {
public:
    void sort(vector<int> &numbers) {

        sort(numbers, 0, numbers.size() - 1);
    }
    void sort(vector<int> &numbers, size_t pos_l, size_t pos_r) {

        cout << "enters with [" << pos_l << ", " << pos_r << "]" << endl;

        if (pos_r <= pos_l) return;

        auto mid = numbers[pos_l];

        auto ptr_l = pos_l;
        auto ptr_r = pos_r;

        while(true) {

            while(numbers[ptr_l] <= mid and ptr_l < ptr_r) ptr_l ++;
            while(numbers[ptr_r] >= mid and ptr_r > ptr_l) ptr_r --;

            if (ptr_l == ptr_r) break;

            swap(numbers[ptr_l], numbers[ptr_r]);
        }
        if (numbers[ptr_l] < mid) swap(numbers[pos_l], numbers[ptr_l]);

        sort(numbers, pos_l, ptr_l - 1);
        sort(numbers, ptr_l + 1, pos_r);
    }
};

int main() {
	Solution solution;

	std::vector numbers{5, 2, 1, 9, 6, 8, 3, 2, 4, 7};

    cout << numbers.size() << endl;    

	solution.sort(numbers);

    for (auto n: numbers) cout << n << " ";

	return 0;
}