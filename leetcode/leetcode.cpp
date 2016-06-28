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

using namespace std;

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
			for (int i = 0; i < 26; ++i){
				delNode(node->children[i]);
			}

			delete[]node->children;
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
			for (int i = 0; i < 26; ++i){
				delNode(node->next[i]);
			}

			delete[]node->next;
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

int _tmain(int argc, _TCHAR* argv[])
{
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

