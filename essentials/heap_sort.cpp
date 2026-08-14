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
    bool is_parent(size_t i, size_t curr_size) {

        return (i + i + 1) < curr_size;
    }

    size_t to_l_kid(size_t i) {

        return i + i + 1;
    }
    size_t to_r_kid(size_t i) {

        return i + i + 2;
    }

    void heapify(vector<int> &numbers, size_t i, size_t curr_size) {

        cout << "heapifies node " << i << endl;

        auto l_kid = to_l_kid(i);
        auto r_kid = to_r_kid(i);

        size_t t_kid = l_kid;

        if (r_kid < curr_size and numbers[l_kid] < numbers[r_kid]) t_kid = r_kid;

        if (numbers[i] < numbers[t_kid]) {

            swap(numbers[i], numbers[t_kid]);

            if(is_parent(t_kid, curr_size)) heapify(numbers, t_kid, curr_size);
        }
    }

    void sort(vector<int> &numbers) {

        for(size_t i = numbers.size(); i != 0; i --) if(is_parent(i - 1, numbers.size())) heapify(numbers, i - 1, numbers.size());

        for (auto n: numbers) cout << n << " ";
        cout << endl;

        for(size_t size = numbers.size(); size != 2; size --) {

            swap(numbers[size - 1], numbers.front());

            heapify(numbers, 0, size - 1);
        }
        swap(numbers[1], numbers.front());
    }
};

int main() {
	Solution solution;

	std::vector numbers{5, 2, 1, 9, 6, 8, 3, 2, 4, 7};

	solution.sort(numbers);

    for (auto n: numbers) cout << n << " ";

	return 0;
}