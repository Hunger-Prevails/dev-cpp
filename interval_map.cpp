#include <map>
#include <stdexcept>
#include <iostream>
#include <map>

using namespace std;

template<typename K, typename V>
class interval_map {
public:
	V m_valBegin;
	std::map<K, V> m_map;
public:
	interval_map(V const& val): m_valBegin(val)	{}

	void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
		if (!(keyBegin < keyEnd)) return;

		if (m_map.empty()) {
			if (val == m_valBegin) throw std::invalid_argument( "input value violates canonical constraint" );

			m_map[keyBegin] = val;
			m_map[keyEnd] = m_valBegin;
			return;
		}
		auto begNextIt = m_map.upper_bound(keyBegin);
		auto endNextIt = m_map.upper_bound(keyEnd);

		if (begNextIt != endNextIt) {
			// keyBegin and keyEnd fall into separate intervals
			if (begNextIt == m_map.begin()) {
				// keyBegin falls into the first interval
				if (val == m_valBegin) throw std::invalid_argument( "input value violates canonical constraint" );

			} else {
				// keyBegin falls into some other interval
				auto begPrevIt = begNextIt;
				begPrevIt --;

				if (begPrevIt->first < keyBegin) {
					if (val == begPrevIt->second) throw std::invalid_argument( "input value violates canonical constraint" );
				} else {
					if (begPrevIt == m_map.begin() and val == m_valBegin) throw std::invalid_argument( "input value violates canonical constraint" );

					if (begPrevIt != m_map.begin() and val == (--begPrevIt)->second) throw std::invalid_argument( "input value violates canonical constraint" );
				}
			}
			auto endPrevIt = endNextIt;
			endPrevIt --;

			auto endVal = endPrevIt->second;

			if (val == endVal) throw std::invalid_argument( "input value violates canonical constraint" );

			m_map.erase(begNextIt, endNextIt);
			m_map[keyBegin] = val;
			m_map[keyEnd] = endVal;
			return;

		} else {
			// keyBegin and keyEnd fall into the same interval
			if (endNextIt == m_map.begin()) {
				// keyBegin and keyEnd both fall into the first interval
				if (val == m_valBegin) throw std::invalid_argument( "input value violates canonical constraint" );

				m_map[keyBegin] = val;
				m_map[keyEnd] = m_valBegin;
				return;

			} else {
				// keyBegin and keyEnd both fall into some other interval
				auto begPrevIt = begNextIt;
				begPrevIt --;

				if (begPrevIt->first < keyBegin) {
					if (val == begPrevIt->second) throw std::invalid_argument( "input value violates canonical constraint" );
				} else {
					if (begPrevIt == m_map.begin() and val == m_valBegin) throw std::invalid_argument( "input value violates canonical constraint" );

					if (begPrevIt != m_map.begin() and val == (--begPrevIt)->second) throw std::invalid_argument( "input value violates canonical constraint" );
				}
				auto endPrevIt = endNextIt;
				endPrevIt --;

				auto endVal = endPrevIt->second;

				if (val == endVal) throw std::invalid_argument( "input value violates canonical constraint" );

				m_map[keyBegin] = val;
				m_map[keyEnd] = endVal;
				return;
			}
		}
	}
	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it = m_map.upper_bound(key);
		if(it == m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};

void printIntervals(interval_map<int, char> &intervals) {

	for (auto it = intervals.m_map.begin(); it != intervals.m_map.end(); it ++) cout << it->first << " -> " << it->second << endl;
}

void IntervalMapTest() {
	interval_map<int, char> intervals('A');

	intervals.assign(4, 10, 'B');
	intervals.assign(6, 8, 'C');
	intervals.assign(0, 2, 'D');
	intervals.assign(5, 6, 'D');
	intervals.assign(1, 4, 'E');

	printIntervals(intervals);
}

int main() {
	IntervalMapTest();
	return 0;
}