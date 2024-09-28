#include <iostream>
#include <vector>
#include <algorithm>
 
std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::sort(nums.begin(), nums.end());
 
    for (int i = 0; i < nums.size(); ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
 
        int left = i + 1, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum < 0) {
                ++left;
            } else if (sum > 0) {
                --right;
            } else {
                result.push_back({nums[i], nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) ++left;
                while (left < right && nums[right] == nums[right - 1]) --right;
                ++left;
                --right;
            }
        }
    }
 
    return result;
}
 
int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }
 
    std::vector<std::vector<int>> result = threeSum(nums);
 
    for (const auto& triplet : result) {
        for (int i = 0; i < triplet.size(); ++i) {
            std::cout << triplet[i];
            if (i < triplet.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
 
    return 0;
}