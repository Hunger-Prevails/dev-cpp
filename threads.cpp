# include <iostream>
# include <future>
# include <thread>
# include <vector>
# include <mutex>
# include <algorithm>

class Incrementer {
protected:
    int value;
    mutable std::mutex mtx;
public:
    Incrementer() = delete;
    Incrementer(int initialValue) : value(initialValue) {}

    int increment() {
        std::lock_guard<std::mutex> lock(mtx);
        return ++value;
    }
    int increment_by(int amount) {
        std::lock_guard<std::mutex> lock(mtx);
        return value += amount;
    }
    int get_value() const {
        std::lock_guard<std::mutex> lock(mtx);
        return value;
    }
};

int main() {
    Incrementer inc(0);

    std::vector<std::future<int>> task_results;

    std::vector<std::thread> workers;

    for (int i = 0; i < 10; ++i) {
        std::packaged_task<int(int)> task(
            [&inc](int amount) {
                return inc.increment_by(amount) + inc.increment();
            }
        );
        task_results.emplace_back(task.get_future());

        workers.emplace_back(std::move(task), 2);
    }

    std::vector<int> results;

    for (auto& result : task_results) results.emplace_back(result.get());

    for (auto& worker : workers) worker.join();

    std::sort(results.begin(), results.end());

    for (auto& result : results) std::cout << "result: " << result << std::endl;

    std::cout << "=> final value: " << inc.get_value() << std::endl;

    return 0;
}
