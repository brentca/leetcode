// leetcode.cpp : Defines the entry point for the console application.
//

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

using namespace std;


//////////////////////////Tag Segment Tree//////////////////////////////////////////


/*218. The Skyline Problem (hard)*/
class Solution218 {
public:
	//https://briangordon.github.io/2014/08/the-skyline-problem.html

	vector<pair<int, int>> mergeSkyline(vector<pair<int, int>> &A, vector<pair<int, int>> &B)
	{
		vector<pair<int, int>> result;

		int h1 = 0, h2 = 0;
		int i = 0, j = 0;

		while (i < A.size() && j < B.size())
		{
			int x = 0, h = 0;

			if (A[i].first < B[j].first)
			{
				x = A[i].first;
				h1 = A[i++].second;
				h = max(h1, h2);
			}
			else if (A[i].first > B[j].first)
			{
				x = B[j].first;
				h2 = B[j++].second;
				h = max(h1, h2);
			}
			else
			{
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

	vector<pair<int, int>> recurSkyline(vector<vector<int>>& buildings, int low, int high)
	{
		vector<pair<int, int>> result;
		if (low >= high)
		{
			result.push_back(make_pair(buildings[low][0], buildings[low][2]));
			result.push_back(make_pair(buildings[low][1], 0));
		}
		else
		{
			int mid = low + (high - low) / 2;

			vector<pair<int, int>> left = recurSkyline(buildings, low, mid);
			vector<pair<int, int>> right = recurSkyline(buildings, mid + 1, high);

			result = mergeSkyline(left, right);

		}

		return result;
	}

	vector<pair<int, int>> getSkyline1(vector<vector<int>>& buildings) {
		vector<pair<int, int>> result;

		if (buildings.empty())
			return result;

		result = recurSkyline(buildings, 0, buildings.size() - 1);

		return result;
	}

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
		SnakeGame* test = new SnakeGame(2, 3, { {1, 2}, {0, 1} });

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

int _tmain(int argc, _TCHAR* argv[])
{
	Solution218::main();
	Solution327::main();
	Solution315::main();
	SummaryRanges352::main();
	Solution220::main();
	Solution329::main();
	SnakeGame::main();
	
	return 0;
}

