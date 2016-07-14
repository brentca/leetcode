// LCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <list>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <set>
#include <queue>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <numeric>
#include <functional>
#include <map>

using namespace std;


//////////////////////////Tag BACKTRACK//////////////////////////////////////////
namespace BACKTRACK {
	/*23. Merge k Sorted Lists (medium)
	*/
	/*23. Merge k Sorted Lists end */


	/*23. Merge k Sorted Lists (medium)
	*/
	/*23. Merge k Sorted Lists end */


	/*22. Generate Parentheses (medium)
	https://leetcode.com/problems/generate-parentheses/
	https://discuss.leetcode.com/topic/4485/concise-recursive-c-solution
	*/
	class Solution22 {
		vector<string> res;
	public:
		vector<string> generateParenthesis(int n) {
			string str;
			generate(n, 0, 0, str);

			return res;
		}

		void generate(int n, int left, int right, string str) {
			auto compare = [&](int a1, int b1) {return 1; };

			if (left == n && right == n)
				res.push_back(str);

			if (left < n)
				generate(n, left + 1, right, str + "(");

			if (right < n && right < left)
				generate(n, left, right + 1, str + ")");
		}
		
		/*
		void generate1(int n) {
			auto compare = [&](int a1, int b1) {return 1; };

			if (left == n && right == n)
				res.push_back(str);

			if (left < n)
				generate(n, left + 1, right, str + "(");

			if (right < n && right < left)
				generate(n, left, right + 1, str + ")");
		}
		*/
		static void main() {
			Solution22* test = new Solution22;
			vector<string> result;

			int num1 = 3;
			result = test->generateParenthesis(num1);

			delete test;
		}
	};
	/*22. Generate Parentheses end */

	/*17. Letter Combinations of a Phone Number (medium)
	https://leetcode.com/problems/letter-combinations-of-a-phone-number/
	https://discuss.leetcode.com/topic/8465/my-java-solution-with-fifo-queue
	*/
	class Solution17 {
	public:
		vector<string> letterCombinations(string digits) {
			vector<string> result;
			if (digits.empty())
				return result;

			vector<string> strmap = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

			result.push_back("");
			for (int i = 0; i < digits.size(); ++i) {
				int num = digits[i] - '0';

				if (num < 0 || num > 9)
					break;

				string candidate = strmap[num];

				if (candidate.empty()) continue;

				vector<string> tmp;

				for (int j = 0; j < candidate.size(); ++j)
				for (int k = 0; k < result.size(); ++k)
					tmp.push_back(result[k] + candidate[j]);

				result.swap(tmp);
			}

			return result;
		}
	};
	/*17. Letter Combinations of a Phone Number end */


	/*89. Gray Code (medium)
	https://leetcode.com/problems/gray-code/
	https://discuss.leetcode.com/topic/1011/what-is-the-best-solution-for-gray-code-problem-no-extra-space-used-and-no-recursion
	https://discuss.leetcode.com/topic/8557/an-accepted-three-line-solution-in-java
	*/
	class Solution89 {
	public:
		vector<int> grayCode(int n) {
			vector<int> result;

			if (n == 0) {
				result.push_back(0);
				return result;
			}

			result.push_back(0);
			result.push_back(1);
			for (int idx = 1; idx < n; ++idx) {

				int num = result.size();

				int base = 1 << idx;
				for (int j = num - 1; j >= 0; --j)
					result.push_back(base + result.at(j));
			}

			return result;
		}
	};
	/*89. Gray Code end */

}
//////////////////////////Tag BACKTRACK end//////////////////////////////////////////


//////////////////////////Tag STACK//////////////////////////////////////////
namespace STACK {
	/*42. Trapping Rain Water (hard)
	https://leetcode.com/problems/trapping-rain-water/
	https://discuss.leetcode.com/topic/5125/sharing-my-simple-c-code-o-n-time-o-1-space
	https://discuss.leetcode.com/topic/18731/7-lines-c-c
	*/
	class Solution {
	public:
		int trap(vector<int>& height) {
			if (height.size() < 2)
				return 0;

			int result = 0, left = 0, maxleft = 0, maxright = 0;
			int right = height.size() - 1;

			while (left <= right) {
				if (height[left] <= height[right]) {
					if (height[left] >= maxleft)
						maxleft = height[left];
					else
						result += maxleft - height[left];

					++left;
				}
				else {
					if (height[right] >= maxright)
						maxright = height[right];
					else
						result += maxright - height[right];

					--right;
				}
			}

			return result;
		}
	};
	/*42. Trapping Rain Water end */


	/*224. Basic Calculator (hard)
	https://leetcode.com/problems/basic-calculator/
	https://discuss.leetcode.com/topic/15816/iterative-java-solution-with-stack
	https://discuss.leetcode.com/topic/22359/16-ms-solution-in-c-with-stacks
	*/
	class Solution224 {
	public:
		int calculate(string s) {
			int flag = 1;
			int result = 0, num = 0;
			stack<int> ops;

			for (int i = 0; i < s.size(); ++i) {
				if (s[i] >= '0' && s[i] <= '9') {
					num = (s[i] - '0');
					while (i + 1 < s.size() && isdigit(s[i + 1])) {
						num = num * 10 + (s[i + 1] - '0');
						++i;
					}

					result += flag*num;
				}
				else if (s[i] == '+' || s[i] == '-')
					flag = (s[i] == '+' ? 1 : -1);
				else if (s[i] == '(') {
					ops.push(result);
					ops.push(flag);
					result = 0;
					flag = 1;
				}
				else if (s[i] == ')') {
					int tmp = ops.top();
					ops.pop();
					result = result*tmp + ops.top();
					ops.pop();
				}
			}

			return result;
		}
	};
	/*224. Basic Calculator end */


	/*84. Largest Rectangle in Histogram (hard)
	https://leetcode.com/problems/largest-rectangle-in-histogram/
	https://discuss.leetcode.com/topic/3913/my-concise-c-solution-ac-90-ms
	http://www.geeksforgeeks.org/largest-rectangle-under-histogram/
	*/
	class Solution84 {
	public:
		int largestRectangleArea(vector<int>& heights) {
			stack<int> s;
			heights.push_back(0);
			int res = 0;

			int k = 0;
			while (k < heights.size()) {
				if (s.empty() || heights[k] > heights[s.top()])
					s.push(k++);
				else {
					int t = s.top();

					s.pop();
					res = max(res, heights[t] * (s.empty() ? k : (k - s.top() - 1)));
				}
			}

			return res;
		}

		static void main() {
			Solution84* test = new Solution84;
			int result;

			vector<int> heights1 = { 4, 5, 6, 2 };
			result = test->largestRectangleArea(heights1);

			vector<int> heights2 = { 6, 2, 5, 4, 5, 1, 6 };
			result = test->largestRectangleArea(heights2);
		}
	};
	/*84. Largest Rectangle in Histogram end */


	/*85. Maximal Rectangle (hard)
	https://leetcode.com/problems/maximal-rectangle/
	https://discuss.leetcode.com/topic/1634/a-o-n-2-solution-based-on-largest-rectangle-in-histogram
	https://discuss.leetcode.com/topic/6650/share-my-dp-solution
	*/
	class Solution85 {
	public:
		int maximalRectangle(vector<vector<char>>& matrix) {
			if (matrix.empty() || matrix[0].empty())
				return 0;

			int row = matrix.size();
			int col = matrix[0].size();

			vector<int> height(col + 1, 0);
			int result = 0;

			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < col; ++j) {
					if (height[j] == 0)
						height[j] = (matrix[i][j] == '1');
					else if (matrix[i][j] == '0')
						height[j] = 0;
					else
						height[j] ++;
				}

				stack<int> s;
				int k = 0;

				while (k < col + 1) {
					if (s.empty() || height[k] > height[s.top()])
						s.push(k++);
					else {
						int t = s.top();
						s.pop();

						result = max(result, height[t] * (s.empty() ? k : k - s.top() - 1));
					}
				}
			}

			return result;
		}

		int maximalRectangle1(vector<vector<char> > &matrix) {
			if (matrix.empty()) return 0;
			const int m = matrix.size();
			const int n = matrix[0].size();
			vector<int> left(n, 0);
			vector<int> right(n, n);
			vector<int> height(n, 0);
			int maxA = 0;

			for (int i = 0; i < m; ++i) {
				int cur_left = 0, cur_right = n;

				for (int j = 0; j < n; ++j) { // compute height (can do this from either side)
					if (matrix[i][j] == '1') 
						height[j]++;
					else 
						height[j] = 0;
				}

				for (int j = 0; j < n; ++j) { // compute left (from left to right)
					if (matrix[i][j] == '1') 
						left[j] = max(left[j], cur_left);
					else { 
						left[j] = 0; cur_left = j + 1; 
					}
				}

				// compute right (from right to left)
				for (int j = n - 1; j >= 0; j--) {
					if (matrix[i][j] == '1') 
						right[j] = min(right[j], cur_right);
					else { 
						right[j] = n; cur_right = j; 
					}
				}

				// compute the area of rectangle (can do this from either side)
				for (int j = 0; j<n; j++)
					maxA = max(maxA, (right[j] - left[j])*height[j]);
			}

			return maxA;
		}

		static void main() {
			Solution85* test = new Solution85;
			int result;
			vector<vector<char>> matrix1 = { { '0', '0', '0', '1', '0', '0', '0' },
			{ '0', '0', '1', '1', '1', '0', '0' },
			{ '0', '1', '1', '1', '1', '1', '0' } };

			result = test->maximalRectangle(matrix1);
			result = test->maximalRectangle1(matrix1);

			delete test;
		}
	};
	/*85. Maximal Rectangle end */


	/*150. Evaluate Reverse Polish Notation (medium)
	https://leetcode.com/problems/evaluate-reverse-polish-notation/
	https://discuss.leetcode.com/topic/5780/accepted-c-recursive-solution-56-ms-with-explanation-simplest-possible
	https://discuss.leetcode.com/topic/1941/java-accepted-code-stack-implementation
	*/
	class Solution150 {
	public:
		int evalRPN(vector<string>& tokens) {
			stack<string> tmp;
			string opr1, opr2;
			int result;

			for (int i = 0; i < tokens.size(); ++i) {
				if ((tokens[i].size() == 1) && (tokens[i][0] < '0' || tokens[i][0] > '9')) {
					opr2 = tmp.top();
					tmp.pop();

					opr1 = tmp.top();
					tmp.pop();

					if (tokens[i][0] == '+') {
						result = atoi(opr1.data()) + atoi(opr2.data());
						tmp.push(to_string(result));
					}
					else if (tokens[i][0] == '-') {
						result = atoi(opr1.data()) - atoi(opr2.data());
						tmp.push(to_string(result));
					}
					else if (tokens[i][0] == '/') {
						if (atoi(opr2.data()) == 0)
							break;

						result = atoi(opr1.data()) / atoi(opr2.data());
						tmp.push(to_string(result));
					}
					else if (tokens[i][0] == '*') {
						result = atoi(opr1.data()) * atoi(opr2.data());
						tmp.push(to_string(result));
					}
				}
				else
					tmp.push(tokens[i]);

			}

			return atoi(tmp.top().data());
		}
	};
	/*150. Evaluate Reverse Polish Notation end */


	/*331. Verify Preorder Serialization of a Binary Tree (medium)
	https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/
	https://discuss.leetcode.com/topic/35976/7-lines-easy-java-solution
	*/
	class Solution331 {
	public:
		bool isValidSerialization(string preorder) {
			if (preorder.empty())
				return false;

			int len = preorder.size();
			stack<string> buf;
			string strnum;

			for (int i = 0; i < len; ++i) {
				if (preorder[i] == '#') {
					strnum.clear();
					if (!buf.empty() && buf.top() == "#") {
						while (!buf.empty() && buf.top() == "#") {
							buf.pop();

							if (!buf.empty() && buf.top() != "#")
								buf.pop();
							else
								return false;
						}

						buf.push("#");
					}
					else
						buf.push("#");
				}
				else if (preorder[i] != ',') {
					strnum.push_back(preorder[i]);
					if (i == len - 1)
						buf.push(strnum);
				}
				else if (!strnum.empty())
					buf.push(strnum);
			}

			if (buf.size() == 1 && buf.top() == "#")
				return true;

			return false;
		}
	};
	/*331. Verify Preorder Serialization of a Binary Tree end */


	/*71. Simplify Path (medium)
	https://leetcode.com/problems/simplify-path/
	https://discuss.leetcode.com/topic/2872/my-o-n-ac-code-just-need-to-handle-two-special-cases
	https://discuss.leetcode.com/topic/8678/c-10-lines-solution
	*/
	class Solution71 {
	public:
		string simplifyPath(string path) {
			vector<string> parents;
			string result;
			string node;

			path.push_back('/');
			for (int i = 0; i < path.size(); ++i) {
				if (path[i] == '/') {
					if (node.size() == 0)
						continue;

					if (node == ".")
						;
					else if (node == "..") {
						if (parents.size() > 0)
							parents.pop_back();
					}
					else
						parents.push_back(node);

					node.clear();
				}
				else
					node.push_back(path[i]);
			}

			if (parents.size() == 0)
				return "/";

			for (int i = 0; i < parents.size(); ++i)
				result.append("/" + parents[i]);

			return result;
		}
	};
	/*71. Simplify Path end */



	/*232. Implement Queue using Stacks (easy)
	https://leetcode.com/problems/implement-queue-using-stacks/
	*/
	class Queue232 {
	public:
		// Push element x to the back of queue.
		void push(int x) {
			stack<int> tmp;

			while (!data.empty()) {
				tmp.push(data.top());
				data.pop();
			}

			data.push(x);

			while (!tmp.empty()) {
				data.push(tmp.top());
				tmp.pop();
			}
		}

		// Removes the element from in front of queue.
		void pop(void) {
			data.pop();
		}

		// Get the front element.
		int peek(void) {
			return data.top();
		}

		// Return whether the queue is empty.
		bool empty(void) {
			return data.empty();
		}

		stack<int> data;
	};
	/*232. Implement Queue using Stacks end */


	/*20. Valid Parentheses (easy)
	https://leetcode.com/problems/valid-parentheses/
	https://discuss.leetcode.com/topic/7813/my-easy-to-understand-java-solution-with-one-stack
	*/
	class Solution20 {
	public:
		bool isValid(string s) {
			stack<char> left;

			for (int i = 0; i < s.size(); ++i) {
				char tmp = s.at(i);

				if ('(' == tmp || '{' == tmp || '[' == tmp)
					left.push(tmp);
				else if (!left.empty() && (')' == tmp) && left.top() == '(')
					left.pop();
				else if (!left.empty() && ('}' == tmp) && left.top() == '{')
					left.pop();
				else if (!left.empty() && (']' == tmp) && left.top() == '[')
					left.pop();
				else
					return false;
			}


			return left.empty();
		}
	};
	/*20. Valid Parentheses end */
}
//////////////////////////Tag STACK end//////////////////////////////////////////


//////////////////////////Tag HEAP//////////////////////////////////////////
namespace HEAP {
	/*23. Merge k Sorted Lists (hard)
	https://leetcode.com/problems/merge-k-sorted-lists/
	https://discuss.leetcode.com/topic/21812/difference-between-priority-queue-and-heap-and-c-implementation
	http://bangbingsyb.blogspot.ca/2014/11/leetcode-merge-k-sorted-lists.html
	*/
	class Solution23 {
	public:
		struct ListNode {
			int val;
			ListNode *next;
			ListNode(int x) : val(x), next(NULL) {}
		};

		ListNode* mergetwo(ListNode* l1, ListNode* l2) {
			ListNode dummy(-1);
			ListNode* pre = &dummy;

			while (l1 && l2) {
				if (l1->val <= l2->val) {
					pre->next = l1;
					l1 = l1->next;
				}
				else {
					pre->next = l2;
					l2 = l2->next;
				}

				pre = pre->next;
			}

			pre->next = (l1 != NULL ? l1 : l2);

			return dummy.next;
		}

		ListNode* mergeKLists(vector<ListNode*>& lists) {
			ListNode* result = NULL;

			if (lists.empty())
				return NULL;

			result = lists[0];

			for (int i = 1; i < lists.size(); ++i)
				result = mergetwo(result, lists[i]);

			return result;
		}
	};
	/*23. Merge k Sorted Lists end */


	/*239. Sliding Window Maximum (hard)
	https://leetcode.com/problems/sliding-window-maximum/
	https://discuss.leetcode.com/topic/19055/java-o-n-solution-using-deque-with-explanation
	https://discuss.leetcode.com/topic/19297/this-is-a-typical-monotonic-queue-problem
	*/
	class Solution239 {
	public:
		vector<int> maxSlidingWindow(vector<int>& nums, int k) {
			vector<int> result;

			if (nums.size() < 1 || k < 1)
				return result;

			deque<int> window;
			for (int i = 0; i < nums.size(); ++i) {
				if (!window.empty() && window.front() == i - k)
					window.pop_front();

				while (!window.empty() && nums[window.back()] < nums[i])
					window.pop_back();

				window.push_back(i);

				if (i >= k - 1)
					result.push_back(nums[window.front()]);
			}

			return result;
		}

		static void main() {
			Solution239* test = new Solution239;
			vector<int> result;

			vector<int> nums1 = { 1, 3, -1, -3, 5, 3, 6, 7 };
			int k1 = 3;
			//result = test->maxSlidingWindow(nums1, k1);

			vector<int> nums2 = { 6, 5, 4, 3, 2, 1 };
			int k2 = 3;
			result = test->maxSlidingWindow(nums2, k2);

			delete test;
		}
	};
	/*239. Sliding Window Maximum end */


	/*347. Top K Frequent Elements (meduim)
	https://leetcode.com/problems/top-k-frequent-elements/
	https://discuss.leetcode.com/topic/44226/c-o-n-log-n-k-unordered_map-and-priority_queue-maxheap-solution
	https://discuss.leetcode.com/topic/44237/java-o-n-solution-bucket-sort
	*/
	class Solution347 {
	public:
		vector<int> topKFrequent(vector<int>& nums, int k) {
			unordered_map<int, int> map;

			for (int i = 0; i < nums.size(); ++i)
				map[nums[i]] ++;


			vector<int> res;
			priority_queue<pair<int, int>> pq;
			for (auto it = map.begin(); it != map.end(); it++) {
				pq.push(make_pair(it->second, it->first));
			}

			for (int i = 0; i < k; ++i) {
				res.push_back(pq.top().second);
				pq.pop();
			}

			return res;
		}
	};
	/*347. Top K Frequent Elements end */


	/*313. Super Ugly Number (meduim)
	https://leetcode.com/problems/super-ugly-number/
	https://discuss.leetcode.com/topic/31012/7-line-consice-o-kn-c-solution
	*/
	class Solution313 {
	public:
		int nthSuperUglyNumber(int n, vector<int>& primes) {
			vector<int> uglynumbs(n, INT_MAX);
			vector<int> index(primes.size(), 0);

			uglynumbs[0] = 1;

			for (int i = 1; i < n; ++i) {
				for (int j = 0; j < primes.size(); ++j)
					uglynumbs[i] = min(uglynumbs[i], uglynumbs[index[j]] * primes[j]);
				for (int j = 0; j < primes.size(); ++j)
					index[j] += (uglynumbs[i] == uglynumbs[index[j]] * primes[j]);
			}

			return uglynumbs[n - 1];
		}

		static void main() {
			Solution313* test = new Solution313;
			int result;

			vector<int> primes1 = { 2, 7, 13, 19 };
			int n1 = 12;

			result = test->nthSuperUglyNumber(n1, primes1);
			delete test;
		}
	};
	/*313. Super Ugly Number end */


	/*215. Kth Largest Element in an Array (meduim)
	https://leetcode.com/problems/kth-largest-element-in-an-array/
	https://discuss.leetcode.com/topic/14597/solution-explained
	*/
	class Solution215 {
	public:
		int partition(vector<int>& nums, int low, int high) {
			int pivot = nums[low];
			int left = low + 1, right = high;

			while (left <= right) {
				if (nums[left] < pivot && nums[right] > pivot)
					swap(nums[left++], nums[right--]);

				if (nums[left] >= pivot)
					++left;

				if (nums[right] <= pivot)
					--right;
			}

			swap(nums[low], nums[right]);
			return right;
		}

		void heapadjust(vector<int>& nums, int s, int m) {
			int ori = nums[s];

			for (int j = 2 * s; j <= m; j *= 2) {
				if (j < m && nums[j] < nums[j + 1])
					++j;

				if (ori >= nums[j])
					break;

				swap(nums[s], nums[j]);
				s = j;
			}

			nums[s] = ori;
		}

		int findKthLargest(vector<int>& nums, int k) {
			int len = nums.size();
			for (int i = len / 2; i >= 0; --i)
				heapadjust(nums, i, len - 1);

			for (int i = 0; i < k; ++i) {
				swap(nums[0], nums[len - i - 1]);
				heapadjust(nums, 0, len - i - 2);
			}

			return nums[len - k];
		}

		int findKthLargest1(vector<int>& nums, int k) {
			int low = 0;
			int high = nums.size() - 1;
			int pivot;

			while (true) {
				pivot = partition(nums, low, high);

				if (pivot == k - 1)
					return nums[pivot];

				if (pivot > k - 1)
					high = pivot - 1;
				else
					low = pivot + 1;

			}
		}
	};
	/*215. Kth Largest Element in an Array end */


	/*264. Ugly Number II (meduim)
	https://leetcode.com/problems/ugly-number-ii/
	https://discuss.leetcode.com/topic/21882/my-16ms-c-dp-solution-with-short-explanation
	*/
	class Solution264 {
	public:

		int nthUglyNumber(int n) {
			if (n == 1)
				return 1;

			int t2(0), t3(0), t5(0);
			vector<int> nums(n);
			nums[0] = 1;

			for (int i = 1; i < n; ++i) {
				nums[i] = min(nums[t2] * 2, min(nums[t3] * 3, nums[t5] * 5));

				if (nums[i] == nums[t2] * 2)
					++t2;
				if (nums[i] == nums[t3] * 3)
					++t3;
				if (nums[i] == nums[t5] * 5)
					++t5;
			}

			return nums[n - 1];
		}
	};
	/*264. Ugly Number II end */
	
}
//////////////////////////Tag HEAP end//////////////////////////////////////////



//////////////////////////Tag Greedy//////////////////////////////////////////
namespace GREEDY {
	/*135. Candy (hard)
	https://leetcode.com/problems/candy/
	https://discuss.leetcode.com/topic/37924/very-simple-java-solution-with-detail-explanation/2
	*/
	class Solution135 {
	public:
		int candy(vector<int>& ratings) {
			int len = ratings.size();
			vector<int> nums(len, 0);

			nums[0] = 1;
			for (int i = 1; i < len; ++i) {
				if (ratings[i] > ratings[i - 1])
					nums[i] = nums[i - 1] + 1;
				else
					nums[i] = 1;
			}


			for (int i = len - 2; i >= 0; --i) {
				if (ratings[i] > ratings[i + 1] && nums[i] <= nums[i + 1])
					nums[i] = nums[i + 1] + 1;
			}

			int result = 0;
			for (auto item : nums)
				result += item;

			return result;
		}
	};
	/*135. Candy end */


	/*321. Create Maximum Number (hard)
	https://leetcode.com/problems/create-maximum-number/
	https://discuss.leetcode.com/topic/32272/share-my-greedy-solution
	*/
	class Solution321 {
	public:
		vector<int> helper(vector<int>& nums, int k) {
			int n = nums.size();
			int j = 0; // the count of the stacked array 
			vector<int> result(k, 0);

			for (int i = 0; i < n; ++i) {
				//result[j-1] stores the top of the stack 
				while (j > 0 && n - i + j > k && nums[i] > result[j - 1])  j--;
				if (j < k) result[j++] = nums[i];
			}
			return result;
		}

		vector<int> merge(vector<int>& nums1, vector<int>& nums2, int k) {
			vector<int> result(k, 0);
			ostringstream num_str1, num_str2;
			string str1, str2;
			for (auto num : nums1)  num_str1 << num;
			for (auto num : nums2)  num_str2 << num;
			str1 = num_str1.str();
			str2 = num_str2.str();
			for (int i = 0, j = 0, r = 0; r < k; ++r)
				result[r] = str1.substr(i).compare(str2.substr(j)) > 0 ? nums1[i++] : nums2[j++];

			return result;
		}

	public:
		vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
			int n = nums1.size(), m = nums2.size();
			vector<int> result(k, 0);
			string result_str;
			for (int i = max(0, k - m); i <= k && i <= n; i++) {
				vector<int> sub_1 = helper(nums1, i);
				vector<int> sub_2 = helper(nums2, k - i);
				vector<int> candidate = merge(sub_1, sub_2, k);
				ostringstream str_c;
				for (auto number : candidate)  str_c << number;
				if (result_str == "" || str_c.str().compare(result_str) > 0) {
					result_str = str_c.str();
					result = candidate;
				}
			}
			return result;
		}

		static void main() {
			Solution321* test = new Solution321;
			vector<int> result;

			vector<int> nums1_1 = { 3, 4, 6, 5 };
			vector<int> nums1_2 = { 9, 1, 2, 5, 8, 3};
			int k1 = 5;

			result = test->maxNumber(nums1_1, nums1_2, k1);

			vector<int> nums2_1 = { 3, 4, 6, 5 };
			vector<int> nums2_2 = { 9, 1, 2, 5, 8, 3 };
			int k2 = 5;

			result = test->maxNumber(nums2_1, nums2_2, k2);
			delete test;
		}
	};
	/*321. Create Maximum Number end */


	/*316. Remove Duplicate Letters (hard)
	https://leetcode.com/problems/remove-duplicate-letters/
	https://discuss.leetcode.com/topic/31413/easy-to-understand-iterative-java-solution/2
	*/
	class Solution316 {
	public:
		string removeDuplicateLetters(string s) {
			vector<int> nums(26, 0);

			for (auto item : s)
				nums[item - 'a'] ++;

			int pos = 0;
			char c;
			for (int i = 0; i < s.size(); ++i) {
				c = s[i];

				if (c < s[pos])
					pos = i;

				if (--nums[c - 'a'] == 0)
					break;
			}

			string tmp;
			for (int i = pos + 1; i < s.size(); ++i) {
				if (s[i] != s[pos])
					tmp.push_back(s[i]);
			}

			return s.empty() ? "" : s.substr(pos, 1) + removeDuplicateLetters(tmp);
		}

		string removeDuplicateLetters1(string s) {

			map<char, int> pos;
			int diffs = 0;

			//find last postion of every char
			for (int i = s.size() - 1; i >= 0; --i) {
				if (pos.count(s[i]) < 1) {
					pos[s[i]] = i;
					++diffs;
				}

				if (diffs >= 26)
					break;
			}

			string result;
			result.resize(diffs);
			int start = 0;
			int cur = 0;

			for (int i = 0; i < diffs; ++i) {
				//cout<<item.first<<","<<item.second<<endl;
				start = findSmallest(s, start, pos);
				char c = s[start++];
				result[cur++] = c;
				pos[c] = -1;
			}

			return result;
		}

		int findSmallest(const string& s, int start, map<char, int>& pos) {
			int end = INT_MAX;
			for (auto item : pos)
			if (item.second != -1)
				end = min(end, item.second);

			int result = end;
			for (int i = end - 1; i >= start; --i)
			if ((pos[s[i]] != -1) && (s[i] <= s[result]))
				result = i;

			return result;
		}
	};
	/*316. Remove Duplicate Letters end */


	/*45. Jump Game II (hard)
	https://leetcode.com/problems/jump-game-ii/
	https://discuss.leetcode.com/topic/3191/o-n-bfs-solution
	*/
	class Solution45 {
	public:
		int jump(vector<int>& nums) {
			if (nums.size() < 2)
				return 0;

			int i = 0, nextmax = 0, step = 0;
			int level = 0, curmax = 0;

			while (curmax - i + 1 > 0) {
				++level;

				for (; i <= curmax; ++i) {
					nextmax = max(nextmax, nums[i] + i);
					if (nextmax >= nums.size() - 1)
						return level;
				}

				curmax = nextmax;
			}

			return 0;
		}
	};
	/*45. Jump Game II end */


	/*330. Patching Array (hard)
	https://leetcode.com/problems/patching-array/
	https://discuss.leetcode.com/topic/35494/solution-explanation
	*/
	class Solution330 {
	public:
		int minPatches(vector<int>& nums, int n) {
			long miss = 1, addnum = 0, i = 0;

			while (miss <= n) {
				if (i < nums.size() && nums[i] <= miss)
					miss += nums[i++];
				else {
					miss += miss;
					addnum++;
				}
			}

			return addnum;
		}
	};
	/*330. Patching Array end */


	/*44. Wildcard Matching (hard)
	https://leetcode.com/problems/wildcard-matching/
	https://discuss.leetcode.com/topic/3040/linear-runtime-and-constant-space-solution
	https://discuss.leetcode.com/topic/17901/accepted-c-dp-solution-with-a-trick
	*/
	class Solution44 {
	public:
		bool isMatch1(string s, string p) {
			int m = s.size();
			int n = p.size();

			vector<bool> vec(m + 1, false);
			if (n > 3000) return false;
			vec[0] = true;
			bool pre;
			for (int j = 1; j <= n; ++j) {
				pre = vec[0];
				vec[0] = vec[0] && (p[j - 1] == '*');

				for (int i = 1; i <= m; ++i) {
					int tmp = vec[i];
					if (p[j - 1] != '*')
						vec[i] = pre && (s[i - 1] == p[j - 1] || p[j - 1] == '?');
					else
						vec[i] = vec[i - 1] || vec[i];

					pre = tmp;
				}
			}

			return vec[m];
		}

		bool isMatch(string& sstr, string &pstr) {
			const char* s = sstr.data();
			const char* p = pstr.data();
			const char* star = NULL;
			const char* ss = s;

			while (*s){
				//advancing both pointers when (both characters match) or ('?' found in pattern)
				//note that *p will not advance beyond its length 
				if ((*p == '?') || (*p == *s)){ s++; p++; continue; }

				// * found in pattern, track index of *, only advancing pattern pointer 
				if (*p == '*'){ star = p++; ss = s; continue; }

				//current characters didn't match, last pattern pointer was *, current pattern pointer is not *
				//only advancing pattern pointer
				if (star){ p = star + 1; s = ++ss; continue; }

				//current pattern pointer is not star, last patter pointer was not *
				//characters do not match
				return false;
			}

			//check for remaining characters in pattern
			while (*p == '*'){ p++; }

			return !*p;
		}
	};
	/*44. Wildcard Matching end */


	/*134. Gas Station (medium)
	https://leetcode.com/problems/gas-station/
	https://discuss.leetcode.com/topic/1344/share-some-of-my-ideas
	*/
	class Solution134 {
	public:
		int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
			int start(0), total(0), tank(0);

			for (int i = 0; i < gas.size(); ++i) {
				tank += gas[i] - cost[i];

				if (tank < 0) {
					start = i + 1;
					total += tank;
					tank = 0;
				}
			}

			return (total + tank < 0 ? -1 : start);
		}
	};
	/*134. Gas Station end */

	/*122. Best Time to Buy and Sell Stock II (medium)
	https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
	https://discuss.leetcode.com/topic/17081/three-lines-in-c-with-explanation
	*/
	class Solution122 {
	public:
		int maxProfit(vector<int> &prices) {
			int nlen = prices.size();
			if (nlen < 2) 
				return 0;

			int max_pro = 0, ntmp;

			for (int i = nlen - 1; i > 0; --i) {
				ntmp = prices[i] - prices[i - 1];

				if (ntmp > 0) 
					max_pro += ntmp;
			}

			return max_pro;
		}
	};
	/*122. Best Time to Buy and Sell Stock II end */


	/*55. Jump Game (medium)
	https://leetcode.com/problems/jump-game/
	https://discuss.leetcode.com/topic/4911/linear-and-simple-solution-in-c/2
	*/
	class Solution55 {
	public:
		bool canJump1(vector<int>& nums) {
			if (nums.empty())
				return false;

			int last = nums.size() - 1;
			for (int i = nums.size() - 2; i >= 0; --i) {
				if (i + nums[i] >= last)
					last = i;
			}

			return last <= 0;
		}

		bool canJump(vector<int>& nums) {
			if (nums.empty())
				return false;

			int i = 0;

			for (int reach = 0; i < nums.size() && i <= reach; ++i)
				reach = max(i + nums[i], reach);

			return i == nums.size();
		}
	};
	/*55. Jump Game end */
}
//////////////////////////Tag Greedy end//////////////////////////////////////////



//////////////////////////Tag Sort//////////////////////////////////////////
namespace SORT {
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};

	/*56. Merge Intervals (hard)
	https://leetcode.com/problems/merge-intervals/
	https://discuss.leetcode.com/topic/4319/a-simple-java-solution
	https://discuss.leetcode.com/topic/20263/c-10-line-solution-easing-understanding
	*/
	class Solution56 {
	public:
		struct Interval {
			int start;
			int end;
			Interval() : start(0), end(0) {}
			Interval(int s, int e) : start(s), end(e) {}
		};

		vector<Interval> merge(vector<Interval>& intervals) {
			vector<Interval> ret;

			if (intervals.size() < 1)
				return ret;
			sort(intervals.begin(), intervals.end(), [](Interval a, Interval b) {return a.start<b.start; });

			ret.push_back(intervals[0]);
			for (int i = 1; i < intervals.size(); ++i) {
				if (intervals[i].start > ret.back().end)
					ret.push_back(intervals[i]);
				else
					ret.back().end = max(ret.back().end, intervals[i].end);
			}

			return ret;
		}
	};
	/*56. Merge Intervals end */


	/*57. Insert Interval (hard)
	https://leetcode.com/problems/insert-interval/
	https://discuss.leetcode.com/topic/7808/short-and-straight-forward-java-solution
	https://discuss.leetcode.com/topic/12899/very-short-and-easy-to-understand-c-solution
	*/
	class Solution57 {
	public:
		struct Interval {
			int start;
			int end;
			Interval() : start(0), end(0) {}
			Interval(int s, int e) : start(s), end(e) {}
		};

		vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
			vector<Interval> ret;
			int i = 0;

			for (; i < intervals.size() && intervals[i].end < newInterval.start; ++i)
				ret.push_back(intervals[i]);

			for (; i < intervals.size() && intervals[i].start <= newInterval.end; ++i) {
				Interval tmp;
				tmp.start = min(newInterval.start, intervals[i].start);
				tmp.end = max(newInterval.end, intervals[i].end);
				newInterval = tmp;
			}

			ret.push_back(newInterval);

			for (; i < intervals.size(); ++i)
				ret.push_back(intervals[i]);

			return ret;
		}
	};
	/*57. Insert Interval end */


	/*164. Maximum Gap (hard)
	https://leetcode.com/problems/maximum-gap/
	https://discuss.leetcode.com/topic/5999/bucket-sort-java-solution-with-explanation-o-n-time-and-space/12
	https://discuss.leetcode.com/topic/9986/my-c-code-12-ms-bucket-sort-o-n-time-and-space
	*/
	class Solution164 {
	public:
		int maximumGap(vector<int>& num) {
			int len = num.size();
			if (len < 2)
				return 0;

			int minnum = num[0];
			int maxnum = num[0];

			for (int item : num) {
				minnum = min(minnum, item);
				maxnum = max(maxnum, item);
			}

			int buck_len = (maxnum - minnum) / len + 1;
			vector<vector<int>> buckets((maxnum - minnum) / buck_len + 1);

			for (int item : num) {
				int i = (item - minnum) / buck_len;

				if (buckets[i].empty()) {
					buckets[i].push_back(item);
					buckets[i].push_back(item);
				}
				else {
					if (item < buckets[i][0])
						buckets[i][0] = item;

					if (item > buckets[i][1])
						buckets[i][1] = item;
				}
			}

			int gap = 0;
			int pre = 0;

			for (int i = 1; i < buckets.size(); ++i) {
				if (buckets[i].empty())
					continue;

				gap = max(gap, buckets[i][0] - buckets[pre][1]);
				pre = i;
			}

			return gap;
		}

		static void main() {
			Solution164* test = new Solution164;
			vector<int> num1 = { 1, 3, 4, 4};
			int result;

			result = test->maximumGap(num1);
			delete test;
		}
	};
	/*164. Maximum Gap end */


	/*274. H-Index (medium)
	https://leetcode.com/problems/h-index/
	https://discuss.leetcode.com/topic/23307/my-o-n-time-solution-use-java
	https://discuss.leetcode.com/topic/23310/my-easy-solution
	*/
	class Solution274 {
	public:
		void quick_sort_recursive(vector<int>& citations, int low, int high) {
			if (low >= high)
				return;

			int mid = citations[high];
			int left = low;
			int right = high - 1;

			while (left < right) {
				while (mid > citations[left] && left < right)
					++left;

				while (mid <= citations[right] && left < right)
					--right;

				swap(citations[left], citations[right]);
			}

			if (citations[left] >= citations[high])
				std::swap(citations[left], citations[high]);
			else
				left++;

			quick_sort_recursive(citations, low, left - 1);
			quick_sort_recursive(citations, left + 1, high);
		}

		int hIndex2(vector<int>& citations) {
			if (citations.empty())
				return 0;

			int len = citations.size();
			quick_sort_recursive(citations, 0, len - 1);

			int result = 0;
			for (int i = 0; i < len; ++i) {
				if (len - i > citations[i])
					result = max(result, citations[i]);
				else
					result = max(result, len - i);
			}

			return result;
		}

		int hIndex(vector<int>& citations) {
			if (citations.empty())
				return 0;

			int len = citations.size();
			int *counter = new int[len + 1];

			memset(counter, 0x00, (len + 1) * sizeof(int));

			for (int i = 0; i < len; ++i){
				if (citations[i] >= len)
					counter[len] ++;
				else
					counter[citations[i]] ++;
			}

			if (counter[len] >= len)
				return len;

			for (int i = len - 1; i >= 0; --i){
				counter[i] = counter[i] + counter[i + 1];

				if (counter[i] >= i)
					return i;
			}

			return 0;
		}

		int hIndex3(vector<int>& citations) {
			int left = 0, len = citations.size(), right = len - 1, mid;

			while (left <= right){
				mid = (left + right) >> 1;
				if (citations[mid] == (len - mid)) return citations[mid];
				else if (citations[mid] > (len - mid)) right = mid - 1;
				else left = mid + 1;
			}

			return len - (right + 1);
		}
	};
	/*274. H-Index end */


	/*324. Wiggle Sort II (medium)
	https://leetcode.com/problems/wiggle-sort-ii/
	https://discuss.leetcode.com/topic/32929/o-n-o-1-after-median-virtual-indexing/2
	https://discuss.leetcode.com/topic/32920/o-n-time-o-1-space-solution-with-detail-explanations
	*/
	class Solution324 {
	public:
		void wiggleSort(vector<int>& nums) {
			int len = nums.size();
			auto midptr = nums.begin() + len / 2;

			nth_element(nums.begin(), midptr, nums.end());
			int mid = *midptr;

			//(n | 1) calculates the nearest odd that is not less than n
			#define A(i) nums[(1+2*i) % (len | 1)]
			int i = 0, j = 0, k = len - 1;

			while (j <= k) {
				if (A(j) > mid)
					swap(A(j++), A(i++));
				else if (A(j) < mid)
					swap(A(j), A(k--));
				else
					++j;
			}
		}
	};
	/*324. Wiggle Sort II end */


	/*148. Sort List (medium)
	https://leetcode.com/problems/sort-list/
	https://discuss.leetcode.com/topic/643/i-have-a-pretty-good-mergesort-method-can-anyone-speed-up-the-run-time-or-reduce-the-memory-usage
	*/
	class Solution148 {
	public:
		ListNode* sortList(ListNode* head) {
			if (NULL == head || NULL ==  head->next)
				return head;

			ListNode* slow = head;
			ListNode* fast = head;
			ListNode* pre = NULL;

			while (NULL != fast && NULL != fast->next) {
				pre = slow;
				slow = slow->next;
				fast = fast->next->next;
			}

			pre->next = NULL;
			ListNode* list1 = sortList(head);
			ListNode* list2 = sortList(slow);

			return merge(list1, list2);
		}


		ListNode* merge(ListNode* list1, ListNode* list2) {
			ListNode root(0);
			ListNode* tmp = &root;

			while (NULL != list1 && NULL != list2) {
				if (list1->val < list2->val) {
					tmp->next = list1;
					list1 = list1->next;
				}
				else {
					tmp->next = list2;
					list2 = list2->next;
				}

				tmp = tmp->next;
			}

			if (NULL != list1)
				tmp->next = list1;

			if (NULL != list2)
				tmp->next = list2;

			return root.next;
		}
	};
	/*148. Sort List end */


	/*147. Insertion Sort List (medium)
	https://leetcode.com/problems/insertion-sort-list/
	https://discuss.leetcode.com/topic/14916/explained-c-solution-24ms
	*/
	class Solution147 {
	public:
		ListNode* insertionSortList(ListNode* head) {
			if (NULL == head)
				return head;

			ListNode tmp(0);
			ListNode* pre = &tmp;
			ListNode* cur = head;
			ListNode* next = NULL;

			while (NULL != cur) {
				next = cur->next;

				while (NULL !=  pre->next && pre->next->val < cur->val)
					pre = pre->next;

				cur->next = pre->next;
				pre->next = cur;
				cur = next;
				pre = &tmp;
			}

			return tmp.next;
		}
	};
	/*147. Insertion Sort List end */


	/*75. Sort Colors (medium)
	https://leetcode.com/problems/sort-colors/
	https://discuss.leetcode.com/topic/6968/four-different-solutions
	*/
	class Solution75 {
	public:
		void sortColors(vector<int>& nums) {
			int red = 0;
			int white = 0;
			int blue = nums.size() - 1;
			int tmp;

			while (white <= blue) {
				if (0 == nums[white]) {
					swap(nums[red], nums[white]);
					++red;
					++white;
				}
				else if (2 == nums[white]) {
					swap(nums[blue], nums[white]);
					--blue;
				}
				else
					++white;
			}
		}
	};
	/*75. Sort Colors end */


	/*179. Largest Number (medium)
	https://leetcode.com/problems/largest-number/
	https://discuss.leetcode.com/topic/8018/my-java-solution-to-share/2
	*/
	class Solution179 {
	public:
		string largestNumber(vector<int>& nums) {
			vector<string> vec;

			for (auto item : nums)
				vec.push_back(to_string(item));

			sort(vec.begin(), vec.end(), [](string& str1, string& str2){return str1 + str2 > str2 + str1; });
			string result;

			if (vec[0] == string("0"))
				return string("0");

			for (auto item : vec)
				result += item;
			return result;
		}
	};
	/*179. Largest Number end */


	/*350. Intersection of Two Arrays II (easy)
	https://leetcode.com/problems/intersection-of-two-arrays-ii/
	https://discuss.leetcode.com/topic/45893/c-hash-table-solution-and-sort-two-pointers-solution-with-time-and-space-complexity
	*/
	class Solution350 {
	public:
		vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
			vector<int> result;
			unordered_map<int, int> dict;

			for (int i = 0; i < nums1.size(); ++i)
				dict[nums1[i]] ++;

			for (int i = 0; i < nums2.size(); ++i) {
				if (dict.find(nums2[i]) != dict.end() && --dict[nums2[i]] >= 0)
					result.push_back(nums2[i]);

			}

			return result;
		}
	};
	/*350. Intersection of Two Arrays II end */


	/*349. Intersection of Two Arrays (easy)
	https://leetcode.com/problems/intersection-of-two-arrays/
	https://discuss.leetcode.com/topic/45693/8ms-concise-c-using-unordered_set
	*/
	class Solution349 {
	public:
		vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
			sort(nums1.begin(), nums1.end());
			sort(nums2.begin(), nums2.end());

			vector<int> result;
			int m = 0;
			int n = 0;

			while (m < nums1.size() && n < nums2.size()) {
				if (nums1[m] == nums2[n]) {
					int len = result.size();

					if (len == 0 || result[len - 1] != nums1[m])
						result.push_back(nums1[m]);

					++m;
					++n;
				}
				else if (nums1[m] > nums2[n])
					++n;
				else
					++m;
			}

			return result;
		}
	};
	/*349. Intersection of Two Arrays end */


	/*242. Valid Anagram (easy)
	https://leetcode.com/problems/valid-anagram/
	https://discuss.leetcode.com/topic/20303/2-c-solutions-with-explanations
	*/
	class Solution242 {
	public:
		bool isAnagram(string s, string t) {
			std::sort(s.begin(), s.end());
			std::sort(t.begin(), t.end());

			return s == t;
		}
	};
	/*242. Valid Anagram end */
}
//////////////////////////Tag Sort end//////////////////////////////////////////


//////////////////////////Tag Bit Manipulation//////////////////////////////////////////
namespace BIT {	
	/*201. Bitwise AND of Numbers Range (medium)
	https://leetcode.com/problems/bitwise-and-of-numbers-range/
	https://discuss.leetcode.com/topic/12133/bit-operation-solution-java
	*/
	class Solution201 {
	public:
		int rangeBitwiseAnd(int m, int n) {
			int result = 1;

			if (m == 0)
				return 0;

			while (m != n) {
				m >>= 1;
				n >>= 1;
				result <<= 1;
			}

			return m*result;
		}
	};
	/*201. Bitwise AND of Numbers Range end */


	/*78. Subsets (medium)
	https://leetcode.com/problems/subsets/
	https://discuss.leetcode.com/topic/19110/c-recursive-iterative-bit-manipulation-solutions-with-explanations
	*/
	class Solution78 {
	public:
		vector<vector<int>> subsets(vector<int>& nums) {
			vector<vector<int>> result;

			sort(nums.begin(), nums.end());
			result.push_back(vector<int>());

			for (int i = 0; i < nums.size(); ++i) {
				int cursize = result.size();

				for (int j = 0; j < cursize; ++j) {
					result.push_back(result[j]);
					result.back().push_back(nums[i]);
				}
			}
			
			return result;
		}

		vector<vector<int>> result;
	};
	/*78. Subsets end */


	/*338. Counting Bits (medium)
	https://leetcode.com/problems/counting-bits/
	https://discuss.leetcode.com/topic/40262/four-lines-c-time-o-n-space-o-n
	*/
	class Solution338 {
	public:
		int countbit(int num) {
			int ret = 0;

			for (int i = 0; i < 8 * sizeof(int); ++i) {
				if ((1 << i) & num)
					++ret;
			}

			return ret;
		}

		vector<int> countBits1(int num) {
			vector<int> ret(num+1, 0);

			for (int i = 1; i <= num; ++i) 
				ret[i] = ret[i >> 1] + (i & 1);

			return ret;
		}

		vector<int> countBits(int num) {
			vector<int> ret;

			for (int i = 0; i <= num; ++i)
				ret.push_back(countbit(i));

			return ret;
		}
	};
	/*338. Counting Bits end */


	/*318. Maximum Product of Word Lengths (medium)
	https://leetcode.com/problems/maximum-product-of-word-lengths/
	https://discuss.leetcode.com/topic/31766/bit-shorter-c
	*/
	class Solution318 {
	public:
		int maxProduct(vector<string>& words) {
			unordered_map<int, int> maxlen;
			int result = 0;

			for (string word : words) {
				int mask = 0;

				for (char c : word)
					mask |= 1 << (c - 'a');

				maxlen[mask] = max(maxlen[mask], (int)word.size());

				for (auto maskAndlen : maxlen){
					if (!(mask & maskAndlen.first))
						result = max(result, (int)word.size()*maskAndlen.second);
				}
			}

			return result;
		}

		static void main() {
			Solution318* test = new Solution318;
			int result;

			vector<string> words1 = { "abcw", "baz", "foo", "bar", "xtfn", "abcdef" };

			result = test->maxProduct(words1);
			delete test;
		}
	};
	/*318. Maximum Product of Word Lengths end */


	/*268. Missing Number (medium)
	https://leetcode.com/problems/missing-number/
	https://discuss.leetcode.com/topic/22313/c-solution-using-bit-manipulation
	*/
	class Solution268 {
	public:
		int missingNumber(vector<int>& nums) {
			int len, result = 0;
			len = nums.size();

			for (int i = 0; i < len; ++i)
				result += nums[i] - i;

			result = len - result;
			return result;
		}
	};
	/*268. Missing Number end */


	/*260. Single Number III (medium)
	https://leetcode.com/problems/single-number-iii/
	https://discuss.leetcode.com/topic/21605/accepted-c-java-o-n-time-o-1-space-easy-solution-with-detail-explanations
	*/
	class Solution260 {
	public:
		vector<int> singleNumber(vector<int>& nums) {
			vector<int> result = { 0, 0 };
			int diff = 0;

			diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
			diff &= -diff;

			for (int i = 0; i < nums.size(); ++i) {
				if (diff & nums[i])
					result[0] ^= nums[i];
				else
					result[1] ^= nums[i];
			}

			return result;
		}
	};
	/*260. Single Number III end */


	/*137. Single Number II (medium)
	https://leetcode.com/problems/single-number-ii/
	https://discuss.leetcode.com/topic/2031/challenge-me-thx/2
	*/
	class Solution137 {
	public:
		int singleNumber(vector<int>& A) {
			int ones = 0, twos = 0;

			for (int i = 0; i < A.size(); ++i){
				ones = ones ^ A[i] & ~twos;
				twos = twos ^ A[i] & ~ones;
			}

			return ones;
		}

		static void main() {
			Solution137* test = new Solution137;
			vector<int> A1 = { 1, 2, 1, 1 };

			test->singleNumber(A1);
			delete test;
		}
		
	};
	/*137. Single Number II end */


	/*136. Single Number (medium)
	https://leetcode.com/problems/single-number/
	https://discuss.leetcode.com/topic/1916/my-o-n-solution-using-xor
	*/
	class Solution136 {
	public:
		int singleNumber(int A[], int n) {
			for (int i = 1; i < n; ++i)
				A[0] ^= A[i];

			return A[0];
		}
	};
	/*136. Single Number end */


	/*187. Repeated DNA Sequences (medium)
	https://leetcode.com/problems/repeated-dna-sequences/
	https://discuss.leetcode.com/topic/8487/i-did-it-in-10-lines-of-c
	*/
	class Solution187 {
	public:
		vector<string> findRepeatedDnaSequences(string s) {
			vector<string> ret;
			unordered_map<int, int> m;

			for (int i = 0, t = 0; i < s.size(); ++i) {
				if (m[t = t << 3 & 0x3FFFFFFF | s[i] & 7]++ == 1)
					ret.push_back(s.substr(i - 9, 10));
			}

			return ret;
		}

		static void main() {
			Solution187* test = new Solution187;

			vector<string> result;
			string str1("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
			result = test->findRepeatedDnaSequences(str1);
			delete test;
		}
	};
	/*187. Repeated DNA Sequences end */


	/*190. Reverse Bits (easy)
	https://leetcode.com/problems/reverse-bits/
	*/
	class Solution190 {
	public:
		unsigned int reverseBits(unsigned int n) {
			int len = sizeof(unsigned int)* 8;
			unsigned int result = 0;
			for (int i = 0; i < len; ++i) {
				if ((1 << i) & n)
					result = result | (1 << (len - i - 1));
			}

			return result;
		}
	};
	/*190. Reverse Bits end */


	/*191. Number of 1 Bits (easy)
	https://leetcode.com/problems/number-of-1-bits/
	https://discuss.leetcode.com/topic/9915/short-code-of-c-o-m-by-time-m-is-the-count-of-1-s-and-another-several-method-of-o-1-time
	*/
	class Solution191 {
	public:
		int hammingWeight(unsigned int n) {
			int result = 0;

			int base;
			for (int nIdx = 0; nIdx<32; ++nIdx) {
				base = 1 << nIdx;

				if (base&n)
					result++;
			}

			return result;
		}
	};
	/*191. Number of 1 Bits end */


	/*169. Majority Element (easy)
	https://leetcode.com/problems/majority-element/
	https://discuss.leetcode.com/topic/17446/6-suggested-solutions-in-c-with-explanations
	*/
	class Solution169 {
	public:
		int majorityElement(vector<int> &num) {
			int maj;
			int count = 0;
			int n = int(num.size());

			for (int i = 0; i < n; i++) {
				if (0 == count) {
					maj = num[i];
					++count;
				}
				else if (maj == num[i]) {
					++count;
					if (count > n / 2)
						return maj;
				}
				else
					--count;
			}

			return maj;
		}
	};
	/*169. Majority Element end */


	/*342. Power of Four (easy)
	https://leetcode.com/problems/power-of-four/
	https://discuss.leetcode.com/topic/42914/1-line-c-solution-without-confusing-bit-manipulations/5
	*/
	class Solution342 {
	public:
		bool isPowerOfFour(int num) {
			return num > 0 && (num & (num - 1)) == 0 && (num - 1) % 3 == 0;
		}

		bool isPowerOfFour2(int num) {
			if (0 == num || INT_MIN == num)
				return false;

			if (num < 0)
				num = -num;

			return((num % 4) == 0);
		}
	};
	/* 342. Power of Four end * /


	/*231. Power of Two (easy)
	https://leetcode.com/problems/power-of-two/
	https://discuss.leetcode.com/topic/17857/using-n-n-1-trick/3
	*/
	class Solution231 {
	public:
		bool isPowerOfTwo(int n) {
			if (n <= 0) 
				return false;

			return !(n&(n - 1));
		}

		bool isPowerOfTwo1(int n) {
			while ((n & 1) == 0 && n > 0)
				n = n >> 1;

			return n == 1;
		}
	};
	/*231. Power of Two end */
}

//////////////////////////Tag Bit Manipulation end//////////////////////////////////////////
namespace TREE {
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	void delNode(TreeNode* root) {
		if (NULL != root) {
			delNode(root->left);
			delNode(root->right);
			delete root;
		}
	}

	/*145. Binary Tree Postorder Traversal (hard)
	https://leetcode.com/problems/binary-tree-postorder-traversal/
	https://discuss.leetcode.com/topic/2919/my-accepted-code-with-explaination-does-anyone-have-a-better-idea
	*/
	class Solution145 {
	public:
		vector<int> postorderTraversal(TreeNode* root) {
			vector<int> result;

			if (NULL == root)
				return result;

			stack<TreeNode* > nodeStack;
			TreeNode* curr = root;
			TreeNode* pre = NULL;

			while (!nodeStack.empty() || curr) {
				while (curr) {
					nodeStack.push(curr);
					curr = curr->left;
				}

				if (nodeStack.top()->right && (pre != nodeStack.top()->right))
					curr = nodeStack.top()->right;
				else {
					result.push_back(nodeStack.top()->val);
					pre = nodeStack.top();
					nodeStack.pop();
				}
			}

			return result;
		}
	};
	/*145. Binary Tree Postorder Traversal end */


	/*95. Unique Binary Search Trees II (medium)
	https://leetcode.com/problems/unique-binary-search-trees-ii/
	https://discuss.leetcode.com/topic/3079/a-simple-recursive-solution
	*/
	class Solution95 {
	public:
		vector<TreeNode*> genTree(int start, int end) {
			vector<TreeNode*> result;

			if (start > end) {
				result.push_back(NULL);
				return result;
			}

			if (start == end) {
				result.push_back(new TreeNode(end));
				return result;
			}

			vector<TreeNode*> left;
			vector<TreeNode*> right;

			for (int i = start; i <= end; ++i) {
				left = genTree(start, i - 1);
				right = genTree(i + 1, end);

				for (auto litem : left)
				for (auto ritem : right) {
					TreeNode* root = new TreeNode(i);
					root->left = litem;
					root->right = ritem;
					result.push_back(root);
				}
			}

			return result;
		}

		vector<TreeNode*> generateTrees(int n) {
			vector<TreeNode*> result;

			if (n < 1)
				return result;

			result = genTree(1, n);
			return result;
		}
	};
	/*95. Unique Binary Search Trees II end */


	/*96. Unique Binary Search Trees (medium)
	https://leetcode.com/problems/unique-binary-search-trees/
	https://discuss.leetcode.com/topic/8398/dp-solution-in-6-lines-with-explanation-f-i-n-g-i-1-g-n-i
	*/
	class Solution96 {
	public:
		int numTrees(int n) {
			vector<int> a(n + 1, 0);

			a[0] = 1;
			for (int i = 1; i <= n; ++i)
			for (int j = 0; j < i; ++j) {
				a[i] += a[j] * a[i - j - 1];
			}

			return a[n];
		}
	};
	/*96. Unique Binary Search Trees end */


	/*236. Lowest Common Ancestor of a Binary Tree (medium)
	https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
	https://discuss.leetcode.com/topic/18561/4-lines-c-java-python-ruby
	*/
	class Solution236 {
	public:
		void listparent(vector<TreeNode*>&path) {
			stack<TreeNode*> result;
			int num = path.size();
			TreeNode* node = path[num - 1];

			result.push(node);
			num--;
			for (int i = num - 1; i >= 0; --i) {
				TreeNode* tmp = result.top();
				if (path[i]->left && path[i]->left == tmp)
					result.push(path[i]);
				else if (path[i]->right && path[i]->right == tmp)
					result.push(path[i]);
			}

			path.resize(result.size());
			int i = 0;
			while (!result.empty()) {
				path[i++] = result.top();
				result.pop();
			}
		}

		TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
			if (root == NULL || p == root || q == root)
				return root;

			TreeNode* left = lowestCommonAncestor1(root->left, p, q);
			TreeNode* right = lowestCommonAncestor1(root->right, p, q);

			return left != NULL ? right ? root : left : right;
		}

		TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
			if (!root || root == p || root == q)
				return root;

			vector<TreeNode*>pathp, pathq, pathtmp;
			stack<TreeNode*> nodes;
			nodes.push(root);

			while (1) {
				TreeNode* tmp = nodes.top();
				nodes.pop();
				pathtmp.push_back(tmp);

				if (p == tmp)
					pathp = pathtmp;

				if (q == tmp)
					pathq = pathtmp;

				if (pathp.size() && pathq.size())
					break;

				if (tmp->right)
					nodes.push(tmp->right);

				if (tmp->left)
					nodes.push(tmp->left);
			}

			//bottom up the path of node
			listparent(pathp);
			listparent(pathq);
			int n = min(pathp.size(), pathq.size());

			for (int i = 1; i < n; ++i) {
				if (pathp[i] != pathq[i])
					return pathp[i - 1];
			}

			return pathp[n - 1];
		}

		static void main() {
			Solution236* test = new Solution236;
			TreeNode* result;

			TreeNode *node1 = new TreeNode(1);
			TreeNode *node2 = new TreeNode(2);
			TreeNode *node3 = new TreeNode(3);
			TreeNode *node4 = new TreeNode(4);
			TreeNode *node5 = new TreeNode(5);
			node1->left = node2;
			node1->right = node3;
			node2->right = node4;
			node3->left = node5;

			result = test->lowestCommonAncestor(node1, node2, node3);
			delNode(node1);
			delete test;
		}
	};
	/*236. Lowest Common Ancestor of a Binary Tree end */


	/*230. Kth Smallest Element in a BST (medium)
	https://leetcode.com/problems/kth-smallest-element-in-a-bst/
	https://discuss.leetcode.com/topic/17810/3-ways-implemented-in-java-binary-search-in-order-iterative-recursive
	*/
	class Solution230 {
	public:
		int kthSmallest(TreeNode* root, int k) {
			stack<TreeNode*> order;
			TreeNode* tmp;
			order.push(root);

			while (!order.empty()) {
				tmp = order.top();
				while (tmp) {
					order.push(tmp->left);
					tmp = tmp->left;
				}

				order.pop();
				tmp = order.top();
				order.pop();
				--k;

				if (0 == k)
					return tmp->val;

				order.push(tmp->right);
			}

			return 0;
		}
	};
	/*230. Kth Smallest Element in a BST end */


	/*222. Count Complete Tree Nodes (medium)
	https://leetcode.com/problems/count-complete-tree-nodes/
	https://discuss.leetcode.com/topic/15533/concise-java-solutions-o-log-n-2
	*/
	class Solution222 {
	public:
		int countNodes(TreeNode* root) {
			if (NULL == root)
				return 0;

			int left = 0, right = 0;
			TreeNode* lnode = root;
			TreeNode* rnode = root;

			while (lnode) {
				++left;
				lnode = lnode->left;
			}

			while (rnode) {
				++right;
				rnode = rnode->right;
			}

			if (left == right)
				return pow(2, left) - 1;

			return 1 + countNodes(root->left) + countNodes(root->right);
		}
	};
	/*222. Count Complete Tree Nodes end */


	/*144. Binary Tree Preorder Traversal (medium)
	https://leetcode.com/problems/binary-tree-preorder-traversal/
	https://discuss.leetcode.com/topic/6493/accepted-iterative-solution-in-java-using-stack
	*/
	class Solution144 {
	public:
		vector<int> preorderTraversal(TreeNode *root) {
			vector<int> result;
			stack <TreeNode*> pool;

			if (NULL == root)
				return result;

			pool.push(root);
			while (!pool.empty()) {
				TreeNode* tmp = pool.top();

				pool.pop();
				result.push_back(tmp->val);

				if (tmp->right)
					pool.push(tmp->right);

				if (tmp->left)
					pool.push(tmp->left);
			}

			return result;
		}
	};
	/*144. Binary Tree Preorder Traversal end */


	/*103. Binary Tree Zigzag Level Order Traversal (medium)
	https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
	https://discuss.leetcode.com/topic/3413/my-accepted-java-solution
	*/
	class Solution103 {
	public:
		vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
			vector<vector<int>> result;
			if (NULL == root)
				return result;

			queue<TreeNode*> nodes;
			nodes.push(root);
			TreeNode* tmp;
			bool fromleft = true;

			while (!nodes.empty()) {
				vector<int> curline(nodes.size());
				int nums = nodes.size();
				for (int i = 0; i < nums; ++i) {
					tmp = nodes.front();
					nodes.pop();

					int index = fromleft ? i : nums - 1 - i;
					curline[index] = tmp->val;

					if (tmp->left)
						nodes.push(tmp->left);

					if (tmp->right)
						nodes.push(tmp->right);
				}

				fromleft = !fromleft;

				if (curline.size())
					result.push_back(curline);
			}

			return result;
		}
	};
	/*103. Binary Tree Zigzag Level Order Traversal end */


	/*94. Binary Tree Inorder Traversal (medium)
	https://leetcode.com/problems/binary-tree-inorder-traversal/
	https://discuss.leetcode.com/topic/6478/iterative-solution-in-java-simple-and-readable
	*/
	class Solution94 {
	public:
		vector<int> inorderTraversal(TreeNode *root) {
			vector<int> result;
			stack<TreeNode*> test;
			TreeNode* tmp;

			if (NULL == root)
				return result;

			test.push(root);
			while (!test.empty()) {
				tmp = test.top();
				while (NULL != tmp) {
					test.push(tmp->left);
					tmp = tmp->left;
				}

				test.pop();
				tmp = test.top();
				test.pop();
				result.push_back(tmp->val);

				if (NULL != tmp->right)
					test.push(tmp->right);
			}
			/* the following will chang the tree node, will may cause memory leak
			while (!test.empty()) {
				tmp = test.top();
				if (tmp->left) {
					test.push(tmp->left);
					tmp->left = NULL;
				}
				else {
					test.pop();
					result.push_back(tmp->val);
					if (tmp->right)
						test.push(tmp->right);
				}
			}
			*/
			return result;
		}

		static void main() {
			Solution94* test = new Solution94;
			vector<int> result;

			TreeNode *node1 = new TreeNode(1);
			TreeNode *node2 = new TreeNode(2);
			TreeNode *node3 = new TreeNode(3);
			TreeNode *node4 = new TreeNode(4);
			TreeNode *node5 = new TreeNode(5);
			node1->left = node2;
			node1->right = node3;
			node2->right = node4;
			node3->left = node5;

			result = test->inorderTraversal(node1);
			delNode(node1);
			delete test;
		}
	};
	/*94. Binary Tree Inorder Traversal end */


	/*226. Invert Binary Tree (easy)
	https://leetcode.com/problems/invert-binary-tree/
	https://discuss.leetcode.com/topic/16039/straightforward-dfs-recursive-iterative-bfs-solutions
	*/
	class Solution226 {
	public:
		TreeNode* invertTree(TreeNode* root) {
			if (root == NULL)
				return NULL;

			TreeNode* pTmpNode = root->left;
			root->left = root->right;
			root->right = pTmpNode;

			invertTree(root->left);

			invertTree(root->right);

			return root;
		}
	};
	/*226. Invert Binary Tree end */


	/*235. Lowest Common Ancestor of a Binary Search Tree (easy)
	https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
	https://discuss.leetcode.com/topic/18387/3-lines-with-o-1-space-1-liners-alternatives
	*/
	class Solution235 {
	public:
		TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
			TreeNode* result = root;

			while (result) {
				if ((result->val > p->val) && (result->val > q->val))
					result = result->left;
				else if ((result->val < p->val) && (result->val < q->val))
					result = result->right;
				else
					break;
			}

			return result;
		}
	};
	/*235. Lowest Common Ancestor of a Binary Search Tree end */
}
//////////////////////////Tag Tree end//////////////////////////////////////////


//////////////////////////Tag Depth-first Search//////////////////////////////////////////
namespace DFS {
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};

	struct TreeLinkNode {
		int val;
		TreeLinkNode *left, *right, *next;
		TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
	};

	void delNode(TreeNode* root) {
		if (NULL != root) {
			delNode(root->left);
			delNode(root->right);
			delete root;
		}
	}

	void delList(ListNode* root) {
		if (NULL != root) {
			if (NULL != root->next)
				delList(root->next);

			delete root;
		}
	}


	/*124. Binary Tree Maximum Path Sum (hard)
	https://leetcode.com/problems/binary-tree-maximum-path-sum/
	https://discuss.leetcode.com/topic/4407/accepted-short-solution-in-java
	*/
	class Solution124 {
	public:
		int m_maxvalue;

		int pathDown(TreeNode* root){
			if (NULL == root)
				return 0;

			int left = max(0, pathDown(root->left));
			int right = max(0, pathDown(root->right));

			m_maxvalue = max(m_maxvalue, left + right + root->val);

			return max(left, right) + root->val;
		}

		int maxPathSum(TreeNode* root) {
			m_maxvalue = INT_MIN;
			pathDown(root);

			return m_maxvalue;
		}
	};
	/*124. Binary Tree Maximum Path Sum end */

	/*99. Recover Binary Search Tree (hard)
	https://leetcode.com/problems/recover-binary-search-tree/
	https://discuss.leetcode.com/topic/3988/no-fancy-algorithm-just-simple-and-powerful-in-order-traversal
	*/
	class Solution99 {
	public:
		void recoverTree(TreeNode* root) {
			vector<TreeNode*> nodes;
			stack<TreeNode*> pre;
			bool bdone = false;
			TreeNode* curr = root;

			while (!bdone){
				if (curr){
					pre.push(curr);
					curr = curr->left;
				}
				else{
					if (pre.empty())
						bdone = true;
					else{
						curr = pre.top();
						pre.pop();

						nodes.push_back(curr);
						curr = curr->right;
					}
				}
			}

			int i, j;
			int len = nodes.size();
			for (i = 0; i < len - 1; ++i)
			if (nodes[i]->val >= nodes[i + 1]->val)
				break;

			for (j = len - 1; j > 0; --j)
			if (nodes[j]->val <= nodes[j - 1]->val)
				break;

			int val = nodes[i]->val;
			nodes[i]->val = nodes[j]->val;
			nodes[j]->val = val;
		}
	};
	/*99. Recover Binary Search Tree end */


	/*117. Populating Next Right Pointers in Each Node II (hard)
	https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
	https://discuss.leetcode.com/topic/1106/o-1-space-o-n-complexity-iterative-solution
	*/
	class Solution117 {
	public:
		void connect(TreeLinkNode *root) {
			TreeLinkNode *curr = root;

			if (NULL == curr)
				return;

			TreeLinkNode *levelhead = root->left != NULL ? root->left : root->right;
			TreeLinkNode *nextnode = NULL;

			while (levelhead != NULL){
				nextnode = curr->next;
				while (nextnode && NULL == nextnode->left && NULL == nextnode->right)
					nextnode = nextnode->next;

				if (curr->left && curr->right)
					curr->left->next = curr->right;
				else if (curr->left){
					if (nextnode && nextnode->left)
						curr->left->next = nextnode->left;
					else if (nextnode && nextnode->right)
						curr->left->next = nextnode->right;
				}

				if (curr->right){
					if (nextnode && nextnode->left)
						curr->right->next = nextnode->left;
					else if (nextnode && nextnode->right)
						curr->right->next = nextnode->right;
				}

				if (nextnode){
					curr = nextnode;
					continue;
				}

				curr = levelhead;

				while (levelhead && levelhead->left == NULL && levelhead->right == NULL)
					levelhead = levelhead->next;

				if (levelhead && levelhead->left)
					levelhead = levelhead->left;
				else if (levelhead && levelhead->right)
					levelhead = levelhead->right;
				else
					levelhead = NULL;
			}
		}
	};
	/*117. Populating Next Right Pointers in Each Node II end */


	/*337. House Robber III (medium)
	https://leetcode.com/problems/house-robber-iii/
	https://discuss.leetcode.com/topic/39834/step-by-step-tackling-of-the-problem
	*/
	class Solution337 {
	public:
		vector<int> dfs(TreeNode* root){
			vector<int> ret(2, 0);

			if (root == NULL)
				return ret;

			vector<int> left = dfs(root->left);
			vector<int> right = dfs(root->right);

			ret[0] = left[1] + right[1] + root->val;
			ret[1] = max(left[0], left[1]) + max(right[0], right[1]);
		}

		int rob(TreeNode* root) {
			vector<int> ret(2, 0);

			ret = dfs(root);

			return max(ret[0], ret[1]);
		}
	};
	/*337. House Robber III end */


	/*105. Construct Binary Tree from Preorder and Inorder Traversal (medium)
	https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
	https://discuss.leetcode.com/topic/3695/my-accepted-java-solution
	*/
	class Solution105 {
	public:
		TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
			if (preorder.empty() || preorder.size() != inorder.size())
				return NULL;

			int i = 0, j = 0;
			TreeNode* root = new TreeNode(0x80000000);
			stack<TreeNode*> nodes;
			nodes.push(root);
			TreeNode *pp = NULL, *ptr = root;

			while (j < inorder.size()){
				if (nodes.top()->val == inorder[j]){
					pp = nodes.top();
					nodes.pop();
					j++;
				}
				else if (pp){
					ptr = new TreeNode(preorder[i]);
					pp->right = ptr;
					pp = NULL;
					nodes.push(ptr);
					++i;
				}
				else{
					ptr = new TreeNode(preorder[i]);
					nodes.top()->left = ptr;
					nodes.push(ptr);
					++i;
				}
			}

			TreeNode* result = root->left;
			delete root;

			return result;
		}

		static void main() {
			Solution105* test = new Solution105;
			TreeNode* node1 = new TreeNode(1);
			TreeNode* node2 = new TreeNode(2);
			TreeNode* node3 = new TreeNode(3);
			TreeNode* node4 = new TreeNode(4);
			TreeNode* node5 = new TreeNode(5);
			TreeNode* result;

			node1->left = node2;
			node1->right = node3;
			node2->right = node4;
			node3->left = node5;

			vector<int> preorder1 = {1, 2, 4, 3, 5};
			vector<int> inorder1 = {2, 4, 1, 5, 3};
			result = test->buildTree(preorder1, inorder1);
			delNode(result);
			delete test;
		}
	};
	/*105. Construct Binary Tree from Preorder and Inorder Traversal end */


	/*129. Sum Root to Leaf Numbers end (medium)
	https://leetcode.com/problems/sum-root-to-leaf-numbers/
	https://leetcode.com/discuss/20451/short-java-solution-recursion
	*/
	class Solution129 {
	public:
		int sumNumbers(TreeNode* root) {
			if (NULL == root)
				return 0;

			int result = 0;
			stack<int> nums;
			stack<TreeNode*> nodes;
			nodes.push(root);
			nums.push(root->val);
			TreeNode* nodetmp = NULL;
			int valtmp;

			while (!nodes.empty()){
				nodetmp = nodes.top();
				nodes.pop();

				valtmp = nums.top();
				nums.pop();

				if (NULL == nodetmp->left && NULL == nodetmp->right)
					result += valtmp;

				if (NULL != nodetmp->left){
					nodes.push(nodetmp->left);
					nums.push(valtmp * 10 + nodetmp->left->val);
				}

				if (NULL != nodetmp->right){
					nodes.push(nodetmp->right);
					nums.push(valtmp * 10 + nodetmp->right->val);
				}
			}

			return result;
		}
	};
	/*129. Sum Root to Leaf Numbers end*/


	/*116. Populating Next Right Pointers in Each Node (medium)
	https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
	https://leetcode.com/discuss/7327/a-simple-accepted-solution
	*/
	class Solution116 {
	public:
		void connect(TreeLinkNode *root) {
			if (NULL == root)
				return;

			TreeLinkNode *curr = root;
			TreeLinkNode *levelhead = root->left;

			while (levelhead != NULL){
				if (curr->left)
					curr->left->next = curr->right;
				else if (curr->right)
					curr->right->next = curr->right;

				if (curr->next){
					curr->right->next = curr->next->left;
					curr = curr->next;
					continue;
				}

				curr = levelhead;
				levelhead = levelhead->left;
			}
		}
	};
	/*116. Populating Next Right Pointers in Each Node end*/


	/*114. Flatten Binary Tree to Linked List (medium)
	https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
	https://leetcode.com/discuss/30719/my-short-post-order-traversal-java-solution-for-share
	*/
	class Solution114 {
	public:
		TreeNode* pre = NULL;
		void flatten(TreeNode* root) {
			if (root == NULL)
				return;

			flatten(root->right);
			flatten(root->left);

			root->right = pre;
			root->left = NULL;
			pre = root;
		}

		static void main() {
			Solution114* test = new Solution114;
			TreeNode* node1 = new TreeNode(1);
			TreeNode* node2 = new TreeNode(2);
			TreeNode* node3 = new TreeNode(3);
			TreeNode* node4 = new TreeNode(4);
			TreeNode* node5 = new TreeNode(5);
			TreeNode* node6 = new TreeNode(6);

			node1->left = node2;
			node1->right = node3;
			node2->left = node4;
			node2->right = node5;
			node3->left = node6;
			test->flatten(node1);

			delNode(node1);
			delete test;
		}
	};
	/*114. Flatten Binary Tree to Linked List end*/


	/*113. Path Sum II (medium)
	https://leetcode.com/problems/path-sum-ii/
	https://leetcode.com/discuss/16980/dfs-with-one-linkedlist-accepted-java-solution
	*/
	class Solution113 {
	public:
		vector<vector<int>> m_result;

		void pathSum(TreeNode* root, vector<int> parents, int sum) {
			if (NULL == root)
				return;

			parents.push_back(root->val);
			if (NULL == root->left && NULL == root->right){
				if (sum == root->val)
					m_result.push_back(parents);

				parents.pop_back();
			}
			else{
				pathSum(root->left, parents, sum - root->val);
				pathSum(root->right, parents, sum - root->val);
			}
		}

		vector<vector<int>> pathSum(TreeNode* root, int sum) {
			vector<int> parents;
			pathSum(root, parents, sum);

			return m_result;
		}
	};
	/*113. Path Sum II end*/


	/*106. Construct Binary Tree from Inorder and Postorder Traversal (medium)
	https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
	https://leetcode.com/discuss/10961/my-recursive-java-code-with-o-n-time-and-o-n-space
	*/
	class Solution106 {
	public:
		int finditem(vector<int>& nodes, int low, int high, int target){
			for (int i = low; i <= high; ++i){
				if (nodes[i] == target)
					return i;
			}
		}

		TreeNode* buildTree(vector<int>& inorder, int instart, int inend, vector<int>& postorder, 
							int poststart, int posend){
			TreeNode* root = new TreeNode(postorder[posend]);

			int index = finditem(inorder, instart, inend, postorder[posend]);
			int leftnum = index - instart;
			int rightnum = inend - index;

			if (posend == poststart)
				return root;

			if (leftnum > 0)
				root->left = buildTree(inorder, instart, index - 1, postorder, poststart, poststart + leftnum - 1);

			if (rightnum > 0)
				root->right = buildTree(inorder, index + 1, inend, postorder, posend - rightnum, posend - 1);

			return root;
		}

		TreeNode* buildTree1(vector<int>& inorder, vector<int>& postorder) {
			if (inorder.empty() || postorder.size() != inorder.size())
				return NULL;

			TreeNode* root = buildTree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
			return root;
		}

		//lastnode is the boundary of left subtree
		TreeNode* myBuild2(vector<int>& inorder, vector<int>& postorder, TreeNode* lastnode){
			if (posPost < 0)
				return NULL;

			TreeNode* node = new TreeNode(postorder[posPost--]);

			if (inorder[posIn] != node->val)
				node->right = myBuild2(inorder, postorder, node);

			posIn--;

			if ((NULL == lastnode) || (inorder[posIn] != lastnode->val))
				node->left = myBuild2(inorder, postorder, lastnode);

			return node;
		}

		int posIn, posPost;
		TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
			if (inorder.empty() || postorder.size() != inorder.size())
				return NULL;

			posIn = inorder.size() - 1;
			posPost = postorder.size() - 1;

			TreeNode* result = myBuild2(inorder, postorder, NULL);
			return result;

		}

		static void main(){
			Solution106* test = new Solution106;
			TreeNode* result;

			vector<int> inorder1 = {2, 1, 4, 3};
			vector<int> postorder1 = {2, 4, 3, 1};

			result = test->buildTree(inorder1, postorder1);
			delNode(result);
			delete test;
		}
	};
	/*106. Construct Binary Tree from Inorder and Postorder Traversal end*/


	/*108. Convert Sorted Array to Binary Search Tree (medium)
	https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
	https://leetcode.com/discuss/10484/my-accepted-java-solution
	*/
	class Solution108 {
	public:
		TreeNode *BuildTree(vector<int> &num, int nBegin, int nEnd){
			if (nBegin > nEnd)
				return NULL;

			int nIdx = (nEnd + nBegin) / 2;
			TreeNode* curr = new TreeNode(num[nIdx]);

			curr->left = BuildTree(num, nBegin, nIdx - 1);
			curr->right = BuildTree(num, nIdx + 1, nEnd);

		}

		TreeNode *sortedArrayToBST(vector<int> &num) {
			if (num.empty())
				return NULL;

			return BuildTree(num, 0, num.size() - 1);
		}
	};
	/*108. Convert Sorted Array to Binary Search Tree end*/


	/*109. Convert Sorted List to Binary Search Tree (medium)
	https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
	https://leetcode.com/discuss/10924/share-my-code-with-o-n-time-and-o-1-space
	 time O(n) and space O(1)*/
	class Solution109 {
	public:
		ListNode* m_list;
		int listsize(ListNode* head){
			int size = 0;
			while (head){
				++size;
				head = head->next;
			}

			return size;
		}

		TreeNode* genode(int n){
			if (0 == n)
				return NULL;

			TreeNode* tmp = new TreeNode(0);

			tmp->left = genode(n / 2);
			tmp->val = m_list->val;
			m_list = m_list->next;
			tmp->right = genode(n - n / 2 - 1);

			return tmp;
		}


		TreeNode* sortedListToBST(ListNode* head) {
			m_list = head;

			return genode(listsize(head));
		}

		static void main(){
			Solution109* test = new Solution109;
			TreeNode* result;

			ListNode* node1 = new ListNode(1);
			ListNode* node2 = new ListNode(2);
			ListNode* node3 = new ListNode(3); 
			ListNode* node4 = new ListNode(4);

			node1->next = node2;
			node2->next = node3;
			node3->next = node4;

			result = test->sortedListToBST(node1);
			delNode(result);

			delete test;
		}
	};
	/*109. Convert Sorted List to Binary Search Tree end*/


	/*98. Validate Binary Search Tree (medium)
	https://leetcode.com/problems/validate-binary-search-tree/
	https://leetcode.com/discuss/14886/order-traversal-please-rely-buggy-int_max-int_min-solutions
	*/
	class Solution98 {
	public:
		bool checkBST(TreeNode* root, int max_val, int min_val){
			if (NULL == root)
				return true;

			if (root->val >= min_val && root->val <= max_val){
				if (NULL != root->left && INT_MIN == root->val)
					return false;

				if (NULL != root->right && INT_MAX == root->val)
					return false;

				return checkBST(root->left, root->val - 1, min_val) && checkBST(root->right, max_val, root->val + 1);
			}

			return false;
		}

		bool isValidBST(TreeNode* root) {
			return checkBST(root, INT_MAX, INT_MIN);
		}
	};
	/*98. Validate Binary Search Tree end*/


	/*110. Balanced Binary Tree (easy)
	https://leetcode.com/problems/balanced-binary-tree/
	https://leetcode.com/discuss/22898/the-bottom-up-o-n-solution-would-be-better*/
	class Solution110 {
	public:
		int currLevel(TreeNode* root){
			if (NULL == root)
				return 0;

			int nleft = currLevel(root->left);
			int nright = currLevel(root->right);

			return (nleft > nright ? nleft + 1 : nright + 1);
		}

		bool isBalanced(TreeNode* root) {
			if (NULL == root)
				return true;

			return isBalanced(root->left) && isBalanced(root->right) && abs(currLevel(root->left) - currLevel(root->right)) <= 1;
		}
	};
	/*110. Balanced Binary Tree end*/


	/*112. Path Sum (easy)*/
	class Solution112{
	public:
		bool hasPathSum(TreeNode *root, int sum) {
			if (root == NULL) 
				return false;

			if (root->val == sum && NULL == root->left && NULL == root->right)
				return true;

			return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
		}
	};
	/*112. Path Sum end*/

	/*257. Binary Tree Paths (easy)*/
	class Solution257 {
		public:
		string generatepath(vector<int> &path){
			string str;
			int len = path.size();
			for (int i = 0; i <len - 1; ++i)
				str += to_string(path[i]) + "->";

			str += to_string(path[len - 1]);
			return str;
		}

		void dfs(TreeNode* node, vector<int>path, vector<string>&result){
			if (!node)
				return;

			path.push_back(node->val);
			if (node->left == NULL && node->right == NULL)
				result.push_back(generatepath(path));
			else{
				if (node->left)
					dfs(node->left, path, result);

				if (node->right)
					dfs(node->right, path, result);
			}
		}

		vector<string> binaryTreePaths(TreeNode* root) {
			vector<string> result;
			vector<int> path;

			dfs(root, path, result);
			return result;
		}

		static void main() {
			Solution257* test = new Solution257;
			vector<string> result;

			TreeNode* node1 = new TreeNode(1);
			TreeNode* node2 = new TreeNode(2);
			TreeNode* node3 = new TreeNode(3);
			TreeNode* node4 = new TreeNode(4);
			node1->left = node2;
			node2->right = node4;
			node1->right = node3;

			delNode(node1);
			result = test->binaryTreePaths(node1);
			delete test;
		}
	};
	/*257. Binary Tree Paths end*/


	/*104. Maximum Depth of Binary Tree (easy)*/
	class Solution104 {
	public:
		int maxDepth(TreeNode *root) {
			return root == NULL ? 0 : max(maxDepth(root->left), maxDepth(root->right)) + 1;
		}

		int maxDepthBfs(TreeNode *root){
			if (root == NULL)
				return 0;

			int res = 0;
			queue<TreeNode *> q;
			q.push(root);
			while (!q.empty()){
				++res;

				for (int i = 0, n = q.size(); i < n; ++i){
					TreeNode *p = q.front();
					q.pop();

					if (NULL != p->left)
						q.push(p->left);
					if (NULL != p->right)
						q.push(p->right);
				}
			}

			return res;
		}
	};
	/*104. Maximum Depth of Binary Tree end*/


	/*100. Same Tree (easy)*/
	class Solution100 {
	public:
		bool isSameTree(TreeNode *p, TreeNode *q) {
			if ((p == NULL) && q)
				return false;

			if ((q == NULL) && p)
				return false;

			if (q == p)
				return true;

			return ((p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
		}
	};
	/*100. Same Tree end*/
}
//////////////////////////Tag Depth-first Search end//////////////////////////////////////////



//////////////////////////Tag Breadth-first Search//////////////////////////////////////////
namespace BFS{
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	void delNode(TreeNode* root){
		if (NULL != root){
			delNode(root->left);
			delNode(root->right);
			delete root;
		}
	}

	/*301. Remove Invalid Parentheses (hard)*/
	class Solution301 {
	public:
		bool isValid(const string & s){
			int count = 0;
			for (int i = 0; i < s.size(); ++i){
				if ('(' == s[i])
					++count;
				else if (')' == s[i] && count-- == 0)
					return false;
			}

			return count == 0;
		}

		vector<string> removeInvalidParentheses(string s) {
			unordered_set<string> visited;
			vector<string> result;
			queue<string> qstr;
			qstr.push(s);

			bool found = false;
			while (!qstr.empty()){
				string tmp = qstr.front();
				qstr.pop();

				if (isValid(tmp)){
					result.push_back(tmp);
					found = true;
				}

				//find valid in the current level and check other possibilities
				if (found)
					continue;

				for (int i = 0; i < tmp.size(); ++i){
					if ('(' != tmp[i] && ')' != tmp[i])
						continue;

					string str = tmp.substr(0, i) + tmp.substr(i + 1);

					if (visited.count(str) < 1){
						visited.insert(str);
						qstr.push(str);
					}
				}
			}

			return result;
		}

		static void main() {
			Solution301* test = new Solution301;
			vector<string> result;

			string str1("()())()");
			string str2("(a)())()");

			result = test->removeInvalidParentheses(str1);
			result = test->removeInvalidParentheses(str2);
			delete test;
		}
	};
	/*301. Remove Invalid Parentheses end*/


	/*126. Word Ladder II (hard)*/
	class Solution126 {
	public:
		vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
			vector<vector<string> > paths;
			vector<string> path(1, beginWord);

			if (beginWord == endWord) {
				paths.push_back(path);
				return paths;
			}

			unordered_set<string>word1;
			unordered_set<string>word2;
			unordered_map<string, vector<string>> nexts;
			bool bfromword1 = false;

			word1.insert(beginWord);
			word2.insert(endWord);

			if (findwords(word1, word2, wordList, nexts, bfromword1))
				getPath(beginWord, endWord, nexts, path, paths);

			return paths;
		}

		void getPath(string beginWord, string &endWord, unordered_map<string,
			vector<string> > &nexts, vector<string> &path, vector<vector<string> > &paths){
			if (beginWord == endWord)
				paths.push_back(path);
			else{
				for (auto it : nexts[beginWord]){
					path.push_back(it);
					getPath(it, endWord, nexts, path, paths);
					path.pop_back();
				}
			}
		}

		bool findwords(unordered_set<string>& word1, unordered_set<string>& word2,
			unordered_set<string> &dict, unordered_map<string, vector<string>>& nexts, bool fromword1){
			fromword1 = !fromword1;

			if (word1.empty())
				return false;

			if (word1.size() > word2.size())
				return findwords(word2, word1, dict, nexts, fromword1);

			for (auto it : word1)
				dict.erase(it);

			for (auto it : word2)
				dict.erase(it);

			unordered_set<string> word3;
			bool reach = false;

			for (auto it : word1){
				string word = it;

				for (auto ch = word.begin(); ch != word.end(); ++ch){
					char tmp = *ch;
					for (*ch = 'a'; *ch <= 'z'; ++(*ch)){
						if (*ch != tmp){
							if (word2.find(word) != word2.end()){
								reach = true;
								fromword1 ? nexts[it].push_back(word) : nexts[word].push_back(it);
							}
							else if (!reach && dict.find(word) != dict.end()){
								word3.insert(word);
								fromword1 ? nexts[it].push_back(word) : nexts[word].push_back(it);
							}
						}
					}
					*ch = tmp;
				}
			}

			return reach || findwords(word2, word3, dict, nexts, fromword1);
		}

		static void main(){
			Solution126* test = new Solution126;
			vector<vector<string>> result;
			string beginWord1("hit");
			string endWord1("cog");
			unordered_set<string> wordList1 = { "hot", "dot", "dog", "lot", "log" };

			result = test->findLadders(beginWord1, endWord1, wordList1);


			string beginWord2("hab");
			string endWord2("haw");
			unordered_set<string> wordList2 = { "hac", "hcw"};
			result = test->findLadders(beginWord2, endWord2, wordList2);
			delete test;
		}
	};
	/*126. Word Ladder II end*/


	/*279. Perfect Squares (medium)*/
	class Solution279 {
	public:
		int numSquares(int n) {
			vector<int> mindp(n + 1, INT_MAX);

			mindp[0] = 0;

			for (int i = 1; i <= n; ++i){
				for (int j = 1; j*j <= i; ++j)
					mindp[i] = min(mindp[i], mindp[i - j*j] + 1);
			}

			return mindp.back();
		}

		static void main(){
			Solution279* test = new Solution279;
			int result;

			//12 = 4 + 4 + 4
			result = test->numSquares(12);

			//12 = 4 + 9
			result = test->numSquares(13);
			delete test;
		}
	};
	/*279. Perfect Squares end*/


	/*199. Binary Tree Right Side View (medium)*/
	class Solution199 {
	public:
		vector<int> rightSideView(TreeNode* root) {
			vector<int> result;
			if (NULL == root)
				return result;

			queue<TreeNode*> nodes;
			TreeNode* tmp = NULL, *pre = NULL;

			nodes.push(root);
			nodes.push(tmp);

			while (!nodes.empty()){
				tmp = nodes.front();
				while (tmp != NULL){
					pre = tmp;
					nodes.pop();
					if (pre->left)
						nodes.push(pre->left);

					if (pre->right)
						nodes.push(pre->right);

					tmp = nodes.front();
				}

				nodes.pop();
				result.push_back(pre->val);

				if (nodes.empty())
					break;

				pre = NULL;
				nodes.push(pre);
			}

			return result;
		}

		static void main(){
			Solution199* test = new Solution199;
			vector<int> result;

			TreeNode* node1 = new TreeNode(1);
			TreeNode* node2 = new TreeNode(2);
			TreeNode* node3 = new TreeNode(3);
			TreeNode* node4 = new TreeNode(4);
			TreeNode* node5 = new TreeNode(5);

			node1->left = node2;
			node1->right = node3;
			node2->right = node4;
			node3->right = node5;
			result = test->rightSideView(node1);
			delNode(node1);
			delete test;
		}
	};
	/*199. Binary Tree Right Side View end*/

	
	/*107. Binary Tree Level Order Traversal II (easy)*/
	class Solution107 {
	public:
		vector<vector<int>> result;
		void levelorder(TreeNode* root, int depth){
			if (NULL == root)
				return;

			//for current layer
			if (result.size() == depth)
				result.push_back(vector<int>());

			result[depth].push_back(root->val);

			levelorder(root->left, depth + 1);
			levelorder(root->right, depth + 1);
		}

		vector<vector<int>> levelOrderBottom(TreeNode* root) {
			if (root == NULL)
				return result;

			levelorder(root, 0);
			reverse(result.begin(), result.end());
			return result;
		}

		vector<vector<int>> levelOrderBottom1(TreeNode* root) {
			vector<vector<int>> result;

			if (root == NULL)
				return result;

			queue<TreeNode*> tmpQue;

			tmpQue.push(root);
			tmpQue.push(NULL);

			vector<int> tmpVec;
			while (!tmpQue.empty())
			{
				TreeNode* tmpNode = tmpQue.front();
				tmpQue.pop();

				if (NULL == tmpNode){
					result.push_back(tmpVec);
					tmpVec.clear();

					if (!tmpQue.empty())
						tmpQue.push(NULL);
				}
				else{
					tmpVec.push_back(tmpNode->val);
					if (tmpNode->left)
						tmpQue.push(tmpNode->left);

					if (tmpNode->right)
						tmpQue.push(tmpNode->right);
				}
			}

			reverse(result.begin(), result.end());
			return result;
		}

		static void main(){
			Solution107* test = new Solution107;
			vector<vector<int>> result;

			TreeNode* node1 = new TreeNode(1);
			TreeNode* node2 = new TreeNode(2);
			TreeNode* node3 = new TreeNode(3);
			TreeNode* node4 = new TreeNode(4);

			node1->left = node2;
			node1->right = node3;
			node2->right = node4;

			result = test->levelOrderBottom1(node1);
			result = test->levelOrderBottom(node1);
			delNode(node1);
			delete test;
		}
	};
	/*107. Binary Tree Level Order Traversal II end*/

	/*111. Minimum Depth of Binary Tree (easy)*/
	class Solution111 {
	public:
		int minDepth(TreeNode* root) {
			if (root == 0)
				return 0;

			if (!root->left)
				return minDepth(root->right) + 1;

			if (!root->right)
				return minDepth(root->left) + 1;

			int nleft = minDepth(root->left) + 1;
			int nright = minDepth(root->right) + 1;
			return nleft > nright ? nright : nleft;
		}

		static void main(){
			Solution111* test = new Solution111;
			int result;

			TreeNode* node1 = new TreeNode(1);
			TreeNode* node2 = new TreeNode(2);
			TreeNode* node3 = new TreeNode(3);
			TreeNode* node4 = new TreeNode(4);

			node1->left = node2;
			node1->right = node3;
			node2->right = node4;
			result = test->minDepth(node1);
			delNode(node1);
			delete test;
		}
	};
	/*111. Minimum Depth of Binary Tree end*/


	/*102. Binary Tree Level Order Traversal */
	class Solution102 {
	public:
		vector<vector<int>> result;

		void levelorder(TreeNode* root, int depth){
			if (NULL == root)
				return;

			//for current layer
			if (result.size() == depth)
				result.push_back(vector<int>());

			result[depth].push_back(root->val);

			levelorder(root->left, depth + 1);
			levelorder(root->right, depth + 1);
		}

		void levelorder(TreeNode* root){
			if (NULL == root)
				return;

			queue<TreeNode*> lst;
			lst.push(root);
			lst.push(NULL);

			vector<int> current;
			while (!lst.empty()){
				TreeNode* tmp = lst.front();
				lst.pop();

				if (tmp == NULL){
					result.push_back(current);
					current.resize(0);

					if (lst.size())
						lst.push(NULL);
				}
				else{
					current.push_back(tmp->val);
					if (tmp->left)
						lst.push(tmp->left);
					if (tmp->right)
						lst.push(tmp->right);
				}

			}
		}

		vector<vector<int>> levelOrder(TreeNode* root) {
			//levelorder(root, 0);
			levelorder(root);
			return result;
		}

		static void main(){
			Solution102* test = new Solution102;
			vector<vector<int>> result;

			TreeNode* node1 = new TreeNode(1);
			TreeNode* node2 = new TreeNode(2);
			TreeNode* node3 = new TreeNode(3);
			TreeNode* node4 = new TreeNode(4);

			node1->left = node2;
			node1->right = node3;
			node2->right = node4;

			result = test->levelOrder(node1);
			delNode(node1);
			delete test;
		}
	};
	/*102. Binary Tree Level Order Traversal end */


	/*101. Symmetric Tree (easy)*/
	class Solution101 {
	public:
		bool mySymmetric(TreeNode* left, TreeNode* right){
			if (left == NULL && right == NULL)
				return true;
			else if (right == NULL)
				return false;
			else if (left == NULL)
				return false;

			if (left->val != right->val)
				return false;

			return mySymmetric(left->left, right->right) && mySymmetric(left->right, right->left);
		}

		bool isSymmetric(TreeNode* root) {
			if (root == NULL)
				return true;

			return mySymmetric(root->left, root->right);
		}

		static void main(){
			Solution101* test = new Solution101;
			bool result;

			TreeNode* node1 = new TreeNode(1);
			TreeNode* node2 = new TreeNode(2);
			TreeNode* node3 = new TreeNode(2);
			TreeNode* node4 = new TreeNode(4);

			node1->left = node2;
			node1->right = node3;
			result = test->isSymmetric(node1);

			node2->left = node4;
			result = test->isSymmetric(node1);
			delNode(node1);
			delete test;
		}
	};
	/*101. Symmetric Tree end*/
	//////////////////////////Tag Breadth-first Search end//////////////////////////////////////////
}
//////////////////////////Tag Breadth-first Search end//////////////////////////////////////////

//////////////////////////Tag Graph//////////////////////////////////////////
/*332. Reconstruct Itinerary (medium)*/
class Solution332 {
public:
	unordered_map<string, multiset<string>> maps;
	vector<string> ret;


	vector<string> findItinerary(vector<pair<string, string>> tickets) {
		if (tickets.empty())
			return ret;

		for (auto item : tickets)
			maps[item.first].insert(item.second);

		if (maps.count("JFK") < 1)
			return ret;

		visit("JFK");
		return vector<string>(ret.rbegin(), ret.rend());
	}


	void visit(string port){
		while (!maps[port].empty()){
			string tmp = *maps[port].begin();
			maps[port].erase(maps[port].begin());
			visit(tmp);
		}


		ret.push_back(port);
	}

	static void main(){
		Solution332* test = new Solution332;


		delete test;
	}
};
/*332. Reconstruct Itinerary end*/


/*310. Minimum Height Trees (medium)*/
class Solution310 {
public:
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
		vector<unordered_set<int>> adj(n);

		for (pair<int, int> item : edges){
			adj[item.first].insert(item.second);
			adj[item.second].insert(item.first);
		}


		vector<int> leaves;
		if (n == 1){
			leaves.push_back(0);
			return leaves;
		}

		for (int i = 0; i < adj.size(); ++i){
			if (1 == adj[i].size())
				leaves.push_back(i);
		}

		while (n > 2){
			n -= leaves.size();

			vector<int> nextleaves;
			for (int i = 0; i < leaves.size(); ++i){
				int nextnode = *(adj[leaves[i]].begin());

				adj[leaves[i]].erase(nextnode);
				adj[nextnode].erase(leaves[i]);

				if (1 == adj[nextnode].size())
					nextleaves.push_back(nextnode);
			}

			leaves = nextleaves;
		}

		return leaves;
	}

	static void main(){
		Solution310* test = new Solution310;
		vector<int> result;

		int n1 = 4;
		vector<pair<int, int>> edges1 = { { 1, 0 }, { 1, 2 }, { 1, 3 } };
		result = test->findMinHeightTrees(n1, edges1);

		int n2 = 6;
		vector<pair<int, int>> edges2 = { { 0, 3 }, { 1, 3 }, { 2, 3 }, { 4, 3 }, { 5, 4 } };

		result = test->findMinHeightTrees(n2, edges2);

		delete test;
	}
};
/*310. Minimum Height Trees end*/


/*133. Clone Graph (medium)*/
class Solution133 {
public:
	struct UndirectedGraphNode {
		int label;
		vector<UndirectedGraphNode *> neighbors;
		UndirectedGraphNode(int x) : label(x) {};
	};

	unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> hash;
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (!node)
			return node;


		if (hash.find(node) == hash.end()){
			hash[node] = new UndirectedGraphNode(node->label);

			for (auto item : node->neighbors)
				hash[node]->neighbors.push_back(cloneGraph(item));
		}

		return hash[node];
	}


	void delGraph(UndirectedGraphNode* root, unordered_set<UndirectedGraphNode*>& mem){
		if (root  && mem.find(root) == mem.end()){
			mem.insert(root);
			for (auto item : root->neighbors){
					delGraph(item, mem);
			}

			delete root;
			root = NULL;
		}
	}

	static void main(){
		Solution133* test = new Solution133;
		UndirectedGraphNode* node0 = new UndirectedGraphNode(0);
		UndirectedGraphNode* node1 = new UndirectedGraphNode(1);
		UndirectedGraphNode* node2 = new UndirectedGraphNode(2);

		node0->neighbors.push_back(node1);
		node0->neighbors.push_back(node2);

		node1->neighbors.push_back(node2);
		node2->neighbors.push_back(node2);


		UndirectedGraphNode* root = test->cloneGraph(node0);
		unordered_set<UndirectedGraphNode*> mem;
		test->delGraph(node0, mem);


		mem.clear();
		test->delGraph(root, mem);
		delete test;
	}
};
/*133. Clone Graph end*/
//////////////////////////Tag Graph end//////////////////////////////////////////



//////////////////////////Tag Union Find//////////////////////////////////////////
/*128. Longest Consecutive Sequence (hard)*/
class Solution128 {
public:
	int longestConsecutive(vector<int>& nums) {
		unordered_map<int, int> map;
		int result = 0, sum;

		int left, right;
		for (int i = 0; i < nums.size(); ++i){
			if (0 == map.count(nums[i])){
				left = (map.count(nums[i] - 1) > 0) ? map[nums[i] - 1] : 0;
				right = (map.count(nums[i] + 1) > 0) ? map[nums[i] + 1] : 0;

				sum = left + right + 1;
				map[nums[i]] = sum;
				result = max(sum, result);
				map[nums[i] - left] = sum;
				map[nums[i] + right] = sum;
			}
		}

		return result;
	}

	static void main() {
		Solution128* test = new Solution128;
		int result;

		vector<int> nums1 = { 100, 4, 200, 1, 3, 2 };

		result = test->longestConsecutive(nums1);
		delete test;
	}
};
/*128. Longest Consecutive Sequence end*/


/*200. Number of Islands (Medium)*/
class Solution200 {
public:
	void dfs(vector<vector<char>>& grid, int i, int j){
		if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() ||
			grid[i][j] != '1')
			return;

		grid[i][j] = '0';
		dfs(grid, i + 1, j);
		dfs(grid, i - 1, j);
		dfs(grid, i, j - 1);
		dfs(grid, i, j + 1);
	}

	void bfs(vector<vector<char>>& grid, int i, int j){
		grid[i][j] = '0';
		queue<vector<int>> adjs;
		adjs.push({ i,j });

		while (!adjs.empty()){
			int m = adjs.front()[0];
			int n = adjs.front()[1];
			adjs.pop();

			if (m > 0 && grid[m - 1][n] == '1'){
				adjs.push({ m - 1,n });
				grid[m - 1][n] = '0';
			}

			if (m < grid.size() - 1 && grid[m + 1][n] == '1'){
				adjs.push({ m + 1,n });
				grid[m + 1][n] = '0';
			}

			if (n > 0 && grid[m][n - 1] == '1'){
				adjs.push({ m,n - 1 });
				grid[m][n - 1] = '0';
			}

			if (n < grid[0].size() - 1 && grid[m][n + 1] == '1'){
				adjs.push({ m,n + 1 });
				grid[m][n + 1] = '0';
			}
		}
	}

	int numIslands(vector<vector<char>>& grid) {
		if (grid.empty() || grid[0].empty())
			return 0;

		int ret = 0;

		for (int i = 0; i < grid.size(); ++i)
			for (int j = 0; j < grid[0].size(); ++j){
				if (grid[i][j] == '1'){
					ret++;
					//dfs(grid, i, j);
					bfs(grid, i, j);
				}
			}

		return ret;
	}

	static void main() {
		Solution200* test = new Solution200;
		int result;
		vector<vector<char>> grid1 = { { '1', '1', '1', '1', '0'},
										{ '1', '1', '0', '1', '0' },
										{ '1', '1', '0', '0', '0' },
										{ '0', '0', '0', '0', '0' } };
		result = test->numIslands(grid1);
		delete test;
	}
};
/*200. Number of Islands end*/


/*130. Surrounded Regions (medium)*/
/*one of solution is to dfs all the elements*/
class Solution130 {
public:
	void solve(vector<vector<char>>& board) {
		int i, j;
		int row = board.size();
		if (!row)
			return;

		int col = board[0].size();

		for (i = 0; i < row; ++i) {
			check(board, i, 0, row, col);
			if (col > 1)
				check(board, i, col - 1, row, col);
		}

		for (j = 1; j + 1 < col; ++j) {
			check(board, 0, j, row, col);
			if (row > 1)
				check(board, row - 1, j, row, col);
		}

		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				if ('O' == board[i][j])
					board[i][j] = 'X';
				else if ('1' == board[i][j])
					board[i][j] = 'O';
			}
		}
	}

	void check(vector<vector<char> >&vec, int i, int j, int row, int col) {
		if (i < 0 || i >= row || j < 0 || j >= col)
			return;

		if (vec[i][j] == 'O') {
			vec[i][j] = '1';
			check(vec, i - 1, j, row, col);
			check(vec, i, j - 1, row, col);
			check(vec, i + 1, j, row, col);
			check(vec, i, j + 1, row, col);
		}
	}

	static void main() {
		Solution130* test = new Solution130;
		vector<vector<char>> board1 = { {'X', 'X', 'X', 'X'},
										{'X', 'O', 'O', 'X' },
										{'X', 'X', 'O', 'X' },
										{'X', 'O', 'X', 'X' } };
		test->solve(board1);
		delete test;
	}
};
/*130. Surrounded Regions end*/
//////////////////////////Tag Union Find end//////////////////////////////////////////



//////////////////////////Tag Design//////////////////////////////////////////
/*297. Serialize and Deserialize Binary Tree (hard)*/
class Codec297 {
public:
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	void serialize(TreeNode* root, ostringstream& out) {
		if (root){
			out << root->val << ' ';
			serialize(root->left, out);
			serialize(root->right, out);
		}
		else
			out << "# ";
	}

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream out;
		serialize(root, out);

		return out.str();
	}

	TreeNode* deserialize(istringstream &in) {
		string str;

		in >> str;
		if (str == "#")
			return NULL;

		TreeNode* node = new TreeNode(stoi(str));
		node->left = deserialize(in);
		node->right = deserialize(in);
		return node;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream in(data);

		return deserialize(in);
	}

	void delNode(TreeNode* root){
		if (NULL == root)
			return;

		delNode(root->left);
		delNode(root->right);
		delete root;
	}

	static void main(){
		Codec297* test = new Codec297;
		TreeNode* node1 = new TreeNode(1);
		TreeNode* node2 = new TreeNode(2);
		TreeNode* node3 = new TreeNode(3);
		node1->left = node2;
		node2->right = node3;

		string str = test->serialize(node1);
		test->delNode(node1);

		TreeNode* root = test->deserialize(str);
		test->delNode(root);
		delete test;
	}
};
/*297. Serialize and Deserialize Binary Tree end*/


/*146. LRU Cache (hard)*/
class LRUCache146{
public:
	LRUCache146(int capacity) {
		max_num = capacity;
	}

	int get(int key) {
		auto it = keys.find(key);
		if (it == keys.end())
			return -1;

		used.erase(it->second.second);
		used.push_front(key);
		it->second.second = used.begin();

		return keys[key].first;
	}

	void set(int key, int value) {
		if (keys.count(key) < 1){
			if (used.size() >= max_num){
				keys.erase(used.back());
				used.pop_back();
			}

			used.push_front(key);
			keys[key] = make_pair(value, used.begin());
		}
		else{
			used.erase(keys[key].second);
			used.push_front(key);
			keys[key] = make_pair(value, used.begin());
		}
	}

	unordered_map<int, pair<int, list<int>::iterator>> keys;
	list<int> used;

	int max_num;

	static void main(){
		LRUCache146* test = new LRUCache146(2);
		int result;

		test->set(1, 11);
		test->set(2, 22);

		result = test->get(3);
		result = test->get(1);
		test->set(3, 33);
		result = test->get(1); //return 11
		result = test->get(2); //return -1

		delete test;
	}
};
/*146. LRU Cache end*/


/*341. Flatten Nested List Iterator (medium)*/
#if 0
class NestedIterator341 {
public:
	NestedIterator341(vector<NestedInteger> &nestedList) {

		dfs(nestedList);
		m_cur = 0;
	}

	void dfs(vector<NestedInteger> &nestedList)
	{
		for (int i = 0; i < nestedList.size(); ++i)
		{
			if (nestedList[i].isInteger())
				m_vec.push_back(nestedList[i].getInteger());
			else
			{
				vector<NestedInteger> tmp = nestedList[i].getList();
				dfs(tmp);
			}
		}
	}

	int next() {
		return  m_vec[m_cur++];
	}

	bool hasNext() {
		return m_cur < m_vec.size();
	}


	vector<int> m_vec;
	int m_cur;
};
#endif
/*341. Flatten Nested List Iterator end*/


/*295. Find Median from Data Stream (hard)*/
class MedianFinder295 {
public:

	// Adds a number into the data structure.
	void addNum(int num) {
		small.push(num);
		large.push(-small.top());
		small.pop();

		if (large.size() > small.size())
		{
			small.push(-large.top());
			large.pop();
		}
	}

	// Returns the median of current data stream
	double findMedian() {
		return small.size() > large.size() ? small.top() : (small.top() - large.top()) / 2.0;
	}

	priority_queue<long> small, large;

	static void main(){
		MedianFinder295* test = new MedianFinder295;
		double result;

		test->addNum(1);
		test->addNum(2);
		result = test->findMedian();

		delete test;
	}
};

/*295. Find Median from Data Stream end*/


/*173. Binary Search Tree Iterator (medium)*/
class BSTIterator173 {
public:
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	BSTIterator173(TreeNode *root) {
		pushall(root);
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !m_stack.empty();
	}

	/** @return the next smallest number, time O(h)*/
	int next() {
		TreeNode *tmp = m_stack.top();
		m_stack.pop();
		pushall(tmp->right);
		return tmp->val;
	}

	static void main(){
		TreeNode *root = new TreeNode(2);
		TreeNode *node1 = new TreeNode(1);
		TreeNode *node2 = new TreeNode(3);
		root->left = node1;
		root->right = node2;
		BSTIterator173* test = new BSTIterator173(root);

		while (test->hasNext())
			cout << test->next() << endl;

		delete test;
	}

private:
	void pushall(TreeNode *node)
	{
		for (; node != NULL; m_stack.push(node), node = node->left)
			;
	}
	stack<TreeNode *> m_stack;
};

/**
* Your BSTIterator will be called like this:
* BSTIterator i = BSTIterator(root);
* while (i.hasNext()) cout << i.next();
*/
/*173. Binary Search Tree Iterator end*/


/*355. Design Twitter (medium)*/
class Twitter355 {
public:
	/** Initialize your data structure here. */
	Twitter355() {
		idxfeed = 0;
	}

	/** Compose a new tweet. */
	void postTweet(int userId, int tweetId) {
		twits[userId].push_back(make_pair(idxfeed, tweetId));
		++idxfeed;
	}

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
	vector<int> getNewsFeed(int userId) {
		vector<int> result;
		vector<pair<int, int>> feeds;

		for (auto item : follows[userId])
		{
			if (twits.count(item) && twits[item].size())
				feeds.insert(feeds.end(), twits[item].begin(), twits[item].end());
		}

		if (twits.count(userId) && twits[userId].size())
			feeds.insert(feeds.end(), twits[userId].begin(), twits[userId].end());

		auto f = [](const pair<int, int>& a, const pair<int, int>& b) {
			return a.first < b.first;
		};

		make_heap(feeds.begin(), feeds.end(), f);

		int count = 10;
		int last_id = -1;
		for (int i = 0; i < count && !feeds.empty(); ++i)
		{
			pop_heap(feeds.begin(), feeds.end(), f);
			auto& lastfeed = feeds.back();
			if (last_id != lastfeed.second)
			{
				result.push_back(lastfeed.second);
				last_id = lastfeed.second;
			}

			feeds.pop_back();
		}

		return result;
	}

	/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
	void follow(int followerId, int followeeId) {
		if (followerId == followeeId)
			return;

		if (follows.count(followerId))
		{
			if (follows[followerId].count(followeeId) < 1)
				follows[followerId].insert(followeeId);
		}
		else
			follows[followerId].insert(followeeId);
	}

	/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
	void unfollow(int followerId, int followeeId) {
		if (followerId == followeeId)
			return;

		if (follows.count(followerId) && follows[followerId].count(followeeId))
			follows[followerId].erase(followeeId);
	}

	unordered_map<int, unordered_set<int>> follows;
	unordered_map<int, vector<pair<int, int>>> twits;
	int idxfeed;

	static void main(){
		Twitter355* twitter = new Twitter355;
		vector<int> result;

		// User 1 posts a new tweet (id = 5).
		twitter->postTweet(1, 5);

		// User 1's news feed should return a list with 1 tweet id -> [5].
		result = twitter->getNewsFeed(1);

		// User 1 follows user 2.
		twitter->follow(1, 2);

		// User 2 posts a new tweet (id = 6).
		twitter->postTweet(2, 6);

		// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
		// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
		result = twitter->getNewsFeed(1);

		// User 1 unfollows user 2.
		twitter->unfollow(1, 2);

		// User 1's news feed should return a list with 1 tweet id -> [5],
		// since user 1 is no longer following user 2.
		result = twitter->getNewsFeed(1);
		delete twitter;
	}
};

/**
* Your Twitter object will be instantiated and called as such:
* Twitter obj = new Twitter();
* obj.postTweet(userId,tweetId);
* vector<int> param_2 = obj.getNewsFeed(userId);
* obj.follow(followerId,followeeId);
* obj.unfollow(followerId,followeeId);
*/
/*355. Design Twitter end*/


#if 0
/*284. Peeking Iterator(medium)*/
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator284 {
	struct Data;
	Data* data;
public:
	Iterator284(const vector<int>& nums);
	Iterator284(const Iterator284& iter);
	virtual ~Iterator284();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};


class PeekingIterator284 : public Iterator284 {
public:
	PeekingIterator284(const vector<int>& nums) : Iterator284(nums) {
		// Initialize any member here.
		// **DO NOT** save a copy of nums and manipulate it directly.
		// You should only use the Iterator interface methods.

	}

	// Returns the next element in the iteration without advancing the iterator.
	int peek() {
		return Iterator284(*this).next();
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
		Iterator284::next();
	}

	bool hasNext() const {
		return Iterator284::hasNext();
	}

	static void main(){
		vector<int> nums1 = { 3, 2, 5 };
		PeekingIterator284* test = new PeekingIterator284(nums1);
		int result;

		result = test->peek();
		result = test->next();
		test->hasNext();

		delete test;
	}
};
#endif
/*284. Peeking Iterator end*/


/*225. Implement Stack using Queues (easy)*/
class Stack225 {
public:
	queue<int> num;
	// Push element x onto stack.
	void push(int x) {
		num.push(x);
		for (int i = 0; i < num.size() - 1; ++i)
		{
			num.push(num.front());
			num.pop();
		}
	}

	// Removes the element on top of the stack.
	void pop() {
		num.pop();
	}

	// Get the top element.
	int top() {
		return num.front();
	}

	// Return whether the stack is empty.
	bool empty() {
		return num.empty();
	}

	static void main(){
		Stack225* test = new Stack225;

		delete test;
	}

};
/*225. Implement Stack using Queues end*/


/*155. Min Stack(easy)*/
class MinStack155 {
	struct Node {
		int val;
		int min;
		Node *next;
	};

private:
	Node *head;

public:
	MinStack155(){
		head = NULL;
	}

	~MinStack155(){
		delete head;
	}

	void push(int x) {
		Node *tmp = new Node;
		tmp->val = x;
		tmp->next = NULL;
		tmp->min = x;

		if (head == NULL){
			head = tmp;
		}
		else{
			if (head->min < x)
				tmp->min = head->min;
		}

		tmp->next = head;

		head = tmp;
	}

	void pop() {
		Node *tmp = head;

		head = head->next;
		delete tmp;

	}

	int top() {
		return head->val;
	}

	int getMin() {
		return head->min;
	}

	static void main(){
		MinStack155* test = new MinStack155;
		int result;

		test->push(-2);
		test->push(0);
		test->push(-3);
		result = test->getMin();   // Returns - 3
		test->pop();
		test->top();      // Returns 0
		result = test->getMin();   // Returns - 2

		delete test;
	}

};

class MinStack155_2 {
	long min;
	stack<long> nums;

public:
	MinStack155_2(){
	}

	void push(int x) {
		if (nums.empty()){
			nums.push(0);
			min = x;
		}
		else{
			nums.push(x - min);//Could be negative if min value needs to change
			if ( x < min) 
				min = x;
		}
	}

	void pop() {
		if (nums.empty())
			return;

		long pop = nums.top();
		nums.pop();

		if (pop < 0)  
			min = min - pop;//If negative, increase the min value
	}

	int top() {
		long top = nums.top();
		if (top > 0) // current top is the dif with min
			return (int)(top + min);
		else		// current top the min
			return (int)(min);
	}

	int getMin() {
		return (int)min;
	}

	static void main(){
		MinStack155_2* test = new MinStack155_2;
		int result;

		test->push(-2);
		test->push(0);
		test->push(-3);
		result = test->getMin();   // Returns - 3
		test->pop();
		test->top();      // Returns 0
		result = test->getMin();   // Returns - 2

		delete test;
	}
};
/*155. Min Stack end*/
//////////////////////////Tag Design end//////////////////////////////////////////



//////////////////////////Tag Topological Sort//////////////////////////////////////////
/*210. Course Schedule II (medium)*/
class Solution210 {
public:
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<int> innum(numCourses, 0);
		queue<int> nodes;
		vector<int> topsort;

		vector<unordered_set<int>> adj(numCourses);

		for (auto item : prerequisites)
			adj[item.second].insert(item.first);

		for (auto item : adj)
		for (int neighbor : item)
			innum[neighbor] ++;

		for (int i = 0; i < numCourses; ++i){
			if (0 == innum[i])
				nodes.push(i);
		}

		for (int i = 0; i < numCourses; ++i){
			if (nodes.empty())
				return{};

			int cur = nodes.front();
			nodes.pop();

			topsort.push_back(cur);

			for (int item : adj[cur]){
				if (!--innum[item])
					nodes.push(item);
			}
		}

		return topsort;
	}

	static void main(){
		Solution210* test = new Solution210;
		vector<int> result;

		int numCourses1 = 2;//true
		vector<pair<int, int>> prerequisites1 = { { 1, 0 } };
		result = test->findOrder(numCourses1, prerequisites1);

		int numCourses2 = 3;//true
		vector<pair<int, int>> prerequisites2 = { { 2, 0 }, { 1, 0 }, { 2, 1 } };
		result = test->findOrder(numCourses2, prerequisites2);

		int numCourses3 = 3;//false
		vector<pair<int, int>> prerequisites3 = { { 2, 0 }, { 2, 1 }, { 0, 2 } };
		result = test->findOrder(numCourses3, prerequisites3);

		delete test;
	}
};
/*210. Course Schedule II end*/


/*207. Course Schedule (medium)*/
class Solution207 {
public:
	/*normal dfs time O(|V| + |E|), space O(|E|)*/
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<unordered_set<int>> adj(numCourses);

		for (auto item : prerequisites)
			adj[item.second].insert(item.first);

		for (int i = 0; i < adj.size(); ++i){
			vector<int> visit(numCourses, 0);
			stack<int> nodeque;

			for (auto edge : adj[i]){
				if (edge == i)
					return false;
				visit[edge] = 1;
				nodeque.push(edge);
			}

			while (!nodeque.empty()){
				int tmp = nodeque.top();
				nodeque.pop();

				for (auto edge : adj[tmp]){
					if (edge == i)
						return false;

					if (visit[edge] == 0){
						visit[edge] = 1;
						nodeque.push(edge);
					}
				}
			}
		}

		return true;
	}

	/*use topological sorting time O(|V| + |E|), space O(|V| + |E|) */
	bool canFinish1(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<unordered_set<int>> adj(numCourses);
		vector<int> degrees(numCourses, 0);

		/*build graph*/
		for (auto item : prerequisites)
			adj[item.second].insert(item.first);

		/*calulate in degrees*/
		for (auto item : adj){
			for (auto neighbor : item)
				++degrees[neighbor];
		}

		list<int> nodes;
		for (int i = 0; i < numCourses; ++i){
			if (0 == degrees[i])
				nodes.push_back(i);
		}

		while (!nodes.empty()){
			int cur = nodes.front();
			nodes.pop_front();

			for (auto item : adj[cur]){
				if (0 == --degrees[item])
					nodes.push_back(item);
			}

		}

		for (auto item : degrees){
			if (0 != item)
				return false;
		}

		return true;
	}

	static void main(){
		Solution207* test = new Solution207;
		bool result;

		int numCourses1 = 2;//true
		vector<pair<int, int>> prerequisites1 = { { 1, 0 } };
		result = test->canFinish(numCourses1, prerequisites1);
		result = test->canFinish1(numCourses1, prerequisites1);

		int numCourses2 = 3;//true
		vector<pair<int, int>> prerequisites2 = { { 2, 0 }, { 1, 0 }, { 2, 1 } };
		result = test->canFinish(numCourses2, prerequisites2);
		result = test->canFinish1(numCourses2, prerequisites2);

		int numCourses3 = 3;//false
		vector<pair<int, int>> prerequisites3 = { { 2, 0 }, { 2, 1 }, { 0, 2 } };
		result = test->canFinish(numCourses3, prerequisites3);
		result = test->canFinish1(numCourses3, prerequisites3);

		delete test;
	}

};
/*207. Course Schedule end*/
//////////////////////////Tag Topological Sort end//////////////////////////////////////////


//////////////////////////Tag Trie//////////////////////////////////////////
/*336. Palindrome Pairs (hard)*/
class Solution336 {
public:
	bool isPalin(string& str){
		int len = str.size() - 1;
		int i = 0;

		while (i <= len){
			if (str[i++] != str[len--])
				return false;
		}

		return true;
	}

	/*time O(n k ^ 2), space O(n)*/
	vector<vector<int>> palindromePairs(vector<string>& words) {
		vector<vector<int>> result;

		if (words.empty())
			return result;

		unordered_map<string, int> dict;

		for (int i = 0; i < words.size(); ++i)
			dict[words[i]] = i;

		int len = words.size();
		for (int i = 0; i < len; ++i){
			for (int j = 0; j <= words[i].size(); ++j){
				string str1 = words[i].substr(0, j);
				string str2 = words[i].substr(j);
				vector<int> vec(2, 0);
				if (isPalin(str1)){
					string str2rev = str2;
					reverse(str2rev.begin(), str2rev.end());

					if (dict.count(str2rev) > 0 && dict[str2rev] != i){
						vec[0] = dict[str2rev];
						vec[1] = i;
						result.push_back(vec);
					}
				}

				if (isPalin(str2)){
					string str1rev = str1;
					reverse(str1rev.begin(), str1rev.end());

					if (dict.count(str1rev) > 0 && dict[str1rev] != i && !str2.empty()){
						vec[1] = dict[str1rev];
						vec[0] = i;
						result.push_back(vec);
					}
				}
			}
		}

		return result;
	}

	static void main(){
		Solution336* test = new Solution336;
		vector<vector<int>> result;

		vector<string> words1 = { "bat", "tab", "cat" };
		vector<string> words2 = { "abcd", "dcba", "lls", "s", "sssll" };

		result = test->palindromePairs(words1);

		result = test->palindromePairs(words2);
		delete test;
	}
};
/*336. Palindrome Pairs end*/

/*212. Word Search II (hard)*/
class Solution212 {
	class Trie{
	public:
		Trie *children[26]; // pointers to its substrings starting with 'a' to 'z'
		bool leaf;			// if the node is a leaf, or if there is a word stopping at here
		int idx;			// if it is a leaf, the string index of the array words
		Trie(){
			fill_n(children, 26, nullptr);
			leaf = false;
			idx = 0;
		}
	};

public:
	void delNode(Trie* node){
		if (NULL != node){
			for (int i = 0; i < 26; ++i)
				delNode(node->children[i]);

			delete node;
		}
	}

	void insertWords(Trie *root, vector<string>& words, int idx){
		int pos = 0, len = words[idx].size();

		while (pos < len){
			if (NULL == root->children[words[idx][pos] - 'a'])
				root->children[words[idx][pos] - 'a'] = new Trie();

			root = root->children[words[idx][pos++] - 'a'];
		}

		root->leaf = true;
		root->idx = idx;
	}

	Trie *buildTrie(vector<string>& words){
		Trie *root = new Trie();
		int i;

		for (i = 0; i<words.size(); i++)
			insertWords(root, words, i);

		return root;
	}

	void checkWords(vector<vector<char>>& board, int i, int j, int row, int col, Trie *root, vector<string> &res, vector<string>& words)
	{
		char temp;
		if (board[i][j] == 'X')
			return; // visited before;

		if (NULL == root->children[board[i][j] - 'a'])
			return; // no string with such prefix
		else{
			temp = board[i][j];

			if (root->children[temp - 'a']->leaf){  // if it is a leaf
				res.push_back(words[root->children[temp - 'a']->idx]);
				root->children[temp - 'a']->leaf = false; // set to false to indicate that we found it already
			}

			board[i][j] = 'X'; //mark the current position as visited
			// check all the possible neighbors
			if (i > 0)
				checkWords(board, i - 1, j, row, col, root->children[temp - 'a'], res, words);

			if (i + 1 < row)
				checkWords(board, i + 1, j, row, col, root->children[temp - 'a'], res, words);

			if (j > 0)
				checkWords(board, i, j - 1, row, col, root->children[temp - 'a'], res, words);

			if (j + 1 < col)
				checkWords(board, i, j + 1, row, col, root->children[temp - 'a'], res, words);

			board[i][j] = temp; // recover the current position
		}
	}

	/*Trie + Backtrace time O(row*col) space O(26*max word length)*/
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		vector<string> result;

		int row = board.size();

		if (0 == row)
			return result;

		int col = board[0].size();

		if (0 == col)
			return result;

		int wordCount = words.size();
		if (0 == wordCount)
			return result;

		Trie *root = buildTrie(words);

		int i, j;
		for (i = 0; i < row; ++i){
			for (j = 0; j < col && wordCount > result.size(); ++j)
				checkWords(board, i, j, row, col, root, result, words);
		}

		delNode(root);
		return result;
	}

	static void main(){
		Solution212* test = new Solution212;
		vector<vector<char>> board1 = { { 'o', 'a', 'a', 'n' }, { 'e', 't', 'a', 'e' }, { 'i', 'h', 'k', 'r' }, { 'i', 'f', 'l', 'v' } };
		vector<string> words1 = { "oath", "pea", "eat", "rain" };

		vector<string> result;

		result = test->findWords(board1, words1);

		delete test;
	}
};
/*212. Word Search II end*/


/*211. Add and Search Word - Data structure design (medium)*/
class WordDictionary211 {
public:

	struct TreeNode{
		TreeNode* next[26];
		bool isword;

		TreeNode(bool bword = false){
			memset(next, 0x00, sizeof(next));
			isword = bword;
		}
	};
	// Adds a word into the data structure.
	void addWord(string word) {
		TreeNode* ptmp = root;

		for (int i = 0; i < word.size(); ++i){
			if (ptmp->next[word[i] - 'a'] == NULL)
				ptmp->next[word[i] - 'a'] = new TreeNode();

			ptmp = ptmp->next[word[i] - 'a'];
		}

		ptmp->isword = true;
	}

	// Returns if the word is in the data structure. A word could
	// contain the dot character '.' to represent any one letter.
	bool mysearch(string word, TreeNode* father) {
		int len = word.size();

		if (0 == len)
			return father->isword;
		else if (word[0] == '.'){
			string tmp = word.substr(1);
			for (int i = 0; i < 26; ++i){
				if (father->next[i] != NULL && mysearch(tmp, father->next[i]))
					return true;
			}

			return false;
		}
		else
			return father->next[word[0] - 'a'] != NULL && mysearch(word.substr(1), father->next[word[0] - 'a']);
	}

	bool search(string word)
	{
		if (word.empty())
			return false;

		return mysearch(word, root);
	}

	WordDictionary211(){
		root = new TreeNode();
	}

	TreeNode* root;

	static void main(){
		WordDictionary211* test = new WordDictionary211;
		bool result;

		test->addWord("aba");
		result = test->search(".b.");
		result = test->search(".a.");
		result = test->search("..a");

		delete test;
	}
};
/*211. Add and Search Word - Data structure design end*/


/*208. Implement Trie (Prefix Tree) (medium)*/
class Trie208 {
public:

	class TrieNode {
	public:
		TrieNode* next[26];
		bool is_word;
		// Initialize your data structure here.
		TrieNode(bool b = false) {
			memset(next, 0x00, sizeof(next));
			is_word = b;
		}
	};

	Trie208() {
		root = new TrieNode();
	}

	~Trie208() {
		delNode(root);
	}

	void delNode(TrieNode* node){
		if (NULL != node){
			for (int i = 0; i < 26; ++i)
				delNode(node->next[i]);

			delete node;
		}
	}
	// Inserts a word into the trie.
	void insert(string word) {
		TrieNode* p = root;
		for (int i = 0; i < word.size(); ++i){
			if (p->next[word[i] - 'a'] == NULL)
				p->next[word[i] - 'a'] = new TrieNode();

			p = p->next[word[i] - 'a'];
		}

		p->is_word = true;
	}

	// Returns if the word is in the trie.
	bool search(string word) {
		TrieNode* p = find(word);

		return p && p->is_word;
	}

	TrieNode* find(string key){
		TrieNode* p = root;

		for (int i = 0; i < key.size() && p != NULL; ++i){
			p = p->next[key[i] - 'a'];
		}

		return p;
	}

	// Returns if there is any word in the trie
	// that starts with the given prefix.
	bool startsWith(string prefix) {
		return find(prefix) != NULL;
	}

	static void main(){
		Trie208* test = new Trie208;
		bool result;

		test->insert("helloz");
		result = test->search("helloz");
		result = test->search("hello");

		delete test;
	}

private:
	TrieNode* root;
};
/*208. Implement Trie (Prefix Tree) end*/
//////////////////////////Tag Trie end//////////////////////////////////////////



//////////////////////////Tag Segment Tree//////////////////////////////////////////
/*218. The Skyline Problem (hard)*/
class Solution218 {
public:
	//http ://www.geeksforgeeks.org/divide-and-conquer-set-7-the-skyline-problem/
	vector<pair<int, int>> mergeSkyline(vector<pair<int, int>> &A, vector<pair<int, int>> &B){
		vector<pair<int, int>> result;

		int h1 = 0, h2 = 0;
		int i = 0, j = 0;

		while (i < A.size() && j < B.size()){
			int x = 0, h = 0;

			if (A[i].first < B[j].first){
				x = A[i].first;
				h1 = A[i++].second;
				h = max(h1, h2);
			}
			else if (A[i].first > B[j].first){
				x = B[j].first;
				h2 = B[j++].second;
				h = max(h1, h2);
			}
			else{
				x = B[j].first;
				h1 = A[i++].second;
				h2 = B[j++].second;
				h = max(h1, h2);
			}

			int len = result.size();
			if (len == 0 || h != result[len - 1].second)
				result.push_back(make_pair(x, h));
		}

		while (i < A.size())
			result.push_back(A[i++]);

		while (j < B.size())
			result.push_back(B[j++]);

		return result;
	}

	vector<pair<int, int>> recurSkyline(vector<vector<int>>& buildings, int low, int high){
		vector<pair<int, int>> result;

		if (low >= high){
			result.push_back(make_pair(buildings[low][0], buildings[low][2]));
			result.push_back(make_pair(buildings[low][1], 0));
		}
		else{
			int mid = low + (high - low) / 2;

			vector<pair<int, int>> left = recurSkyline(buildings, low, mid);
			vector<pair<int, int>> right = recurSkyline(buildings, mid + 1, high);

			result = mergeSkyline(left, right);
		}

		return result;
	}

	/*time O(nLogn)*/
	vector<pair<int, int>> getSkyline1(vector<vector<int>>& buildings) {
		vector<pair<int, int>> result;

		if (buildings.empty())
			return result;

		result = recurSkyline(buildings, 0, buildings.size() - 1);

		return result;
	}

	//https://briangordon.github.io/2014/08/the-skyline-problem.html
	/*time O(n log n) space O(n)*/
	vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
		vector<pair<int, int>> height, skyline;
		for (auto& b : buildings) {
			height.push_back({ b[0], -b[2] });
			height.push_back({ b[1], b[2] });
		}

		sort(height.begin(), height.end());
		multiset<int> m;
		int prev = 0;
		m.insert(0);
		for (auto& h : height) {
			if (h.second < 0) {
				m.insert(-h.second);
			}
			else {
				m.erase(m.find(h.second));
			}
			int cur = *m.rbegin();
			if (cur != prev) {
				skyline.push_back({ h.first, cur });
				prev = cur;
			}
		}

		return skyline;
	}

	static void main(){
		vector<pair<int, int>> result;
		vector<vector<int>> buildings1 = { { 2, 9, 10 }, { 3, 7, 15 }, { 5, 12, 12 }, { 15, 20, 10 }, { 19, 24, 8 } };
		Solution218* test = new Solution218;

		result = test->getSkyline(buildings1);
		result = test->getSkyline1(buildings1);

		delete test;
	}

};
/*218. The Skyline Problem end*/


/*307. Range Sum Query - Mutable (medium)*/
class NumArray307 {
public:
	struct Streenode{
		Streenode(int value, int s, int e) :val(value), start(s), end(e), left(NULL), right(NULL){}
		int val;
		int start;
		int end;
		Streenode* left;
		Streenode* right;
	};

	/*space O(n)*/
	NumArray307(vector<int> &nums) {
		root = buildTree(nums, 0, nums.size() - 1);
	}

	Streenode* buildTree(vector<int> &nums, int start, int end){
		if (start > end)
			return NULL;
		else if (start == end)
			return new Streenode(nums[start], start, start);
		else
		{
			int mid = start + (end - start) / 2;
			Streenode* parent = new Streenode(0, start, end);
			Streenode* left = buildTree(nums, start, mid);
			Streenode* right = buildTree(nums, mid + 1, end);

			if (left){
				parent->left = left;
				parent->val += left->val;
			}

			if (right){
				parent->right = right;
				parent->val += right->val;
			}

			return parent;
		}
	}

	/*time O(log n)*/
	void update(int i, int val) {
		update(root, i, val);
	}

	void update(Streenode* parent, int i, int val) {
		if (parent->start == parent->end)
			parent->val = val;
		else{
			int mid = parent->start + (parent->end - parent->start) / 2;

			if (i <= mid)
				update(parent->left, i, val);
			else if (i >= mid + 1)
				update(parent->right, i, val);

			parent->val = parent->left->val + parent->right->val;
		}
	}

	/*time O(log n)*/
	int sumRange(int i, int j) {
		return sumRange(root, i, j);
	}

	int sumRange(Streenode* parent, int start, int end){
		if (parent->start == start &&  parent->end == end)
			return parent->val;
		else{
			int mid = parent->start + (parent->end - parent->start) / 2;

			if (end <= mid)
				return sumRange(parent->left, start, end);
			else if (start >= mid + 1)
				return sumRange(parent->right, start, end);
			else
				return sumRange(parent->left, start, mid) + sumRange(parent->right, mid + 1, end);
		}
	}

	Streenode* root;

	static void main(){
		vector<int> nums = { 1, 3, 5 };
		NumArray307* test = new NumArray307(nums);
		test->sumRange(0, 2);
		test->update(1, 2);
		test->sumRange(0, 2);

		delete test;
	}
};
/*307. Range Sum Query - Mutable end*/
//////////////////////////Tag Segment Tree end//////////////////////////////////////////



//////////////////////////Tag Binary Search Tree//////////////////////////////////////////
/*327. Count of Range Sum (hard)*/
class Solution327 {
public:
	int countWithMerge(vector<long>& sums, int start, int end, int lower, int upper)
	{
		if (end - start <= 1)
			return 0;

		int mid = (start + end) / 2;

		int count = countWithMerge(sums, start, mid, lower, upper) +
			countWithMerge(sums, mid, end, lower, upper);


		int m = mid, n = mid, t = mid, s = 0;
		vector<long> cache(end - start, 0);

		for (int i = start; i < mid; ++s, ++i)
		{
			while (m < end && sums[m] - sums[i] < lower)
				++m;

			while (n < end && sums[n] - sums[i] <= upper)
				++n;

			count += n - m;

			while (t < end && sums[t] < sums[i])
				cache[s++] = sums[t++];

			cache[s] = sums[i];
		}

		for (int i = 0; i < s; ++i)
			sums[start + i] = cache[i];

		return count;
	}

	/*time O(n log n), space O(n)*/
	int countRangeSum(vector<int>& nums, int lower, int upper) {
		int len = nums.size();

		if (len < 1)
			return 0;

		vector<long> sums(len + 1, 0);
		for (int i = 0; i < len; ++i)
			sums[i + 1] = sums[i] + nums[i];

		return countWithMerge(sums, 0, len + 1, lower, upper);
	}

	static void main(){
		Solution327* test = new Solution327;
		int result;

		vector<int> nums1 = { -2, 5, -1 };
		int lower1 = -2;
		int upper1 = 2;

		result = test->countRangeSum(nums1, lower1, upper1);
		delete test;
	}
};
/*327. Count of Range Sum end*/


/*315. Count of Smaller Numbers After Self (hard)*/
class Solution315 {
public:
	struct TreeNode
	{
		int val;
		int lcount;
		int dup;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int v, int s) :val(v), lcount(s), dup(1), left(NULL), right(NULL){}
	};

	TreeNode* insert(int num, TreeNode* node, vector<int>& result, int i, int presum){
		if (NULL == node){
			node = new TreeNode(num, 0);
			result[i] = presum;
		}
		else if (node->val == num){
			++node->dup;
			result[i] = presum + node->lcount;
		}
		else if (node->val > num){
			++node->lcount;
			node->left = insert(num, node->left, result, i, presum);
		}
		else
			node->right = insert(num, node->right, result, i, presum + node->dup + node->lcount);

		return node;
	}

	/*space O(n), time O(n logn ) ??*/
	vector<int> countSmaller(vector<int>& nums){
		if (nums.empty())
			return vector<int>();

		vector<int> result(nums.size());
		TreeNode* root = NULL;

		for (int i = nums.size() - 1; i >= 0; --i)
			root = insert(nums[i], root, result, i, 0);

		return result;
	}

	static void main()
	{
		Solution315* test = new Solution315;
		vector<int> result;

		vector<int> nums1 = { 3, 2, 2, 6, 1 };
		result = test->countSmaller(nums1);

		vector<int> nums2 = { 5, 2, 6, 1 };
		result = test->countSmaller(nums2);
		delete test;
	}
};
/*315. Count of Smaller Numbers After Self end*/


/*352. Data Stream as Disjoint Intervals (hard)*/
class SummaryRanges352 {
public:
	struct Interval {
		int start;
		int end;
		Interval() : start(0), end(0) {}
		Interval(int s, int e) : start(s), end(e) {}
	};

	/** Initialize your data structure here. */
	SummaryRanges352() {

	}

	/*time O(log n)*/
	void addNum(int val) {
		auto it = items.lower_bound(Interval(val, val));

		int start = val;
		int end = val;

		//find the min up boarder of val
		if (it != items.begin() && (--it)->end + 1 < val)
			it++;

		//merge the interval
		while (it != items.end() && val + 1 >= it->start && val - 1 <= it->end)
		{
			start = min(start, it->start);
			end = max(end, it->end);
			it = items.erase(it);
		}

		items.insert(it, Interval(start, end));
	}

	/*time O(n)*/
	vector<Interval> getIntervals() {
		vector<Interval> result;
		for (auto it : items)
			result.push_back(it);

		return result;
	}

	struct Cmp
	{
		bool operator()(Interval a, Interval b) { return a.start < b.start; }
	};

	set<Interval, Cmp> items;

	static void main(){
		SummaryRanges352* test = new SummaryRanges352;
		vector<Interval> result;

		//1, 3, 7, 2, 6
		test->addNum(1);
		test->addNum(3);
		test->addNum(7);
		test->addNum(2);
		test->addNum(6);

		result = test->getIntervals();

		delete test;
	}
};
/*352. Data Stream as Disjoint Intervals end*/


/*220. Contains Duplicate III (medium)*/
class Solution220 {
public:
	/*time O(nlogk)*/
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		set<int> window;

		for (int i = 0; i < nums.size(); ++i){
			if (i > k)
				window.erase(nums[i - k - 1]);

			auto low = window.lower_bound(nums[i] - t);
			if (low != window.end() && *low - nums[i] <= t)
				return true;

			window.insert(nums[i]);
		}

		return false;
	}

	static void main(){
		Solution220* test = new Solution220;
		bool result;
		vector<int> nums1 = { 7, 4, 9, 6, 1 };
		int k1 = 2;
		int t1 = 2;


		vector<int> nums2 = { 7, 4, 9, 6, 1 };
		int k2 = 2;
		int t2 = 1;
		result = test->containsNearbyAlmostDuplicate(nums1, k1, t1);
		result = test->containsNearbyAlmostDuplicate(nums2, k2, t2);

		vector<int> nums3 = { 4, 1, 6, 4, 1 };
		int k3 = 2;
		int t3 = 2;

		result = test->containsNearbyAlmostDuplicate(nums3, k3, t3);
		delete test;
	}
};
/*220. Contains Duplicate III end*/
//////////////////////////Tag Binary Search Tree end//////////////////////////////////////////



//////////////////////////Tag Memoization//////////////////////////////////////////
/*329. Longest Increasing Path in a Matrix (hard)*/
class Solution329 {
public:
	int dfs(vector<vector<int>>& matrix, int i, int j, int rows, int cols, vector<vector<int>>& cache){
		if (cache[i][j] != 0)
			return cache[i][j];

		int maxlen = 1;
		int directs[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
		for (int k = 0; k < 4; ++k)
		{
			int x = i + directs[k][0];
			int y = j + directs[k][1];

			if (x < 0 || x >= rows || y < 0 || y >= cols || matrix[i][j] >= matrix[x][y])
				continue;

			int len = 1 + dfs(matrix, x, y, rows, cols, cache);
			maxlen = max(len, maxlen);
		}

		cache[i][j] = maxlen;
		return maxlen;
	}

	int longestIncreasingPath(vector<vector<int>>& matrix) {
		if (matrix.empty() || matrix[0].empty())
			return 0;

		int rows = matrix.size();
		int cols = matrix[0].size();
		int maxlen = 1;

		vector<vector<int>> cache(rows, vector<int>(cols, 0));
		for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
		{
			int len = dfs(matrix, i, j, rows, cols, cache);
			maxlen = max(maxlen, len);
		}

		return maxlen;

	}

	static void main()
	{
		Solution329* test = new Solution329;
		vector<vector<int>> matrix1 = { { 9, 9, 4 }, { 6, 6, 8 }, { 2, 1, 1 } };
		int result;

		result = test->longestIncreasingPath(matrix1);
		delete test;
	}
};
/*O(mn) time O(mn) space*/
/*329. Longest Increasing Path in a Matrix end*/
//////////////////////////Tag Memoization end//////////////////////////////////////////



//////////////////////////Tag Queue//////////////////////////////////////////
/* LeetCode 353. Design Snake Game (Medium)*/
class SnakeGame {
public:
	struct pos
	{
		pos() :x(0), y(0){}
		pos(int posx, int posy) :x(posx), y(posy){}
		int x;
		int y;

		string tostring()
		{
			return to_string(x) + "," + to_string(y);
		}
	};

	/** Initialize your data structure here.
	@param width - screen width
	@param height - screen height
	@param food - A list of food positions
	E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
	SnakeGame(int width, int height, vector<pos> food)
	{
		m_food = food;
		m_row = height;
		m_col = width;
		m_score = 0;

		pos head;
		m_snake.push_back(head);
	}

	/** Moves the snake.
	@param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
	@return The game's score after the move. Return -1 if game over.
	Game over when snake crosses the screen boundary or bites its body. */
	int move(char direction)
	{
		pos head = m_food.front();
		pos next = head;

		switch (direction)
		{
		case 'U':
			--next.x;
			break;

		case 'D':
			++next.x;
			break;

		case 'L':
			--next.y;
			break;

		case 'R':
			++next.y;
			break;

		default:
			return -1;
			break;
		}

		if (next.x >= m_row || next.x < 0 ||
			next.y >= m_col || next.y < 0)
			return -1;

		if (eat(next))
		{
			m_snake.push_front(next);
			m_board.insert(next.tostring());
			return ++m_score;
		}

		pos tail = m_snake.back();
		m_snake.pop_back();
		m_board.erase(tail.tostring());

		if (m_board.count(next.tostring()))
			return -1;

		m_snake.push_front(next);
		m_board.insert(next.tostring());

		return m_score;
	}


	bool eat(pos cur)
	{
		if (m_score >= m_food.size())
			return false;

		if (m_food[m_score].x >= m_row || m_food[m_score].x < 0 ||
			m_food[m_score].y >= m_col || m_food[m_score].y < 0)
			return false;

		if (cur.x == m_food[m_score].x && cur.y == m_food[m_score].y)
			return true;

		return false;
	}

	static void main()
	{
		SnakeGame* test = new SnakeGame(2, 3, { { 1, 2 }, { 0, 1 } });

		delete test;
	}

private:
	vector<pos> m_food;
	int m_row;
	int m_col;
	list<pos> m_snake;
	int m_score;
	unordered_set<string> m_board;

};

/**
* Your SnakeGame object will be instantiated and called as such:
* SnakeGame obj = new SnakeGame(width, height, food);
* int param_1 = obj.move(direction);
*/
/* LeetCode 353. Design Snake Game end*/
//////////////////////////Tag Queue end//////////////////////////////////////////

using namespace BFS;
using namespace DFS;
using namespace TREE;
using namespace BIT;
using namespace SORT;
using namespace GREEDY;
using namespace HEAP;
using namespace STACK;
using namespace BACKTRACK;

int _tmain(int argc, _TCHAR* argv[])
{
	Solution84::main();
	Solution85::main();
	Solution239::main();
	Solution313::main();
	Solution321::main();
	Solution164::main();
	Solution318::main();
	Solution137::main();
	Solution187::main();
	Solution236::main();
	Solution94::main();
	Solution105::main();
	Solution114::main();
	Solution106::main();
	Solution109::main();
	Solution257::main();
	Solution301::main();
	Solution126::main();
	Solution199::main();
	Solution107::main();
	Solution111::main();
	Solution102::main();
	Solution101::main();
	Solution310::main();
	Solution133::main();
	Codec297::main();
	LRUCache146::main();
	Solution128::main();
	Solution200::main();
	Solution200::main();
	Solution130::main();
	MedianFinder295::main();
	BSTIterator173::main();
	Twitter355::main();
	//PeekingIterator284::main();
	Stack225::main();
	MinStack155_2::main();
	MinStack155::main();
	Solution329::main();
	Solution210::main();
	Solution207::main();
	Solution336::main();
	Solution212::main();
	WordDictionary211::main();
	Trie208::main();
	Solution218::main();
	Solution327::main();
	Solution315::main();
	SummaryRanges352::main();
	Solution220::main();
	SnakeGame::main();

	return 0;
}

