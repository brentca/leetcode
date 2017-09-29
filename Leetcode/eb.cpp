#if 0
//////////////////////// begin///////////////////////////
http://mm.fancymore.com/reading/java-threadpools.html

http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=293203&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	第一轮：刚开始烙印出了JavaScript的 题，我说我prefer用Java面试，因为之前已和recruiter说了，不知道是不是坑。
	1）merger 3 unsorted no duplcate integer array
	2）a stream of integers, find the smallest.from

	第二轮：
	1）serialize and de - serialize bt
	2）swap pairs in linked list
	follow up : use recursive

	第三轮：
	1) choose k randome value equally from a stream of integers.//http://www.geeksforgeeks.org/reservoir-sampling/
	2) maximum subarray, array contains positvie and negative integers.

	第四轮：
	1） Palindrome binary number
	2）reverse String

第五轮 :
	  1）periodic table, longest englishwords
		  2）BQs

http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=293839&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	  第一轮：土耳其小哥，问了简历＋给了一个array num, 让转化成BST
	  第二轮 : 中国小哥，人很好，特别nice，longest panlindrome subsequence 我写了基础解法，让优化成o(nlongn) (lc 300)
			第三轮：印度manager，leetcode phone keyboard 那道题的变形
			第四轮：烙印，斐波那契数列，shuffle an array，又问了简历 project和引申问题

		http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=223664&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	  每輪都喜歡對一些基本的東西裝傻
		  一直問你那是什麼
		  然後嘗試要誘導你到錯誤的方向

		  random shuffle variation

		  string match
		  要求不同的姊髮

		  sql vs nosql
		  mongodb vs cassandro

	  http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=281766&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311

	  第一轮
		  merge n sorted array （忘记了可以用priority tree，两两merge做完后被面试官提醒，也没有重写）
		  nth element in a BST

		  第二轮
		  given[2, 3, 6, 7, 8] array and target T, find the count of all the possible permutations in the candidate array so that the sum of permutations is T.
		  For example, target 5, we have[[2, 3], [3, 2]]. return 2;
	  follow up : combinations instead of permutations.上面的例子, return 1.

		  第三轮.三哥manager， Culture， behavior question.

		  第四轮.Design :
		  API  version management, new version of API published, how to not break old client(without changing code in the client).
		  写LRU

		  求bless

	  http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=176792&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	  今天中午去了ebay家onsite，12点开始，大概四轮，其实我也上确定第一轮算上算。晚上就收到了HR的positive feedback， 真是飞速。

		  1. 第一轮， 跟Hiring manager一起吃个饭，然后到会议室里了解一下情况，大多都是behavior question.
		  2. 第二轮，两道题，一道题是，在一个unsorted number array 里，有一个数字出现概率大于50% 用O(n)时间 和O(1)空间去找到他；
	  http ://wiki.jikexueyuan.com/project/for-offer/question-twenty-nine.html
	  第二题是power(x, n);
  http://www.cnblogs.com/littlepanpc/p/3811373.html
	  3. 第三轮，跟另一个manager谈，大多都是现在的项目，你觉得ebay有什么可以改进的东西什么的。
		  4. 第四轮，两个题， 1. number array，比如[4, 1, 3, 2.....] 按照up, left, down, right, 顺序走，判断是否cross each other;
	  2. delete node in BST.

	  http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=236055&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	  1.让用array实现stack，写完了让我把他变成generic的
		  2.后来让口述bubble sort， selection sort， insertsort， 我说我忘了，能上能换成quick sort 和 merge sort，哥说可以，哥人还是很好的，开头开了几个玩笑气氛就上错。
		  它给的例子我实在口述上来，我就索性自己写了一个quicksort，它go through了一下说可以。
		  3.问linkedlist 怎么实现的
		  4.打印出一个数组里element右边所有值都比他小的所有element，我说两个for从后向前，他说行

	  http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=101186&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	  第一轮：
		  1. Binary Tree Level Order
		  2. a.how to get top 10 frequent words in a small file ?
		  b.how to get top 10 frequent words in a large file(cannot fit into memory) ?
		  c.how to get top n frequent words in a large file(cannot fit into memory, n could be dynamically changed, this function would be called for several times) ?
		  d.how to get top n frequent words in a word stream ?

		  第二轮：
		  1. 问了简历上一个项目，聊了20多分钟，问的偏重设计，很细。
		  2. Decide whether one binary tree is a binary search tree ?

	  http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=184156&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311

			等了一周都没消息，应该是跪了，五轮
			1. 上来问我特长是什么，以后想做什么。题目是给一个array，找k percentile的数，特简单的题，我纠结percentile搞了很久，后来提醒了一下，quickselect搞定
			2.让我介绍一下自己，然后是longest common subarray
		http ://www.geeksforgeeks.org/longest-common-substring/
	  3.他指定了一个project让我说一下。 然后做题，给一个array，求window average
		  4.纯聊天，system design
		  5.外面包装了一个夊杂的描述，实质是求longest increasing subsequence
	  https ://www.youtube.com/watch?v=CE2b_-XfVDk

	  CC150
	  https ://youtu.be/aClxtDcdpsQ
  https ://www.youtube.com/watch?v=rEJzOhC5ZtQ

Select Sort: repeatedly pick the smallest element to append to the result.
	Stable with O(n) extra space, for example using lists
Insert Sort: repeatedly add new element to the sorted result.
	Stable; i.e., does not change the relative order of elements with equal keys
	In - place; i.e., only requires a constant amount O(1) of additional memory space
Bubble Sort: repeatedly compare neighbor pairs and swap if necessary.
Quick Sort
	Is usually done in - place with O(log n) stack space
//////////////////////// end///////////////////////////
#endif

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "eb.h"

using namespace std;
namespace EB {
	int partition(vector<int>& nums, int low, int high)
	{
		int pivot = nums[low];
		int left = low + 1, right = high;

		while (left <= right) {
			if (nums[left] > pivot && nums[right] < pivot)
				swap(nums[left++], nums[right--]);

			if (nums[left] <= pivot)
				++left;

			if (nums[right] >= pivot)
				--right;
		}

		//right must point to the last element which is larger than pivot
		swap(nums[low], nums[right]);
		return right;
	}

	void quickSort(vector<int>& nums, int first, int last)
	{
		int pivotElement;

		if (first < last)
		{
			pivotElement = partition(nums, first, last);
			quickSort(nums, first, pivotElement - 1);
			quickSort(nums, pivotElement + 1, last);
		}
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

	class TreeNode {
	public:
		TreeNode(int value) : val(value), left(nullptr), right(nullptr){}

		int val;
		TreeNode* left;
		TreeNode* right;

		TreeNode* treeDeserial(const string& str) {
			stringstream in(str);

			return deserial(in);
		}

		string treeSerial(TreeNode* root) {
			stringstream out;
			serial(root, out);
			return out.str();
		}

		TreeNode* deserial(stringstream& in) {
			string str;
			in >> str;
			if (str == "#")
				return nullptr;

			TreeNode* node = new TreeNode(stoi(str));

			node->left = deserial(in);
			node->right = deserial(in);
			return node;
		}

		void serial(TreeNode* root, stringstream& out) {
			if (nullptr == root) {
				out << "# ";
				return;
			}

			out << root->val << " ";
			serial(root->left, out);
			serial(root->right, out);
		}

		static void test() {
			TreeNode* ins = new TreeNode(0);
			TreeNode node1(1);
			TreeNode node2(2);
			TreeNode node3(3);
			TreeNode node4(4);

			node2.left = &node1;
			node2.right = &node3;
			node3.right = &node4;

			string str = ins->treeSerial(&node2);
			cout << str << endl;
			TreeNode* root = ins->treeDeserial(str);
			delete ins;
			ins = nullptr;
		}
	};

	class ListNode
	{
	public:
		ListNode(int value) :val(value), next(nullptr) {}
		int val;
		ListNode* next;
	};


	ListNode* reverPairInList1(ListNode* head) {
		if (nullptr == head || nullptr == head->next)
			return head;

		ListNode* newhead = head->next;
		ListNode* next = newhead->next;
		newhead->next = head;
		head->next = reverPairInList1(next);
		return newhead;
	}

	ListNode* reverPairInList2(ListNode* head) {
		if (nullptr == head || nullptr == head->next)
			return head;

		ListNode dummy(0);
		ListNode* pre = &dummy;
		ListNode* next = nullptr;
		ListNode* cur = head;
		while (cur) {
			pre->next = cur;
			
			if (nullptr == cur->next)
				break;

			next = cur->next->next;
			pre->next = cur->next;
			pre->next->next = cur;

			cur->next = next;
			pre = cur;
			cur = next;
		}

		return dummy.next;
	}

	//http://www.geeksforgeeks.org/reservoir-sampling/
	void selectKItems(vector<int> data, int k){
		int i = 0;
		// reservoir[] is the output array. Initialize it with
		// first k elements from stream[]
		vector<int> reservoir(k);
		for (i = 0; i < k; i++)
			reservoir[i] = data[i];

		// Use a different seed value so that we don't get
		// same result each time we run this program
		//srand(time(NULL));

		// Iterate from the (k+1)th element to nth element
		for (; i < data.size(); i++)
		{
			// Pick a random index from 0 to i.
			int j = rand() % (i + 1);

			// If the randomly  picked index is smaller than k, then replace
			// the element present at the index with new element from stream
			if (j < k)
				reservoir[j] = data[i];
		}
	}

	//https://leetcode.com/problems/maximum-subarray/description/
	int maxSubArray(vector<int> nums) {
		if (nums.empty())
			return 0;

		int sum = 0;
		int res = nums[0];
		for (int i = 0; i < nums.size(); ++i) {
			if (sum > 0)
				sum += nums[i];
			else
				sum = nums[i];

			res = max(res, sum);
		}

		return res;
	}

	//http://www.geeksforgeeks.org/check-binary-representation-number-palindrome/
	bool isKthBitSet(int x, int k){
		return (x & (1 << (k - 1))) ? true : false;
	}

	bool isPalindrome(unsigned int x){
		int l = 1; // Initialize left position
		int r = sizeof(int) * 8; // initialize right position

		// One by one compare bits
		while (l < r){
			if (isKthBitSet(x, l) != isKthBitSet(x, r))
				return false;

			l++, r--;
		}

		return true;
	}
	class ReverseString
	{
	public:
		string reverseString(string s) {
			string str;
			int len = s.size();
			str.resize(len);
			for (int i = len - 1; i >= 0; --i)
				str[len - i - 1] = s[i];

			return str;
		}

		void reverse(string &s, int i, int j) {
			while (j - i > 1) {
				char t = s[i];
				s[i] = s[j - 1];
				s[j - 1] = t;
				++i; --j;
			}
		}

		void reverseWords(string &s) {
			// first remove all leading, tailing and duplicate spaces
			bool hasMetChar = false;
			int len = 0;
			for (int j = 0; j < s.length(); j++) {
				if (!hasMetChar) {
					if (s[j] != ' '){
						hasMetChar = true;
						s[len++] = s[j];
					}
				}
				else if (s[j] != ' ' || s[len - 1] != ' ') {
					s[len++] = s[j];
				}
			}
			// remove the last space
			if (len > 0 && s[len - 1] == ' ') {
				--len;
			}
			// shrink the string
			s.resize(len);

			// reverse each word
			for (int i = -1, j = 0; j <= s.length(); ++j) {
				if (s[j] == ' ' || s[j] == '\0') {
					reverse(s, i + 1, j);
					i = j;
				}
			}
			// reverse the whole string
			reverse(s, 0, s.length());
		}
	};

	//merger 3 unsorted no duplcate integer array
	//1. 可以各自排序，然后两两合并
	//2. 可以用hash去重，然后再排序
	vector<int> mergefor3(vector<int> num1, vector<int> num2, vector<int> num3) {
		unordered_set<int> data;
		for (auto it : num1)
			data.insert(it);

		for (auto it : num2)
			data.insert(it);

		for (auto it : num3)
			data.insert(it);

		vector<int> res(data.begin(), data.end());
		
		sort(res.begin(), res.end());
		return res;
	}

	//http://www.algolist.net/Data_structures/Binary_search_tree/Insertion
	TreeNode* addtoBST(int val, TreeNode* root) {
		if (nullptr == root) {
			root = new TreeNode(val);
			return root;
		}

		if (val < root->val) {
			if (nullptr == root->left)
				root->left = new TreeNode(val);
			else
				addtoBST(val, root->left);
		}
		else {
			if (nullptr == root->right)
				root->right = new TreeNode(val);
			else
				addtoBST(val, root->right);
		}

		return root;
	}

	TreeNode* arraytoBST(vector<int> nums) {
		if (nums.empty())
			return nullptr;
		TreeNode* root = nullptr;
		
		root = addtoBST(nums[0], root);
		
		for (int i = 1; i < nums.size(); ++i)
			addtoBST(nums[i], root);

		return root;
	}

	//phone keyboard
	vector<string> letterCombinations(string digits) {
		vector<string> res;
		if (digits.empty())
			return res;

		res.push_back("");
		vector<string> strmap = {"", "", "abc", "def","ghi","jkl","mno","pqrs","tuv","wxyz" };
		
		for (auto it : digits) {
			if (it < '2' || it > '9')
				continue;

			string candidates = strmap[it - '0'];
			vector<string> tmp;
			for (auto pre : res)
				for (auto next : candidates)
					tmp.push_back(pre + next);

			res.swap(tmp);
		}
		
		return res;
	}
	//https://stackoverflow.com/questions/23673812/algorithm-for-largest-word-formed-from-perodic-table-elements
	void EB_main(){
		{
			vector<int> nums1 = { 5 , 4, 6, 3, 1, 8 };
			TreeNode* root = arraytoBST(nums1);
			cout << root->val << endl;
			//int i = 1000000000b;
			//int foo = 0b00100101;
			cout << isPalindrome(0xFFFFFFFF) << endl;
			cout << isPalindrome(0xFFFEFFFF) << endl;
			ListNode node1(1);
			ListNode node2(2);
			ListNode node3(3);
			ListNode node4(4);
			ListNode node5(5);

			node1.next = &node2;
			node2.next = &node3;
			node3.next = &node4;
			node4.next = &node5;

			ListNode* after1 = reverPairInList1(&node1);
			ListNode* after2 = reverPairInList1(after1);

			after1 = reverPairInList2(&node1);
			after2 = reverPairInList2(after1);

			int i;
			i = 0;
		}
		TreeNode::test();
		int i = 0;
	}
}