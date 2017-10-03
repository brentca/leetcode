#if 0
//////////////////////// begin///////////////////////////.
polynomial exponent factorial
http://mm.fancymore.com/reading/java-threadpools.html

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=293203&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	第一轮：刚开始烙印出了JavaScript的 题，我说我prefer用Java面试，因为之前已和recruiter说了，不知道是不是坑。
	1）merger 3 unsorted no duplcate integer array
	2）a stream of integers, find the smallest.from

	第二轮：
	1）serialize and de - serialize bt
	2）swap pairs in linked list
	follow up : use recursive

	第三轮：
	1) choose k randome value equally from a stream of integers.
	//http://www.geeksforgeeks.org/reservoir-sampling/
	2) maximum subarray, array contains positvie and negative integers.

	第四轮：
	1） Palindrome binary number
	2）reverse String

第五轮 :
	1）periodic table, longest englishwords
	2）BQs

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=293839&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	第一轮：土耳其小哥，问了简历＋给了一个array num, 让转化成BST
	第二轮 : 中国小哥，人很好，特别nice，longest panlindrome subsequence 我写了基础解法，让优化成o(nlongn) (lc 300)
	第三轮：印度manager，leetcode phone keyboard 那道题的变形
	第四轮：烙印，斐波那契数列，shuffle an array，又问了简历 project和引申问题 O(1.6n)

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=223664&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	每輪都喜歡對一些基本的東西裝傻,一直問你那是什麼,然後嘗試要誘導你到錯誤的方向
	random shuffle variation

	string match
	要求不同的姊髮

	sql vs nosql
	mongodb vs cassandro

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=281766&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	第一轮
	merge n sorted array （忘记了可以用priority tree，两两merge做完后被面试官提醒，也没有重写）
	nth element in a BST

	第二轮
	given[2, 3, 6, 7, 8] array and target T, find the count of all the possible permutations in the candidate array so that the sum of permutations is T.
	For example, target 5, we have[[2, 3], [3, 2]]. return 2;
	//for simple use two loop or can use O(n) space for unoredered_set to keep track. if have duplicable, unordered_map
	follow up : combinations instead of permutations.上面的例子, return 1.
		  
	第三轮.三哥manager， Culture， behavior question.

	第四轮.Design :
	API  version management, new version of API published, how to not break old client(without changing code in the client).
	写LRU

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=176792&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	今天中午去了ebay家onsite，12点开始，大概四轮，其实我也上确定第一轮算上算。晚上就收到了HR的positive feedback， 真是飞速。

	1. 第一轮， 跟Hiring manager一起吃个饭，然后到会议室里了解一下情况，大多都是behavior question.
	2. 第二轮，两道题，一道题是，在一个unsorted number array 里，有一个数字出现概率大于50% 用O(n)时间 和O(1)空间去找到他；
	http://wiki.jikexueyuan.com/project/for-offer/question-twenty-nine.html
	可以考虑在遍历数组的时候保存两个值： 一个是数组中的一个数字， 一个是次数。当我们遍历到下～个数字的时候，如果下一个数字和我们之前保存的数字相同，则次数加 l ：如果下一个数字和我们之前保存的数字，不同，则次数减 1 。

	第二题是power(x, n);
	http://www.cnblogs.com/littlepanpc/p/3811373.html
	3. 第三轮，跟另一个manager谈，大多都是现在的项目，你觉得ebay有什么可以改进的东西什么的。
	4. 第四轮，两个题， 1. number array，比如[4, 1, 3, 2.....] 按照up, left, down, right, 顺序走，判断是否cross each other;
	//use hash to keep very passed point's position, for every move will check the hash
	2. delete node in BST.

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=236055&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	1.让用array实现stack，写完了让我把他变成generic的
	2.后来让口述bubble sort， selection sort， insertsort， 我说我忘了，能上能换成quick sort 和 merge sort，哥说可以，哥人还是很好的，开头开了几个玩笑气氛就上错。
	它给的例子我实在口述上来，我就索性自己写了一个quicksort，它go through了一下说可以。
	3.问linkedlist 怎么实现的
		LinkedList 和 ArrayList 一样，都实现了 List 接口，但其内部的数据结构有本质的不同。
		LinkedList 是基于链表实现的（通过名字也能区分开来），所以它的插入和删除操作比 ArrayList 
		更加高效。但也是由于其为基于链表的，所以随机访问的效率要比 ArrayList 差。
		LinkedList 是基于链表结构实现，所以在类中包含了 first 和 last 两个指针(Node)。Node 
		中包含了上一个节点和下一个节点的引用，这样就构成了双向的链表。每个 Node 只能知道自己的前
		一个节点和后一个节点，但对于链表来说，这已经足够了。
		ConcurrentHashMap允许多个修改操作并发进行，其关键在于使用了锁分离技术。它使用了多个锁来控制对hash表的不同部分进行的修改。
		ConcurrentHashMap内部使用段(Segment)来表示这些不同的部分，每个段其实就是一个小的hash table，它们有自己的锁。只要多个
		修改操作发生在不同的段上，它们就可以并发进行。
	4.打印出一个数组里element右边所有值都比他小的所有element，我说两个for从后向前，他说行

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=101186&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	第一轮：
		1. Binary Tree Level Order
		2. a.how to get top 10 frequent words in a small file ?
		b.how to get top 10 frequent words in a large file(cannot fit into memory) ?
		c.how to get top n frequent words in a large file(cannot fit into memory, n could be dynamically changed, this function would be called for several times) ?
		d.how to get top n frequent words in a word stream ?
		http://www.geeksforgeeks.org/find-the-k-most-frequent-words-from-a-file/
		We can use Trie and Min Heap. 
	第二轮：
		1. 问了简历上一个项目，聊了20多分钟，问的偏重设计，很细。
		2. Decide whether one binary tree is a binary search tree ?

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=184156&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	等了一周都没消息，应该是跪了，五轮
	1.上来问我特长是什么，以后想做什么。题目是给一个array，找k percentile的数，特简单的题，我纠结percentile搞了很久，后来提醒了一下，quickselect搞定
		The kth percentile is a value in a data set that splits the data into two pieces : The 
		lower piece contains k percent of the data, and the upper piece contains the rest of 
		the data(which amounts to[100 – k] percent, because the total amount of data is 100 % ).
		Note : k is any number between 0 and 100.
	2.让我介绍一下自己，然后是longest common subarray
		http://www.geeksforgeeks.org/longest-common-substring/
	3.他指定了一个project让我说一下。 然后做题，给一个array，求window average
	4.纯聊天，system design
	5.外面包装了一个夊杂的描述，实质是求longest increasing subsequence
	  https://www.youtube.com/watch?v=CE2b_-XfVDk

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=187188&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	1.  Print a Binary Tree in Vertical Order。一个二叉树从左到右从上到下遍历，不是层级遍历。想象每个节点有一个xy坐标，先输出x小的，再大的。x坐标一样的，先输出y上面的.geeksforgeeks 上原题.
	2. a) 判断一个string是否是 valid的 IPv4 地址 bool isValid(string str)    b) 设计一个Cache系统，如果是分布式的cache系统要怎么设计，设计的时候要考虑什么因素
	3. 给一个 二叉树， 每个节点除了左右指针还有parent指针，给任意两个节点找最近公共祖先。follow up 是要求用O(1)的空间复杂度和O(logN)的时间复杂度
	4. 海量query，要求统计query的次数。follow up 如何在有限内存无法hold所有的query文件下统计词频， hash 分桶。
	follow up2， 建立倒排索引，query string 对应多个user ID, 如何找出两个query的共有user id， 即找 两个user id 集合的交集。 Naive 方案O(N2), follow up3, 如果user id list有序，要求O(N)的时间复杂度

//10. Vending machine
//https://ece.uwaterloo.ca/~se464/06ST/lecture/05_oo-design.pdf
//http://javarevisited.blogspot.ca/2016/06/design-vending-machine-in-java.html
/*
You need to design a Vending Machine which
Accepts coins of 1,5,10,25 Cents i.e. penny, nickel, dime, and quarter.
Allow user to select products Coke(25), Pepsi(35), Soda(45)
Allow user to take refund by canceling the request.
Return selected product and remaining change if any
Allow reset operation for vending machine supplier.
VendingMachine
It defines the public API of vending machine, usually all high-level functionality should go in this class

VendingMachineImpl
Sample implementation of Vending Machine

VendingMachineFactory
A Factory class to create different kinds of Vending Machine

Item
Java Enum to represent Item served by Vending Machine

Inventory
Java class to represent an Inventory, used for creating case and item inventory inside Vending Machine

Coin
Another Java Enum to represent Coins supported by Vending Machine

Bucket
A parameterized class to hold two objects. It's kind of Pair class.


public interface VendingMachine {
public long selectItemAndGetPrice(Item item);
public void insertCoin(Coin coin);
public List<Coin> refund();
public Bucket<Item, List<Coin>> collectItemAndChange();
public void reset();
}

public class VendingMachineImpl implements VendingMachine {
private Inventory<Coin> cashInventory = new Inventory<Coin>();
private Inventory<Item> itemInventory = new Inventory<Item>();
private long totalSales;
private Item currentItem;
private long currentBalance;


long selectItemAndGetPrice(Item item) {
	if(itemInventory.hasItem(item)){
		currentItem = item;
		return currentItem.getPrice();
	}
	throw new SoldOutException("Sold Out, Please buy another item");
}

void insertCoin(Coin coin) {
	currentBalance = currentBalance + coin.getDenomination();
	cashInventory.add(coin);
}

Bucket<Item, List<Coin>> collectItemAndChange() {
	Item item = collectItem();
	totalSales = totalSales + currentItem.getPrice();

	List<Coin> change = collectChange();

	return new Bucket<Item, List<Coin>>(item, change);
}

Item collectItem() throws NotSufficientChangeException,
	NotFullPaidException{
		if(isFullPaid()){
		if(hasSufficientChange()){
			itemInventory.deduct(currentItem);
			return currentItem;
		}
		throw new NotSufficientChangeException("Not Sufficient change in
		Inventory");
	}
	long remainingBalance = currentItem.getPrice() - currentBalance;
	throw new NotFullPaidException("Price not full paid, remaining : ",
	remainingBalance);
}

List<Coin> collectChange() {
	long changeAmount = currentBalance - currentItem.getPrice();
	List<Coin> change = getChange(changeAmount);
	updateCashInventory(change);
	currentBalance = 0;
	currentItem = null;
	return change;
}

List<Coin> refund(){
	List<Coin> refund = getChange(currentBalance);
	updateCashInventory(refund);
	currentBalance = 0;
	currentItem = null;
	return refund;
}

private boolean isFullPaid() {
	if(currentBalance >= currentItem.getPrice()){
		return true;
	}
	return false;
}

List<Coin> getChange(long amount) throws NotSufficientChangeException{
	List<Coin> changes = Collections.EMPTY_LIST;

	if(amount > 0){
		changes = new ArrayList<Coin>();
		long balance = amount;
		while(balance > 0){
		if(balance >= Coin.QUARTER.getDenomination()
			&& cashInventory.hasItem(Coin.QUARTER)){
			changes.add(Coin.QUARTER);
			balance = balance - Coin.QUARTER.getDenomination();
			continue;
		} else if(balance >= Coin.DIME.getDenomination()
			&& cashInventory.hasItem(Coin.DIME)) {
			changes.add(Coin.DIME);
			balance = balance - Coin.DIME.getDenomination();
			continue;
		}else if(balance >= Coin.NICKLE.getDenomination()
			&& cashInventory.hasItem(Coin.NICKLE)) {
			changes.add(Coin.NICKLE);
			balance = balance - Coin.NICKLE.getDenomination();
			continue;
		}else if(balance >= Coin.PENNY.getDenomination()
			&& cashInventory.hasItem(Coin.PENNY)) {
			changes.add(Coin.PENNY);
			balance = balance - Coin.PENNY.getDenomination();
			continue;
		}else{
			throw new NotSufficientChangeException("NotSufficientChange,
			Please try another product");
		}
	}

	return changes;
}

public void reset(){
	cashInventory.clear();
	itemInventory.clear();
	totalSales = 0;
	currentItem = null;
	currentBalance = 0;
}

void printStats(){
	System.out.println("Total Sales : " + totalSales);
	System.out.println("Current Item Inventory : " + itemInventory);
	System.out.println("Current Cash Inventory : " + cashInventory);
}

boolean hasSufficientChange()
boolean hasSufficientChangeForAmount(long amount)
void updateCashInventory(List change)
long getTotalSales()
....
}

Read more: http://javarevisited.blogspot.com/2016/06/design-vending-machine-in-java.html#ixzz4u8Ku9IPv
*/

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=291573&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
Interviewer是个三姐， 人还不错。先是问了几个很基础的java问题，然后开始做题。
第一题：
how to check if a string is Palindrome.
我就用two pointer做的，她也没说啥。到面试快结束时，她说可以reverse string然后比较是否相等。

第二题：
LC 5: Longest Palindromic Substring由于题目刷的不好，开始时没想出来dp解法，就用two pointer做了一下。
然后她问能不能用dp，想了一两分钟，然后在google doc里给她讲我的dp思路，然后写出来。

第三题：
也很简单，check if a Integer is Palindrome.
我也没能给出leetcode上vote最多的那个方法，还是reverse然后比较大小，告诉她要处理溢出和负数的情况。

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=223971&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
Onsite:
1. OOD 的5个principle 逐一解释.....https ://scotch.io/bar-talk/s-o-l ... ect-oriented-design
2. 简化后背景，其实就是两个array的intersection&union
3. 老板Lunch。 都是一些很简单的算法题... 和Top k一个难度.
4. 简化背景后就是permutation
5. (坑)LC原题 Gas Station--> 虽然做过，但是不是高频题，不常看, 不太熟练，坑坑洼洼的做好了。 烙印还要求用数学证明一下....需要面试Search组的童鞋建议看一下吧...
6. refactor一段有很多if block的代码。 + first missing integer

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=270887&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D16%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
1 given a num, find the immediate larger element in a BST.num may be not in the BST
2 maximum pairs of valid ‘(’ and ‘)’ in a string s. ((()))) -> 3()()() -> 1
If s has invaid pairs e.g. ((), throw exception.

CC150
https://youtu.be/aClxtDcdpsQ
https://www.youtube.com/watch?v=rEJzOhC5ZtQ

Deadlock

Deadlock describes a situation where two or more threads are blocked forever, 
waiting for each other.Deadlock occurs when multiple threads need the same 
locks but obtain them in different order.A Java multithreaded program may 
suffer from the deadlock condition because the synchronized keyword causes 
the executing thread to block while waiting for the lock, or monitor, 
associated with the specified object.Here is an example.

One of the best ways to prevent the potential for deadlock is to avoid acquiring
more than one lock at a time, which is often practical.
Following are some techniques available that help mitigate the deadlock problem:
1)Non Overlapping Locks
2)Lock Ordering
3)Lock Timeout
4)Single Thread

Difference between final, finally and finalize
Final is a keyword.
Finally is a block.
Finalize is a method.

Final is used to apply restrictions on class, method and variable.Final class 
can't be inherited, final method can't be overridden and final variable value 
can't be changed.

Finally is used to place important code, it will be executed whether exception 
is handled or not.

Finalize is used to perform clean up processing just before object is garbage 
collected.

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
#include <unordered_map>
#include <time.h>
#include <queue>
#include <tuple>
#include <functional>
#include <array>
#include <map>
#include "eb.h"

using namespace std;
namespace EB {
	int partition(vector<int>& nums, int low, int high){
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

	void quickSort(vector<int>& nums, int first, int last){
		int pivotElement;

		if (first < last) {
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

	// O(n) + k * long(n)
	int findKthLargest(vector<int>& nums, int k) {
		int len = nums.size();
		if (k < 1 || k > len)
			return 0;
		//O(n)
		for (int i = len / 2; i >= 0; --i)
			heapadjust(nums, i, len - 1);

		//O(klog(n))
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

TreeNode* findimLagerElementBST(TreeNode* root, int num) {
	TreeNode* res = nullptr;

	if (nullptr == root)
		return res;

	while (root && num > root->val)
		root = root->right;

	if (root) {
		if (root->val == num) {
			res = root->right;
			TreeNode* pre = res;
			while (pre) {
				res = pre;
				pre = res->left;
			}
		}
		else
			res = root;
	}

	return res;
}

class ListNode{
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
//Case 1: For last n-k stream items, i.e., 
//[Probability that one of the first k indexes is picked in iteration for 
//stream[n - 2]] X[Probability that the index picked in iteration for stream[n - 1] 
//for stream[i] where k <= i < n
//stream[n-2] ] = [k/(n-1)]*[(n-1)/n] = k/n.
//Case 2: For first k stream items, i.e., for stream[i] where 0 <= i < k 
//The probability that an item from stream[0..k-1] is in final array = Probability that 
//the item is not picked when items stream[k], stream[k+1], …. stream[n-1] are considered 
//= [k/(k+1)] x [(k+1)/(k+2)] x [(k+2)/(k+3)] x … x [(n-1)/n] = k/n
void selectKItems(vector<int> data, int k) {
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
	for (; i < data.size(); i++) {
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

class ReverseString {
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
				if (s[j] != ' ') {
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

	if (root->val == val)
		return root;
	else if (val < root->val) {
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

//http://www.geeksforgeeks.org/shuffle-a-given-array/
//The probability of ith element going to second position = (probability that ith element is not picked in previous iteration) x (probability that ith element is picked in this iteration)
//So the probability = ((n - 1) / n) x(1 / (n - 1)) = 1 / n
void shuffle(vector<int> m_cards) {
	int len = m_cards.size();

	for (int i = 0; i < len; ++i) {
		int j = rand() % (len - i) + i;
		swap(m_cards[j], m_cards[i]);
	}
}

TreeNode* deleteNode(TreeNode* root, int key) {
	TreeNode* result = NULL;
	if (NULL == root)
		return root;

	if (root->val == key) {
		if (NULL == root->right) {
			result = root->left;
			delete root;
			return result;
		}
		else if (NULL == root->left){
			result = root->right;
			delete root;
			return result;
		}
		else {
			TreeNode* cur = root->right;
			while (cur->left)
				cur = cur->left;
			swap(cur->val, root->val);
			root->right = deleteNode(root->right, key);
			return root;
		}
	}
	else if (root->val > key)
		root->left = deleteNode(root->left, key);
	else
		root->right = deleteNode(root->right, key);


	return root;
}

//https://stackoverflow.com/questions/22055495/algorithm-to-merge-multiple-sorted-sequences-into-one-sorted-sequence-in-c
vector<int> mergeNArray(vector<vector<int>> nums) {
	typedef tuple <int, vector<int>::iterator, vector<int>::iterator> element;
	priority_queue<element, vector<element>, greater<element>> heaps;

	//must use &, otherwise it will be a copy and its iterator will be invalid
	for (auto& it : nums) {
		if (!nums.empty())
			heaps.emplace(it.front(), it.begin(), it.end());
	}

	vector<int> res;
	while (!heaps.empty()) {
		auto temp = heaps.top();
		heaps.pop();
			
		if (get<1>(temp) != get<2>(temp)) {
			res.push_back(get<0>(temp));
			++(get<1>(temp));
			get<0>(temp) = *get<1>(temp);
			heaps.push(temp);
			//heaps.emplace(*get<1>(temp), get<1>(temp), get<2>(temp));
		}
	}

	copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout));
	return res;
}
	
class LRUCache {
public:
	LRUCache(int capacity) {
		cap = capacity;
		cur = 0;
	}

	int get(int key) {
		if (0 == hsh.count(key))
			return -1;

		//auto it = hsh.find(key);

		data.erase(hsh[key].second);
		data.push_front(key);
		//it->second.second = data.begin();
		hsh[key] = make_pair(hsh[key].first, data.begin());
		return hsh[key].first;
	}

	void put(int key, int value) {
		if (hsh.count(key)) {
			get(key);
			hsh[key].first = value;
		}
		else {
			++cur;
			if (cur > cap) {
				int oldkey = data.back();
				data.pop_back();
				hsh.erase(oldkey);
				cur = cap;
			}

			data.push_front(key);
			hsh[key] = make_pair(value, data.begin());
		}
	}

	int cap;
	int cur;
	list<int> data;
	unordered_map<int, pair<int, list<int>::iterator>> hsh;
};

//http://www.cnblogs.com/littlepanpc/p/3811373.html
int ipow1(int base, int exp) {
	int result = 1;
	while (exp != 0) {
		if ((exp & 1) == 1) {
			result *= base;
		}
		exp >>= 1;
		base *= base;
	}
	return result;
}

/* when exp is bigger than zero */
long ipow2(long base, long exp) {
	if (exp == 0) {
		return 1;
	}
	if (exp == 1) {
		return base;
	}

	if (exp % 2 == 0) {
		long half = ipow2(base, exp / 2);
		return half * half;
	}
	else {
		long half = ipow2(base, (exp - 1) / 2);
		return base * half * half;
	}
}

template <class T> 
class MyStack {
public:
	MyStack(int max) {
		curidx = 0;
		data.resize(max);
	}

	void push(T node) {
		if (curidx < data.size())
			data[curidx++] = node;
	}

	T top() {
		if (isempty())
			return T(-1);
		else
			return data[curidx-1];
	}
	bool isfull() {
		return curidx == data.size();
	}

	bool isempty() {
		return curidx == 0;
	}

	void pop() {
		if (!isempty())
			--curidx;
	}

private:
	const int STACK_CAP = 100;
	vector<T> data;
	int curidx;
};

class Solution98 {
public:
	bool checkBST(TreeNode* root, int max_val, int min_val) {
		if (NULL == root)
			return true;

		if (root->val >= min_val && root->val <= max_val) {
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

//给 3 输出 111,112,113,121,122,123,132,133,211,212,213,221,222,223,
//231,232,233,311,312,313,321,322,323,331,332,333 (27个数)
void dfs(vector<vector<int> > &results, int n, vector<int> & sol) {
	if (sol.size() == n) {
		results.push_back(sol);
		return;
	}

	for (int i = 1; i <= n; i++) {
		sol.push_back(i);
		dfs(results, n, sol);
		sol.pop_back();
	}
}

vector<vector<int> > getSets(int n) {
	vector<vector<int> > results;
	if (n == 0) return results; 
		vector<int> sol;
	dfs(results, n, sol);
	return results;
}

//Longest Palindromic Subsequence
//https://www.youtube.com/watch?v=_nCsPn7_OgI
//use n*n matrix, dp[i][j] means max palindromic subsequence length of a[i...j]
//if a[i] == a[j], then dp[i][j] = dp[i+1][j-1] + 2
//else dp[i][j] = max(dp[i][j-1], dp[i+1][j])

/*314. Binary Tree Vertical Order Traversal (medium)
https://leetcode.com/problems/binary-tree-vertical-order-traversal/
https://discuss.leetcode.com/topic/31954/5ms-java-clean-solution
*/
class Solution314 {
public:
	vector<vector<int>> verticalOrder(TreeNode* root) {
		vector<vector<int>> result;

		if (nullptr == root)
			return result;

		queue<pair<TreeNode*, int>> que;
		map<int, vector<int>> data;

		que.push({ root , 0 });
		while (!que.empty()) {
			TreeNode* cur = que.front().first;
			int val = que.front().second;

			que.pop();
			data[val].push_back(root->val);
			if (nullptr != cur->left)
				que.push({ cur->left , val - 1 });

			if (nullptr != cur->right)
				que.push({ cur->right , val + 1 });
		}

		for (auto item : data)
			result.push_back(item.second);

		return result;
	}
};
/*314. Binary Tree Vertical Order Traversal end */

TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
	//iterative solution

	unordered_map<TreeNode*, TreeNode*> mm;
	mm[root] = NULL;
	queue<TreeNode*> qq;
	qq.push(root);

	//get the parent child nodes
	while (mm.count(p) == 0 || mm.count(q) == 0) {
		TreeNode* tmp = qq.front();
		qq.pop();
		if (tmp->left) {
			mm[tmp->left] = tmp;
			qq.push(tmp->left);
		}
		if (tmp->right) {
			mm[tmp->right] = tmp;
			qq.push(tmp->right);
		}
	}

	//get path from root to p
	unordered_set<TreeNode*> ss;
	while (p != NULL) {
		ss.insert(p);
		p = mm[p];
	}

	//check the lowerst common parent in above path
	while (ss.count(q) == 0) {
		q = mm[q];
	}

	return q;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if (NULL == root || p == root || q == root)
		return root;

	TreeNode* left = lowestCommonAncestor(root->left, p, q);
	TreeNode* right = lowestCommonAncestor(root->right, p, q);

	return left ? (right ? root : left) : right;
}

/*295. Find Median from Data Stream (hard)*/
class MedianFinder295 {
public:
	// Adds a number into the data structure.
	void addNum(int num) {
		small.push(num);
		large.push(-small.top());
		small.pop();

		if (large.size() > small.size()) {
			small.push(-large.top());
			large.pop();
		}
	}

	// Returns the median of current data stream
	double findMedian() {
		return small.size() > large.size() ? small.top() : (small.top() - large.top()) / 2.0;
	}

	priority_queue<long> small, large;

	static void main() {
		MedianFinder295* test = new MedianFinder295;
		double result;

		test->addNum(1);
		test->addNum(2);
		result = test->findMedian();

		delete test;
	}
};

//longest substring without repeating character
class Solution3 {
public:
	int lengthOfLongestSubstring(string s) {
		vector<int> pos(256, -1);

		int result = 0;
		int offset = 0;
		for (int i = 0; i < s.size(); ++i) {
			offset = max(pos[s[i]] + 1, offset);

			result = max(result, i - offset + 1);
			pos[s[i]] = i;
		}

		return result;
	}
};

class Solution139 {
public:
	bool wordBreak(string s, unordered_set<string>& wordDict) {
		if (wordDict.empty())
			return false;

		vector<int> dp(s.size() + 1, false);
		dp[0] = true;

		for (int i = 1; i <= s.size(); ++i) {
			for (int j = i - 1; j >= 0; --j) {
				if (dp[j]) {
					string word = s.substr(j, i - j);
					if (wordDict.find(word) != wordDict.end()) {
						dp[i] = true;
						break;
					}
				}
			}
		}

		return dp[s.size()];
	}
};

class Solution264 {
public:
	int nthUglyNumber(int n) {
		if (n <= 0) return false; // get rid of corner cases 
		if (n == 1) return true; // base case
		int t2 = 0, t3 = 0, t5 = 0; //pointers for 2, 3, 5
		vector<int> k(n);
		k[0] = 1;
		for (int i = 1; i < n; i++) {
			k[i] = min(k[t2] * 2, min(k[t3] * 3, k[t5] * 5));
			if (k[i] == k[t2] * 2) t2++;
			if (k[i] == k[t3] * 3) t3++;
			if (k[i] == k[t5] * 5) t5++;
		}
		return k[n - 1];
	}
};

//Repeated Substring Pattern
class Solution459 {
public:
	//Roughly speaking, dp[i+1] stores the maximum number of characters that the string is repeating itself up to position i.
	//Therefore, if a string repeats a length 5 substring 4 times, then the last entry would be of value 15.
	//To check if the string is repeating itself, we just need the last entry to be non - zero and str.size() to divide(str.size() - last entry).
	bool repeatedSubstringPattern(string s) {
		int i = 1, j = 0, len = s.size();
		vector<int> dp(len + 1, 0);

		while (i < len) {
			if (s[i] == s[j])
				dp[++i] = ++j;
			else if (0 == j)
				++i;
			else
				j = dp[j];
		}

		return dp[len] && (dp[len] % (len - dp[len]) == 0);
	}

	bool repeatedSubstringPattern1(string s) {
		int len = s.size();

		for (int i = len / 2; i > 0; --i) {
			int num = len / i;

			if (0 == (len % i)) {
				bool flag = true;
				string str = s.substr(0, i);

				for (int j = 1; j < num; ++j) {
					if (str != s.substr(i * j, i)) {
						flag = false;
						break;
					}
				}

				if (flag)
					return true;
			}
		}

		return false;
	}
};

int LCSubStr(char *X, char *Y, int m, int n) {
	// Create a table to store lengths of longest common suffixes of
	// substrings.   Notethat LCSuff[i][j] contains length of longest
	// common suffix of X[0..i-1] and Y[0..j-1]. The first row and
	// first column entries have no logical meaning, they are used only
	// for simplicity of program
	//int LCSuff[m + 1][n + 1];
	vector<vector<int>> LCSuff(m + 1, vector<int>(n + 1));
	int result = 0;  // To store length of the longest common substring

					 /* Following steps build LCSuff[m+1][n+1] in bottom up fashion. */
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0 || j == 0)
				LCSuff[i][j] = 0;
			else if (X[i - 1] == Y[j - 1]) {
				LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;
				result = max(result, LCSuff[i][j]);
			}
			else LCSuff[i][j] = 0;
		}
	}

	return result;
}

//https://stackoverflow.com/questions/23673812/algorithm-for-largest-word-formed-from-perodic-table-elements
void EB_main() {
	{
		MyStack<int> teststack(3);

		teststack.push(1);
		teststack.push(2);
		teststack.push(3);
		cout << teststack.isempty() << "," << teststack.top() << endl;
		teststack.pop();
		cout << teststack.isempty() << "," << teststack.top() << endl;
		teststack.pop();
		cout << teststack.isempty() << "," << teststack.top() << endl;
		teststack.pop();
		cout << teststack.isempty() << "," << teststack.top() << endl;
		//vector<vector<int>> nums22 = { { 1, 5, 6, 16, 90 }, { 2, 2, 5, 17, 91 } };
		vector<vector<int>> nums22 = { { 1, 5, 6, 16, 90 }, { 2, 5, 17, 91 } };
		//mergeNArray(nums22);


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

/*parking lot design begin*/
enum SpotType {
	T_MOTO,
	T_COMPACT,
	T_SUV
};

class Spot {
public:
	Spot() {}
	~Spot() {}

	bool     m_available;
	SpotType m_type;
};

class Vehicle
{
public:
	Vehicle(int len, int wid) : m_length(len), m_width(wid), m_parked(false), m_spot(nullptr) {};
	~Vehicle(){}

	virtual SpotType getParkType() = 0;

	bool isParked() {
		return m_parked;
	}

	void parkVehicle(Spot* s) {
		m_spot = s;
		m_spot->m_available = false;
		m_parked = true;
	}

	Spot* removeVehicle() {
		if (nullptr != m_spot)
			m_spot->m_available = true;

		m_parked = false;
		Spot* result = m_spot;
		m_spot = nullptr;

		return result;
	}

private:
	int m_length;
	int m_width;
	bool m_parked;
	Spot* m_spot;
};

class Moto : public Vehicle {
public:
	Moto(int len, int wid) : Vehicle(len, wid) {}
	SpotType getParkType() {
		return T_MOTO;
	}
};

class Compact : public Vehicle {
public:
	Compact(int len, int wid) : Vehicle(len, wid) {}
	SpotType getParkType() {
		return T_COMPACT;
	}
};


class Suv : public Vehicle {
public:
	Suv(int len, int wid) : Vehicle(len, wid) {}
	SpotType getParkType() {
		return T_SUV;
	}
};

class Level {
public:
	Level() {};

	void setSpots(vector<Spot*> spots) {
		for (auto item : spots)
			m_spots.push_back(item);
	}

	Spot* findSpot(SpotType type) {
		Spot* result = nullptr;
		for (auto item : m_spots) {
			if (item->m_available && item->m_type == type) {
				result = item;
				break;
			}
		}

		return result;
	}

private:
	vector<Spot*> m_spots;
};

class ParkingLot {
private:
	vector<Level> m_levels;
	static ParkingLot* m_pIns;

	unordered_map<Vehicle*, time_t> m_parkInfo;
	ParkingLot(){}
	// Stop the compiler generating methods of copy the object
	ParkingLot(const ParkingLot &copy);					// Not Implemented
	ParkingLot& operator = (const ParkingLot & copy);    // Not Implemented

	time_t getCurrentTime() {
		return time(0);
	}

	double calculateFee(Vehicle *v) { return 0; }

public:
	static ParkingLot *getInstance(){
		if (nullptr == m_pIns)
			m_pIns = new ParkingLot();

		return m_pIns;
	}

	// NOTE: vehicleEnter and leave is not thread safe!
	bool vehicleEnter(Vehicle *v) {
		Spot* spot = nullptr;

		for (auto level : m_levels) {
			spot = level.findSpot(v->getParkType());
			if (spot)
				break;
		}

		if (nullptr == spot)
			return false;

		v->parkVehicle(spot);
		m_parkInfo[v] = getCurrentTime();
		return true;
	}

	bool vehicleLeave(Vehicle *v, double *fee) {
		*fee = 0;

		if (nullptr == v || !v->isParked())
			return false;

		Spot* spot = v->removeVehicle();
		spot->m_available = true;
		*fee = calculateFee(v);
		m_parkInfo.erase(v);
	}
};

}
/*parking lot design end*/