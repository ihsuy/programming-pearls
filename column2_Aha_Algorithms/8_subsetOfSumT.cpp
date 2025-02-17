#include <math.h>
#include <algorithm>
#include <bitset>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

typedef long long ll;
template <typename T>
inline void inspect(T& t) {
    typename T::iterator i1 = t.begin(), i2 = t.end();
    while (i1 != i2) {
        std::cout << (*i1) << ' ';
        i1++;
    }
    std::cout << '\n';
}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Given a set of n real numbers, a real number t, and an integer k,
how quickly can you determine whether there exists a k-element
subset of the set that sums to at most t?

hint from the book:
The aha! insight for this problem is that some
n-element subset sums to at most t if and only if
the subset consisting of the k smallest elements does.
That subset can be found in time proportional to n log n
by sorting the original set, or in time proportional to n
by using a selection algorithm.
When Ullman assigned this as a class exercise,
students designed algorithms with both running times mentioned
above, as well as O(n log k), O(nk), O(n2), and O(n^k).
Can you find natural algorithms to go with those running times?
*/

// solution n log(n)
bool subsetOfSumT1(
    vector<int>& nums,
    const int& k,
    const int& t) {  // determine whether there exists a k-element
    // subset of the set that sums to at most t
    if (k > nums.size()) {
        return false;
    }
    // as stated in the hint above as well, its obvious that
    // such subset if exists, at least one of them will be
    // the first k elements of nums sorted
    // since these are the smallest k number in the array
    // if their sum is larger than t, we conclude there's no
    // other subsets can have their sum to be less than t
    sort(nums.begin(), nums.end());
    return (accumulate(nums.begin(), nums.begin() + k, 0) <= t);
}

// solution n^k

void subsetOfSumT2_helper(vector<int>& nums,
                          const int& i,
                          const int& s,
                          const int& count,
                          const int& k,
                          vector<int>& sums) {
    if (count == k) {
        sums.push_back(s);
        return;
    } else if (i == nums.size()) {
        return;
    }
    subsetOfSumT2_helper(nums, i + 1, s + nums[i], count + 1, k, sums);
    subsetOfSumT2_helper(nums, i + 1, s, count, k, sums);
}

bool subsetOfSumT2(vector<int>& nums,
                   const int& k,
                   const int& t) {  // brute force
    // simply try out every possible k element subsets in nums
    if (k > nums.size()) {
        return false;
    }

    vector<int> sums;
    subsetOfSumT2_helper(nums, 0, 0, 0, k, sums);
    for (auto& s : sums) {
        if (s <= t) {
            return true;
        }
    }
    return false;
}

// solution nlogk
// this method will be a variation of the n log(n) solution
// instead of sorting everything inplace
// we sort only first k (find the smallest k elements)

// solution nk
// having time complexity equal to nk means that we go through all
// n elements k times, and then we ask ourselves how to find the solution
// by doing so?
// the answer would be: just like the solution above, we search for the
// k smallest elements using linear search

// solution n^2
// I'm not sure if this is the only approach to achieve this time complexity
// but if we use a sort algorithm like bubble sort instead of quicksort or
// mergesort in the first solution, we would end up having a n^2 solution

int main() {
    vector<int> nums{1, 2, 0, 4};
    cout << subsetOfSumT1(nums, 3, 2) << '\n';
    cout << subsetOfSumT2(nums, 3, 2) << '\n';

    return 0;
}
