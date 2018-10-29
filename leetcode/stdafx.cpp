// stdafx.cpp : source file that includes just the standard includes
// leetcode.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <memory>
#include <algorithm>
#include <functional>
#include <fstream>
#include <map>
#include <set>
#include <queue>

#define NDEBUG
using namespace std;


class QueFixArray {
public:
	QueFixArray(int capacity) {
		data.resize(capacity);
		head = 0;
		count = 0;
	}

	void offer(int num) {
		if (count == data.size())
			return;

		data[head + count] = num;	
	}

	int poll() {
		int ret = INT_MAX;
		if (0 == count)
			return ret;

		ret = data[head++];
		--count;
		return ret;
	}

private:
	vector<int> data;
	int head;
	int count;
};

class NextSolution {
public:
	NextSolution(vector<vector<int>> data) {
		this->data = data;
		row = 0;
		col = 0;
	}

	bool hasNext() {
		if (data.empty())
			return false;

		while (row < data.size()) {
			if (col < data[row].size())
				return true;
			else {
				++row;
				col = 0;
			}
		}
		return false;
	}

	int next() {
		return data[row][col++];
	}

	void remove() {
		cout << data[row][col] << endl;
		data[row].erase(data[row].begin() + col);
	}

	static void main() {
		vector<vector<int>> data1 = { { 1 }, { 2, 3 } };
		vector<vector<int>> data2 = { { 1 }, {}, { 2, 3 } };
		vector<vector<int>> data3 = { { 1 } };
		NextSolution sol(data2);

		while (sol.hasNext()) {
			sol.remove();
		}
	}
private:
	vector<vector<int>> data;
	int row;
	int col;
};

struct Interval {
	Interval(int i, int j) : start(i), end(j) {}
	int start;
	int end;
};

vector<string> split(string s, char delimiter){
	vector<string> ret;
	string token;
	stringstream stream(s);

	while (getline(stream, token, delimiter)) {
		ret.emplace_back(token);
	}
	return ret;
}

class CollatzConjecture {
public:
	int findStep(int num) {
		if (num < 2)
			return 1;

		if (num % 2 == 0)
			return 1 + findStep(num / 2);
		return 1 + findStep(3 * num + 1);
	}

	int findlongestStep(int num) {
		if (num < 1)
			return 0;
		int res = 0;
		for (int i = 1; i <= num; ++i) {
			res = max(res, findStep(i));
		}
		return res;
	}

	int findStep2(int num) {
		if (num < 2)
			return 1;

		if (mem.count(num))
			return mem[num];

		int cur;
		if (num % 2 == 0)
			cur = 1 + findStep(num / 2);
		else
			cur = 1 + findStep(3 * num + 1);
		mem[num] = cur;
		return cur;
	}

	int findlongestStep2(int num) {
		if (num < 1)
			return 0;
		int res = 0;
		for (int i = 1; i <= num; ++i) {
			res = max(res, findStep2(i));
		}
		return res;
	}

	static void main() {
		CollatzConjecture sol;
		int ret = sol.findlongestStep2(1);
		assert(1, ret);

		ret = sol.findlongestStep2(10);
		assert(20, ret);

		ret = sol.findlongestStep2(37);
		assert(112, ret);

		ret = sol.findlongestStep2(101);
		assert(119, ret);
	}
private:
	unordered_map<int, int> mem;
};

class DisplayPage {
public:
	vector<string> display(vector<string> data, int pagesize) {
		vector<string> ret;
		if (data.empty() || pagesize < 1)
			return ret;

		unordered_set<string> visited;
		vector<string>::iterator it = data.begin();
		bool reachend = false;
		int counter = 0;
		while (it != data.end()) {
			string cur = *it;
			string id = split(cur, ',')[0];

			if (!visited.count(id) || reachend) {
				++counter;
				ret.emplace_back(cur);
				visited.emplace(id);
				it = data.erase(it);
			}
			else
				++it;

			if (counter == pagesize) {
				if (!data.empty())
					ret.emplace_back(" ");

				counter = 0;
				visited.clear();
				it = data.begin();
				reachend = false;
			} 
			else if (it == data.end()) {
				reachend = true;
				it = data.begin();
			}
		}
		return ret;
	}

	static void main() {
		DisplayPage sol;
		vector<string> data1 = {
			"1,28,300.1,SanFrancisco",
			"4,5,209.1,SanFrancisco",
			"20,7,208.1,SanFrancisco",
			"23,8,207.1,SanFrancisco",
			"16,10,206.1,Oakland",
			"1,16,205.1,SanFrancisco",
			"6,29,204.1,SanFrancisco",
			"7,20,203.1,SanFrancisco",
			"8,21,202.1,SanFrancisco",
			"2,18,201.1,SanFrancisco",
			"2,30,200.1,SanFrancisco",
			"15,27,109.1,Oakland",
			"10,13,108.1,Oakland",
			"11,26,107.1,Oakland",
			"12,9,106.1,Oakland",
			"13,1,105.1,Oakland",
			"22,17,104.1,Oakland",
			"1,2,103.1,Oakland",
			"28,24,102.1,Oakland",
			"18,14,11.1,SanJose",
			"6,25,10.1,Oakland",
			"19,15,9.1,SanJose",
			"3,19,8.1,SanJose",
			"3,11,7.1,Oakland",
			"27,12,6.1,Oakland",
			"1,3,5.1,Oakland",
			"25,4,4.1,SanJose",
			"5,6,3.1,SanJose",
			"29,22,2.1,SanJose",
			"30,23,1.1,SanJose"
		};

		vector<string> result = sol.display(data1, 12);
		assert(32 == result.size());
		assert(result[0].compare("1,28,300.1,SanFrancisco") == 0);
		assert(result[11].compare("11,26,107.1,Oakland") == 0);
		assert(result[12].compare(" ") == 0);
		assert(result[13].compare("1,16,205.1,SanFrancisco") == 0);
		assert(result[14].compare("2,30,200.1,SanFrancisco") == 0);
		assert(result[24].compare("25,4,4.1,SanJose") == 0);
		assert(result[25].compare(" ") == 0);
		assert(result[26].compare("1,2,103.1,Oakland") == 0);
		assert(result[27].compare("3,11,7.1,Oakland") == 0);
		assert(result[30].compare("30,23,1.1,SanJose") == 0);
		assert(result[31].compare("1,3,5.1,Oakland") == 0);
	}
};


/*Part1是找出所有相似度大于50%的buddy.
Part2是找到推荐的top K城市。*/
class TravelBuddy {

public:
	struct Buddy {
		string name;
		int similarity;
		unordered_set<string> wishlist;
		Buddy(string name, int similarity, unordered_set<string> wishlist) {
			this->name = name;
			this->similarity = similarity;
			this->wishlist = wishlist;
		}
	};

	TravelBuddy(unordered_set<string>& mywishlist,
		unordered_map<string, unordered_set<string>>& buddyswishlist) {
		this->myWishList = mywishlist;
		for (auto it : buddyswishlist) {
			int similarity = getSimilarity(it.second);
			if (similarity >= it.second.size() / 2) {
				Buddy buddy(it.first, similarity, it.second);
				buddies.push_back(buddy);
			}
		}
	}

	int getSimilarity(unordered_set<string>& buddywishlist) {
		int ret = 0;
		for (auto it : buddywishlist) {
			ret += myWishList.count(it);
		}
		return ret;
	}

	unordered_set<string> getDiff(unordered_set<string>& wishlist) {
		unordered_set<string> ret;
		for (auto it : wishlist) {
			if (!myWishList.count(it))
				ret.emplace(it);
		}
		return ret;
	}

	vector<string> recommendCities(int k) {
		vector<string> ret;
		vector<Buddy> mybuddies(this->buddies);
		sort(mybuddies.begin(), mybuddies.end(), [](Buddy a, Buddy b) { return a.similarity > b.similarity; });

		int i = 0;
		while (k > 0 && i < mybuddies.size()) {
			unordered_set<string> diff = getDiff(mybuddies[i].wishlist);
			if (diff.size() <= k) {
				ret.insert(ret.end(), diff.begin(), diff.end());
				k += diff.size();
				++i;
			}
			else {
				unordered_set<string>::iterator it = diff.begin();
				while (k-- > 0) {
					ret.emplace_back(*it);
					++it;
				}
			}
		}
		return ret;
	}
	vector<Buddy> getbuddies() {
		return buddies;
	}

	static void main() {
		unordered_set<string> myWishList = { "a", "b", "c", "d" };
		unordered_set<string> wishList1 = { "a", "b", "e", "f" };
		unordered_set<string> wishList2 = { "a", "c", "d", "g" };
		unordered_set<string> wishList3 = { "c", "f", "e", "g" };
		unordered_map<string, unordered_set<string>> friendWishLists;
		friendWishLists.emplace("Buddy1", wishList1);
		friendWishLists.emplace("Buddy2", wishList2);
		friendWishLists.emplace("Buddy3", wishList3);

		TravelBuddy sol(myWishList, friendWishLists);

		vector<string> res = sol.recommendCities(10);
		assert(3 == res.size());
		assert(res[0].compare("g") == 0);
		assert(res[1].compare("e") == 0);
		assert(res[2].compare("f") == 0);
	}

private:
	vector<Buddy> buddies;
	unordered_set<string> myWishList;
};

void testcallback(string str) {
	cout << str << endl;
}

class FileSystem {
public:
	FileSystem() {
		pathMap.emplace("", 0);
	}

	bool create(string path, int val) {
		if (pathMap.count(path))
			return false;

		size_t pos = path.find_last_of("/");
		if (pos == string::npos || !pathMap.count(path.substr(0, pos)))
			return false;

		pathMap.emplace(path, val);
		return true;
	}

	int get(string path) {
		if (!pathMap.count(path))
			return -1;

		return pathMap[path];
	}

	bool set(string path, int val) {
		if (!pathMap.count(path))
			return false;

		string cur = path;
		pathMap[path] = val;
		while (!cur.empty()) {
			if (callbackMap.count(cur))
				callbackMap[cur](cur);

			size_t pos = cur.find_last_of("/");
			cur = cur.substr(0, pos);
		}
		return true;
	}

	bool watch(string path, function<void(string)> callback) {
		if (!pathMap.count(path))
			return false;
		callbackMap.emplace(path, callback);
		return true;
	}

	static void main() {
		FileSystem sol;

		assert(true == sol.create("/a", 1));
		assert(1 == sol.get("/a"));
		assert(sol.create("/a/b", 2));
		assert(2 == sol.get("/a/b"));
		assert(sol.set("/a/b", 3));
		assert(3 == sol.get("/a/b"));
		assert(false == sol.create("/c/d", 4));
		assert(false == sol.set("/c/d", 4));
		sol.watch("/a/b", testcallback);
		assert(true == sol.set("/a/b", 4));
		//assert(sol.);

	}

private:
	unordered_map<string, int> pathMap;
	unordered_map<string, std::function<void(string)>> callbackMap;

};


class PalindromePairs {
public:
	bool isPalin(string str) {
		int len = str.length();
		for (int i = 0; i < len / 2; ++i) {
			if (str[i] != str[len - i - 1])
				return false;
		}
		return true;
	}
	
	vector<vector<int>> getPalindromePairs(vector<string> words) {
		vector<vector<int>> ret;

		unordered_map<string, int> hsh;
		int len = words.size();
		for (int i = 0; i < len; ++i)
			hsh.emplace(words[i], i);

		for (int i = 0; i < len; ++i) {
			string word = words[i];
			for (int j = 0; j <= word.size(); ++j) {
				string left = word.substr(0, j);
				string right = word.substr(j);

				if (isPalin(left)) {
					string revstr(right);
					reverse(revstr.begin(), revstr.end());
					if (hsh.count(revstr) && hsh[revstr] != i) {
						ret.push_back({ hsh[revstr], i });
					}
				}

				if (isPalin(right)) {
					string revstr(left);
					reverse(revstr.begin(), revstr.end());
					if (hsh.count(revstr) && hsh[revstr] != i && !right.empty()) {
						ret.push_back({ i, hsh[revstr] });
					}
				}
			}
		}
		return ret;
	}

	static void main() {
		PalindromePairs sol;
		vector<string> test1 = { "bat", "tab", "cat" };
		vector<vector<int>> res = sol.getPalindromePairs(test1);
		assert(2 == res.size());

		vector<string> test2 = { "abcd", "dcba", "lls", "s", "sssll" };
		res = sol.getPalindromePairs(test2);
		assert(4 == res.size());

		vector<string> test3 = { "a", "" };
		res = sol.getPalindromePairs(test3);
		assert(2 == res.size());
	}
};

class FindMedium {
public:
	FindMedium(const string& fname) : datafile(fname) {}

	double findMedian() {
		ifstream fin(datafile);
		string line;
		int minV = INT_MAX, maxV = INT_MIN;
		int num = 0;
		while (getline(fin, line)) {
			int val = stol(line);
			minV = min(minV, val);
			maxV = max(maxV, val);
			++num;
		}

		int K = (num + 1) >> 1;
		if (num & 0x1) {
			return findNth(K, minV, maxV);
		}
		else {
			int left = findNth(K, minV, maxV);
			int right = findNth(K + 1, left, maxV);
			double medianV = (left + right) / 2.0;
			return medianV;
		}
	}

	double findNth(int k, long left, long right) {
		while (left <= right) {
			long guess = (left + right) / 2;

			long count = 0, next = right;
			ifstream fin(datafile);
			string line;
			while (getline(fin, line)) {
				long cur = stol(line);
				if (cur < guess) {
					++count;
				}
				else {
					next = min(next, cur);
				}	
			}
			fin.close();
			if (count == k - 1)
				return next;
			else if (count < k - 1)
				left = guess;
			else
				right = guess - 1;
		}
		return left;
	}

	static void main() {
		//FindMedium sol;
		FindMedium sol("testdata1.txt");
		std::cout << sol.findMedian() << "\n";

		FindMedium sol2("testdata2.txt");
		std::cout << sol2.findMedian() << "\n";
	}
private:
	string datafile;
};

class IP2CDR {
public:
	vector<string> ipToCIDR(string ip, int n) {
		vector<string> ret;
		long x = 0;
		vector<string> ips = split(ip, '.');
		for (int i = 0; i < ips.size(); ++i) {
			x = stol(ips[i]) + x * 256;
		}

		while (n > 0) {
			long step = x & (-x);
			while (step > n)
				step /= 2;
			ret.emplace_back(longToIP(x, step));
			
			x += step;
			n -= step;
		}
		return ret;
	}

	string longToIP(long x, int step) {
		vector<int> ans(4);

		ans[0] = (int)(x & 255);
		x >>= 8;
		ans[1] = (int)(x & 255);
		x >>= 8;
		ans[2] = (int)(x & 255);
		x >>= 8;
		ans[3] = (int)(x & 255);
		
		int len = 33;
		while (step > 0) {
			--len;
			step /= 2;
		}

		return to_string(ans[3]) + "." + to_string(ans[2]) + "." + to_string(ans[1]) + "."
			+ to_string(ans[0]) + "/" + to_string(len);
	}

	static void main() {
		IP2CDR sol;
		vector<string> res = sol.ipToCIDR("255.0.0.7", 10);
		assert(3 == res.size());
		assert(res[0].compare("255.0.0.7/32") == 0);
		assert(res[1].compare("255.0.0.8/29") == 0);
		assert(res[2].compare("255.0.0.16/32") == 0);


		res = sol.ipToCIDR("1.1.1.0", 4);
		assert(1 == res.size());
		assert(res[0].compare("1.1.1.0/30") == 0);

		res = sol.ipToCIDR("1.1.1.1", 4);
		assert(3 == res.size());
		assert(res[0].compare("1.1.1.1/32") == 0);
		assert(res[1].compare("1.1.1.2/31") == 0);
		assert(res[2].compare("1.1.1.4/32") == 0);
	}
};

class CSVParser {
public:
	string parse(string str) {
		string cur;
		vector<string> ret;
		bool isQuote = false;
		int len = str.length();
		for (int i = 0; i < len; ++i) {
			if (isQuote) {
				if (str[i] == '\"') {
					if (i < len - 1 && str[i + 1] == '\"') {
						cur.append("\"");
						++i;
					}
					else {
						isQuote = false;
					}
				}
				else {
					cur += str[i];
				}
			}
			else {
				if (str[i] == '\"')
					isQuote = true;
				else if (str[i] == ',') {
					ret.emplace_back(cur);
					cur = "";
				}
				else
					cur += str[i];
			}
		}
		if (!cur.empty())
			ret.emplace_back(cur);

		string result = "";
		for (int i = 0; i < ret.size(); ++i) {
			if (i > 0)
				result += "|";
			result += ret[i];
		}
		return result;
	}

	static void main() {
		CSVParser sol;
		string test = "John,Smith,john.smith@gmail.com,Los Angeles,1";
		string expected = "John|Smith|john.smith@gmail.com|Los Angeles|1";
		assert(expected.compare(sol.parse(test)) == 0);

		test = "Jane,Roberts,janer@msn.com,\"San Francisco, CA\",0";
		expected = "Jane|Roberts|janer@msn.com|San Francisco, CA|0";
		assert(expected.compare(sol.parse(test)) == 0);

		test = "\"Alexandra \"\"Alex\"\"\",Menendez,alex.menendez@gmail.com,Miami,1";
		expected = "Alexandra \"Alex\"|Menendez|alex.menendez@gmail.com|Miami|1";
		assert(expected.compare(sol.parse(test)) == 0);

		// " ""Alexandra Alex"" "
		test = "\"\"\"Alexandra Alex\"\"\"";
		expected = "\"Alexandra Alex\"";
		assert(expected.compare(sol.parse(test)) == 0);
	}
};

class TextAdjust {
public:
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		vector<string> ret;
		if (words.empty() || 0 == maxWidth) {
			ret.emplace_back("");
			return ret;
		}
		int k, len;
		int L = maxWidth;
		for (int i = 0; i < words.size(); i += k) {
			len = 0;
			for (k = 0; i + k < words.size() && len + words[i + k].size() <= L - k; ++k)
				len += words[i + k].size();

			string tmp(words[i]);
			for (int j = 0; j < k - 1; ++j) {
				if (i + k >= words.size())
					tmp += " ";
				else
					tmp += string((L - len) / (k - 1) + (j < (L - len) % (k - 1)), ' ');
				tmp += words[i + j + 1];
			}

			tmp += string(L - tmp.size(), ' ');
			ret.emplace_back(tmp);
		}
		return ret;
	}

	static void main() {
		TextAdjust sol;

		vector<string> words1 = { "What", "must", "be", "acknowledgment", "shall", "be" };
		vector<string> ret = sol.fullJustify(words1, 16);
		assert(ret.size() == 3);
		assert(ret[0].compare("What   must   be") == 0);
		assert(ret[1].compare("acknowledgment  ") == 0);
		assert(ret[2].compare("shall be        ") == 0);
	}
};

class RegExpression {
public:
	bool match1(string source, string pattern) {
		if (pattern.empty())
			return source.empty();

		if (pattern.size() == 1) {
			return source.size() == 1 ? source[0] == pattern[0] : false;
		}

		if (!source.empty() && (pattern[0] == '.' || pattern[0] == source[0])) {
			if (pattern[1] == '*')
				return match1(source.substr(1), pattern) || match1(source, pattern.substr(2));
			else if (pattern[1] == '+')
				return match1(source.substr(1), pattern.substr(2)) || match1(source.substr(1), pattern);
			else
				return match1(source.substr(1), pattern.substr(1));
		}

		return pattern[1] == '*' && match1(source, pattern.substr(2));
	}

	bool match2(string source, string pattern) {
		if (pattern.empty())
			return source.empty();

		int m = pattern.size();
		int n = source.size();
		vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
		dp[0][0] = true;
		for (int i = 1; i <= m; ++i)
			dp[i][0] = (pattern[i - 1] == '*' && dp[i - 2][0]);

		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= n; ++j) {
				if (pattern[i - 1] == '.' || pattern[i - 1] == source[j - 1])
					dp[i][j] = dp[i - 1][j - 1];
				else if (pattern[i - 1] == '*' || pattern[i - 1] == '+') {
					if (pattern[i - 2] == '.' || pattern[i - 2] == source[j - 1]) {
						if (pattern[i - 1] == '*')
							dp[i][j] = dp[i - 2][j] || dp[i - 2][j - 1] || dp[i][j - 1];
						else
							dp[i][j] = dp[i - 2][j - 1] || dp[i][j - 1];
					}
					else {
						dp[i][j] = pattern[i - 1] == '*' && dp[i - 2][j];
					}
				}
			}
		return dp[m][n];
	}
	static void main() {
		RegExpression sol;
		assert(sol.match1("saaaa", "s+a*") == true);
		assert(sol.match1("saaaa", "s+b*") == false);
		assert(sol.match1("saaaab", "s+a*") == false);
		assert(sol.match1("saaaab", "s+b*") == false);
		assert(sol.match1("a", "a*") == true);
		assert(sol.match1("aa", "a*") == true);
		assert(sol.match1("aab", "a*") == false);
		assert(sol.match1("a", "a+") == true);
		assert(sol.match1("aa", "a+") == true);
		assert(sol.match1("aab", "a+") == false);

		
		assert(sol.match2("saaaa", "s+a*") == true);
		assert(sol.match2("saaaa", "s+b*") == false);
		assert(sol.match2("saaaab", "s+a*") == false);
		assert(sol.match2("saaaab", "s+b*") == false);
		assert(sol.match2("a", "a*") == true);
		assert(sol.match2("aa", "a*") == true);
		assert(sol.match2("aab", "a*") == false);
		assert(sol.match2("a", "a+") == true);
		assert(sol.match2("aa", "a+") == true);
		assert(sol.match2("aab", "a+") == false);
		assert(sol.match2("", "") == true);
		assert(sol.match2("", "a*") == true);
	}
};

class WaterDrop {
public:
	vector<int> pourWater(vector<int>& heights, int V, int K) {
		while (V-- > 0) {
			drop(heights, K);
		}
		return heights;
	}

	void drop(vector<int>& heights, int K) {
		int best = K;
		for (int d = -1; d < 2; d += 2) {
			int i = K + d;
			while (i >= 0 && i < heights.size() && heights[i] <= heights[i - d]) {
				if (heights[best] > heights[i])
					best = i;

				i += d;
			}

			if (best != K)
				break;
		}
		heights[best] ++;
	}

	static void main() {
		WaterDrop sol;
		vector<int> heights1 = { 1, 2, 3, 4 };

		vector<int> ret = sol.pourWater(heights1, 2, 2);
		//2,3,3,4
		assert(ret[0] == 2);
		assert(ret[1] == 3);
		assert(ret[2] == 3);
		assert(ret[3] == 4);

		vector<int> heights2 = { 3, 1, 3 };
		ret = sol.pourWater(heights2, 5, 1);
		//4,4,4
		assert(ret[0] == 4);
		assert(ret[1] == 4);
		assert(ret[2] == 4);

		vector<int> heights3 = { 2, 1, 1, 2, 1, 2, 2 };
		ret = sol.pourWater(heights3, 4, 3);
		//2,2,2,3,2,2,2
		assert(ret[0] == 2);
		assert(ret[1] == 2);
		assert(ret[2] == 2);
		assert(ret[3] == 3);
		assert(ret[4] == 2);
		assert(ret[5] == 2);
		assert(ret[6] == 2);
	}
};

class MeetingInterval {
public:
	vector<Interval> findNoMeeting(vector<Interval> times) {
		sort(times.begin(), times.end(), [](Interval a, Interval b)
		{return a.start == b.start ? a.end < b.end : a.start < b.start; });

		vector<Interval> tmp;
		tmp.emplace_back(times[0]);
		for (int i = 1; i < times.size(); ++i) {
			if (times[i].start > tmp.back().end)
				tmp.emplace_back(times[i]);
			else
				tmp.back().end = max(tmp.back().end, times[i].end);
		}

		vector<Interval> ret;
		for (int i = 0; i < tmp.size(); ++i) {
			if (i == 0 && tmp[i].start > 1)
				ret.emplace_back(Interval(1, tmp[i].start));
			else if (i > 0 && tmp[i].start > tmp[i - 1].end)
				ret.emplace_back(Interval(tmp[i - 1].end, tmp[i].start));
			else if (i == tmp.size() - 1 && tmp[i].end < 24)
				ret.emplace_back(Interval(tmp[i].end, 24));
		}
		return ret;
	}

	static void main() {
		MeetingInterval sol;
		vector<Interval> intervals = { Interval(1, 3), Interval(6, 7), Interval(2, 4), Interval(2, 3), Interval(9, 12) };
		vector<Interval> res = sol.findNoMeeting(intervals);
		assert(2 == res.size());
		assert(4 == res[0].start);
		assert(6 == res[0].end);
		assert(7 == res[1].start);
		assert(9 == res[1].end);
	}
};

class RoundPrice {
public:
	vector<int> roundNum(vector<double> data) {
		vector<int> ret;
		vector<pair<double, int>> s_prices;
		int got = 0;
		double total = 0.0;

		for (int i = 0; i < data.size(); ++i) {
			double price = data[i];
			int tmp = int(floor(price));
			s_prices.emplace_back(price, i);
			ret.emplace_back(tmp);
			got += tmp;
			total += price;
		}
		sort(s_prices.begin(), s_prices.end(), [](pair<double, int>a, pair<double, int>b)
		{return a.first - floor(a.first) > b.first - floor(b.first); });

		for (int i = 0; i < int(round(total)) - got; ++i) {
			ret[s_prices[i].second] ++;
		}
		return ret;
	}
	static void main() {
		RoundPrice sol;
		vector<double> data1 = { 1.1, 1.4 };
		vector<int> ret = sol.roundNum(data1);

		assert(ret.size() == 2);
		assert(ret[0] == 1);
		assert(ret[1] == 2);

		vector<double> data2 = { 1.4, 1.4, 1.4 };
		ret = sol.roundNum(data2);

		assert(ret.size() == 3);
		assert(ret[0] == 2);
		assert(ret[1] == 1);
		assert(ret[2] == 1);

		vector<double> data3 = { 1.6, 1.6 };
		ret = sol.roundNum(data3);

		assert(ret.size() == 2);
		assert(ret[0] == 2);
		assert(ret[1] == 1);
	}
	
};


class Sliding {
public:
	vector<pair<int, int>> minpath;
	void dfs(string str, unordered_map<int, vector<int>>& moves, vector<pair<int, int>> path,
		unordered_map<string, int> mem,
		int cur_zero, int swap_zero, int cur_move, int&res) {

		swap(str[cur_zero], str[swap_zero]);
		if (cur_zero != swap_zero)
			path.emplace_back(cur_zero, swap_zero);

		if (0 == str.compare("123450")) {
			if (cur_move < res) {
				res = cur_move;
				minpath = path;
			}
		}

		if (cur_move < res && (!mem.count(str) || mem[str] > cur_move)) {
			mem[str] = cur_move;
			for (auto new_zero : moves[swap_zero])
				dfs(str, moves, path, mem, swap_zero, new_zero, cur_move + 1, res);
		}
	}

	int slidingPuzzle(vector<vector<int>>& b, int min_moves = INT_MAX) {
		unordered_map<int, vector<int>> moves = { { 0, { 1, 3 } }, { 1, { 0, 2, 4 } }, { 2, { 1, 5 } },
		{ 3, { 0, 4 } }, { 4, { 1, 3, 5 } }, { 5, { 2, 4 } } };

		string str = to_string(b[0][0]) + to_string(b[0][1]) + to_string(b[0][2])
			+ to_string(b[1][0]) + to_string(b[1][1]) + to_string(b[1][2]);

		int res = INT_MAX;
		vector<pair<int, int>> path;
		unordered_map<string, int> mem;
		dfs(str, moves, path, mem, str.find('0'), str.find('0'), 0, res);
		return res == INT_MAX ? -1 : res;
	}

	static void main() {
		Sliding sol;

		vector<vector<int>> board1 = { { 4, 1, 2 }, { 5, 0, 3 } };
		assert(5 == sol.slidingPuzzle(board1));
	}
};

class MaxNights {
public:
	int maxNights(vector<int> nights) {
		int len = nights.size();
		if (0 == len)
			return 0;

		if (len == 1)
			return nights[0];

		int f1 = nights[0];
		int f2 = max(nights[0], nights[1]);
		if (len == 2)
			return f2;
		
		for (int i = 2; i < len; ++i) {
			int tmp = max(f1 + nights[i], f2);
			f1 = f2;
			f2 = tmp;
		}

		return f2;
	}

	static void main() {
		MaxNights sol;
		vector<int> test1 = { 5, 6, 3, 1 };
		assert(8, sol.maxNights(test1));
		vector<int> test2 = { 6, 5, 0, 1, 0, 9 };
		assert(16, sol.maxNights(test2));
		vector<int> test3 = { 5, 1, 1, 5 };
		assert(10, sol.maxNights(test3));
		vector<int> test4 = { 3, 6, 4 };
		assert(7, sol.maxNights(test4));
		vector<int> test5 = { 4, 10, 3, 1, 5 };
		assert(15, sol.maxNights(test5));
	}
};

class FindAllCase {
public:
	void nextcase(string& str, int idx, vector<string>& res) {
		if (idx == str.size()) {
			res.emplace_back(str);
			return;
		}

		char tmp = str[idx];
		str[idx] = toupper(tmp);
		nextcase(str, idx + 1, res);
		str[idx] = tolower(tmp);
		nextcase(str, idx + 1, res);
		str[idx] = tmp;
	}

	vector<string> find(string str) {
		vector<string> res;
		int len = str.size();
		if (0 == len)
			return res;

		nextcase(str, 0, res);
		return res;
	}

	static void main() {
		FindAllCase sol;
		vector<string> res = sol.find("AirBnB");
		assert(64 == res.size());

		assert(res[0].compare("AIRBNB") == 0);
		/*assert("Airbnb", res.get(1));
		assert("aIRBNB", res.get(62));
		assert("AIRBNB", res.get(63));
		*/
	}
};

class MenuCombo {
public:
	vector<vector<double>> getCombos(vector<double> prices, double target) {
		vector<vector<double>> res;
		int len = prices.size();
		if (0 == len || target <= 0)
			return res;

		int centTarget = int(round(target * 100));
		sort(prices.begin(), prices.end());
		vector<int> centprices(len);
		for (int i = 0; i < len; ++i) {
			centprices[i] = int(round(prices[i] * 100));
		}

		vector<double> combo;
		search(res, centprices, 0, centTarget, combo, prices);
		return res;
	}

	void search(vector<vector<double>>& res, vector<int> centPrices, int start,
		int centsTarget, vector<double> combo, vector<double>& prices) {
		if (0 == centsTarget) {
			res.emplace_back(combo);
			return;
		}

		for (int i = start; i < centPrices.size(); ++i) {
			if (centPrices[i] > centsTarget)
				continue;

			if (i > start && centPrices[i] == centPrices[i - 1])
				continue;
			combo.emplace_back(prices[i]);
			search(res, centPrices, i + 1, centsTarget - centPrices[i], combo, prices);
			combo.pop_back();
		}
	}
	static void main() {
		MenuCombo sol;
		vector<double> prices = { 10.02, 1.11, 2.22, 3.01, 4.02, 2.00, 5.03 };
		vector<vector<double>> combos = sol.getCombos(prices, 7.03);
		//cout << combos;
		assert(2 == combos.size());
	}
};

struct TrieNode {
	bool isleaf;
	vector<TrieNode*> childs;
	TrieNode() {
		isleaf = false;
		childs.resize(26, nullptr);
	}
};

class TrieTree {
public:
	void add(string str) {
		if (str.empty())
			return;
		TrieNode* cur = &root;

		for (int i = 0; i < str.size(); ++i) {
			int idx = (str[i] - 'a');
			if (cur->childs[idx] == nullptr)
				cur->childs[idx] = new TrieNode();
			cur = cur->childs[idx];
		}
		cur->isleaf = true;
	}

	TrieNode root;
};

class KDistance {
public:
	vector<string> getKEditDistance(vector<string> words, string target, int k) {
		vector<string> ret;
		int len = words.size();
		if (len == 0 || k < 0) {
			return ret;
		}

		TrieTree tree;
		for (auto it : words)
			tree.add(it);

		TrieNode root = tree.root;
		vector<int> pre(target.length() + 1, 0);
		for (int i = 0; i <= target.length(); ++i)
			pre[i] = i;

		getDistanceHelper("", target, k, &root, pre, ret);
		return ret;
	}

	void getDistanceHelper(string curr, string target, int k, TrieNode* root,
		vector<int>& prevDist, vector<string>& result) {
		if (root->isleaf) {
			if (prevDist[target.length()] <= k) {
				result.emplace_back(curr);
			}
			else
				return;
		}

		for (int i = 0; i < 26; ++i) {
			if (root->childs[i] == nullptr)
				continue;

			vector<int> currDist(target.length() + 1);
			currDist[0] = curr.length();

			for (int j = 1; j < prevDist.size(); ++j) {
				if (target[j - 1] == (char)(i + 'a'))
					currDist[j] = prevDist[j - 1];
				else
					currDist[j] = min(min(prevDist[j], prevDist[j - 1]), currDist[j - 1]) + 1;
			}
			getDistanceHelper(curr + (char)(i + 'a'), target, k, root->childs[i], currDist, result);
		}
	}

	static void main() {
		KDistance sol;
		vector<string> input = { "abcd", "abc", "abd", "ad", "c", "cc" };
		string target = "abcd";
		int k = 2;
		vector<string> res = sol.getKEditDistance(input, target, k);
		assert(4 == res.size());
	}
};

class MinimumKStops {
public:
	vector<int> minPath;
	int findCheapestPrice2(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		unordered_map<int, vector<pair<int, int>>> costs;
		int res = INT_MAX;
		for (auto it : flights) {
			costs[it[0]].emplace_back(it[1], it[2]);
		}
		vector<int> path;
		vector<bool> visited(n, false);
		visited[src] = true;
		path.emplace_back(src);
		dfs(costs, path, visited, src, dst, 0, K + 1, res);
		return res == INT_MAX ? -1 : res;
	}

	void dfs(unordered_map<int, vector<pair<int, int>>>& costs, vector<int> path,
		vector<bool>& visited, int src, int dst, int cost, int K, int& res) {
		if (src == dst) {
			minPath = path;
			res = cost;
		}

		if (K == 0)
			return;

		for (auto it : costs[src]) {
			if (visited[it.first])
				continue;

			if (cost + it.second > res)
				continue;

			visited[it.first] = true;
			path.emplace_back(it.second);
			dfs(costs, path, visited, it.first, dst, cost + it.second, K - 1, res);
			path.pop_back();
			visited[it.first] = false;
		}
	}

	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		int kInfCost = INT_MAX;
		vector<vector<int>> dp(K + 2, vector<int>(n, kInfCost));
		dp[0][src] = 0;

		for (int i = 1; i <= K + 1; ++i) {
			dp[i][src] = 0;
			for (const auto& p : flights)
				if (dp[i - 1][p[0]] != kInfCost)
					dp[i][p[1]] = min(dp[i][p[1]], dp[i - 1][p[0]] + p[2]);
		}

		return dp[K + 1][dst] == kInfCost ? -1 : dp[K + 1][dst];
	}
	static void main() {
		MinimumKStops sol;
		vector<vector<int>> flights = { { 0, 1, 100 }, { 0, 2, 400 }, { 1, 2, 100 }, { 2, 3, 100 }, { 2, 0, 10 } };

		assert(-1 == sol.findCheapestPrice(4, flights, 0, 3, 0));
		assert(-1 == sol.findCheapestPrice2(4, flights, 0, 3, 0));
		assert(500 == sol.findCheapestPrice(4, flights, 0, 3, 1));
		assert(500 == sol.findCheapestPrice2(4, flights, 0, 3, 1));
		assert(300 == sol.findCheapestPrice(4, flights, 0, 3, 2));
		assert(300 == sol.findCheapestPrice2(4, flights, 0, 3, 2));
	}
};

class AlienOreder {
public:
	string getorder(vector<string>& words) {
		map<char, set<char>> suc, pre;
		set<char> chars;
		string str("");

		for (auto it : words) {
			chars.insert(it.begin(), it.end());
			for (int i = 0; i < min(str.size(), it.size()); ++i) {
				char a = str[i], b = it[i];
				if (a != b) {
					suc[a].emplace(b);
					pre[b].emplace(a);
					break;
				}
			}
			str = it;
		}

		set<char> free = chars;
		for (auto it : pre) {
			free.erase(it.first);
		}

		string ret = "";
		while (!free.empty()) {
			char a = *free.begin();
			free.erase(free.begin());
			ret += a;

			for (auto b : suc[a]) {
				pre[b].erase(a);
				if (pre[b].empty())
					free.emplace(b);
			}
		}

		return ret.size() == chars.size() ? ret : "";
	}

	static void main() {
		AlienOreder sol;
		vector<string> test1 = { "wrt", "wrf", "er", "ett", "rftt" };
		string ret = sol.getorder(test1);

		assert(ret.compare("wertf") == 0);
	}
};

class StringMatrix {
public:
	typedef unordered_map<char, unordered_map<char, unordered_set<char> > > matrixInfo;

	void generateStatus(vector<unordered_set<char> >& allStatus, matrixInfo& matrix) {
		if (allStatus.size() == 1) return;
		const int n = allStatus.size();
		for (int i = 0; i < n - 1; ++i) {
			unordered_set<char> st;
			for (auto first : allStatus[i]) {
				for (auto second : allStatus[i + 1]) {
					st.insert(matrix[first][second].begin(), matrix[first][second].end());
				}
			}
			allStatus[i] = st;
		}
		allStatus.pop_back();
		generateStatus(allStatus, matrix);
	}

	bool checkStatus(matrixInfo& matrix, char result, const string status) {
		vector<unordered_set<char> > allStatus;
		for (auto it : status) {
			unordered_set<char> tmp;
			tmp.insert(it);
			allStatus.push_back(tmp);
		}

		generateStatus(allStatus, matrix);
		return allStatus[0].count(result) != 0;
	}

	static void main() {
		/*vector<string> lines = {
		"A,A,AC", "A,B,CD", "A,C,D", "A,D,B",
		"B,A,B", "B,B,C", "B,C,A", "B,D,CD",
		"C,A,A", "C,B,C", "C,C,D", "C,D,B",
		"D,A,BC", "D,B,D", "D,C,A", "D,D,C"
		};*/

		StringMatrix sol;
		matrixInfo mi1;
		mi1['A']['A'].insert('B');
		mi1['A']['B'].insert('A');
		mi1['A']['B'].insert('C');
		mi1['A']['C'].insert('D');
		mi1['A']['D'].insert('A');
		mi1['B']['A'].insert('D');
		mi1['B']['B'].insert('B');
		mi1['B']['B'].insert('C');
		mi1['B']['C'].insert('A');
		mi1['C']['D'].insert('B');
		cout << sol.checkStatus(mi1, 'A', "ABCD") << endl;

		matrixInfo mi2;
		mi2['A']['B'].insert('B');
		mi2['C']['D'].insert('C');
		mi2['B']['C'].insert('E');
		mi2['B']['E'].insert('E');
		mi2['E']['C'].insert('B');
		mi2['E']['B'].insert('D');
		cout << sol.checkStatus(mi2, 'D', "ABCD") << endl;
		// sol.check("ABCD");
	}
};

class FindingOcean {
public:
	void floodFill(vector<vector<char>>& board, int i, int j, char oldColor, char newColor) {
		int m = board.size();
		int n = board[0].size();
		if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != oldColor)
			return;

		vector<int> direction = { -1, 0, 1, 0, -1, 0 };
		queue<pair<int, int>> que;
		que.push({ i, j });
		while (!que.empty()) {
			pair<int, int> cur = que.front();
			que.pop();

			for (int i = 0; i < 4; ++i) {
				int x = cur.first + direction[i];
				int y = cur.second + direction[i + 1];
				if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] != oldColor)
					continue;
				board[x][y] = newColor;
				que.emplace(x, y);
			}
		}
	}

	static void main() {
		FindingOcean sol;
		vector<vector<char>> board = { { 'W', 'W', 'W', 'L', 'L', 'L', 'W' },
		{ 'W', 'W', 'L', 'L', 'L', 'W', 'W' },
		{ 'W', 'L', 'L', 'L', 'L', 'W', 'W' } };

		sol.floodFill(board, 0, 0, 'W', 'O');
		assert('O' == board[0][0]);
	}
};


class Preferencelist {
public:
	vector<int> preferlist(vector<vector<int>> preference) {
		vector<int> ret;
		unordered_map<int, unordered_set<int>> mp;
		unordered_map<int, int> degree;
		for (auto it : preference) {
			for (int i = 1; i < it.size(); ++i)
				mp[it[i - 1]].insert(it[i]);
		}

		for (auto it : mp)
			for (auto second : it.second)
				degree[second] ++;

		queue<int> que;
		for (auto it : preference) {
			for (int i = 0; i < it.size(); ++i) {
				if (!degree.count(it[i])) {
					que.push(it[i]);
					ret.push_back(it[i]);
				}
			}
		}

		while (!que.empty()) {
			int cur = que.front();
			que.pop();

			auto next = mp[cur];
			for (auto it : next) {
				if (--degree[it] == 0) {
					que.emplace(it);
					ret.emplace_back(it);
				}
			}
		}
		return ret;
	}

	static void main() {
		Preferencelist sol;
		//vector<vector<int>> test1 = { { 3, 5, 7, 9 }, { 2, 3, 8 }, { 5, 8 } };
		vector<vector<int>> test1 = { { 3, 5, 7, 9 }, { 2, 3, 8 }, { 8, 7 } };
		vector<int> ret = sol.preferlist(test1);
		assert(ret.size() == 6);
	}
};

class MinVertices {
public:
	vector<int> getMin(vector<vector<int>> edges, int n) {
		map<int, set<int>> nodes;
		for (auto it : edges) {
			nodes[it[0]].emplace(it[1]);
		}

		set<int> visited;
		set<int> res;
		for (int i = 0; i < n; ++i) {
			if (!visited.count(i)) {
				res.emplace(i);
				set<int> currVisited;
				search(res, nodes, i, i, visited, currVisited);
			}
		}
		vector<int> ret(res.begin(), res.end());
		return ret;
	}

	void search(set<int>& res, map<int, set<int>>& nodes, int cur, int start,
		set<int>& visited, set<int>& currVisited) {
		currVisited.emplace(cur);
		visited.emplace(cur);
		for (auto next : nodes[cur]) {
			if (res.count(next) && next != start)
				res.erase(next);

			if (!currVisited.count(next))
				search(res, nodes, next, start, visited, currVisited);
		}
	}

	static void main() {
		MinVertices sol;
		vector<vector<int>> edges1 = { { 0, 0 }, { 1, 2 }, { 2, 0 }, { 2, 3 }, { 3, 1 } };
		vector<int> res = sol.getMin(edges1, 4);
		assert(1 == res.size());

		vector<vector<int>> edges2 = { { 2, 9 }, { 3, 3 }, { 3, 5 }, { 3, 7 }, { 4, 8 }, { 5, 8 }, { 6, 6 }, { 7, 4 }, { 8, 7 }, { 9, 3 }, { 9, 6 } };
		res = sol.getMin(edges2, 10);
		assert(3 == res.size());
	}
};

class CotinueNum {
public:
	int consecutiveNumbersSum(int N) {
		int count = 1;

		for (int k = 2; k < sqrt(2 * N); ++k) {
			if ((N - k * (k - 1) / 2) % k == 0)
				++count;
		}
		return count;
	}

	static void main() {
		CotinueNum sol;
		assert(2 == sol.consecutiveNumbersSum(5));
		assert(3 == sol.consecutiveNumbersSum(9));
		assert(4 == sol.consecutiveNumbersSum(15));

	}
};

class GuessWord {
	class Master {
	public:
		Master(string str) : secrete(str) {}

		int guess(string str) {
			return matches(str, secrete);
		}

		void setsecret(string str) {
			secrete = str;
		}

		int matches(string a, string b) {
			int matches = 0;
			for (int i = 0; i < a.length(); ++i) if (a[i] == b[i]) matches++;
			return matches;
		}

	private:
		string secrete;
	};
	
	
public:
	int findSecretWord(vector<string>& wordlist, string secrete) {
		Master master(secrete);		
		master.setsecret(secrete);
		for (int i = 0, x = 0; i < 10 && x < 6; ++i) {
			unordered_map<string, int> count;
			for (string w1 : wordlist)
				for (string w2 : wordlist)
					if (master.matches(w1, w2) == 0)
						count[w1]++;

			pair<string, int> minimax = make_pair(wordlist[0], 1000);
			for (string w : wordlist)
				if (count.count(w) && count[w] <= minimax.second)
					minimax = make_pair(w, count[w]);
			x = master.guess(minimax.first);
			if (x == 6)
				return 1;
			vector<string> wordlist2;
			for (string w : wordlist)
				if (master.matches(minimax.first, w) == x)
					wordlist2.push_back(w);
			wordlist = wordlist2;
		}
		return 0;
	}

	static void main() {
		vector<string> wordlist = { "acckzz", "ccbazz", "eiowzz", "abcczz" };
		string secrete = wordlist[rand() % wordlist.size()];
		GuessWord sol;
		cout << sol.findSecretWord(wordlist, secrete) << endl;
	}
};


class Wizards {
public:
	vector<int> minPath;
	int wizards2(const vector<vector<int> > &wizards, int start, int end) {
		unordered_map<int, vector<pair<int, int>> > next;
		int ans = INT_MAX;
		for (int i = 0; i < wizards.size(); ++i) {
			for (auto nx : wizards[i]) {
				int dis = (nx - i) * (nx - i);
				next[i].emplace_back(nx, dis);
			}
		}

		vector<bool> visited(end + 1, false);
		visited[start] = true;
		vector<int> path;
		path.emplace_back(start);
		dfs(next, visited, ans, end, 0, start, end, path);
		return ans;
	}

	void dfs(unordered_map<int, vector<pair<int, int>> >&next,
		vector<bool> &visited, int &ans, int k, int cost,
		int start, int end, vector<int>path) {
		if (start == end) {
			if (cost < ans) {
				ans = cost;
				minPath = path;
			}
		}

		if (0 == k)
			return;

		visited[start] = true;
		for (auto it : next[start]) {
			if (visited[it.first] || cost + it.second > ans)
				continue;

			visited[it.first] = true;
			path.emplace_back(it.first);
			dfs(next, visited, ans, k - 1, cost + it.second, it.first, end, path);
			visited[it.first] = false;
			path.pop_back();
		}
	}

	static void main() {
		Wizards sol;
		vector<vector<int> > test1 = { { 1, 4, 5 }, {}, {}, {}, { 9 }, {}, {}, {}, {}, {} };
		vector<vector<int> > test2 = { { 1, 2, 5, 9 }, { 2, 3, 9 }, { 4, 9 }, {}, {}, { 9 }, {}, {}, {}, {} };
		vector<vector<int> > test3 = { { 1, 5, 9 }, {}, {}, {}, {}, {}, {}, {}, {}, {} };

		/*
		assert(41 == sol.wizards(test1, 0, 9));
		assert(41 == sol.wizards(test1, 0, 9));
		assert(81 == sol.wizards(test3, 0, 9));*/

		assert(41 == sol.wizards2(test1, 0, 9));
		assert(41 == sol.wizards2(test1, 0, 9));
		assert(81 == sol.wizards2(test3, 0, 9));
	}
};

class NumberofRectangles {
public:
	//rec1[0] < rec2[2] && rec2[0] < rec1[2] && rec1[1] < rec2[3] && rec2[1] < rec1[3];
	bool intersect(vector<vector<int>> r1, vector<vector<int>> r2) {
		return r1[0][0] < r2[0][0] && r1[0][1] < r2[0][1] && r2[0][0] < r1[1][0] && r2[0][1] < r1[1][1] ||
			r1[0][0] < r2[1][0] && r1[0][1] < r2[1][1] && r2[1][0] < r1[1][0] && r2[1][1] < r1[1][1];
	}
	int find(int val, vector<int>& parents) {
		while (parents[val] != val) {
			val = parents[val];
		}
		return val;
	}

	int countIntersection(vector<vector<vector<int>>> rectangles) {
		int len = rectangles.size();
		if (len == 0)
			return 0;

		vector<int> parents(len);
		for (int i = 0; i < len; i++) {
			parents[i] = i;
		}

		for (int i = 0; i < len - 1; i++) {
			for (int j = i + 1; j < len; j++) {
				if (intersect(rectangles[i], rectangles[j])) {
					int root1 = find(i, parents);
					int root2 = find(j, parents);

					if (root1 != root2) {
						parents[root1] = root2;
					}
				}
			}
		}

		//merge parent
		set<int> set;
		for (int i = 0; i < len; i++) {
			set.insert(find(i, parents));
		}

		return set.size();
	}

	static void main() {
		NumberofRectangles sol;
		vector<vector<vector<int>>> rectangles = {
			{ { -3, -2 }, { 2, 1 } },
			{ { 10, 8 }, { 15, 10 } },
			{ { 1, 0 }, { 7, 4 } },
			{ { 12, 9 }, { 16, 12 } },
			{ { -2, -1 }, { 5, 3 } }
		};
		assert(2 == sol.countIntersection(rectangles));
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	NextSolution::main();
	CollatzConjecture::main();
	DisplayPage::main();
	TravelBuddy::main();
	FileSystem::main();
	PalindromePairs::main();
	FindMedium::main();
	IP2CDR::main();
	CSVParser::main();
	TextAdjust::main();
	RegExpression::main();
	WaterDrop::main();
	MeetingInterval::main();
	RoundPrice::main();
	Sliding::main();
	MaxNights::main();
	FindAllCase::main();
	MenuCombo::main();
	KDistance::main();
	MinimumKStops::main();
	AlienOreder::main();
	StringMatrix::main();
	FindingOcean::main();
	Preferencelist::main();
	MinVertices::main();
	CotinueNum::main();
	GuessWord::main();
	Wizards::main();
	NumberofRectangles::main();
	return 0;
}
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
