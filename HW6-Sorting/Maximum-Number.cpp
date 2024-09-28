class Solution {
public:
 
 
    std::string largestNumber(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end(), [](int a, int b) {
            return std::to_string(a) + std::to_string(b) > std::to_string(b) + std::to_string(a);
            });
 
        if (nums[0] == 0) {
            return "0"; // 如果最大的数字是 0，那么所有数字都是 0
        }
 
        std::string result;
        for (int num : nums) {
            result += std::to_string(num);
        }
        return result;
    }
 
};