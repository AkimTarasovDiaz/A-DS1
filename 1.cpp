#include <iostream>
#include <vector>

int searchInRotatedArray(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        else {
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    return -1;
}

int main() {
    std::vector<int> nums = {7, 8, 9, 1, 2, 3, 4, 5, 6};
    int target = 3;

    int result = searchInRotatedArray(nums, target);

    if (result != -1) {
        std::cout << target << "index: " << result << std::endl;
    } else {
        std::cout << target << " not found" << std::endl;
    }

    return 0;
}