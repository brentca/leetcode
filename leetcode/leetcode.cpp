// LCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
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
#include <iomanip>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <regex>
#include <iterator>
#include <memory>
#include <fstream>
#include "eb.h"

#if 0
c++11 vs 14
multi-thread
c++ feature
linux static libary and dynamic. loading and calling
parking design

Linux
在POSIX标准中定义了三种线程同步机制: Mutexes(互斥量), Condition Variables(条件变量)和POSIX Semaphores(信号量)

[dead lock]
For instance, if thread A is blocked on a condition variable waiting for thread B to signal it, and thread B 
is blocked on a condition variable waiting for thread A to signal it, a deadlock has occurred because neither 
thread will ever signal the other

A simple type of deadlock may occur when the same thread attempts to lock a mutex twice in a row.
If the mutex was locked by another thread, pthread_mutex_lock blocks execution and returns only 
eventually when the mutex is unlocked by the other thread.

One common error that can cause a deadlock involves a problem in which more than one thread is trying to lock 
the same set of objects. For example, consider a program in which two different threads, running two different 
thread functions, need to lock the same two mutexes. Suppose that thread A locks mutex 1 and then mutex 2, and 
thread B happens to lock mutex 2 before mutex 1. In a sufficiently unfortunate scheduling scenario, Linux may 
schedule thread A long enough to lock mutex 1, and then schedule thread B, which promptly locks mutex 2. Now 
neither thread can progress because each is blocked on a mutex that the other thread holds locked.

[mutex vs Condition Variables]
A condition variable allows a thread to be signaled when something of interest to that thread occurs.
By itself, a mutex doesn't do this.

If you just need mutual exclusion, then condition variables don't do anything for you. However, if you need to 
know when something happens, then condition variables can help.

For example, if you have a queue of items to work on, you'll have a mutex to ensure the queue's internals are 
consistent when accessed by the various producer and consumer threads. However, when the queue is empty, how will 
a consumer thread know when something is in there for it to work on? Without something like a condition variable 
it would need to poll the queue, taking and releasing the mutex on each poll (otherwise a producer thread could 
never put something on the queue).

Using a condition variable lets the consumer find that when the queue is empty it can just wait on the condition 
variable indicating that the queue has had something put into it. No polling - that thread does nothing until a 
producer puts something in the queue, then signals the condition that the queue has a new item.

[mutex and critical section]
There is no equivalent to Critical Sections on Windows for linux
In windows:
Mutexes can be shared between processes, but always result in a system call to the kernel which has some overhead.

Critical sections can only be used within one process, but have the advantage that they only switch to kernel mode
in the case of contention - Uncontended acquires, which should be the common case, are incredibly fast. In the 
case of contention, they enter the kernel to wait on some synchronization primitive (like an event or semaphore).

/* Calls do_work repeatedly while the thread flag is set; blocks if 
the flag is clear.  */ 
void* thread_function (void* thread_arg) 
{
	/* Loop infinitely.  */ 
	while (1) {
		/* Lock the mutex before accessing the flag value.  */ 
		pthread_mutex_lock (&thread_flag_mutex); 
		while (!thread_flag) 
			/* The flag is clear. Wait for a signal on the condition 
			variable, indicating that the flag value has changed. When the 
			signal arrives and this thread unblocks, loop and check the 
			flag again.  */ 
			pthread_cond_wait (&thread_flag_cv, &thread_flag_mutex); 
		/* When we've gotten here, we know the flag must be set. Unlock 
		the mutex.  */ 
		pthread_mutex_unlock (&thread_flag_mutex); 
		/* Do some work.  */ 
		do_work (); 
	} 
	return NULL; 
} 

/* Sets the value of the thread flag to FLAG_VALUE.  */ 

void set_thread_flag (int flag_value) 
{
	/* Lock the mutex before accessing the flag value.  */ 
	pthread_mutex_lock (&thread_flag_mutex); 
	/* Set the flag value, and then signal in case thread_function is 
	blocked, waiting for the flag to become set. However, 
	thread_function can't actually check the flag until the mutex is 
	unlocked.  */ 
	thread_flag  =  flag_value; 
	pthread_cond_signal  (&thread_flag_cv); 
	/*  Unlock  the  mutex.   */ 
	pthread_mutex_unlock  (&thread_flag_mutex); 
} 

[spin lock vs mutex]
从实现原理上来讲，Mutex是属于sleep-waiting类型 的锁。例如在一个双核的机器上有两个线程(线程A和线程B)，它们分别运行在Core0和
Core1上。当线程A想要 pthread_mutex_lock操作去得到一个临界区的锁时，如果这个锁正被线程B所持有，那么线程A就会被阻塞(bolcking)，
Core0 会在此时进行上下文切换(Context Switch)，这样Core0就可以运行其他的任务(例如另一个线程C)而上必进行忙等待。而Spin lock
则上然，它是属于busy-waiting类型的锁，如果线程A是使用pthread_spin_lock操作去请求锁，那么线程A就会一直在 Core0上进行忙等待
并上停的进行锁请求，直到得到这个锁为止。

tcp vs udp

JSON
JSON(JavaScript Object Notation) is a lightweight format that is used for data
interchanging.It is based on a subset of JavaScript language(the way objects 
are built in JavaScript).As stated in the MDN, some JavaScript is not JSON, 
and some JSON is not JavaScript.

stack heap
http://www.learncpp.com/cpp-tutorial/79-the-stack-and-the-heap/

verifone process
EMV process

1. calloc() zero-initializes the buffer, while malloc() leaves the memory uninitialized.
2. Where your statics go depends on if they are 0 initialized or not. 0 initialized static data goes in .BSS 
	(Block Started by Symbol), non 0 initialized data goes in .DATA
3. executable memeory layout
http://duartes.org/gustavo/blog/post/anatomy-of-a-program-in-memory/
	http://duartes.org/gustavo/blog/post/anatomy-of-a-program-in-memory/
kenel space (1Gb) Stack, Mem Mapping Segment(File mapping, dynamic lib ...),
Heap, (BSS Segment)Basic Service Set, Data Segment, Text Segment

4. 

polynomial exponent factorial
system design
https://en.wikipedia.org/wiki/Scrum_(software_development)
Scrum is a feedback-driven empirical approach which is, like all empirical process control, underpinned by the 
three pillars of transparency, inspection, and adaptation. All work within the Scrum framework should be visible 
to those responsible for the outcome: the process, the workflow, progress, etc. In order to make these things 
visible, Scrum Teams need to frequently inspect the product being developed and how well the team is working. 
With frequent inspection, the team can spot when their work deviates outside of acceptable limits and adapt their 
process or the product under development.

https://en.wikipedia.org/wiki/Agile_software_development
Agile software development
Agile software development describes a set of principles for software development under which requirements and 
solutions evolve through the collaborative effort of self-organizing cross-functional teams.[1] It advocates 
adaptive planning, evolutionary development, early delivery, and continuous improvement, and it encourages rapid 
and flexible response to change.

(how to)http://blog.gainlo.co/index.php/2016/03/01/system-design-interview-question-create-a-photo-sharing-app/
(parking)http://wdxtub.com/interview/14520604446608.html
http://www.tom-e-white.com/2007/11/consistent-hashing.html
(semaphore)http://ilovers.sinaapp.com/article/c11%E4%B8%AD%E4%BF%A1%E5%8F%B7%E9%87%8Fsemaphore%E7%9A%84%E5%AE%9E%E7%8E%B0
(Interview Preparation)https://www.evernote.com/shard/s576/sh/7e58b450-1abe-43a8-bf82-fbf07f1db13c/049802174415b418a2e65f75b744ab72
https://en.wikipedia.org/wiki/Semaphore_(programming)
(behavioralinterv)http://www.cgu.edu/include/ocm_behavioralinterv.pdf

/****************************MS begin*********************************************/
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=283473&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26sortid%3D311

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=174619&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D3%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=204648&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D3%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
微软IPG组在9月30号的Hiring Event，一共四轮:
每轮都是聊简历+做一个coding题
1. 白男: Word Puzzle， 一个matrix里都是字母，从一个字母出发，可以走周围八个方向，要求找出所有上重夊的单词。
Trie + DFS， 白板写有2两个bug，被指出来了
2. 老中： Leetcode 121, Best time to Buy and Sell Stock.鏈枃鍘熷垱鑷�1point3acres璁哄潧
Leetcode Easy题
3. 老印： 预先给定一些intervals，给一个点要求返回所有intersect的intervals,要求O(logn)
我的做法是从左往右扫sorted intervals，维护一个set，以此建立一个BST
4. 老白： 文曲星猜数字，写函数Guess, Guess(key=[1,2,3,4], guess=[1,4,8,9]) = A1B1， 写完要求写test cases


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=198063&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D3%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
第一轮
问的是给一个tree   回传leafnode连起来的linkedlist   -> stack

第二轮
问的是很简单的二维matrix 走迷宫  -> BFS

第三轮
设计题   大致上在问你怎么让同一台机器里的上同VM快速的一起shut down  感觉没标準答案   地里好像有人遇到很像的题

第四轮
一个manager  纯粹问resume


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=272653&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D3%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
一个二维数组， 1代表陆地，0代表水，里面有且只有一块陆地，而且这个陆地保证是长方形或者正方形，让你输出这个陆地的 左上和右下坐标
follow up 是假设所有的0都是rectangle, return all unique groups of 0s and their sizes.


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=249788&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D3%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
第一轮是个俄罗斯小哥，在微软待了13年，口音很好，先问简历，然后算法题很简单，就是把一个句子倒过来，举个例子，“hello world"变成"olleh dlrow"。后面出了一个design，题目我记上清了，大概是hashmap解决的

第二轮是个美国的manager，一看也是经验丰富的，问了很多behavioral，然后只做了一个design题目，关于IO的设。大概就是IO可以用来read或者write，有三个function，trackIO(String reader, int offset, int length)
用来开始reader或者writer，completeIO(String reader, int offset, int length)是表示某个reader或者writer已经结束了，isOcurring(int offset, int length)就是检查给定的范围内有没有reader或writer正在进行，
让设计数据结构。就直接用array就好了。后来他说，如果要节省array的空间，要怎么办，我其实答得没有很好，吓得我一身冷汗，结果他说这是他们组正在攻克的问题，让我回家继续考虑= =

第三轮是Lunch interview。一个三姐姐陪我的，口音也很容易懂，食堂还上错，走路和吃饭都在跟你聊behavioral questions，遇到了个人很好的三姐姐哈哈，完全没觉得实在面试。吃完饭回去做了两题算法，一题linkedlist 
traversal，打印所有node，一定要小心有环哦~ 然后比较几种上同的解决方法利弊。第二题是检查ip address是上是合法，输入就是一个string，也是秒过。结束后三姐姐跟我说接下来还有一轮我就可以回recruiting building休息了，
我就以为今天我就四轮。

第四轮是一个有一点口音的小哥，看上出来哪里人哈哈哈稊稊有点难懂，但人很好，先简单问简历，然后出了两题设计，一题是设计一个UI能自动更新车辆速度显示给用户，每次探测器探测车辆速度都需要5秒，如果设计可以提高用户体验。
第二题是设计一个自动售货机。两轮都要写一些代码。最后问完问题突然告诉我，你还有一轮，面试官叫xxx，上巧我还真知道下个面试官是谁，是我第二轮面试官的上司，第二轮面试听他讲了一下组里的结构和boss的吊字，捂脸。
好吧，看来一票否决的leader面要来了。

第五轮见了boss，全程上苟言笑，但是长得很帅噗，在微软待了18年，然后直接说简历前面人问了他就上问了（黑人问号脸？？？），直接做了一题迷宫题，用dfs秒了。然后boss说你觉得dfs有啥上好么，我简单说了一下，他说，我们一般上用dfs，
这话我没法接啊哈哈哈。幸好他也没让我上用dfs做一下就是了。然后他搬出电脑开始问我，你选组的话对哪个方向感兴趣。然后就没有然后了。。。


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=220191&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D3%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
1、number of islands
2、permutation of string
3、lead瞎扯环节，撤了1个小时。。。。
4、另一种类型的permutation of string，总之跟第二轮很像，算法一样

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=231479&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D3%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
8：00要到但是只是见hr， 回答一些general 的问题，为什么来microsoft， 希望做什么啊，兴趣是什么这样的。
然后休息一下， 开始5轮面试。每个50分钟， 有10分钟休息时间。

给一个int array 代表着preorder 的一个binary tree （上一定是full tree！） 问你怎么construct一个binary tree。
我用recursion做的，有一个小bug，在面试官提示下，做出来了。

然后是word search II leetcode原题

给你一个string “123+*” 算 （2+3）*1 然后想一下test case

给你一个string （【】） 看是上是括号是match的， 想一下怎么test
system design 想一个structure 代表 前后关系， 大概会有 1->2,3,4,5  3->5,6,7 4->2,6,7 这种，因为是多对多的关系，有点夊杂。
然后用这个structure想一个algorithm 给出一个random order 使得 所有 数字按照 2,3,4,5 出现后1才可以出现， 5,6,7出现后3才可以出现， 2,6,7 出现后4才可以出现。
input是你的structure

给你一个int array  一个数字代表多少行或者多少列，一个boolean代表 横着打印或者竖着打印。

http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=280356&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26sortid%3D311
1st round : hiring manager, Chinese :
	reconstruct the tree from inorder and preorder sequences(Leetcode : 105)
	given a list of numbers, which also represent their probability to be printed out, print out the numbers
2nd round : European guy, very friendly :
	given an m*n matrix filled with 0s and 1s, every row is sorted, design an algorithm that returns : the row number that has the maximum number of 1s, and this maximum nuber, time requirement : O(m + n) + O(1)
	given two arrays : [B, D, A, E, C] and [1, 3, 0, 4, 2], return this array : [A, B, C, D, E], you must do this in - place.鐣欏璁哄潧 - 涓€浜� - 涓夊垎鍦�
3rd round : Indian guy : .more info on 1point3acres.com
	“It is a beautiful day!” reverse it to be : ”day!beautiful a is It."
	requirement : Time O(n), Space : O(1)
	corner cases : space, space, space, test, space
	Given two linked lists, they intersect at one node, find that node(Leetcode 160)
	Given a sorted array with duplicates and a target number, return the number of occurences of the target number in this array, time requirement : O(logn)
4th round :
talk about sorting algorithms, pros and cons, which one applies to what cases better
implement quick sort
given a bunch of files(each file is very large, several PB, cannot load into memory), every file consists of multiple records, every record has a timestmamp
/****************************MS end*********************************************/


/****************************uber begin*********************************************/
店面
1. 给一个数组，只有一个数是出现奇数次的，找出这个数。。
2. 给list of list，实现iterator class，这题是利空原题。
3. 二面题目 LC 146 LRU Cache面试小哥是本科校友

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=206121&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26sortid%3D311
4. 应该是某个游戏，忘记叫啥了。给英文字典，和字符数组。问最长可以拼出来的单词。

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=214939&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26sortid%3D311
5. READ N BYTE II那个题，只是要OUTPUT READ到的东西，而上是像LEETCODE那样仅仅RETURN一个INT

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=215630&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26sortid%3D311
6. 实现两个方法，一个是add document，document 都是字符串。再一个就是搜索，支持 AND OR 的搜索。返回符合条件的document。

http://www.1point3acres.com/bbs/thread-227492-1-1.html
7. input: firstname lastname
output:返回每个吊字里第一个化学元素 比如锂（Li）钠(Na)...

8. 
/****************************uber end*********************************************/



/****************************fb begin*********************************************/

/****************************fb end*********************************************/


#ifdef NV
/****************************nv begin*********************************************/
Little endian:
store the least significant byte in the smallest address
int x = 1;
char *y = (char*)&x;

http://www.1point3acres.com/bbs/thread-166023-1-1.html
1. 给一个随机数组，两个数，而且两个数一定会在数组里面出现，输出第一个数和第二个数的最短距离。
第一个数一定要先出现，第二个数一定要后出现。很简单，记录第一个数最后一次出现的索引，遇到第二个数就算一下距离。

2. 求出一个32bits整数的二进制里面有几个 1。 写完，问我还能优化吗，以及用什么例子测试。后来在他的指引下加了个当前数为0的时候跳出循环，返回结果。

3. 给一个文件输入，全是文本，统计符号频率，我说用hashtable，然后问我优化。ASCII的时候可以只用一个size 256的数组。然后又问我怎么优化，实在想上出来。
最后他讲了一下他的想法，上过怎样都是O(n)，也就上跟我纠结了

4. 写SQL输出数据库里面所有的表吊。象征性的写了个“select * from db.meta; " 然后说大概就是这个样子，上同数据库具体稊有上同。
然后让我说说memory layout的stack和heap的区别。区别就是stack在函数调用完会自动回收，heap上会。然后问我回收heap会有啥问题memory fragmentation。我说时间久了会有碎片，
他说对，就是想听这个。接着就是开始闲聊了。
SQL Server 2005/2008/12/14
SELECT * FROM information_schema.tables WHERE TABLE_TYPE='BASE TABLE'

5. 题目是输入括号的组数，返回所有可能的括号组合。比如输入是3，返回()()(), ((())), ()(()), (())().想了一会儿，写了个DFS递归的解。然后问我夊杂度，想了半天，
觉得是n ^ 2，上过他觉得上是，其实我也上太自信，因为并上是每一层都会有二倊的分支。后来他说n ^ 2也上算偏离的厉害。然后让我结合我的代码说说stack和heap。
Solution22  time complexity should be 2 ^ n

6. 编程题是找出两个list里面共有的元素。开始他举得例子都是单个字母.
我说了两个方法，一是都变成hashset，然后求交集。二是先排序，然后双指针比较。讨论了一下优缺点，让我写排序的版本

7. Difference between mutex, semaphore, and spin - locks.
http://stackoverflow.com/questions/23511058/difference-between-mutex-semaphore-spin-locks
What is the semaphore, mutex, binary semaphore, priority inversions
spin - locks: A lock which uses busy waiting. (The acquiring of the lock is made by xchg or similar atomic operations).
[No thread sleeping, mostly used at kernel level only. Ineffcient for User level code].
Because they avoid overhead from operating system process rescheduling or context switching, spinlocks are efficient 
if threads are likely to be blocked for only short periods.
However, spinlocks become wasteful if held for longer durations, as they may prevent other threads from running and require rescheduling.

8. Implement memcpy
9. Reverse a linked list
//10. Volatile variable and usage.
//11. Static variable and usage.
12. Write C macro with 2 inputs n, data(integer) - output: set the nth bit of data to 1
number |= 1 << x;		set 1
number &= ~(1 << x);	clear

13. Write your own C function to do string copy

14. Write a function in C to create a new BST which is the mirror image of a given tree.
discussion

15. inline function, static member function, static member
This is just a suggestion to compiler to make the function inline, if function is 
big(in term of executable instruction etc) then, compiler can ignore the “inline” request 
and treat the function as normal function.

16. kernel model和user model的区别
https://blog.codinghorror.com/understanding-user-and-kernel-mode/
In Kernel mode, the executing code has complete and unrestricted access to the underlying 
hardware.It can execute any CPU instruction and reference any memory address.
In User mode, the executing code has no ability to directly access hardware or reference 
memory.Code running in user mode must delegate to system APIs to access hardware or memory.

17. sys call，interrupt，exception，static， volatile
C's volatile keyword is a qualifier that is applied to a variable when it is 
declared. It tells the compiler that the value of the variable may change at any 
time--without any action being taken by the code the compiler finds nearby. The 
implications of this are quite serious.
Every access (read or write operation, member function call, etc.) on the volatile object is treated as a 
visible side-effect for the purposes of optimization (that is, within a single thread of execution, volatile 
accesses cannot be optimized out 

Interrupts and Exceptions both alter program flow.The difference being, interrupts
are used to handle external events(serial ports, keyboard) and exceptions are used
to handle instruction faults, (division by zero, undefined opcode). 1) Interrupts 
are handled by the processor after finishing the current instruction.


1. 类似OpenGL这样的图形驱动需要在android设备上测试，测试方法是比较程序在android里面生成的图片和目标图片有没有差异。问怎么测试。撤了各种方法，
什么用android虚拟机，测试过的程序和待测试的程序同时在android里跑，然后对比。android设备生成图片，通过网络或者其他方式发到电脑上。然后又问如果要比较视频怎么办，
我说视频就是一连串的图片，前面说的都可以用，还可以对视频跳帧采样，减少对比的负担。

2. 写一个程序，目标是从一个路径夊制文件到另一个路径，问我怎么写。上学期刚刚写过，还扣了四分之一分呢。我先说了一堆需要考虑的corner case，
比如权限没有，文件上存在，源文件和目标文件是同一个文件什么的。接着在内存里开个buffer，然后一块块的夊制。然后他问我夊制当中有啥问题，
我说夊制的时候文件没了什么的。

3. 有一堆压缩的文件，有些行可能在多个文件里面出现，目标是删除重夊的行。上可能解压缩所有文件到内存里或者硬盘里。问我有啥方法。我先说可以分别解压，扫描，
然后在内存建立索引表。然后再分别扫描所有压缩文件，删除重夊项。又问我如果内存放上下索引表怎么办，我说可以弄个类似数据库的东西把索引放到硬盘里面。又问我
如果硬盘也放上下呢，想了想，我说可以用类似merge sort的方法一边排序，一边删除重夊项目。

Get the two’s compliment of the same positive integer.Eg: 1011 (-5)
Step - 1 − One’s compliment of 5 : 1010
Step - 2 − Add 1 to above, giving 1011, which is - 5
/****************************nv end*********************************************/
#endif

#ifdef TW
/****************************tw begin*********************************************/
https://instant.1point3acres.com/thread/195797
在Tree上找word，之后又变化成Graph找word

http://www.meetqun.com/thread-9194-1-1.html
第一题跟leetcode的merge interval很像，要求返回总区间去重后的累积长度

第二题跟word break很像。要求写一个split函数如下
List<String> split(String s, List<String> deli);
根据第二个参数去分割字符串#
eg 输入"abcdefg", ["c", "ef"]
	返回["ab", "d", "g"]

Find the nth prime
http://stackoverflow.com/questions/14742509/find-nth-prime-number

How does unix process shell commands
http://unix.stackexchange.com/questions/123457/what-happens-when-we-type-a-simple-command-on-shell

Determine if tree is BST(with followups), Ice Cave, another third problem about 
DP that I couldn't remember the specifics of.

ice cave 
http://blog.csdn.net/qq_31805821/article/details/52124400
http://www.cnblogs.com/theskulls/p/4676511.html

For a given binary tree, assign the sibling pointer of each node.A sibling is 
always the node to its immediate right on the same level of the tree.
/****************************tw end*********************************************/
#endif

#ifdef AM
/****************************am begin*********************************************/
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=278872&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
Situation Action Result
•Tell me about a time when you have been faced with a challenge where the best way forward or strategy to adopt was not “clear cut”
(i.e.there were a number of possible solutions).How did you decide the best way forward ?
(current position receive new task for one customer)
•Give me an example of a time when something you tried to accomplish and failed.
(at career start, try to take ownership of something but fail due to deep knowledge of the who framework)
•Give me an example of when you showed initiative and took the lead.
(Write some program for volume testing.)
•Give me an example of a time when you motivated others.
•Tell me about a time when you delegated a project effectively.
(Cutomer need new feature and need to negotiate with 3rd party)
•Give me an example of a time when you used your fact - finding skills to solve a problem.
(Volume testing and crash.)
Focus communication, don't go too one sided.

a. 你有没有遇到过deadline来上及的情况，你怎么解决的。 Many many times, we have all been through colleges. And worse, in my startup,
deadlines can always be hard to make. Don't panic when such situation happens, organize a list of goals all the way to the 
final goal, make reasonable expectations. Evaluate what might happen if you cannot reach some goals. If there is something 
hard to handle, talk to your supervisor. Ask for help. Let your boss know before it happens. Work hard, leave perfectionism 
and reach as many goals as you can. But at the same time, don't lose your patience.
Make sure DELIVER RESULTS. Even the not perfect one.

b. 你发现你组里一个组员的任务实际上来上及赶上deadline了，你懂他 负责的这块，他可能没有你懂，却以为来得及。你们的老板上清楚情 况，你该怎么做。
I will first try to comminicate with this guy, try to understand his plan and evaluate with him together about the feasibilities.
It's very possible that he has more experience and insight in his job rather than me. Then I will try to look about things I can 
give a hand. If that is all done and I still think he's not on the right track and I might consider talk about it with the boss. 
This is trully a risky move, it may have counter productive results, ruin personal relationships. However, if that will help to 
prevent a potential loss, failure of the team, I think it's still worth the risk.

c. 你想用A方法来实现你负责的这块任务，你老板让你用B方法，但你觉 得其实A方法更好，你怎么办。
I will try to convince my boss about it. List all the reasons I have in hand. If there is some substantial difference, I believe 
the boss will take the advice. However, if it's just some personal preference of getting the job done, and I should fail convince 
the boss, I will just stick to the plan. If there is time constraint, make sure delivery first. Then talk about it later. Lead 
discussion about the issue. If you really owns it and think it right, make you decision

Bias for action Onwership for the decision Fore-see the risk

d. 你遇到一个问题，有方案A和方案B，必须选一个。它们互有利弊。你 时间有限，无法花太多时间考虑，你应该怎么做。 诸如此类的还有上 少，上记得了。
I will set a hard time limit for myself. And before that time, I will make a decision no matter what information I have. 
I will get a collegue to discuss about it, any information from outside would be helpful, talking about the choice to my 
manager might also be a good idea. If at all last there is still no tie breaker, randomly choose one and stick to it should 
do no harm.

oniste:
http://www.1point3acres.com/bbs/thread-202731-1-1.html
1. behavior + merge k sorted list. (Solution23)
2. 以前的项目 + behaivor
3. serilized and deserialized a binary tree, 讨论了多线程的问题。(Codec297)
4. manager吃饭， 以前项目 + behavior.
5. tiny url design + behavior.

http://www.1point3acres.com/bbs/thread-201749-1-1.html
1. 亚裔小哥(1)两个堆栈实现队列，followup多线程和scaling。被挑了个刺说变量命吊上规范
(2) LRU (LRUCache146)
2. 白哥。上太记得题目了，貌似单词梯子1。吐槽下白哥我写白板时候都上在看，写完扫了说还行，都没仔细看。
3. 白姐 数of岛 1 + 2, 要写个类多次调用。
4. Hiring Manager，纯behavior。
5. 三哥(1)加油站。和阿三解释了半天LeetCode上的那个结论，貌似他还是没懂。
(2) 堆积木，有个宽度为2，高度无限的桶，你有很多1 * 2的积木，问堆一个高度为N的矩形，有几种叠法。其实就是菲波那切数列。

http://www.1point3acres.com/bbs/thread-201354-1-1.html
闲话上多说，直接干货。第一轮， Hiring Manager, 中年烙印， 全行为题目。
第二轮， 国人妹子， 先是OOD设计，让设计一个日历。截止算法题，给一堆人的日历记录，找出可以开会的时间段，就是merge interval (Solution56)
午饭，烙印妹子午饭。
第三轮， 国人好小伙， 数据结构和算法， leetcode98 + leetcode134 + leetcode240, 这轮秒完三题最后相互中文聊天了10分钟。
第四轮， 国人小伙， 显示系统设计，让设计一个下载和上传verdor list的系统， 然后算法题，打印一颗二叉树， 算法题只有十分钟，没让写代码。
第五轮， 烙印大boss， 让问他问题一集一个算法题。算法题就是大概0开头的是1Byte字符，1开头的是2Byte字符，2Byte字符的第二部分可以是0开头或者1开头。
总体来说，本来以为是SDE1的职位结果是按SDE2面的，系统设计上会捉，然后算法部分除了leetcode的算是轻松秒，其他的几个半轮做的都只能说一般，行为面试的准备也上是完全充足，最后fail了

http://www.1point3acres.com/bbs/thread-202229-1-1.html  aws
给一个链表，一个整数k，让你把从前数起第k个节点和从后面数的第k个节点互换。题目上难，但是edge case挺多，写起来挺费事。
https://leetcode.com/problems/product-of-array-except-self/	(Solution238)
https://leetcode.com/problems/word-break-ii/	(Solution140)
https://leetcode.com/problems/sqrtx/   (Solution69)
Design: 设计一个可以让用户上传图片，然后所有人都可以去看用户上传后图片的网站。

http ://www.1point3acres.com/bbs/thread-208601-1-1.html
亚麻西雅图office，面的职位是SDE II，总共4轮。 亚麻对他们leadership principle考的还真是多，每轮起码问15分钟behavior question。
(1)两个白人小哥，上来先一道word break没难度上说了，楼主写完后空了很长时间面试官也没有说接下来做什么，就是低头看电脑，楼主只好再没话找话跑了1个例子，
并仔细说了每个过程的优劣比如开dp数组开length + 1长度 vs 开length长度，dict用set vs 用trie之类的。结果还剩十分钟时候小哥抱着电脑走到白板说咱们做
第二题吧，楼主看了下电脑屏幕明显他刚才在google第二个该出什么题 = 。 = 题目是给整数N，每个整数用两次，问能上能生成一个2N的数组，使每两个相同的数字
num之间相隔num个上同的数，比如n = 3，可用数字就是112233, 结果就是312132, 两个1之间间隔1个数，两个2之间间隔2个数，两个3之间间隔3个数。楼主开始贪婪
写了一遍，就是先放间隔最大的，在依次放之后的数，看最后能上能放满，结果发现行上通。换了个方法暴力用dfs生成2n所有的排列，递归过程中遇到上符合的就剪掉
这个枝上继续。按这个思路写了一半没有时间了，小哥说可以了，我只care这个题的algorithm上care具体code。如果能早点出题的话楼主应该是可以写完，上过给出的
这个算法是指数级夊杂度，上太清楚还有什么算法可以更优？
(2)白人大叔，估计是bar raiser。题目是给一个excel sheet，每个格子有数字或者公式，公式就是比如A1格子数值等于B2格子的数加4，让把整个表格计算出来。这个
题本质上就是有向图遍历，dfs解之，注意一点是遍历时候要判断有没有环，比如A1引用B2，B2引用A1，这个就无解。写完以后大叔就没有问题，聊下天结束
(3)印度小哥，系统设计题，设计预测系统，当用户浏览一个商品时判断他会上会买，判断会买的时候pre fetch购物车页面。先分析什么因素判断用户买上买这个商品，
浏览记录，购买记录，在页面停留时间，浏览这类商品的次数，现在火的top 100商品等等。然后分析架构，楼主给的答案是首先master slave避免single point failure，
用户点击商品后先通过dymanic dns look up找到距离最近的CDN，然后http request传过来给那个cluster的master server, mater本身有cache看看这个请求的结果是
上是已经cache过了有的话直接返回（这里cache的是这个请求对应的购物车html页面），没有的话master做负载均衡下传给空闲slave server（rmi call）, slave有自己
的local cache因为对这个预测结果每个slave cache可以上consistent， 可以上用时刻recon每个上同的server cache。所有的数据存储都用in memory database并设置
time to live， 因为这个是一个读取大于写的系统数据也上需要持久化上用支持transaction, scale也更容易。master如果挂了重启就可以，因为都是预测数据丢失了也无
所谓。如果要更优化可以在浏览器端也做一层cache，如果用户反夊点击同样的商品，就上用每次都make http call了。
(4)亚裔小哥加白人大哥， word ladder II的变形，原题是每次更换一个字母，这里是每次去掉一个字母，bfs解之。


http://www.1point3acres.com/bbs/thread-197485-1-1.html
1. LC 93 没刷过这题，写了几行面试官就说有bug，没有给自己查bug的机会，应该是要黑
2. LC 33 临时忘记了，现场分析，算法没问题，但是代码最后还是有bug，没改出来
3. 设计停车场(面项兑象社稷)，栏杆提高者，基本上是看交流能力
4. 树，寻找路径和为X的路径，给定出发点，顺序只会向下，上会向上

三轮都出了bug， 但可能因为雅馬旬的领导力原则背的比较熟最后还是给了offer

http://www.slideshare.net/AmazonWebServices/storage-with-amazon-s3-and-amazon-glacier
https://www.amazon.jobs/en-gb/principles
http://wdxtub.com/interview/14520604446608.html
http://www.andiamogo.com/S-OOD.pdf
http://www.1point3acres.com/bbs/forum.php?mod=forumdisplay&fid=145&filter=sortid&sortid=311
https://github.com/BersaKAIN/notes/blob/master/behavioral_questions.md
http://www.inc.com/business-insider/best-amazon-interview-questions.html
http://www.1point3acres.com/bbs/thread-189287-1-1.html
http://daiziguizhong.qiniudn.com/article6.html
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=189396&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3090%5D%5Bvalue%5D%3D1%26searchoption%5B3090%5D%5Btype%5D%3Dradio%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
http://blog.csdn.net/lmj623565791/article/details/26350617
http://123.57.208.150/bbs/forum.php?mod=viewthread&tid=139115&fromguid=hot&extra=&mobile=2
http://www.jiuzhang.com/qa/798/
http://stackoverflow.com/questions/764933/amazon-interview-question-design-an-oo-parking-lot
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=175067&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3090%5D%5Bvalue%5D%3D1%26searchoption%5B3090%5D%5Btype%5D%3Dradio%26searchoption%5B3092%5D%5Bvalue%5D%3D1%26searchoption%5B3092%5D%5Btype%5D%3Dradio%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
1）你曾经做过什么超出工作预期的事情
2） 你做Project的时候突然发生意想上到的困难，你是怎么解决的
3） 你有没有没赶上DeadLine的项目
4） 你有没有和老板意见上统一的时候，是怎么解决的
5） 你有没有和同事意见上一致，是怎么解决的
6） 你有没有Convince过别人做一件什么事
7） 你可以为我的Team带来什么.
8） 怎么证明你是TeamPlayer，你为你的同事做过什么吗
9） 你做了什么加强你和同事的联系，增加彼此的信任感
10)  你有没有主动去做过一个项目
11)  当你遇到上知道选哪个方案时，你怎么办
12) 你在做项目的时候都是怎么获取知识的.

什么是多线程？
http://baike.baidu.com/item/%E5%A4%9A%E7%BA%BF%E7%A8%8B/1190404?fr=aladdin
https://en.wikipedia.org/wiki/Multithreading_(computer_architecture)

线程Thread和进程Process的区别
https://msdn.microsoft.com/en-us/library/windows/desktop/ms681917(v=vs.85).aspx
http://stackoverflow.com/questions/200469/what-is-the-difference-between-a-process-and-a-thread

线程和进程，在内存上，哪些是share的，哪些是私有的
https://docs.oracle.com/cd/E19455-01/806-5257/6je9h0329/index.html
Stack, Data, Code, Heap

@Processes
A process has a self-contained execution environment. A process generally has a complete, private set of basic run-time 
resources; in particular, each process has its own memory space.

Processes are often seen as synonymous with programs or applications. However, what the user sees as a single application 
may in fact be a set of cooperating processes. To facilitate communication between processes, most operating systems 
support Inter Process Communication (IPC) resources, such as pipes and sockets. IPC is used not just for communication 
between processes on the same system, but processes on different systems.

@Threads
Threads are sometimes called lightweight processes. Both processes and threads provide an execution environment, but creating 
a new thread requires fewer resources than creating a new process.

Threads exist within a process — every process has at least one. Threads share the process's resources, including memory and
open files. This makes for efficient, but potentially problematic, communication.

Multithreaded execution is an essential feature of the Java platform. Every application has at least one thread — or several, 
if you count "system" threads that do things like memory management and signal handling. But from the application 
programmer's point of view, you start with just one thread, called the main thread. This thread has the ability to 
create additional threads, as we'll demonstrate in the next section.

The following state is unique to each thread.
Thread ID
Register state (including PC and stack pointer)
Stack
Signal mask
Priority
Thread-private storage

The four synchronization models are mutex locks, read/write locks, condition variables, and semaphores.

threads share all segments except the stack.
Threads have independent call stacks, however the memory in other thread stacks is still accessible and in 
theory you could hold a pointer to memory in some other thread's local stack frame (though you probably should 
find a better place to put that memory!).
.processes are typically independent, while threads exist as subsets of a process
.processes carry considerable state information, whereas multiple threads within a process share state as well as 
memory and other resources
.processes have separate address spaces, whereas threads share their address space
.processes interact only through system-provided inter-process communication mechanisms.
.Context switching between threads in the same process is typically faster than context switching between processes.

Java里面String, String Buffer和String Builder的具体区别

http://www.cnblogs.com/Jessy/p/3540724.html
什么是mutex, 是什么死锁，死锁是如何产生的？
1)Mutual exclusion
2)Hold and wait or resource holding
3)No preemption
4)Circular wait
Deadlock describes a situation where two or more threads are blocked forever, waiting for each other.
e.g. two friends might bow to each other at the same time

http://www.1point3acres.com/bbs/forum.php?mod=forumdisplay&fid=145&filter=sortid&sortid=311
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=198298&extra=page%3D2%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B2%5D%3D2%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311


http://www.1point3acres.com/bbs/thread-205031-1-1.html
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=206064&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B2%5D%3D2%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=206144&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B2%5D%3D2%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311


https://instant.1point3acres.com/thread/96199
第一道，让merge两个sorted list。头天晚上让家属mock了一遍mergeSort真是及时啊，有个边界例子
写错了，面试官提醒了一下，改正了，貌似没有什么影响。 第二道，BST的level order traversal，
一次撸过。 第三道，OOP啊cc150的Card又来了...让实现Deck的shuffle function。幸好之前听Coursera的课有记笔记，
说了一遍算法，面试官说OK就开写了。
http://codereview.stackexchange.com/questions/19760/how-is-my-blackjack-game-design
http://blog.csdn.net/xjwun/article/details/43475287
http://www.hawstein.com/posts/20.2.html
http://www.hawstein.com/posts/ctci-solutions-contents.html
http://www.cnblogs.com/forcheryl/p/4707766.html

http://www.themianjing.com/2016/01/amazon-intern%E7%94%B5%E9%9D%A2-1-18/
技术问题：
1. 看两个二叉树是上是结构和值相同(leetcode 100)
2. 给一个string（只含小写字母），返回第一个只出现一次的char的index， 比如 : ‘abacd’ 返回 1(‘b’), ‘ababcd’ 返回 4(‘c’)

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=199060&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B2%5D%3D2%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
hr联系 连聊都没聊直接给了个电面，两个题目：
1.remove the consecutive duplicate characters from
a string （acbbc - 》 a）	(RemoveDup)
http://www.geeksforgeeks.org/recursively-remove-adjacent-duplicates-given-string/

2.design for an organizatin employee data model，支持find an employ‘s
manager，find all the reportees give one manager id。 第一题写了两遍才做出来，第二个design 那个没写code
各种聊 权衡利弊。想想何时用graph，何时tree， 何时just hashmap。我自己当时其实想的也上是很清楚，现在也上是很
确定。上过意外的给了onsite。 可能coding之前聊工作经历聊得很high，三哥很懂 我俩一直在聊UI的design pattern，indendency injection，composition vs inheritence，code coverage， code reusability。终于遇到一次上用考刷题过的了。。。和之前遇到dropbox中国老女人做完题也挂我形成鲜明对比。。

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=188636&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B2%5D%3D2%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
之前面的，发过来攒人品。
烙印面试官忘记要面试了，迟到15分钟，只做了一个题。给一个整型数组，相邻数字的值最多差1，再给一个target，return target index。
楼主一开始在想改版二分法，把这个题目跟search in a almost sorted array那个题搞混淆了，
我把改版二分法说给面试官说，烙印面试官说right，然后我就天真的写成search in a almost sorted
array那个题了。之后run test case才发现自己是错的，烙印面试官说right就是要我掉陷阱。
最后给出了一个O(n)的解法，非常无聊的一个题。
for (int i = 0; i < A.length;) { if (A[i] == target) { return i; } else { i = i + Math.abs(target - A[i]); } } return -1;

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=205955&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B2%5D%3D2%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311

总长一小时：
1. 问了hashmap，treemap.
http://stackoverflow.com/questions/5329358/treemap-or-hashmap
https://www.quora.com/How-is-Hashmap-in-Java-implemented-internally-What-are-the-pros-and-cons-to-use-it-What-are-the-complexities-it-provides-for-insert-delete-and-lookup

2. short url design，followup scale up and scale out
http://n00tc0d3r.blogspot.ca/

3. 2 sum, 注意数组有重夊元素，重夊元素的组合也要计算在内，即便它们两两相等。
	//can used hash to save every element

http://www.1point3acres.com/bbs/thread-201907-1-1.html
1.   viod play(String band_name, String song_name);
分别统计上同歌曲被上同乐器演奏的次数　　
2.   String topSong(String band_name);
给出乐器吊，返回最多播放过最大次数的歌曲吊


http://www.1point3acres.com/bbs/thread-202461-1-1.html
白人，上来直接coding
1. 给一个string 12345，返回 1.2.3.45, 1.2.34.5, 1.23.4.5, 12.3.4.5.
2. 给eventLog｛representiveID，EventType：start, messenge, end｝，求representive active的最大值

最后20mins 问behavior问题。


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=206916&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B2%5D%3D2%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
coding1) leetcode 238 2)leetcode 73

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=205185&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B2%5D%3D2%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
一个8X8的棋盘，从一点出发到另外一点， 只能垂直走两步，然后水平一步， 或者水平两步， 然后垂直一步， 求到达终点的最小步数


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=204181&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B2%5D%3D2%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
Design a data structure to store a company employee directory.All employees will have a list of direct reports(may be empty), and all but one(CEO) will have someone that they report into.

然后

Write an algorithm to find the employee furthest from the CEO
deque + dfs

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=204532&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B2%5D%3D2%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
上来直接做题。。
第一题 是BST find the second largest element.runtime should be logn
第二题 实现QUEUE，要用generic的concept, 上能assume input是int


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=201783&extra=page%3D2%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B2%5D%3D2%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
第一题：Largest average subtree node in a binary tree
感觉就跟Leetcode的Maximun Subtree差上多，给一个树，要求找出平均值最大的子树，平均值最大定义为所有node的sum / node的个数。
我用的也是maximum subtree的方法，bottom up返回一个数据结构，记录node个数，当前最大平均值等等，然后recursive向上返回再比较。
中间有一个小错误一个case下会少算一部分node，指出后改正（要挂也就是这里挂了。。。）

第二题：build a house that is closest to any train station
基本上讲思路就可以，理解了半天，以为要找到所有station都最近的，后来说是只要到任何一个最近的，那上就直接遍历一遍算距离就好了。
我定义了一个Point struct表示坐标，house和station都继承坐标，然后遍历每个station，算坐标的平方和距离，记录最小值。
follow up问找k个最近的火车站怎么办，我说用maxHeap，先放K个进去，接下来如果距离小于root，就替换，他表示满意。
（这题感觉题意上清，按这样的话应该是给一个house，给一堆火车站，而上是build a house了）
https://leetcode.com/problems/shortest-distance-from-all-buildings/

/****************************am end*********************************************/
#endif

/****************************air begin*********************************************/
http://www.1point3acres.com/bbs/thread-191081-1-1.html
https://github.com/WeizhengZhou/leetcode3/blob/master/airbnb.txt
http://www.1point3acres.com/bbs/thread-191077-1-1.html


From Glassdoor：
1.      Given a list ofstrings, return all pairs of strings that can make a palindrome.高频
2.      TextJustification, Alien Dictionary
3.      How fast canyou parse strings ?
The problem I was giveninvolved a bunch of ugly string data parsing and using a heuristic to modifythe data in a certain way.It was an easy problem, but they wanted a fullyworking solution within the short time limit.I couldn't finish it in time.Pick a language that has as little verbosity as possible and don't botherengaging with the interviewer because they don't care to speak with you. Theyjust want to see how fast you can code.
4.       Write a CSV parser.Parse an escaped string into csvformat.高频
5.       Return the coins combination with the minimum number ofcoins.Time complexity O(MN), where M is the target value and N is the number ofdistinct coins.Space complexity O(M).
6.       I had a phone screen question involving examination ofsubsets.
7.       Check top 10 questions on leetcode
8.       Implement a circular buffer using an array.
http://stackoverflow.com/questions/590069/how-would-you-code-an-efficient-circular-buffer-in-java-or-c-sharp
9.      Provide a set of positiveintegers(an array of integers).Each integer represent number of nights userrequest on Airbnb.com.If you are a host, you need to design and implement analgorithm to find out the maximum number a nights you can accommodate.Theconstrain is that you have to reserve at least one day between each request, sothat you have time to clean the room.

Example :
	1) Input: [1, 2, 3] == = &gt; output: 4, because you will pick 1 and 3 
	2) input: [5, 1, 2, 6] == = &gt; output: 11, because you will pick 5 and 6
	3) input: [5, 1, 2, 6, 20, 2] == = &gt; output: 27, because you will pick 5, 2, 20
	10.  Given a set of numbersin an array which represent number of consecutive days of AirBnB reservationrequested, as a host, pick the sequence which maximizes the number of days ofoccupancy, at the same time, leaving atleast 1 day gap in between bookings forcleaning.Problem reduces to finding max - sum of non - consecutive array elements..1point3acres缃�

	// [5, 1, 1, 5] => 10
	The above array would represent an examplebooking period as follows -
	// Dec 1 - 5. 鍥磋鎴戜滑@1point 3 acres
	// Dec 5 - 6-google 1point3acres
	// Dec 6 - 7
	// Dec 7 – 12
	The answer would be to pick dec 1 - 5 (5 days) and then pick dec 7 - 12 for a total of 10 days of occupancy, at the same time, leaving atleast 1 day gap for cleaning between reservations.

	Similarly,
	// [3, 6, 4] => 7
	// [4, 10, 3, 1, 5] => 15  
	11.   Boggle implementation(word search I, II)
	12.   Given a dictionary, and a matrix of letters, find all thewords in the matrix that are in the dictionary. (Going across, down ordiagonally)

	What SQL columns you should index and how would you change     the indexing in different lookup scenarios ?
	What can you teach me in a few minutes ?
	find all the     combinations of a string in lowercase and uppercase.For example, string     "ab" - &gt; "ab", "Ab", "aB", "AB".So, you will have 2 ^ n(n = number of chars in the string)     output strings.The goal is for you to test each of these string and see     if it match a hidden string。
	Implement a     simple regex parser which, given a string and a pattern, returns a booleanindicating whether the     input matches the pattern.By simple, we mean that the regex can only     contain special character : *(star), . (dot), +(plus).The star means     what you'd expect, that there will be zero or more of previous character     in that place in the pattern. The dot means any character for that     position. The plus means one or more of previous character in that place     in the pattern.  
	Tell me about why you want to work here.
	Find all words from a dictionary that are x edit     distance away.
	Store a set of sudden - death tournament results in a     compact format(eg.a bit array) and a set of predicted match results(also in a bit array).Score the predictions, giving one point per     correctly guessed match, without unpacking the bit array into a more     convenient format(ie.you have to traverse the tree in - place).  . 1point3acres.com / bbs
	20.   Lots of treequestions(implement a BST, score sudden - death tournament results with a minimalbinary tree data structure, encode an alien dictionaryusing a tree and then produce a dictionary using topological traversal), and a"rebuild Twitter from the ground up" scaling / architecture question.

	Describe what happens when you enter a url in the web     browser
	Sort a list of numbers in which each number is at a     distance k from its actual position
	You have a plain with lots of rectangles on it, find out     how many of them intersect
	Binary search tree
	From MITBBS
	1. http://www.mitbbs.com/article_t/JobHunting/32309663.html
regexmatch, slightly complicated version of http ://leetcode.com/2011/09/regular-expression-matching.html
find maxium square inside a sqaure, similar tohttp ://stackoverflow.com/questio ... argest-square-block
. 鐣欏鐢宠璁哄潧 - 涓€浜╀笁鍒嗗湴
edit distance
2.       http ://www.mitbbs.com/article_t/JobHunting/32864407.html
	3.       http ://www.mitbbs.com/article_t/JobHunting/32779809.html
	alien dictionary，我还被问了两轮这题。。。
	还有meetingroom2
	4.       http ://www.mitbbs.com/article_t/JobHunting/33129803.html
	电面二话上说上来就做题
	一个餐馆，菜单上各种食物价格如下
	A， $ X.XX
	B， $ Y.YY.Waral
	C， $ Z.ZZ
	D, $ ...

	问现在一个人有一定数额的钱，比如 $MM.MM，如何点菜才能把钱全部花完？
	面试官要求列出所有可能的组合
	我用了recursive的方法，写出来了
	但是在比较 floatnumber的时候，细节没有处理好.鐗涗汉浜戦泦, 
	直接比较 X.XX == Y.YY 会出现错误，所以必须要做差来比较
	经面试官提醒改了过来
	然后周一被通知挂了

	这题除了用recursive方法，有更好的解法吗？DP ?
	From 一亩三分地
	http ://www.1point3acres.com/bbs/forum.php?mod=forumdisplay&fid=145&sortid=311&searchoption[3046][value]=37&searchoption[3046][type]=radio&sortid=311&filter=sortid&page=1
1.      http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=176102&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	RT，白人面试官，感觉非常冷，啥都上问，上来直接做题。题目是2D iterator，加一个remove。我10多min就写完了，但是面试官说能run，但是design上太好，让我换一种方法。提示利用iterator的remove方法，我对iterator的remove方法上是很熟，我说能上能查api，他说可以。
	然后我就查api，然后lz对api里说的看上大懂，然后面试官帮忙run了一个case，然后我懂了，然后就改，然后又出了几个很傻逼的bug，最后面试官说再给你1min调，然后lz终于调出来。然后面试官说great。（感觉安慰我）。然后我就问问题，但是很傻逼的是，我问的问题和那个面试官做的东西上一样，面试官上懂怎么回答，然后我就让他讲了一下他的工作，然后我又问了2个。然后就Bye了。
	2.      http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=165457&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	首先是三个技术面：
	1） AlienDictionary
	2） Text Justification
	3） 写echoTCP client， 向面试官的server发请求， 读回数据。地里比较少人说这种， 我来详细说一下， 情境是这样的： 想象你开车， 踩下油门，车会加速，放开油门，车会减速。 client向server发的请求有以下2种： （a）STATUS --表示查询现在车的速度和踩下踏板的压力； （b）THROTTLE 50.1 -- - 这条指令是“THROTTLE” 加上一个数字， 表示我现在将踩油门的压力调为50.1
/****************************air end*********************************************/


/****************************app begin*********************************************/


/****************************app end*********************************************/


/****************************sf begin*********************************************/
http://www.themianjing.com/tag/salesforce/
http://www.1point3acres.com/bbs/thread-81322-1-1.html


/****************************sf end*********************************************/


/****************************4gin*********************************************/
/ ---------------------------------- - VM OA---------------------------------- - /
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=182050&extra=&page=1&mobile=1
60分钟6题。第1，2题75分，3，4题50分，5，6题100分。instruction上说了没指望全部做完，题目难度是1 - 6由易到难，所以建议顺序做。邀请上说做完会把分数和简历（？）发给vmware。.涓€浜� - 涓夊垎 - 鍦帮紝鐙鍙戝竷
题目1，2题基本算法题
3，4题文本处理题.more info on 1point3acres.com
5，6题高级算法题（其实也没有太高级。。。）

我碰到的题
1, max difference in an array: 找i<j, a<a[j]情况下最大差a[j] - a, 否则返回－1。
	2, k subsequences : 找出所有和可被k整除的subsequence的个数，如：k = 3，［1，2，3，4，1］，返回4，分别为3，12，123，234。.1point3acres缃�
	3, 把所有java / c++ / c source code里的注释弄出来：只需要考虑行注释// 和 块注释/* */就可以
	4, 从html里将所有domain name 弄出来，形如abcd.abf.com。域名开头"www."或者"ww2."或者"web."将这些开头去掉， 如https ://abcd.abf.com/a/b取出abcd.abf.com，https://www.abf.com/a/b取出abf.com
5, strongly connect group, 给node个数n，edge数量m，求largest minimum number of nodes that must form a strongly connected group.这个largest minimum也没有太明白.Waral 鍗氬鏈夋洿澶氭枃绔�,
6, wedding planner, 题目和地里某篇帖子的内容一样，帖子一下子找不到，大概意思是一个整数数列［10，20，50，100，500］对应一个float数列［1.2，2.5，3.8，6.9，10.4］，给一个整数，如果正好存在在整数数列里，返回对应float，如给10，返回1.2；否则给30，找到20，50，对应2.5，3.8，算出差到2.5, 3.8中30对应多少，返回。


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=223895&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D40%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	 20收到，21号周六做的，今天收到onsite
		 三道一样的题目，感谢原来在post的小伙伴：
		 1. 让一个array降序排列的最少交换次数，array里面的树字是1～n
		 2 求一个树组，里面所有的树的奇数factor的sum
		 3. 类似 LC 零钱找取原题
		 . more info on 1point3acres.com
	 S1: 简单地在number array根据index找circle，找到了，就在总swap数量上加count
	 S2: 需要sqrt优化。 a是c的factor，那么b = c/a也是，然后查重，判断奇偶
	 S3: DP解


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=271825&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D40%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	 oa的名字写的是lifecircle challenge-qpan， 其实我也不记得投的什么什么具体职位了，然后看了一圈地理的面经，信心满满的去做了。。。一打开60min4题，每题读题就要快5分钟什么鬼。。。. 1point 3acres 璁哄潧
		 第一题，设计一个create bst， 给一个int[], 不断insert进bst，并且打印操作次数
		 第二题，给一个integer，按顺序输出binary bit为1的所有position
		 第三题，给一串string[], 先讲一大通ipv6和ipv4的区别和format，lz看了5分多钟。。 然后让判断每个string是ipv4 address还是ipv6的，或者neither，做完这题就剩5分钟了。。。
	 http://codezavvy.com/minimum-unique-array-sum/
 https://stackoverflow.com/questions/38384537/minimum-unique-array-sum
		 第四题，给一个int[], 找出所有之中dup的数++，直到所有的数都不一样了，求最小的sum值


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=223796&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D40%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	 第一题，给一个播放列表（a list of string），给一个当前播放的歌（index k），给一个要切去的歌名儿，可以往前一首也可以后退一首（而且是列表循环），问你要切过去需要几次操作。歌名儿有重复。其实不难，我就遍历一遍，算一下两种切歌（往前和往后）方法所需要的次数，取最小。test case都过了。

		 第二题，就是之前同学发的那道求奇数因子和。

		 第三题，给一个序列，给一个数挨亩，问你包含m个奇数的子串儿的个数。比如 2, 5, 4, 9，挨亩=1的话返回溜。弱弱的我没有想出最优解。。test case最后几个超时了。。

		 另外，我是内推那个Propel项目的。

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=223549&fromuid=108622
	第一题，给整数的数组，找每个整数的基数因子并求和，返回这个所有整数的技术因子和的和。注意大数据，后面几个test case不知道为什么过不了，废了好多时间。有优化想法的欢迎讨论。
	第二题，给整数数组，一次交换两个数的位置，求最少的置换次数使之成为降序排列。没做出来，欢迎讨论。
	第三题，动态规划，题面想不起来了，但用利特抠的三白儿时而的方法就能做出来，照葫芦画瓢即可。

	估计是跪了，尤其是第二题，想用利特抠的私事以题的方法做，时间太紧没做出来。

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=223639&fromuid=108622
	准备做前半小时看到新题面经，又重新准备了，否则我可能一题都不会吧

	题目一毛一样，三道题
	第一题，“奇数”，看上面面经的时候不懂什么基数，还查了basic divisor。。。。一看题居然是。。。嗯就是只算奇数的
	算N的因子的时候先把N开个方，可以大大缩短时间，后面的case也能过了。N开方后计为s，如果s是因子，N/s也是，注意一下s和N／s相等的情况，去重

	第二题，n个数，打乱顺序的，排成降序，基本思想就是跟排好序的比较，位置没变的不考虑，剩下的减去这些数构成环的个数就行
	比如2，3，4，5，1
	应该是5，4，3，2，1
	2，5一个环，3，4一个环，最后就是4-2=2

	再比如3，5，4，2，1
	3，5，4构成一个环，所以是3-1=2
	. from: 1point3acres.com/bbs 
	第三题dp不说了

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=290050&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D40%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	 新的vmware propel oa（new 1），可以参考的面经很少，75min 三道题，1. 遍历一个int array，对每一个数有两种操作，加入或删除，每操作一次返回当前min＊max， 用treemap test都能过. 鐣欏鐢宠璁哄潧-涓€浜╀笁鍒嗗湴
		 2. int 数组排序
		 3. consecutive sum.1point3acres缃�
		 第二题第三题都可以参考 这位同学的面经 http://www.1point3acres.com/bbs/ ... adio%26sortid%3D311

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=289788&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D40%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	 new 1
	 Recruiter直接联系拿的OA， 应该是新的，和之前的propel项目的都不一样，75分钟3道题。整体来看不算特别难1. 给一个int array，然后给另一个array是表示向左rotate这个array多少个position，然后输出每次进行这样操作后最大值所在的Index
		 2. int数组排序，只不过要先按照二进制1的个数排，比如7是111，8是1000，7的1比8的1多，所以7比8大。如果1的个数相同再比较十进制值的大小
		 3. 这个题特别tricky，求一个数有多少种consecutive sum，比如15=1+2+3+4+5=4+5+6=7+8，所以有三种。这个geeksforgeeks上有，但会超时。特别坑的数学问题，大家看看这个吧
		 https ://mathblag.wordpress.com/2011/11/13/sums-of-consecutive-integers/
	 https://math.stackexchange.com/questions/1100897/sum-of-consecutive-numbers
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=290390&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D40%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	1是比较array的很简单没啥难度
	2是数学题 算子集的和 很简单 主要考虑int的溢出就行
	3是dp 类似利特扣得卅②而 地里面经说错.


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=290299&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D40%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	 第一题大概是说collision，题目比较难懂，第二题很简单amazing number，第三题prefixTopostfix，感觉他家除了不靠谱，oa也不怎么有水平，拉黑吧2333

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=292218&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D40%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	 new 1
		 孪生字符串：两个字符串a和b，同字符串内，奇数位和奇数位的字符可以互相交换，偶数位和偶数位的字符也可以。问是否可以通过这种交换操作使两个字符串相等。-google 1point3acres
		 解法：只需分别统计奇数位和偶数位每个字母的出现次数，然后比较两个字符串的统计结果是否相等即可
		 最少步数：两个相同长度的整数数组，对应位置的两个整数位数也是相同的，通过改变每一位的数字，可以使两个整数相同。问一共需要改多少步，才可以使两个整数数组相同。一步相当于把一个数位加一或减一。
		 解法：直接逐位相减取绝对值，然后加起来就行了
		 社交网络：给一个数组，表示用户i所属的圈子的人数。推算出每个人属于哪个圈子，并输出每个圈子里面的用户id。如果两个圈子人数相同，id是从小到大分配的，也就是第一个圈子是最小的几个id，第二个圈子次之。输出结果每个圈子按照用户id排序，圈子和圈子按照圈子里最小用户id排序。
		 解法：可以直接扫描数组，每次取相同圈子大小的用户进一个圈子，选够了就从头开始选下一个圈子。这样做是O(n^2)。更好的解法是新建一个（用户id，圈子大小）的数据结构，按照圈子大小排序，
		 然后直接从头到尾扫一遍就能把所有的圈子生成，最后按照每个圈子第一个用户id排序。需要注意的是第一次排序的排序算法必须是stable的（python的list.sort, sorted）。这样做是O(nlogn)。我直接实现的第二个方法，能过所有case。第一个方法没试过，不太确定。

http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=292966&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D40%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	 OA三道题，前两道地理都有人发过面经了。第三道是比较少见的背包问题，大意是有n套丛书，每套书包含X本书，按套卖，每套价值Y元。
		 所以有两个等长input array分别代表每套书包含几本书和每套书卖多少钱。另一个input是int，代表你的预算。求最多能买多少本书
		 https ://www.kancloud.cn/kancloud/pack/70125


http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=293136&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D40%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
	lz在招聘会上投了vmware， 然后做了hr发的oa，不太清楚是不是propel那个项目，感觉hr发邮件比较仓促没说清，75min 3题。
	跟地里的面经完全不一样，题不是太简单，最后一题10多个test case有2个超时，是不是他家必须oa全过才能onsite啊？
	1.给一个long型的数n，返回第k大的因子
	这题不难，可以暴力做，但是要小心题里所有变量都是long. From 1point 3acres bbs

	2.给一个字符串，可以修改里面任意字符，使得字符串中不存在两个相邻且相等的字符。求最小修改次数

	3.给一个关系表，在中间找到一个三人组两两之间是好友。又定义一个概念叫“其他好友”，其中每个人至少是三人组中一人的好友（但不是三人
	组之一）。求一个最好的三人组，在这个三人组定义下，“其他好友”的数量最少。。
	光理解题意就很费时间，我的做法是先穷举所有可能的三人组，再求其他好友的数量，在bruce force的基础上加了剪枝策略什么的。10多个
	test case有2个超时，实在想不到更好的方法，光是代码量本身就有点大。。

http://www.1point3acres.com/bbs/thread-182050-2-1.html
1) vmware: 一个2d grid，可以向下用v，可以向右用h，从左上角开始走，到一个点有好几种hv的排列组合，返回他们按字母顺序的的排列，比如0，0 到2，2
0 hhvv
	1 hvhv
	2 hvvh
	3 vhhv
	4 vhvh
	5 vvhh
	比如给你（2，2）还有3那你就得返回vhhv


	https ://instant.1point3acres.com/thread/169706
https://www.hackerrank.com/challenges/detect-the-domain-name
2) 昨天收到的vmware oa邀请，在hackerrank上完成。60分钟6题。第1，2题75分，3，4题50分，5，6题100分。instruction上说了没指望全部做完，题目难度是1 - 6由易到难，所以建议顺序做。邀请上说做完会把分数和简历（？）发给vmware。.鍥磋鎴戜滑@1point 3 acres
	
题目1，2题基本算法题.more info on 1point3acres.com
		1. Lexicographic paths
			https://www.hackerrank.com/contests/w9/challenges/lexicographic-steps/submissions/code/7431514
		2. Consecutive Subsequences
			https://www.hackerrank.com/contests/w6/challenges/consecutive-subsequences/submissions/code/7439036
		3. Building a Smart IDE : Identifying comments
			https://www.hackerrank.com/challenges/ide-identifying-comments/submissions/code/30290513
		4. Detect the Domain Name
			https://www.hackerrank.com/challenges/detect-the-domain-name
	5，6题高级算法题（其实也没有太高级。。。）
	.From 1point 3acres bbs
	我碰到的题
	1, max difference in an array: 找i<j, a<a[j]情况下最大差a[j] - a, 否则返回＊1。
	2, k subsequences : 找出所有和可被k整除的subsequence的个数，如：k = 3，［1，2，3，4，1］，返回4，分别为3，12，123，234。
	//https ://github.com/ShrikantJadhav/HackerRank-Solutions/blob/master/IdentifyComments.cpp
	//https ://www.hackerrank.com/challenges/ide-identifying-comments
	3, 把所有java / c++ / c source code里的注释弄出来：只需要考虑行注释// 和 块注释/* */就可以. Waral 鍗氬鏈夋洿澶氭枃绔?,
	4, 从html里将所有domain name 弄出来，形如abcd.abf.com。域吊开头"www."或者"ww2."或者"web."将这些开头去掉， 如https ://abcd.abf.com/a/b取出abcd.abf.com，https://www.abf.com/a/b取出abf.com
	https://github.com/UtkarshPathrabe/Competetive-Coding/blob/master/HackerRank%20Solutions/Algorithms/Regex/Detect%20the%20Domain%20Name.java
	5, strongly connect group, 给node个数n，edge数量m，求largest minimum number of nodes that must form a strongly connected group.这个largest minimum也没有太明白
	https://www.hackerrank.com/challenges/clique
	https://github.com/fernandoBRS/HackerRank/blob/master/clique.cpp
	http://math.stackexchange.com/questions/1279241/minimum-size-of-largest-clique-in-a-graph
	6, wedding planner, 题目和地里某篇帖子的内容一样，帖子一下子找上到，大概意思是一个整数数列［10，20，50，100，500］对应一个float数列［1.2，2.5，3.8，6.9，10.4］，给一个整数，如果正好存在在整数数列里，
	返回对应float，如给10，返回1.2；否则给30，找到20，50，对应2.5，3.8，算出差到2.5, 3.8中30对应多少，返回。


	最后60分钟做了前三题，第四题没有通过所有case。第四题用正则表达式才能解，输入文件是真正的html，相当夊杂。

	3) http://www.meetqun.com/forum.php?mod=forumdisplay&fid=36&filter=typeid&typeid=97


http://www.1point3acres.com/bbs/thread-143881-1-1.html
1. 寫一個內插外插的function
他給你兩個array, 像是10, 20, 50, 100; 還有 5.33, 6.85, 8.9, 10 (float type)
還有一個數n
1) 如果第一個array中恰巧有跟n一樣的值, 直接返回這個值就好
2) 如果給的n介於第一個array的某個區間之內, 比方說30, 那要用20 & 50對應的值內插算出30對應到什麼值(return float type to decimal precision 2)
3) 如果都n都大於(或小於)給的第一個array中的數, 找出最接近的兩個數作外插(ex.n = 110, 用 50 & 100對應的值作外插)
4) 如果第二個array裡面的值有0或是負數, 那那個數不能用做計算
5) 如果只有一個數可以用來做內插或外插的計算, 那無論n是什麼都直接返回這個唯一的值(ex.第二個array: 0 0 0 0 25)-> return 25
- google 1point3acres
2) 給三個數x, y, k
在所有從(0, 0)走到(x, y)的走法當中, 找到 lexicographically kth smallest one, 輸出走法順序的字串, H代表horizontal, V代表Vertical
比方說input : 2 2 3.1point3acres缃�
	表示從0, 0 - 2, 2 總共要走2次H和2次V
	0th : HHVV
	1st : HVHV
	2nd : HVVH
	3rd : VHHV <-output this one
	4th : VHVH
	5th : VVHH

	注意index是從0 - 5而不是1 - 6, 最後可能會差1

	3.
	input有3個 : 1個數D(distance), 1個array描述不同齒輪的直徑(R), 1個array描述使用不同齒輪的cost(C)
	output是一個array

	對於每一個齒輪i, 要找到滿足(1)Ri + Rj >= D(2) cost盡可能小的解
	ex :
	input
	5 (array size) 8(D)
	R : 1 3 6 2 5
	C : 5 6 8 3 4

	output
	0 5 4 3 5

	explain :
	因為第一個齒輪找不到任何其他的齒輪可以符合第一個條件, 所以要output 0
	能讓第二個齒輪符合第一個條件的有第3和第5個齒輪, 但是第5個齒輪cost較低, 所以output 5. visit 1point3acres.com for more.
	齒輪可以重複用(包括自己), 所以第五個齒輪output 5. from : 1point3acres.com / bbs
	**注意暴力法最後面的test case不會過

	4.
	input : 給N個點, 還有M個邊(以兩端點的index表示) - google 1point3acres
	要做的事情 :
找出有幾個part, 然後他有一個算cost的方法, 把part的個數mapping到最後的cost

ex :
input.
4 (number of point)
2 (number of edge) 
1 2
1 4

output :
	3

	explain :
	1, 2, 4是連在一起的part
	總共有兩個part(1, 2, 4) & (3). 1point3acres.com / bbs
	mapping的方式是把每個part的個數取方根(然後取ceiling), 然後全部加起來
	所以ceiling(sqrt(3)) + ceiling(sqrt(1)) = 3
/****************************VM end*********************************************/



/****************************TAB begin*********************************************/
http://www.1point3acres.com/bbs/thread-143610-1-1.html


polynomial exponent factorial
/****************************TAB end*********************************************/
#endif 

namespace Sys {
	/**
	* Find and return the index of pivot element.
	* @param a - The array.
	* @param first - The start of the sequence.
	* @param last - The end of the sequence.
	* @return - the pivot element
	*/
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

	/**
	* Quicksort.
	* @param a - The array to be sorted.
	* @param first - The start of the sequence to be sorted.
	* @param last - The end of the sequence to be sorted.
	*/
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

	/*blackjack design begin*/
	class Card {
	public:
		enum FACE{
			CLUB,
			DIMOND,
			HEART,
			SPADE
		};

		Card() : m_face(CLUB), m_val(0), available(false){};
		Card(FACE face, int val) :m_face(face), m_val(val), available(true){}

		void makeAvailable() { available = true; }
		void makeUnavailable() { available = false; }
		bool isAvailable() { return available; }

		int getValue() {
			return m_val;
		}

		FACE getFace() { return m_face; }

	private:
		FACE m_face;
		int m_val;
		bool available;
	};


	class Hand {
	public:
		int score() {
			int result = 0;

			for (auto item : m_cards)
				result += item.getValue();

			return result;
		}

		void addCard(Card newcard) {
			m_cards.push_back(newcard);
		}

	private:
		vector<Card> m_cards;
	};

	class Deck{
	public:
		void setDeckofCard(vector<Card>& cards) {
			m_count = 0;
			for (auto item : cards)
				m_cards.push_back(item);
		}

		void shuffle() {
			int len = m_cards.size();
			for (int i = 0; i < len; ++i) {
				int j = rand() % (len - i) + i;
				swap(m_cards[j], m_cards[i]);
			}
		}

		int remainCards()  {
			return m_cards.size() - m_count;
		}

		Card dealCard() {
			Card result;
			if (!m_cards.empty()) {
				++m_count;
				result = m_cards.back();
				m_cards.pop_back();
			}

			return result;
		}

	private:
		vector<Card> m_cards;
		int m_count;
	};
	/*blackjack design end*/

	/*parking lot design begin*/
	enum SpotType
	{
		T_MOTO,
		T_COMPACT,
		T_SUV
	};

	class Spot
	{
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
	/*parking lot design end*/


	class Semaphore {
	public:
		Semaphore(int max) :count(max) {
		}

		void Get() {
			unique_lock<std::mutex> lock{ mute };
			cout << "current thread begin=" << this_thread::get_id() << "," << count << endl;
			if (--count < 0) {
				cout << "current waiting=" << this_thread::get_id() << endl;
				cond.wait(lock);
			}
			cout << "current thread end=" << this_thread::get_id() << endl;
		}

		void Release() {
			//lock_guard<std::mutex> lock{ mute };
			unique_lock<std::mutex> lock{ mute };
			if (++count <= 0) // have some thread suspended ?
				cond.notify_one(); // notify one !
		}

	private:	
		volatile int count;
		int maxcount;
		mutex mute;
		condition_variable cond;
	};

	Semaphore smtest(3);

	void a()
	{
		smtest.Get();
		for (int i = 0; i < 10; ++i) {
			std::cout << "thread a:" << this_thread::get_id() << "," << i << '\n';
			//_sleep(1);
		}
		smtest.Release();
	}

	void b()
	{
		smtest.Get();
		for (int i = 0; i < 10; ++i) {
			std::cout << "thread b:" << this_thread::get_id() << "," << '\n';
			//_sleep(1);
		}
		smtest.Release();
	}

	void c()
	{
		smtest.Get();
		for (int i = 0; i < 10; ++i) {
			std::cout << "thread c:" << this_thread::get_id() << "," << i << '\n';
			//_sleep(1);
		}
		smtest.Release();
	}

	void d()
	{
		smtest.Get();
		for (int i = 0; i < 10; ++i) {
			std::cout << "thread d:" << this_thread::get_id() << "," << i << '\n';
			//_sleep(1);
		}
		smtest.Release();
	}


	static void main() {
		vector<int> nums1 = { 5, 4, 3, 2, 1 };
		quickSort(nums1, 0, nums1.size() - 1);

		vector<int> nums2 = { 3, 4, 3, 5, 2 };
		quickSort(nums2, 0, nums2.size() - 1);

		//vector<int> nums2 = { 3, 4, 3, 5, 2 };
		//quickSort(nums2, 0, nums2.size() - 1);


		thread th1{ a }, th2{ b }, th3{ c }, th4{ d };
		int result;

		th1.join();
		th2.join();
		th3.join();
		th4.join();

		result = 0;
	}
}

namespace FB {
}

namespace NV {
	struct TreeNode {
		TreeNode(int value) : val(value), left(nullptr), right(nullptr){}

		int val;
		TreeNode* left;
		TreeNode* right;
	};
	
	struct ListNode {
		char val;
		ListNode* next;
	};

	int calcPrime(int inp) {
		vector<int> arr;
		arr.push_back(2);
		arr.push_back(3);

		int counter = 4;
		while (arr.size() < inp) {
			if (counter % 2 != 0 && counter % 3 != 0) {
				int temp = 4;
				while (temp*temp <= counter) {
					if (counter % temp == 0)
						break;
					temp++;
				}
				if (temp*temp > counter) {
					arr.push_back(counter);
				}
			}
			counter++;
		}

		return *arr.rbegin();
	}

	vector<char> findDup(list<char>& list1, list<char>& list2) {
		vector<char> res;
		if (list1.empty() || list2.empty())
			return res;

		list1.sort();
		list2.sort();
		//sort(list1.begin(), list2.end());
		//sort(list2.begin(), list2.end());

		auto ite1 = list1.begin();
		auto ite2 = list2.begin();

		while (ite1 != list1.end() && ite2 != list2.end()) {
			if (*ite1 == *ite2) {
				if (res.empty() || *res.rbegin() != *ite1)
					res.push_back(*ite1);

				++ite1;
				++ite2;
			}
			else if (*ite1 < *ite2)
				++ite1;
			else
				++ite2;
		}

		return res;
	}

	class mirrorTree {
	public:
		TreeNode* createMirror(TreeNode* root) {
			if (nullptr == root)
				return nullptr;

			TreeNode* node = new TreeNode(root->val);
			node->left = createMirror(root->right);
			node->right = createMirror(root->left);
			return node;
		}

		static void main() {
			unique_ptr<mirrorTree> test(new mirrorTree);
			TreeNode node1(1);
			TreeNode node2(2);
			TreeNode node3(3);
			TreeNode node4(4);
			TreeNode node5(5);
			TreeNode node6(6);
			TreeNode node7(7);
			TreeNode* result = nullptr;

			node1.left = &node2;
			node1.right = &node3;

			node2.left = &node4;
			node2.right = &node5;

			node3.left = &node6;
			node3.right = &node7;

			result = test->createMirror(&node1);
		}
	};

	class calBits {
	public:
		static int countBits(int val) {
			int count = 0;
			for (int i = 0; i < 32; ++i) {
				if (1 << i & val)
					++count;
			}

			return count;
		}

		static int countBits2(int val) {
			//or can define 256 arrary for 0xFF
			vector<int> data = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };
			int count = 0;

			count += data[val & 0xF];
			count += data[val >> 4 & 0xF];
			count += data[val >> 8 & 0xF];
			count += data[val >> 12 & 0xF];
			count += data[val >> 16 & 0xF];
			count += data[val >> 20 & 0xF];
			count += data[val >> 24 & 0xF];
			count += data[val >> 28 & 0xF];

			return count;
		}

		static void main() {
			int test1 = 0xFFFFFFFF;
			int test2 = 0xF0FFF0FF;
			int test3 = 0x00FFF0FF;
			int result = 0;

			result = countBits2(test1);
			result = countBits2(test2);
			result = countBits2(test3);
		}
	};

	//for chain rule
	//e.g. int length = strlen( strcpy( strDest, "hello world") );
	char *strcpy(char *strDest, const char *strSrc) {
		//assert((strDest != NULL) && (strSrc != NULL));
		if (nullptr == strDest || nullptr == strSrc)
			return nullptr;

		char *address = strDest;
		while ((*strDest++ = *strSrc++) != '\0') ;
		return address;
	}

	static void main() {
		vector<char> res;
		list<char> list11 = { 'c', 'b', 'a' };//{'e', 'e', 'a', 'c'};
		list<char> list21 = { 'c', 'b', 'a' };//{ 'f', 'm', 'e' };
		res = findDup(list11, list21);
		mirrorTree::main();
		calBits::main();
		unsigned int a = 6;
		int b = -20;
		if (b + a > 6)
			b++;
		else
			--b;
	}
}

namespace TW {
	struct Node {
		string val;
		Node* left;
		Node* right;
	};

	struct TreeNode {
		TreeNode(int newval) : val(newval), left(nullptr), right(nullptr), sibling(nullptr) {}
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode* sibling;
	};

	class IceCave {
	public:
		bool canPass(vector<vector<char>>& grid, int i, int j) {
			if (i == desi && j == desj)
				return true;

			if (i < 0 || i > row || j < 0 || j > col || 'X' == grid[i][j])
				return false;

			return true;
		}

		bool canSurvive(vector<vector<char>>& grid, int starti, int startj, int desi, int desj) {
			if (grid.empty() || grid[0].empty())
				return false;

			row = grid.size();
			col = grid[0].size();
			
			vector<pair<int, int>> direct = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
			queue<pair<int, int>> data;
			data.push({ starti, startj });

			while (!data.empty()) {
				int count = data.size();

				while (count-- > 0) {
					pair<int, int> cur = data.front();
					data.pop();

					grid[cur.first][cur.second] = 'X';
					for (auto item : direct) {
						pair<int, int> next;
						next.first = cur.first + item.first;
						next.second = cur.second + item.second;

						if (canPass(grid, next.first, next.second)) {
							if (next.first == desi && next.second == desj && 'X' == grid[next.first][next.second])
								return true;

							data.push(next);
						}
					}
				}
			}
			
			return false;
		}

	private:
		int desi;
		int desj;
		int row;
		int col;
	};

	void getSibling(TreeNode* root) {
		if (nullptr == root)
			return;

		queue<TreeNode*> level;
		level.push(root);

		while (!level.empty()) {
			int count = level.size();
			TreeNode* pre = level.front();

			for (int i = 0; i < count; ++i) {
				TreeNode* curnode = level.front();
				level.pop();
				if (i > 0) {
					pre->sibling = curnode;
					pre = curnode;
				}

				if (curnode->left)
					level.push(curnode->left);

				if (curnode->right)
					level.push(curnode->right);
			}
		}
	}

	bool findword(Node* root, string word) {
		if (nullptr == root)
			return false;

		queue<Node*> data;
		data.push(root);

		while (!data.empty()) {
			int count = data.size();

			while (count-- > 0) {
				Node* node = data.front();
				data.pop();
				
				if (node->val == word)
					return true;

				if (node->left)
					data.push(node->left);

				if (node->right)
					data.push(node->right);
			}
		}

		return false;
	}

	struct Node1 {
		string val;
		vector<Node1*> adjs;
	};

	bool findword2(list<Node1*>& nodes, string word) {
		unordered_set<Node1*> visited;

		for (auto node : nodes) {
			queue<Node1*> data;
			if (0 == visited.count(node))
				data.push(node);

			while (!data.empty()) {
				int count = data.size();

				while (count-- > 0) {
					Node1* curnode = data.front();
					data.pop();

					if (visited.count(curnode))
						continue;

					visited.insert(curnode);
					if (word == curnode->val)
						return true;

					for (auto adj : curnode->adjs) {
						if (0 == visited.count(adj))
							data.push(adj);
					}
				}
			}
		}

		return false;
	}

	list<string> split(string& str, string& deli) {
		list<string> result;
		size_t start = 0;

		size_t found = str.find(deli);
		while (found != string::npos) {
			if (found > start)
				result.push_back(str.substr(start, found - start));
			start = found + deli.size();
			found = str.find(deli, found + 1);
		}

		if (start > 0 && start < str.size())
			result.push_back(str.substr(start));

		return result;
	}

	list<string> multisplit(string& str, list<string>& delis) {
		list<string> result;
		list<string> tosplit;

		tosplit.push_back(str);
		for (auto deli : delis) {
			list<string> output;
			bool bsplit = false;

			for (auto item1 : tosplit) {
				list<string> tmp = split(item1, deli);
				if (tmp.empty())
					output.push_back(item1);
				else {
					bsplit = true;
					output.insert(output.end(), tmp.begin(), tmp.end());
				}
			}

			//find split with current deli
			if (bsplit) {
				tosplit.clear();
				result.clear();

				tosplit.insert(tosplit.end(), output.begin(), output.end());
				result.insert(result.end(), output.begin(), output.end());
			}
		}

		return result;
	}

	static void main() {
		TreeNode tnode1(1);
		TreeNode tnode2(2);
		TreeNode tnode3(3);
		TreeNode tnode4(4);
		TreeNode tnode5(5);

		tnode1.left = &tnode2;
		tnode1.right = &tnode3;
		tnode2.left = &tnode4;
		tnode3.left = &tnode5;

		getSibling(&tnode1);
		list<string> result2;
		string str2("abcdefg");
		//list<string> delis1 = { "c", "ef" };
		list<string> delis1 = { "c", "af", "ef" };
		//abcdefg", ["c", "ef"]
		result2 = multisplit(str2, delis1);
		Node1 node1;
		node1.val = "a1";

		Node1 node2;
		node2.val = "a2";

		Node1 node3;
		node3.val = "a3";

		Node1 node4;
		node4.val = "a4";

		node1.adjs = { &node2,  &node3 };
		node2.adjs = { &node1,  &node3 };
		node3.adjs = { &node1,  &node2, &node4};
		node4.adjs = { &node3 };

		list<Node1*> nodes = { &node1 , &node2, &node3, &node4 };
		bool result;

		result = findword2(nodes, "a4");
	}
}

namespace AM {
	vector<string> maxAssociation(vector<pair<string, string>> associations){
		unordered_map<string, string> data;
		unordered_set<string> degrees;
		map<string, vector<string>> ret;

		for (auto it : associations) {
			data[it.first] = it.second;
			degrees.insert(it.second);
		}

		queue<string> nodes;
		for (auto it : associations) {
			if (0 == degrees.count(it.first))
				nodes.push(it.first);
		}
	
		int maxsize = 0;
		while (!nodes.empty()) {
			string cur = nodes.front();
			nodes.pop();

			vector<string> tmp;
			unordered_set<string> visit;

			tmp.push_back(cur);
			visit.insert(cur);
			
			while (data.count(cur) && !visit.count(data[cur])) {
				cur = data[cur];
				tmp.push_back(cur);
			}

			maxsize = max(maxsize, (int)tmp.size());
			ret[*tmp.begin()] = tmp;
		}

		for (auto it : ret) {
			if (it.second.size() == maxsize)
				return it.second;
		}
	}
	/*vector<string> maxAssociation(vector<pair<string, string>> associations){
		vector<vector<string>> ret;
		int maxsize = 0;
		map<string, int> visit;

		for (auto it : associations) {
			if (visit.count(it.first)) {
				ret[visit[it.first]].insert(it.second);
				visit[it.second] = visit[it.first];
			}
			else if (visit.count(it.second)) {
				ret[visit[it.second]].insert(it.first);
				visit[it.first] = visit[it.second];
			}
			else {
				unordered_set<string> tmp;
				tmp.insert(it.first);
				visit[it.first] = ret.size();

				if (it.first != it.second) {
					tmp.insert(it.second);
					visit[it.second] = ret.size();
				}
				
				ret.push_back(tmp);
				maxsize = max(maxsize, (int)ret.rbegin()->size());
			}

		}
	}*/

	struct Node
	{
		Node(int value) : val(value), left(nullptr), right(nullptr)
		{}
		int val;
		Node* left;
		Node* right;
	};
	
	int findSecondLargestValueInBST(Node* root)
	{
		int secondMax;
		Node* pre = root;
		Node* cur = root;

		while (nullptr != cur->right) {
			pre = cur;
			cur = cur->right;
		}

		if (nullptr != cur->left){
			cur = cur->left;
			while (cur->right != nullptr)
				cur = cur->right;

			secondMax = cur->val;
		}
		else {
			if (cur == root && pre == root)
				secondMax = INT_MIN;	//Only one node in BST
			else
				secondMax = pre->val;
		}

		return secondMax;
	}


	//http://www.geeksforgeeks.org/recursively-remove-adjacent-duplicates-given-string/
	class RemoveDup {
	public:
		string remove(string str, char& last_rm) {
			int len = str.size();
			if (len < 2)
				return str;
			
			//make sure the first left is not duplicate
			if (str[0] == str[1]) {
				last_rm = str[0];
				int idx = 1;
				while (idx < len && str[0] == str[idx])
					++idx;

				return remove(str.substr(idx), last_rm);
			}

			//get the result from the second element
			string tmpstr = remove(str.substr(1), last_rm);

			//if first element of temporary is same as original
			//then return temporary without the first element
			if (!tmpstr.empty() && tmpstr[0] == str[0]) {
				last_rm = str[0];
				return tmpstr.substr(1);
			}

			//last remove element is same as the first element
			//in original, then return empty string
			if (tmpstr.empty() && last_rm == str[0])
				return tmpstr;

			//last remove element isn't same as the first element
			//then return the first element with the temporary result
			return str.substr(0, 1)+tmpstr;
		}

		static void main() {
			auto_ptr<RemoveDup> test(new RemoveDup);
			char last_rm = '\0';
			string str1("aaaaaaaaaaa");
			string str2("aaaaaaaaaaab");

			string str3("abbcc");
			string str4("abbaa");
			string str5("abccba");
			string str6("abccbd");

			string result;

			result = test->remove(str1, last_rm);
			result = test->remove(str2, last_rm);
			result = test->remove(str3, last_rm);
			result = test->remove(str4, last_rm);
			result = test->remove(str5, last_rm);
			result = test->remove(str6, last_rm);
		}
	};

	class PlaySong {
	public:
		unordered_map <string, unordered_map<string, int>> data;
		void play(string band_name, string song_name) {
			data[band_name][song_name] ++;
		}

		string topSong(string band_name) {
			string result;
			int count = -1;

			for (auto song : data[band_name]) {
				if (song.second > count) {
					count = song.second;
					result = song.first;
				}
			}

			return result;
		}
	};

	vector<int> calLarge(Node* root, int& maxval) {
		vector<int> result(2, 0);
		vector<int> left(2, 0);
		vector<int> right(2, 0);

		if (NULL == root)
			return result;

		left = calLarge(root->left, maxval);
		right = calLarge(root->right, maxval);

		result[0] = left[0] + right[0] + 1;
		result[1] = left[1] + right[1] + root->val;

		maxval = max(maxval, result[1] / result[0]);
		return result;
	}

	void dotdfs(int dots, int insert, string curr, vector<string>& res) {
		if (dots == 3) {
			res.push_back(curr);
			return;
		}

		for (int i = insert; i < curr.length(); i++)
			dotdfs(dots + 1, i + 2, curr.substr(0, i) + "." + curr.substr(i), res);
	}

	vector<string> insertDots() {
		vector<string> res;
		dotdfs(0, 1, "12345", res);
		return res;
	}

	void shuffle(vector<int> data) {
		int len = data.size();
		for (int i = 0; i < len; ++i) {
			int j = rand() % (len - i) + i;
			swap(data[j], data[i]);
		}
	}

	void mergearray(vector<int>&a, vector<int> &b)
	{
		int i = 0, j = 0;

		while (i < a.size())
		{
			if (a[i] <= b[j])
				++i;
			else
			{
				int cur = a[i];
				int k = j;
				//a[i] = b[j++];

				while (k < b.size() && b[k] <= cur && i < a.size())
				{
					swap(a[i], b[k]);
					++i;
					++k;
				}

				if (k == j)
				{
					++i;
					++j;
				}
			}
		}
	}

	void mergearray1(vector<int>&a, vector<int> &b)
	{
		int m = a.size() - 1;

		for (int i = b.size() - 1; i >= 0; --i)
		{
			int j, last = a[m];

			for (j = m - 1; j >= 0 && a[j] > b[i]; --j)
				a[j + 1] = a[j];

			if (j != m - 1 || last > b[i])
			{
				a[j + 1] = b[i];
				b[i] = last;
			}
		}
	}

	static void main() {
		{
			//vector<string> maxAssociation(vector<pair<string, string>> associations)
			vector<string> ret;
			vector<pair<string, string>> associations1 = { { "item1", "item2" } };
			//vector<pair<string, string>> associations2 = { { "item1", "item1" } };
			vector<pair<string, string>> associations3 = { { "item3", "item4" }, { "item1", "item2" } };
			vector<pair<string, string>> associations4 = { { "item2", "item3" }, { "item1", "item2" } };
			vector<pair<string, string>> associations5 = { { "item5", "item6" }, { "item4", "item5" }, { "item2", "item3" }, { "item1", "item2" } };

			ret = maxAssociation(associations1);
			//ret = maxAssociation(associations2);
			ret = maxAssociation(associations3);
			ret = maxAssociation(associations4);
			ret = maxAssociation(associations5);
		}
		{
			vector<int> a = { 1, 5, 6, 10 };
			vector<int> b = { 2, 3, 9 };

			mergearray1(a, b);

			int i = 0;
		}

		{
			vector<int> result;
			int maxval = INT_MIN;
			Node n1(-1);
			Node n2(5);
			Node n3(3);

			n1.left = &n2;
			n1.right = &n3;
			result = calLarge(&n1, maxval);

			Node n4(3);
			n2.right = &n4;
			maxval = INT_MIN;
			result = calLarge(&n1, maxval);

			Node n5(-1);
			n2.left = &n5;
			maxval = INT_MIN;
			result = calLarge(&n1, maxval);
		}

		RemoveDup::main();
	}
}

namespace VM {
//http://www.geeksforgeeks.org/maximum-difference-between-two-elements/
	int maxDiff(vector<int> data) {
		int res = -1;
		int len = data.size();
		if (len < 2)
			return res;
		
		int maxright = data[len - 1];

		for (int i = len - 2; i >= 0; --i) {
			if (data[i] > maxright)
				maxright = data[i];
			else   //if overflow, use long
				res = max(res, maxright - data[i]);
		}
		
		return res;
	}

//https://stackoverflow.com/questions/24518682/count-subarrays-divisible-by-k
	long k_diff(vector<int> data, int k) {
		vector<int> mod_k(k, 0);
		mod_k[0] = 1;
		long res = 0;
		long presum = 0;
		for each (auto num in data){
			presum += num;
			presum %= k;
			mod_k[presum] ++;
		}

		for each (auto num in mod_k)
			res += num * (num - 1) / 2;
		
		return res;
	}

//https://www.hackerrank.com/challenges/detect-the-domain-name/copy-from/30405397
	//convert e.g. %3A  -> :
	string urlDecode(const string &SRC) {
		string ret;
		char ch;
		int i, ii;
		for (i = 0; i<SRC.length(); i++) {
			if (int(SRC[i]) == 37) {
				sscanf(SRC.substr(i + 1, 2).c_str(), "%x", &ii);
				ch = static_cast<char>(ii);
				ret += ch;
				i = i + 2;
			}
			else {
				ret += SRC[i];
			}
		}

		return ret;
	}

	int detect_domain() {
		/* Enter your code here. Read input from STDIN. Print output to STDOUT */
		//regex format("(http|https)\\://(www.|ww2.|)([a-zA-Z0-9\\-\\.]+)(\\.[a-zA-Z]+)(/\\S*)?");
		regex format("(http|https)\\://(www.|ww2.|)([a-zA-Z0-9\\-\\.]+)(\\.[a-zA-Z]+)(/\\S*)?");
		std::smatch match;
		vector<string>links;
		int N;
		string src;
		cin >> N;

		while (N--) {
			cin.ignore();
			src.clear();
			getline(cin, src);
			string source = urlDecode(src);

			auto searchStart(source.cbegin());
			while (regex_search(searchStart, source.cend(), match, format))
			{
				string item = match[3].str() + match[4].str();
				if (item.substr(0, 4) == "www.")
					item = item.substr(4);

				if (links.end() == find(links.begin(), links.end(), item)) {
					links.push_back(item);

				}
				searchStart += match.position() + match.length();
			}
		}

		sort(links.begin(), links.end());
		for (int j = 0; j < links.size(); ++j){
			if (j == links.size() - 1)
				cout << links[j];
			else
				cout << links[j] + ";";
		}
		return 0;
	}

//http://blog.csdn.net/codetz/article/details/51152407
	//序列升序排列
	int getMinSwaps(vector<int> &nums) {
		vector<int> nums1(nums);
		sort(nums1.begin(), nums1.end());
		unordered_map<int, int> m;
		int len = nums.size();
		for (int i = 0; i < len; i++) {
			m[nums1[i]] = i;//建立每个元素与其应放位置的映射关系
		}

		int loops = 0;//循环节个数
		vector<bool> flag(len, false);
		//找出循环节的个数
		for (int i = 0; i < len; i++) {
			if (!flag[i]) {//已经访问过的位置不再访问
				int j = i;
				while (!flag[j]) {
					flag[j] = true;
					j = m[nums[j]];//原序列中j位置的元素在有序序列中的位置
				}
				loops++;
			}
		}
		return len - loops;
	}

	//序列降序排列
	int getMinSwaps2(vector<int> &nums) {
		vector<int> nums1(nums);
		sort(nums1.begin(), nums1.end(), greater<int>());
		unordered_map<int, int> m;
		int len = nums.size();
		for (int i = 0; i < len; i++) {
			m[nums1[i]] = i;//建立每个元素与其应放位置的映射关系
		}

		int loops = 0;//循环节个数
		vector<bool> flag(len, false);
		//找出循环节的个数
		for (int i = 0; i < len; i++) {
			if (!flag[i]) {//已经访问过的位置不再访问
				int j = i;
				while (!flag[j]) {
					flag[j] = true;
					j = m[nums[j]];//原序列中j位置的元素在有序序列中的位置
				}
				loops++;
			}
		}
		return len - loops;
	}

//https://leetcode.com/problems/coin-change/discuss/
	int coinChange(vector<int>& coins, int amount) {
		int Max = amount + 1;
		vector<int> dp(amount + 1, Max);
		dp[0] = 0;
		for (int i = 1; i <= amount; i++) {
			for (int j = 0; j < coins.size(); j++) {
				if (coins[j] <= i) {
					dp[i] = min(dp[i], dp[i - coins[j]] + 1);
				}
			}
		}
		return dp[amount] > amount ? -1 : dp[amount];
	}

//http://www.algolist.net/Data_structures/Binary_search_tree/Insertion
	class BSTNode {
	public:
		BSTNode(int value) :left(NULL),right(NULL), val(value) {}
		BSTNode* left;
		BSTNode* right;
		int val;

		bool add(int value);
	};

	BSTNode* root = NULL;
	bool bstadd(int value) {
		if (root == NULL) {
			root = new BSTNode(value);
			return true;
		}
		else
			return root->add(value);
	}

	bool BSTNode::add(int value) {
		if (value == this->val)
			return false;
		else if (value < this->val) {
			if (left == NULL) {
				left = new BSTNode(value);
				return true;
			}
			else
				return left->add(value);
		}
		else if (value > this->val) {
			if (right == NULL) {
				right = new BSTNode(value);
				return true;
			}
			else
				return right->add(value);
		}
		return false;
	}

	void get_bit1(int val) {
		int cur = 1;
		for (int i = 0; i < sizeof(int) * 8; ++i) {
			cur = (1 << i);
			if ((val & cur) == cur)
				cout << i << endl;
		}

		cout << "get_bit1 done" << endl;
	}

//http://blog.csdn.net/mind_v/article/details/72157624
	void str_split(const string &str, const string &sign, vector<string> &results)
	{
		string::size_type pos;
		size_t size = str.size();
		for (size_t i = 0; i < size; ++i)
		{
			pos = str.find(sign, i); //从第i个位置查找sign分割符第一次出现的位置，没有找到则返回npos；
			if (pos == str.npos)
			{//将剩余部分存入
				string s = str.substr(i, size);
				results.push_back(s);
				break;
			}
			if (pos < size)
			{
				string s = str.substr(i, pos - i);//把从i开始，长度为pos-i的元素拷贝给s;  
				results.push_back(s);
				i = pos;
			}
		}
	}

	vector<string> checkIP(vector<string> ip_array)
	{
		size_t n = ip_array.size();
		vector<string> results_vec;  //保存结果

									 //vector为空
		if (n == 0)
		{
			results_vec.push_back("Empty");
			return results_vec;
		}

		//存入元素个数
		results_vec.push_back(to_string(n));

		vector<string>::iterator it = ip_array.begin();
		for (; it != ip_array.end(); ++it)
		{
			vector<string> results_4, results_6;
			str_split(*it, ".", results_4);  //results_4存储ipv4的每段
			str_split(*it, ":", results_6);  //results_6存储ipv6的每段

											 //地址段数不合法
			if (results_4.size() != 4 && results_6.size() != 8)
			{
				results_vec.push_back("Neither");
				continue;
			}

			//段数合法(4段)，可能是IPv4，接下来判断每一段的合法性
			if (results_4.size() == 4)
			{
				vector<string>::iterator it_4 = results_4.begin();

				for (; it_4 != results_4.end(); ++it_4)
				{
					int a = atoi((*it_4).c_str());
					if (a < 0 || a > 255)
						break;
				}
				if (it_4 == results_4.end())
					results_vec.push_back("IPv4");
				else
					results_vec.push_back("Neither");
			}

			//段数合法(8段)，可能是IPv6，接下来判断每一段的合法性
			if (results_6.size() == 8)
			{
				vector<string>::iterator it_6 = results_6.begin();

				for (; it_6 != results_6.end(); ++it_6)
				{
					size_t it6_size = (*it_6).size();
					if (it6_size <= 0 || it6_size > 4)  //IPv6的每段的十六进制数的位数不合法
						break;

					size_t j = 0;
					while (j < it6_size)
					{//十六进制表示的合法性检测
						char s = (*it_6)[j];
						if ((s >= '0' && s <= '9') ||
							(s >= 'a' && s <= 'f') ||
							(s >= 'A' && s <= 'F'))
							++j;
						else
							break;
					}
					if (j != it6_size)  //存在某一位的十六进制表示不合法
						break;
				}
				if (it_6 == results_6.end())  //所有位的十六进制表示均合法
					results_vec.push_back("IPv6");
				else
					results_vec.push_back("Neither");
			}
		}

		return results_vec;
	}

	//http://codezavvy.com/minimum-unique-array-sum/
	//https://stackoverflow.com/questions/38384537/minimum-unique-array-sum
	int getMinimumUniqueSum(vector<int> arr) {
		sort(arr.begin(), arr.end());
		int count = 0;
		int len = arr.size();
		for (int i = 0; i < len; i++){
			for (int j = i + 1; j < len; j++){
				if (arr[i] == arr[j]){
					arr[j] = arr[j] + 1;
				}
			}
		}

		for (int x : arr)
			count += x;
		return count;
	}

	int minUniqueSum(vector<int> arr) {
		int len = arr.size();

		int sum = arr[0];
		int prev = arr[0];

		for (int i = 1; i < len; i++) {
			int curr = arr[i];

			if (prev >= curr) {
				curr = prev + 1;
			}
			sum += curr;
			prev = curr;
		}

		return sum;
	}

//https://discuss.codechef.com/questions/103416/contiguous-subarray
	int countOddSub(vector<int> nums) {
		if (nums.empty())
			return 0;

		int k = 1, res = 0, sum = 0;
		int len = nums.size();
		//vector<int> save(INT_MAX, 0);
		unordered_map<int,int> save;
		vector<int> odd(len, 0);
		save[0] = 1;
		for (int i = 0; i < len; i++)
		{
			if (nums[i] % 2 == 0)
				odd[i] = 0;
			else
				odd[i] = 1;
			sum += odd[i];

			if (sum >= k)
				res += save[sum - k];
			save[sum]++;
		}
		cout << res << endl;
	}


	int countOddSub2(vector<int> nums)
	{
		int sum = 0;
		int n, k, ans = 0;
		k = 1;
		n = nums.size();
		//cin >> n >> k;
		//int save[1000010];
		int save[1000];
		vector<int> odd(n);
		memset(save, 0, sizeof(save));
		save[0]++;
		for (int i = 0; i<n; i++)
		{
			//cin >> a[i];
			if (nums[i] % 2 == 0)
				odd[i] = 0;
			else
				odd[i] = 1;
			sum += odd[i];
			if (sum >= k)
				ans += save[sum - k];
			save[sum]++;
		}
		cout << ans << endl;

		return 0;
	}

	class TestBase {
	};

	class TestDerive: public TestBase {
	};

	class Father {
	public:
		void DoSomething1(TestBase val){
			cout << "Father::DoSomething1(TestBase val)" << endl;
		}

		void DoSomething2(TestDerive val) {
			cout << "Father::DoSomething2(TestBase val)" << endl;
		}
	};

	class Son: public Father {
	public:
		void DoSomething1(TestBase val) {
			cout << "Son::DoSomething1(TestBase val)" << endl;
		}

		void DoSomething2(TestDerive val) {
			cout << "Son::DoSomething2(TestBase val)" << endl;
		}
	};

	int sumOddDivisor(vector<int> nums) {
		int res = 0;

		for (int i = 0; i < nums.size(); ++i) {
			int cur = sqrt(nums[i]);

			for (int i = 1; i <= cur; i+=2) {
				if (0 == (nums[i] % i))
					res += i;
			}

			if (nums[i] > 1 && (nums[i] & 1))
				res += nums[i];
		}

		cout << res << endl;
		return res;
	}

	void minRCost(vector<int> radius, vector<int>cost) {
		vector<pair<int, int>> datas(radius.size());
		vector<int> data(radius);
		int len = radius.size();
		sort(data.begin(), data.end());

		int r_min = data[0] + data[1];
		int r_max = data[len - 2] + data[len - 1];

		data.assign(cost.begin(), cost.end());
		sort(data.begin(), data.end());
		int c_min = data[0] + data[1];
		int c_max = data[len - 2] + data[len - 1];

		vector<int> res(radius.size());
		for (int i = 0; i < radius.size(); ++i)
			datas[i] = make_pair(radius[i], cost[i]);

		sort(datas.begin(), datas.end());
		int i = 0;
	}

	//https://stackoverflow.com/questions/8871204/count-number-of-1s-in-binary-representation
	void VM_Main() {
		{
			vector<int> radius1 = { 1, 3, 6, 2, 5 };
			vector<int> cost1 = { 5, 6, 8, 3, 4 };
			minRCost(radius1, cost1);

			vector<int> num11 = { 1, 5, 7, 9 };
			sumOddDivisor(num11);
			TestDerive* derive = new TestDerive();
			Son* testson = new Son();
			testson->DoSomething1(*derive);
			testson->DoSomething2(*derive);

			vector<int> num1 = { 1, 4, 3, 2, 5 };
			vector<int> num2 = { 1, 2, 3, 4, 5 };
			vector<int> num3 = { 1, 3, 2, 4, 5 };
			vector<int> num4 = { 5, 4, 3, 2, 1 };
			vector<int> num5 = { 2, 5, 6, 9 };

			countOddSub(num2);
			countOddSub(num5);
			cout << getMinSwaps2(num1) << endl;
			cout << getMinSwaps2(num2) << endl;
			cout << getMinSwaps2(num3) << endl;
			cout << getMinSwaps2(num4) << endl;
		}
		{
			
			vector<string> ip_array = { "This is not an ip_address!", "192.168.1.1", "256.168.1.1", "0000:0123:ff00:00:ff:1234:00ff:1111" ,"0000:0123:ff00:00:ff:1234:00ff" };
			vector<string> results;
			results = checkIP(ip_array);
			for (vector<string>::iterator it = results.begin(); it != results.end(); ++it)
				cout << *it << endl;

			get_bit1(0xffffffff);
			get_bit1(0x1);
			get_bit1(0x8);
			get_bit1(0x9);
			int res;
			vector<int> data1 = { 2, 3, 10, 6, 4, 8, 1 };
			vector<int> data2 = { 7, 9, 5, 6, 3, 2 };
			vector<int> data3 = { 7, 5, 4, 3 };
			cout << maxDiff(data1) << endl;
			cout << maxDiff(data2) << endl;
			cout << maxDiff(data3) << endl;
			res = 0;
		}

		{
			int k1 = 3;
			vector<int> data1 = { 1, 2, 3, 4, 1 };
			cout << k_diff(data1, k1) << endl;

		}


		int i = 0;
	}

	//HHVV sequence
	class HVSEQ {
	public:
		vector<string> data;
		string res;
		int index;
		void calHV(int row, int col, int i, int j, string result, int idx) {
			if (row - 1 == i && col - 1 == j) {
				if (index++ == idx)
					res = result;
				return;
			}

			if (j < col - 1)
				calHV(row, col, i, j + 1, result + "H", idx);

			if (i < row - 1)
				calHV(row, col, i + 1, j, result + "V", idx);
		}

		void calHV2(int row, int col, int i, int j, string result) {
			if (row - 1 == i && col - 1 == j) {
				data.push_back(result);
				return;
			}

			if (j < col - 1)
				calHV2(row, col, i, j + 1, result + "H");

			if (i < row - 1)
				calHV2(row, col, i + 1, j, result + "V");
		}

		void findseq(int row, int col, int idx) {
			data.clear();
			res.clear();
			index = 0;
			string result;
			calHV(row, col, 0, 0, result, idx);
		}


		string findseq2(int row, int col, int idx) {
			data.clear();
			res.clear();
			index = 0;
			string result;
			calHV(row, col, 0, 0, result, idx);

			return data[idx];
		}

		static void main() {
			auto_ptr<HVSEQ> test(new HVSEQ);
			string result;

			test->findseq(3, 3, 0);
			result = test->res;

			test->findseq(3, 3, 2);
			result = test->res;

			test->findseq(3, 3, 3);
			result = test->res;

			test->findseq(3, 3, 5);
			result = test->res;

			test->findseq(2, 3, 2);
			result = test->res;
		}

		int main2() {
			/* Enter your code here. Read input from STDIN. Print output to STDOUT */
			int T, x, y, K;
			int total = 12;
			vector<vector<int>> dp(total, vector<int>(total, 0));

			for (int i = 0; i < 10; ++i) {
				dp[i][10] = 1;
				dp[10][i] = 1;
			}

			for (int i = 9; i >= 0; --i)
				for (int j = 9; j >= 0; --j) {
					dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
				}

			cin >> T;

			while (T--) {
				cin >> x;
				cin >> y;
				cin >> K;

				++K;
				string res;
				int cx = 10 - x, cy = 10 - y;
				for (int i = 0; i < x + y; ++i) {
					//cout<< "test1:" <<i <<endl;
					if (cx == 10) {
						res += "V";
						++cy;
						continue;
					}
					else if (cy == 10) {
						res += "H";
						++cx;
						continue;
					}

					if (dp[cx + 1][cy] < K) {
						res += "V";
						K -= dp[cx + 1][cy];
						++cy;
					}
					else {
						res += 'H';
						++cx;
					}
				}

				cout << res << endl;
			}

			return 0;
		}
	};

	//http://www.cnblogs.com/hellogiser/p/maximum-difference-of-array.html
	class MaxDif {
	public:
		int maxdiftwo(vector<int> vec) {
			int len = vec.size();
			if (len < 2)
				return -1;

			long maxdiff = numeric_limits<long>::min();
			long cur = vec[0];

			for (int i = 1; i < len; ++i) {
				if (cur < vec[i - 1])
					cur = vec[i - 1];

				if (cur > vec[i])
					maxdiff = max(maxdiff, cur - vec[i]);
			}
			
			return maxdiff == numeric_limits<long>::min() ? -1 : maxdiff;
		}

		static void main() {
			auto_ptr<MaxDif> test(new MaxDif);
			int result;

			vector<int> vec1 = { 2, 4, 1, 16, 7, 5, 11, 9 };
			vector<int> vec2 = { 2, 4, 4, 4 };

			result = test->maxdiftwo(vec1);
			result = test->maxdiftwo(vec2);
		}
	};

	//http://stackoverflow.com/questions/24518682/count-subarrays-divisible-by-k
	//https://github.com/derekhh/HackerRank/blob/master/consecutive-subsequences.cpp
	class Ksub {
	public:
		Ksub(){
		}

		void set(vector<int>& vec, int i) {
			data = vec;
			k = i;

			
		}

		int find() {
			long long result = 0;
			int len = data.size();
			vector<int> cntk(k, 0);
			int  presum = 0;
			cntk[0] = 1;

			for (int i = 0; i < len; ++i) {
				presum += data[i];
				presum %= k;
				++cntk[presum];
			}

			for (int i = 0; i < k; ++i)
				if (cntk[i] > 0)
					result += (long long)cntk[i] * (cntk[i] - 1) / 2;

			return result;
		}

		int main2() {
			/* Enter your code here. Read input from STDIN. Print output to STDOUT */
			int T, N, K;


			cin >> T;
			while (T--) {
				long long result = 0;

				cin >> N >> K;
				vector<int> cntk(K, 0);
				int presum = 0;
				int item;
				cntk[0] = 1;

				for (int i = 0; i < N; ++i) {
					cin >> item;
					presum += item;
					presum %= K;
					cntk[presum] ++;
				}

				for (int i = 0; i < K; ++i)
				if (cntk[i] > 0)
					result += (long long)cntk[i] * (cntk[i] - 1) / 2;

				cout << result << endl;
			}

			return 0;
		}

		static void main() {
			auto_ptr<Ksub> test(new Ksub);
			int result;

			vector<int> vec1 = { 1, 2, 1, 2, 1, 2 };
			int i1 = 2;

			test->set(vec1, i1);
			result = test->find();

			vector<int> vec2 = { 1, 2, 1, 2, 1, 2 };

		}

	private:
		vector<int> data;
		int k;
	};

	string urlDecode(string &SRC) {
		string ret;
		char ch;
		int i, ii;
		for (i = 0; i<SRC.length(); i++) {
			if (int(SRC[i]) == 37) {
				sscanf(SRC.substr(i + 1, 2).c_str(), "%x", &ii);
				ch = static_cast<char>(ii);
				ret += ch;
				i = i + 2;
			}
			else {
				ret += SRC[i];
			}
		}
		return (ret);
	}

	void detectDomain(void) {
		regex format("(http|https)\\://(www.|ww2.|)([a-zA-Z0-9\\-\\.]+)(\\.[a-zA-Z]+)(/\\S*)?");
		std::smatch match;
		vector<string>links;
		int N;
		string src;
		cin >> N;

		while (N--) {
			cin.ignore();
			src.clear();
			getline(cin, src);
			string source = urlDecode(src);

			auto searchStart(source.cbegin());
			while (regex_search(searchStart, source.cend(), match, format))
			{
				string item = match[3].str() + match[4].str();
				if (item.substr(0, 4) == "www.")
					item = item.substr(4);

				if (links.end() == find(links.begin(), links.end(), item)) {
					links.push_back(item);

				}
				searchStart += match.position() + match.length();
			}
		}

		sort(links.begin(), links.end());
		for (int j = 0; j < links.size(); ++j){
			if (j == links.size() - 1)
				cout << links[j];
			else
				cout << links[j] + ";";
		}
	}


	static void main() {
		Ksub::main();
		//detectDomain();
		
		MaxDif::main();
		HVSEQ::main();
	}
}


namespace AIR {
	class A{
	public:
		int i;
		string &t;

	};

	template <class T> class circlebuf {
	public:
		circlebuf(int n) {
			head = 0;
			back = 0;
			used = 0;
			data.resize(n);
		}

		void add(T item) {
			if (used == data.size()) {
				cout << "buf full\n";
				return;
			}

			if (head >= data.size())
				head = 0;

			data[head++] = item;
			++used;
			cout << "add item:"<< item << ",used:"<< used <<"\n";
		}

		T get() {
			T result;
			if (0 == used) {
				cout << "buf empty\n";
				result;
			}

			result = data[back++];
			if (back >= data.size())
				back = 0;
			--used;

			cout << "get item:" << result << ",used:" << used << "\n";
			return result;
		}
	private:
		int head;
		int back;
		int used;
		vector<T>data;
	};
		
	//enum EHstate { noErr, zeroOp, negativeOp, severeError };
	//enum EHstate state = noErr;

	
	class EHstate {
	public:
		EHstate() : error(0){ cout << "EHstate():" << this << endl; }

		EHstate(const EHstate& ref) {
		cout<< "this:" << this<< ",EHstate(EHstate& ref) : " <<&ref<< endl; error = ref.error; }

		EHstate & operator = (const EHstate& ref)
		{

			cout << "EHstate & operator =" << &ref << endl;
			return *this;
		}

		~EHstate() { cout << "~EHstate():" << this << endl; }
		int error;
	};

	EHstate state;
	void testf(int i, int& j) {
		int k = 0;
		k = i + j;
		if (0 == i) {
			state.error = 1;
			throw state;
		}
	}

	void calHV(int row, int col) {
		vector<vector<int>> dp(row, vector<int>(col, 0));
		int result;
		for (int i = 0; i < row; ++i)
			dp[i][0] = 1;

		for (int j = 0; j < col; ++j)
			dp[0][j] = 1;

		for (int i = 1; i < row; ++i)
		for (int j = 1; j < col; ++j) {
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}

		result = 0;
	}

	vector<string> hvresult;
	void calHV(int row, int col, int i, int j, string result) {
		if (row - 1 == i && col - 1 == j) {
			hvresult.push_back(result);
			return;
		}

		if (i < row - 1)
			calHV(row, col, i + 1, j, result + "V");

		if (j < col - 1)
			calHV(row, col, i, j + 1, result + "H");
	}

	static void main() {
		circlebuf<int> test(3);
		int i = 0, j = 3;
		try {
			testf(i, j);
		}

		catch (EHstate& mystate) {
			mystate.error = 0;
			//throw;
		}

		catch (std::exception e) {
			;//mystate.error = 0;
			//throw mystate;
		}

		{
			string result;
			calHV(3, 3, 0, 0, result);
			result.clear();
			calHV(2, 3, 0, 0, result);
		}
		int n = sizeof(A);
		test.add(1);
		test.add(2);
		test.add(3);
		test.add(4);
		test.get();
		test.add(4);
	}
}

//////////////////////////Tag GG//////////////////////////////////////////
namespace GG {
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	struct ListNode {
		int val;
		ListNode* next;
		ListNode(int x) : val(x), next(NULL) {}
	};

	struct UndirectedGraphNode {
		int label;
		UndirectedGraphNode(int x) : label(x) {};
		vector<UndirectedGraphNode *> neighbors;
	};

	struct Interval {
		int start;
		int end;
		Interval() : start(0), end(0) {}
		Interval(int s, int e) : start(s), end(e) {}
	};


	/*407. Trapping Rain Water II (hard)
	https://leetcode.com/problems/trapping-rain-water-ii/
	*/
	class Solution407 {
	public:
		bool isborder(int i, int j, int row, int col) {
			return 0 == i || i == row - 1 || 0 == j || j == col - 1;
		}

		bool islegal(int i, int j, int row, int col) {
			return i >= 0 && i < row && j >= 0 && j < col;
		}

		int trapRainWater(vector<vector<int>>& heightMap) {
			if (heightMap.size() < 3 || heightMap[0].size() < 3)
				return 0;

			int result;
			int row = heightMap.size();
			int col = heightMap[0].size();
			vector<pair<int, int>> dire = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

			vector<vector<bool>> flag(row, vector<bool>(col, false));

			for (int i = 1; i < row; ++i) {
				for (int j = 1; j < col; ++j) {
					int minheight = 0;
					vector<pair<int, int>> witems;
					queue<pair<int, int>> pos;

					if (!flag[i][j]) {
						bool havewater = true;

						pos.push(make_pair(i, j));
						while (!pos.empty()) {
							pair<int, int> cur = pos.front();
							pos.pop();
							witems.push_back(cur);
							flag[cur.first][cur.second] = true;
							for (auto item : dire) {
								int new_i = i + item.first;
								int new_j = j + item.second;

								if (!islegal(new_i, new_j, row, col) || flag[new_i][new_i])
									continue;

								//if ()
							}
						}
					}
				}
			}

			return result;
		}
	};
	/*407. Trapping Rain Water II end */


	/*391. Perfect Rectangle (hard)
	https://leetcode.com/problems/perfect-rectangle/
	https://discuss.leetcode.com/topic/55997/short-java-solution-with-explanation-updated
	*/
	class Solution391 {
	public:
		unordered_map<string, int> hash;
		bool isRectangleCover(vector<vector<int>>& rectangles) {
			int lx = numeric_limits<int>::max();
			int ly = lx;
			int rx = numeric_limits<int>::min();
			int ry = rx;
			int total = 0;

			for (auto item : rectangles) {
				lx = min(item[0], lx);
				ly = min(item[1], ly);
				rx = max(item[2], rx);
				ry = max(item[3], ry);

				total += (item[2] - item[0]) * (item[3] - item[1]);
				//bottom left 
				if (overLap(to_string(item[0]) + " " + to_string(item[1]), 1))
					return false;

				//top left
				if (overLap(to_string(item[0]) + " " + to_string(item[3]), 2))
					return false;

				//bottom right
				if (overLap(to_string(item[2]) + " " + to_string(item[1]), 4))
					return false;

				//top right
				if (overLap(to_string(item[2]) + " " + to_string(item[3]), 8))
					return false;
			}

			int count = 0;
			for (auto item : hash) {
				int type = item.second;
				//1111, 1100, 1010, 1001, 0110, 0101, 0011
				if (15 != type && 12 != type && 10 != type && 9 != type
					&& 6 != type && 5 != type && 3 != type)
					++count;
			}

			return 4 == count && total == (rx - lx)*(ry - ly);
		}

		bool overLap(string str, int type) {
			int tmp;
			if (hash.count(str) < 1)
				tmp = type;
			else {
				tmp = hash[str];
				if (0 != (tmp & type))
					return false;
				else
					tmp |= type;
			}

			hash[str] = tmp;
			return false;
		}
	};
	/*391. Perfect Rectangle end */


	/*380. Insert Delete GetRandom O(1) (hard)
	https://leetcode.com/problems/insert-delete-getrandom-o1/
	https://discuss.leetcode.com/topic/53286/ac-c-solution-unordered_map-vector
	*/
	class RandomizedSet380 {
	public:
		/** Initialize your data structure here. */
		RandomizedSet380() {

		}

		/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
		bool insert(int val) {
			if (m.find(val) != m.end()) return false;
			nums.emplace_back(val);
			m[val] = nums.size() - 1;
			return true;
		}

		/** Removes a value from the set. Returns true if the set contained the specified element. 
			move the last to the removed one because the size of vector will be decreased by 1*/
		bool remove(int val) {
			if (m.find(val) == m.end()) return false;
			int last = nums.back();
			m[last] = m[val];
			nums[m[val]] = last;
			nums.pop_back();
			m.erase(val);
			return true;
		}

		/** Get a random element from the set. */
		int getRandom() {
			int n = nums.size();

			return  0 == n ? -1 : nums[rand() % n];
		}
	private:
		vector<int> nums;
		unordered_map<int, int> m;
	};
	/*380. Insert Delete GetRandom O(1) end */



	/*363. Max Sum of Rectangle No Larger Than K (hard)
	Time = O(min(m,n)^2 * max(m,n) * log(max(m,n)))		Space = O(max(m, n)).
	https://leetcode.com/problems/max-sum-of-sub-matrix-no-larger-than-k/
	https://discuss.leetcode.com/topic/48875/accepted-c-codes-with-explanation-and-references
	*/
	class Solution363 {
	public:
		int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
			int row = matrix.size();
			int col = matrix[0].size();
			long cursum, result, curmax;

			result = numeric_limits<long>::min();
			for (int left = 0; left < col; ++left) {
				vector<long> cur(row, 0);

				for (int right = left; right < col; ++right) {
					for (int i = 0; i < row; ++i)
						cur[i] += matrix[i][right];

					set<long> sets;
					cursum = 0;
					curmax = numeric_limits<long>::min();
					sets.insert(0);

					for (auto item : cur) {
						cursum += item;

						set<long>::iterator ite = sets.lower_bound(cursum - k);
						if (ite != sets.end())
							curmax = max(curmax, cursum - *ite);

						sets.insert(cursum);
					}

					result = max(result, curmax);
				}
			}

			return result;
		}

		vector<int> findKadane1(vector<int> vec, int k) {
			long maxcur = vec[0];
			long maxglobal = vec[0];
			vector<int> result(2, -1);
			int left = 0;
			int right = 0;

			for (int i = 1; i < vec.size(); ++i) {
				if (vec[i] > maxcur + vec[i]) {
					left = i;
					maxcur = vec[i];
				}
				else
					maxcur = maxcur + vec[i];

				right = i;
				if (maxcur > maxglobal) {
					result[0] = left;
					result[1] = right;
					maxglobal = maxcur;
				}
			}

			return result;
		}

		vector<int> findKadane(vector<int> vec) {
			long maxcur = vec[0];
			long maxglobal = vec[0];
			vector<int> result(2, 0);
			int left = 0;
			int right = 0;

			for (int i = 1; i < vec.size(); ++i) {
				if (vec[i] > maxcur + vec[i]) {
					left = i;
					maxcur = vec[i];
				}
				else
					maxcur = maxcur + vec[i];

				right = i;
				if (maxcur > maxglobal) {
					result[0] = left;
					result[1] = right;
					maxglobal = maxcur;
				}
			}

			return result;
		}

		static void main() {
			auto_ptr<Solution363> test(new Solution363);
			vector<int> result;
			vector<int> vec1 = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
			result = test->findKadane(vec1);
		}
	};
	/*363. Max Sum of Rectangle No Larger Than K end */


	/*358. Rearrange String k Distance Apart (hard)
	https://leetcode.com/problems/rearrange-string-k-distance-apart/
	https://discuss.leetcode.com/topic/48091/c-unordered_map-priority_queue-solution-using-cache
	https://discuss.leetcode.com/topic/48260/java-15ms-solution-with-two-auxiliary-array-o-n-time
	*/
	class Solution358 {
	public:
		string rearrangeString(string str, int k) {
			if (k < 2)
				return str;

			string result("");
			unordered_map<char, int> data;
			for (auto item : str)
				data[item] ++;

			int len = str.size();
			priority_queue<pair<int, char>> que;
			for (auto item : data)
				que.push({ item.second, item.first });

			while (!que.empty()) {
				vector<pair<int, char>> cache;
				int count = min(k, len);

				for (int i = 0; i < count; ++i) {
					if (que.empty())
						return "";

					auto item = que.top();
					que.pop();
					result += item.second;
					if (--item.first)
						cache.push_back(item);
					--len;
				}

				for (auto item : cache)
					que.push(item);
			}

			return result;
		}
	};
	/*358. Rearrange String k Distance Apart end */


	/*354. Russian Doll Envelopes (hard)
	https://leetcode.com/problems/russian-doll-envelopes/
	https://discuss.leetcode.com/topic/47469/java-nlogn-solution-with-explanation/4
	https://discuss.leetcode.com/topic/28738/java-python-binary-search-o-nlogn-time-with-explanation
	https://discuss.leetcode.com/topic/28685/c-typical-dp-n-2-solution-and-nlogn-solution-from-geekforgeek/2
	*/
	class Solution354 {
	public:
		int maxEnvelopes1(vector<pair<int, int>>& envelopes) {
			int len = envelopes.size();
			if (len < 2)
				return len;

			sort(envelopes.begin(), envelopes.end(), [](pair<int, int>&a, pair<int, int>&b) { return a.first == b.first ? a.second > b.second : a.first < b.first; });
			vector<int> tails(len + 1);

			int i = 0, count = 0, j;
			for (auto x : envelopes) {
				i = 0;
				j = count;

				while (i != j) {
					int mid = i + (j - i) / 2;

					if (tails[mid] < x.second)
						i = mid + 1;
					else
						j = mid;
				}

				tails[i] = x.second;
				if (i == count)
					++count;
			}

			return count;
		}

		static bool cmp_first(const pair<int, int>& i, const pair<int, int>& j) {
			if (i.first == j.first)
				return i.second > j.second;
			return i.first < j.first;
		}

		int maxEnvelopes(vector<pair<int, int>>& envelopes) {
			vector<int> candidates;
			sort(envelopes.begin(), envelopes.end(), cmp_first);
			vector<int> dp;
			for (int i = 0; i < envelopes.size(); ++i) {
				auto itr = lower_bound(dp.begin(), dp.end(), envelopes[i].second);
				if (itr == dp.end()) {
					dp.push_back(envelopes[i].second);
				}
				else {
					*itr = envelopes[i].second;
				}
			}
			return dp.size();
		}
	};
	/*354. Russian Doll Envelopes end */


	/*340. Longest Substring with At Most K Distinct Characters (hard)
	https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/
	https://discuss.leetcode.com/topic/41711/8-lines-c-o-n-8ms
	*/
	class Solution340 {
	public:
		int lengthOfLongestSubstringKDistinct(string s, int k) {
			if (s.empty() || 0 == k)
				return 0;

			int result = 1;
			int len = s.size();
			unordered_map<int, int> hash;
			for (int idx = 0, start = 0; idx < len; ++idx) {
				hash[s[idx]] ++;

				if (hash.size() <= k)
					result = max(result, idx - start + 1);

				while (hash.size() > k && start < len) {
					if (--hash[s[start]] == 0)
						hash.erase(s[start]);

					++start;
				}
			}

			return result;
		}

		int lengthOfLongestSubstringKDistinct1(string s, int k) {
			if (s.empty() || 0 == k)
				return 0;

			int result = 1;
			vector<int> hash(256, 0);
			int len = s.size();
			int count = 0, idx = 0;
			for (auto item : s)
				hash[item - 'a']++;

			for (int i = 0; i < len; ++i) {
				unordered_set<char> data;
				data.insert(s[i]);
				for (int j = i + 1; j < len; ++j){
					data.insert(s[j]);

					if (data.size() > k)
						break;
					
					result = max(result, j - i + 1);
				}
			}

			return result;
		}

		static void main() {
			auto_ptr<Solution340> test(new Solution340);
			int result;

			string s1("bacc");
			int k1 = 2;
			result = test->lengthOfLongestSubstringKDistinct(s1, k1);
		}
	};
	/*340. Longest Substring with At Most K Distinct Characters end */


	/*336. Palindrome Pairs (hard)
	https://leetcode.com/problems/palindrome-pairs/
	https://discuss.leetcode.com/topic/40657/150-ms-45-lines-java-solution
	*/
	class Solution336 {
	public:
		bool isPalin(string & str) {
			int low = 0, high = str.size() - 1;
			while (low < high) {
				if (str[low] != str[high])
					return false;

				++low;
				--high;
			}

			return true;
		}

		vector<vector<int>> palindromePairs(vector<string>& words) {
			vector<vector<int>> result;
			int len = words.size();
			if (len < 2)
				return result;

			unordered_map<string, int> hash;
			for (int i = 0; i < len; ++i)
				hash[words[i]] = i;

			for (int i = 0; i < len; ++i)
			for (int k = 0; k <= words[i].size(); ++k) {
				string str1 = words[i].substr(0, k);
				string str2 = words[i].substr(k);

				if (isPalin(str1)) {
					string tmp(str2);
					reverse(tmp.begin(), tmp.end());
					if (hash.count(tmp) && hash[tmp] != i)
						result.push_back({ hash[tmp], i });
				}

				if (isPalin(str2)) {
					string tmp(str1);
					reverse(tmp.begin(), tmp.end());
					if (hash.count(tmp) && hash[tmp] != i && !tmp.empty())
						result.push_back({ i, hash[tmp] });
				}
			}

			return result;
		}

		vector<vector<int>> palindromePairs1(vector<string>& words) {
			vector<vector<int>> result;
			int len = words.size();
			if (len < 2)
				return result;
			
			unordered_set<string> hash;

			for (int i = 0; i < len - 1; ++i)
			for (int j = i + 1; j < len; ++j) {
				string tmp = words[i] + words[j];

				if (hash.count(tmp) || isPalin(tmp)) {
					result.push_back({ i, j });
					if (0 == hash.count(tmp))
						hash.insert(tmp);
				}

				tmp = words[j] + words[i];
				if (hash.count(tmp) || isPalin(tmp)) {
					result.push_back({ j, i });

					if (0 == hash.count(tmp))
						hash.insert(tmp);
				}
			}

			return result;
		}

		static void main() {
			auto_ptr<Solution336> test(new Solution336);
			vector<vector<int>> result;

			vector<string> words1 = { "bat", "tab", "cat" };
			vector<string> words2 = { "abcd", "dcba", "lls", "s", "sssll" };
			vector<string> words3 = { "a", "" };

			//result = test->palindromePairs(words1);
			result = test->palindromePairs(words3);
		}
	};
	/*336. Palindrome Pairs end */


	/*330. Patching Array (hard)
	https://leetcode.com/problems/patching-array/
	https://discuss.leetcode.com/topic/35494/solution-explanation
	*/
	class Solution330 {
	public:
		int minPatches(vector<int>& nums, int n) {
			long missed = 1, result = 0, i = 0;
			int len = nums.size();

			while (missed <= n) {
				if (i < len && missed >= nums[i])
					missed += nums[i++];
				else {
					missed += missed;
					++result;
				}
			}

			return result;
		}
	};
	/*330. Patching Array end */


	/*329. Longest Increasing Path in a Matrix (hard)
	Time = O(m*n)	Space = O(m*n)
	https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
	https://discuss.leetcode.com/topic/35021/graph-theory-java-solution-o-v-2-no-dfs
	https://discuss.leetcode.com/topic/34835/15ms-concise-java-solution
	*/
	class Solution329 {
	public:
		int findPath(vector<vector<int>>& matrix, int i, int j, int row, int col, vector<vector<int>>& mem, int &result) {
			vector<pair<int, int>> dir = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
			if (mem[i][j] != 1)
				return mem[i][j];

			int ans = 1;
			for (auto item : dir) {
				int pos_i = i + item.first;
				int pos_j = j + item.second;

				if (pos_i < 0 || pos_j < 0 || pos_i >= row || pos_j >= col)
					continue;

				if (matrix[i][j] >= matrix[pos_i][pos_j])
					continue;

				int tmp = findPath(matrix, pos_i, pos_j, row, col, mem, result) + 1;
				ans = max(ans, tmp);
			}

			result = max(result, ans);
			mem[i][j] = ans;
			return ans;
		}

		int longestIncreasingPath(vector<vector<int>>& matrix) {
			if (matrix.empty() || matrix[0].empty())
				return 0;

			int result = 0;
			int row = matrix.size();
			int col = matrix[0].size();

			vector<vector<int>> mem(row, vector<int>(col, 1));
			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j)
					findPath(matrix, i, j, row, col, mem, result);

			return result;
		}
	};
	/*329. Longest Increasing Path in a Matrix end */


	/*327. Count of Range Sum (hard)
	Time = O(n*logn)	Space = O(n)
	https://leetcode.com/problems/count-of-range-sum/
	https://discuss.leetcode.com/topic/33738/share-my-solution
	*/
	class Solution327 {
	public:
		int countRangeSum(vector<int>& nums, int lower, int upper) {
			int size = nums.size();
			if (size == 0)  return 0;
			vector<long> sums(size + 1, 0);
			for (int i = 0; i<size; i++)  sums[i + 1] = sums[i] + nums[i];
			return help(sums, 0, size + 1, lower, upper);
		}

		/*** [start, end)  ***/
		int help(vector<long>& sums, int start, int end, int lower, int upper){
			/*** only-one-element, so the count-pair=0 ***/
			if (end - start <= 1)  return 0;
			int mid = (start + end) / 2;
			int count = help(sums, start, mid, lower, upper)
				+ help(sums, mid, end, lower, upper);

			int m = mid, n = mid, t = mid, len = 0;
			/*** cache stores the sorted-merged-2-list ***/
			/*** so we use the "count" to record the merged length ***/
			vector<long> cache(end - start, 0);
			for (int i = start, s = 0; i < mid; ++i, ++s){
				/*** wrong code: while(m<end && sums[m++]-sums[i]<lower);  ***/
				while (m < end && sums[m] - sums[i] < lower) ++m;
				while (n < end && sums[n] - sums[i] <= upper) ++n;
				count += n - m;
				/*** cache will merge-in-the-smaller-part-of-list2 
				that means small part of list2 needs to be mergerd to the front,
				because all the merge are in the same vector***/
				while (t < end && sums[t] < sums[i]) cache[s++] = sums[t++];
				cache[s] = sums[i];
				len = s;
			}

			for (int i = 0; i <= len; i++)  sums[start + i] = cache[i];
			return count;
		}

		int countRangeSum1(vector<int>& nums, int lower, int upper) {
			int result = 0;
			int len = nums.size();
			vector<long> sums(len + 1, 0);

			for (int i = 0; i < len; ++i)
				sums[i + 1] = sums[i] + nums[i];

			for (int i = 0; i < len; ++i) {
				for (int j = i + 1; j <= len; ++j) {
					long tmp = sums[j] - sums[i];
					if (tmp >= lower && tmp <= upper)
						++result;
				}

			}

			return result;
		}

		static void main() {
			//Solution327* test = new Solution327;
			auto_ptr<Solution327> test(new Solution327);
			int result;
			vector<int> nums1 = {1, -2, -1, 4};

			result = test->countRangeSum(nums1, -2, 2);
			result = result;
		}
	};
	/*327. Count of Range Sum end */


	/*321. Create Maximum Number (hard)
	Time O((m+n)^3) in the worst case
	https://leetcode.com/problems/create-maximum-number/
	https://discuss.leetcode.com/topic/32272/share-my-greedy-solution/2
	*/
	class Solution321 {
	public:
		vector<int> maxArray(vector<int>& nums, int k) {
			vector<int> result(k);
			int len = nums.size();

			for (int i = 0, j = 0; i < len; ++i) {
				//make sure enough items for compose k items
				while (len - i > k - j  && j > 0 && result[j - 1] < nums[i])
					--j;

				if (j < k)
					result[j++] = nums[i];
			}

			return result;
		}

		bool greater(vector<int>& num1, int i, vector<int>& num2, int j) {
			int len1 = num1.size();
			int len2 = num2.size();

			while (i < len1 && j < len2 && num1[i] == num2[j]) {
				++i;
				++j;
			}

			return j == len2 || (i < len1 && num1[i] > num2[j]);
		}

		vector<int> mergerArray(vector<int>& num1, vector<int>& num2, int k) {
			vector<int> result(k);
			int idx = 0;

			for (int i = 0, j = 0; idx < k; ++idx)
				result[idx] = greater(num1, i, num2, j) ? num1[i++] : num2[j++];

			return result;
		}

		vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
			int len1 = nums1.size();
			int len2 = nums2.size();
			vector<int> result;

			for (int i = max(0, k - len2); i <= k && i <= len1; ++i) {
				vector<int> max1 = maxArray(nums1, i);
				vector<int> max2 = maxArray(nums2, k - i);
				vector<int> tmp = mergerArray(max1, max2, k);
				
				if (greater(tmp, 0, result, 0))
					result = tmp;
			}

			return result;
		}

		static void main() {
			auto_ptr<Solution321> test(new Solution321);
			vector<int> result;
			vector<int> nums1 = {6, 7};
			vector<int> nums2 = { 6, 0, 4 };
			int k = 5;

			result = test->maxNumber(nums1, nums2, k);
		}
	};
	/*321. Create Maximum Number end */


	/*317. Shortest Distance from All Buildings (hard)
	Time = O(kmn)	Space = O(m*n)  k is number of empty place 
	https://leetcode.com/problems/shortest-distance-from-all-buildings/
	https://discuss.leetcode.com/topic/31702/36-ms-c-solution
	https://discuss.leetcode.com/topic/31925/java-solution-with-explanation-and-time-complexity-analysis
	*/
	class Solution317 {
	public:
		int shortestDistance(vector<vector<int>>& grid) {
			int m = grid.size(), n = grid[0].size();
			auto total = grid;
			int walk = 0, mindist, delta[] = { 0, 1, 0, -1, 0 };

			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < n; ++j) {
					if (grid[i][j] == 1) {
						mindist = -1;
						auto dist = grid;
						queue<pair<int, int>> q;
						q.emplace(i, j);
						while (q.size()) {
							auto ij = q.front();
							q.pop();
							for (int d = 0; d < 4; ++d) {
								int pos_i = ij.first + delta[d];
								int pos_j = ij.second + delta[d + 1];
								if (pos_i >= 0 && pos_i < m && pos_j >= 0 && pos_j < n && grid[pos_i][pos_j] == walk) {
									grid[pos_i][pos_j]--;
									dist[pos_i][pos_j] = dist[ij.first][ij.second] + 1;
									total[pos_i][pos_j] += dist[pos_i][pos_j] - 1;
									q.emplace(pos_i, pos_j);
									if (mindist < 0 || mindist > total[pos_i][pos_j])
										mindist = total[pos_i][pos_j];
								}
							}
						}
						walk--;
					}
				}
			}

			return mindist;
		}

		static void main() {
			auto_ptr<Solution317> test(new Solution317);
			int result;
			vector<vector<int>> grid1 = { { 1, 0, 2, 0, 1 }, { 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0 } };

			result = test->shortestDistance(grid1);
		}
	};
	/*317. Shortest Distance from All Buildings end */


	/*316. Remove Duplicate Letters (hard)
	Time = O(26 * n)	Space = O(n) or O(1)
	https://leetcode.com/problems/remove-duplicate-letters/
	https://discuss.leetcode.com/topic/31404/a-short-o-n-recursive-greedy-solution
	https://discuss.leetcode.com/topic/31413/easy-to-understand-iterative-java-solution
	*/
	class Solution316 {
	public:
		string removeDuplicateLetters(string s) {
			vector<int> hash(26, 0);

			for (auto item : s)
				hash[item - 'a'] ++;

			int pos = 0;
			char c;
			for (int i = 0; i < s.size(); ++i) {
				c = s[i];
				if (s[pos] > c)
					pos = i;

				if (--hash[c - 'a'] == 0)
					break;
			}

			string tmp;
			for (int i = pos + 1; i < s.size(); ++i)
			if (s[i] != s[pos])
				tmp.push_back(s[i]);

			return s.empty() ? "" : s[pos] + removeDuplicateLetters(tmp);
		}

		string removeDuplicateLetters1(string s) {
			map<char, int> pos;

			//find last postion of every char
			for (int i = s.size() - 1; i >= 0; --i) {
				if (pos.count(s[i]) < 1)
					pos[s[i]] = i;

				if (pos.size() >= 26)
					break;
			}

			string result;
			result.resize(pos.size());
			int start = 0;
			int cur = 0;

			for (int i = 0; i < pos.size(); ++i) {
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


	/*315. Count of Smaller Numbers After Self (hard)
	Time = O(log n * n)	Space = O(n)
	https://leetcode.com/problems/count-of-smaller-numbers-after-self/
	https://discuss.leetcode.com/topic/31405/9ms-short-java-bst-solution-get-answer-when-building-bst
	https://discuss.leetcode.com/topic/31162/mergesort-solution
	https://discuss.leetcode.com/topic/31288/c-o-nlogn-time-o-n-space-mergesort-solution-with-detail-explanation
	http://blog.csdn.net/qq508618087/article/details/51320926
	*/
	class Solution315 {
	public:
		class Node {
		public:
			Node* left;
			Node* right;
			int val, sum, dup;
			Node(int v, int s):left(nullptr), right(nullptr),val(v),sum(s), dup(1){}
		};

		Node* insert(int num, Node* root, int i, int presum, vector<int>& result) {
			if (nullptr == root) {
				root = new Node(num, 0);
				result[i] = presum;
			}
			else if (root->val == num) {
				root->dup++;
				result[i] = presum + root->sum;
			}
			else if (root->val < num)
				root->right = insert(num, root->right, i, presum + root->sum + root->dup, result);
			else {
				root->sum++;
				root->left = insert(num, root->left, i, presum, result);
			}

			return root;
		}

		void myCount(vector<int>& nums, vector<int>& result) {
			if (nums.size() == result.size())
				return;

			int len = result.size();
			for (int i = 0; i < len; ++i) {
				if (nums[i] > nums[len])
					result[i] ++;
			}

			result.push_back(0);
			myCount(nums, result);
		}
		
		vector<int> countSmaller1(vector<int>& nums) {
			vector<int> result(nums.size(), 0);

			if (nums.empty())
				return result;

			//myCount(nums, result);
			Node* root = nullptr;
			for (int i = nums.size() - 1; i >= 0; --i)
				root = insert(nums[i], root, i, 0, result);

			return result;
		}

		void help(vector<pair<int, int>>& vec, int low, int high, vector<int>& result) {
			if (low == high - 1)
				return;

			int count = 0;
			int mid = low + (high - low) / 2;
			int right = mid;
			help(vec, low, mid, result);
			help(vec, mid, high, result);
			
			vector<long> cache(high - low, 0);
			for (int i = low; i < mid; ++i) {
				while (right < high && vec[i].first > vec[right].first)
					++right;

				result[vec[i].second] += right - mid;
			}

			//after loop, all the bigger number postion will >= final right
			//so, no sorting for that part
			inplace_merge(vec.begin() + low, vec.begin() + mid, vec.begin() + right);
		}

		vector<int> countSmaller(vector<int>& nums) {
			if (nums.empty())
				return vector<int>();
			int len = nums.size();
			vector<int> result(len, 0);
			vector<pair<int, int>> vec(len);

			for (int i = 0; i < len; ++i)
				vec[i] = { nums[i], i };

			help(vec, 0, len, result);
			return result;
		}
	};
	/*315. Count of Smaller Numbers After Self end */


	/*312. Burst Balloons (hard)
	Time = O(n^3)		Space = O(n)
	https://leetcode.com/problems/burst-balloons/
	https://discuss.leetcode.com/topic/30746/share-some-analysis-and-explanations/16
	*/
	class Solution312 {
	public:
		int maxCoins(vector<int>& nums) {
			vector<int> inums(nums.size() + 2, 0);
			int n = inums.size();

			inums[0] = inums[n - 1] = 1;
			int idx = 1;
			for (auto item : nums)
				inums[idx++] = item;

			//k can be seen as right
			vector<vector<int>> dp(n, vector<int>(n, 0));
			for (int k = 2; k < n; ++k) {
				for (int left = 0; left < n - k; ++left) {
					int right = left + k;
					//this loop can be thought as first loop
					for (int i = left + 1; i < right; ++i)
						dp[left][right] = max(dp[left][right], inums[left] * inums[i] * inums[right] + dp[left][i] + dp[i][right]);
				}
			}

			return dp[0][n - 1];
		}
	};
	/*312. Burst Balloons end */


	/*308. Range Sum Query 2D - Mutable (hard)
	Time = O(n * log n)		Space = O(2 * n) 
	https://leetcode.com/problems/range-sum-query-2d-mutable/
	http://blog.csdn.net/qq508618087/article/details/51303552
	http://www.guoting.org/leetcode/leetcode-308-range-sum-query-2d-mutable/
	http://blog.csdn.net/qq508618087/article/details/50952147
	*/
	class NumMatrix308 {
	public:
		vector<vector<int>> &vec;
		vector<vector<int>> sum;
		NumMatrix308(vector<vector<int>> &matrix):vec(matrix){
			if (matrix.empty())
				return;

			int m = matrix.size();
			int n = matrix[0].size();

			sum.resize(m, vector<int>(n + 1, 0));
			for (int i = 0; i < m; i++)
				for (int j = 1; j <= n; j++)
					add(matrix[i][j - 1], i, j);
		}
		
		void add(int val, int x, int y) {
			while (y < sum[x].size()) {
				sum[x][y] += val;
				y += (y & -y);
			}
		}
		
		int getSum(int x, int y) {
			int ans = 0;
			while (y > 0) {
				ans += sum[x][y];
				y -= (y & -y);
			}

			return ans;
		}

		void update(int row, int col, int val) {
			int d = val - vec[row][col];
			vec[row][col] = val;
			add(d, row, col + 1);
		}

		int sumRegion(int row1, int col1, int row2, int col2) {
			int ans = 0;
			for(int i = row1; i <= row2; ++i)
				ans += (getSum(i, col2 + 1) - getSum(i, col1));

			return ans;
		}
	};

	/*308. Range Sum Query 2D - Mutable end */


	/*305. Number of Islands II (hard)
	https://leetcode.com/problems/number-of-islands-ii/
	https://discuss.leetcode.com/topic/29518/java-python-clear-solution-with-unionfind-class-weighting-and-path-compression
	*/
	class Solution305 {
	public:
		class unionFind {
		public:
			int m, n, count;
			vector<int> ids;
			vector<int> sz;

			unionFind(int row, int col) {
				m = row;
				n = col;
				count = 0;
				ids.resize(m * n + 1, 0);
				sz.resize(m * n + 1, 0);
			}

			int index(int x, int y) {
				return x * n + y + 1;
			}

			int getid(int x, int y) {
				if (x >= 0 && x < m && y >= 0 && y < n)
					return ids[index(x, y)];

				return -1;
			}

			bool find(int p, int q) {
				return root(p) == root(q);
			}

			void merge(int p, int q) {
				int i = root(p);
				int j = root(q);

				if (sz[i] < sz[j]) {
					ids[i] = j;
					sz[j] += sz[i];
				}
				else {
					ids[j] = i;
					sz[i] += sz[j];
				}

				--count;
			}

			int add(int id) {
				//int id = index(x, y);
				ids[id] = id;
				sz[id] = 1;
				++count;

				return id;
			}

			int root(int index) {
				while (index != ids[index]) {
					ids[index] = ids[ids[index]];
					index = ids[index];
				}

				return index;
			}
		};

		vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
			vector<int> result;
			unionFind islands(m, n);
			vector<pair<int, int>>dirs = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

			for (auto item : positions) {
				int x = item.first;
				int y = item.second;
				int p = islands.index(x, y);

				islands.add(p);
				for (auto dir : dirs) {
					int q = islands.getid(x + dir.first, y + dir.second);
					if (q > 0 && !islands.find(p, q))
						islands.merge(p, q);
				}

				result.push_back(islands.count);
			}

			return result;
		}

	};
	/*305. Number of Islands II end */


	/*302. Smallest Rectangle Enclosing Black Pixels (hard)
	Time = O(m * log n + n * log m)		Space = O(1)
	https://leetcode.com/problems/smallest-rectangle-enclosing-black-pixels/
	https://discuss.leetcode.com/topic/29006/c-java-python-binary-search-solution-with-explanation
	*/
	class Solution302 {
	public:
		vector<vector<char>> *image;
		int minArea(vector<vector<char>>& iImage, int x, int y) {
			image = &iImage;
			int row = iImage.size();
			int col = iImage[0].size();
			int left, right, up, down;

			up = searchRow(0, x, 0, col, true);
			down = searchRow(x + 1, row, 0, col, false);
			left = searchCol(0, y, up, down, true);
			right = searchCol(y + 1, col, up, down, false);
			return (right - left) * (down - up);
		}

		int searchRow(int i, int j, int low, int high, bool opt) {
			while (i != j) {
				int k = low;
				int mid = i + (j - i) / 2;
				//try to find 1 in current row 
				while (k < high && '0' == (*image)[mid][k])
					++k;

				//no any 1 in current row
				if (k < high == opt)
					j = mid;
				else
					i = mid + 1;
			}

			return i;
		}

		int searchCol(int i, int j, int low, int high, bool opt) {
			while (i != j) {
				int k = low;
				int mid = i + (j - i) / 2;
				while (k < high && '0' == (*image)[k][mid])
					++k;

				if (k < high == opt)
					j = mid;
				else
					i = mid + 1;
			}

			return i;
		}

		int minArea1(vector<vector<char>>& image, int x, int y) {
			if (image.empty() || image[0].empty() ||
				x > image.size() || x < 0 ||
				y > image[0].size() || y < 0)
				return 0;

			int row = image.size();
			int col = image[0].size();
			unordered_set<int> flag;
			queue<pair<int, int>> visit;
			int left, right, up, down;

			left = right = y;
			up = down = x;
			visit.push({ x, y });

			while (!visit.empty()) {
				pair<int, int> cur = visit.front();
				int i = cur.first;
				int j = cur.second;
				flag.insert(i * col + j);
				visit.pop();

				left = min(left, j);
				right = max(right, j);
				up = min(up, i);
				down = max(down, i);

				if (i > 0 && '1' == image[i - 1][j] && 0 == flag.count((i - 1) * col + j))
					visit.push({ i - 1, j });

				if (i < row - 1 && '1' == image[i + 1][j] && 0 == flag.count((i + 1) * col + j))
					visit.push({ i + 1, j });

				if (j > 0 && '1' == image[i][j - 1] && 0 == flag.count(i * col + j - 1))
					visit.push({ i, j - 1 });

				if (j < col - 1 && '1' == image[i][j + 1] && 0 == flag.count(i * col + j + 1))
					visit.push({ i, j + 1 });
			}

			return (right - left + 1) * (down - up + 1);
		}
	};
	/*302. Smallest Rectangle Enclosing Black Pixels end */


	/*297. Serialize and Deserialize Binary Tree (hard)
	https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
	https://discuss.leetcode.com/topic/28041/recursive-preorder-python-and-c-o-n/2
	*/
	class Codec297 {
	public:
		void serialize(TreeNode* root, ostringstream& out) {
			if (root) {
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

		static void main(){
			Codec297* test = new Codec297;
			TreeNode* node1 = new TreeNode(1);
			TreeNode* node2 = new TreeNode(2);
			TreeNode* node3 = new TreeNode(3);
			TreeNode* node4 = new TreeNode(4);
			TreeNode* node5 = new TreeNode(5);
			node1->left = node2;
			node1->right = node3;
			node3->left = node4;
			node3->right = node5;
			string str = test->serialize(node1);

			TreeNode* root = test->deserialize(str);
			delete test;
		}
	};
	/*297. Serialize and Deserialize Binary Tree end */


	/*295. Find Median from Data Stream (hard)
	Time = O(1)		Space = O(n)
	https://leetcode.com/problems/find-median-from-data-stream/
	https://discuss.leetcode.com/topic/27521/short-simple-java-c-python-o-log-n-o-1
	https://discuss.leetcode.com/topic/27522/java-python-two-heap-solution-o-log-n-add-o-1-find
	*/
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
	};
	/*295. Find Median from Data Stream end */


	/*282. Expression Add Operators (hard)
	Time = O(4 ^ n)		Space = O(4 ^ n)
	T(n) = 3 * T(n-1) + 3 * T(n-2) + 3 * T(n-3) + ... + 3 *T(1);
	T(n-1) = 3 * T(n-2) + 3 * T(n-3) + ... 3 * T(1);
	Thus T(n) = 4T(n-1);
	https://leetcode.com/problems/expression-add-operators/
	https://discuss.leetcode.com/topic/24523/java-standard-backtrace-ac-solutoin-short-and-clear/2
	https://discuss.leetcode.com/topic/24478/17-lines-solution-dfs-c
	*/
	class Solution282 {
	public:
		void cal(string num, int target, char preoper, long prenum, vector<string>&res, int total, string form) {
			int curtotal;
			for (int i = 1; i <= num.size(); ++i) {
				string s = num.substr(0, i);
				curtotal = total;
				if (s.size() > 1 && '0' == s[0])
					continue;

				int flag = 1;
				if ('-' == preoper)
					flag = -1;

				long cur = atol(s.c_str()) * flag;
				if ('+' == preoper || '-' == preoper)
					curtotal += cur;
				else {
					curtotal -= prenum;
					cur *= prenum;
					curtotal += cur;
				}

				if (i == num.size()) {
					if (curtotal == target)
						res.push_back(form + s);

					return;
				}

				cal(num.substr(i), target, '-', cur, res, curtotal, form + s + "-");
				cal(num.substr(i), target, '+', cur, res, curtotal, form + s + "+");
				cal(num.substr(i), target, '*', cur, res, curtotal, form + s + "*");
			}
		}

		vector<string> addOperators(string num, int target) {
			vector<string> result;
			int total = 0;
			string form;
			cal(num, target, '+', 0, result, total, form);
			return result;
		}


		// cur: {string} expression generated so far.
		// pos: {int}    current visiting position of num.
		// cv:  {long}   cumulative value so far.
		// pv:  {long}   previous operand value.
		// op:  {char}   previous operator used.
		void dfs(std::vector<string>& res, const string& num, const int target, string cur, int pos, const long cv, const long pv, const char op) {
			if (pos == num.size() && cv == target) {
				res.push_back(cur);
			}
			else {
				for (int i = pos + 1; i <= num.size(); i++) {
					string t = num.substr(pos, i - pos);
					long now = stol(t);
					if (to_string(now).size() != t.size()) continue;
					dfs(res, num, target, cur + '+' + t, i, cv + now, now, '+');
					dfs(res, num, target, cur + '-' + t, i, cv - now, now, '-');
					dfs(res, num, target, cur + '*' + t, i, (op == '-') ? cv + pv - pv*now : ((op == '+') ? cv - pv + pv*now : pv*now), pv*now, op);
				}
			}
		}

		vector<string> addOperators1(string num, int target) {
			vector<string> res;
			if (num.empty()) return res;
			for (int i = 1; i <= num.size(); i++) {
				string s = num.substr(0, i);
				long cur = stol(s);
				if (to_string(cur).size() != s.size()) continue;
				dfs(res, num, target, s, i, cur, cur, '#');         // no operator defined.
			}

			return res;
		}

		static void main() {
			Solution282* test = new Solution282;
			vector<string> result;

			string num1("123");
			int target1 = 6;

			string num2("105");
			int target2 = 5;

			string num3("2147483648");
			int target3 = -2147483648;

			//result = test->addOperators(num1, target1);
			result = test->addOperators(num3, target3);
			delete test;
		}
	};
	/*282. Expression Add Operators end */


	/*272. Closest Binary Search Tree Value II (hard)
	Time = O(n)		Space = O(n)
	https://leetcode.com/problems/closest-binary-search-tree-value-ii/
	https://discuss.leetcode.com/topic/22940/ac-clean-java-solution-using-two-stacks/29
	http://codingmelon.com/2015/12/13/closest-binary-search-tree-value-ii-leetcode-272/
	*/
	class Solution272 {
	public:
		void findClosest(TreeNode* root, double target, int k, priority_queue<pair<double, int>>& diffs) {
			if (nullptr == root)
				return;

			if (diffs.size() == k) {
				double tmp = abs(target - root->val);
				if (tmp < diffs.top().first) {
					diffs.pop();
					diffs.push({ tmp, root->val });
				}

				findClosest(root->left, target, k, diffs);
				findClosest(root->right, target, k, diffs);
			}
			else {
				diffs.push({ abs(target - root->val), root->val });
				findClosest(root->left, target, k, diffs);
				findClosest(root->right, target, k, diffs);
			}
		}

		vector<int> closestKValues(TreeNode* root, double target, int k) {
			priority_queue<pair<double, int>> diffs;

			findClosest(root, target, k, diffs);

			vector<int> result;
			while (!diffs.empty()) {
				result.push_back(diffs.top().second);
				diffs.pop();
			}

			return result;
		}

		vector<int> preOrder(TreeNode* root) {
			vector<int> left;

			if (nullptr == root)
				return left;

			vector<int> right;
			left = preOrder(root->left);
			left.push_back(root->val);
			right = preOrder(root->right);
			left.insert(left.end(), right.begin(), right.end());
			return left;
		}

		vector<int> closestKValues1(TreeNode* root, double target, int k) {
			vector<int> pre_vec;
			vector<int> result;
			pre_vec = preOrder(root);

			int len = pre_vec.size();
			double diff = numeric_limits<double>::max();
			int start;
			for (int i = 0; i < len; ++i) {
				double tmp = abs(target - pre_vec[i]);
				if (tmp < diff) {
					start = i;
					diff = tmp;
				}
			}
			
			result.push_back(pre_vec[start]);
			int left = start - 1;
			int right = start + 1;
			while (--k > 0) {
				if (left >= 0 && right < len) {
					if (abs(target - pre_vec[left]) < abs(target - pre_vec[right]))
						result.insert(result.begin(), pre_vec[left--]);
					else
						result.push_back(pre_vec[right++]);
				}
				else if (left >= 0)
					result.insert(result.begin(), pre_vec[left--]);
				else
					result.push_back(pre_vec[right++]);
			}

			return result;
		}

		static void main() {
			Solution272* test = new Solution272;
			vector<int> result;

			TreeNode node43(43), node44(44), node10(10), node3(3), node12(12), node11(11), node21(21);
			TreeNode node1(1), node7(7), node0(0), node2(2), node5(5), node9(9);
			
			node43.left = &node10, node43.right = &node44;
			node10.left = &node3, node10.right = &node12;
			node3.left = &node1, node3.right = &node7;
			node12.left = &node11, node12.right = &node21;
			node1.left = &node0, node1.right = &node2;
			node7.left = &node5, node7.right = &node9;
			result = test->closestKValues(&node43, 4.857143, 1);
			delete test;
		}
	};
	/*272. Closest Binary Search Tree Value II end */


	/*269. Alien Dictionary (hard)
	Time = O()
	https://leetcode.com/problems/alien-dictionary/
	https://discuss.leetcode.com/topic/28308/java-ac-solution-using-bfs/9
	*/
	class Solution269 {
	public:
		string alienOrder(vector<string>& words) {
			string result;
			unordered_map<char, int> degrees;
			unordered_map<char, unordered_set<char>> nodes;

			for (auto word : words) {
				int idx = 0;
				while (idx < word.size() - 1) {
					if (0 == degrees.count(word[idx]))
						degrees[word[idx]] = 0;

					if (word[idx] != word[idx + 1])
						nodes[word[idx]].insert(word[idx + 1]);

					++idx;
				}
			}

			for (auto item : nodes)
				for (auto point : item.second)
					++degrees[point];

			queue<char> visit;
			for (auto item : degrees) {
				if (0 == item.second)
					visit.push(item.first);
			}

			while (!visit.empty()) {
				char tmp = visit.front();
				visit.pop();
				result += tmp;
				for (auto point : nodes[tmp]) {
					degrees[point] --;
					if (0 == degrees[point])
						visit.push(point);
				}
			}

			return result.size() == degrees.size() ? result : string("");
		}

		static void main() {
			Solution269* test = new Solution269;
			string result;
			vector<string> words1 = { "wrt","wrf","er","ett","rftt" };

			result = test->alienOrder(words1);
			delete test;
		}
	};
	/*269. Alien Dictionary end */


	/*239. Sliding Window Maximum (hard)
	Time = O(n)		Space = O(k)
	https://leetcode.com/problems/sliding-window-maximum/
	https://discuss.leetcode.com/topic/19055/java-o-n-solution-using-deque-with-explanation
	*/
	class Solution239 {
	public:
		vector<int> maxSlidingWindow(vector<int>& nums, int k) {
			vector<int> result;
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
	};
	/*239. Sliding Window Maximum end */


	/*224. Basic Calculator (hard)
	https://leetcode.com/problems/basic-calculator/
	https://discuss.leetcode.com/topic/22359/16-ms-solution-in-c-with-stacks/2
	*/
	class Solution224 {
	public:
		int calculate(string s) {
			string strtmp("(" + s + ")");
			stack<char> ops;
			stack<int> nums;

			int result = 0;
			int len = strtmp.size();

			for (int i = 0; i < len; ++i) {
				if (isdigit(strtmp[i])) {
					result = strtmp[i] - '0';

					while (i + 1 < len && isdigit(strtmp[i + 1]))
						result = result * 10 + strtmp[++i] - '0';
				}
				else if (isspace(strtmp[i]))
					continue;
				else if (strtmp[i] == '(') {
					ops.push('(');
					ops.push('+');
				}
				else {
					if (ops.top() == '*' || ops.top() == '/') {
						result = ops.top() == '/' ? nums.top() / result : nums.top() * result;
						ops.pop();
						nums.pop();
					}

					if (')' == strtmp[i]) {
						if ('-' == ops.top())
							result = -result;
						ops.pop();

						while (ops.top() != '(') {
							result += (ops.top() == '-') ? -nums.top() : nums.top();
							ops.pop();
							nums.pop();
						}

						ops.pop(); // remove '('
					}
					else { // +,-,*,/
						ops.push(strtmp[i]);
						nums.push(result);
						result = 0;
					}
				}
			}

			return result;
		}

		int calculate1(string s) {
			string str("(" + s + ")");
			int result = 0;
			stack<int> data;
			stack<int> oper;
			int flag = 1;
			int num = 0;

			for (int i = 0; i < str.size(); ++i) {
				if (' ' == str[i])
					continue;
				else if (isdigit(str[i]))
					num = 10 * num + (str[i] - '0');
				else {
					result += num * flag;
					num = 0;

					if ('-' == str[i])
						flag = -1;
					else if ('+' == str[i])
						flag = 1;
					else if ('(' == str[i]) {
						data.push(result);
						oper.push(flag);
						result = 0;
						flag = 1;
					}
					else {
						result = oper.top() * result + data.top();
						oper.pop();
						data.pop();
					}
				}
			}

			result += num * flag;
			return result;
		}

		static void main() {
			Solution224* test = new Solution224;
			int result;
			string s1(" 2-1 + 2 ");
			string s2("(1 + ((4 + 5 + 2) - 3)) + (6 + 8)");
			string s3("- 2 * 2 - 3 + 2 * 5");
			result = test->calculate(s3);

			delete test;
		}
	};
	/*224. Basic Calculator end */


	/*218. The Skyline Problem (hard)
	Time = O(n * log n)		Space = O(n)
	https://leetcode.com/problems/the-skyline-problem/
	https://briangordon.github.io/2014/08/the-skyline-problem.html
	https://discuss.leetcode.com/topic/38065/java-solution-using-priority-queue-and-sweepline
	http://www.geeksforgeeks.org/divide-and-conquer-set-7-the-skyline-problem/
	http://allenlipeng47.com/PersonalPage/index/view/172/nkey
	*/
	class Solution218 {
	public:
		vector<pair<int, int>> mergeSkyline(vector<pair<int, int>> &A, vector<pair<int, int>> &B) {
			vector<pair<int, int>> result;
			int h1 = 0, h2 = 0;
			int i = 0, j = 0;

			while (i < A.size() && j < B.size()) {
				int x = 0, h = 0;

				if (A[i].first < B[j].first) {
					x = A[i].first;
					h1 = A[i++].second;
				}
				else if (A[i].first > B[j].first) {
					x = B[j].first;
					h2 = B[j++].second;
				}
				else {
					x = B[j].first;
					h1 = A[i++].second;
					h2 = B[j++].second;
				}

				h = max(h1, h2);
				int len = result.size();
				//second check is to make sure the current high is not 
				//at the same level
				if (len == 0 || h != result[len - 1].second)
					result.push_back(make_pair(x, h));
			}

			while (i < A.size())
				result.push_back(A[i++]);

			while (j < B.size())
				result.push_back(B[j++]);

			return result;
		}

		vector<pair<int, int>> recurSkyline(vector<vector<int>>& buildings, int low, int high) {
			vector<pair<int, int>> result;
			if (low >= high) {
				result.push_back(make_pair(buildings[low][0], buildings[low][2]));
				result.push_back(make_pair(buildings[low][1], 0));
			}
			else {
				int mid = low + (high - low) / 2;

				vector<pair<int, int>> left = recurSkyline(buildings, low, mid);
				vector<pair<int, int>> right = recurSkyline(buildings, mid + 1, high);

				result = mergeSkyline(left, right);

			}

			return result;
		}

		vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
			vector<pair<int, int>> result;

			if (buildings.empty())
				return result;

			result = recurSkyline(buildings, 0, buildings.size() - 1);

			return result;
		}

		//time = O(n * log n)
		vector<pair<int, int>> getSkyline1(vector<vector<int>>& buildings) {
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
				if (h.second < 0)
					m.insert(-h.second);
				else
					m.erase(m.find(h.second));

				int cur = *m.rbegin();
				if (cur != prev) {
					skyline.push_back({ h.first, cur });
					prev = cur;
				}
			}
			return skyline;
		}

		static void main() {
			Solution218* test = new Solution218;
			vector<pair<int, int>> result;

			//vector<vector<int>> buildings1 = { { 2, 5, 4 },  { 1, 3, 3 } };
			//vector<vector<int>> buildings2 = { { 2, 5, 4 }, { 3, 4, 3 } };
			vector<vector<int>> buildings3 = { { 1, 3, 2 }, { 2, 4, 1 } };
			result = test->getSkyline(buildings3);
			delete test;
		}
	};
	/*218. The Skyline Problem end */


	/*214. Shortest Palindrome (hard)
	Time = O(n)		Space = O(n)
	https://leetcode.com/problems/shortest-palindrome/
	https://discuss.leetcode.com/topic/14526/c-8-ms-kmp-based-o-n-time-o-n-memory-solution
	*/
	class Solution214 {
	public:
		string shortestPalindrome(string s) {
			string rev_s = s;
			reverse(rev_s.begin(), rev_s.end());
			string l = s + "#" + rev_s;

			vector<int> p(l.size(), 0);
			for (int i = 1; i < l.size(); i++) {
				int j = p[i - 1];

				while (j > 0 && l[i] != l[j])
					j = p[j - 1];
				p[i] = (j += l[i] == l[j]);
			}

			return rev_s.substr(0, s.size() - p[l.size() - 1]) + s;
		}
	};
	/*214. Shortest Palindrome end */


	/*212. Word Search II (hard)
	Time = O(m * n * k)		Space = O(26 * k)
	k = average of each words length
	https://leetcode.com/problems/word-search-ii/
	https://discuss.leetcode.com/topic/33246/java-15ms-easiest-solution-100-00/2
	*/
	class Solution212 {
	public:
		class Trie {
		public:
			vector<Trie*> data;
			int idx;
			bool isword;
			Trie() {
				data.assign(26, nullptr);
				idx = -1;
				isword = false;
			}
		};

		void insertWord(string& str, int idx, Trie *parent) {
			Trie * cur = parent;
			for (auto item : str) {
				int i = item - 'a';
				if (nullptr == cur->data[i])
					cur->data[i] = new Trie;

				cur = cur->data[i];
			}

			cur->idx = idx;
			cur->isword = true;
		}

		void buildTrie(vector<string>& words, Trie *parent) {
			for (int i = 0; i < words.size(); ++i)
				insertWord(words[i], i, parent);
		}

		void checkWord(int i, int j, vector<string>& board, vector<string>& words, Trie *parent) {
			if (i >= board.size() || i < 0 || j >= board[0].size() || j < 0 || 'X' == board[i][j])
				return;

			char tmp = board[i][j];
			int k = tmp - 'a';
			if (nullptr != parent->data[k]) {
				board[i][j] = 'X';

				if (parent->data[k]->isword) {
					parent->data[k]->isword = false;
					result.push_back(words[parent->data[k]->idx]);
				}

				checkWord(i + 1, j, board, words, parent->data[k]);
				checkWord(i - 1, j, board, words, parent->data[k]);
				checkWord(i, j + 1, board, words, parent->data[k]);
				checkWord(i, j - 1, board, words, parent->data[k]);

				board[i][j] = tmp;
			}
		}

		vector<string> result;
		vector<string> findWords(vector<string>& board, vector<string>& words) {
			if (board.empty() || board[0].empty() || words.empty())
				return result;

			Trie root;

			buildTrie(words, &root);
			for (int i = 0; i < board.size(); ++i)
			for (int j = 0; j < board[0].size(); ++j)
				checkWord(i, j, board, words, &root);

			return result;
		}

		static void main() {
			Solution212* test = new Solution212;
			vector<string> result;

			vector<string> board1 = { "oaan", "etae", "ihkr", "iflv" };
			vector<string> words1 = { "oath", "pea", "eat", "rain" };
			result = test->findWords(board1, words1);
			delete test;
		}
	};
	/*212. Word Search II end */


	/*159. Longest Substring with At Most Two Distinct Characters (hard)
	https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/
	https://discuss.leetcode.com/topic/7399/share-my-c-solution
	*/
	class Solution159 {
	public:
		int lengthOfLongestSubstringTwoDistinct(string s) {
			if (s.empty())
				return 0;

			vector<int> hash(256, 0);
			int count = 0, result = 1, start = 0;

			for (int i = 0; i < s.size(); ++i) {
				hash[s[i]] ++;

				if (1 == hash[s[i]]) {
					++count;

					while (count > 2) {
						--hash[s[start]];
						if (0 == hash[s[start]])
							--count;
						++start;
					}
				}

				result = max(result, i - start + 1);
			}

			return result;
		}

		int lengthOfLongestSubstringTwoDistinct1(string s) {
			int result = 0;
			int count = 0;
			int curtotal = 0;
			unordered_set<char> hash;

			for (int i = 0; i < s.size(); ++i) {
				if (count < 2 || hash.count(s[i])) {
					++curtotal;
					if (!hash.count(s[i]))
						++count;

					hash.insert(s[i]);
					result = max(result, curtotal);

				}
				else {
					result = max(result, curtotal);
					curtotal = 2;
					int k = i - 2;
					while (s[k] == s[i - 1]) {
						++curtotal;
						--k;
					}

					hash.erase(s[k]);
					hash.insert(s[i]);
				}
			}

			return result;
		}
	};
	/*159. Longest Substring with At Most Two Distinct Characters end */


	/*158. Read N Characters Given Read4 II - Call multiple times (hard)
	https://leetcode.com/problems/read-n-characters-given-read4-ii-call-multiple-times/
	https://discuss.leetcode.com/topic/7094/a-simple-java-code/2
	https://discuss.leetcode.com/topic/32780/simple-short-java-c/2
	*/
	class Solution158 {
	public:
		/**
		* @param buf Destination buffer
		* @param n   Maximum number of characters to read
		* @return    The number of characters read
		*/
		int count;
		int index;
		char data[4];

		Solution158() {
			count = 0;
			index = 0;
			//buf.resize(4);
		}

		int read(char *buf, int n) {
			int total = 0;

			while (total < n) {
				if (0 == index)
					;// count = read4(data);

				if (0 == count)
					break;

				while (total < n && index < count)
					buf[total++] = data[index++];

				if (index >= count)
					index = 0;
			}

			return total;
		}
	};
	/*158. Read N Characters Given Read4 II - Call multiple times end */


	/*146. LRU Cache (hard)
	https://leetcode.com/problems/lru-cache/
	https://discuss.leetcode.com/topic/6812/c-11-code-74ms-hash-table-list
	https://discuss.leetcode.com/topic/6613/java-hashtable-double-linked-list-with-a-touch-of-pseudo-nodes
	*/
	class LRUCache146 {
	public:
		class DLinkNode {
		public:
			DLinkNode() : key(-1), val(-1), pre(nullptr), next(nullptr)
			{}

			DLinkNode(int inkey, int inval) : key(inkey), val(inval), pre(nullptr), next(nullptr)
			{}

			int key;
			int val;
			DLinkNode* pre;
			DLinkNode* next;			
		};

		unordered_map<int, DLinkNode*> usedata;
		DLinkNode head;
		DLinkNode tail;

		void addNode(DLinkNode* newnode) {
			newnode->pre = &head;
			newnode->next = head.next;

			head.next->pre = newnode;
			head.next = newnode;
		}

		void removeNode(DLinkNode* newnode) {
			DLinkNode* tmpre = newnode->pre;
			DLinkNode* tmpnext = newnode->next;

			tmpre->next = tmpnext;
			tmpnext->pre = tmpre;
		}

		void movetoHead(DLinkNode* newnode) {
			removeNode(newnode);
			addNode(newnode);
		}

		DLinkNode* popTail() {
			DLinkNode* node = tail.pre;
			node->pre->next = &tail;
			tail.pre = node->pre;

			return node;
		}

		int get(int key) {
			int result = -1;
			
			if (usedata.count(key)) {
				result = usedata[key]->val;
				movetoHead(usedata[key]);
			}

			return result;
		}

		void set(int key, int value) {
			if (usedata.count(key)) {
				usedata[key]->val = value;
				movetoHead(usedata[key]);
			}
			else {
				DLinkNode* node = nullptr;
				if (usedata.size() >= total) {
					node = popTail();
					usedata.erase(node->key);
					node->key = key;
					node->val = value;
				}
				else
					node = new DLinkNode(key, value);

				addNode(node);
				usedata[key] = node;
			}
		}

		LRUCache146(int capacity) {
			total = capacity;
			head.next = &tail;
			tail.pre = &head;
		}

		int get1(int key) {
			int result = -1;
			auto it = hash.find(key);
			if (it != hash.end()) {
				data.erase(it->second.second);
				result = it->second.first;
				data.push_front(key);
				it->second.second = data.begin();
			}

			return result;
		}

		void set1(int key, int value) {
			if (hash.count(key)) {
				data.erase(hash[key].second);
				data.push_front(key);
				hash[key] = { value, data.begin() };
			}
			else {
				if (data.size() >= total) {
					hash.erase(data.back());
					data.pop_back();
				}

				data.push_front(key);
				hash[key] = { value, data.begin() };
			}			
		}
		
		static void main() {
			LRUCache146* test = new LRUCache146(1);
			test->set(2, 1);
			test->get(2);
			delete test;
		}
		int total;
		//key, <value, pos>
		unordered_map<int, pair<int, list<int>::iterator>> hash;
		list<int> data;
	};
	/*146. LRU Cache end */


	/*140. Word Break II (hard)
	https://leetcode.com/problems/word-break-ii/
	https://discuss.leetcode.com/topic/12997/11ms-c-solution-concise
	*/
	class Solution140 {
	public:
		unordered_map<string, vector<string>> m;
		vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
			vector<string> result;

			if (m.count(s))
				return m[s];

			if (wordDict.count(s))
				result.push_back(s);

			for (int i = 1; i < s.size(); ++i) {
				string cur = s.substr(0, i);
				
				if (wordDict.count(cur)) {
					string word = s.substr(i);

					vector<string> after = wordBreak(word, wordDict);
					for (auto item : after)
						result.push_back(cur.substr(0).append(" " + item));
				}
			}

			m[s] = result;
			return result;
		}

		
		vector<string> wordBreak1(string s, unordered_set<string>& wordDict) {
			vector<string> result;
			if (s.empty())
				return result;

			if (m.count(s))
				return m[s];

			int len = s.size();
			for (auto item : wordDict) {
				int itemlen = item.size();
				
				vector<string> bresult;
				if (len >= itemlen && s.substr(0, itemlen) == item) {
					if (len == itemlen) {
						result.push_back(item);
						continue;
					}

					bresult = wordBreak1(s.substr(itemlen), wordDict);
				}

				for (auto subitem : bresult)
					result.push_back(s.substr(0, itemlen).append(" " + subitem));
			}

			m[s] = result;
			return result;
		}

		static void main() {
			Solution140* test = new Solution140;
			vector<string> result;

			string s1("catsanddog");
			unordered_set<string> wordDict1 = { "cat","cats","and","sand","dog" };

			result = test->wordBreak(s1, wordDict1);
			delete test;
		}
	};
	/*140. Word Break II end */


	/*128. Longest Consecutive Sequence (hard)
	https://leetcode.com/problems/longest-consecutive-sequence/
	https://discuss.leetcode.com/topic/6148/my-really-simple-java-o-n-solution-accepted
	*/
	class Solution128 {
	public:
		int longestConsecutive(vector<int>& nums) {
			int result = 0;
			int left, right;
			unordered_map<int, int> data;

			for (auto item : nums) {
				if (0 == data.count(item)) {
					left = data.count(item - 1) ? data[item - 1] : 0;
					right = data.count(item + 1) ? data[item + 1] : 0;

					int sum = left + right + 1;
					data[item] = sum;
					data[item - left] = sum;
					data[item + right] = sum;
					result = max(result, sum);
				}
			}

			return result;
		}
	};
	/*128. Longest Consecutive Sequence end */


	/*57. Insert Interval (hard)
	https://leetcode.com/problems/insert-interval/
	https://discuss.leetcode.com/topic/16988/7-lines-3-easy-solutions
	*/
	class Solution57 {
	public:
		vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
			vector<Interval> result;
			
			Interval next = newInterval;
			int i;
			for (i = 0; i < intervals.size() && intervals[i].end < next.start; ++i)
				result.push_back(intervals[i]);

			for (; i < intervals.size() && intervals[i].start <= next.end; ++i) {
				next.start = min(intervals[i].start, next.start);
				next.end = max(next.end, intervals[i].end);
			}

			result.push_back(next);
			for (; i < intervals.size(); ++i)
				result.push_back(intervals[i]);
			return result;
		}

		static void main() {
			Solution57* test = new Solution57;
			vector<Interval> result;
			vector<Interval> intervals1 = { {1, 5} };
			Interval newInterval1 = { 6, 7 };

			result = test->insert(intervals1, newInterval1);
			delete test;
		}
	};
	/*57. Insert Interval end */


	/*56. Merge Intervals (hard)
	https://leetcode.com/problems/merge-intervals/
	https://discuss.leetcode.com/topic/20263/c-10-line-solution-easing-understanding
	*/
	class Solution56 {
	public:
		vector<Interval> merge(vector<Interval>& intervals) {
			vector<Interval> result;
			if (intervals.empty())
				return result;

			sort(intervals.begin(), intervals.end(), [](Interval &a, Interval &b) {return a.start < b.start; });

			result.push_back(intervals[0]);

			for (int i = 1; i < intervals.size(); ++i) {
				if (intervals[i].start > result.rbegin()->end)
					result.push_back(intervals[i]);
				else
					result.rbegin()->end = max(result.rbegin()->end, intervals[i].end);
			}

			return result;

		}
	};
	/*56. Merge Intervals end */


	/*44. Wildcard Matching (hard)
	https://leetcode.com/problems/wildcard-matching/
	https://discuss.leetcode.com/topic/17901/accepted-c-dp-solution-with-a-trick
	*/
	class Solution44 {
	public:
		bool isMatch(string s, string p) {
			if (p.empty())
				return s.empty();

			int m = s.size();
			int n = p.size();
			vector<bool> dp(m + 1, false);
			bool upleft;

			dp[0] = true;

			for (int j = 1; j <= n; ++j) {
				upleft = dp[0];
				dp[0] = dp[0] && ('*' == p[j - 1]);
				
				for (int i = 1; i <= m; ++i) {
					bool tmp = dp[i];
					if ('*' != p[j - 1])
						dp[i] = upleft && (s[i - 1] == p[j - 1] || '?' == p[j - 1]);
					else
						dp[i] = dp[i] || dp[i - 1];
					
					upleft = tmp;
				}
			}

			return dp[m];
		}

		bool isMatch1(string s, string p) {
			if (p.empty())
				return s.empty();

			int m = s.size();
			int n = p.size();
			vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

			dp[0][0] = true;
			for (int j = 1; j <= n; ++j)
				dp[0][j] = dp[0][j - 1] && ('*' == p[j - 1]);

			for (int i = 1; i <= m; ++i) {
				for (int j = 1; j <= n; ++j) {
					if ('*' != p[j - 1])
						dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '?' == p[j - 1]);
					else
						dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
				}
			}

			return dp[m][n];
		}

		static void main() {
			Solution44* test = new Solution44;
			bool result;
			string s1("aa"), p1("*");

			result = test->isMatch(s1, p1);
			delete test;
		}
	};
	/*44. Wildcard Matching end */


	/*42. Trapping Rain Water (hard)
	https://leetcode.com/problems/trapping-rain-water/
	https://discuss.leetcode.com/topic/5125/sharing-my-simple-c-code-o-n-time-o-1-space
	https://discuss.leetcode.com/topic/4939/a-stack-based-solution-for-reference-inspired-by-histogram
	*/
	class Solution42 {
	public:
		int trap(vector<int>& height) {
			int left = 0, right = height.size() - 1;
			int result = 0, maxleft = 0, maxright = 0;

			while (left <= right) {
				if (height[left] < height[right]) {
					if (height[left] > maxleft)
						maxleft = height[left];
					else
						result += maxleft - height[left];
					++left;
				}
				else {
					if (height[right] > maxright)
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


	/*23. Merge k Sorted Lists (hard)
	Time = O(k*n*logk)		Space = O(1)
	https://leetcode.com/problems/merge-k-sorted-lists/
	https://discuss.leetcode.com/topic/6882/sharing-my-straightforward-c-solution-without-data-structure-other-than-vector
	*/
	class Solution23 {
	public:
		ListNode *mergeTwoList(ListNode * node1, ListNode * node2) {
			if (nullptr == node1)
				return node2;

			if (nullptr == node2)
				return node1;

			ListNode * result;
			if (node1->val > node2->val) {
				node1->next = mergeTwoList(node1->next, node2);
				return node1;
			}
			else {
				node2->next = mergeTwoList(node1, node2->next);
				return node2;
			}
		}

		ListNode *mergeKLists1(vector<ListNode *> &lists) {
			if (lists.empty())
				return nullptr;

			while (lists.size() > 1) {
				lists.push_back(mergeTwoList(lists[0], lists[1]));
				lists.erase(lists.begin());
				lists.erase(lists.begin());
			}

			return lists.front();
		}
		
		class comp {
		public:
			bool operator ()(ListNode *a, ListNode * b) {
				return a->val > b->val;
			}
		};

		class comp1 {
		public:
			bool operator ()(list<pair<int, int>>::iterator a, list<pair<int, int>>::iterator b) {
				return a->first < b->first;
			}
		};
		ListNode *mergeKLists(vector<ListNode *> &lists) {
			if (lists.empty())
				return nullptr;

			ListNode dummy(0);
			ListNode* curr = &dummy;


			//priority_queue<vector<pair<int, int>>::iterator, vector<vector<pair<int, int>>::iterator>, comp1> data1;
			priority_queue<list<pair<int, int>>::iterator, vector<list<pair<int, int>>::iterator>, comp1> feeds;

			//list<pair<int, int>>::iterator tmp = feeds.top();

			
			priority_queue<ListNode *, vector<ListNode *>, comp> data;

			for (auto item : lists) {
				if (nullptr != item)
					data.push(item);
			}

			while (!data.empty()) {
				curr->next = data.top();
				data.pop();
				if (curr->next->next)
					data.push(curr->next->next);

				curr = curr->next;
			}

			return dummy.next;
		}
	};
	/*23. Merge k Sorted Lists end */


	/*10. Regular Expression Matching (hard)
	https://leetcode.com/problems/regular-expression-matching/
	https://discuss.leetcode.com/topic/6183/my-concise-recursive-and-dp-solutions-with-full-explanation-in-c
	*/
	class Solution10 {
	public:
		bool isMatch(string s, string p) {
			if (p.empty())
				return s.empty();

			if (p.size() > 1 && '*' == p[1])
				return isMatch(s, p.substr(2)) || !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p);
			else
				return !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p.substr(1));
		}

		bool isMatch1(string s, string p) {
			int m = s.size();
			int n = p.size();
			vector<int> dp(n + 1, false);

			dp[0] = true;
			// j-3 (dp[j-2]), j-2, j-1(*) (dp[j])
			for (int j = 1; j <= n; ++j)
				dp[j] = j > 1 && ('*' == p[j - 1]) && dp[j - 2];

			bool leftup;

			for (int i = 0; i < m; ++i) {
				leftup = dp[0];
				dp[0] = 0;
				for (int j = 0; j < n; ++j) {
					bool up = dp[j + 1];
					if ('*' != p[j])
						dp[j + 1] = (s[i] == p[j] || '.' == p[j]) && leftup;
					else
						dp[j + 1] = dp[j - 1] || ((s[i] == p[j - 1] || '.' == p[j - 1])) && dp[j + 1];

					leftup = up;
				}
			}

			return dp[n];
		}
	};
	/*10. Regular Expression Matchingend */


	/*4. Median of Two Sorted Arrays (hard)
	https://leetcode.com/problems/median-of-two-sorted-arrays/
	https://discuss.leetcode.com/topic/4996/share-my-o-log-min-m-n-solution-with-explanation
	*/
	class Solution4 {
	public:
		int getkth(vector<int>& nums1, int len1, vector<int>& nums2, int len2, int k) {
			if (len1 > len2)
				return getkth(nums2, len2, nums1, len1, k);

			if (0 == len1)
				return nums2[k - 1];

			if (1 == k)
				return min(nums1[0], nums2[0]);

			int i = min(len1, k / 2);
			int j = min(len2, k / 2);

			//at lease j number in nums2
			if (nums1[i - 1] > nums2[j - 1]) {
				vector<int> tmp(nums2.begin() + j, nums2.end());
				return getkth(nums1, len1, tmp, tmp.size(),  k - j);
			}
			else {
				vector<int> tmp(nums1.begin() + i, nums1.end());
				return getkth(tmp, tmp.size(), nums2, len2, k - i);
			}
		}

		double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
			int len1 = nums1.size();
			int len2 = nums2.size();

			int m = (len1 + len2 + 1) >> 1;
			int n = (len1 + len2 + 2) >> 1;

			if (m == n)
				return getkth(nums1, nums1.size(), nums2, nums2.size(), m);
			else
				return (getkth(nums1, len1, nums2, len2, m) + getkth(nums1, len1, nums2, len2, n)) / 2.0;
		}
	};
	/*4. Median of Two Sorted Arrays end */


	/*399. Evaluate Division (medium)
	Time = Big-Theta(|V| + |E|)		Space = O(|V|) in the worst case
	https://leetcode.com/problems/evaluate-division/
	https://discuss.leetcode.com/topic/58312/c-0ms-hash-dfs-solution
	*/
	class Solution399 {
	public:
		vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
			unordered_map<string, unordered_map<string, double>> hash;
			vector<double> res;

			for (int i = 0; i < values.size(); ++i) {
				hash[equations[i].first].insert({ equations[i].second, values [i] });

				if (0 != values[i])
					hash[equations[i].second].insert({ equations[i].first, 1 / values[i] });
			}

			for (auto item : queries) {
				unordered_set<string> s;
				double tmp = checkVal(item.first, item.second, hash, s);
				if (0 == tmp)
					res.push_back(-1);
				else
					res.push_back(tmp);
			}

			return res;
		}

		double checkVal(string up, string down,
			unordered_map<string, unordered_map<string, double>> &m,
			unordered_set<string> &s) {
			if (m[up].count(down))
				return m[up][down];

			for (auto item : m[up]) {
				if (0 == s.count(item.first)) {
					s.insert(item.first);
					double tmp = checkVal(item.first, down, m, s);
					if (0 != tmp)
						return item.second * tmp;
				}
			}

			return 0;
		}
	};
	/*399. Evaluate Division end */


	/*394. Decode String (medium)
	https://leetcode.com/problems/decode-string/
	https://discuss.leetcode.com/topic/57159/simple-java-solution-using-stack
	*/
	class Solution394 {
	public:
		string decodeString1(string s) {
			stack<string> data;
			data.push("");

			string cur("");
			for (auto c : s) {
				if ('[' == c) {
					data.push(cur);
					cur = "";
				}
				else if (']' == c) {
					while (!isdigit(data.top()[0])) {
						cur = data.top() + cur;
						data.pop();
					}

					int times = stoi(data.top());
					data.pop();
					string tmp("");
					while (times-- > 0)
						tmp.append(cur);

					data.push(tmp);
					cur = "";
				}
				else if (isdigit(c))
					cur += c;
				else {
					cur = c;
					data.push(cur);
					cur = "";
				}
			}

			while (!data.empty()) {
				cur = data.top() + cur;
				data.pop();
			}

			return cur;
		}

		string decodeString(string s) {
			stack<string> data;
			data.push("");

			int i = 0;
			int len = s.size();
			string cur("");
			while (i < len) {
				if ('[' == s[i]) {
					data.push(cur);
					cur = "";
				}
				else if (']' == s[i]) {
					while (!isdigit(data.top()[0])) {
						cur = data.top() + cur;
						data.pop();
					}
					
					int times = stoi(data.top());
					data.pop();
					string tmp("");
					while (times-- > 0)
						tmp.append(cur);

					data.push(tmp);
					cur = "";
				}
				else if (isdigit(s[i])) {
					if (!cur.empty())
						data.push(cur);
					cur = s[i];
					while ('[' != s[i + 1])
						cur += s[++i];
				}
				else
					cur += s[i];

				++i;
			}

			while (!data.empty()) {
				cur = data.top() + cur;
				data.pop();
			}

			return cur;
		}
	};
	/*394. Decode String end */


	/*393. UTF-8 Validation (medium)
	https://leetcode.com/problems/utf-8-validation/
	https://discuss.leetcode.com/topic/57195/concise-c-implementation
	*/
	class Solution393 {
	public:
		bool validUtf8(vector<int>& data) {
			int count = 0;
			for (auto item : data) {
				if (0 == count) {
					if (item >> 5 == 0xC0)//if (item >> 5 == 0b110)
						count = 1;
					else if (item >> 4 == 0xE0)//else if (item >> 4 == 0b1110)
						count = 2;
					else if (item >> 3 == 0xF0)//else if (item >> 3 == 0b11110)
						count = 3;
					else if (item >> 7)	//first bit is 1
						return false;
				}
				else {
					if (item >> 6 != 0x80)//if (item >> 6 != 0b10)
						return false;

					--count;
				}
			}

			return count == 0;
		}
	};
	/*393. UTF-8 Validation end */


	/*388. Longest Absolute File Path (medium)
	https://leetcode.com/problems/longest-absolute-file-path/
	https://discuss.leetcode.com/topic/55097/simple-python-solution/12
	*/
	class Solution388 {
	public:
		vector<string> split(const string &text, char sep) {
			vector<string> tokens;
			size_t start = 0, end = 0;

			while ((end = text.find(sep, start)) != string::npos) {
				while (' ' == text[start])
					++start;

				string temp = text.substr(start, end - start);
				tokens.push_back(temp);
				start = end + 1;
			}

			string temp = text.substr(start);
			tokens.push_back(temp);

			return tokens;
		}

		int lengthLongestPath1(string input) {
			vector<string> items;

			items = split(input, '\n');
			stack<string> path;

			int len = 0, result = 0;
			for (auto item : items) {
				int idx = 0;
				while ('\t' == item[idx])
					++idx;

				if (string::npos != item.find('.'))
					result = max(result, len + (int)item.size() - idx + (int)path.size());
				else {
					if (path.empty() || 0 == idx) {
						while (!path.empty())
							path.pop();
						len = 0;
						path.push(item);
						len += item.size() - idx;
					}
					else {
						int level2 = 0;
						string tmp = path.top();
						while ('\t' == tmp[level2])
							++level2;

						while (level2 >= idx) {
							path.pop();
							len -= tmp.size() - level2;
							tmp = path.top();
							level2 = 0;
							while ('\t' == tmp[level2])
								++level2;
						}

						path.push(item);
						len += item.size() - idx;
					}
				}
			}

			return result;
		}

		int lengthLongestPath(string input) {
			int maxlen = 0;
			vector<int>pathlen(input.length() + 1, 0);
			vector<string> items;

			items = split(input, '\n');
			for (auto line : items) {
				int idx = 0;
				while ('\t' == line[idx])
					++idx;

				int namelen = line.length() - idx;
				if (string::npos != line.find('.'))
					maxlen = max(maxlen, pathlen[idx] + namelen);
				else
					pathlen[idx + 1] = pathlen[idx] + namelen + 1;
			}

			return maxlen;
		}

		static void main() {
			Solution388* test = new Solution388;
			int result;
			string input1("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext");
			string input2("a\n\tb.txt\na2\n\tb2.txt");
			result = test->lengthLongestPath(input1);
			delete test;
		}
	};
	/*388. Longest Absolute File Path end */


	/*382. Linked List Random Node (medium)
	https://leetcode.com/problems/linked-list-random-node/
	https://discuss.leetcode.com/topic/53753/brief-explanation-for-reservoir-sampling
	https://en.wikipedia.org/wiki/Reservoir_sampling
	*/
	class Solution382 {
	public:
		/** @param head The linked list's head.
		Note that the head is guaranteed to be not null, so it contains at least one node. */
		Solution382(ListNode* head) {
			nodes = head;
		}

		/** Returns a random node's value. */
		int getRandom() {
			int val = nodes->val;
			int i = 2;
			ListNode* cur = nodes->next;

			while (cur) {
				int j = rand() % i;

				if (0 == j)
					val = cur->val;

				++i;
				cur = cur->next;
			}

			return val;
		}

		ListNode* nodes;
	};
	/*382. Linked List Random Node end */


	/*379. Design Phone Directory (medium)
	https://leetcode.com/problems/design-phone-directory/
	https://discuss.leetcode.com/topic/53098/c-two-array-solution
	*/
	class PhoneDirectory379 {
	public:
		/** Initialize your data structure here
		@param maxNumbers - The maximum numbers that can be stored in the phone directory. */
		PhoneDirectory379(int maxNumbers) {
			total = maxNumbers;
			used.resize(total);
			pool.resize(total, true);
			index = 0;
			for (int i = 0; i < total; ++i) {
				used[i] = i;
			}
		}

		/** Provide a number which is not assigned to anyone.
		@return - Return an available number. Return -1 if none is available. */
		int get() {
			int result = -1;
			if (index < total) {
				result = used[index++];
				pool[result] = false;
			}

			return result;
		}

		/** Check if a number is available or not. */
		bool check(int number) {
			if (number > total || number < 0)
				return false;

			return pool[number];
		}

		/** Recycle or release a number. */
		void release(int number) {
			if (number > total || number < 0 || pool[number])
				return;

			used[--index] = number;
			pool[number] = true;
		}

		static void main() {
			PhoneDirectory379* test = new PhoneDirectory379(4);
			cout << test->get() << endl;
			cout << test->get() << endl;
			cout << test->get() << endl;
			cout << test->get() << endl;
			test->release(1);
			cout << test->get() << endl;
			delete test;
		}

		int total;
		int index;
		vector<int> used;
		vector<bool> pool;
	};

	/**
	* Your PhoneDirectory object will be instantiated and called as such:
	* PhoneDirectory obj = new PhoneDirectory(maxNumbers);
	* int param_1 = obj.get();
	* bool param_2 = obj.check(number);
	* obj.release(number);
	*/
	/*379. Design Phone Directory end */


	/*378. Kth Smallest Element in a Sorted Matrix (medium)
	Time = O(k)		Space = O(k)
	https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
	https://discuss.leetcode.com/topic/52948/share-my-thoughts-and-clean-java-code
	*/
	class Solution378 {
	public:
		struct item {
			int val;
			int row;
			int col;
			item(int itemval, int itemr, int itemc) : val(itemval), row(itemr), col(itemc)
			{}
		};
		
		class cmp {
		public:
			bool operator()(item& a, item& b) {
				return a.val > b.val;
			}
		};
		
		int kthSmallest(vector<vector<int>>& matrix, int k) {
			int n = matrix.size();
			priority_queue <item, vector<item>, cmp> data;

			//time = Big-Theta n * n * log n
			for (int i = 0; i < n; ++i)
				data.push(item(matrix[0][i], 0, i));

			//time = around k * log n
			//top one is always minimal, pop k - 1 will get the kth
			while (--k) {
				item head = data.top();
				data.pop();
				if (n - 1 == head.row)
					continue;
				++head.row;
				data.push(item(matrix[head.row][head.col], head.row, head.col));
			}

			return data.top().val;
		}

		static void main() {
			Solution378* test = new Solution378;
			vector<vector<int>> matrix1 = { { 1,  5,  9}, {10, 11, 13}, {12, 13, 15 } };
			vector<vector<int>> matrix2 = { { 1,  2 },{ 3, 3 } };

			test->kthSmallest(matrix2, 2);
			delete test;
		}
	};
	/*378. Kth Smallest Element in a Sorted Matrix end */


	/*377. Combination Sum IV (medium)
	https://leetcode.com/problems/combination-sum-iv/
	https://discuss.leetcode.com/topic/52302/1ms-java-dp-solution-with-detailed-explanation
	https://discuss.leetcode.com/topic/52186/my-3ms-java-dp-solution
	*/
	class Solution377 {
	public:
		int combination(vector<int>& nums, int target) {
			if (0 == target)
				return 1;

			int count = 0;
			for (auto item : nums) {
				if (item > target)
					break;

				count += combination(nums, target - item);
			}

			return count;
		}

		int combinationSum41(vector<int>& nums, int target) {
			if (nums.empty())
				return 0;

			sort(nums.begin(), nums.end());
			return combination(nums, target);
		}

		int combinationSum4(vector<int>& nums, int target) {
			if (nums.empty())
				return 0;

			vector<int> dp(target + 1, 0);

			//target 0 has only 1 empty combination
			dp[0] = 1;
			for (int i = 1; i < dp.size(); ++i) {
				for (auto it : nums) {
					if (i >= it)
						dp[i] += dp[i - it];
				}
			}

			return dp[target];
		}

		static void main() {
			Solution377* test = new Solution377;
			int result;
			vector<int> nums1 = { 1, 2, 4 };
			int target1 = 32;

			result = test->combinationSum4(nums1, target1);
			delete test;
		}
	};
	/*377. Combination Sum IV end */


	/*375. Guess Number Higher or Lower II (medium)
	Time = O(n ^ 3)		Space = O(n * n)
	https://leetcode.com/problems/guess-number-higher-or-lower-ii/
	https://discuss.leetcode.com/topic/52100/dp-java-o-n-3-solution-with-explanation-15ms-17-lines
	https://discuss.leetcode.com/topic/52627/recursion-memization
	https://discuss.leetcode.com/topic/51984/java-o-n-2-dp-solution-with-clear-explanation
	*/
	class Solution375 {
	public:
		int dp(vector<vector<int>>&data, int s, int e) {
			if (s >= e)
				return 0;

			if (0 != data[s][e])
				return data[s][e];

			//query for every item's lost and get the minimal one
			//for every item, use bigger lost of left side and right
			//will gurantee a win for this lost with that bigger value
			int result = numeric_limits<int>::max();
			for (int k = s; k <= e; ++k) {
				int tmp = k + max(dp(data, s, k - 1), dp(data, k + 1, e));
				result = min(result, tmp);
			}

			data[s][e] = result;
			return result;
		}

		int getMoneyAmount(int n) {
			if (n < 2)
				return n;

			vector<vector<int>> data(n + 1, vector<int>(n + 1, 0));

			return dp(data, 1, n);
		}
	};
	/*375. Guess Number Higher or Lower II end */


	/*373. Find K Pairs with Smallest Sums (medium)
	https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
	https://discuss.leetcode.com/topic/50450/slow-1-liner-to-fast-solutions
	*/
	class Solution373 {
	public:
		struct node {
			int idx;
			int num1;
			int num2;

			node(int id, int a, int b) : idx(id), num1(a), num2(b)
			{}
		};

		class comp {
		public:
			bool operator ()(node&a, node& b){
				return a.num1 + a.num2 < b.num1 + b.num2;
			}
		};

		vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
			vector<pair<int, int>> result;

			if (0 == k || nums1.empty() || nums2.empty())
				return result;

			//auto cmp = [](pair<int, int> a, pair<int, int> b) { return a.first + a.second < b.first + b.second; };
			//priority_queue <pair<int, int>, vector<pair<int, int>>, decltype(cmp)> data;

			priority_queue<node, vector<node>, comp> data;
			for (int i = 0; i < nums1.size() && i < k; ++i) {
				node cur(0, nums1[i], nums2[0]);
				data.push(cur);
			}

			//top is always the smallest one
			for (int i = 0; i < k && !data.empty(); ++i) {
				node cur = data.top();
				result.push_back({ cur.num1, cur.num2 });
				data.pop();

				if (cur.idx < nums2.size() - 1) {
					int next = cur.idx + 1;
					data.push(node(next, cur.num1, nums2[next]));
				}
			}

			return result;
		}

		vector<pair<int, int>> kSmallestPairs1(vector<int>& nums1, vector<int>& nums2, int k) {
			multimap<int, pair<int, int>> data;
			vector<pair<int, int>> result;

			for (int i = 0; i < nums1.size() && i < k; ++i)
			for (int j = 0; j < nums2.size() && j < k; ++j) {
				if (data.size() >= k && nums1[i] + nums2[j] >= data.rbegin()->first)
					break;
				data.insert({ nums1[i] + nums2[j], make_pair(nums1[i] , nums2[j]) });
			}

			int num = 0;

			for (auto item : data) {
				result.push_back(item.second);
				++num;

				if (num >= k)
					break;
			}

			return result;
		}
	};
	/*373. Find K Pairs with Smallest Sums end */


	/*370. Range Addition (medium)
	https://leetcode.com/problems/range-addition/
	https://discuss.leetcode.com/topic/49691/java-o-k-n-time-complexity-solution
	*/
	class Solution370 {
	public:
		vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
			vector<int> result(length, 0);

			for (auto item : updates) {
				result[item[0]] += item[2];

				if (item[1] < length - 1)
					result[item[1] + 1] += -item[2];
			}

			int cur = 0;
			for (int i = 0; i < length; ++i) {
				cur += result[i];
				result[i] = cur;
			}

			return result;
		}
	};
	/*370. Range Addition end */


	/*369. Plus One Linked List (medium)
	https://leetcode.com/problems/plus-one-linked-list/
	https://discuss.leetcode.com/topic/49556/iterative-two-pointers-with-dummy-node-java-o-n-time-o-1-space
	*/
	class Solution369 {
	public:
		ListNode* plusOne1(ListNode* head) {
			stack<ListNode*> data;
			ListNode* cur = head;

			while (cur) {
				data.push(cur);
				cur = cur->next;
			}

			int flag = 1;
			while (!data.empty()) {
				cur = data.top();
				data.pop();
				cur->val += flag;
				if (cur->val > 9) {
					cur->val = 0;
					flag = 1;
				}
				else 
					flag = 0;
			}

			cur = head;
			if (flag) {
				cur = new ListNode(1);
				cur->next = head;
			}

			return cur;
		}

		ListNode* plusOne(ListNode* head) {
			ListNode dummy(0);
			dummy.next = head;

			ListNode* i = &dummy;
			ListNode* j = &dummy;

			while (nullptr != j->next) {
				j = j->next;

				if (j->val != 9)
					i = j;
			}

			if (j->val != 9)
				j->val++;
			else {
				i->val++;
				i = i->next;

				while (nullptr != i) {
					i->val = 0;
					i = i->next;
				}
			}

			ListNode* newhead = head;
			if (0 != dummy.val) {
				newhead = new ListNode(1);
				newhead->next = head;
			}

			return newhead;
		}
	};
	/*369. Plus One Linked List end */


	/*368. Largest Divisible Subset (medium)
	https://leetcode.com/problems/largest-divisible-subset/
	https://discuss.leetcode.com/topic/49456/c-solution-with-explanations
	*/
	class Solution368 {
	public:
		vector<int> largestDivisibleSubset(vector<int>& nums) {
			vector<int> result;
			int n = nums.size();
			sort(nums.begin(), nums.end());
			vector<int> dp(n, 0);
			vector<int> parent(n, 0);
			int mi = 0;
			int m = 0;

			//m used for the maximal length, mi used for the first in that subset
			//so it is easier to start from the end of the array
			for (int i = n - 1; i >= 0; --i)
			for (int j = i; j < n; ++j) {
				if (0 == nums[j] % nums[i] && dp[i] < dp[j] + 1) {
					dp[i] = dp[j] + 1;
					parent[i] = j;

					if (dp[i] > m) {
						m = dp[i];
						mi = i;
					}
				}
			}
			
			for (int i = 0; i < m; ++i) {
				result.push_back(nums[mi]);
				mi = parent[mi];
			}
					
			return result;
		}
	};
	/*368. Largest Divisible Subset end */


	/*362. Design Hit Counter (medium)
	https://leetcode.com/problems/design-hit-counter/
	https://discuss.leetcode.com/topic/48758/super-easy-design-o-1-hit-o-s-gethits-no-fancy-data-structure-is-needed/3
	*/
	class HitCounter362 {
	public:
		/** Initialize your data structure here. */
		HitCounter362() {
			times.resize(300, 0);
			hits.resize(300, 0);
		}

		/** Record a hit.
		@param timestamp - The current timestamp (in seconds granularity). */
		void hit(int timestamp) {
			int idx = timestamp % 300;

			if (timestamp != times[idx]) {
				times[idx] = timestamp;
				hits[idx] = 1;
			}
			else
				++hits[idx];
		}

		/** Return the number of hits in the past 5 minutes.
		@param timestamp - The current timestamp (in seconds granularity). */
		int getHits(int timestamp) {
			int result = 0;
			for (int i = 0; i < 300; ++i) {
				if (timestamp - times[i] < 300)
					result += hits[i];
			}

			return result;
		}

		vector<int> hits, times;
	};

	/*362. Design Hit Counter end */


	/*361. Bomb Enemy (medium)
	https://leetcode.com/problems/bomb-enemy/
	https://discuss.leetcode.com/topic/48565/short-o-mn-solution
	*/
	class Solution361 {
	public:
		int maxKilledEnemies(vector<string>& grid) {
			if (grid.empty() || grid[0].empty())
				return 0;

			int result = 0;
			int row = grid.size();
			int col = grid[0].size();
			int rowhit;
			vector<int> colhits(col, 0);

			for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j){
				if ('W' == grid[i][j])
					continue;

				if (!j || 'W' == grid[i][j - 1]) {
					rowhit = 0;
					for (int k = j; k < col && grid[i][k] != 'W'; ++k)
						rowhit += grid[i][k] == 'E';
				}

				if (!i || 'W' == grid[i - 1][j]) {
					colhits[j] = 0;
					for (int k = i; k < row && grid[k][j] != 'W'; ++k)
						colhits[j] += grid[k][j] == 'E';
				}

				if ('0' == grid[i][j])
					result = max(result, rowhit + colhits[j]);
			}

			return result;
		}

		static void main() {
			Solution361* test = new Solution361;
			vector<string> grid1 = { "0E00", "E0WE", "0E00" };
			int result;

			result = test->maxKilledEnemies(grid1);
			delete test;
		}
	};
	/*361. Bomb Enemy end */


	/*360. Sort Transformed Array (medium)
	https://leetcode.com/problems/sort-transformed-array/
	https://discuss.leetcode.com/topic/48424/java-o-n-incredibly-short-yet-easy-to-understand-ac-solution
	*/
	class Solution360 {
	public:
		vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
			int n = nums.size();
			vector<int> result(n);

			int i = 0, j = n - 1;
			int index = (a >= 0 ? n - 1 : 0);

			while (i <= j) {
				int num1 = cal(a, b, c, nums[i]);
				int num2 = cal(a, b, c, nums[j]);
				if (a >= 0)
					result[index--] = num1 > num2 ? cal(a, b, c, nums[i++]) : cal(a, b, c, nums[j--]);
				else
					result[index++] = num1 > num2 ? cal(a, b, c, nums[j--]) : cal(a, b, c, nums[i++]);
			}

			return result;
		}

		int cal(int a, int b, int c, int x) {
			return a * x * x + b * x + c;
		}
	};
	/*360. Sort Transformed Array end */


	/*357. Count Numbers with Unique Digits (medium)
	https://leetcode.com/problems/count-numbers-with-unique-digits/
	https://discuss.leetcode.com/topic/47983/java-dp-o-1-solution/2
	https://discuss.leetcode.com/topic/48332/java-o-1-with-explanation
	*/
	class Solution357 {
	public:
		int countNumbersWithUniqueDigits(int n) {
			if (n == 0)     return 1;

			int res = 10;
			int uniqueDigits = 9;
			int availableNumber = 9;
			while (n-- > 1 && availableNumber > 0) {
				uniqueDigits = uniqueDigits * availableNumber;
				res += uniqueDigits;
				availableNumber--;
			}

			return res;
		}
	};
	/*357. Count Numbers with Unique Digits end */


	/*356. Line Reflection (medium)
	Timer = O(n) without sorting	Space = O(n)
	https://leetcode.com/problems/line-reflection/
	https://discuss.leetcode.com/topic/47851/11ms-two-pass-hashset-based-java-solution/2
	*/
	class Solution356 {
	public:
		bool isReflected1(vector<pair<int, int>>& points) {
			sort(points.begin(), points.end());
			//sort(points.begin(), points.end(), [](pair<int, int> a, pair<int, int>b) {return a.first < b.first; });
	
			int len = points.size();

			if (len < 2)
				return true;

			//left and right can be got via going over the
			//whole vector, no need for sorting firstly
			int left = points[0].first;
			int right = points[len - 1].first;
			
			unordered_map<int, unordered_set<int>> lefthash;
			unordered_map<int, unordered_set<int>> righthash;

			for (auto item : points) {
				if (item.first - left < right - item.first)
					lefthash[item.first].insert(item.second);
				else if (item.first - left > right - item.first) {
					righthash[item.first].insert(item.second);
				}
			}
			
			for (auto item : lefthash) {
				int mirror_x = right - item.first + left;
				if (righthash[mirror_x].size() != item.second.size())
					return false;
				
				for (auto point : item.second) {
					if (righthash[mirror_x].count(point) < 1)
						return false;
				}
			}

			return lefthash.size() == righthash.size();
		}

		bool isReflected(vector<pair<int, int>>& points) {
			sort(points.begin(), points.end());

			int len = points.size();

			if (len < 2)
				return true;

			int left = points[0].first;
			int right = points[len - 1].first;

			unordered_set<string> hash;
			unordered_set<string> desthash;
			for (auto item : points) {
				string key = to_string(item.first - left) + "a" + to_string(right - item.first) + "b" + to_string(item.second);
				string mirror_key = to_string(right - item.first) + "a" + to_string(item.first - left) + "b" + to_string(item.second);
				hash.insert(key);
				desthash.insert(mirror_key);
			}

			for (auto item : hash) {
				if (desthash.count(item) < 1)
					return false;
			}

			return hash.size() == desthash.size();
		}

		static void main() {
			Solution356* test = new Solution356;
			bool result;

			vector<pair<int, int>>points1 = { { 1, 1 }, {-1, 1 }};
			result = test->isReflected(points1);
			delete test;
		}
	};
	/*356. Line Reflection end */


	/*353. Design Snake Game (medium)
	https://leetcode.com/problems/design-snake-game/
	https://discuss.leetcode.com/topic/47385/c-straightforward-solution
	*/
	class SnakeGame353 {
	public:
		/** Initialize your data structure here.
		@param width - screen width
		@param height - screen height
		@param food - A list of food positions
		E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
		SnakeGame353(int width, int height, vector<pair<int, int>> food) {
			m_width = width;
			m_height = height;

			m_body.push_back(make_pair(0, 0));
			for (auto item : food)
				m_food.push(item);
		}

		/** Moves the snake.
		@param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
		@return The game's score after the move. Return -1 if game over.
		Game over when snake crosses the screen boundary or bites its body. */
		int move(string direction) {
			pair<int, int> newpos(m_body.front());

			switch (direction[0])
			{
			case 'U':
				--newpos.first;
				break;

			case 'D':
				++newpos.first;
				break;

			case 'L':
				--newpos.second;
				break;

			case 'R':
				++newpos.second;
				break;

			default:
				return -1;
			}

			//check pos
			if (newpos.first < 0 || newpos.first >= m_height ||
				newpos.second < 0 || newpos.second >= m_width)
				return -1;

			//check body
			for (int i = 0; i < m_body.size() - 1; ++i) {
				if (m_body.at(i).first == newpos.first && m_body.at(i).second == newpos.second)
					return -1;
			}

			m_body.push_front(newpos);
			if (!m_food.empty() && m_food.front().first == newpos.first && m_food.front().second == newpos.second)
				m_food.pop();
			else
				m_body.pop_back();

			return m_body.size() - 1;
		}

		static void main() {
			int width = 3, height = 2;
			vector<pair<int, int>> food = { { 3, 2 }, { 0, 1 } };
			int result;

			SnakeGame353* test = new SnakeGame353(width, height, food);
			//["R"],["D"],["R"],["U"],["L"],["U"]
			result = test->move("R");
			result = test->move("D");
			result = test->move("R");
			result = test->move("U");
			result = test->move("L");
			result = test->move("U");

			delete test;
		}

		int m_width;
		int m_height;
		deque<pair<int, int>> m_body;
		queue<pair<int, int>> m_food;
	};

	/**
	* Your SnakeGame object will be instantiated and called as such:
	* SnakeGame obj = new SnakeGame(width, height, food);
	* int param_1 = obj.move(direction);
	*/
	/*353. Design Snake Game end */


	/*351. Android Unlock Patterns (medium)
	https://leetcode.com/problems/android-unlock-patterns/
	https://discuss.leetcode.com/topic/46260/java-dfs-solution-with-clear-explanations-and-optimization-beats-97-61-12ms
	http://blog.csdn.net/qq508618087/article/details/51758481
	*/
	class Solution351 {
	public:
		int dfs(vector<bool>&visit, vector<vector<int>>&skip, int cur, int remain) {
			if (remain < 0)
				return 0;
			else if (0 == remain)
				return 1;

			//legal for jump from 2 to 9
			int result = 0;
			visit[cur] = true;
			for (int i = 1; i < 10; ++i) {
				if (!visit[i] && (0 == skip[cur][i] || visit[skip[cur][i]]))
					result += dfs(visit, skip, i, remain - 1);
			}

			visit[cur] = false;
			return result;
		}

		int numberOfPatterns(int m, int n) {
			vector<bool>visit(10, false);
			vector<vector<int>>skip(10, vector<int>(10, 0));

			skip[1][3] = skip[3][1] = 2;
			skip[3][9] = skip[9][3] = 6;
			skip[7][9] = skip[9][7] = 8;
			skip[1][7] = skip[7][1] = 4;


			skip[1][9] = skip[9][1] = 5;
			skip[3][7] = skip[7][3] = 5;
			skip[2][8] = skip[8][2] = 5;
			skip[4][6] = skip[6][4] = 5;

			int result = 0;
			for (int i = m; i <= n; ++i) {
				result += dfs(visit, skip, 1, i - 1) * 4;
				result += dfs(visit, skip, 2, i - 1) * 4;
				result += dfs(visit, skip, 5, i - 1);
			}

			return result;
		}
	};
	/*351. Android Unlock Patterns end */


	/*348. Design Tic-Tac-Toe (medium)
	https://leetcode.com/problems/design-tic-tac-toe/
	https://leetcode.com/problems/design-tic-tac-toe/
	*/
	class TicTacToe348 {
	public:
		/** Initialize your data structure here. */
		TicTacToe348(int n) {
			rows.resize(n, 0);
			cols.resize(n, 0);
			diagonal = 0;
			antidiagonal = 0;
		}

		/** Player {player} makes a move at ({row}, {col}).
		@param row The row of the board.
		@param col The column of the board.
		@param player The player, can be either 1 or 2.
		@return The current winning condition, can be either:
		0: No one wins.
		1: Player 1 wins.
		2: Player 2 wins. */
		int move(int row, int col, int player) {
			int toadd = (1 == player ? 1 : -1);
			int len = rows.size();

			rows[row] += toadd;
			cols[col] += toadd;

			if (row == col)
				diagonal += toadd;

			if (row == len - 1 - col)
				antidiagonal += toadd;

			if (len == abs(rows[row]) || len == abs(cols[col]) ||
				len == abs(diagonal) || len == abs(antidiagonal))
				return player;
			else
				return 0;
		}

		vector<int> rows;
		vector<int> cols;
		int diagonal;
		int antidiagonal;
	};

	/**
	* Your TicTacToe object will be instantiated and called as such:
	* TicTacToe obj = new TicTacToe(n);
	* int param_1 = obj.move(row,col,player);
	*/
	/*348. Design Tic-Tac-Toe end */


	/*341. Flatten Nested List Iterator (medium)
	https://leetcode.com/problems/flatten-nested-list-iterator/
	https://discuss.leetcode.com/topic/41870/real-iterator-in-python-java-c/2
	*/
	/*
	class NestedIterator341 {
	public:
		NestedIterator341(vector<NestedIterator341> &nestedList) {

			dfs(nestedList);
			m_cur = 0;
		}

		void dfs(vector<NestedIterator341> &nestedList)
		{
			for (int i = 0; i < nestedList.size(); ++i)
			{
				if (nestedList[i].isInteger())
					m_vec.push_back(nestedList[i].getInteger());
				else
				{
					vector<NestedIterator341> tmp = nestedList[i].getList();
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
	*/
	/*341. Flatten Nested List Iterator end */


	/*332. Reconstruct Itinerary (medium)
	https://leetcode.com/problems/reconstruct-itinerary/
	https://discuss.leetcode.com/topic/36383/share-my-solution
	http://www.geeksforgeeks.org/euler-circuit-directed-graph/
	*/
	class Solution332 {
	public:
		vector<string> findItinerary(vector<pair<string, string>> tickets) {
			unordered_map<string, set<string>> datas;

			for (auto item : tickets)
				datas[item.first].insert(item.second);

			stack<string> start;
			vector<string> result;
			string next;

			string from("JFK");
			result.push_back(from);

			for (auto item : datas[from]) {
				if (item.empty())
					continue;

				result.push_back(item);
				while (true) {
					if (datas[item].empty() || from == item)
						break;

					next = *datas[item].begin();
					datas[item].erase(datas[item].begin());
					result.push_back(next);
					item = next;
				}
			}

			return result;
		}

		static void main() {
			Solution332* test = new Solution332;
			vector<pair<string, string>> tickets1 = { { "MUC", "LHR" }, { "JFK", "MUC" }, { "SFO", "SJC" }, { "LHR", "SFO" } };
			vector<pair<string, string>> tickets2 = { { "JFK", "SFO" }, { "JFK", "ATL" }, { "SFO", "ATL" }, { "ATL", "JFK" }, { "ATL", "SFO" } };

			vector<string> result;
			result = test->findItinerary(tickets2);

			delete test;
		}
	};
	/*332. Reconstruct Itinerary end */


	/*331. Verify Preorder Serialization of a Binary Tree (medium)
	https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/
	https://discuss.leetcode.com/topic/35976/7-lines-easy-java-solution
	https://www.hrwhisper.me/leetcode-verify-preorder-serialization-of-a-binary-tree/
	*/
	class Solution331 {
	public:
		bool valid(stack<char>& data) {
			while (!data.empty() && '#' == data.top()) {
				data.pop();

				if (data.empty() || '#' == data.top())
					return false;
			}

			return true;
		}

		bool isValidSerialization(string preorder) {
			if (preorder.empty())
				return false;

			stack<char> buf;
			for (int i = 0; i < preorder.size(); ++i) {
				if ('#' == preorder[i]) {
					if (!buf.empty() && '#' == buf.top())
						if (!valid(buf))
							return false;
				}
				else if (',' != preorder[i]) {
					buf.push(preorder[i]);
					if (!valid(buf))
						return false;
				}
			}

			if (1 == buf.size() && '#' == buf.top())
				return true;
			return false;
		}

		bool isValidSerialization1(string preorder) {
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
					}
				
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

			return 1 == buf.size() && "#" == buf.top();
		}
	};
	/*331. Verify Preorder Serialization of a Binary Tree end */


	/*324. Wiggle Sort II (medium)
	https://leetcode.com/problems/wiggle-sort-ii/
	https://discuss.leetcode.com/topic/32929/o-n-o-1-after-median-virtual-indexing/21
	https://discuss.leetcode.com/topic/41464/step-by-step-explanation-of-index-mapping-in-java
	https://en.wikipedia.org/wiki/Quickselect
	https://discuss.leetcode.com/topic/32861/3-lines-python-with-explanation-proof
	https://discuss.leetcode.com/topic/32920/o-n-time-o-1-space-solution-with-detail-explanations
	*/
	class Solution324 {
	public:
		void wiggleSort(vector<int>& nums) {
			if (nums.size() < 2)
				return;

			//quickselect, get median, O(n) time and O(1) space
			int n = nums.size();
			int i = 0, j = n - 1, median = 0;
			int mid = (n - 1) / 2;
			while (i <= j) {
				int p = i, a = i + 1, b = j;
				while (a <= b) {
					if (nums[a] <= nums[p])
						swap(nums[a], nums[b--]);
					else
						++a;
				}

				swap(nums[p], nums[b]);

				if (b == mid) {
					median = nums[b];
					break;
				}
				else if (b > mid)
					j = b - 1;
				else
					i = b + 1;
			}

			int left = 0, right = n - 1;
			i = 0;

			//large number is put in odd index from left
			//small number is put in even index from right
			while (i <= right) {
				if (nums[newindex(i, n)] > median)
					swap(nums[newindex(left++, n)], nums[newindex(i++, n)]);
				else if (nums[newindex(i, n)] < median)
					swap(nums[newindex(right--, n)], nums[newindex(i, n)]);
				else
					++i;
			}
		}

		//n | 1 means when n is odd(n | 1 = n) and when n is even(n | 1 = n + 1)
		int newindex(int index, int n) {
			return (1 + 2 * index) % (n | 1);
		}

		static void main() {
			Solution324* test = new Solution324;
			//vector<int> nums1 = { 10,11,12,13,14,15,16,17,18,19 };
			vector<int> nums2 = { 4, 3, 6, 5, 2, 9 };
			test->wiggleSort(nums2);
			delete test;
		}
	};
	/*324. Wiggle Sort II end */


	/*323. Number of Connected Components in an Undirected Graph (medium)
	https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
	https://www.youtube.com/watch?v=9pIvy6fksHs&index=4&list=PLUX6FBiUa2g4YWs6HkkCpXL6ru02i7y3Q
	https://discuss.leetcode.com/topic/32752/easiest-2ms-java-solution
	*/
	class Solution323 {
	public:
		int countComponents(int n, vector<pair<int, int>>& edges) {
			vector<int> root(n);

			for (int i = 0; i < n; ++i)
				root[i] = i;

			for (auto item : edges) {
				int p = item.first;
				int q = item.second;

				int rootp = findroot(root, p);
				int rootq = findroot(root, q);

				if (rootp != rootq) {
					--n;
					root[rootp] = rootq;
				}
			}

			return n;
		}

		int findroot(vector<int>&root, int id) {
			while (id != root[id]) {
				root[id] = root[root[id]];
				id = root[id];
			}

			return id;
		}

		int countComponents1(int n, vector<pair<int, int>>& edges) {
			vector<bool> flag(n, false);
			queue<int> nodes;
			int result = 0;
			unordered_map<int, unordered_set<int>> maps;

			for (auto item : edges) {
				maps[item.first].insert(item.second);
				maps[item.second].insert(item.first);
			}

			for (auto item : maps) {
				if (flag[item.first])
					continue;

				++result;
				nodes.push(item.first);
				while (!nodes.empty()) {
					int cur = nodes.front();
					flag[cur] = true;
					nodes.pop();

					for (auto next : maps[cur]) {
						if (!flag[next])
							nodes.push(next);
					}
				}
			}

			for (auto item : flag) {
				if (!item)
					++result;
			}

			return result;
		}
	};
	/*323. Number of Connected Components in an Undirected Graph end */


	/*320. Generalized Abbreviation (medium)
	https://leetcode.com/problems/generalized-abbreviation/
	https://discuss.leetcode.com/topic/32163/meet-in-google-interview-solution-with-concise-explanation
	https://discuss.leetcode.com/topic/32270/java-backtracking-solution/2
	*/
	class Solution320 {
	public:
		//count indicate how many chars have been abbriveated
		void backtrack(vector<string>& result, string word, int pos, int count, string cur) {
			if (pos == word.size()) {
				if (count > 0)
					cur += to_string(count);

				result.push_back(cur);
				return;
			}

			//keep it
			if (count > 0)
				 //has abbrivation before it, just abbriveate it.
				backtrack(result, word, pos + 1, 0, cur + to_string(count) + word[pos]);
			else //no abbrivation before it
				backtrack(result, word, pos + 1, 0, cur + word[pos]);

			//abbriveate it
			backtrack(result, word, pos + 1, count + 1, cur);
		}

		vector<string> generateAbbreviations(string word) {
			vector<string> result;

			backtrack(result, word, 0, 0, "");

			return result;
		}
	};
	/*320. Generalized Abbreviation end */


	/*318. Maximum Product of Word Lengths (medium)
	https://leetcode.com/problems/maximum-product-of-word-lengths/
	https://discuss.leetcode.com/topic/35539/java-easy-version-to-understand
	*/
	class Solution318 {
	public:
		int maxProduct(vector<string>& words) {
			unordered_map<int, int> maxlen;
			int result = 0;
			for (auto item : words) {
				int mask = 0;
				for (char c : item)
					mask |= 1 << (c - 'a');

				//make sure hash hold the maximal legth with the same key
				//because this will make the product maximal if exist
				//other wise the maximal legth will be missed by the later small one
				maxlen[mask] = max(maxlen[mask], (int)item.size());

				for (auto lenitem : maxlen) {
					if (!(mask & lenitem.first))
						result = max(result, int(item.size() * lenitem.second));
				}
			}

			return result;
		}
	};
	/*318. Maximum Product of Word Lengths end */


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


	/*313. Super Ugly Number (medium)
	https://leetcode.com/problems/super-ugly-number/
	https://discuss.leetcode.com/topic/31012/7-line-consice-o-kn-c-solution
	https://discuss.leetcode.com/topic/52791/fastest-nth-ugly-number-ugly-number-ii-and-super-ugly-number-similar-solutions-java-dynamic-programming
	https://discuss.leetcode.com/topic/24306/elegant-c-solution-o-n-space-time-with-detailed-explanation/2
	*/
	class Solution313 {
	public:
		int nthSuperUglyNumber(int n, vector<int>& primes) {
			int len = primes.size();
			vector<int> index(len, 0);
			vector<int> result(n, INT_MAX);

			//current prime generate by former multiply one of primes
			//index[j] always point to the first unused index 
			//in result for primes[j]
			result[0] = 1;
			for (int i = 1; i < n; ++i) {
				for (int j = 0; j < len; ++j)
					result[i] = min(result[i], result[index[j]] * primes[j]);

				for (int j = 0; j < len; ++j)
					index[j] += (result[i] == result[index[j]] * primes[j]);
			}


			return result[n - 1];
		}

		static void main() {
			Solution313* test = new Solution313;
			int result;
			vector<int> primes = { 2, 7, 13, 19 };

			result = test->nthSuperUglyNumber(10, primes);
			delete test;
		}
	};
	/*313. Super Ugly Number end */


	/*310. Minimum Height Trees (medium)
	https://leetcode.com/problems/minimum-height-trees/
	https://discuss.leetcode.com/topic/30572/share-some-thoughts
	*/
	class Solution310 {
	public:
		vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
			if (1 == n)
				return vector<int>(1, 0);

			vector<int> cur;
			vector<unordered_set<int>> adj(n);
			for (auto item : edges) {
				adj[item.first].insert(item.second);
				adj[item.second].insert(item.first);
			}

			for (int i = 0; i < n; ++i)
				if (1 == adj[i].size())
					cur.push_back(i);

			while (true) {
				vector<int> next;

				for (auto item : cur) {
					for (auto neighbor : adj[item]) {
						adj[neighbor].erase(item);
						if (1 == adj[neighbor].size())
							next.push_back(neighbor);
					}
				}

				if (next.empty())
					return cur;

				cur = next;
			}
		}
	};
	/*310. Minimum Height Trees end */


	/*309. Best Time to Buy and Sell Stock with Cooldown (medium)
	https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
	https://discuss.leetcode.com/topic/30421/share-my-thinking-process
	*/
	class Solution309 {
	public:
		int maxProfit(vector<int>& prices) {
			int size = prices.size();
			if (size < 2)
				return 0;

			int sell_pre = 0;
			int sell = 0;
			int buy_pre;// = -prices[0];
			int buy = -prices[0];// = max(buy_pre, -price[1]);
			//1)buy[i] = max(rest[i-1]-price, buy[i-1])
			//sell[i] = max(buy[i-1]+price, sell[i-1])
			//rest[i] = max(rest[i-1], buy[i-1], sell[i-1])
			//****    = max(rest[i-1], sell[i-1]) as buy[i] <= rest[i]
			//rest[i] <= sell[i], so rest[i-1] <= sell[i-1]
			//->  rest[i] = sell[i-1]
			//2) buy[i] = max(sell[i-2]-price, buy[i-1])
			//	sell[i] = max(buy[i-1]+price, sell[i-1])
			for (int i = 0; i < size; ++i) {
				buy_pre = buy;
				buy = max(sell_pre - prices[i], buy_pre);

				sell_pre = sell;
				sell = max(sell_pre, buy_pre + prices[i]);
			}

			return sell;
		}
	};
	/*309. Best Time to Buy and Sell Stock with Cooldown end */


	/*298. Binary Tree Longest Consecutive Sequence (medium)
	Time = O(n)
	https://leetcode.com/problems/binary-tree-longest-consecutive-sequence/
	https://discuss.leetcode.com/topic/28234/easy-java-dfs-is-there-better-time-complexity-solution/8
	*/
	class Solution298 {
	public:
		int result;
		void nextNode(TreeNode* root, int cur, int target) {
			if (nullptr == root)
				return;

			if (target == root->val)
				++cur;
			else
				cur = 1;

			result = max(result, cur);
			nextNode(root->left, cur, root->val + 1);
			nextNode(root->right, cur, root->val + 1);
		}

		int longestConsecutive(TreeNode* root) {
			if (nullptr == root)
				return 0;

			nextNode(root, 0, root->val);
			return result;
		}
	};
	/*298. Binary Tree Longest Consecutive Sequence end */


	/*294. Flip Game II (medium)
	Time = O(2 ^ n)
	https://leetcode.com/problems/flip-game-ii/
	https://discuss.leetcode.com/topic/27282/theory-matters-from-backtracking-128ms-to-dp-0ms
	https://discuss.leetcode.com/topic/27351/java-backtracking-solution-with-time-optimization-through-dp-205ms-19ms/3
	*/
	class Solution294 {
	public:
		string str;
		int len;
		bool nextStep() {
			for (int i = 0; i < len - 1; ++i) {
				if ('+' == str[i] && '+' == str[i + 1]) {
					str[i] = str[i + 1] = '-';
					bool flag = !nextStep();
					str[i] = str[i + 1] = '+';

					if (flag)
						return true;
				}
			}

			return false;
		}

		bool canWin(string s) {
			str = s;
			len = s.size();
			return nextStep();
		}

		static void main() {
			Solution294* test = new Solution294;
			bool result;
			string s1("");
			string s2("+");
			string s3("++");
			string s4("+++");
			string s5("++++");
			string s6("+++++");

			/*result = test->canWin(s1);
			result = test->canWin(s2);
			result = test->canWin(s3);
			result = test->canWin(s4);
			result = test->canWin(s5);*/
			result = test->canWin(s6);
			delete test;
		}
	};
	/*294. Flip Game II end */


	/*289. Game of Life (medium)
	Time = O(m * n)		Space = O(1)
	https://leetcode.com/problems/game-of-life/
	https://discuss.leetcode.com/topic/26112/c-o-1-space-o-mn-time
	*/
	class Solution289 {
	public:
		void gameOfLife(vector<vector<int>>& board) {
			int m = board.size();
			int n = m ? board[0].size() : 0;
			int count;

			//use two bits, next status + current status
			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j) {
					count = 0;
					//cal the total alive cell including i,j
					for (int row = max(i - 1, 0); row < min(i + 2, m); ++row)
						for (int col = max(j - 1, 0); col < min(j + 2, n); ++col)
							count += board[row][col] & 1;

					//count == 3 if current is alive, its next status must be alive
					//			 if current is dead, its next status is alive
					//count - board[i][j] == 3 is to calculate the neighbors
					if (count == 3 || count - board[i][j] == 3)
						board[i][j] |= 2;
				}

			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j)
					board[i][j] >>= 1;
		}
	};
	/*289. Game of Life end */


	/*286. Walls and Gates (medium)
	Time = O(m * n)		Space = O(1)
	https://leetcode.com/problems/walls-and-gates/
	https://discuss.leetcode.com/topic/35242/benchmarks-of-dfs-and-bfs
	*/
	class Solution286 {
	public:
		void bsf(int i, int j, int dis, vector<vector<int>>& rooms) {
			vector<pair<int, int>> offset = { { 1, 0 },{ -1, 0 },{ 0, 1 },{ 0, -1 } };

			for (auto item : offset) {
				int row = i + item.first;
				int col = j + item.second;

				//rooms[row][col] < dis means alreay have a another closer gate
				if (row < 0 || row >= rooms.size() ||
					col < 0 || col >= rooms[0].size() || rooms[row][col] < dis)
					continue;

				rooms[row][col] = min(rooms[row][col], dis);
				bsf(row, col, dis + 1, rooms);
			}
		}

		void wallsAndGates(vector<vector<int>>& rooms) {
			if (rooms.empty() || rooms[0].empty())
				return;

			int row = rooms.size();
			int col = rooms[0].size();
			queue<pair<int, int>> points;

			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j) {
					if (0 == rooms[i][j])
						points.push({ i, j });
				}

			while (!points.empty()) {
				pair<int, int> cur = points.front();
				points.pop();

				//because this bfs, if the neightbor's value is not maximal, that means
				//there already has a closer gate for it.
				if (cur.first > 0 && numeric_limits<int>::max() == rooms[cur.first - 1][cur.second]) {
					rooms[cur.first - 1][cur.second] = rooms[cur.first][cur.second] + 1;
					points.push({ cur.first - 1 , cur.second });
				}

				if (cur.second > 0 && numeric_limits<int>::max() == rooms[cur.first][cur.second - 1]) {
					rooms[cur.first][cur.second - 1] = rooms[cur.first][cur.second] + 1;
					points.push({ cur.first , cur.second - 1 });
				}

				if (cur.first < row - 1 && numeric_limits<int>::max() == rooms[cur.first + 1][cur.second]) {
					rooms[cur.first + 1][cur.second] = rooms[cur.first][cur.second] + 1;
					points.push({ cur.first + 1 , cur.second });
				}

				if (cur.second < col - 1 && numeric_limits<int>::max() == rooms[cur.first][cur.second + 1]) {
					rooms[cur.first][cur.second + 1] = rooms[cur.first][cur.second] + 1;
					points.push({ cur.first , cur.second + 1 });
				}
			}
		}

		void wallsAndGates1(vector<vector<int>>& rooms) {
			if (rooms.empty() || rooms[0].empty())
				return;

			int row = rooms.size();
			int col = rooms[0].size();
			vector<pair<int, int>> gates;

			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j) {
					if (0 == rooms[i][j])
						bsf(i, j, 1, rooms);
				}
		}

		static void main() {
			Solution286* test = new Solution286;
			vector<vector<int>> rooms1 = { { INT_MAX, -1, 0, INT_MAX },
			{ INT_MAX, INT_MAX, INT_MAX, -1 },
			{ INT_MAX, -1, INT_MAX, -1 },
			{ 0, -1, INT_MAX, INT_MAX } };

			vector<vector<int>> rooms2 = { { -1, INT_MAX, 0 },
			{ INT_MAX, -1, INT_MAX },
			{ INT_MAX, 0, INT_MAX } };
			test->wallsAndGates(rooms2);
			delete test;
		}
	};
	/*286. Walls and Gates end */


	/*284. Peeking Iterator (medium)
	https://leetcode.com/problems/peeking-iterator/
	https://discuss.leetcode.com/topic/24883/concise-java-solution
	*/
#if 0
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

		static void main() {
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
	/*284. Peeking Iterator end */


	/*281. Zigzag Iterator (medium)
	https://leetcode.com/problems/zigzag-iterator/
	https://discuss.leetcode.com/topic/24548/c-with-queue-compatible-with-k-vectors
	https://discuss.leetcode.com/topic/24231/short-java-o-1-space
	*/
	class ZigzagIterator281 {
	public:
		ZigzagIterator281(vector<int>& v1, vector<int>& v2) {
			if (v1.size() != 0)
				Q.push(make_pair(v1.begin(), v1.end()));
			if (v2.size() != 0)
				Q.push(make_pair(v2.begin(), v2.end()));
		}

		int next() {
			vector<int>::iterator it = Q.front().first;
			vector<int>::iterator endIt = Q.front().second;
			Q.pop();
			if (it + 1 != endIt)
				Q.push(make_pair(it + 1, endIt));
			return *it;
		}

		bool hasNext() {
			return !Q.empty();
		}
	private:
		queue<pair<vector<int>::iterator, vector<int>::iterator>> Q;
	};

	class ZigzagIterator281_2 {
	public:
		ZigzagIterator281_2(vector<int>& v1, vector<int>& v2) {
			ites.push_back({ v1.begin(), v1.end() });
			ites.push_back({ v2.begin(), v2.end() });

			idx = 0;
			begin = v1.begin();
		}

		int next() {
			hasNext();
			
			int result = *(ites[idx].first);
			ites[idx].first ++;
			
			idx = (idx + 1) % ites.size();
			begin = ites[idx].first;
			return result;
		}

		bool hasNext() {
			int total = ites.size() + idx;
			int next = idx;

			while (next < total && begin == ites[next % ites.size()].second) {
				++next;
				begin = ites[next % ites.size()].first;
			}

			idx = next % ites.size();
			return begin != ites[idx].second;
		}

		static void main() {
			vector<int> v1 = { 1, 2 };
			vector<int> v2 = { 3, 4, 5, 6 };
			ZigzagIterator281* test = new ZigzagIterator281(v1, v2);

			while (test->hasNext()) 
				cout << test->next();
			delete test;
		}

		vector<pair<vector<int>::iterator, vector<int>::iterator>> ites;
		int idx;
		vector<int>::iterator begin;
	};
	/*281. Zigzag Iterator end */


	/*280. Wiggle Sort (medium)
	https://leetcode.com/problems/wiggle-sort/
	https://discuss.leetcode.com/topic/42605/my-explanations-of-the-best-voted-algo/2
	*/
	class Solution280 {
	public:
		void wiggleSort(vector<int>& nums) {
			for (int i = 1; i < nums.size(); ++i) {
				if (((i & 1) && nums[i] < nums[i - 1]) ||
					(!(i & 1) && nums[i] > nums[i - 1]))
					swap(nums[i - 1], nums[i]);
			}
		}

		void wiggleSort1(vector<int>& nums) {
			if (nums.empty() || 1 == nums.size())
				return;

			vector<int> tmp(nums);
			sort(tmp.begin(), tmp.end());

			int low = 0, high = nums.size() - 1;

			for (int i = 0; i < nums.size(); ++i) {
				if (i & 1)
					nums[i] = tmp[high--];
				else
					nums[i] = tmp[low++];					
			}
		}
	};
	/*280. Wiggle Sort end */


	/*279. Perfect Squares (medium)
	Time = O(n ^ 2)		Space = O(n)
	https://leetcode.com/problems/perfect-squares/
	https://discuss.leetcode.com/topic/24255/summary-of-4-different-solutions-bfs-dp-static-dp-and-mathematics
	*/
	class Solution279 {
	public:
		int numSquares(int n) {
			vector<int> dp(n + 1);

			for (int i = 1; i <= n; ++i)
				dp[i] = i;

			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j*j <= i; ++j) {
					if (j * j == i) {
						dp[i] = 1;
						break;
					}

					dp[i] = min(dp[i], 1 + dp[i - j * j]);
				}
			}

			return dp[n];
		}
	};
	/*279. Perfect Squares end */


	/*274. H-Index (medium)
	Time = O(n)		Space = O(n)
	https://leetcode.com/problems/h-index/
	https://discuss.leetcode.com/topic/23307/my-o-n-time-solution-use-java
	*/
	class Solution274 {
	public:
		int hIndex(vector<int>& citations) {
			if (citations.empty())
				return 0;

			int len = citations.size();
			vector<int> data(len + 1, 0);

			for (auto item : citations) {
				if (item >= len)
					++data[len];
				else
					++data[item];
			}

			int total = 0;
			for (int i = len; i >= 0; --i) {
				total += data[i];
				if (total >= i)
					return i;
			}

			return 0;
		}
	};
	/*274. H-Index end */


	/*271. Encode and Decode Strings (medium)
	https://leetcode.com/problems/encode-and-decode-strings/
	https://discuss.leetcode.com/topic/22798/accepted-simple-c-solution
	*/
	class Codec271 {
	public:
		// Encodes a list of strings to a single string.
		string encode(vector<string>& strs) {
			string result;

			for (auto item : strs) {
				char tmp[9] = { 0 };
				sprintf(tmp, "%08x", item.size());
				result += string(tmp) + item;
			}

			return result;
		}

		// Decodes a single string to a list of strings.
		vector<string> decode(string s) {
			vector<string> result;

			int i = 0;
			while (i < s.size()) {
				int len = stoi(s.substr(i, 8), nullptr, 16);
				i += 8;
				if (len)
					result.push_back(s.substr(i, len));
				else
					result.push_back(string(""));

				i += len;
			}

			return result;
		}
	};

	/*271. Encode and Decode Strings end */


	/*261. Graph Valid Tree (medium)
	Time = O(V * E)		Space = O(n)
	https://leetcode.com/problems/graph-valid-tree/
	https://discuss.leetcode.com/topic/21712/ac-java-union-find-solution/6
	http://www.geeksforgeeks.org/union-find/
	*/
	class Solution261 {
	public:
		bool validTree(int n, vector<pair<int, int>>& edges) {
			vector<int> roots(n, -1);

			for (auto item : edges) {
				int x = findroot(roots, item.first);
				int y = findroot(roots, item.second);

				if (x == y)
					return false;

				roots[x] = y;
			}

			//if less than n - 1, there must be multi tree
			return n - 1 == edges.size();
		}

		int findroot(vector<int>&roots, int id) {
			if (-1 == roots[id])
				return id;

			return findroot(roots, roots[id]);
		}
	};
	/*261. Graph Valid Tree end */


	/*259. 3Sum Smaller (medium)
	Time = O(n ^ 2)		Space = O(1)
	https://leetcode.com/problems/3sum-smaller/
	https://discuss.leetcode.com/topic/23421/simple-and-easy-understanding-o-n-2-java-solution
	*/
	class Solution259 {
	public:
		int threeSumSmaller(vector<int>& nums, int target) {
			int result = 0;
			sort(nums.begin(), nums.end());

			int len = nums.size();
			for (int i = 0; i < len - 2; ++i) {
				int j = i + 1, k = len - 1;

				while (j < k) {
					//the three value is the biggest for currentW
					if (nums[i] + nums[j] + nums[k] < target) {
						result += k - j;
						++j;
					}
					else
						--k;
				}
			}

			return result;
		}
	};
	/*259. 3Sum Smaller end */


	/*253. Meeting Rooms II (medium)
	Time = O(n * log n)		Spacer = O(n)
	https://leetcode.com/problems/meeting-rooms-ii/
	https://discuss.leetcode.com/topic/20958/ac-java-solution-using-min-heap/19
	https://discuss.leetcode.com/topic/20958/ac-java-solution-using-min-heap/6
	http://www.cnblogs.com/yrbbest/p/5012534.html
	*/
	class Solution253 {
	public:
		int minMeetingRooms(vector<Interval>& intervals) {
			if (intervals.empty())
				return 0;

			sort(intervals.begin(), intervals.end(), [](Interval& a, Interval& b) { return a.start < b.start; });

			//auto comp = [](Interval a, Interval b) { return a.end < b.end; };
			//priority_queue<Interval, decltype(comp)> heap(intervals.begin(), intervals.end());
			priority_queue<int> heap;
			int result = 0;

			for (auto item : intervals) {
				while (!heap.empty() && item.start >= -heap.top())
					heap.pop();

				heap.push(-item.end);
				result = max(result, (int)heap.size());
			}

			return result;
		}

		static void main() {
			Solution253* test = new Solution253;
			int result;

			vector<Interval> intervals1 = { { 0, 30 }, { 15, 20 }, { 5, 10 } };
			vector<Interval> intervals2 = { { 0, 15 }, { 5, 20 }, { 6, 10 } };
			vector<Interval> intervals3 = { { 2, 6 }, { 12, 18 }, { 9, 18 }, { 15, 20 } };
			//result = test->minMeetingRooms(intervals1);
			//result = test->minMeetingRooms(intervals2);
			result = test->minMeetingRooms(intervals3);
			delete test;
		}
	};
	/*253. Meeting Rooms II end */


	/*251. Flatten 2D Vector (medium)
	https://leetcode.com/problems/flatten-2d-vector/
	https://discuss.leetcode.com/topic/20697/7-9-lines-added-java-and-c-o-1-space
	*/
	class Vector2D251 {//Space = O(1)
	public:
		Vector2D251(vector<vector<int>>& vec2d) {
			it = vec2d.begin();
			iend = vec2d.end();
			j = 0;
		}

		int next() {
			hasNext();

			return (*it)[j++];
		}

		bool hasNext() {
			while (it != iend && j == it->size())
				it++, j = 0;

			return it != iend;
		}

		int j;
		vector<vector<int>>::iterator it;
		vector<vector<int>>::iterator iend;
	};

	class Vector2D251_1 {	//Space = O(n)
	public:
		Vector2D251_1(vector<vector<int>>& vec2d) {
			if (!vec2d.empty()) {
				for (int i = 0; i < vec2d.size(); ++i) {
					if (vec2d[i].empty())
						continue;

					for (int j = 0; j < vec2d[i].size(); ++j)
						data.push_back(vec2d[i][j]);
				}
			}

			cur = 0;
		}

		int next() {
			return data[cur++];
		}

		bool hasNext() {
			return cur < data.size();
		}

		int cur;
		vector<int> data;
	};
	/*251. Flatten 2D Vector end */


	/*247. Strobogrammatic Number II (medium)
	Time = O(2 ^ n)		Space = O(n)
	https://leetcode.com/problems/strobogrammatic-number-ii/
	https://discuss.leetcode.com/topic/20753/ac-clean-java-solution
	*/
	class Solution247 {
	public:
		vector<string> findStrobogrammatic(int n) {
			return findStrobogrammatic(n, n);
		}

		vector<string> findStrobogrammatic(int n, int m) {
			vector<string> result;
			if (n == 0) {
				result.push_back("");
				return result;
			}

			if (1 == n) {
				result.push_back("0");
				result.push_back("1");
				result.push_back("8");
				return result;
			}

			vector<string> tmp = findStrobogrammatic(n - 2, m);


			for (auto item : tmp) {
				if (n != m)
					result.push_back("0" + item + "0");
				result.push_back("6" + item + "9");
				result.push_back("9" + item + "6");
				result.push_back("8" + item + "8");
				result.push_back("1" + item + "1");
			}

			return result;
		}
	};
	/*247. Strobogrammatic Number II end */


	/*240. Search a 2D Matrix II (medium)
	Time = O(m + n)		Space = O(1)
	https://leetcode.com/problems/search-a-2d-matrix-ii/
	https://discuss.leetcode.com/topic/20064/my-concise-o-m-n-java-solution/2
	*/
	class Solution240 {
	public:
		bool searchMatrix(vector<vector<int>>& matrix, int target) {
			if (matrix.empty() || matrix[0].empty())
				return false;
			int row = matrix.size();
			int col = matrix[0].size();

			int j = col - 1, i = 0;

			while (j >= 0 && i < row) {
				if (matrix[i][j] == target)
					return true;

				if (matrix[i][j] > target)
					--j;
				else
					++i;
			}

			return false;
		}
	};
	/*240. Search a 2D Matrix II end */


	/*230. Kth Smallest Element in a BST (medium)
	https://leetcode.com/problems/kth-smallest-element-in-a-bst/
	https://discuss.leetcode.com/topic/17810/3-ways-implemented-in-java-binary-search-in-order-iterative-recursive/1
	https://discuss.leetcode.com/topic/17573/4-lines-in-c
	*/
	class Solution230 {
	public:
		int kthSmallest(TreeNode* root, int k) {
			//time = O(log n)	Space = O(k)
			stack<TreeNode*> nodes;
			nodes.push(root);

			while (!nodes.empty()) {
				TreeNode* tmp = nodes.top();

				while (tmp) {
					nodes.push(tmp->left);
					tmp = tmp->left;
				}

				nodes.pop();
				tmp = nodes.top();
				nodes.pop();
				--k;
				if (0 == k)
					return tmp->val;

				nodes.push(tmp->right);
			}

		}

		//time = O(log n)	Space = O(1)
		int kthSmallest1(TreeNode* root, int& k) {
			if (root) {
				int x = kthSmallest(root->left, k);

				//k == 0 means reach the kth node;
				//k != 0 means kth node in the right sub tree or current node
				//--k = 0 means current node is the kth node
				return !k ? x : !--k ? root->val : kthSmallest(root->right, k);
			}

			return -1;
		}
	};
	/*230. Kth Smallest Element in a BST end */


	/*228. Summary Ranges (medium)
	https://leetcode.com/problems/summary-ranges/
	https://discuss.leetcode.com/topic/17151/accepted-java-solution-easy-to-understand
	*/
	class Solution228 {
	public:
		//0,1,2,4,5,7
		vector<string> summaryRanges(vector<int>& nums) {
			vector<string> result;

			for (int i = 0; i < nums.size(); ++i) {
				int j = i;
				while (j + 1 < nums.size() && nums[j + 1] == nums[j] + 1)
					++j;

				if (j == i)
					result.push_back(to_string(nums[i]));
				else
					result.push_back(to_string(nums[i]) + "->" + to_string(nums[j]));

				i = j;
			}

			return result;
		}
	};
	/*228. Summary Ranges end */


	/*208. Implement Trie (Prefix Tree) (medium)
	https://leetcode.com/problems/implement-trie-prefix-tree/
	https://discuss.leetcode.com/topic/13463/maybe-the-code-is-not-too-much-by-using-next-26-c
	*/
	class TrieNode {
	public:
		// Initialize your data structure here.
		TrieNode(bool bword=false) {
			isword = bword;
			for (int i = 0; i < 26; ++i)
				next[i] = nullptr;
		}

		bool isword;
		TrieNode* next[26];
	};

	class Trie208 {
	public:
		Trie208() {
			root = new TrieNode();
		}

		// Inserts a word into the trie.
		void insert(string word) {
			TrieNode* node = root;
			for (auto item : word) {
				if (nullptr == node->next[item - 'a'])
					node->next[item - 'a'] = new TrieNode();

				node = node->next[item - 'a'];
			}

			node->isword = true;
		}

		// Returns if the word is in the trie.
		bool search(string word) {
			TrieNode* node = root;
			for (auto item : word) {
				if (nullptr == node->next[item - 'a'])
					return false;
				node = node->next[item - 'a'];
			}

			return node->isword;
		}

		// Returns if there is any word in the trie
		// that starts with the given prefix.
		bool startsWith(string prefix) {
			TrieNode* node = root;
			for (auto item : prefix) {
				if (nullptr == node->next[item - 'a'])
					return false;
				node = node->next[item - 'a'];
			}

			return true;
		}

	private:
		TrieNode* root;
	};
	/*208. Implement Trie (Prefix Tree) end */


	/*200. Number of Islands (medium)
	https://leetcode.com/problems/number-of-islands/
	https://discuss.leetcode.com/topic/11589/dfs-and-bfs-in-c
	*/
	class Solution200 {
	public:
		void expandIsland(vector<vector<char>>& grid, int i, int j) {
			int row = grid.size();
			int col = grid[0].size();

			if (i < 0 || j < 0 || i >= row || j >= col || '1' != grid[i][j])
				return;

			grid[i][j] = '3';
			expandIsland(grid, i + 1, j);
			expandIsland(grid, i - 1, j);
			expandIsland(grid, i, j + 1);
			expandIsland(grid, i, j - 1);
		}

		//Time = O(m * n)	Space = O(1)
		int numIslands1(vector<vector<char>>& grid) {
			if (grid.empty() || grid[0].empty())
				return 0;

			int result = 0;
			int row = grid.size();
			int col = grid[0].size();

			for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j) {
				if ('1' == grid[i][j]) {
					++result;
					expandIsland(grid, i, j);
				}
			}

			return result;
		}

		//Time = O(m * n)	Space = O(total 1s in maximal island)
		int numIslands(vector<vector<char>>& grid) {
			if (grid.empty() || grid[0].empty())
				return 0;

			int result = 0;
			int row = grid.size();
			int col = grid[0].size();

			queue<pair<int, int>> points;

			int step = 0, total = row * col;
			while (step < total) {
				if ('1' == grid[step / col][step % col]) {
					++result;
					points.push(make_pair(step / col, step % col));
					grid[step / col][step % col] = '0';

					while (!points.empty()) {
						int i = points.front().first;
						int j = points.front().second;

						points.pop();
						if (i > 0 && '1' == grid[i - 1][j]) {
							points.push(make_pair(i - 1, j));
							grid[i - 1][j] = '0';
						}

						if (j > 0 && '1' == grid[i][j - 1]) {
							points.push(make_pair(i, j - 1));
							grid[i][j - 1] = '0';
						}

						if (i < row - 1 && '1' == grid[i + 1][j]) {
							points.push(make_pair(i + 1, j));
							grid[i + 1][j] = '0';
						}

						if (j < col - 1 && '1' == grid[i][j + 1]) {
							points.push(make_pair(i, j + 1));
							grid[i][j + 1] = '0';
						}
					}
				}

				++step;
			}

			return result;
		}

		int findIsland(vector<int>& roots, int id) {
			while (id != roots[id]) id = roots[id];
			return id;
		}

		static void main() {
			Solution200* test = new Solution200;
			int result;

			vector<vector<char>> grid1 = { { '1', '1', '1', '1', '0' }, 
			{ '1', '1', '0', '1', '0' }, { '1', '1', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' } };

			vector<vector<char>> grid2 = { { '1', '0', '1', '1', '0', '1', '1' } };
				result = test->numIslands(grid2);
			delete test;
		}
	};
	/*200. Number of Islands end */


	/*173. Binary Search Tree Iterator (medium)
	Time = O(1)		Space = O(h)
	https://leetcode.com/problems/binary-search-tree-iterator/
	https://discuss.leetcode.com/topic/6575/my-solutions-in-3-languages-with-stack
	*/
	class BSTIterator173 {
	public:
		BSTIterator173(TreeNode *root) {
			pushall(root);
		}

		/** @return whether we have a next smallest number */
		bool hasNext() {
			return !nodes.empty();
		}

		/** @return the next smallest number */
		int next() {
			TreeNode *cur = nodes.top();
			nodes.pop();
			pushall(cur->right);
			return cur->val;
		}

	private:
		void pushall(TreeNode *cur) {
			for (; nullptr != cur; nodes.push(cur), cur = cur->left)
				;
		}
		stack<TreeNode*> nodes;
	};
	/*173. Binary Search Tree Iterator end */


	/*166. Fraction to Recurring Decimal (medium)
	https://leetcode.com/problems/fraction-to-recurring-decimal/
	https://discuss.leetcode.com/topic/6079/accepted-cpp-solution-with-explainations
	*/
	class Solution166 {
	public:
		string fractionToDecimal(long numerator, long denominator) {
			string ret;

			if (numerator == 0)
				return "0";

			if (numerator < 0 ^ denominator < 0)
				ret += "-";

			numerator = abs(numerator);
			denominator = abs(denominator);

			ret += to_string(numerator / denominator);

			if (numerator % denominator == 0)
				return ret;

			ret += ".";

			//<digit, postion in ret>
			unordered_map<int, int> data;
			for (long r = numerator % denominator; r; r %= denominator) {
				if (data.count(r) > 0) {
					ret.insert(data[r], 1, '(');
					ret += ")";
					break;
				}

				data[r] = ret.size();
				r *= 10;
				ret += to_string(r / denominator);
			}

			return ret;
		}

		static void main() {
			Solution166* test = new Solution166;
			string result;
			long numerator1 = 1;
			long denominator1 = 30;

			result = test->fractionToDecimal(numerator1, denominator1);
			delete test;
		}
	};
	/*166. Fraction to Recurring Decimal end */


	/*163. Missing Ranges (medium)
	https://leetcode.com/problems/missing-ranges/
	https://discuss.leetcode.com/topic/18612/accepted-java-solution-with-explanation
	*/
	class Solution163 {
	public:
		//[0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].
		vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
			vector<string> result;
			// the next number we need to find
			int next = lower;

			for (int i = 0; i < nums.size(); ++i) {
				// not within the range yet
				if (nums[i] < lower)
					continue;

				// continue to find the next one
				if (nums[i] == next) {
					++next;
					continue;
				}

				next == nums[i] - 1 ? result.push_back(to_string(next)) :
					result.push_back(to_string(next) + "->" + to_string(nums[i] - 1));

				next = nums[i] + 1;
			}

			if (next <= upper)
				next == upper ? result.push_back(to_string(next)) :
				result.push_back(to_string(next) + "->" + to_string(upper));

			return result;
		}

		vector<string> findMissingRanges1(vector<int>& nums, int lower, int upper) {
			vector<string> result;

			if (nums.empty()) {

				if (lower == upper)
					result.push_back(to_string(lower));
				else
					result.push_back(to_string(lower) + "->" + to_string(upper));
				return result;
			}

			if (nums[0] > lower + 1)
				result.push_back(to_string(lower) + "->" + to_string(nums[0] - 1));
			else if (nums[0] > lower)
				result.push_back(to_string(lower));

			int lastpos = nums[0];
			int len = nums.size();

			for (int i = 0; i < len; ++i) {
				if (nums[i] > lastpos + 2)
					result.push_back(to_string(lastpos + 1) + "->" + to_string(nums[i] - 1));
				else if (nums[i] > lastpos + 1)
					result.push_back(to_string(lastpos + 1));

				while (i < len - 1 && nums[i + 1] == nums[i] + 1)
					++i;

				lastpos = nums[i];
			}

			if (upper > nums[len - 1] + 1)
				result.push_back(to_string(nums[len - 1] + 1) + "->" + to_string(upper));
			else if (upper > nums[len - 1])
				result.push_back(to_string(nums[len - 1] + 1));

			return result;
		}
	};
	/*163. Missing Ranges end */


	/*162. Find Peak Element (medium)
	https://leetcode.com/problems/find-peak-element/
	https://discuss.leetcode.com/topic/5724/find-the-maximum-by-binary-search-recursion-and-iteration
	https://discuss.leetcode.com/topic/5848/o-logn-solution-javacode
	*/
	class Solution162 {
	public:
		//Time = O(log n)		Space = O(1)
		int findPeak(vector<int>& nums, int low, int high) {
			if (low == high)
				return low;
			else if (low + 1 == high)
				return nums[high] > nums[low] ? high : low;
			else {
				int mid = low + (high - low) / 2;

				if (nums[mid] > nums[mid + 1] && nums[mid] > nums[mid - 1])
					return mid;
				else if (nums[mid] < nums[mid + 1] && nums[mid] > nums[mid - 1])
					return findPeak(nums, mid + 1, high);
				else
					return findPeak(nums, low, mid - 1);
			}
		}

		int findPeakElement(vector<int>& nums) {
			return findPeak(nums, 0, nums.size() - 1);
		}

		//Time = O(n)		Space = O(1)
		int findPeakElement1(vector<int>& nums) {
			int len = nums.size();

			if (0 == len)
				return -INT_MAX;
			else if (1 == len)
				return 0;
			else if (nums[0] > nums[1])
				return 0;

			for (int i = 1; i < len; ++i) {
				if (nums[i] > nums[i - 1]) {
					if (len - 1 == i)
						return i;

					if (nums[i] > nums[i + 1])
						return i;
				}
			}

			return -INT_MAX;
		}
	};
	/*162. Find Peak Element end */

	/*139. Word Break (medium)
	https://leetcode.com/problems/word-break/
	https://discuss.leetcode.com/topic/6156/java-implementation-using-dp-in-two-ways
	*/
	class Solution139 {
	public:
		//Time = O(n ^ 2)		Space = O(n)
		bool wordBreak(string s, unordered_set<string>& wordDict) {
			if (wordDict.empty())
				return false;

			//dp[i] indicates [0, i) in the string can be broke or not
			vector<bool> dp(s.size() + 1, false);

			dp[0] = true;
			for (int i = 1; i <= s.size(); ++i) {
				//[0, i] divided into [0, j) + [j, i)
				//check dp[j] and sub string (j,i-j)
				//if exist one successful break, that means
				//current string can be broke
				for (int j = i - 1; j >= 0; --j) {
					if (dp[j] && wordDict.count(s.substr(j, i - j)) > 0) {
						dp[i] = true;
						break;
					}
				}
			}

			return dp[s.size()];
		}

		//Time maybe = O(2 ^ n)		Space = O(1)
		bool wordBreak1(string s, unordered_set<string>& wordDict) {
			if (s.empty() || wordDict.empty())
				return true;

			std::size_t found;
			for (auto item : wordDict)
			{
				found = s.find(item);
				if (found != std::string::npos)
				{
					bool bleft = true;
					bool bright = true;
					if (found != 0)
					{
						string strleft = s.substr(0, found);
						bleft = wordBreak(strleft, wordDict);
					}

					if (found + item.size() < s.size())
					{
						string strleft = s.substr(found + item.size(), s.size() - found - item.size());
						bright = wordBreak(strleft, wordDict);
					}

					if (bleft && bright)
						return true;
				}
			}

			return false;
		}

		/*this will time out*/
		bool wordBreak2(string s, unordered_set<string>& wordDict) {
			if (s.empty())
				return true;

			for (auto item : wordDict) {
				int len = s.size();
				bool found = false;
				if (len >= item.size() && s.substr(0, item.size()) == item)
					found = wordBreak1(s.substr(item.size()), wordDict);

				if (found)
					return true;
			}

			return false;
		}
	};
	/*139. Word Break end */


	/*133. Clone Graph (medium)
	https://leetcode.com/problems/clone-graph/
	https://discuss.leetcode.com/topic/4690/simple-java-iterative-bfs-solution-with-hashmap-and-queue/2
	*/
	class Solution133 {
	public:
		UndirectedGraphNode *copyNode(UndirectedGraphNode *node, unordered_map<int, UndirectedGraphNode *>& visit) {
			UndirectedGraphNode* cur = new UndirectedGraphNode(node->label);
			visit[node->label] = cur;

			for (auto it : node->neighbors) {
				if (visit.count(it->label) < 1)
					cur->neighbors.push_back(copyNode(it, visit));
				else
					cur->neighbors.push_back(visit[it->label]);
			}

			return cur;
		}

		UndirectedGraphNode *cloneGraph1(UndirectedGraphNode *node) {
			if (nullptr == node)
				return nullptr;

			unordered_map<int, UndirectedGraphNode *> visit;

			return copyNode(node, visit);
		}

		UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
			if (nullptr == node)
				return nullptr;

			unordered_map<int, UndirectedGraphNode *> visit;

			queue<UndirectedGraphNode *> qnode;
			qnode.push(node);
			UndirectedGraphNode* clonenode = new UndirectedGraphNode(node->label);
			visit[node->label] = clonenode;

			while (!qnode.empty()) {
				UndirectedGraphNode * cur = qnode.front();
				qnode.pop();

				for (auto item : cur->neighbors) {
					if (visit.count(item->label) < 1) {
						UndirectedGraphNode* tmp = new UndirectedGraphNode(item->label);
						visit[item->label] = tmp;
						qnode.push((UndirectedGraphNode*)item);
					}

					visit[cur->label]->neighbors.push_back((UndirectedGraphNode*)visit[item->label]);
				}
			}

			return clonenode;
		}
	};
	/*133. Clone Graph end */


	/*54. Spiral Matrix (medium)
	https://leetcode.com/problems/spiral-matrix/
	https://discuss.leetcode.com/topic/15558/a-concise-c-implementation-based-on-directions
	https://discuss.leetcode.com/topic/3713/super-simple-and-easy-to-understand-solution
	*/
	class Solution54 {
	public:
		vector<int> spiralOrder(vector<vector<int>>& matrix) {
			vector<int> ret;

			if (matrix.empty() || matrix[0].empty())
				return ret;

			int row = matrix.size();
			int col = matrix[0].size();

			vector<int> nstep = { col, row - 1 };
			vector<pair<int, int>> direct = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };

			int cur = 0;
			int irow = 0, icol = -1;

			while (nstep[cur % 2]) {
				for (int i = 0; i < nstep[cur % 2]; ++i) {
					irow += direct[cur].first;
					icol += direct[cur].second;
					ret.push_back(matrix[irow][icol]);
				}

				--nstep[cur % 2];
				cur = (cur + 1) % 4;
			}
		}
	};
	/*54. Spiral Matrix end */

	/*50. Pow(x, n) (medium)
	https://leetcode.com/problems/powx-n/
	https://discuss.leetcode.com/topic/5425/short-and-easy-to-understand-solution/25
	*/
	class Solution50 {
	public:
		double myPow(double x, int n) {
			if (0 == n)
				return 1;

			if (n < 0) {
				return 1 / x * myPow(1 / x, -(++n));
			}

			return (0 == n % 2) ? myPow(x*x, n / 2) : x * myPow(x*x, n / 2);
		}
	};
	/*50. Pow(x, n) */


	/*31. Next Permutation (medium)
	https://leetcode.com/problems/next-permutation/
	http://blog.csdn.net/wwh578867817/article/details/46506673
	https://discuss.leetcode.com/topic/2542/share-my-o-n-time-solution
	https://discuss.leetcode.com/topic/15216/a-simple-algorithm-from-wikipedia-with-c-implementation-can-be-used-in-permutations-and-permutations-ii
	*/
	class Solution31 {
	public:
		void nextPermutation1(vector<int>& nums) {
			if (nums.size() <= 1)
				return;

			int len = nums.size() - 1, start;
			int swap1 = -1, swap2;
			while (len >= 0) {
				for (start = len - 1; start >= 0; --start) {
					if (nums[len] > nums[start])
						break;
				}

				if (start >= 0 && start > swap1) {
					swap1 = start;
					swap2 = len;
				}

				--len;
			}

			if (swap1 < 0)
				sort(nums.begin(), nums.end());
			else {
				int tmp = nums[swap2];
				nums[swap2] = nums[swap1];
				nums[swap1] = tmp;

				sort(nums.begin() + swap1 + 1, nums.end());
			}
		}

		void nextPermutation(vector<int>& nums) {
			if (nums.size() <= 1)
				return;

			int index = nums.size() - 1;

			//try to find the first number larger than its left from right
			while (index > 0) {
				if (nums[index - 1] < nums[index])
					break;

				--index;
			}

			//whole array is descending
			if (index == 0)
				reversesort(nums, 0, nums.size() - 1);
			else {
				//nums[index - 1] < nums[index]
				int val = nums[index - 1];
				int j = nums.size() - 1;

				//find pos j to insert val
				while (j >= index) {
					if (nums[j] > val)
						break;

					--j;
				}

				nums[index - 1] = nums[j];
				nums[j] = val;
				//because [index, end) is already descending, just exchange the pairs
				//no need for sorting
				reversesort(nums, index, nums.size() - 1);
			}
		}

		void reversesort(vector<int>& nums, int start, int end) {
			if (start >= end)
				return;

			for (int i = start; i <= (start + (end - start) / 2); ++i) {
				int tmp = nums[i];
				nums[i] = nums[end + start - i];
				nums[end + start - i] = tmp;
			}
		}

		static void main() {
			auto_ptr<Solution31> test(new Solution31);
			vector<int> nums1 = { 5, 3, 8, 7, 6, 4 };
			test->nextPermutation(nums1);

			vector<int> nums2 = { 5, 1, 5, 5, 2 };
			test->nextPermutation(nums2);

			vector<int> nums3 = { 5, 1, 5, 5, 2 };

		}
	};
	/*31. Next Permutation end */


	/*22. Generate Parentheses (medium)
	Time = O(n!) 
	https://leetcode.com/problems/generate-parentheses/
	https://discuss.leetcode.com/topic/4485/concise-recursive-c-solution/2
	https://discuss.leetcode.com/topic/3474/an-iterative-method
	*/
	class Solution22 {
	public:
		vector<string> res;

		vector<string> generateParenthesis(int n) {
			string str;
			generate(n, 0, 0, str);

			return res;
		}

		void generate(int n, int left, int right, string str) {
			if (left == n && right == n)
				res.push_back(str);

			if (left < n)
				generate(n, left + 1, right, str + "(");

			if (right < n && right < left)
				generate(n, left, right + 1, str + ")");
		}

		vector<string> generateParenthesis1(int n) {
			vector<string> result;

			if (n < 1)
				return result;

			vector<vector<string>> f(n + 1);

			f[0].push_back("");

			for (int i = 1; i < n + 1; ++i) {
				for (int j = 0; j < i; ++j)
					for (auto item1 : f[j])
						for (auto item2 : f[i - j - 1])
							f[i].push_back("(" + item1 + ")" + item2);
			}

			return f[n];
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

			result.push_back("");
			vector<string> strmap = { "", "","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };

			for (auto item : digits) {
				if (item < '2' || item > '9')
					continue;

				string candidate = strmap[item - '0'];
				vector<string> tmp;

				for (auto front : result) {
					for (auto after : candidate)
						tmp.push_back(front + after);
				}

				result.swap(tmp);
			}

			return result;
		}
	};
	/*17. Letter Combinations of a Phone Number end */



	/*400. Nth Digit (easy)
	https://leetcode.com/problems/nth-digit/
	http://www.cnblogs.com/y119777/p/5882638.html
	*/
	class Solution400 {
	public:
		int findNthDigit(int n) {
			int bits = 1;
			long count = 9;

			while (n > bits * count) {
				n -= bits * count;
				++bits;
				count *= 10;
			}

			int start = count / 9;
			int idx = (n - 1) / bits;
			int offset = (n - 1) % bits;

			string str = to_string(start + idx);
			return str[offset] - '0';
		}

		static void main() {
			auto_ptr<Solution400> test(new Solution400);			
			int result;
			int n1 = 11;

			result = test->findNthDigit(n1);
			result = result;
		}
	};
	/*400. Nth Digit end */


	/*389. Find the Difference (easy)
	https://leetcode.com/problems/find-the-difference/
	*/
	class Solution389 {
	public:
		char findTheDifference(string s, string t) {
			char c = 0;

			for (auto item : s)
				c ^= item;

			for (auto item : t)
				c ^= item;

			return c;
		}
	};
	/*389. Find the Difference end */


	/*374. Guess Number Higher or Lower (easy)
	https://leetcode.com/problems/guess-number-higher-or-lower/
	https://discuss.leetcode.com/topic/51184/0ms-c-binary-search
	*/
	class Solution374 {
	public:
		int guessNumber(int n) {
			int low = 1, high = n;

			while (1) {
				int mid = low + (high - low) / 2;

				int res = 0;// guess(mid);
				if (0 == res)
					return mid;
				else if (1 == res)
					low = mid + 1;
				else
					high = mid - 1;
			}

			return 0;
		}
	};
	/*374. Guess Number Higher or Lower end */


	/*359. Logger Rate Limiter (easy)
	https://leetcode.com/problems/logger-rate-limiter/
	https://discuss.leetcode.com/topic/48359/short-c-java-python-bit-different
	*/
	class Logger {
	public:
		/** Initialize your data structure here. */
		Logger() {
		}

		/** Returns true if the message should be printed in the given timestamp, otherwise returns false.
		If this method returns false, the message will not be printed.
		The timestamp is in seconds granularity. */
		bool shouldPrintMessage(int timestamp, string message) {
			if (map.count(message)) {
				if (timestamp - map[message] >= 10) {
					map[message] = timestamp;
					return true;
				}

				return false;
			}
			else
				map[message] = timestamp;

			return true;
		}

		unordered_map<string, int> map;
	};
	/*359. Logger Rate Limiter end */


	/*346. Moving Average from Data Stream (easy)
	https://leetcode.com/problems/moving-average-from-data-stream/
	https://discuss.leetcode.com/topic/44113/java-o-1-using-deque
	*/
	class MovingAverage346 {
	public:
		/** Initialize your data structure here. */
		int m_total;
		int m_size;
		queue<int> nums;

		MovingAverage346(int size) {
			m_total = 0;
			m_size = size;
		}

		double next(int val) {
			if (nums.size() >= m_size) {
				m_total -= nums.front();
				nums.pop();
			}

			m_total += val;
			nums.push(val);

			return (double)m_total / nums.size();
		}

		static void main() {
			MovingAverage346* test = new MovingAverage346(3);
			double result;

			result = test->next(1);		//output 1
			result = test->next(10);	//output (1 + 10) / 2
			result = test->next(3);		//output (1 + 10 + 3) / 3
			result = test->next(5);		//output (10 + 3 + 5) / 3
			delete test;
		}
	};
	/*346. Moving Average from Data Stream end */


	/*345. Reverse Vowels of a String (easy)
	https://leetcode.com/problems/reverse-vowels-of-a-string/
	https://discuss.leetcode.com/topic/53760/compare-three-java-solutions
	*/
	class Solution345 {
	public:
		bool isvowel(char c) {
			if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
				c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
				return true;

			return false;
		}

		string reverseVowels(string s) {
			string result(s);

			int low = 0, high = s.size() - 1;

			while (low < high) {
				while (low < high && !isvowel(result[low]))
					++low;

				while (low < high && !isvowel(result[high]))
					--high;

				if (high <= low)
					break;

				swap(result[low], result[high]);
				++low;
				--high;
			}

			return result;
		}
	};
	/*345. Reverse Vowels of a String end */


	/*326. Power of Three (easy)
	https://leetcode.com/problems/power-of-three/
	https://discuss.leetcode.com/topic/43385/c-solution-no-loop-recursion
	*/
	class Solution326 {
	public:
		bool isPowerOfThree(int n) {
			if (n < 1)
				return false;

			int t = pow(3, (int)(log(INT_MAX) / log(3)));
			return (t%n == 0);
		}
	};
	/*326. Power of Three end */


	/*293. Flip Game (easy)
	https://leetcode.com/problems/flip-game/
	https://discuss.leetcode.com/topic/27190/8-lines-c-7-lines-python
	*/
	class Solution293 {
	public:
		vector<string> generatePossibleNextMoves(string s) {
			vector<string> result;

			if (s.empty())
				return result;

			for (int i = 0; i < s.size() - 1; ++i) {
				if ('+' == s[i] && '+' == s[i + 1]) {
					s[i] = s[i + 1] = '-';
					result.push_back(s);
					s[i] = s[i + 1] = '+';
				}
			}

			return result;
		}
	};
	/*293. Flip Game end */


	/*288. Unique Word Abbreviation (easy)
	https://leetcode.com/problems/unique-word-abbreviation/
	https://discuss.leetcode.com/topic/25929/8-lines-in-c
	*/
	class ValidWordAbbr288 {
	public:
		ValidWordAbbr288(vector<string> &dictionary) {
			for (auto item : dictionary) {
				string key;
				int len = item.size();

				key = item[0] + to_string(len) + item[len - 1];
				map[key].insert(item);
			}
		}

		bool isUnique(string word) {
			if (word.empty() || map.empty())
				return true;

			string key;
			int len = word.size();

			key = word[0] + to_string(len) + word[len - 1];

			return map.count(key) && (map[key].count(word) == map[key].size());
		}

		static void main() {
			vector<string> dic1;
			vector<string> dic2 = { "a", "a" };
			ValidWordAbbr288* test1 = new ValidWordAbbr288(dic1);
			ValidWordAbbr288* test2 = new ValidWordAbbr288(dic2);
			bool result;

			string word1_1("");
			string word1_2("a");

			result = test1->isUnique(word1_1);
			result = test1->isUnique(word1_2);

			string word2_1("a");
			string word2_2("aa");

			result = test2->isUnique(word2_1);
			result = test2->isUnique(word2_2);
			delete test1;
			delete test2;
		}

		unordered_map<string, unordered_set<string>> map;
	};
	/*288. Unique Word Abbreviation end */


	/*276. Paint Fence (easy)
	https://leetcode.com/problems/paint-fence/
	https://discuss.leetcode.com/topic/23463/lucas-formula-maybe-o-1-and-3-4-liners
	*/
	class Solution276 {
	public:
		int numWays(int n, int k) {
			vector<int> dp(n + 1, 0);

			if (1 == n)
				return k;
			else if (2 == n)
				return k * k;

			dp[1] = k;
			dp[2] = k * k;

			for (int i = 3; i <= n; ++i)
				dp[i] = (dp[i - 1] + dp[i - 2]) * (k - 1);

			return dp[n];
		}

		static void main() {
			Solution276* test = new Solution276;
			int result;
			int n1 = 4, k1 = 2;
			result = test->numWays(n1, k1);

			delete test;
		}
	};
	/*276. Paint Fence end */


	/*270. Closest Binary Search Tree Value (easy)
	https://leetcode.com/problems/closest-binary-search-tree-value/
	*/
	class Solution270 {
	public:
		int closestValue(TreeNode* root, double target) {
			stack<TreeNode*> nodes;
			double diff = std::numeric_limits<double>::max();

			nodes.push(root);
			int result = root->val;
			while (!nodes.empty()) {
				TreeNode* cur = nodes.top();
				nodes.pop();
				double tmp = abs(double(cur->val) - target);
				if (tmp <= diff) {
					diff = tmp;
					result = cur->val;
				}

				if (target < cur->val) {
					if (cur->left)
						nodes.push(cur->left);
				}
				else {
					if (cur->right)
						nodes.push(cur->right);
				}
			}

			return result;
		}

		int closestValue1(TreeNode* root, double target) {
			int closest = root->val;
			double diff = std::numeric_limits<double>::max();

			while (root) {
				double tmp = abs(double(root->val) - target);
				if (diff >= tmp) {
					closest = root->val;
					diff = tmp;
				}

				root = target < root->val ? root->left : root->right;
			}
			return closest;
		}

		int closestValue3(TreeNode* root, double target) {
			int a = root->val;
			auto kid = target < root->val ? root->left : root->right;

			if (!kid)
				return a;

			int b = closestValue(kid, target);
			return abs(double(a) - target) > abs(double(b) - target) ? b : a;
		}

		static void main() {
			Solution270* test = new Solution270;
			int result;
			TreeNode node1(1);
			TreeNode node2(2);

			node1.right = &node2;
			result = test->closestValue(&node1, 3.415f);
			delete test;
		}
	};
	/*270. Closest Binary Search Tree Value end */


	/*266. Palindrome Permutation (easy)
	https://leetcode.com/problems/palindrome-permutation/
	https://discuss.leetcode.com/topic/21999/1-4-lines-python-ruby-c-c-java
	*/
	class Solution266 {
	public:
		bool canPermutePalindrome(string s) {
			unordered_map<char, int> map;

			for (auto it : s)
				++map[it];

			int odds = 0;
			for (auto it : map)
				odds += (it.second % 2);

			return odds < 2;
		}
	};
	/*266. Palindrome Permutation end */


	/*257. Binary Tree Paths (easy)
	https://leetcode.com/problems/binary-tree-paths/
	https://discuss.leetcode.com/topic/21559/python-solutions-dfs-stack-bfs-queue-dfs-recursively
	*/
	class Solution257 {
	public:
		void dfs(TreeNode* root, string path, vector<string>& result) {
			if (nullptr == root)
				return;

			path += to_string(root->val);

			if (nullptr == root->left && nullptr == root->right)
				result.push_back(path);
			else {
				dfs(root->left, path + "->", result);
				dfs(root->right, path + "->", result);
			}
		}

		vector<string> binaryTreePaths(TreeNode* root) {
			vector<string> result;

			dfs(root, "", result);

			return result;
		}
	};
	/*257. Binary Tree Paths end */


	/*249. Group Shifted Strings (easy)
	https://leetcode.com/problems/group-shifted-strings/
	https://discuss.leetcode.com/topic/20823/4ms-easy-c-solution-with-explanations
	*/
	class Solution249 {
	public:
		bool check(const string& str1, const string& str2) {
			if (str1.size() != str2.size())
				return false;

			int dif1, dif2;
			for (int i = 1; i < str1.size(); ++i) {
				dif1 = (str1[i] + 26 - str1[i - 1]) % 26;
				dif2 = (str2[i] + 26 - str2[i - 1]) % 26;

				if (dif1 != dif2)
					return false;
			}

			return true;
		}

		vector<vector<string>> groupStrings(vector<string>& strings) {
			vector<vector<string>> result;
			unordered_map<string, vector<string>> map;

			for (auto item : strings) {
				if (map.empty())
					map[item].push_back(item);
				else {
					bool found = false;
					for (auto it = map.begin(); it != map.end(); ++it) {
						if (check(it->first, item)) {
							map[it->first].push_back(item);
							found = true;
							break;
						}
					}

					if (!found)
						map[item].push_back(item);
				}
			}

			for (auto it : map)
				result.push_back(it.second);

			return result;
		}

		vector<vector<string>> groupStrings1(vector<string>& strings) {
			unordered_map<string, vector<string>> map;
			vector<vector<string>> result;

			for (auto item : strings)
				map[shift(item)].push_back(item);

			for (auto item : map)
				result.push_back(item.second);


			return result;
		}

		string shift(const string& str) {
			string result;

			for (int i = 1; i < str.size(); ++i)
				result += 'a' + ((str[i] + 26 - str[i - 1]) % 26);

			return result;
		}
		static void main() {
			Solution249* test = new Solution249;
			vector<vector<string>> result;

			vector<string> strings1 = { "abc", "bcd", "acef", "xyz", "az", "ba", "a", "z" };
			result = test->groupStrings(strings1);
			delete test;
		}
	};
	/*249. Group Shifted Strings end */


	/*246. Strobogrammatic Number (easy)
	https://leetcode.com/problems/strobogrammatic-number/
	*/
	class Solution246 {
	public:
		bool isStrobogrammatic1(string num) {
			int low = 0, high = num.size() - 1;
			unordered_map<char, char> map;

			map['0'] = '0';
			map['8'] = '8';
			map['1'] = '1';
			map['6'] = '9';
			map['9'] = '6';

			while (low < high) {
				char a = num[low];
				char b = num[high];

				if (!map.count(a) || map[a] != b)
					return false;

				++low;
				--high;
			}

			return high < low || '0' == num[low] || '1' == num[low] || '8' == num[low];
		}

		bool isStrobogrammatic(string num) {
			int low = 0, high = num.size() - 1;

			if (low == high)
				return '0' == num[0] || '1' == num[0] || '8' == num[0];

			while (low <= high) {
				switch (num[low])
				{
				case '0':
				case '1':
				case '8':
					if (num[high] != num[low])
						return false;
					break;

				case '6':
					if ('9' != num[high])
						return false;
					break;

				case '9':
					if ('6' != num[high])
						return false;
					break;

				default:
					return false;
				}

				++low;
				--high;
			}

			return true;
		}
	};
	/*246. Strobogrammatic Number end */


	/*231. Power of Two (easy)
	https://leetcode.com/problems/power-of-two/
	https://discuss.leetcode.com/topic/17857/using-n-n-1-trick
	*/
	class Solution231 {
	public:
		bool isPowerOfTwo(int n) {
			int count = 0;

			if (n <= 0)
				return false;

			for (int i = 0; i < 8 * sizeof(int); ++i) {
				if (n & (1 << i))
					++count;

				if (count > 1)
					return false;
			}

			return true;
		}

		static void main() {
			Solution231* test = new Solution231;
			bool result;
			int n1 = 1;
			int n2 = 3;
			int n3 = 16;

			result = test->isPowerOfTwo(n1);
			result = test->isPowerOfTwo(n2);
			result = test->isPowerOfTwo(n3);
			delete test;
		}
	};
	/*231. Power of Two end */


	/*155. Min Stack (easy)
	https://leetcode.com/problems/min-stack/
	https://discuss.leetcode.com/topic/36246/c-concise-solution-with-explanation
	https://discuss.leetcode.com/topic/52709/c-6-lines-solution-beat-all
	*/
	class MinStack155_1 {
	public:
		stack<pair<int, int>> stk;
		int  minval;
		MinStack155_1() {

		}

		void push(int x) {
			if (stk.empty()) stk.push(make_pair(x, x));
			else stk.push(make_pair(x, min(x, stk.top().second)));
		}

		void pop() {
			stk.pop();
		}

		int top() {
			return stk.top().first;
		}

		int getMin() {
			return stk.top().second;
		}

		static void main() {
			MinStack155_1* test = new MinStack155_1;

			test->push(2);
			test->push(0);
			test->push(3);

			cout << "MinStack155:" << test->top() << "," << test->getMin() << endl;
			test->pop();

			cout << "MinStack155:" << test->top() << "," << test->getMin() << endl;
			test->pop();

			cout << "MinStack155:" << test->top() << "," << test->getMin() << endl;
			test->pop();
			//cout << "MinStack155:" << test->top() << "," << test->getMin() << endl;
			delete test;
		}
	};


	class MinStack155 {
	public:
		stack<int> nums;
		stack<int> minstack;
		MinStack155() {

		}

		void push(int x) {
			nums.push(x);
			// if x == currentMin, also push x to minStack
			// because when popping, x == currentMin will be
			// popped
			if (minstack.empty() || minstack.top() >= x)
				minstack.push(x);
		}

		void pop() {
			if (nums.top() == minstack.top())
				minstack.pop();
			
			nums.pop();
		}

		int top() {
			return nums.top();
		}

		int getMin() {
			return minstack.top();
		}

		static void main() {
			MinStack155* test = new MinStack155;

			test->push(2);
			test->push(0);
			test->push(3);

			cout << "MinStack155:" << test->top() << "," << test->getMin() << endl;
			test->pop();

			cout << "MinStack155:" << test->top() << "," << test->getMin() << endl;
			test->pop();

			cout << "MinStack155:" << test->top() << "," << test->getMin() << endl;
			test->pop();
			//cout << "MinStack155:" << test->top() << "," << test->getMin() << endl;
			delete test;
		}
	};
	/*155. Min Stack end */


	/*66. Plus One (easy)
	https://leetcode.com/problems/plus-one/
	https://discuss.leetcode.com/topic/4556/is-it-a-simple-code-c
	*/
	class Solution66 {
	public:
		vector<int> plusOne(vector<int>& digits) {
			vector<int> result(digits);
			int n = result.size();

			for (int i = n - 1; i >= 0; --i) {
				if (result[i] < 9) {
					++result[i];
					return result;
				}
				else
					result[i] = 0;
			}

			result[0] = 0;
			result.insert(result.begin(), 1);
			return result;
		}

		static void main() {
			Solution66* test = new Solution66;
			vector<int> result;

			vector<int> digits1 = { 0 };
			result = test->plusOne(digits1);

			vector<int> digits2 = { 9, 9 };
			result = test->plusOne(digits2);

			vector<int> digits3 = { 9, 8, 9 };
			result = test->plusOne(digits3);
			delete test;
		}
	};
	/*66. Plus One end */


	/*20. Valid Parentheses (easy)
	https://leetcode.com/problems/valid-parentheses/
	https://discuss.leetcode.com/topic/13231/2ms-c-sloution
	*/
	class Solution20 {
	public:
		bool isValid(string s) {
			stack<char> parents;

			for (int i = 0; i < s.size(); ++i) {
				char tmp = s[i];
				if ('(' == tmp || '[' == tmp || '{' == tmp)
					parents.push(tmp);
				else if ((')' == tmp) && !parents.empty() && ('(' == parents.top()))
					parents.pop();
				else if ((']' == tmp) && !parents.empty() && ('[' == parents.top()))
					parents.pop();
				else if (('}' == tmp) && !parents.empty() && ('{' == parents.top()))
					parents.pop();
				else
					return false;
			}

			return parents.empty();
		}
	};
	/*20. Valid Parentheses end */


	static void main() {
		int a = -2;
		int b = a >> 1;
		int c = a >> 0;
		Solution224::main();
		Solution400::main();
		Solution31::main();
		Solution363::main();
		Solution340::main();
		Solution336::main();
		Solution327::main();
		Solution321::main();
		Solution317::main();
		Solution282::main();
		Solution272::main();
		Solution269::main();
		Solution212::main();
		LRUCache146::main();
		Solution140::main();
		Solution57::main();
		Solution44::main();
		PhoneDirectory379::main();
		Solution388::main();
		Solution378::main();
		Solution361::main();
		Solution356::main();
		Solution332::main();
		Solution324::main();
		Solution294::main();
		ZigzagIterator281_2::main();
		Solution253::main();
		Solution200::main();
		Solution377::main();
		Solution286::main();
		SnakeGame353::main();
		Solution313::main();
		Solution270::main();
		Solution249::main();
		Solution276::main();
		MovingAverage346::main();
		Solution231::main();
		MinStack155_1::main();
		MinStack155::main();
		ValidWordAbbr288::main();
		Solution66::main();
		
	}
}
//////////////////////////Tag GG//////////////////////////////////////////


//////////////////////////Tag Array//////////////////////////////////////////
namespace ARRAY {
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	/*41. First Missing Positive (medium)
	https://leetcode.com/problems/first-missing-positive/
	https://discuss.leetcode.com/topic/8293/my-short-c-solution-o-1-space-and-o-n-time
	*/
	class Solution41 {
	public:
		int firstMissingPositive(vector<int>& nums) {
			if (nums.size() < 1)
				return 1;

			int result = 0;
			int n = nums.size();

			for (int i = 0; i < n; ++i) {
				while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
					swap(nums[i], nums[nums[i] - 1]);
			}

			for (int i = 0; i < n; ++i) {
				if (nums[i] != i + 1)
					return i + 1;
			}

			return n + 1;
		}
	};
	/*41. First Missing Positive end */


	/*154. Find Minimum in Rotated Sorted Array II (hard)
	https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
	https://discuss.leetcode.com/topic/6468/my-pretty-simple-code-to-solve-it
	*/
	class Solution154 {
	public:
		int findMin(vector<int>& nums) {
			int low = 0;
			int high = nums.size() - 1;
			int mid;

			while (low < high) {
				mid = low + (high - low) / 2;
				if (nums[mid] > nums[high])
					low = mid + 1;
				else if (nums[mid] < nums[high])
					high = mid;
				else
					--high;
			}

			return nums[low];
		}
	};
	/*154. Find Minimum in Rotated Sorted Array II end */


	/*228. Summary Ranges (medium)
	https://leetcode.com/problems/summary-ranges/
	https://discuss.leetcode.com/topic/17151/accepted-java-solution-easy-to-understand
	*/
	class Solution228 {
	public:
		vector<string> summaryRanges(vector<int>& nums) {
			vector<string> result;
			string tmp;
			int nLen = nums.size();
			char temp[32];

			if (nLen == 1) {
				sprintf(temp, "%d", nums[0]);
				tmp.append(temp);
				result.push_back(tmp);
			}

			if (nLen <= 1)
				return result;

			int step;
			for (int nIdx = 0; nIdx < nLen; nIdx += step) {
				memset(temp, 0x00, sizeof(temp));
				sprintf(temp, "%d", nums[nIdx]);
				tmp = temp;

				step = 1;
				while (nIdx + step < nLen && nums[nIdx + step - 1] + 1 == nums[nIdx + step])
					step++;

				if (step > 1) {
					memset(temp, 0x00, sizeof(temp));
					sprintf(temp, "%d", nums[nIdx + step - 1]);
					tmp.append(string("->") + temp);
				}

				result.push_back(tmp);
			}

			return result;
		}
	};
	/*228. Summary Ranges end */


	/*238. Product of Array Except Self (medium)
	https://leetcode.com/problems/product-of-array-except-self/
	https://discuss.leetcode.com/topic/18864/simple-java-solution-in-o-n-without-extra-space
	*/
	class Solution238 {
	public:
		vector<int> productExceptSelf(vector<int>& nums) {
			vector<int> result(nums.size(), 1);
			int tmp;

			for (int nIdx = 0, tmp = 1; nIdx < nums.size(); ++nIdx) {
				result[nIdx] = tmp;
				tmp *= nums[nIdx];
			}

			for (int nIdx = nums.size() - 1, tmp = 1; nIdx >= 0; --nIdx) {
				result[nIdx] *= tmp;
				tmp *= nums[nIdx];
			}

			return result;
		}
	};
	/*238. Product of Array Except Self end */


	/*48. Rotate Image (medium)
	https://leetcode.com/problems/rotate-image/
	https://discuss.leetcode.com/topic/6796/a-common-method-to-rotate-the-image
	*/
	class Solution48 {
	public:
		void rotate(vector<vector<int>>& matrix) {
			reverse(matrix.begin(), matrix.end());

			for (int i = 0; i < matrix.size(); ++i)
				for (int j = i; j < matrix.size(); ++j)
					swap(matrix[i][j], matrix[j][i]);
		}
	};
	/*48. Rotate Image end */


	/*31. Next Permutation (medium)
	https://leetcode.com/problems/next-permutation/
	https://discuss.leetcode.com/topic/2542/share-my-o-n-time-solution
	*/
	class Solution31 {
	public:
		void nextPermutation1(vector<int>& nums) {
			if (nums.size() <= 1)
				return;

			int len = nums.size() - 1, start;
			int swap1 = -1, swap2;
			while (len >= 0) {
				for (start = len - 1; start >= 0; --start) {
					if (nums[len] > nums[start])
						break;
				}

				if (start >= 0 && start > swap1) {
					swap1 = start;
					swap2 = len;
				}

				--len;
			}

			if (swap1 < 0)
				sort(nums.begin(), nums.end());
			else {
				int tmp = nums[swap2];
				nums[swap2] = nums[swap1];
				nums[swap1] = tmp;

				sort(nums.begin() + swap1 + 1, nums.end());
			}
		}


		void nextPermutation(vector<int>& nums) {
			if (nums.size() <= 1)
				return;

			int index = nums.size() - 1;

			while (index > 0) {
				if (nums[index - 1] < nums[index])
					break;

				--index;
			}

			if (index == 0)
				reversesort(nums, 0, nums.size() - 1);
			else {
				int val = nums[index - 1];
				int j = nums.size() - 1;

				while (j >= index) {
					if (nums[j] > val)
						break;

					--j;
				}

				nums[index - 1] = nums[j];
				nums[j] = val;

				reversesort(nums, index, nums.size() - 1);
			}
		}

		void reversesort(vector<int>& nums, int start, int end)
		{
			if (start >= end)
				return;

			for (int i = start; i <= (start + (end - start) / 2); ++i) {
				int tmp = nums[i];
				nums[i] = nums[end + start - i];
				nums[end + start - i] = tmp;
			}
		}
	};
	/*31. Next Permutation end */


	/*34. Search for a Range (medium)
	https://leetcode.com/problems/search-for-a-range/
	https://discuss.leetcode.com/topic/5891/clean-iterative-solution-with-two-binary-searches-with-explanation
	*/
	class Solution34 {
	public:
		int findvec(vector<int>& nums, int target) {
			int low = 0, high = nums.size() - 1;
			int mid;

			while (low <= high) {
				mid = low + ((high - low) >> 2);
				if (nums[mid] == target)
					return mid;

				if (target > nums[mid])
					low = mid + 1;
				else
					high = mid - 1;
			}

			return -1;
		}

		vector<int> searchRange(vector<int>& nums, int target) {
			if (nums.empty())
				return vector<int>(2, -1);

			int found = findvec(nums, target);

			if (found == -1)
				return vector<int>(2, -1);

			vector<int> result(2, 0);

			int left = found;
			int right = found;
			//while (left >= 0 && nums[left--] == target);
			for (int i = found - 1; i >= 0; --i) {
				if (nums[i] == target)
					left = i;
				else
					break;
			}

			for (int i = found + 1; i < nums.size(); ++i) {
				if (nums[i] == target)
					right = i;
				else
					break;
			}

			result[0] = left;
			result[1] = right;

			return result;
		}
	};
	/*34. Search for a Range end */


	/*73. Set Matrix Zeroes (medium)
	https://leetcode.com/problems/set-matrix-zeroes/
	https://discuss.leetcode.com/topic/5056/any-shorter-o-1-space-solution/2
	https://discuss.leetcode.com/topic/5056/any-shortest-o-1-space-solution
	*/
	class Solution73 {
	public:
		void setZeroes(vector<vector<int>>& matrix) {
			if (matrix.empty() || matrix[0].empty())
				return;

			int col0 = 1;
			int row = matrix.size();
			int col = matrix[0].size();

			for (int i = 0; i < row; ++i) {
				if (matrix[i][0] == 0) col0 = 0;
				for (int j = 1; j < col; ++j) {
					if (0 == matrix[i][j])
						matrix[i][0] = matrix[0][j] = 0;
				}
			}

			for (int i = row - 1; i >= 0; i--) {
				for (int j = col - 1; j >= 1; j--)
					if (matrix[i][0] == 0 || matrix[0][j] == 0)
						matrix[i][j] = 0;
				if (col0 == 0) matrix[i][0] = 0;
			}
		}

		void setZeroes1(vector<vector<int>>& matrix) {
			if (matrix.empty() || matrix[0].empty())
				return;

			int m = matrix.size();
			int n = matrix[0].size();

			unordered_map<int, int> indexR;
			unordered_map<int, int> indexC;

			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < n; ++j) {
					if (matrix[i][j] == 0) {
						indexR[i] = 1;
						indexC[j] = 1;
					}
				}
			}

			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < n; ++j) {
					if (indexR[i] == 1 || indexC[j] == 1)
						matrix[i][j] = 0;
				}
			}
		}
	};
	/*73. Set Matrix Zeroes end */


	/*289. Game of Life (medium)
	https://leetcode.com/problems/game-of-life/
	https://discuss.leetcode.com/topic/29054/easiest-java-solution-with-explanation
	*/
	class Solution289 {
	public:
		void gameOfLife(vector<vector<int>>& board) {
			int m = board.size();
			int n = m ? board[0].size() : 0;
			int count;

			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j) {
					count = 0;
					for (int row = max(i - 1, 0); row < min(i + 2, m); ++row)
						for (int col = max(j - 1, 0); col < min(j + 2, n); ++col)
							count += board[row][col] & 1;

					if (count == 3 || count - board[i][j] == 3)
						board[i][j] |= 2;
				}

			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j)
					board[i][j] >>= 1;
		}
	};
	/*289. Game of Life end */


	/*105. Construct Binary Tree from Preorder and Inorder Traversal (medium)
	https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
	https://discuss.leetcode.com/topic/3695/my-accepted-java-solution
	*/
	class Solution105 {
	public:
		int finditem(vector<int> invec, int low, int high, int target) {
			for (int i = low; i <= high; ++i) {
				if (invec[i] == target)
					return i;
			}
		}

		TreeNode* buildTree(vector<int>& preorder, int prelow, int prehigh, vector<int>& inorder, int inlow, int inhigh) {
			TreeNode* root = new TreeNode(preorder[prelow]);
			if (prelow == prehigh)
				return root;

			int index = finditem(inorder, inlow, inhigh, preorder[prelow]);
			int leftnum = index - inlow;
			int rightnum = inhigh - index;


			if (leftnum > 0)
				root->left = buildTree(preorder, prelow + 1, prelow + leftnum, inorder, inlow, index - 1);

			if (rightnum > 0)
				root->right = buildTree(preorder, prelow + leftnum + 1, prehigh, inorder, index + 1, inhigh);

			return root;
		}

		TreeNode* buildTree1(vector<int>& preorder, vector<int>& inorder) {
			if (preorder.empty() || preorder.size() != inorder.size())
				return NULL;

			return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
		}

		TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
			if (preorder.empty() || preorder.size() != inorder.size())
				return NULL;

			int i = 0, j = 0;
			TreeNode root(0x80000000);
			stack<TreeNode*> nodes;
			nodes.push(&root);
			TreeNode *pp = NULL, *ptr = &root;

			while (j < inorder.size()) {
				if (nodes.top()->val == inorder[j]) {
					pp = nodes.top();
					nodes.pop();
					j++;
				}
				else if (pp) {
					ptr = new TreeNode(preorder[i]);
					pp->right = ptr;
					pp = NULL;
					nodes.push(ptr);
					++i;
				}
				else {
					ptr = new TreeNode(preorder[i]);
					nodes.top()->left = ptr;
					nodes.push(ptr);
					++i;
				}
			}

			TreeNode* result = root.left;
			return result;
		}
	};
	/*105. Construct Binary Tree from Preorder and Inorder Traversal end */


	/*81. Search in Rotated Sorted Array II (medium)
	https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
	https://discuss.leetcode.com/topic/8087/c-concise-log-n-solution
	*/
	class Solution81 {
	public:
		bool search(vector<int>& nums, int target) {
			int low = 0;
			int high = nums.size() - 1;
			int mid;

			while (low <= high) {
				mid = low + (high - low) / 2;

				if (nums[mid] == target)
					return true;

				if (nums[mid] > nums[low]) {
					if (target >= nums[low] && target < nums[mid])
						high = mid - 1;
					else
						low = mid + 1;
				}
				else if (nums[mid] < nums[low]) {
					if (target <= nums[high] && target > nums[mid])
						low = mid + 1;
					else
						high = mid - 1;
				}
				else
					++low;
			}

			return false;
		}
	};
	/*81. Search in Rotated Sorted Array II end */


	/*216. Combination Sum III (medium)
	https://leetcode.com/problems/combination-sum-iii/
	https://discuss.leetcode.com/topic/14641/my-c-solution-backtracking
	*/
	class Solution216 {
	public:
		void combinationSum(vector<vector<int>>&result, vector<int> cur, int k, int n) {
			if (cur.size() == k && n == 0) {
				result.push_back(cur);
				return;
			}

			if (cur.size() < k) {
				for (int i = (cur.size() > 0 ? cur.back() + 1 : 1); i <= 9; ++i) {
					if (n - i < 0)
						break;
					cur.push_back(i);
					combinationSum(result, cur, k, n - i);
					cur.pop_back();
				}
			}
		}

		vector<vector<int>> combinationSum3(int k, int n) {
			vector<int> cur;
			vector<vector<int>> result;

			combinationSum(result, cur, k, n);

			return result;
		}
	};
	/*216. Combination Sum III end */


	/*229. Majority Element II (medium)
	https://leetcode.com/problems/majority-element-ii/
	https://discuss.leetcode.com/topic/17564/boyer-moore-majority-vote-algorithm-and-my-elaboration
	*/
	class Solution229 {
	public:
		vector<int> majorityElement(vector<int>& nums) {
			int num1 = 0, num2 = 0, a1 = 0, a2 = 1;

			for (auto item : nums) {
				if (item == a1)
					num1++;
				else if (item == a2)
					num2++;
				else if (num1 == 0) {
					a1 = item;
					num1 = 1;
				}
				else if (num2 == 0) {
					a2 = item;
					num2 = 1;
				}
				else {
					--num1;
					--num2;
				}
			}

			num1 = 0;
			num2 = 0;

			for (auto item : nums) {
				if (item == a1)
					++num1;
				else if (item == a2)
					++num2;
			}

			vector<int> ret;

			if (num1 > (nums.size() / 3))
				ret.push_back(a1);

			if (num2 > (nums.size() / 3))
				ret.push_back(a2);

			return ret;
		}
	};
	/*229. Majority Element II end */


	/*59. Spiral Matrix II (medium)
	https://leetcode.com/problems/spiral-matrix-ii/
	https://discuss.leetcode.com/topic/7282/simple-c-solution-with-explaination
	*/
	class Solution59 {
	public:
		vector<vector<int>> generateMatrix(int n) {
			vector<vector<int>> result(n, vector<int>(n));
			int k = 1;
			int total = n * n;
			int i = 0, j;

			while (k <= total) {
				j = i;
				while (j < n - i) {
					result[i][j] = k++;
					j++;
				}

				j = i + 1;
				while (j < n - i)
					result[j++][n - i - 1] = k++;

				j = n - i - 2;
				while (j > i)
					result[n - i - 1][j--] = k++;

				j = n - i - 1;
				while (j > i)
					result[j--][i] = k++;

				++i;
			}

			return result;
		}
	};
	/*59. Spiral Matrix II end */


	/*40. Combination Sum II (medium)
	https://leetcode.com/problems/combination-sum-ii/
	https://discuss.leetcode.com/topic/19845/java-solution-using-dfs-easy-understand
	*/
	class Solution40 {
	public:
		vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
			sort(candidates.begin(), candidates.end());
			vector<vector<int> > res;
			vector<int> combination;
			combinationSum(candidates, target, res, combination, 0);
			return res;
		}

		void combinationSum(std::vector<int> &candidates, int target, std::vector<std::vector<int> > &res, std::vector<int> &combination, int begin) {
			if (0 == target) {
				res.push_back(combination);
				return;
			}

			for (int i = begin; i != candidates.size() && target >= candidates[i]; ++i) {
				if (i && candidates[i - 1] == candidates[i] && i > begin)
					continue;

				combination.push_back(candidates[i]);
				combinationSum(candidates, target - candidates[i], res, combination, i + 1);
				combination.pop_back();
			}
		}

		void dsf(vector<int>& candidates, int target, int start, vector<vector<int>>& ret, vector<int>& locaret) {
			if (target == 0) {
				ret.push_back(locaret);
				return;
			}

			for (int i = start; i < candidates.size(); ++i) {
				if (candidates[i] > target)
					return;

				if (i && candidates[i - 1] == candidates[i] && i > start)
					continue;

				locaret.push_back(candidates[i]);
				dsf(candidates, target - candidates[i], i + 1, ret, locaret);
				locaret.pop_back();
			}
		}

		vector<vector<int>> combinationSum2_1(vector<int>& candidates, int target) {
			vector<vector<int>> result;
			vector<int> localret;

			sort(candidates.begin(), candidates.end());
			if (candidates.empty() || target < candidates[0])
				return result;

			dsf(candidates, target, 0, result, localret);
			return result;
		}
	};
	/*40. Combination Sum II end */


	/*153. Find Minimum in Rotated Sorted Array (medium)
	https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
	https://discuss.leetcode.com/topic/4100/compact-and-clean-c-solution
	*/
	class Solution153 {
	public:
		int findMin(vector<int>& nums) {
			int low = 0, high = nums.size() - 1;
			int middle;

			while (low < high) {
				middle = (low + high) / 2;

				if (nums[middle] > nums[high])
					low = middle + 1;
				else if (nums[middle] < nums[high])
					high = middle;
			}

			return nums[low];
		}
	};
	/*153. Find Minimum in Rotated Sorted Array end */


	/*106. Construct Binary Tree from Inorder and Postorder Traversal (medium)
	https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
	*/
	class Solution106 {
	public:
		int finditem(vector<int>& nodes, int low, int high, int target) {
			for (int i = low; i <= high; ++i) {
				if (nodes[i] == target)
					return i;
			}
		}

		TreeNode* buildTree(vector<int>& inorder, int instart, int inend, vector<int>& postorder, int poststart, int posend) {
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

		TreeNode* myBuild2(vector<int>& inorder, vector<int>& postorder, TreeNode* lastnode) {
			if (posPost < 0)
				return NULL;

			TreeNode* node = new TreeNode(postorder[posPost--]);

			if (inorder[posIn] != node->val)
				node->right = myBuild2(inorder, postorder, node);

			posIn--;

			if ((lastnode == NULL) || (inorder[posIn] != lastnode->val))
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
	};
	/*106. Construct Binary Tree from Inorder and Postorder Traversal end */


	/*209. Minimum Size Subarray Sum (medium)
	https://leetcode.com/problems/minimum-size-subarray-sum/
	https://discuss.leetcode.com/topic/13749/two-ac-solutions-in-java-with-time-complexity-of-n-and-nlogn-with-explanation
	*/
	class Solution209 {
	public:
		int minSubArrayLen1(int s, vector<int>& nums) {
			if (nums.empty())
				return 0;

			int ret = 0, total, j, len;

			for (int i = 0; i < nums.size(); ++i) {
				total = 0;
				for (j = i; j < nums.size(); ++j) {
					if (total + nums[j] < s)
						total += nums[j];
					else
						break;
				}

				len = j - i + 1;
				if (j < nums.size() && total + nums[j] >= s)
					ret = min(ret == 0 ? len : ret, len);
			}

			return ret;
		}

		int minSubArrayLen(int s, vector<int>& nums) {
			if (nums.empty())
				return 0;
			int ret = INT_MAX, total = 0, start = 0, end = 0, len;

			while (end < nums.size()) {
				while (end < nums.size() && total < s)
					total += nums[end++];

				if (total < s)
					break;

				while (start < end && total >= s)
					total -= nums[start++];

				if (end - start + 1 < ret)
					ret = end - start + 1;
			}

			return ret == INT_MAX ? 0 : ret;
		}
	};
	/*209. Minimum Size Subarray Sum end */


	/*27. Remove Element (easy)
	https://leetcode.com/problems/remove-element/
	https://discuss.leetcode.com/topic/1228/my-solution-for-your-reference
	*/
	class Solution27 {
	public:
		int removeElement(int A[], int n, int elem) {
			int count = 0;
			for (int i = 0; i<n; ++i) {
				if (A[i] != elem)
					A[count++] = A[i];
			}

			return count;
		}
	};
	/*27. Remove Element end */


	/*119. Pascal's Triangle II (easy)
	https://leetcode.com/problems/pascals-triangle-ii/
	https://discuss.leetcode.com/topic/2510/here-is-my-brief-o-k-solution
	*/
	class Solution119 {
	public:
		vector<int> getRow(int rowIndex) {
			vector<int> result;
			result.resize(rowIndex + 1);
			result[0] = result[rowIndex] = 1;

			for (int i = 1; i <= rowIndex / 2; ++i)
				result[i] = result[rowIndex - i] = (unsigned long)result[i - 1] * (unsigned long)(rowIndex + 1 - i) / i;

			return result;
		}
	};
	/*119. Pascal's Triangle II end */


	/*118. Pascal's Triangle (easy)
	https://leetcode.com/problems/pascals-triangle/
	https://discuss.leetcode.com/topic/4303/maybe-shortest-c-solution
	*/
	class Solution118 {
	public:
		vector<vector<int>> generate(int numRows) {
			vector<vector<int>> result(numRows);

			for (int i = 0; i < numRows; ++i) {
				result[i].resize(i + 1);

				result[i][0] = result[i][i] = 1;
				for (int j = 1; j < i; ++j)
					result[i][j] = result[i - 1][j - 1] + result[i - 1][j];
			}

			return result;
		}
	};
	/*118. Pascal's Triangle end */


	/*189. Rotate Array (easy)
	https://leetcode.com/problems/rotate-array/
	https://discuss.leetcode.com/topic/9801/summary-of-c-solutions
	*/
	class Solution189 {
	public:
		void rotate(vector<int>& nums, int k) {
			int offset = nums.size() - (k % nums.size());
			
			vector<int> t(nums.begin() + offset, nums.end());
			nums.resize(offset);
			nums.insert(nums.begin(), t.begin(), t.end());
		}
	};
	/*189. Rotate Array end */


	/*26. Remove Duplicates from Sorted Array (easy)
	https://leetcode.com/problems/remove-duplicates-from-sorted-array/
	*/
	class Solution26 {
	public:
		int removeDuplicates(vector<int>& nums) {
			int len = nums.size();

			if (len < 2)
				return len;

			int count = 0;
			for (int i = 0; i < len; ++i) {
				if (nums[i] != nums[count])
					nums[++count] = nums[i];
			}

			return count + 1;
		}
	};
	/*26. Remove Duplicates from Sorted Array end */
}
//////////////////////////Tag Array end//////////////////////////////////////////



//////////////////////////Tag Hash Table//////////////////////////////////////////
namespace HASHT {
	/*380. Insert Delete GetRandom O(1) (medium)
	https://leetcode.com/problems/insert-delete-getrandom-o1/
	https://discuss.leetcode.com/topic/53216/java-solution-using-a-hashmap-and-a-arraylist-131-ms
	*/
	class RandomizedSet380 {
	public:
		/** Initialize your data structure here. */
		RandomizedSet380() {

		}

		/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
		bool insert(int val) {
			if (m.find(val) != m.end()) return false;
			nums.emplace_back(val);
			m[val] = nums.size() - 1;
			return true;
		}

		/** Removes a value from the set. Returns true if the set contained the specified element. */
		bool remove(int val) {
			if (m.find(val) == m.end()) 
				return false;

			int last = nums.back();
			m[last] = m[val];
			nums[m[val]] = last;
			nums.pop_back();
			m.erase(val);
			return true;
		}

		/** Get a random element from the set. */
		int getRandom() {
			int n = nums.size();

			return  0 == n ? -1 : nums[rand() % n];
		}

	private:
		vector<int> nums;
		unordered_map<int, int> m;
	};
	/*380. Insert Delete GetRandom O(1) end */


	/*219. Contains Duplicate II (easy)
	https://leetcode.com/problems/contains-duplicate-ii/
	https://discuss.leetcode.com/topic/15045/c-solution-with-unordered_set
	*/
	class Solution219 {
	public:
		bool containsNearbyDuplicate(vector<int>& nums, int k) {
			set<int> cand;

			for (int nIdx = 0; nIdx < nums.size(); ++nIdx) {
				if (nIdx > k)
					cand.erase(nums[nIdx - k - 1]);
				
				//pair<iterator,bool> insert (value_type&& val);
				if (!cand.insert(nums[nIdx]).second)
					return true;
			}

			return false;
		}
	};
	/*219. Contains Duplicate II end */


	/*36. Valid Sudoku (easy)
	https://leetcode.com/problems/valid-sudoku/
	https://discuss.leetcode.com/topic/8241/my-short-solution-by-c-o-n2
	*/
	class Solution36 {
	public:
		bool isValidSudoku(vector<vector<char>>& board) {
			int use1[9][9] = { 0 };
			int use2[9][9] = { 0 };
			int use3[9][9] = { 0 };
			int k, num;

			for (int i = 0; i < 9; ++i)
				for (int j = 0; j < board[i].size(); ++j) {
					if (board[i][j] != '.') {
						num = board[i][j] - '1';
						k = i / 3 * 3 + j / 3;

						if (use1[i][num] || use2[j][num] || use3[k][num])
							return false;

						use1[i][num] = 1;
						use2[j][num] = 1;
						use3[k][num] = 1;
					}
				}

			return true;
		}
	};
	/*36. Valid Sudoku end */


	/*290. Word Pattern (easy)
	https://leetcode.com/problems/word-pattern/
	https://leetcode.com/problems/word-pattern/
	https://discuss.leetcode.com/topic/26376/short-c-read-words-on-the-fly
	*/
	class Solution290 {
	public:
		bool wordPattern(string pattern, string str) {
			map<char, int> patoi;
			map<string, int> strtoi;

			istringstream in(str);
			int i = 0;
			int n = pattern.size();
			for (string word; in >> word; ++i) {
				if (i == n || patoi[pattern[i]] != strtoi[word])
					return false;

				patoi[pattern[i]] = strtoi[word] = i + 1;
			}

			return i == n;
		}
	};
	/*290. Word Pattern end */


	/*1. Two Sum (easy)
	https://leetcode.com/problems/two-sum/
	https://discuss.leetcode.com/topic/3294/accepted-c-o-n-solution
	*/
	class Solution1 {
	public:
		vector<int> twoSum(vector<int>& nums, int target) {
			unordered_map<int, int> value_index;
			vector<int> result;

			for (int i = 0; i < nums.size(); ++i) {
				if (value_index.count(target - nums[i])) {
					result.push_back(value_index[target - nums[i]]);
					result.push_back(i + 1);
					break;
				}

				value_index[nums[i]] = i + 1;
			}

			return result;
		}
	};
	/*1. Two Sum end */


	/*217. Contains Duplicate (easy)
	https://leetcode.com/problems/contains-duplicate/
	https://discuss.leetcode.com/topic/14944/single-line-c-solution-60ms
	*/
	class Solution217 {
	public:
		bool containsDuplicate(vector<int>& nums) {
			if ((nums.size() == 0) || (nums.size() == 1)) return false;

			std::sort(nums.begin(), nums.end());

			for (int nIdx = 0; nIdx<nums.size() - 1; ++nIdx)
				if (nums[nIdx] == nums[nIdx + 1])
					return true;

			return false;
		}
	};
	/*217. Contains Duplicate end */


	/*205. Isomorphic Strings (easy)
	https://leetcode.com/problems/isomorphic-strings/
	https://discuss.leetcode.com/topic/12981/my-6-lines-solution
	*/
	class Solution205 {
	public:
		bool isIsomorphic(string a, string b) {
			if (a.size() != b.size()) 
				return false;

			vector<char> aTob(128, NULL);
			vector<char> bToa(128, NULL);

			for (int i = 0; i < a.size(); ++i) {
				if (!aTob[a[i]] && !bToa[b[i]]) {
					aTob[a[i]] = b[i];
					bToa[b[i]] = a[i];
				}
				else if (aTob[a[i]] != b[i] || bToa[b[i]] != a[i])
					return false;
			}

			return true;
		}
	};
	/*205. Isomorphic Strings end */


	/*299. Bulls and Cows (easy)
	https://leetcode.com/problems/bulls-and-cows/
	https://discuss.leetcode.com/topic/28463/one-pass-java-solution
	*/
	class Solution29 {
	public:
		string getHint(string secret, string guess) {
			string result;
			vector<int> gcount(10, 0);
			vector<int> scount(10, 0);
			int bull = 0, cows = 0;

			if (secret.empty() || guess.empty())
				return string("0A0B");

			for (int i = 0; i < secret.size(); ++i) {
				if (secret[i] == guess[i])
					bull++;
				else {
					scount[secret[i] - '0'] ++;
					gcount[guess[i] - '0'] ++;
				}
			}

			for (int i = 0; i < 10; ++i)
				cows += (scount[i] > gcount[i] ? gcount[i] : scount[i]);

			char tmp[100];

			memset(tmp, 0x00, sizeof(tmp));
			sprintf(tmp, "%dA%dB", bull, cows);
			result = string(tmp);

			return result;
		}
	};
	/*299. Bulls and Cows end */

}

//////////////////////////Tag Hash Table end//////////////////////////////////////////




//////////////////////////Tag Linked List//////////////////////////////////////////
namespace LLIST {
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};


	/*25. Reverse Nodes in k-Group (hard)
	https://leetcode.com/problems/reverse-nodes-in-k-group/
	https://discuss.leetcode.com/topic/7126/short-but-recursive-java-code-with-comments
	*/
	class Solution25 {
	public:
		ListNode* reverseKGroup(ListNode* head, int k) {
			if (head == NULL || head->next == NULL || k < 2)
				return head;

			ListNode dummy(-1);
			dummy.next = head;
			ListNode* pre = &dummy;
			ListNode* tmp = NULL;
			ListNode* next = NULL;
			ListNode* curr = head;
			int count = 0;

			while (curr) {
				++count;
				curr = curr->next;
			}

			while (count >= k) {
				curr = pre->next;
				next = curr->next;

				for (int i = 1; i < k; ++i) {
					tmp = next->next;
					next->next = pre->next;
					pre->next = next;
					curr->next = tmp;
					next = tmp;
				}

				pre = curr;
				count -= k;
			}

			return dummy.next;
		}
	};
	/*25. Reverse Nodes in k-Group end */


	/*23. Merge k Sorted Lists (hard)
	https://leetcode.com/problems/merge-k-sorted-lists/
	https://discuss.leetcode.com/topic/6882/sharing-my-straightforward-c-solution-without-data-structure-other-than-vector
	*/
	class Solution23 {
	public:
		ListNode *mergeTwoLists(ListNode* l1, ListNode* l2) {
			if (NULL == l1) 
				return l2;

			else if (NULL == l2) 
				return l1;

			if (l1->val <= l2->val) {
				l1->next = mergeTwoLists(l1->next, l2);
				return l1;
			}
			else {
				l2->next = mergeTwoLists(l1, l2->next);
				return l2;
			}
		}

		ListNode *mergeKLists(vector<ListNode *> &lists) {
			if (lists.empty()) 
				return NULL;

			int len = lists.size();
			while (len > 1) {
				for (int i = 0; i < len / 2; ++i)
					lists[i] = mergeTwoLists(lists[i], lists[len - 1 - i]);

				len = (len + 1) / 2;
			}

			return lists.front();
		}

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

		ListNode* mergeKLists1(vector<ListNode*>& lists) {
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


	/*138. Copy List with Random Pointer (hard)
	https://leetcode.com/problems/copy-list-with-random-pointer/
	https://discuss.leetcode.com/topic/53289/c-o-n-time-complexity-o-1-space
	*/
	struct RandomListNode {
		int label;
		RandomListNode *next, *random;
		RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
	};

	class Solution138 {
	public:
		RandomListNode *copyRandomList(RandomListNode *head) {
			if (head == NULL)
				return NULL;

			unordered_map<RandomListNode *, int> map;
			unordered_map<int, RandomListNode *> destmap;
			RandomListNode *phead = NULL;
			RandomListNode *p1;
			RandomListNode *p2;
			RandomListNode dummy(0);

			p2 = &dummy;
			int count = 0;
			for (p1 = head; p1 != NULL; p1 = p1->next) {
				RandomListNode *tmp = new RandomListNode(p1->label);

				destmap[count] = tmp;
				map[p1] = count++;
				p2->next = tmp;
				p2 = p2->next;
			}

			count = 0;
			phead = dummy.next;
			p2 = phead;
			for (p1 = head; p1 != NULL; p1 = p1->next) {
				if (p1->random != NULL) {
					int tmp = map[p1->random];
					p2->random = destmap[tmp];
				}

				p2 = p2->next;
			}

			return phead;
		}
	};
	/*138. Copy List with Random Pointer end */


	/*82. Remove Duplicates from Sorted List II (medium)
	https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
	https://discuss.leetcode.com/topic/51656/short-c-iterative-solution-using-dummy
	*/
	class Solution82 {
	public:
		ListNode* deleteDuplicates(ListNode* head) {
			ListNode dummy(0);
			ListNode* ptmp = &dummy;
			bool duplicate;

			while (head) {
				duplicate = false;
				while (head->next && head->next->val == head->val) {
					head = head->next;
					duplicate = true;
				}

				if (!duplicate) {
					ptmp->next = head;
					ptmp = ptmp->next;
				}

				head = head->next;
			}

			ptmp->next = NULL;
			return dummy.next;
		}
	};
	/*82. Remove Duplicates from Sorted List II end */


	/*92. Reverse Linked List II (medium)
	https://leetcode.com/problems/reverse-linked-list-ii/
	https://discuss.leetcode.com/topic/53273/clean-yet-efficient-solution-in-c
	*/
	class Solution92 {
	public:
		ListNode* reverseBetween1(ListNode* head, int m, int n) {
			if (m == n)
				return head;

			ListNode root(0);
			ListNode* pre = &root;
			ListNode* cur = head;
			ListNode* next = NULL;

			root.next = head;
			int pos = 1;

			while (pos < n) {
				if (pos < m) {
					pre = cur;
					cur = cur->next;
				}
				else {
					next = cur->next;
					cur->next = cur->next->next;
					next->next = pre->next;
					pre->next = next;
				}

				++pos;
			}

			return root.next;
		}


		ListNode* reverseBetween(ListNode* head, int m, int n) {
			stack<ListNode*> nodes;
			ListNode root(0);
			ListNode* father = &root;

			int count = 1;
			ListNode* reverfather = NULL;
			while (head && count <= n) {
				if (count >= m) {
					nodes.push(head);
					if (count == m)
						reverfather = father;
				}

				father->next = head;
				father = head;
				head = head->next;
				count++;
			}

			if (nodes.size() > 1) {
				ListNode* tmp = nodes.top()->next;

				while (!nodes.empty()) {
					reverfather->next = nodes.top();
					nodes.pop();
					reverfather = reverfather->next;
				}

				reverfather->next = tmp;
			}

			return root.next;
		}
	};
	/*92. Reverse Linked List II end */


	/*328. Odd Even Linked List (medium)
	https://leetcode.com/problems/odd-even-linked-list/
	https://discuss.leetcode.com/topic/50295/sharing-my-16-ms-cpp-solution-beats-99-54
	*/
	class Solution328 {
	public:
		ListNode* oddEvenList(ListNode* head) {
			if (head == NULL)
				return NULL;

			ListNode* oddnode = head;
			ListNode* evennode = head->next;
			ListNode* evenhead = evennode;

			while (evennode != NULL && evennode->next != NULL) {
				oddnode->next = oddnode->next->next;
				evennode->next = evennode->next->next;
				evennode = evennode->next;
				oddnode = oddnode->next;
			}

			oddnode->next = evenhead;
			return head;
		}
	};
	/*328. Odd Even Linked List end */


	/*143. Reorder List (medium)
	https://leetcode.com/problems/reorder-list/
	https://discuss.leetcode.com/topic/53032/accept-answer-in-c-using-stack
	*/
	class Solution143 {
	public:
		void reorderList(ListNode* head) {
			if (NULL == head)
				return;

			stack<ListNode*> nodes;
			ListNode* tmp = head;
			int count = 0;

			while (tmp) {
				nodes.push(tmp);
				tmp = tmp->next;
				++count;
			}

			tmp = head;
			for (int i = 0; i < count / 2; ++i) {
				ListNode* end = nodes.top();
				nodes.pop();
				ListNode* next = tmp->next;

				tmp->next = end;
				end->next = next;
				tmp = next;
			}

			tmp->next = NULL;
		}
	};
	/*143. Reorder List end */


	/*83. Remove Duplicates from Sorted List (easy)
	https://leetcode.com/problems/remove-duplicates-from-sorted-list/
	https://discuss.leetcode.com/topic/8345/my-pretty-solution-java
	*/
	class Solution83 {
	public:
		ListNode *deleteDuplicates(ListNode *head) {
			if (head == NULL) 
				return head;

			ListNode* cur = head;
			while (cur->next != NULL) {
				if (cur->val == cur->next->val) {
					ListNode* tmp = cur->next;
					cur->next = tmp->next;
					delete tmp;
				}
				else cur = cur->next;
			}

			return head;
		}
	};
	/*83. Remove Duplicates from Sorted List end */


	/*203. Remove Linked List Elements (easy)
	https://leetcode.com/problems/remove-linked-list-elements/
	https://discuss.leetcode.com/topic/52063/easy-c-solution
	*/
	class Solution203 {
	public:
		ListNode* removeElements(ListNode* head, int val) {
			ListNode node(0);
			node.next = head;
			ListNode* cur = &node;

			while (cur->next) {
				ListNode* entry = cur->next;

				if (entry->val == val) {
					cur->next = entry->next;
					delete entry;
				}
				else
					cur = cur->next;
			}

			return node.next;
		}

		ListNode* removeElements1(ListNode* head, int val) {
			ListNode* root = head;
			ListNode* result = head;
			ListNode* pre = head;
			while (root) {
				if (root->val == val) {
					if (result == root) {
						result = root->next;
						pre = result;
					}
					else
						pre->next = root->next;
				}
				else
					pre = root;

				root = root->next;
			}

			return result;
		}
	};
	/*203. Remove Linked List Elements end */


	/*206. Reverse Linked List (easy)
	https://leetcode.com/problems/reverse-linked-list/
	https://discuss.leetcode.com/topic/52949/simple-5-liner-in-java
	*/
	class Solution206 {
	public:
		ListNode* reverseList(ListNode* head) {
			ListNode* root = head;
			ListNode* pre = NULL;

			while (root) {
				ListNode* tmp = root->next;
				root->next = pre;

				pre = root;
				root = tmp;
			}

			return pre;
		}
	};
	/*206. Reverse Linked List end */


	/*160. Intersection of Two Linked Lists (easy)
	https://leetcode.com/problems/intersection-of-two-linked-lists/
	https://discuss.leetcode.com/topic/50006/simple-yet-best-solution-in-c/2
	*/
	class Solution160 {
	public:
		ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
		{
			ListNode *pA = headA, *pB = headB;
			int lenA = 0, lenB = 0;
			while (pA) 
				pA = pA->next, lenA++;

			while (pB) 
				pB = pB->next, lenB++;

			pA = headA, pB = headB;
			if (lenA > lenB) 
				for (int i = 0; i < lenA - lenB; ++i) 
					pA = pA->next;
			else 
				for (int i = 0; i < lenB - lenA; ++i) 
					pB = pB->next;

			while (pA)
			{
				if (pA == pB) return pA;
				pA = pA->next;
				pB = pB->next;
			}

			return NULL;
		}

		ListNode *getIntersectionNode1(ListNode *headA, ListNode *headB) {
			if (headA == NULL || headB == NULL)
				return NULL;

			ListNode *headAEnd = NULL;
			ListNode *headAStart = headA;
			while (headAStart) {
				headAEnd = headAStart;
				headAStart = headAStart->next;
			}

			headAEnd->next = headB;
			ListNode * fast = headA->next;
			ListNode * slow = headA;

			while (1) {
				if (fast == slow)
					break;

				if (fast == NULL || slow == NULL || fast->next == NULL) {
					headAEnd->next = NULL;
					return NULL;
				}

				fast = fast->next->next;
				slow = slow->next;
			}

			int loopsize = 1;
			fast = fast->next;

			while (fast != slow) {
				fast = fast->next;
				loopsize++;
			}

			fast = headA;
			slow = headA;
			for (int i = 0; i < loopsize; ++i)
				fast = fast->next;

			while (fast != slow) {
				fast = fast->next;
				slow = slow->next;
			}

			headAEnd->next = NULL;
			return fast;
		}
	};
	/*160. Intersection of Two Linked Lists end */


	/*21. Merge Two Sorted Lists (easy)
	https://leetcode.com/problems/merge-two-sorted-lists/
	https://discuss.leetcode.com/topic/39228/1ms-java-clean-code
	*/
	class Solution21 {
	public:
		ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
			if ((NULL == l1) || (NULL == l2))
				return (NULL == l1) ? l2 : l1;

			ListNode head = ListNode(0);
			ListNode* curr = &head;

			while (l1 && l2) {
				if (l1->val < l2->val) {
					curr->next = l1;
					l1 = l1->next;
				}
				else {
					curr->next = l2;
					l2 = l2->next;
				}

				curr = curr->next;
			}

			if (l1 == NULL)
				curr->next = l2;

			if (l2 == NULL)
				curr->next = l1;

			return head.next;
		}
	};
	/*21. Merge Two Sorted Lists end */


	/*237. Delete Node in a Linked List (easy)
	https://leetcode.com/problems/delete-node-in-a-linked-list/
	https://discuss.leetcode.com/topic/51739/2-solutions
	*/
	class Solution237 {
	public:
		void deleteNode(ListNode* node) {
			ListNode* temp = node->next;
			*node = *temp;
			delete temp;
		}
	};
	/*237. Delete Node in a Linked List end */


	/*24. Swap Nodes in Pairs (easy)
	https://leetcode.com/problems/swap-nodes-in-pairs/
	https://discuss.leetcode.com/topic/53021/maybe-the-most-easy-to-understand-one
	*/
	class Solution24 {
	public:
		ListNode* swapPairs(ListNode* head) {
			ListNode node(0);
			node.next = head;

			ListNode* cur = &node;
			while (cur->next && cur->next->next) {
				ListNode* node1 = cur->next;
				ListNode* node2 = node1->next;
				ListNode* node3 = node2->next;

				node2->next = node1;
				node1->next = node3;
				cur->next = node2;
				cur = node1;
			}

			return node.next;
		}

		ListNode* swapPairs1(ListNode* head) {
			if ((head == NULL) || (head->next == NULL))
				return head;

			ListNode* pNewHead = head->next;
			ListNode* pPair1 = head;
			ListNode* pPair2 = head->next;

			while (pPair1 && pPair2) {
				head->next = pPair2;
				ListNode* pTmp = pPair2->next;
				pPair2->next = pPair1;

				pPair1->next = pTmp;
				head = pPair1;
				pPair1 = pTmp;
				pPair2 = pPair1 ? pPair1->next : NULL;
			}

			return pNewHead;
		}

		static void main() {
			Solution24* test = new Solution24;
			ListNode* result;
			ListNode node1(1);
			ListNode node2(2);
			ListNode node3(3);

			node1.next = &node2;
			node2.next = &node3;

			result = test->swapPairs(&node1);
			delete test;
		}
	};
	/*24. Swap Nodes in Pairs end */
}
//////////////////////////Tag Linked List end//////////////////////////////////////////



//////////////////////////Tag Math//////////////////////////////////////////
namespace MATH {
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};


	/*149. Max Points on a Line (hard)
	https://leetcode.com/problems/max-points-on-a-line/
	https://discuss.leetcode.com/topic/52957/really-think-hash-map-with-floating-point-is-awkward-as-the-input-data-is-integer-only-my-solution-is-o-n-3-with-pruning-12ms-and-beat-94
	*/
	struct Point {
		int x;
		int y;
		Point() : x(0), y(0) {}
		Point(int a, int b) : x(a), y(b) {}
	};

	class Solution149 {
	public:
		int maxPoints(vector<Point>& points) {
			if (points.size() < 2)
				return points.size();

			int result = 0;
			for (int i = 0; i < points.size(); ++i) {
				map<pair<int, int>, int> dict;
				int localmax = 0, vertical = 0, overlap = 0;

				for (int j = i + 1; j < points.size(); ++j) {
					if (points[i].x == points[j].x && points[i].y == points[j].y) {
						++overlap;
						continue;
					}
					else if (points[i].x == points[j].x)
						++vertical;
					else {
						int a = points[j].x - points[i].x;
						int b = points[j].y - points[i].y;
						int gcd = GCD(a, b);

						a = a / gcd;
						b = b / gcd;

						dict[make_pair(a, b)] ++;
						localmax = max(localmax, dict[make_pair(a, b)]);
					}

					localmax = max(localmax, vertical);
				}

				result = max(result, localmax + overlap + 1);
			}

			return result;
		}

		int GCD(int a, int b) {
			if (b == 0) return a;
			else return GCD(b, a%b);
		}

		static void main() {
			Solution149* test = new Solution149;
			int result;
			vector<Point> points1 = { Point(4, 4), Point(2, 2), Point(8, 8) };

			result = test->maxPoints(points1);
			delete test;
		}
	};
	/*149. Max Points on a Line end */


	/*65. Valid Number (hard)
	https://leetcode.com/problems/valid-number/
	https://discuss.leetcode.com/topic/51867/solution-using-a-state-machine
	*/
	class Solution65 {
	public:
		bool isNumber(string s) {
			int state = 0, flag = 0;

			while (s[0] == ' ')
				s.erase(0, 1);

			while (s[s.size() - 1] == ' ')
				s.erase(s.size() - 1, 1);

			for (int i = 0; i < s.size(); ++i) {
				if (isdigit(s[i])) {
					flag = 1;

					if (state <= 2)
						state = 2;
					else
						state = (state <= 5) ? 5 : 7;
				}
				else if (s[i] == '+' || s[i] == '-') {
					if (state == 0 || state == 3)
						state++;
					else
						return false;
				}
				else if (s[i] == '.') {
					if (state <= 2)
						state = 6;
					else
						return false;
				}
				else if (s[i] == 'e') {
					if (flag && (state == 2 || state == 6 || state == 7))
						state = 3;
					else
						return false;
				}
				else
					return false;
			}

			return (state == 2 || state == 5 || (flag&&state == 6) || state == 7);
		}
	};
	/*65. Valid Number end */


	/*335. Self Crossing (hard)
	https://leetcode.com/problems/self-crossing/
	https://discuss.leetcode.com/topic/50325/more-intuitive-explanation-added-here
	*/
	class Solution335 {
	public:
		bool isSelfCrossing(vector<int>& x) {
			for (int i = 3; i < x.size(); ++i) {
				if (x[i] >= x[i - 2] && x[i - 1] <= x[i - 3])
					return true;
				else if (i > 3 && x[i - 4] + x[i] == x[i - 2] && x[i - 1] == x[i - 3])
					return true;
				else if (i > 4 && x[i - 2] >= x[i - 4] && x[i] + x[i - 4] >= x[i - 2]
					&& x[i - 3] >= x[i - 1] && x[i - 1] + x[i - 5] >= x[i - 3])
					return true;
			}

			return false;
		}
	};
	/*335. Self Crossing end */


	/*233. Number of Digit One (hard)
	https://leetcode.com/problems/number-of-digit-one/
	https://discuss.leetcode.com/topic/18054/4-lines-o-log-n-c-java-python
	*/
	class Solution233 {
	public:
		int countDigitOne(int n) {
			int ones = 0;

			for (long long m = 1; m <= n; m *= 10) {
				int a = n / m, b = n % m;
				ones += (a + 8) / 10 * m + (a % 10 == 1) * (b + 1);
			}

			return ones;
		}
	};
	/*233. Number of Digit One end */


	/*2. Add Two Numbers (medium)
	https://leetcode.com/problems/add-two-numbers/
	https://discuss.leetcode.com/topic/5905/c-sharing-my-11-line-c-solution-can-someone-make-it-even-more-concise
	*/
	class Solution2 {
	public:
		ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
			ListNode preHead(0), *p = &preHead;
			int extra = 0;

			while (l1 || l2 || extra) {
				int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + extra;
				extra = sum / 10;
				p->next = new ListNode(sum % 10);
				p = p->next;
				l1 = l1 ? l1->next : l1;
				l2 = l2 ? l2->next : l2;
			}

			return preHead.next;
		}

		ListNode* addTwoNumbers1(ListNode* l1, ListNode* l2) {
			int carry = 0;

			ListNode* sb = new ListNode(0);
			ListNode* result = sb;
			int val_1, val_2, val;

			while (l1 || l2) {
				val_1 = l1 ? l1->val : 0;
				val_2 = l2 ? l2->val : 0;

				if (val_1 + val_2 + carry >= 10) {
					val = val_1 + val_2 + carry - 10;
					carry = 1;
				}
				else {
					val = val_1 + val_2 + carry;
					carry = 0;
				}

				result->next = new ListNode(val);
				result = result->next;
				if (l1)
					l1 = l1->next;

				if (l2)
					l2 = l2->next;
			}

			if (carry)
				result->next = new ListNode(1);

			return sb->next;
		}
	};
	/*2. Add Two Numbers end */


	/*368. Largest Divisible Subset (medium)
	https://leetcode.com/problems/largest-divisible-subset/
	https://discuss.leetcode.com/topic/49456/c-solution-with-explanations
	*/
	class Solution368 {
	public:
		vector<int> largestDivisibleSubset(vector<int>& nums) {
			int nsize = nums.size();
			vector<int> dp(nsize, 0);
			vector<int> parent(nsize, 0);
			sort(nums.begin(), nums.end());

			int m = 0;
			int mi = 0;
			for (int i = nsize - 1; i >= 0; --i) {
				for (int j = i; j < nsize; ++j) {
					if (0 == nums[j] % nums[i] && dp[i] < dp[j] + 1) {
						dp[i] = dp[j] + 1;
						parent[i] = j;

						if (dp[i] > m) {
							m = dp[i];
							mi = i;
						}
					}
				}
			}

			vector<int> result;
			for (int i = 0; i < m; ++i) {
				result.push_back(nums[mi]);
				mi = parent[mi];
			}

			return result;
		}
	};
	/*368. Largest Divisible Subset end */


	/*365. Water and Jug Problem (medium)
	https://leetcode.com/problems/water-and-jug-problem/
	https://discuss.leetcode.com/topic/49238/math-solution-java-solution
	https://discuss.leetcode.com/topic/49238/math-solution-java-solution
	*/
	class Solution365 {
	public:
		int GCD(int a, int b){
			while (b != 0){
				int temp = b;
				b = a % b;
				a = temp;
			}
			return a;
		}

		bool canMeasureWater(int x, int y, int z) {
			return z == 0 || z <= (long long)x + y && z % GCD(x, y) == 0;
		}
	};
	/*365. Water and Jug Problem end */


	/*372. Super Pow (medium)
	https://leetcode.com/problems/super-pow/
	https://discuss.leetcode.com/topic/50489/c-clean-and-short-solution
	*/
	class Solution372 {
		const int base = 1337;
		int powmod(int a, int k) //a^k mod 1337 where 0 <= k <= 10
		{
			a %= base;
			int result = 1;
			for (int i = 0; i < k; ++i)
				result = (result * a) % base;
			return result;
		}

	public:
		int superPow(int a, vector<int>& b) {
			if (b.empty()) 
				return 1;

			int last_digit = b.back();
			b.pop_back();
			return powmod(superPow(a, b), 10) * powmod(a, last_digit) % base;
		}
	};
	/*372. Super Pow end */


	/*319. Bulb Switcher (medium)
	https://leetcode.com/problems/bulb-switcher/
	https://discuss.leetcode.com/topic/31929/math-solution
	*/
	class Solution319 {
	public:
		int bulbSwitch(int n) {
			int count = 0;

			for (int i = 1; i * i <= n; ++i)
				count++;

			return count;
		}
	};
	/*319. Bulb Switcher end */


	/*7. Reverse Integer (easy)
	https://leetcode.com/problems/reverse-integer/
	https://discuss.leetcode.com/topic/6104/my-accepted-15-lines-of-code-for-java
	*/
	class Solution7 {
	public:
		int reverse(int x) {
			if (INT_MIN == x)
				return 0;

			int num = (x > 0 ? x : -x);
			int tmp = 0;

			while (num > 0) {
				int a = num % 10;
				num /= 10;

				if ((INT_MAX - a) / 10 < tmp)
					return 0;

				tmp = tmp * 10 + a;
			}

			num = (x > 0 ? tmp : -tmp);
			return num;
		}
	};
	/*7. Reverse Integer end */


	/*326. Power of Three (easy)
	https://leetcode.com/problems/power-of-three/
	https://discuss.leetcode.com/topic/33536/a-summary-of-all-solutions-new-method-included-at-15-30pm-jan-8th
	*/
	class Solution326 {
	public:
		bool isPowerOfThree(int n) {
			if (n > 1) {
				while (n % 3 == 0) 
					n = n / 3;
			}

			return n == 1;
		}
	};
	/*326. Power of Three end */


	/*168. Excel Sheet Column Title (easy)
	https://leetcode.com/problems/excel-sheet-column-title/
	https://discuss.leetcode.com/topic/6214/my-1-lines-code-in-java-c-and-python
	*/
	class Solution168 {
	public:
		string convertToTitle(int n) {
			string result;

			while (n) {
				char tmp = 'A' + (n - 1) % 26;

				result.insert(0, string(1, tmp));
				n = (n - 1) / 26;
			}

			return result;
		}
	};
	/*168. Excel Sheet Column Title end */


	/*204. Count Primes (easy)
	https://leetcode.com/problems/count-primes/
	*/
	class Solution204 {
	public:
		/*
		bool isPrime(int n) {
			for (int i = 3; i * i <= n / 2; i=+2) {
				if ((n % i) == 0)
					return false;
			}

			return true;
		}

		int countPrimes(int n) {
			if (n <= 2)
				return 0;

			int count = 1;

			for (int i=0; i <= n; ++i) {
				if (isPrime(i))
					count ++;
			}

			return count;
		}
		*/

		int countPrimes(int n) {
			vector<bool> prime(n, true);
			prime[0] = false, prime[1] = false;

			for (int i = 0; i < sqrt(n); ++i) {
				if (prime[i]) {
					for (int j = i*i; j < n; j += i)
						prime[j] = false;
				}
			}

			return count(prime.begin(), prime.end(), true);
		}
	};
	/*204. Count Primes end */


	/*172. Factorial Trailing Zeroes (easy)
	https://leetcode.com/problems/factorial-trailing-zeroes/
	https://discuss.leetcode.com/topic/6516/my-one-line-solutions-in-3-languages
	*/
	class Solution172 {
	public:
		int trailingZeroes(int n) {
			int num = 0;

			while (n) {
				n /= 5;
				num += n;
			}

			return num;
		}
	};
	/*172. Factorial Trailing Zeroes end */


	/*171. Excel Sheet Column Number (easy)
	https://leetcode.com/problems/excel-sheet-column-number/
	https://discuss.leetcode.com/topic/6458/my-solutions-in-3-languages-does-any-one-have-one-line-solution-in-java-or-c
	*/
	class Solution171 {
	public:
		int titleToNumber(string s) {
			int nResult = 0;
			int nLen = s.size();

			for (int i = 0; i < nLen; ++i)
				nResult = nResult * 26 + (s[i] - 'A' + 1);

			return nResult;
		}
	};
	/*171. Excel Sheet Column Number end */


	/*223. Rectangle Area (easy)
	https://leetcode.com/problems/rectangle-area/
	https://discuss.leetcode.com/topic/17705/just-another-short-way
	*/
	class Solution223 {
	public:
		int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
			//B>=H or E>=C or F>=D or A>=G
			if (E >= C || A >= G || B >= H || F >= D)
				return (C - A)*(D - B) + (G - E) * (H - F);
			else
				return (C - A) * (D - B) + (G - E) * (H - F) - (min(C, G) - max(A, E)) * (min(D, H) - max(B, F));
		}
	};
	/*223. Rectangle Area end */


	/*202. Happy Number (easy)
	https://leetcode.com/submissions/detail/26100759/
	https://discuss.leetcode.com/topic/12587/my-solution-in-c-o-1-space-and-no-magic-math-property-involved
	*/
	class Solution202 {
	public:
		bool isHappy(int n) {
			unordered_set<int> result;
			int tmp;
			while (true) {
				if (n == 1)
					return true;

				if (result.count(n) == 1)
					return false;

				result.insert(n);
				tmp = 0;
				while (n > 0) {
					tmp += (n % 10) * (n % 10);
					n /= 10;
				}

				n = tmp;
			}
		}
	};
	/*202. Happy Number end */


	/*258. Add Digits (easy)
	https://leetcode.com/problems/add-digits/
	https://discuss.leetcode.com/topic/21498/accepted-c-o-1-time-o-1-space-1-line-solution-with-detail-explanations
	*/
	class Solution258 {
	public:
		int addDigits(int num) {
			int result = num;

			while (num > 9) {
				result = 0;
				while (num > 0) {
					result += (num % 10);
					num /= 10;
				}

				num = result;
			}

			return result;
		}
	};
	/*258. Add Digits end */


	/*9. Palindrome Number (easy)
	https://leetcode.com/problems/palindrome-number/
	https://discuss.leetcode.com/topic/12820/an-easy-c-8-lines-code-only-reversing-till-half-and-then-compare
	*/
	class Solution9 {
	public:
		bool isPalindrome(int x) {
			if (x < 0)
				return false;

			int div1 = x;
			int div2 = 0;
			while (x > 0) {
				div2 = div2 * 10 + (x % 10);
				x /= 10;
			}

			while (div1 > 0) {
				if ((div1 % 10) != (div2 % 10))
					return false;

				div1 /= 10;
				div2 /= 10;
			}

			return true;
		}
	};
	/*9. Palindrome Number end */


	/*66. Plus One (easy)
	https://leetcode.com/problems/plus-one/
	https://discuss.leetcode.com/topic/24288/my-simple-java-solution
	*/
	class Solution66 {
	public:
		vector<int> plusOne(vector<int>& digits) {
			vector<int> result;
			int tmp = 1, current;
			for (int i = 0; i < digits.size(); ++i) {
				if (digits[digits.size() - 1 - i] + tmp > 9) {
					current = 0;
					tmp = 1;
				}
				else {
					current = digits[digits.size() - 1 - i] + tmp;
					tmp = 0;
				}

				result.insert(result.begin(), current);
			}

			if (tmp == 1)
				result.insert(result.begin(), 1);

			return result;
		}
	};
	/*66. Plus One end */


	/*263. Ugly Number (easy)
	https://leetcode.com/problems/ugly-number/
	https://discuss.leetcode.com/topic/21785/2-4-lines-every-language
	*/
	class Solution263 {
	public:
		bool isUgly(int num) {
			if (num == 1)
				return true;

			if (num < 1)
				return false;

			while ((num % 2) == 0)
				num /= 2;

			while ((num % 3) == 0)
				num /= 3;

			while ((num % 5) == 0)
				num /= 5;

			return num == 1;
		}
	};
	/*263. Ugly Number end */
}
//////////////////////////Tag Math end//////////////////////////////////////////



//////////////////////////Tag Two Pointers//////////////////////////////////////////
namespace TWOP {

	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};


	/*287. Find the Duplicate Number (medium)
	https://leetcode.com/problems/find-the-duplicate-number/
	https://discuss.leetcode.com/topic/25913/my-easy-understood-solution-with-o-n-time-and-o-1-space-without-modifying-the-array-with-clear-explanation
	*/
	class Solution287 {
	public:
		int findDuplicate(vector<int>& nums) {
			if (nums.size() > 0) {
				int slow = nums[0];
				int fast = nums[nums[0]];

				while (fast != slow) {
					slow = nums[slow];
					fast = nums[nums[fast]];
				}

				fast = 0;
				while (fast != slow) {
					fast = nums[fast];
					slow = nums[slow];
				}

				return slow;
			}

			return -1;
		}
	};
	/*287. Find the Duplicate Number end */

	/*11. Container With Most Water (medium)
	https://leetcode.com/problems/container-with-most-water/
	https://discuss.leetcode.com/topic/503/anyone-who-has-a-o-n-algorithm/2
	https://discuss.leetcode.com/topic/3462/yet-another-way-to-see-what-happens-in-the-o-n-algorithm
	*/
	class Solution11 {
	public:
		int maxArea(vector<int>& height) {
			int water = 0;
			int i = 0, j = height.size() - 1;
			int h;

			while (i < j) {
				h = min(height[i], height[j]);

				water = max(water, (j - i)*h);

				while (height[i] <= h && i < j)
					++i;

				while (height[j] <= h && i < j)
					--j;
			}

			return water;
		}
	};
	/*11. Container With Most Water end */


	/*209. Minimum Size Subarray Sum (medium)
	https://leetcode.com/problems/minimum-size-subarray-sum/
	https://discuss.leetcode.com/topic/17063/4ms-o-n-8ms-o-nlogn-c
	*/
	class Solution209 {
	public:
		int minSubArrayLen(int s, vector<int>& nums) {
			if (nums.empty())
				return 0;

			int ret = INT_MAX, total = 0, start = 0, end = 0, len;

			while (end < nums.size()) {
				while (end < nums.size() && total < s)
					total += nums[end++];

				if (total < s)
					break;

				while (start < end && total >= s)
					total -= nums[start++];

				if (end - start + 1 < ret)
					ret = end - start + 1;
			}

			return ret == INT_MAX ? 0 : ret;
		}
	};
	/*209. Minimum Size Subarray Sum end */


	/*86. Partition List (medium)
	https://leetcode.com/problems/partition-list/
	https://discuss.leetcode.com/topic/7005/very-concise-one-pass-solution
	*/
	class Solution86 {
	public:
		ListNode* partition(ListNode* head, int x) {
			ListNode node1(0), node2(0);
			ListNode* p1 = &node1;
			ListNode* p2 = &node2;

			while (head) {
				if (head->val < x) {
					p1->next = head;
					p1 = p1->next;
				}
				else {
					p2->next = head;
					p2 = p2->next;
				}

				head = head->next;
			}

			p2->next = NULL;
			p1->next = node2.next;
			return node1.next;
		}
	};
	/*86. Partition List end */


	/* 80. Remove Duplicates from Sorted Array II(medium)
	https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
	https://discuss.leetcode.com/topic/17180/3-6-easy-lines-c-java-python-ruby
	*/
	class Solution80 {
	public:
		int removeDuplicates(vector<int>& nums) {
			int idx = 0;
			int len = nums.size();
			int count = 0;

			if (0 == len)
				return 0;

			for (int i = 1; i < len; ++i) {
				count = 0;

				while (i < len && nums[idx] == nums[i]) {
					++i;
					++count;
				}

				if (count > 0) {
					nums[idx + 1] = nums[idx];
					++idx;
				}

				if (i < len)
					nums[++idx] = nums[i];
			}

			return idx + 1;
		}
	};
	/*80. Remove Duplicates from Sorted Array II end */


	/*61. Rotate List (medium)
	https://leetcode.com/problems/rotate-list/
	https://discuss.leetcode.com/topic/14470/my-clean-c-code-quite-standard-find-tail-and-reconnect-the-list
	*/
	class Solution61 {
	public:
		ListNode* rotateRight(ListNode* head, int k) {
			ListNode* result = head;

			if (head == NULL || head->next == NULL || k == 0)
				return result;

			ListNode* p1 = head;
			ListNode* end = head;
			int count = 0;
			while (p1) {
				end = p1;
				p1 = p1->next;
				++count;
			}

			k = k % count;
			if (k == 0)
				return head;

			p1 = head;
			ListNode* pre = head;
			for (int i = 0; i < count - k; ++i) {
				pre = p1;
				p1 = p1->next;
			}

			result = p1;
			pre->next = NULL;
			end->next = head;
			return result;
		}
	};
	/*61. Rotate List end */


	/*142. Linked List Cycle II (medium)
	https://leetcode.com/problems/linked-list-cycle-ii/
	https://discuss.leetcode.com/topic/2975/o-n-solution-by-using-two-pointers-without-change-anything
	*/
	class Solution142 {
	public:
		ListNode *detectCycle(ListNode *head) {
			if (head == NULL)
				return NULL;

			ListNode* slow = head;
			ListNode* fast = head;
			bool bcycle = false;
			while (fast->next && fast->next->next) {
				slow = slow->next;
				fast = fast->next->next;

				if (slow == fast) {
					bcycle = true;
					break;
				}
			}

			if (!bcycle)
				return NULL;

			fast = head;
			while (fast != slow) {
				fast = fast->next;
				slow = slow->next;
			}

			return fast;
		}
	};
	/*142. Linked List Cycle II end */


	/*18. 4Sum (medium)
	https://leetcode.com/problems/4sum/
	https://discuss.leetcode.com/topic/28641/my-16ms-c-code
	*/
	class Solution18 {
	public:
		vector<vector<int>> m_ret;

		vector<vector<int>> fourSum1(vector<int>& nums, int target) {
			if (nums.empty() || nums.size() < 4)
				return m_ret;

			int n = nums.size();
			sort(nums.begin(), nums.end());

			for (int i = 0; i < n - 3; ++i) {
				if (i > 0 && nums[i] == nums[i - 1])
					continue;

				if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
					break;

				if (nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target)
					continue;

				for (int j = i + 1; j < n - 2; ++j) {
					if (j > i + 1 && nums[j] == nums[j - 1])
						continue;

					if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
						break;

					if (nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target)
						continue;

					int left = j + 1, right = n - 1;

					while (left < right) {
						int sum = nums[i] + nums[j] + nums[left] + nums[right];

						if (sum < target)
							left++;
						else if (sum > target)
							right--;
						else {
							m_ret.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
							do { --left; } while (nums[left] == nums[left - 1] && left < right);

							do { --right; } while (nums[right] == nums[right + 1] && left < right);
						}
					}
				}
			}

			return m_ret;
		}

		vector<vector<int>> fourSum(vector<int>& nums, int target) {
			if (nums.empty() || nums.size() < 4)
				return m_ret;

			int n = nums.size();
			sort(nums.begin(), nums.end());
			int i, j;
			for (i = 0; i < n; ++i)
			{
				int target_3 = target - nums[i];

				for (j = i + 1; j < n; ++j) {
					int target_2 = target_3 - nums[j];

					int front = j + 1;
					int back = n - 1;

					while (front < back) {
						int two_sum = nums[front] + nums[back];

						if (two_sum < target_2)
							++front;
						else if (two_sum > target_2)
							--back;
						else {
							vector<int> tmp{ nums[i],nums[j],nums[front],nums[back] };
							m_ret.push_back(tmp);

							while (front < back && nums[front] == tmp[2])
								++front;

							while (front < back && nums[back] == tmp[3])
								--back;
						}
					}

					while (j + 1 < n && nums[j + 1] == nums[j])
						++j;
				}

				while (i + 1 < n && nums[i + 1] == nums[i])
					++i;
			}

			return m_ret;
		}
	};
	/*18. 4Sum end */


	/*16. 3Sum Closest (medium)
	https://leetcode.com/problems/3sum-closest/
	https://discuss.leetcode.com/topic/1978/a-n-2-solution-can-we-do-better
	*/
	class Solution16 {
	public:
		int threeSumClosest(vector<int>& nums, int target) {
			if (nums.size() <= 3) {
				int result = 0;
				for (auto item : nums)
					result += item;
				return result;
			}

			sort(nums.begin(), nums.end());

			int lastsum = nums[0] + nums[1] + nums[2];
			int j, k, cur;
			int nitem = nums.size();
			for (int i = 0; i < nitem - 2; ++i) {
				j = i + 1;
				k = nitem - 1;

				while (j < k) {
					cur = nums[i] + nums[j] + nums[k];

					if (abs(target - lastsum) > abs(target - cur)) {
						lastsum = cur;
						if (lastsum == target)
							return target;
					}

					cur > target ? k-- : j++;
				}
			}

			return lastsum;
		}
	};
	/*16. 3Sum Closest end */


	/*15. 3Sum (medium)
	https://leetcode.com/problems/3sum/
	https://discuss.leetcode.com/topic/8107/share-my-ac-c-solution-around-50ms-o-n-n-with-explanation-and-comments
	*/
	class Solution15 {
	public:
		vector<vector<int>> threeSum(vector<int>& nums) {
			vector<vector<int>> ret;

			int len = nums.size();
			if (len < 3)
				return ret;

			sort(nums.begin(), nums.end());
			for (int i = 0; i < len; ++i) {
				int target = -nums[i];

				int low = i + 1;
				int high = len - 1;

				while (low < high) {
					int tmp = nums[low] + nums[high];
					if (target > tmp)
						++low;
					else if (tmp > target)
						--high;
					else {
						vector<int> vec = { nums[i], nums[low], nums[high] };

						ret.push_back(vec);

						//bypass same element for num[low]
						while (low < high && nums[low] == vec[1])
							++low;

						//bypass same element for num[high]
						while (low < high && nums[high] == vec[2])
							--high;
					}
				}

				//bypass same element for num[i]
				while (i + 1 < len && nums[i + 1] == nums[i])
					++i;
			}

			return ret;
		}
	};
	/*15. 3Sum end */


	/*234. Palindrome Linked List (easy)
	https://leetcode.com/problems/palindrome-linked-list/
	https://discuss.leetcode.com/topic/18304/share-my-c-solution-o-n-time-and-o-1-memory
	*/
	class Solution234 {
	public:
		bool isPalindrome(ListNode* head) {
			ListNode* pre = NULL;
			ListNode* slow = head;
			ListNode* fast = head;

			while (fast && fast->next) {
				ListNode* tmp = slow->next;
				fast = fast->next->next;

				slow->next = pre;
				pre = slow;
				slow = tmp;
			}

			//odd case
			if (fast)
				slow = slow->next;

			while (pre) {
				if (pre->val != slow->val)
					return false;

				pre = pre->next;
				slow = slow->next;
			}

			return true;
		}
	};
	/*234. Palindrome Linked List end */


	/*88. Merge Sorted Array (easy)
	https://leetcode.com/problems/merge-sorted-array/
	*/
	class Solution88 {
	public:
		void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
			int tar = m + n - 1, idx1 = m - 1, idx2 = n - 1;

			while (idx2 >= 0) {
				if (idx1 >= 0) {
					if (nums1[idx1] > nums2[idx2])
						nums1[tar--] = nums1[idx1--];
					else
						nums1[tar--] = nums2[idx2--];
				}
				else
					nums1[tar--] = nums2[idx2--];
			}
		}
	};
	/*88. Merge Sorted Array end */


	/*19. Remove Nth Node From End of List (easy)
	https://leetcode.com/problems/remove-nth-node-from-end-of-list/
	https://discuss.leetcode.com/topic/5397/my-short-c-solution
	http://blogread.cn/it/article/6243?f=wb
	*/
	class Solution19 {
	public:
		ListNode* removeNthFromEnd(ListNode* head, int n) {
			int idx = 1;
			ListNode**t1 = &head;
			ListNode*t2 = head;

			for (int i = 1; i < n; ++i)
				t2 = t2->next;

			while (t2->next) {
				t1 = &((*t1)->next);
				t2 = t2->next;
			}

			*t1 = (*t1)->next;
			return head;
		}

		ListNode* removeNthFromEnd1(ListNode* head, int n) {
			if (head == NULL || n < 1)
				return NULL;

			int pos = 1;
			ListNode* pre = NULL;
			ListNode* start = head;
			ListNode* curr = head;

			while (curr && pos < n) {
				curr = curr->next;
				pos++;
			}

			if (curr == NULL)
				return NULL;

			while (curr->next) {
				pre = start;
				start = start->next;
				curr = curr->next;
			}

			if (pre == NULL)
				head = head->next;
			else
				pre->next = start->next;

			return head;
		}
	};
	/*19. Remove Nth Node From End of List end */


	/*283. Move Zeroes (easy)
	https://leetcode.com/problems/move-zeroes/
	https://discuss.leetcode.com/topic/24716/simple-o-n-java-solution-using-insert-index
	*/
	class Solution283 {
	public:
		void moveZeroes(vector<int>& nums) {
			if (nums.empty())
				return;

			int idx = 0;
			for (int i = 0; i < nums.size(); ++i) {
				if (nums[i] != 0)
					nums[idx++] = nums[i];
			}

			while (idx < nums.size())
				nums[idx++] = 0;
		}
	};
	/*283. Move Zeroes end */
}
//////////////////////////Tag Two Pointers end//////////////////////////////////////////



//////////////////////////Tag String//////////////////////////////////////////
namespace STRING {

	/*385. Mini Parser (medium)
	https://leetcode.com/problems/mini-parser/
	https://discuss.leetcode.com/topic/54270/an-java-iterative-solution/2
	*/
	/*385. Mini Parser end */


	/*76. Minimum Window Substring (hard)
	https://leetcode.com/problems/minimum-window-substring/
	https://discuss.leetcode.com/topic/30941/here-is-a-10-line-template-that-can-solve-most-substring-problems
	*/
	class Solution76 {
	public:
		string minWindow(string s, string t) {
			vector<int> map(128, 0);
			int begin = 0, end = 0, head = 0;
			int counter = t.size();
			int d = INT_MAX;

			for (auto c : t)
				map[c] ++;

			while (end < s.size()) {
				if (map[s[end++]]-- > 0)
					--counter;

				while (counter == 0) {
					if (end - begin < d)
						d = end - (head = begin);

					if (map[s[begin++]]++ == 0)
						counter++;
				}
			}

			return d == INT_MAX ? "" : s.substr(head, d);
		}

		static void main() {
			Solution76* test = new Solution76;
			string result;

			string s1("adobcna");
			string t1("abc");

			result = test->minWindow(s1, t1);

			string s2("daonbc"); //s2("daonbcna");
			string t2("abc");
			result = test->minWindow(s2, t2);
		}
	};
	/*76. Minimum Window Substring end */


	/*214. Shortest Palindrome (hard)
	https://leetcode.com/problems/shortest-palindrome/
	https://discuss.leetcode.com/topic/14526/c-8-ms-kmp-based-o-n-time-o-n-memory-solution
	*/
	class Solution214 {
	public:
		string shortestPalindrome(string s) {
			string rev_s(s);

			reverse(rev_s.begin(), rev_s.end());

			string tmp = s + "#" + rev_s;
			vector<int> p(tmp.size(), 0);

			for (int i = 1; i < tmp.size(); ++i) {
				int j = p[i - 1];

				while (j > 0 && tmp[i] != tmp[j])
					j = p[j - 1];

				p[i] = (j += tmp[i] == tmp[j]);
			}

			return rev_s.substr(0, s.size() - p[tmp.size() - 1]) + s;
		}
	};
	/*214. Shortest Palindrome end */


	/*68. Text Justification (hard)
	https://leetcode.com/problems/text-justification/
	https://discuss.leetcode.com/topic/4189/share-my-concise-c-solution-less-than-20-lines
	*/
	class Solution68 {
	public:
		vector<string> fullJustify(vector<string>& words, int maxWidth) {
			vector<string> res;

			if (words.empty() || maxWidth == 0) {
				res.push_back("");
				return res;
			}

			int k = 0, len;
			for (int i = 0; i < words.size(); i += k) {
				len = 0;
				for (k = 0; i + k < words.size() && len + words[i + k].size() <= maxWidth - k; ++k)
					len += words[i + k].size();

				string tmp(words[i]);

				for (int j = 0; j < k - 1; ++j) {
					if (i + k >= words.size())
						tmp += " ";
					else
						tmp += string((maxWidth - len) / (k - 1) + (j < (maxWidth - len) % (k - 1)), ' ');

					tmp += words[i + j + 1];
				}

				tmp += string(maxWidth - tmp.size(), ' ');
				res.push_back(tmp);
			}

			return res;
		}
	};
	/*68. Text Justification end */


	/*273. Integer to English Words (hard)
	https://leetcode.com/problems/integer-to-english-words/
	https://discuss.leetcode.com/topic/24112/fairly-clear-4ms-c-solution
	*/
	class Solution273 {
	public:
		string int2string(int n) {
			string digits[20] = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
			string tens[10] = { "Zero", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

			if (n >= 1000000000) {
				return int2string(n / 1000000000) + " Billion" + int2string(n % 1000000000);
			}
			else if (n >= 1000000) {
				return int2string(n / 1000000) + " Million" + int2string(n % 1000000);
			}
			else if (n >= 1000) {
				return int2string(n / 1000) + " Thousand" + int2string(n % 1000);
			}
			else if (n >= 100) {
				return int2string(n / 100) + " Hundred" + int2string(n % 100);
			}
			else if (n >= 20) {
				return  " " + tens[n / 10] + int2string(n % 10);
			}
			else if (n >= 1) {
				return " " + digits[n];
			}
			else {
				return "";
			}
		}

		string numberToWords(int num) {
			if (num == 0) {
				return "Zero";
			}
			else {
				string ret = int2string(num);
				return ret.substr(1, ret.length() - 1);
			}
		}
	};
	/*273. Integer to English Words end */


	/*30. Substring with Concatenation of All Words (hard)
	https://leetcode.com/problems/substring-with-concatenation-of-all-words/
	https://discuss.leetcode.com/topic/6617/an-o-n-solution-with-detailed-explanation
	*/
	class Solution30 {
	public:
		vector<int> findSubstring(string s, vector<string>& words) {
			vector<int> result;
			int len = s.size();

			if (len < 1 || words.size() < 1)
				return result;

			int wlen = words[0].size();
			unordered_map<string, int> dict;

			for (auto it : words)
				dict[it] ++;

			int left, count = 0;
			for (int i = 0; i < wlen; ++i) {
				count = 0;
				unordered_map<string, int> tmpdict;
				left = i;

				for (int j = i; j <= len - wlen; j += wlen) {
					string str = s.substr(j, wlen);

					if (dict.count(str)) {
						tmpdict[str]++;
						if (tmpdict[str] <= dict[str])
							++count;
						else {
							while (tmpdict[str] > dict[str]) {
								string str1 = s.substr(left, wlen);
								tmpdict[str1] --;

								if (tmpdict[str1] < dict[str1])
									--count;

								left += wlen;
							}
						}

						if (count == words.size()) {
							result.push_back(left);
							tmpdict[s.substr(left, wlen)]--;
							--count;
							left += wlen;
						}
					}
					else {
						tmpdict.clear();
						count = 0;
						left = j + wlen;
					}
				}
			}

			return result;
		}
	};
	/*30. Substring with Concatenation of All Words end */


	/*186. Reverse Words in a String II (medium)
	https://leetcode.com/problems/reverse-words-in-a-string-ii/
	*/
	class Solution186 {
	public:
		void reverseWord(string &s) {
			string result;
			int left = 0, right = s.size() - 1;

			while (left < right) {
				swap(s[left], s[right]);
				++left;
				--right;
			}
		}

		void reverseWords(string &s) {
			reverseWord(s);

			istringstream in(s);
			string word, result;
			while (in >> word) {
				reverseWord(word);
				result += word + " ";
			}

			s = result.substr(0, result.size() - 1);
		}

		static void main() {
			auto_ptr<Solution186> test(new Solution186);
			string s("a b");

			test->reverseWords(s);

		}
	};
	/*186. Reverse Words in a String II end */

	/*151. Reverse Words in a String (medium)
	https://leetcode.com/problems/reverse-words-in-a-string/
	https://discuss.leetcode.com/topic/5319/c-solution-in-place-runtime-o-n-memory-o-1
	*/
	class Solution151 {
	public:
		void reverseWords(string &s) {
			int idx = 0;
			int i = 0, j = 0, k;
			int words = 0;
			int len = s.size();

			while (true) {
				while (i < len && s[i] == ' ')
					++i;

				if (i == len)
					break;

				if (words > 0)
					s[j++] = ' ';

				int k = j;

				while (i < len && s[i] != ' ')
					s[j++] = s[i++];

				reverse(s.begin() + k, s.begin() + j);
				words++;
			}

			s.resize(j);
			reverse(s.begin(), s.end());
		}
	};
	/*151. Reverse Words in a String end */


	/*12. Integer to Roman (medium)
	https://discuss.leetcode.com/topic/12384/simple-solution
	*/
	class Solution12 {
	public:
		string intToRoman(int num) {
			map<char, int> value;
			char symbols[7] = { 'I','V','X','L','C','D','M' };
			string roman;

			int scale = 1000;
			int digit;
			for (int i = 6; i >= 0; i -= 2) {
				digit = num / scale;

				if (digit > 0) {
					if (digit <= 3)
						roman.append(digit, symbols[i]);
					else if (digit == 4) {
						roman.append(1, symbols[i]);
						roman.append(1, symbols[i + 1]);
					}
					else if (digit == 5)
						roman.append(1, symbols[i + 1]);
					else if (digit <= 8) {
						roman.append(1, symbols[i + 1]);
						roman.append(digit - 5, symbols[i]);
					}
					else if (digit == 9) {
						roman.append(1, symbols[i]);
						roman.append(1, symbols[i + 2]);
					}
				}

				num = num % scale;
				scale /= 10;
			}

			return roman;
		}
	};
	/*12. Integer to Roman end */


	/*43. Multiply Strings (medium)
	https://leetcode.com/problems/multiply-strings/
	https://discuss.leetcode.com/topic/30508/easiest-java-solution-with-graph-explanation
	*/
	class Solution43 {
	public:
		string multiply(string num1, string num2) {
			int tmp;
			int len1 = num1.size();
			int len2 = num2.size();
			int flag;
			string result(len1 + len2, '0');

			for (int i = len1 - 1; i >= 0; --i) {
				flag = 0;
				for (int j = len2 - 1; j >= 0; --j) {
					tmp = result[i + j + 1] - '0' + (num1[i] - '0') * (num2[j] - '0') + flag;
					result[i + j + 1] = (tmp % 10) + '0';
					flag = tmp / 10;
				}

				result[i] += flag;
			}

			int idx = 0;
			while (idx < len1 + len2  && result[idx++] == '0')
				;

			if (idx >= len1 + len2 && result[len1 + len2 - 1] == '0')
				result = "0";
			else
				result = result.substr(idx - 1);

			return result;
		}
	};
	/*43. Multiply Strings end */


	/*3. Longest Substring Without Repeating Characters (medium)
	https://leetcode.com/problems/longest-substring-without-repeating-characters/
	https://discuss.leetcode.com/topic/24739/c-code-in-9-lines
	*/
	class Solution3 {
	public:
		int lengthOfLongestSubstring(string s) {
			vector<int> charIndex(256, -1);
			int longest = 0, m = 0;

			for (int i = 0; i < s.length(); i++) {
				m = max(charIndex[s[i]] + 1, m);    // automatically takes care of -1 case
				charIndex[s[i]] = i;
				longest = max(longest, i - m + 1);
			}

			return longest;
		}
	};
	/*3. Longest Substring Without Repeating Characters end */


	/*49. Group Anagrams (medium)
	https://leetcode.com/problems/anagrams/
	https://discuss.leetcode.com/topic/21038/10-lines-76ms-easy-c-solution-updated-function-signature
	*/
	class Solution49 {
	public:
		static bool mycmp(string str1, string str2) {
			int k = 0;

			while (k < str1.size() && k < str2.size()) {
				if (str1[k] == str2[k]) {
					k++;
					continue;
				}

				return (str1[k] < str2[k]);
			}

			return k >= str1.size();
		}

		vector<vector<string>> groupAnagrams(vector<string>& strs) {
			unordered_map<string, int> keys;
			vector<vector<string>> ret;

			for (auto item : strs) {
				string tmp(item);
				sort(tmp.begin(), tmp.end());

				if (keys.count(tmp))
					ret[keys[tmp]].push_back(item);
				else {
					keys[tmp] = ret.size();
					ret.push_back(vector<string>(1, item));
				}
			}

			return ret;
		}
	};
	/*49. Group Anagrams end */


	/*227. Basic Calculator II (medium)
	https://leetcode.com/problems/basic-calculator-ii/
	https://discuss.leetcode.com/topic/16935/share-my-java-solution
	*/
	class Solution227 {
	public:
		int calculate1(string s) {
			deque<int> nums;
			deque<char> oper;

			int cur = 0;
			int ret = 0;

			for (int i = 0; i < s.size(); ++i) {
				if (s[i] == ' ' || (i == 0 && s[i] == '+'))
					continue;

				if (s[i] >= '0' && s[i] <= '9') {
					cur *= 10;
					cur += (s[i] - '0');

					if (i == s.size() - 1 || s[i + 1] < '0' || s[i + 1] > '9') {
						ret = cur;
						if (!oper.empty()) {
							int num1 = nums.back();

							if (oper.back() == '/') {
								nums.pop_back();
								oper.pop_back();
								ret = num1 / cur;
							}
							else if (oper.back() == '*') {
								nums.pop_back();
								oper.pop_back();
								ret = num1*cur;
							}
						}

						nums.push_back(ret);
						cur = 0;
					}
				}
				else {
					cur = 0;
					oper.push_back(s[i]);
				}
			}

			while (!oper.empty()) {
				int num1 = nums.front();
				nums.pop_front();
				int num2 = nums.front();
				nums.pop_front();

				if (oper.front() == '+')
					nums.push_front(num1 + num2);
				else
					nums.push_front(num1 - num2);

				oper.pop_front();
			}

			return nums.front();
		}

		int calculate(string s) {
			if (s.empty())
				return 0;

			stack<int> nums;
			char cursign = '+';
			int cur = 0;

			for (int i = 0; i < s.size(); ++i) {
				if (isdigit(s[i]))
					cur = cur * 10 + (s[i] - '0');

				if ((!isdigit(s[i]) && (s[i] != ' ')) || i == s.size() - 1) {
					if (cursign == '+')
						nums.push(cur);
					else if (cursign == '-')
						nums.push(-cur);
					else if (cursign == '*') {
						int tmp = nums.top();
						nums.pop();
						nums.push(tmp*cur);
					}
					else if (cursign == '/') {
						int tmp = nums.top();
						nums.pop();
						nums.push(tmp / cur);
					}

					cur = 0;
					cursign = s[i];
				}
			}

			int ret = 0;
			while (!nums.empty()) {
				ret += nums.top();
				nums.pop();
			}

			return ret;
		}
	};
	/*227. Basic Calculator II end */


	/*5. Longest Palindromic Substring (medium)
	https://leetcode.com/problems/longest-palindromic-substring/
	https://discuss.leetcode.com/topic/12187/simple-c-solution-8ms-13-lines
	*/
	class Solution5 {
	public:
		string prestring(string s) {
			string ret;

			if (s.empty()) {
				ret = "^$";
				return ret;
			}

			ret = "^";
			for (int i = 0; i < s.size(); ++i)
				ret += "#" + s.substr(i, 1);

			ret += "#$";
			return ret;
		}

		string longestPalindrome(string s) {
			string strT = prestring(s);
			int nlen = strT.size();

			vector<int> p(nlen);
			int c = 0, r = 0;

			for (int i = 1; i < nlen - 1; ++i) {
				int i_mirror = 2 * c - i;
				p[i] = r > i ? min(r - i, p[i_mirror]) : 0;

				while (strT[i - 1 - p[i]] == strT[i + 1 + p[i]])
					p[i] ++;

				if (p[i] + i > r) {
					c = i;
					r = p[i] + i;
				}
			}

			int max_len = 0;
			int index = 0;

			for (int i = 1; i < nlen - 1; ++i) {
				if (p[i] > max_len) {
					max_len = p[i];
					index = i;
				}
			}

			return s.substr((index - max_len - 1) / 2, max_len);
		}

		string longestPalindrome1(string s) {
			if (s.size() < 2)
				return s;

			int min_start = 0, max_len = 1;

			for (int i = 0; i < s.size();) {
				if (s.size() - i <= max_len / 2)
					break;

				int j = i, k = i;

				while (k < s.size() - 1 && s[k + 1] == s[k])
					++k;

				i = k + 1;

				while (k < s.size() - 1 && j > 0 && s[k + 1] == s[j - 1]) {
					++k;
					--j;
				}

				int new_len = k - j + 1;

				if (new_len > max_len) {
					max_len = new_len;
					min_start = j;
				}
			}

			return s.substr(min_start, max_len);
		}
	};
	/*5. Longest Palindromic Substring end */


	/*58. Length of Last Word (easy)
	https://leetcode.com/problems/length-of-last-word/
	https://discuss.leetcode.com/topic/2743/my-simple-solution-in-c
	*/
	class Solution58 {
	public:
		int lengthOfLastWord(string s) {
			if (s.empty())
				return 0;
			int nEnd = -1;
			int nBegin = -1;

			for (int nIdx = s.size() - 1; nIdx >= 0; --nIdx) {
				if (s[nIdx] != ' ') {
					if (nEnd == -1)
						nEnd = nIdx;
				}
				else {
					if (nEnd != -1) {
						nBegin = nIdx;
						break;
					}
				}
			}

			return nEnd - nBegin;
		}
	};
	/*58. Length of Last Word end */


	/*14. Longest Common Prefix (easy)
	https://leetcode.com/problems/longest-common-prefix/
	https://discuss.leetcode.com/topic/20991/accepted-c-6-lines-4ms
	*/
	class Solution14 {
	public:
		string longestCommonPrefix(vector<string>& strs) {
			if (strs.empty())
				return "";

			int size = strs[0].size();

			for (int i = 1; i < strs.size(); ++i) {
				int j = 0;

				for (; j < size && j < strs[i].size() && (strs[0][j] == strs[i][j]); ++j);

				size = j;
			}

			return strs[0].substr(0, size);
		}
	};
	/*14. Longest Common Prefix end */


	/*345. Reverse Vowels of a String (easy)
	https://leetcode.com/problems/reverse-vowels-of-a-string/
	https://discuss.leetcode.com/topic/43412/java-standard-two-pointer-solution
	*/
	class Solution345 {
	public:
		bool isVowel(char c) {
			if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
				c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
				return true;

			return false;
		}

		string reverseVowels(string s) {
			string str(s);

			int low = 0;
			int high = s.size() - 1;

			while (low < high) {
				while (low < high && !isVowel(s[low]))
					++low;				

				while (low < high && !isVowel(s[high]))
					--high;

				if (low >= high)
					break;

				str[high] = s[low];
				str[low] = s[high];
				++low;
				--high;
			}

			return str;
		}
	};
	/*345. Reverse Vowels of a String end */


	/*13. Roman to Integer (easy)
	https://leetcode.com/problems/roman-to-integer/
	https://discuss.leetcode.com/topic/7784/clean-o-n-c-solution
	*/
	class Solution13 {
	public:
		int romanToInt(string s) {
			map<char, int> value;

			int nIdx, result = 0;
			value['I'] = 1;
			value['V'] = 5;
			value['X'] = 10;
			value['L'] = 50;
			value['C'] = 100;
			value['D'] = 500;
			value['M'] = 1000;

			for (nIdx = 0; nIdx < s.size() - 1; ++nIdx) {
				if (value[s[nIdx]] >= value[s[nIdx + 1]])
					result += value[s[nIdx]];
				else
					result -= value[s[nIdx]];
			}

			result += value[s[nIdx]];
			return result;
		}
	};
	/*13. Roman to Integer end */


	/*28. Implement strStr() (easy)
	https://leetcode.com/problems/implement-strstr/
	https://discuss.leetcode.com/topic/15569/explained-4ms-easy-c-solution
	https://discuss.leetcode.com/topic/18839/elegant-java-solution
	*/
	class Solution28 {
	public:
		static void main() {
			Solution28* test = new Solution28;
			int result;

			string haystack1("abcbcbad");
			string needle1("cbcba");

			result = test->strStr(haystack1, needle1);
			delete test;
		}

		int strStr(string haystack, string needle) {
			int m = haystack.size();
			int n = needle.size();
			if (n == 0)
				return 0;

			vector<int> next(n);
			int k = -1;
			int i = 0, j = 0;
			next[0] = -1;

			while (j < n - 1) {
				if (k == -1 || needle[j] == needle[k]) {
					++k;
					++j;
					next[j] = k;
				}
				else
					k = next[k];
			}

			i = 0;
			j = 0;
			while (i < m && j < n) {
				if (j == -1 || haystack[i] == needle[j]) {
					++j;
					++i;
				}
				else
					j = next[j];
			}

			return j >= n ? (i - j) : -1;
		}

		int strStr3(string haystack, string needle) {
			int m = haystack.size();
			int n = needle.size();
			if (n == 0)
				return 0;

			vector<int> table(n, 0);

			for (int i = 1, j = 0; i <= n - 1;) {
				if (needle[i] != needle[j]) {
					if (j > 0)
						j = table[j - 1];
					else
						i++;
				}
				else {
					table[i] = j + 1;
					++i;
					++j;
				}
			}

			for (int i = 0, match_pos = 0; i < m;) {
				if (haystack[i] == needle[match_pos]) {
					if (match_pos == n - 1) {
						return i - (n - 1);
					}
					else {
						++i;
						++match_pos;
					}
				}
				else {
					if (match_pos == 0)
						++i;
					else
						match_pos = table[match_pos - 1];
				}
			}

			return -1;
		}

		int strStr1(string haystack, string needle) {
			int m = haystack.size();
			int n = needle.size();
			if (n == 0)
				return 0;

			int i, j;
			for (i = 0; i < m - n + 1; ++i) {
				for (j = 0; j < n; ++j) {
					if (haystack[i + j] != needle[j])
						break;
				}

				if (j == n)
					return i;
			}

			return -1;
		}
	};
	/*28. Implement strStr() end */


	/*8. String to Integer (atoi) (easy)
	https://leetcode.com/problems/string-to-integer-atoi/
	https://discuss.leetcode.com/topic/2666/my-simple-solution
	*/
	class Solution8 {
	public:
		int myAtoi(string str) {
			int begin = 0;
			int flag = 1;
			long res = 0;

			begin = str.find_first_not_of(' ');
			if (str[begin] == '-') {
				begin++;
				flag = -1;
			}
			else if (str[begin] == '+')
				begin++;

			for (; isdigit(str[begin]) && res <= INT_MAX && begin < str.size(); ++begin)
				res = res * 10 + (str[begin] - '0');

			if (res*flag > INT_MAX)
				return INT_MAX;

			if (res*flag < INT_MIN)
				return INT_MIN;

			return res*flag;
		}
	};
	/*8. String to Integer (atoi) end */


	/*67. Add Binary (easy)
	https://leetcode.com/problems/add-binary/
	https://discuss.leetcode.com/topic/8981/short-code-by-c
	*/
	class Solution67 {
	public:
		string addBinary(string a, string b) {
			string result;

			int idxa = a.size() - 1;
			int idxb = b.size() - 1;

			int c = 0;
			while (idxa >= 0 || idxb >= 0 || c == 1) {
				c += (idxa >= 0) ? (a[idxa] - '0') : 0;
				c += (idxb >= 0) ? (b[idxb] - '0') : 0;

				result = to_string(c % 2) + result;

				--idxa;
				--idxb;
				c /= 2;
			}

			return result;
		}


		string addBinary1(string a, string b) {
			string result;

			int last = 0;
			int idxa = a.size() - 1;
			int idxb = b.size() - 1;

			while (idxa >= 0 && idxb >= 0) {
				last = (a[idxa] - '0') + (b[idxb] - '0') + last;

				if (last > 1) {
					result = to_string(last - 2) + result;
					last = 1;
				}
				else {
					result = to_string(last) + result;
					last = 0;
				}

				--idxa;
				--idxb;
			}

			while (idxa >= 0) {
				last = (a[idxa] - '0') + last;

				if (last > 1) {
					result = to_string(last - 2) + result;
					last = 1;
				}
				else {
					result = to_string(last) + result;
					last = 0;
				}

				--idxa;
			}

			while (idxb >= 0) {
				last = (b[idxb] - '0') + last;

				if (last > 1) {
					result = to_string(last - 2) + result;
					last = 1;
				}
				else {
					result = to_string(last) + result;
					last = 0;
				}

				--idxb;
			}

			if (last)
				result = to_string(last) + result;

			return result;
		}

	};
	/*67. Add Binary end */


	/*125. Valid Palindrome (easy)
	https://leetcode.com/problems/valid-palindrome/
	https://discuss.leetcode.com/topic/5581/here-s-a-clean-c-solution
	*/
	class Solution125 {
	public:
		bool isPalindrome(string s) {
			if (s.empty())
				return true;

			bool bResult = true;
			int left = 0;
			int right = s.size() - 1;
			while (left < right) {
				while ((left < right) && !(isalpha(s[left]) || isdigit(s[left])))
					left++;

				while ((left < right) && !(isalpha(s[right]) || isdigit(s[right])))
					right--;

				if (left >= right)
					break;

				if (!((s[left] == s[right]) || (32 == abs(s[left] - s[right]))))
				{
					bResult = false;
					break;
				}

				left++;
				right--;
			}

			return bResult;
		}
	};
	/*125. Valid Palindrome end */


	/*38. Count and Say (easy)
	https://leetcode.com/problems/count-and-say/
	*/
	class Solution38 {
	public:
		string countAndSay(int n) {
			if (0 == n)
				return "";

			string result("1");
			string cur;
			int count;

			while (--n > 0) {
				cur = "";

				for (int i = 0; i < result.size(); ++i) {
					count = 1;

					while (i + 1 < result.size() && result[i] == result[i + 1]) {
						count++;
						i++;
					}

					cur += to_string(count) + result[i];
				}

				result = cur;
			}

			return result;
		}
	};
	/*38. Count and Say end */


	/*6. ZigZag Conversion (easy)
	https://leetcode.com/problems/zigzag-conversion/
	https://discuss.leetcode.com/topic/3162/easy-to-understand-java-solution
	*/
	class Solution6 {
	public:
		string convert(string s, int numRows) {
			if (numRows <= 1)
				return s;

			int len = s.size();
			string* strRow = new string[numRows];
			int step = 0, cur = 0;

			for (int i = 0; i < len; ++i) {
				strRow[cur].push_back(s[i]);

				if (cur == 0)
					step = 1;
				else if (cur == numRows - 1)
					step = -1;

				cur += step;
			}

			string result;

			for (int i = 0; i < numRows; ++i)
				result += strRow[i];

			delete[]strRow;

			return result;
		}
	};
	/*6. ZigZag Conversion end */


	/*165. Compare Version Numbers (easy)
	https://leetcode.com/problems/compare-version-numbers/
	https://discuss.leetcode.com/topic/11410/my-2ms-easy-solution-with-c-c
	*/
	class Solution165 {
	public:
		int compareVersion(string version1, string version2) {
			vector<int> ver1 = getversion(version1);
			vector<int> ver2 = getversion(version2);
			int idx;

			for (idx = 0; idx < ver1.size() && idx < ver2.size(); ++idx) {
				if (ver1[idx] > ver2[idx])
					return 1;

				if (ver1[idx] < ver2[idx])
					return -1;
			}

			//in case all the other nums is 0 for ver1
			//e.g. 1.0.0.0
			if (idx < ver1.size()) {
				while (idx < ver1.size()) {
					if (ver1[idx] > 0)
						return 1;
					++idx;
				}
			}

			//in case all the other nums is 0 for ver2
			//e.g. 1.0.0.0
			if (idx < ver2.size()) {
				while (idx < ver2.size()) {
					if (ver2[idx] > 0)
						return -1;

					++idx;
				}
			}

			return 0;
		}

		vector<int> getversion(string& version) {
			vector<int> result;
			int num = 0;

			for (int idx = 0; idx < version.size(); ++idx) {
				if (version[idx] == '.') {
					result.push_back(num);
					num = 0;
				}
				else
					num = num * 10 + (version[idx] - '0');
			}

			result.push_back(num);

			return result;
		}
	};
	/*165. Compare Version Numbers end */

}
//////////////////////////Tag String end//////////////////////////////////////////



//////////////////////////Tag Binary Search//////////////////////////////////////////
namespace BS {
	/*33. Search in Rotated Sorted Array (medium)
	https://leetcode.com/problems/search-in-rotated-sorted-array/
	https://discuss.leetcode.com/topic/3538/concise-o-log-n-binary-search-solution
	*/
	class Solution33 {
	public:
		int search(vector<int>& nums, int target) {
			int low = 0;
			int high = nums.size() - 1;

			int mid;
			while (low < high) {
				mid = low + (high - low) / 2;

				if (target == nums[mid])
					return mid;

				if (nums[high] > nums[mid]) {
					if (target > nums[mid] && target <= nums[high])
						low = mid + 1;
					else
						high = mid;
				}
				else {
					if (target <= nums[high] || target > nums[mid])
						low = mid + 1;
					else
						high = mid;
				}

			}

			if (low == high && target != nums[low]) return -1;
			return low;
		}
	};
	/*33. Search in Rotated Sorted Array end */


	/*35. Search Insert Position (medium)
	https://leetcode.com/problems/search-insert-position/
	https://discuss.leetcode.com/topic/15955/c-o-logn-binary-search-that-handles-duplicate
	*/
	class Solution35 {
	public:
		int searchInsert(vector<int>& nums, int target) {
			int low = 0, high = nums.size() - 1;

			// Invariant: the desired index is between [low, high+1]
			while (low <= high) {
				int mid = low + (high - low) / 2;

				if (nums[mid] < target)
					low = mid + 1;
				else
					high = mid - 1;
			}

			// (1) At this point, low > high. That is, low >= high+1
			// (2) From the invariant, we know that the index is between [low, high+1], so low <= high+1. Follwing from (1), now we know low == high+1.
			// (3) Following from (2), the index is between [low, high+1] = [low, low], which means that low is the desired index
			//     Therefore, we return low as the answer. You can also return high+1 as the result, since low == high+1
			return low;
		}

		int searchInsert1(int A[], int n, int target) {
			int nResult = 0;
			int i;
			for (i = 0; i < n; ++i) {
				if ((target == A[i]) || (target < A[i])) {
					nResult = i;
					break;
				}
			}

			if (i >= n)
				nResult = n;

			return nResult;
		}
	};
	/*35. Search Insert Position end */


	/*367. Valid Perfect Square (medium)
	https://leetcode.com/problems/valid-perfect-square/
	https://discuss.leetcode.com/topic/49325/a-square-number-is-1-3-5-7-java-code
	*/
	class Solution367 {
	public:
		bool isPerfectSquare(int num) {
			int i = 1;
			while (num > 0) {
				num -= i;
				i += 2;
			}
			return num == 0;
		}
	};
	/*367. Valid Perfect Square end */


	/*29. Divide Two Integers (medium)
	https://leetcode.com/problems/divide-two-integers/
	*/
	class Solution29 {
	public:
		int divide(int dividend, int divisor) {
			if (divisor == 0 || (dividend == INT_MIN && divisor == -1))
				return INT_MAX;

			int bits = 0;
			int sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;
			long long dvd = labs(dividend);
			long long dvs = labs(divisor);
			int result = 0;

			while (dvd >= dvs) {
				long long tmp = dvs, bits = 1;
				while (dvd >= (tmp << 1)) {
					tmp <<= 1;
					bits <<= 1;
				}

				dvd -= tmp;
				result += bits;
			}

			return sign == -1 ? -result : result;
		}

		static void main() {
			Solution29* test = new Solution29;
			int k = sizeof(int);
			test->divide(7, 3);
			delete test;
		}
	};
	/*29. Divide Two Integers end */


	/*162. Find Peak Element (medium)
	https://leetcode.com/problems/find-peak-element/
	https://discuss.leetcode.com/topic/5724/find-the-maximum-by-binary-search-recursion-and-iteration
	*/
	class Solution162 {
	public:
		int findPeakElement(vector<int>& nums) {
			int len = nums.size();

			if (0 == len)
				return -INT_MAX;
			else if (1 == len)
				return 0;
			else if (nums[0] > nums[1])
				return 0;

			for (int i = 1; i < len; ++i) {
				if (nums[i] > nums[i - 1]) {
					if (len - 1 == i)
						return i;

					if (nums[i] > nums[i + 1])
						return i;
				}
			}

			return -INT_MAX;
		}
	};
	/*162. Find Peak Element end */


	/*153. Find Minimum in Rotated Sorted Array (medium)
	https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
	https://discuss.leetcode.com/topic/4100/compact-and-clean-c-solution
	*/
	class Solution153 {
	public:
		int findMin(vector<int>& nums) {
			int low = 0, high = nums.size() - 1;
			int middle;

			while (low < high) {
				middle = (low + high) / 2;

				if (nums[middle] > nums[high])
					low = middle + 1;
				else if (nums[middle] < nums[high])
					high = middle;
			}

			return nums[low];
		}
	};
	/*153. Find Minimum in Rotated Sorted Array end */


	/*81. Search in Rotated Sorted Array II (medium)
	https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
	https://discuss.leetcode.com/topic/8087/c-concise-log-n-solution
	*/
	class Solution81 {
	public:
		bool search(vector<int>& nums, int target) {
			int low = 0;
			int high = nums.size() - 1;
			int mid;

			while (low <= high) {
				mid = low + (high - low) / 2;

				if (nums[mid] == target)
					return true;

				if (nums[mid] > nums[low]) {
					if (target >= nums[low] && target < nums[mid])
						high = mid - 1;
					else
						low = mid + 1;
				}
				else if (nums[mid] < nums[low]) {
					if (target <= nums[high] && target > nums[mid])
						low = mid + 1;
					else
						high = mid - 1;
				}
				else
					++low;
			}

			return false;
		}
	};
	/*81. Search in Rotated Sorted Array II end */


	/*74. Search a 2D Matrix (medium)
	https://leetcode.com/problems/search-a-2d-matrix/
	https://discuss.leetcode.com/topic/3227/don-t-treat-it-as-a-2d-matrix-just-treat-it-as-a-sorted-list
	*/
	class Solution74 {
	public:
		bool searchMatrix(vector<vector<int>>& matrix, int target) {
			if (matrix.empty() || matrix[0].empty())
				return false;

			int m = matrix.size();
			int n = matrix[0].size();
			int high = m * n - 1;

			int low = 0, mid;

			while (low <= high) {
				mid = low + (high - low) / 2;
				if (matrix[mid / n][mid%n] == target)
					return true;
				else if (target > matrix[mid / n][mid%n])
					low = mid + 1;
				else
					high = mid - 1;
			}

			return false;
		}

		bool searchMatrix1(vector<vector<int>>& matrix, int target) {
			int low = 0;
			int high = matrix.size() - 1;
			int mid;

			if (high < 0)
				return false;

			while (low <= high) {
				mid = low + (high - low) / 2;

				if (matrix[mid][0] == target)
					return true;
				else if (target > matrix[mid][0])
					low = mid + 1;
				else
					high = mid - 1;
			}

			int cur = min(low, high);

			if (cur >= matrix.size())
				return false;

			low = 0;
			high = matrix[cur].size() - 1;
			while (low <= high) {
				mid = low + (high - low) / 2;

				if (matrix[cur][mid] == target)
					return true;
				else if (target > matrix[cur][mid])
					low = mid + 1;
				else
					high = mid - 1;
			}

			return false;
		}
	};
	/*74. Search a 2D Matrix end */


	/*69. Sqrt(x) (medium)
	https://leetcode.com/problems/sqrtx/
	https://discuss.leetcode.com/topic/24532/3-4-short-lines-integer-newton-every-language
	*/
	class Solution69 {
	public:
		int mySqrt(int x) {
			if (x <= 1)
				return x;

			int left = 1, right = x;

			while (left < right) {
				int mid = left + (right - left) / 2;

				//mid * mid <= x
				if (mid <= x / mid)
					left = mid + 1;
				else
					right = mid;
			}

			return left - 1;
		}
	};
	/*69. Sqrt(x) end */


	/*50. Pow(x, n) (medium)
	https://leetcode.com/problems/powx-n/
	*/
	class Solution50 {
	public:
		double myPow1(double x, int n) {
			if (x == 0.0)
				return 0;

			if (n == 0)
				return 1;

			if (n < 0) {
				n = -n;
				x = 1 / x;
			}

			return (n % 2 == 0) ? myPow(x*x, n / 2) : x*myPow(x*x, n / 2);
		}

		double myPow(double x, int n) {
			if (n == 0)
				return 1;

			double res = myPow(x, n / 2);
			return n % 2 == 0 ? res * res : n < 0 ? res * res * (1 / x) : res * res * x;
		}
	};
	/*50. Pow(x, n) end */


	/*374. Guess Number Higher or Lower (easy)
	https://leetcode.com/problems/guess-number-higher-or-lower/
	https://discuss.leetcode.com/topic/51113/c-binary-search
	*/
	int guess(int num) { return 0; }

	class Solution374 {
	public:
		int guessNumber(int n) {
			int low = 1;

			while (low <= n) {
				int mid = low + (n - low) / 2;

				int result = guess(mid);

				if (0 == result)
					return mid;
				else if (result < 0)
					n = mid - 1;
				else
					low = mid + 1;
			}

			return -1;
		}
	};
	/*374. Guess Number Higher or Lower end */
}
//////////////////////////Tag Binary Search end//////////////////////////////////////////


//////////////////////////Tag Divide and Conquer//////////////////////////////////////////
namespace DC {
	/*174. Dungeon Game (hard)
	*/
	/*174. Dungeon Game end */


	/*312. Burst Balloons (hard)
	https://leetcode.com/problems/burst-balloons/
	https://discuss.leetcode.com/topic/30746/share-some-analysis-and-explanations
	*/
	class Solution312 {
	public:
		int myCount(vector<vector<int>>& dp, vector<int>& nums, int left, int right) {
			if (left + 1 == right)
				return 0;

			if (dp[left][right] > 0)
				return dp[left][right];

			int ans = 0;
			for (int i = left + 1; i < right; ++i)
				ans = max(ans, nums[left] * nums[i] * nums[right] + myCount(dp, nums, left, i) + myCount(dp, nums, i, right));

			dp[left][right] = ans;

			return ans;
		}

		int maxCoins1(vector<int>& nums) {
			vector<int> i_nums(nums.size() + 2, 0);

			int n = 1;
			for (auto it : nums)
				if (it > 0)
					i_nums[n++] = it;

			i_nums[0] = i_nums[n++] = 1;

			vector<vector<int>> dp(n, vector<int>(n, 0));
			return myCount(dp, i_nums, 0, n - 1);

		}

		int maxCoins(vector<int>& nums) {
			vector<int> i_nums(nums.size() + 2, 0);

			int n = 1;
			for (auto it : nums)
				if (it > 0)
					i_nums[n++] = it;

			i_nums[0] = i_nums[n++] = 1;

			vector<vector<int>> dp(n, vector<int>(n, 0));

			int left, right;
			for (int k = 2; k < n; ++k) {
				for (left = 0; left < n - k; ++left) {
					right = left + k;
					for (int i = left + 1; i < right; ++i)
						dp[left][right] = max(dp[left][right], i_nums[left] * i_nums[i] * i_nums[right] + dp[left][i] + dp[i][right]);
				}
			}

			return dp[0][n - 1];
		}
	};
	/*312. Burst Balloons end */


	/*282. Expression Add Operators (hard)
	https://leetcode.com/problems/expression-add-operators/
	https://discuss.leetcode.com/topic/24523/java-standard-backtrace-ac-solutoin-short-and-clear
	*/
	class Solution282 {
	public:
		void dfs(vector<string>& result, const string& num, int target, const string cur, int pos, long cvalue, long pvalue, char opt) {
			if ((pos == num.size()) && (cvalue == target))
				result.push_back(cur);

			for (int i = pos + 1; i <= num.size(); ++i) {
				string tmp = num.substr(pos, i - pos);
				long t = stol(tmp);

				if (to_string(t).size() != tmp.size())
					continue;

				dfs(result, num, target, cur + "+" + tmp, i, cvalue + t, t, '+');
				dfs(result, num, target, cur + "-" + tmp, i, cvalue - t, t, '-');
				dfs(result, num, target, cur + "*" + tmp, i, (opt == '-' ? cvalue + pvalue - t*pvalue : (opt == '+' ? cvalue - pvalue + t*pvalue : t*pvalue)), t*pvalue, opt);
			}
		}

		vector<string> addOperators(string num, int target) {
			vector<string> result;

			int len = num.size();
			if (len < 1)
				return result;

			for (int i = 1; i <= len; ++i) {
				string tmp = num.substr(0, i);
				long t = stol(tmp);

				if (to_string(t).size() != tmp.size())
					continue;

				dfs(result, num, target, tmp, i, t, t, '#');
			}

			return result;
		}
	};
	/*282. Expression Add Operators end */


	/*4. Median of Two Sorted Arrays (medium)
	https://leetcode.com/problems/median-of-two-sorted-arrays/
	https://discuss.leetcode.com/topic/4996/share-my-o-log-min-m-n-solution-with-explanation
	*/
	class Solution4 {
	public:
		int getkth(vector<int>& nums1, int s1, vector<int>& nums2, int s2, int k) {
			if (s1 > s2)
				return getkth(nums2, s2, nums1, s1, k);

			if (0 == s1)
				return nums2[k - 1];

			if (k == 1)
				return min(nums1[0], nums2[0]);

			int i = min(s1, k / 2);
			int j = min(s2, k / 2);

			if (nums1[i - 1] > nums2[j - 1]) {
				vector<int>tmp(nums2.begin() + j, nums2.end());
				return getkth(nums1, s1, tmp, s2 - j, k - j);
			}
			else {
				vector<int>tmp(nums1.begin() + i, nums1.end());
				return getkth(tmp, s1 - i, nums2, s2, k - i);
			}

			return 0;

		}

		double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
			int m = (nums1.size() + nums2.size() + 1) >> 1;
			int n = (nums1.size() + nums2.size() + 2) >> 1;

			return (getkth(nums1, nums1.size(), nums2, nums2.size(), m) + getkth(nums1, nums1.size(), nums2, nums2.size(), n)) / 2.0;
		}
	};
	/*4. Median of Two Sorted Arrays end */


	/*240. Search a 2D Matrix II (medium)
	https://leetcode.com/problems/search-a-2d-matrix-ii/
	https://discuss.leetcode.com/topic/20064/my-concise-o-m-n-java-solution
	*/
	class Solution240 {
	public:
		bool searchMatrix(vector<vector<int>>& matrix, int target) {
			int m = matrix.size();
			int j = m ? matrix[0].size() - 1 : 0;
			int i = 0;

			while (i < m && j >= 0) {
				if (matrix[i][j] == target)
					return true;
				else if (matrix[i][j] > target)
					--j;
				else
					++i;
			}

			return false;
		}
	};
	/*240. Search a 2D Matrix II end */


	/*241. Different Ways to Add Parentheses (easy)
	https://leetcode.com/problems/different-ways-to-add-parentheses/
	https://discuss.leetcode.com/topic/19906/c-4ms-recursive-dp-solution-with-brief-explanation
	*/
	class Solution241 {
	public:
		vector<int> diffWaysToCompute(string input) {
			vector<int> result;
			if (input.empty())
				return result;

			int num;
			char op = ' ';
			vector<int> data;
			vector<char> ops;
			istringstream ss(input + "+");

			while (ss >> num && ss >> op) {
				data.push_back(num);
				ops.push_back(op);
			}

			const int size_i = data.size();
			vector<vector<vector<int>>> dp(size_i, vector<vector<int>>(size_i, vector<int>()));

			for (int i = 0; i < size_i; ++i)
			for (int j = i; j >= 0; --j) {
				if (j == i) {
					dp[j][i].push_back(data[i]);
					continue;
				}

				for (int k = j; k < i; ++k) {
					for (auto left : dp[j][k])
					for (auto right : dp[k + 1][i]) {
						int val = 0;

						if (ops[k] == '-')
							val = left - right;
						else if (ops[k] == '+')
							val = left + right;
						else
							val = left * right;

						dp[j][i].push_back(val);
					}
				}
			}

			return dp[0][size_i - 1];
		}

		vector<int> diffWaysToCompute1(string input) {
			vector<int> result;

			int len = input.size();

			for (int i = 0; i < len; ++i) {
				if (input[i] == '+' || input[i] == '-' || input[i] == '*') {
					string lval = input.substr(0, i);
					string rval = input.substr(i + 1, len - i - 1);

					vector<int> leftRes = diffWaysToCompute(lval);
					vector<int> rightRes = diffWaysToCompute(rval);
					for (int leftItem : leftRes)
					for (int rifhtItem : rightRes) {
						if (input[i] == '+')
							result.push_back(leftItem + rifhtItem);
						else if (input[i] == '-')
							result.push_back(leftItem - rifhtItem);
						else
							result.push_back(leftItem * rifhtItem);
					}
				}
			}


			if (result.empty())
				result.push_back(stoi(input));

			return result;
		}
	};
	/*241. Different Ways to Add Parentheses end */

}
//////////////////////////Tag Divide and Conquer end//////////////////////////////////////////



//////////////////////////Tag Dynamic Programming//////////////////////////////////////////
namespace DP {
	/*174. Dungeon Game (hard)
	https://leetcode.com/problems/dungeon-game/
	https://discuss.leetcode.com/topic/6912/c-dp-solution
	*/
	class Solution174 {
	public:
		int calculateMinimumHP(vector<vector<int>>& dungeon) {
			if (dungeon.empty() || dungeon[0].empty())
				return 0;

			int m = dungeon.size();
			int n = dungeon[0].size();
			vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));

			dp[m - 1][n] = dp[m][n - 1] = 1;
			for (int i = m - 1; i >= 0; --i)
				for (int j = n - 1; j >= 0; --j)
				{
					int need = min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j];

					dp[i][j] = need <= 0 ? 1 : need;
				}

			return dp[0][0];
		}
	};
	/*174. Dungeon Game end */


	/*354. Russian Doll Envelopes (hard)
	https://leetcode.com/problems/russian-doll-envelopes/
	https://discuss.leetcode.com/topic/47469/java-nlogn-solution-with-explanation
	*/
	class Solution354 {
	public:
		static bool cmp_first(const pair<int, int>& i, const pair<int, int>& j) {
			if (i.first == j.first)
				return i.second > j.second;

			return i.first < j.first;
		}

		int maxEnvelopes(vector<pair<int, int>>& envelopes) {
			vector<int> candidates;
			sort(envelopes.begin(), envelopes.end(), cmp_first);
			vector<int> dp;

			for (int i = 0; i < envelopes.size(); ++i) {
				auto itr = lower_bound(dp.begin(), dp.end(), envelopes[i].second);

				if (itr == dp.end())
					dp.push_back(envelopes[i].second);
				else
					*itr = envelopes[i].second;
			}

			return dp.size();
		}
	};
	/*354. Russian Doll Envelopes end */


	/*32. Longest Valid Parentheses (hard)
	https://leetcode.com/problems/longest-valid-parentheses/
	https://discuss.leetcode.com/topic/2426/my-dp-o-n-solution-without-using-stack
	*/
	class Solution32 {
	public:
		int longestValidParentheses(string s) {
			if (s.size() <= 1)
				return 0;

			vector<int> dp(s.size(), 0);
			int curmax = 0;

			for (int i = 1; i < s.size(); ++i)
			{
				if (s[i] == ')')
				{
					if (s[i - 1] == '(')
						dp[i] = (i >= 2 ? dp[i - 2] + 2 : 2);
					else
					{
						if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(')
							dp[i] = dp[i - 1] + 2 + (i - dp[i - 1] - 2 >= 0 ? dp[i - dp[i - 1] - 2] : 0);
					}
				}

				curmax = max(curmax, dp[i]);
			}

			return curmax;
		}
	};
	/*32. Longest Valid Parentheses end */


	/*188. Best Time to Buy and Sell Stock IV (hard)
	https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
	https://discuss.leetcode.com/topic/8984/a-concise-dp-solution-in-java
	*/
	class Solution188 {
	public:
		int quickProfit(vector<int>& prices) {
			int len = prices.size(), profit = 0;

			for (int i = 1; i < len; ++i) {
				if (prices[i] > prices[i - 1])
					profit += (prices[i] - prices[i - 1]);
			}

			return profit;
		}

		int maxProfit(int k, vector<int>& prices) {
			int len = prices.size();

			if (k >= len / 2)
				return quickProfit(prices);

			vector<vector<int>> dp(k + 1, vector<int>(len, 0));

			for (int i = 1; i <= k; ++i) {
				int tmpmax = -prices[0];
				for (int j = 1; j < len; ++j) {
					dp[i][j] = max(dp[i][j - 1], prices[j] + tmpmax);
					tmpmax = max(tmpmax, dp[i - 1][j - 1] - prices[j]);
				}
			}

			return dp[k][len - 1];
		}
	};
	/*188. Best Time to Buy and Sell Stock IV end */


	/*363. Max Sum of Rectangle No Larger Than K (hard)
	https://leetcode.com/problems/max-sum-of-sub-matrix-no-larger-than-k/
	https://discuss.leetcode.com/topic/48875/accepted-c-codes-with-explanation-and-references
	*/
	class Solution363 {
	public:
		int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
			//2D Kadane's algorithm + 1D maxSum problem with sum limit k
			//2D subarray sum solution

			//boundary check
			if (matrix.empty()) return 0;

			int m = matrix.size(), n = matrix[0].size();
			int result = INT_MIN;

			//outer loop should use smaller axis
			//now we assume we have more rows than cols, therefore outer loop will be based on cols 
			for (int left = 0; left < n; left++) {
				//array that accumulate sums for each row from left to right 
				//int[] sums = new int[m];
				vector<int> sums(m, 0);

				for (int right = left; right < n; right++) {
					//update sums[] to include values in curr right col
					for (int i = 0; i < m; i++) {
						sums[i] += matrix[i][right];
					}

					//we use TreeSet to help us find the rectangle with maxSum <= k with O(logN) time
					set<int> sets;// = new TreeSet<Integer>();
								  //add 0 to cover the single row case
					sets.insert(0);
					int currSum = 0;

					for (int sum : sums) {
						currSum += sum;
						//we use sum subtraction (curSum - sum) to get the subarray with sum <= k
						//therefore we need to look for the smallest sum >= currSum - k
						set<int>::iterator ite = sets.lower_bound(currSum - k);//.ceiling(currSum - k);
						if (ite != sets.end())
							result = max(result, currSum - *ite);

						sets.insert(currSum);
					}
				}
			}

			return result;
		}
	};
	/*363. Max Sum of Rectangle No Larger Than K end */


	/*132. Palindrome Partitioning II (hard)
	https://leetcode.com/problems/palindrome-partitioning-ii/
	https://discuss.leetcode.com/topic/2840/my-solution-does-not-need-a-table-for-palindrome-is-it-right-it-uses-only-o-n-space
	*/
	class Solution132 {
	public:
		int minCut(string s) {
			int n = s.size();
			vector<int> cut(n + 1, 0);  // number of cuts for the first k characters

			for (int i = 0; i <= n; i++) 
				cut[i] = i - 1;

			for (int i = 0; i < n; i++) {
				for (int j = 0; i - j >= 0 && i + j < n && s[i - j] == s[i + j]; j++) // odd length palindrome
					cut[i + j + 1] = min(cut[i + j + 1], 1 + cut[i - j]);

				for (int j = 1; i - j + 1 >= 0 && i + j < n && s[i - j + 1] == s[i + j]; j++) // even length palindrome
					cut[i + j + 1] = min(cut[i + j + 1], 1 + cut[i - j + 1]);
			}
			return cut[n];
		}
	};
	/*132. Palindrome Partitioning II end */


	/*123. Best Time to Buy and Sell Stock III (hard)
	https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
	https://discuss.leetcode.com/topic/5934/is-it-best-solution-with-o-n-o-1
	*/
	class Solution123 {
	public:
		int maxProfit(vector<int>& prices) {
			int hold1 = INT_MIN, hold2 = INT_MIN;
			int release1 = 0, release2 = 0;

			for (auto it : prices) {
				release2 = max(release2, hold2 + it);
				hold2 = max(hold2, release1 - it);

				release1 = max(release1, hold1 + it);
				hold1 = max(hold1, -it);
			}

			return release2;
		}
	};
	/*123. Best Time to Buy and Sell Stock III end */


	/*115. Distinct Subsequences (hard)
	https://leetcode.com/problems/distinct-subsequences/
	https://discuss.leetcode.com/topic/9488/easy-to-understand-dp-in-java
	*/
	class Solution115 {
	public:
		int numDistinct(string s, string t) {
			vector<vector<int>> dp(t.size() + 1, vector<int>(s.size() + 1, false));

			for (int j = 0; j < s.size() + 1; ++j)
				dp[0][j] = 1;

			for (int i = 1; i < t.size() + 1; ++i)
				dp[i][0] = 0;

			for (int i = 1; i <= t.size(); ++i)
				for (int j = 1; j <= s.size(); ++j) {
					if (s[j - 1] == t[i - 1])
						dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1];
					else
						dp[i][j] = dp[i][j - 1];
				}

			return dp[t.size()][s.size()];
		}
	};
	/*115. Distinct Subsequences end */


	/*97. Interleaving String (hard)
	https://leetcode.com/problems/interleaving-string/
	https://discuss.leetcode.com/topic/3532/my-dp-solution-in-c
	*/
	class Solution97 {
	public:
		bool isInterleave(string s1, string s2, string s3) {
			int len1 = s1.size();
			int len2 = s2.size();
			int len3 = s3.size();

			if (len3 != len1 + len2)
				return false;

			vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, false));

			dp[0][0] = true;

			for (int i = 1; i <= len1; ++i) {
				if (s1[i - 1] == s3[i - 1])
					dp[i][0] = true;
				else
					break;
			}

			for (int i = 1; i <= len2; ++i) {
				if (s2[i - 1] == s3[i - 1])
					dp[0][i] = true;
				else
					break;
			}

			for (int i = 1; i <= len1; ++i) {
				char c1 = s1[i - 1];

				for (int j = 1; j <= len2; ++j) {
					int len = i + j;
					char c2 = s2[j - 1];
					char c3 = s3[len - 1];

					if (c1 == c3)
						dp[i][j] = dp[i - 1][j] || dp[i][j];

					if (c2 == c3)
						dp[i][j] = dp[i][j - 1] || dp[i][j];
				}
			}

			return dp[len1][len2];
		}
	};
	/*97. Interleaving String end */


	/*87. Scramble String (hard)
	https://leetcode.com/problems/scramble-string/
	https://discuss.leetcode.com/topic/14337/share-my-4ms-c-recursive-solution
	*/
	class Solution87 {
	public:
		bool isScramble(string s1, string s2) {
			if (s1.size() != s2.size())
				return false;
			string tmp1(s1);
			string tmp2(s2);

			if (s1 == s2)
				return true;

			sort(tmp1.begin(), tmp1.end());
			sort(tmp2.begin(), tmp2.end());

			if (tmp1 != tmp2)
				return false;

			for (int i = 1; i < s1.size(); ++i) {
				string str11 = s1.substr(0, i);
				string str12 = s1.substr(i);
				{
					string str21 = s2.substr(0, i);
					string str22 = s2.substr(i);

					if (isScramble(str11, str21) && isScramble(str12, str22))
						return true;
				}

				{
					string str21 = s2.substr(s1.size() - i);
					string str22 = s2.substr(0, s1.size() - i);

					if (isScramble(str11, str21) && isScramble(str12, str22))
						return true;
				}
			}

			return false;
		}
	};
	/*87. Scramble String end */


	/*72. Edit Distance (hard)
	https://leetcode.com/problems/edit-distance/
	https://discuss.leetcode.com/topic/17639/20ms-detailed-explained-c-solutions-o-n-space
	*/
	class Solution72 {
	public:
		int minDistance(string word1, string word2) {
			int len1 = word1.size();
			int len2 = word2.size();
			vector<int> dp(len2 + 1, 0);

			for (int i = 1; i <= len2; ++i)
				dp[i] = i;

			int pre;
			for (int i = 1; i <= len1; ++i) {
				pre = i;
				for (int j = 1; j <= len2; ++j) {
					int cur;
					if (word1[i - 1] == word2[j - 1])
						cur = dp[j - 1];
					else
						cur = min(min(dp[j - 1], pre), dp[j]) + 1;

					dp[j - 1] = pre;
					pre = cur;
				}

				dp[len2] = pre;
			}

			return dp[len2];
		}
	};
	/*72. Edit Distance end */


	/*221. Maximal Square (medium)
	https://leetcode.com/problems/maximal-square/
	https://discuss.leetcode.com/topic/15328/easy-dp-solution-in-c-with-detailed-explanations-8ms-o-n-2-time-and-o-n-space
	*/
	class Solution221 {
	public:
		int maximalSquare(vector<vector<char>>& matrix) {
			if (matrix.empty())
				return 0;

			int row = matrix.size();
			int col = matrix[0].size();

			int pre = 0;
			vector<int> dp(col + 1, 0);
			int maxsize = 0;

			//for original dp[i][j], it can be add one more row
			//and one more column at the a[0][0], this will eliminate
			//the corner case
			for (int i = 1; i <= row; ++i)
				for (int j = 1; j <= col; ++j) {
					int tmp = dp[j];
					if (matrix[i - 1][j - 1] == '0')
						dp[j] = 0;
					else {
						dp[j] = min(dp[j - 1], min(dp[j], pre)) + 1;
						maxsize = max(maxsize, dp[j]);
					}

					pre = tmp;
				}

			return maxsize*maxsize;
		}
	};
	/*221. Maximal Square end */


	/*213. House Robber II (medium)
	https://leetcode.com/problems/house-robber-ii/
	https://discuss.leetcode.com/topic/14375/simple-ac-solution-in-java-in-o-n-with-explanation
	*/
	class Solution213 {
	public:
		int rob(vector<int>& nums, int start, int end) {
			int withi = 0, withouti = 0;

			for (int k = start; k <= end; ++k) {
				int i = withi, e = withouti;

				withi = withouti + nums[k];
				withouti = max(i, e);
			}

			return max(withi, withouti);
		}

		int rob(vector<int>& nums) {
			if (nums.size() == 1)
				return nums[0];

			return max(rob(nums, 0, nums.size() - 2), rob(nums, 1, nums.size() - 1));
		}
	};
	/*213. House Robber II end */


	/*375. Guess Number Higher or Lower II (medium)
	https://leetcode.com/problems/guess-number-higher-or-lower-ii/
	https://discuss.leetcode.com/topic/51353/simple-dp-solution-with-explanation
	*/
	class Solution375 {
	public:
		int getMoneyAmount(int n) {
			vector<vector<int>>table(n + 1, vector<int>(n + 1, 0));
			return DP(table, 1, n);
		}

		int DP(vector<vector<int>>& t, int s, int e) {
			if (s >= e) 
				return 0;

			if (t[s][e] != 0) return t[s][e];
			int res = INT_MAX;
			for (int x = s; x <= e; x++) {
				int tmp = x + max(DP(t, s, x - 1), DP(t, x + 1, e));
				res = min(res, tmp);
			}

			t[s][e] = res;
			return res;
		}
	};
		
	/*375. Guess Number Higher or Lower II end */


	/*343. Integer Break (medium)
	https://leetcode.com/problems/integer-break/
	https://discuss.leetcode.com/topic/42978/java-dp-solution
	*/
	class Solution343 {
	public:
		int integerBreak(int n) {
			vector<int> vec(n + 1, 0);
			vec[1] = 1;

			for (int i = 2; i <= n; ++i)
			for (int j = 1; j < i; ++j)
				vec[i] = max(vec[i], max(j, vec[j])*max(i - j, vec[i - j]));

			return vec[n];
		}
	};
	/*343. Integer Break end */


	/*152. Maximum Product Subarray (medium)
	https://leetcode.com/problems/maximum-product-subarray/
	https://discuss.leetcode.com/topic/3607/sharing-my-solution-o-1-space-o-n-running-time
	*/
	class Solution152 {
	public:
		int maxProduct(vector<int>& nums) {
			int len = nums.size();

			if (len < 1)
				return 0;

			int maxpre = nums[0], minpre = nums[0];
			int ret = nums[0];
			int maxhere, minhere;

			for (int i = 1; i < len; ++i) {
				maxhere = max(max(maxpre*nums[i], minpre*nums[i]), nums[i]);
				minhere = min(min(maxpre*nums[i], minpre*nums[i]), nums[i]);

				ret = max(ret, maxhere);
				maxpre = maxhere;
				minpre = minhere;
			}

			return ret;
		}
	};
	/*152. Maximum Product Subarray end */


	/*322. Coin Change (medium)
	https://leetcode.com/problems/coin-change/
	https://discuss.leetcode.com/topic/32475/c-o-n-amount-time-o-amount-space-dp-solution
	*/
	class Solution322 {
	public:
		int mincoins(vector<int>& coins, int end, int amount) {
			if (end < 0 || coins[0] > amount)
				return -1;

			int index = end;
			for (; index >= 0; --index) {
				if (coins[index] <= amount)
					break;
			}

			if (index < 0)
				return -1;

			int nums = amount / coins[index];

			//with the max
			int nonums = mincoins(coins, index - 1, amount);

			int withnums = 0;

			if (amount > nums*coins[index])
				withnums = mincoins(coins, index - 1, amount%coins[index]);

			if (nonums == -1 && withnums == -1)
				return -1;
			else if (nonums == -1)
				return (nums + withnums);
			else
				return min(nonums, nums + withnums);
		}

		int coinChange1(vector<int>& coins, int amount) {
			if (coins.empty())
				return -1;

			if (amount == 0)
				return 0;

			sort(coins.begin(), coins.end());

			return mincoins(coins, coins.size() - 1, amount);
		}

		int coinChange(vector<int>& coins, int amount) {
			if (coins.empty())
				return -1;

			if (amount == 0)
				return 0;

			vector<int>dp(amount + 1, 0);
			int sum = 0;
			
			sort(coins.begin(), coins.end());			
			while (++sum <= amount) {
				int mincoin = -1;
				for (auto item : coins) {
					if (sum >= item && dp[sum - item] != -1) {
						int tmp = dp[sum - item] + 1;
						mincoin = mincoin < 0 ? tmp : (tmp < mincoin ? tmp : mincoin);
					}
				}

				dp[sum] = mincoin;
			}

			return dp[amount];
		}

		static void main() {
			Solution322* test = new Solution322;
			int result;

			vector<int> coins1 = { 1, 3, 5 };
			int amount1 = 6;
			result = test->coinChange(coins1, amount1);

			delete test;
		}
	};
	/*322. Coin Change end */


	/*53. Maximum Subarray (medium)
	https://leetcode.com/problems/maximum-subarray/
	https://discuss.leetcode.com/topic/5000/accepted-o-n-solution-in-java
	*/
	class Solution53 {
	public:
		int maxSubArray(int A[], int n) {
			int nResult = A[0];
			int nSum = 0, nBegin;

			for (int i = 0; i < n; ++i) {
				if (nSum > 0)
					nSum += A[i];
				else
					nSum = A[i];

				if (nSum > nResult)
					nResult = nSum;
			}

			return nResult;
		}
	};
	/*53. Maximum Subarray end */


	/*120. Triangle (medium)
	https://leetcode.com/problems/triangle/
	https://discuss.leetcode.com/topic/1669/dp-solution-for-triangle
	*/
	class Solution120 {
	public:
		int minimumTotal(vector<vector<int>>& triangle) {
			int n = triangle.size();
			vector<int> minlen(triangle.back());

			for (int layer = n - 2; layer >= 0; layer--) {// For each layer
				for (int i = 0; i <= layer; i++) // Check its every 'node'
					minlen[i] = min(minlen[i], minlen[i + 1]) + triangle[layer][i];
			}
			return minlen[0];
		}

		int minimumTotal1(vector<vector<int>>& triangle) {
			if (triangle.empty())
				return 0;

			queue<int> pathsum;

			pathsum.push(0);
			for (int i = 0; i < triangle.size(); ++i) {
				int curitems = triangle[i].size();
				if (i + 1 != curitems)
					return 0;

				for (int j = 0; j < curitems; ++j) {
					if (j == 0 || j == curitems - 1) {
						int cursum = pathsum.front() + triangle[i][j];
						if (j == curitems - 1)
							pathsum.pop();
						pathsum.push(cursum);
					}
					else {
						int lastleft = pathsum.front();
						pathsum.pop();
						int cursum = min(lastleft, pathsum.front()) + triangle[i][j];
						pathsum.push(cursum);
					}
				}
			}

			int minsum = INT_MAX;
			while (!pathsum.empty()) {
				if (pathsum.front() < minsum)
					minsum = pathsum.front();

				pathsum.pop();
			}

			return minsum;
		}
	};
	/*120. Triangle end */


	/*304. Range Sum Query 2D - Immutable (medium)
	https://leetcode.com/problems/range-sum-query-2d-immutable/
	https://discuss.leetcode.com/topic/29536/clean-c-solution-and-explaination-o-mn-space-with-o-1-time
	*/
	class NumMatrix304 {
	public:
		NumMatrix304(vector<vector<int>> &matrix) {
			if (matrix.empty() || matrix[0].empty())
				return;

			dp.resize(matrix.size() + 1);

			for (int i = 0; i <= matrix.size(); ++i)
				dp[i].resize(matrix[0].size() + 1, 0);

			for (int i = 1; i <= matrix.size(); ++i)
			for (int j = 1; j <= matrix[0].size(); ++j)
				dp[i][j] = dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1] + matrix[i - 1][j - 1];
		}

		int sumRegion(int row1, int col1, int row2, int col2) {
			int result = dp[row2 + 1][col2 + 1] - dp[row2 + 1][col1] - dp[row1][col2 + 1] + dp[row1][col1];
			return result;
		}

		vector<vector<int>> dp;
	};

	// Your NumMatrix object will be instantiated and called as such:
	// NumMatrix numMatrix(matrix);
	// numMatrix.sumRegion(0, 1, 2, 3);
	// numMatrix.sumRegion(1, 2, 3, 4);
	/*304. Range Sum Query 2D - Immutable end */


	/*91. Decode Ways (medium)
	https://leetcode.com/problems/decode-ways/
	https://discuss.leetcode.com/topic/7025/a-concise-dp-solution
	https://discuss.leetcode.com/topic/2562/dp-solution-java-for-reference
	*/
	class Solution91 {
	public:
		int numDecodings(string s) {
			if (s.empty() || s[0] == '0')
				return 0;

			int num1 = 1, num2 = 1;

			for (int i = 1; i < s.size(); ++i) {
				if (s[i] == '0')
					num1 = 0;

				if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] <= '6') {
					num1 = num2 + num1;
					num2 = num1 - num2;
				}
				else
					num2 = num1;
			}

			return num1;
		}
	};
	/*91. Decode Ways end */


	/*300. Longest Increasing Subsequence (medium)
	https://leetcode.com/problems/longest-increasing-subsequence/
	https://discuss.leetcode.com/topic/28719/short-java-solution-using-dp-o-n-log-n
	http://www.geeksforgeeks.org/construction-of-longest-monotonically-increasing-subsequence-n-log-n/
	*/
	class Solution300 {
	public:
		int findPos(const vector<int>& table, int value, int length) {
			int low = 0, high = length - 1;
			int mid;

			while (low <= high) {
				mid = low + (high - low) / 2;

				if (table[mid] >= value)
					high = mid - 1;
				else
					low = mid + 1;
			}

			return low;
		}

		int lengthOfLIS(vector<int>& nums) {
			int result = 1;
			int total = nums.size();

			if (total < 1)
				return 0;

			//table[i] to keep the minimal value with length i
			vector<int> table(total);
			table[0] = nums[0];
			int len = 1;
			for (int i = 1; i < total; ++i) {
				if (nums[i] > table[len - 1])
					table[len++] = nums[i];
				else {
					int pos = findPos(table, nums[i], len);
					table[pos] = nums[i];
				}
			}

			return len;
		}

		int lengthOfLIS1(vector<int>& nums) {
			int result = 1;
			int total = nums.size();

			if (total < 1)
				return 0;

			vector<int> s(total, 1);

			for (int i = 1; i < total; ++i) {
				for (int j = i - 1; j >= 0; --j) {
					if (nums[i] > nums[j])
						s[i] = max(s[i], s[j] + 1);
				}

				result = max(result, s[i]);
			}

			return result;
		}

		static void main() {
			unique_ptr<Solution300> test(new Solution300);
			int result;

			vector<int> nums1 = {3, 2, 6, 4, 5, 1};
			vector<int> nums2 = {3, 4, -1, 5, 8, 2, 3, 12, 7, 9, 10};
			vector<int> nums3 = { 3, 4, -1};
			result = test->lengthOfLIS(nums3);
			result = test->lengthOfLIS(nums2);
			result = test->lengthOfLIS(nums1);
			
		}
	};
	/*300. Longest Increasing Subsequence end */


	/*64. Minimum Path Sum (medium)
	https://leetcode.com/problems/minimum-path-sum/
	https://discuss.leetcode.com/topic/15269/10-lines-28ms-o-n-space-dp-solution-in-c-with-explanations
	*/
	class Solution64 {
	public:
		int minPathSum4(vector<vector<int>>& grid) {
			int m = grid.size();
			int n = grid[0].size();
			vector<int> cur(n, grid[0][0]);

			for (int i = 1; i < n; ++i)
				cur[i] = cur[i - 1] + grid[0][i];

			for (int i = 1; i < m; ++i) {
				cur[0] += grid[i][0];
				for (int j = 1; j < n; ++j) {
					cur[i] = min(cur[i], cur[i - 1]) + grid[i][j];
				}
			}

			return cur[n - 1];
		}

		int minPathSum(vector<vector<int>>& grid) {
			int m = grid.size();
			int n = grid[0].size();
			vector<int> cur(m, grid[0][0]);

			for (int i = 1; i < m; ++i)
				cur[i] = cur[i - 1] + grid[i][0];

			for (int j = 1; j < n; ++j) {
				cur[0] += grid[0][j];
				for (int i = 1; i < m; ++i)
					cur[i] = min(cur[i], cur[i - 1]) + grid[i][j];
			}

			return cur[m - 1];
		}

		int minPathSum2(vector<vector<int>>& grid) {
			int m = grid.size();
			int n = grid[0].size();

			vector<int> pre(m, grid[0][0]);
			vector<int> cur(m);

			for (int i = 1; i < m; ++i)
				pre[i] = pre[i - 1] + grid[i][0];

			for (int j = 1; j < n; ++j) {
				cur[0] = pre[0] + grid[0][j];
				for (int i = 1; i < m; ++i)
					cur[i] = min(pre[i], cur[i - 1]) + grid[i][j];

				swap(pre, cur);
			}

			return pre[m - 1];
		}

		int minPathSum1(vector<vector<int>>& grid) {
			int m = grid.size();
			int n = grid[0].size();

			vector<vector<int>> sum(m, vector<int>(n, grid[0][0]));
			for (int i = 1; i < m; ++i)
				sum[i][0] = sum[i - 1][0] + grid[i][0];

			for (int i = 1; i < n; ++i)
				sum[0][i] = sum[0][i - 1] + grid[0][i];

			for (int i = 1; i < m; ++i)
			for (int j = 1; j < n; ++j)
				sum[i][j] = min(sum[i - 1][j], sum[i][j - 1]) + grid[i][j];

			return sum[m - 1][n - 1];
		}
	};
	/*64. Minimum Path Sum end */


	/*63. Unique Paths II (medium)
	https://leetcode.com/problems/unique-paths-ii/
	https://discuss.leetcode.com/topic/4325/my-c-dp-solution-very-simple
	*/
	class Solution63 {
	public:
		int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
			if (obstacleGrid.empty() || obstacleGrid[0][0] == 1)
				return 0;

			int m = obstacleGrid.size();
			int n = obstacleGrid[0].size();
			vector<vector<int>> result(m + 1, vector<int>(n + 1, 0));

			result[0][1] = 1;
			for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= n; ++j) {
				if (!obstacleGrid[i - 1][j - 1])
					result[i][j] = result[i - 1][j] + result[i][j - 1];
			}

			return result[m][n];
		}
	};
	/*63. Unique Paths II end */


	/*62. Unique Paths (medium)
	https://leetcode.com/problems/unique-paths/
	https://discuss.leetcode.com/topic/15265/0ms-5-lines-dp-solution-in-c-with-explanations
	*/
	class Solution62 {
	public:
		int uniquePaths(int m, int n) {
			vector<vector<int>> array;

			array.resize(m + 1);

			for (int idx = 0; idx<m + 1; ++idx)
				array[idx].resize(n + 1);

			for (int row = 1; row < m + 1; ++row) {
				for (int col = 1; col < n + 1; ++col) {
					if (row == 1 || col == 1)
						array[row][col] = 1;
					else
						array[row][col] = array[row - 1][col] + array[row][col - 1];
				}
			}

			return array[m][n];
		}

		int uniquePaths1(int m, int n) {
			if (m > n) 
				return uniquePaths(n, m);

			vector<int> cur(m, 1);

			for (int j = 1; j < n; j++)
			for (int i = 1; i < m; i++)
				cur[i] += cur[i - 1];

			return cur[m - 1];
		}
	};
	/*62. Unique Paths end */


	/*70. Climbing Stairs (easy)
	https://leetcode.com/problems/climbing-stairs/
	https://discuss.leetcode.com/topic/955/easy-solutions-for-suggestions
	*/
	class Solution70 {
	public:
		int climbStairs(int n) {
			if (n < 3)
				return n;

			int a2 = 1;
			int result = 2;
			for (int i = 0; i < n - 2; ++i) {
				int tmp = result;
				result += a2;
				a2 = tmp;
			}

			return result;
		}
	};
	/*70. Climbing Stairs end */


	/*121. Best Time to Buy and Sell Stock (easy)
	https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
	https://discuss.leetcode.com/category/129/best-time-to-buy-and-sell-stock
	*/
	class Solution121 {
	public:
		int maxProfit(vector<int>& prices) {
			int max = 0, profit = 0;

			for (int nIdx = 1; nIdx < prices.size(); ++nIdx) {
				profit += prices[nIdx] - prices[nIdx - 1];

				if (profit < 0)
					profit = 0;

				if (profit > max)
					max = profit;
			}

			return max;
		}
	};
	/*121. Best Time to Buy and Sell Stock end */


	/*303. Range Sum Query - Immutable (easy)
	https://leetcode.com/problems/range-sum-query-immutable/
	*/
	class NumArray303 {
	public:
		NumArray303(vector<int> &nums) {
			int result = 0;
			numArray.push_back(0);
			for (int i = 0; i < nums.size(); ++i)
			{
				result += nums[i];
				numArray.push_back(result);
			}
		}

		int sumRange(int i, int j) {
			int result = 0;

			if (i < 0 || j < 0 || i > j || i >= numArray.size() || j >= numArray.size())
				return result;


			result = numArray[j + 1] - numArray[i];

			return result;
		}

	private:
		vector<int> numArray;
	};
	/*303. Range Sum Query - Immutable end */


	/*198. House Robber (easy)
	https://leetcode.com/problems/house-robber/
	https://discuss.leetcode.com/topic/11110/c-1ms-o-1-space-very-simple-solution
	*/
	class Solution198 {
	public:
		int rob(vector<int>& nums) {
			if (nums.empty())
				return 0;
			int len = nums.size();
			if (len == 1)
				return nums[0];
			else if (len == 2)
				return max(nums[0], nums[1]);

			int a1 = nums[0];
			int a2 = max(nums[0], nums[1]);
			int a3;

			for (int i = 3; i <= len; ++i) {
				a3 = max(a2, nums[i - 1] + a1);
				a1 = a2;
				a2 = a3;
			}

			return a3;
		}

		int rob2(vector<int>& nums) {
			int len = nums.size();

			//cur = max(pre + nums[idx], cur)
			int pre = 0, curr = 0;
			for (int nIdx = 0; nIdx < len; ++nIdx)
			{
				int tmp = max(pre + nums[nIdx], curr);

				pre = curr;
				curr = tmp;
			}

			return curr;
		}
	};
	/*198. House Robber end */
}
//////////////////////////Dynamic Programming end//////////////////////////////////////////


//////////////////////////Tag BACKTRACK//////////////////////////////////////////
namespace BACKTRACK {
	/*10. Regular Expression Matching (hard)
	https://leetcode.com/problems/regular-expression-matching/
	https://discuss.leetcode.com/topic/6183/my-concise-recursive-and-dp-solutions-with-full-explanation-in-c
	*/
	class Solution10 {
	public:
		bool isMatch1(string s, string p) {
			if (p.empty())
				return s.empty();

			if (p.size() > 1 && '*' == p[1])
				return (isMatch1(s, p.substr(2)) || !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch1(s.substr(1), p));
			else
				return (!s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch1(s.substr(1), p.substr(1)));
		}

		bool isMatch(string s, string p) {
			int m = s.size();
			int n = p.size();

			vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

			dp[0][0] = true;

			for (int j = 1; j <= n; ++j)
				dp[0][j] = j > 1 && '*' == p[j - 1] && dp[0][j - 2];

			for (int i = 1; i <= m; ++i) {
				for (int j = 1; j <= n; ++j) {
					if (p[j - 1] == '*')
						dp[i][j] = dp[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && dp[i - 1][j];
					else
						dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
				}
			}

			return dp[m][n];
		}
	};
	/*10. Regular Expression Matching end */


	/*140. Word Break II (hard)
	https://leetcode.com/problems/word-break-ii/
	https://discuss.leetcode.com/topic/12997/11ms-c-solution-concise
	https://discuss.leetcode.com/topic/27855/my-concise-java-solution-based-on-memorized-dfs
	*/
	class Solution140 {
	public:
		vector<string> combine(string word, vector<string> prev){
			for (int i = 0; i<prev.size(); ++i){
				prev[i] += " " + word;
			}
			return prev;
		}

		vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
			vector<string> result;

			if (s.empty())
				return result;

			if (m.count(s))
				return m[s];

			if (wordDict.count(s))
				result.push_back(s);

			for (int i = 1; i < s.size(); ++i) {
				string word = s.substr(i);

				if (wordDict.count(word)) {
					string rem = s.substr(0, i);
					vector<string> prev = combine(word, wordBreak(rem, wordDict));
					result.insert(result.end(), prev.begin(), prev.end());
				}
			}

			m[s] = result;
			return result;
		}

		unordered_map<string, vector<string>> m;
	};
	/*140. Word Break II end */


	/*52. N-Queens II (hard)
	https://leetcode.com/problems/n-queens-ii/
	https://discuss.leetcode.com/topic/5962/accepted-java-solution
	https://discuss.leetcode.com/topic/19741/c-solution-dfs-easy-understanding
	*/
	class Solution52 {
	public:
		bool isValid(vector<int>& columns, int col) {
			for (int i = 0; i<col; ++i) {
				if ((columns[i] == columns[col]) ||
					(col - i == columns[col] - columns[i]) ||
					(col - i == columns[i] - columns[col]))
					return false;
			}

			return true;
		}

		int totalQuess(vector<int>& columns, int col) {
			if (col == columns.size())
				return 1;

			int nTotals = 0;
			for (int row = 0; row < columns.size(); ++row) {
				columns[col] = row;
				if (isValid(columns, col))
					nTotals += totalQuess(columns, col + 1);
			}

			return nTotals;
		}

		int totalNQueens(int n) {
			vector<int> columns(n, 0);

			int nResult = 0;
			nResult = totalQuess(columns, 0);

			return nResult;
		}
	};
	/*52. N-Queens II end */


	/*51. N-Queens (hard)
	https://leetcode.com/problems/n-queens/
	https://discuss.leetcode.com/topic/13617/accepted-4ms-c-solution-use-backtracking-and-bitmask-easy-understand
	*/
	class Solution51 {
	public:
		void findqueen(int row, vector<string> &matrix, vector<int>& path) {
			if (row == m_num) {
				m_result.push_back(matrix);
				return;
			}

			bool bvalid = false;
			for (int i = 0; i < m_num; ++i) {
				bvalid = true;
				for (auto item : path) {
					int tmp_i = item / m_num;
					int tmp_j = item % m_num;

					if (row == tmp_i || i == tmp_j || abs(row - tmp_i) == abs(i - tmp_j)) {
						bvalid = false;
						break;
					}
				}

				if (bvalid) {
					matrix[row][i] = 'Q';
					path.push_back(row*m_num + i);
					findqueen(row + 1, matrix, path);
					path.pop_back();
					matrix[row][i] = '.';
				}
			}
		}

		vector<vector<string>> solveNQueens(int n) {
			if (n < 1)
				return m_result;

			vector<string> matrix(n, string(n, '.'));
			m_num = n;
			for (int i = 0; i < n; ++i) {
				vector<int> path;
				matrix[0][i] = 'Q';
				path.push_back(i);
				findqueen(1, matrix, path);
				matrix[0][i] = '.';
			}

			return m_result;
		}

		int m_num;
		vector<vector<string>> m_result;
	};
	/*51. N-Queens end */


	/*37. Sudoku Solver (hard)
	https://leetcode.com/problems/sudoku-solver/
	https://discuss.leetcode.com/topic/11327/straight-forward-java-solution-using-backtracking
	https://discuss.leetcode.com/topic/7195/sharing-my-2ms-c-solution-with-comments-and-explanations
	*/
	class Solution37 {
	public:
		bool isvalid(vector<vector<char>>& board, int i, int j, char c) {
			for (int row = 0; row < 9; ++row) {
				if (board[row][j] == c)
					return false;
			}

			for (int col = 0; col < 9; ++col) {
				if (board[i][col] == c)
					return false;
			}

			for (int row = (i / 3) * 3; row < (i / 3) * 3 + 3; ++row)
				for (int col = (j / 3) * 3; col < (j / 3) * 3 + 3; ++col) {
					if (board[row][col] == c)
						return false;
				}

			return true;
		}

		bool solve(vector<vector<char>>& board) {
			for (int i = 0; i < board.size(); ++i)
				for (int j = 0; j < board[0].size(); ++j) {
					if (board[i][j] == '.') {
						for (char c = '1'; c <= '9'; ++c) {
							if (isvalid(board, i, j, c)) {
								board[i][j] = c;
								if (solve(board))
									return true;
								else
									board[i][j] = '.';
							}
						}

						return false;
					}
				}

			return true;
		}

		void solveSudoku(vector<vector<char>>& board) {
			if (board.empty() || board[0].empty())
				return;

			solve(board);
		}
	};
	/*37. Sudoku Solver end */


	/*131. Palindrome Partitioning (medium)
	https://leetcode.com/problems/palindrome-partitioning/
	https://discuss.leetcode.com/topic/10955/clean-c-backtracking-solution
	https://discuss.leetcode.com/topic/6186/java-backtracking-solution
	*/
	class Solution131 {
	public:
		bool ispalind(const string& s, int low, int high) {
			while (low <= high) {
				if (s[low++] != s[high--])
					return false;
			}

			return true;
		}

		void dsf(const string& s, int start, vector<string>& path, vector<vector<string>>& ret) {
			if (start == s.size()) {
				ret.push_back(path);
				return;
			}

			for (int i = start; i < s.size(); ++i) {
				if (ispalind(s, start, i)) {
					path.push_back(s.substr(start, i - start + 1));
					dsf(s, i + 1, path, ret);
					path.pop_back();
				}
			}
		}

		vector<vector<string>> partition(string s) {
			vector<vector<string>> ret;
			vector<string> path;

			if (s.empty())
				return ret;

			dsf(s, 0, path, ret);
			return ret;
		}
	};
	/*131. Palindrome Partitioning end */


	/*93. Restore IP Addresses (medium)
	https://leetcode.com/problems/restore-ip-addresses/
	https://discuss.leetcode.com/topic/4742/very-simple-dfs-solution
	https://discuss.leetcode.com/topic/3919/my-code-in-java
	*/
	class Solution93 {
	public:
		vector<string> m_ret;

		void iptostr(const string& s, string & ret, int layer) {
			if (layer == 1) {
				if (s.size() > 1 && s[0] == '0')
					return;

				if (!s.empty() && s.size() < 4 && stoi(s) >= 0 && stoi(s) <= 255) {
					ret.append(".");
					ret.append(s);
					m_ret.push_back(ret);
				}

				return;
			}

			if (layer < 4)
				ret += ".";

			string str1, str2, str3;
			if (s.size() > 1) {
				str1 = ret + s.substr(0, 1);
				iptostr(s.substr(1), str1, layer - 1);
			}

			if (s.size() > 2) {
				str2 = ret + s.substr(0, 2);
				if (s[0] != '0')
					iptostr(s.substr(2), str2, layer - 1);
			}

			if (s.size() > 3) {
				str3 = s.substr(0, 3);
				if (stoi(str3) >= 0 && stoi(str3) <= 255 && s[0] != '0') {
					str3 = ret + str3;
					iptostr(s.substr(3), str3, layer - 1);
				}
			}
		}

		vector<string> restoreIpAddresses(string s) {
			if (s.empty())
				return vector<string>();

			string str("");
			iptostr(s, str, 4);

			return m_ret;
		}

		static void main() {
			Solution93* test = new Solution93;
			vector<string> result;

			string str1("25525511135");
			result = test->restoreIpAddresses(str1);
		
			delete test;
		}
	};
	/*93. Restore IP Addresses end */


	/*90. Subsets II (medium)
	https://leetcode.com/problems/subsets-ii/
	https://discuss.leetcode.com/topic/4661/c-solution-and-explanation
	https://discuss.leetcode.com/topic/13543/accepted-10ms-c-solution-use-backtracking-only-10-lines-easy-understand
	*/
	class Solution90 {
	public:
		vector<vector<int>> subsets(vector<int>& nums, int len) {
			vector<vector<int>> result, tmp;
			if (len == 1)
				return vector<vector<int>>(1, vector<int>(1, nums[len - 1]));

			if (nums[len - 1] == nums[len - 2]) {
				tmp = subsets(nums, len - 1);
				int duptotal = 0;

				for (int i = len - 2; i >= 0; --i) {
					if (nums[len - 1] == nums[i])
						++duptotal;
					else
						break;
				}

				for (auto item : tmp) {
					int dupnum = 0;

					for (int i = item.size() - 1; i >= 0; --i) {
						if (item[i] == nums[len - 1])
							dupnum++;
						else
							break;
					}

					result.push_back(item);
					if (dupnum == duptotal) {
						item.push_back(nums[len - 1]);
						result.push_back(item);
					}
				}
			}
			else {
				result.push_back(vector<int>(1, nums[len - 1]));
				tmp = subsets(nums, len - 1);

				for (auto item : tmp) {
					result.push_back(item);
					item.push_back(nums[len - 1]);
					result.push_back(item);
				}
			}

			return result;
		}

		vector<vector<int>> subsetsWithDup(vector<int>& nums) {
			if (nums.empty())
				return vector<vector<int>>();

			sort(nums.begin(), nums.end());

			vector<vector<int>> result;
			//for (int i = 0; i < nums.size(); ++i)
			{
				result = subsets(nums, nums.size());
			}

			result.push_back(vector<int>());

			return result;
		}
	};
	/*90. Subsets II end */


	/*79. Word Search (medium)
	https://leetcode.com/problems/word-search/
	https://discuss.leetcode.com/topic/9826/my-19ms-accepted-c-code
	*/
	class Solution79 {
	public:
		int m;
		int n;

		bool isfound(vector<vector<char>>& board, const char* word, int x, int y) {
			if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] == '\0' || *word != board[x][y])
				return false;

			if (*(word + 1) == '\0')
				return true;

			char tmp = board[x][y];

			board[x][y] = '\0';

			if (isfound(board, word + 1, x - 1, y) || isfound(board, word + 1, x + 1, y) ||
				isfound(board, word + 1, x, y - 1) || isfound(board, word + 1, x, y + 1))
				return true;

			board[x][y] = tmp;
			return false;
		}

		bool exist(vector<vector<char>>& board, string word) {
			if (word.empty() || board.empty() || board[0].empty())
				return false;

			m = board.size();
			n = board[0].size();

			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j) {
					if (isfound(board, word.c_str(), i, j))
						return true;
				}

			return false;
		}
	};
	/*79. Word Search end */


	/*77. Combinations (medium)
	https://leetcode.com/problems/combinations/
	https://discuss.leetcode.com/topic/3950/my-shortest-c-solution-using-dfs
	*/
	class Solution77 {
	public:
		void mycombine(vector<vector<int>> &result, vector<int> cur, int n, int k, int start) {
			if (cur.size() == k) {
				result.push_back(cur);
				return;
			}

			for (int i = start; i <= n; ++i) {
				cur.push_back(i);
				mycombine(result, cur, n, k, i + 1);
				cur.pop_back();
			}
		}

		vector<vector<int>> combine(int n, int k) {
			vector<vector<int>> result;
			if (k > n)
				return result;

			vector<int> cur;
			mycombine(result, cur, n, k, 1);
			return result;
		}
	};
	/*77. Combinations end */


	/*60. Permutation Sequence (medium)
	https://leetcode.com/problems/permutation-sequence/
	https://discuss.leetcode.com/topic/3313/most-concise-c-solution-minimal-memory-required
	https://discuss.leetcode.com/topic/17348/explain-like-i-m-five-java-solution-in-o-n
	*/
	class Solution60 {
	public:
		vector<int> m_vec;
		vector<int> m_invec;
		int m_cur;
		int m_len;

		void getPermute(int start, int k) {
			if (start >= m_len) {
				m_cur++;
				if (k == m_cur)
					m_vec = m_invec;
			}

			for (int i = start; i < m_len; ++i) {
				swap(m_invec[start], m_invec[i]);
				getPermute(start + 1, k);
				swap(m_invec[start], m_invec[i]);
			}
		}

		string getPermutation1(int n, int k) {
			if (n < 1)
				return string("");

			int tmp = k;
			for (int i = n; i >= 1; --i)
				tmp /= i;

			if (tmp > 1)
				return string("");

			m_invec.resize(n);
			for (int i = 0; i < n; ++i)
				m_invec[i] = i + 1;

			m_cur = 0;
			m_len = n;
			getPermute(0, k);

			string result;
			result.resize(n);
			for (int i = 0; i < m_vec.size(); ++i)
				result[i] = '0' + m_vec[i];
			return result;
		}

		string getPermutation(int n, int k) {
			// left part of s is partially formed permutation, right part is the leftover chars.
			string ret(n, '0');
			int i, j, f = 1;
			for (i = 1; i <= n; ++i) {
				ret[i - 1] = '0' + i; // make ret become 1234...n
				f *= i;
			}

			for (i = 0, k--; i < n; ++i) {
				f /= n - i;
				j = i + k / f; // calculate index of char to put at s[i]

				char tmp = ret[j];
				// remove c by shifting to cover up (adjust the right part)
				for (; j > i; --j)
					ret[j] = ret[j - 1];

				k %= f;
				ret[i] = tmp;
			}

			return ret;
		}
	};
	/*60. Permutation Sequence end */


	/*47. Permutations II (medium)
	https://leetcode.com/problems/permutations-ii/
	https://discuss.leetcode.com/topic/8831/a-simple-c-solution-in-only-20-lines
	*/
	class Solution47 {
	public:
		void permuteUnique1(vector<int> nums, int low, int high, vector<vector<int>>& ret) {
			if (low == high - 1) {
				ret.push_back(nums);
				return;
			}

			for (int i = low; i < high; ++i) {
				if (i != low && nums[i] == nums[low])
					continue;

				swap(nums[low], nums[i]);
				permuteUnique1(nums, low + 1, high, ret);
			}
		}

		vector<vector<int>> permuteUnique(vector<int>& nums) {

			vector<vector<int>> result;
			if (nums.empty())
				return result;

			sort(nums.begin(), nums.end());
			permuteUnique1(nums, 0, nums.size(), result);
			return result;
		}

		void recursion2(vector<int> num, int i, int j, vector<vector<int> > &res) {
			if (i == j - 1) {
				res.push_back(num);
				return;
			}

			for (int k = i; k < j; k++) {
				if (i != k && num[i] == num[k]) continue;
				swap(num[i], num[k]);
				recursion2(num, i + 1, j, res);
			}
		}

		vector<vector<int> > permuteUnique2(vector<int> &num) {
			sort(num.begin(), num.end());
			vector<vector<int> >res;
			recursion2(num, 0, num.size(), res);
			return res;
		}
	};
	/*47. Permutations II end */


	/*46. Permutations (medium)
	https://leetcode.com/problems/permutations/
	https://discuss.leetcode.com/topic/5881/my-elegant-recursive-c-solution-with-inline-explanation
	*/
	class Solution46 {
	public:
		vector<vector<int>> result;

		vector<vector<int>> permute(vector<int>& nums) {
			int size = nums.size();
			if (size < 1)
				return result;
			result = mypermute(nums, size);
			return result;
		}

		void permuteRecursive(vector<int> &num, int begin, vector<vector<int> > &result) {
			if (begin >= num.size()) {
				// one permutation instance
				result.push_back(num);
				return;
			}

			for (int i = begin; i < num.size(); i++) {
				swap(num[begin], num[i]);
				permuteRecursive(num, begin + 1, result);
				// reset
				swap(num[begin], num[i]);
			}
		}

		vector<vector<int>> mypermute(vector<int>& nums, int size) {
			if (size == 1)
			{
				vector<vector<int>> tmp;
				tmp.push_back(vector<int>(1, nums[0]));
				return tmp;
			}

			vector<vector<int>> cur;
			for (int i = 0; i < size; ++i)
			{
				swap(nums[i], nums[size - 1]);
				vector<vector<int>> tmp = mypermute(nums, size - 1);
				for (int j = 0; j < tmp.size(); ++j)
				{
					tmp[j].push_back(nums[size - 1]);
					cur.push_back(tmp[j]);
				}

				swap(nums[i], nums[size - 1]);
			}

			return cur;
		}
	};
	/*46. Permutations end */


	/*216. Combination Sum III (medium)
	https://leetcode.com/problems/combination-sum-iii/
	https://discuss.leetcode.com/topic/14641/my-c-solution-backtracking
	*/
	class Solution216 {
	public:
		void combinationSum(vector<vector<int>>&result, vector<int> cur, int k, int n) {
			if (cur.size() == k && n == 0) {
				result.push_back(cur);
				return;
			}

			if (cur.size() < k) {
				for (int i = (cur.size() > 0 ? cur.back() + 1 : 1); i <= 9; ++i) {
					if (n - i < 0)
						break;

					cur.push_back(i);
					combinationSum(result, cur, k, n - i);
					cur.pop_back();
				}
			}
		}

		vector<vector<int>> combinationSum3(int k, int n) {
			vector<int> cur;
			vector<vector<int>> result;

			combinationSum(result, cur, k, n);

			return result;
		}
	};
	/*216. Combination Sum III end */


	/*40. Combination Sum II (medium)
	https://leetcode.com/problems/combination-sum-ii/
	https://discuss.leetcode.com/topic/8916/c-backtracking-solution-with-detailed-explanation
	*/
	class Solution40 {
	public:
		vector<vector<int>> dsf(vector<int>& candidates, int target, int start) {
			vector<vector<int>> ret;

			if (start >= candidates.size() || candidates[start] > target)
				return ret;

			if (target == candidates[start]) {
				ret.push_back(vector<int>(1, target));
				return ret;
			}

			vector<vector<int>> withtar = dsf(candidates, target - candidates[start], start + 1);
			int begin = start + 1;

			while (begin < candidates.size() && candidates[begin] == candidates[start])
				begin++;

			vector<vector<int>> withouttar = dsf(candidates, target, begin);

			for (auto item : withtar) {
				item.insert(item.begin(), candidates[start]);
				ret.push_back(item);
			}

			for (auto item : withouttar)
				ret.push_back(item);

			return ret;
		}

		vector<vector<int>> combinationSum3(vector<int>& candidates, int target) {
			vector<vector<int>> result;

			sort(candidates.begin(), candidates.end());

			if (candidates.empty() || target < candidates[0])
				return result;

			result = dsf(candidates, target, 0);
			return result;
		}

		void dsf(vector<int>& candidates, int target, int start, vector<vector<int>>& ret, vector<int>& locaret) {
			if (target == 0) {
				ret.push_back(locaret);
				return;
			}

			for (int i = start; i < candidates.size(); ++i) {
				if (candidates[i] > target)
					return;

				if (i && candidates[i - 1] == candidates[i] && i > start)
					continue;

				locaret.push_back(candidates[i]);
				dsf(candidates, target - candidates[i], i + 1, ret, locaret);
				locaret.pop_back();
			}
		}

		vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
			vector<vector<int>> result;
			vector<int> localret;

			sort(candidates.begin(), candidates.end());
			if (candidates.empty() || target < candidates[0])
				return result;

			dsf(candidates, target, 0, result, localret);
			return result;
		}
	};
	/*40. Combination Sum II end */


	/*39. Combination Sum (medium)
	https://leetcode.com/problems/combination-sum/
	https://discuss.leetcode.com/topic/14654/accepted-16ms-c-solution-use-backtracking-easy-understand/2
	*/
	class Solution39 {
	public:
		vector<vector<int>> combine(vector<int>& candidates, int nums, int target) {
			vector<vector<int>> result;

			if (nums == 1) {
				if (candidates[0] == target)
					result.push_back(vector<int>(1, target));
				else {
					int count = target / candidates[0];
					if (target % candidates[0] == 0)
						result.push_back(vector<int>(count, candidates[0]));
				}
			}
			else {
				vector<vector<int>> tmp;
				if (candidates[nums - 1] == target) {
					result.push_back(vector<int>(1, target));

					tmp = combine(candidates, nums - 1, target);

					for (auto item : tmp)
						result.push_back(item);
				}
				else if (candidates[nums - 1] > target) {
					tmp = combine(candidates, nums - 1, target);

					for (auto item : tmp)
						result.push_back(item);
				}
				else {
					int count = target / candidates[nums - 1];

					while (count >= 0) {
						tmp = combine(candidates, nums - 1, target - count*candidates[nums - 1]);

						for (auto item : tmp) {
							item.insert(item.end(), count, candidates[nums - 1]);
							result.push_back(item);
						}

						--count;
					}
				}
			}

			return result;
		}

		vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
			if (candidates.empty())
				return vector<vector<int>>();

			sort(candidates.begin(), candidates.end());

			if (target < candidates[0])
				return vector<vector<int>>();

			return combine(candidates, candidates.size(), target);
		}

		vector<vector<int> > combinationSum1(vector<int> &candidates, int target) {
			sort(candidates.begin(), candidates.end());
			vector<vector<int> > res;
			vector<int> combination;
			combinationSum(candidates, target, res, combination, 0);
			return res;
		}

		void combinationSum(std::vector<int> &candidates, int target, std::vector<std::vector<int> > &res, std::vector<int> &combination, int begin) {
			if (0 == target) {
				res.push_back(combination);
				return;
			}

			for (int i = begin; i != candidates.size() && target >= candidates[i]; ++i) {
				combination.push_back(candidates[i]);
				combinationSum(candidates, target - candidates[i], res, combination, i);
				combination.pop_back();
			}
		}
	};
	/*39. Combination Sum end */


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
	class Solution42 {
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


	/*215. Kth Largest Element in an Array (meduim)
	The followings are n log(n) for complexity and O(1) for space. 
	We can use priority_queue, which will cause
	n log(k) for complexity and log (k) for space.
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

			//right must point to the last element which is larger than pivot
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
	https://discuss.leetcode.com/topic/20314/accepted-java-o-n-solution-in-5-lines
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


		vector<vector<int>> subsets2(vector<int>& nums) {
			sort(nums.begin(), nums.end());
			vector<vector<int>> subs;
			vector<int> sub;
			genSubsets(nums, 0, sub, subs);
			return subs;
		}

		void genSubsets(vector<int>& nums, int start, vector<int>& sub, vector<vector<int>>& subs) {
			subs.push_back(sub);
			for (int i = start; i < nums.size(); i++) {
				sub.push_back(nums[i]);
				genSubsets(nums, i + 1, sub, subs);
				sub.pop_back();
			}
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
		unsigned int reverseBits1(unsigned int n) {
			int len = sizeof(unsigned int)* 8;
			unsigned int result = 0;
			for (int i = 0; i < len; ++i) {
				if ((1 << i) & n)
					result = result | (1 << (len - i - 1));
			}

			return result;
		}

		unordered_map<char, int> maps;

		unsigned int reverseone(char c) {
			if (maps.count(c))
				return maps[c];

			unsigned int result = 0;
			for (int i = 0; i < 8; ++i) {
				result += (c >> i) & 1;
				if (i < 7)
					result <<= 1;
			}

			maps[c] = result;
			return result;
		}

		unsigned int reverseBits(unsigned int n) {
			char bits[4];

			for (int i = 0; i < 4; ++i)
				bits[i] = (n >> (i * 8)) & 0xFF;

			unsigned int result = 0;
			for (int i = 0; i < 4; ++i) {
				result += reverseone(bits[i]);
				if (i < 3)
					result <<= 8;
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

	class Solution536 {
	public:
		TreeNode* str2tree(string s) {
			if (s.empty())
				return NULL;

			stringstream strtmp(s);
			int val;
			string childs = "";

			strtmp >> val >> childs;

			TreeNode* node = new TreeNode(val);

			int left = 0;
			stack<char> parents;
			for (int i = 0; i < childs.size(); ++i)
			{
				if ('(' == childs[i])
					parents.push('(');
				else if (')' == childs[i])
				{
					if (1 == parents.size())
					{
						left = i + 1;
						break;
					}
					else
						parents.pop();
				}
			}

			if (left > 0)
				node->left = str2tree(childs.substr(1, left - 2));

			if (!childs.empty() && left < childs.size())
				node->right = str2tree(childs.substr(left + 1, childs.size() - left - 2));

			return node;
		}
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

		TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
			//iterative solution

			unordered_map<TreeNode*, TreeNode*> mm;
			mm[root] = NULL;
			queue<TreeNode*> qq;
			qq.push(root);

			//get the parent child nodes
			while (mm.count(p) == 0 || mm.count(q) == 0){
				TreeNode* tmp = qq.front();
				qq.pop();
				if (tmp->left){
					mm[tmp->left] = tmp;
					qq.push(tmp->left);
				}
				if (tmp->right){
					mm[tmp->right] = tmp;
					qq.push(tmp->right);
				}
			}

			//get path from root to p
			unordered_set<TreeNode*> ss;
			while (p != NULL){
				ss.insert(p);
				p = mm[p];
			}

			//check the lowerst common parent in above path
			while (ss.count(q) == 0){
				q = mm[q];
			}

			return q;
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


	/*333. Largest BST Subtree (medium)
	https://leetcode.com/problems/largest-bst-subtree/
	*/
	class Solution333 {
	public:
		
		bool checkBST(TreeNode* cur, int& max_val, int& min_val, int& nodenum) {
			if (NULL == cur) {
				nodenum = 0;
				return true;
			}

			nodenum = 0;
			int leftnum = 0, rightnum = 0;
			int lmax, rmax, lmin, rmin;
			bool bleft = checkBST(cur->left, lmax, lmin, leftnum);
			bool bright = checkBST(cur->right, rmax, rmin, rightnum);

			if (bleft && bright) {
				if ((!cur->left || cur->val >= lmax) && (!cur->right || cur->val <= rmin))
				{
					min_val = cur->left ? lmin : cur->val;
					max_val = cur->right ? rmax : cur->val;
					nodenum = leftnum + rightnum + 1;
					return true;
				}
				
			}
			
			nodenum = max(leftnum, rightnum);
			return false;
		}

		int largestBSTSubtree(TreeNode* root) {
			int num = 0;
			int leftmin, rightmax;
			checkBST(root, leftmin, rightmax, num);
			return num;
		}

		static void main(int *a, int b) {
			auto_ptr<Solution333> test(new Solution333);
			int result = 0;
			TreeNode node1(1);
			TreeNode node2(2);

			node1.left = &node2;
			result = test->largestBSTSubtree(&node1);
		}
	};
	/*333. Largest BST Subtree end */

	void main()
	{
		Solution536 test536;
		TreeNode* root536 = test536.str2tree("4(2(3)(1))(6(5))");

		delNode(root536);
	}
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
			queue<TreeNode*> nodes;

			vector<int> result;
			if (NULL == root)
				return result;

			nodes.push(root);
			TreeNode* tmp = NULL;

			while (!nodes.empty())
			{
				result.push_back(nodes.back()->val);
				int count = nodes.size();
				while (count--) {
					tmp = nodes.front();
					nodes.pop();
					if (tmp->left)
						nodes.push(tmp->left);

					if (tmp->right)
						nodes.push(tmp->right);
				}
			}

			return result;

		}

		vector<int> rightSideView1(TreeNode* root) {
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

					//next level is not empty and add NULL as its terminator
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


/*460. LFU Cache (hard)
https://leetcode.com/problems/lfu-cache/
*/
class LFUCache460 {
public:
	LFUCache460(int capacity) {
		max_num = capacity;
	}

	int get(int key) {
		if (0 == cache.count(key))
			return -1;

		int val = cache[key].first;
		data.erase(cache[key].second);

		data.push_front(key);
		cache[key] = { val, data.begin() };
		return val;
	}

	void put(int key, int value) {
		if (cache.count(key))
			data.erase(cache[key].second);
		else {
			if (data.size() == max_num) {
				cache.erase(data.back());
				data.pop_back();
			}
		}

		data.push_front(key);
		cache[key] = { value, data.begin() };
	}

	int max_num;
	list<int> data;
	unordered_map<int, pair<int, list<int>::iterator>> cache;
};
/*460. LFU Cache end*/


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

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who 
	the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
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

		//this can be bypassed because make_heap default sort is increasing
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
			//no need for this check because only need return the 
			//10 latest whatever it is duplicate.
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
	//user index,(time, twiid)
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

	/*time O(n *  k ^ 2), space O(n)*/
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
				if (isPalin(str1)) {
					string str2rev = str2;
					reverse(str2rev.begin(), str2rev.end());

					if (dict.count(str2rev) > 0 && dict[str2rev] != i){
						vec[0] = dict[str2rev];
						vec[1] = i;
						result.push_back(vec);
					}
				}

				if (isPalin(str2)) {
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
			//erase will erase all the same value, but it is safe
			//because if there are duplicate elements, 
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



/*277. Find the Celebrity (Medium)*/
/*O() time O() space*/
bool knows(int a, int b) { return false; }

class Solution277 {
public:
	int findCelebrity(int n) {
		unordered_map<int, int> indegree;
		unordered_map<int, int> outdegree;

		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (knows(i, j)) {
					indegree[j] ++;
					outdegree[i] ++;
				}

				if (knows(j, i)) {
					indegree[i] ++;
					outdegree[j] ++;
				}
			}
		}

		for (auto it = outdegree.begin(); it != outdegree.end(); ++it) {
			if (it->second == n - 1 && 0 == indegree[it->first])
				return it->first;
		}

		return -1;
	}
};
/*277. Find the Celebrity end*/



namespace MYTEST {
	class MyClass
	{
	public:
		MyClass() {}
		~MyClass() {}
		
		int maxSubstr(const string input) {
			int n = input.size();
			vector<int> t(n, 1);
			int result = 0;

			for (int i = 0; i < n; ++i) {
				for (int j = i - 1; j >= 0; --j)
					if (input[i] > input[j]) {
						t[i] = t[j] + 1;
						break;
					}

				result = max(result, t[i]);
			}

			return result;
		}

		static void main() {
				MyClass* test = new MyClass;

				string input1("12345");
				string input2("54321");
				string input3("23145");
				string input4("24135");
				string input5("25341");
				string input6("11111");

				cout << "case 1:" << test->maxSubstr(input1) << ",5" << endl;
				cout << "case 2:" << test->maxSubstr(input2) << ",1" << endl;
				cout << "case 3:" << test->maxSubstr(input3) << ",3" << endl;
				cout << "case 4:" << test->maxSubstr(input4) << ",3" << endl;
				cout << "case 5:" << test->maxSubstr(input5) << ",3" << endl;
				cout << "case 6:" << test->maxSubstr(input6) << ",1" << endl;
				delete test;
			}
		};
}
/*********************uber begin************************/
namespace UBER {
	class MyIsland
	{
	private:
		const char LEFT = '/';
		const char RIGHT = '\\';

		enum DIREC {
			TOD	= 1,
			TOU,
			TOR,
			TOL,
		};

		const int NOVISIT	= 0;
		const int UP		= 1;
		const int DOWN		= 2;
		const int VISITED	= 3;

		int res;

	public:
		int CountArea(vector<vector<char>> matrix) {
			if (matrix.empty() || matrix[0].empty())
				return 0;

			int row = matrix.size();
			int col = matrix[0].size();
			vector<vector<int>> visit(row, vector<int>(col, NOVISIT));

			res = row * col * 2;

			for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j) {
				if (VISITED != visit[i][j]) 
				{
					if (LEFT == matrix[i][j]) {
						if (UP != (UP & visit[i][j])) {
							DfsArea(matrix, i, j, TOL, UP, visit);
							DfsArea(matrix, i, j, TOU, UP, visit);
						}
						
						if (DOWN != (DOWN & visit[i][j]))
						{
							DfsArea(matrix, i, j, TOD, DOWN, visit);
							DfsArea(matrix, i, j, TOR, DOWN, visit);
						}
					}
					else {// '\'
						if (UP != (UP & visit[i][j])) {
							DfsArea(matrix, i, j, TOR, UP, visit);
							DfsArea(matrix, i, j, TOU, UP, visit);
						}

						if ((DOWN != (DOWN & visit[i][j]))) {
							DfsArea(matrix, i, j, TOD, DOWN, visit);
							DfsArea(matrix, i, j, TOL, DOWN, visit);
						}
					}
				}
			}

			return res;
		}

		void DfsArea(vector<vector<char>>& matrix, int i, int j, DIREC direct, int cur, vector<vector<int>>& flag) {
			if (i < 0 || j < 0 || i >= matrix.size() || j >= matrix[0].size())
				return;

			int row = matrix.size();
			int col = matrix[0].size();
			
			flag[i][j] |= cur;
			if (TOD == direct && i + 1 < row) {			
				if (LEFT == matrix[i + 1][j] && UP != (flag[i + 1][j] & UP)) {
					--res;
					DfsArea(matrix, i + 1, j, TOL, UP, flag);
				}
				else if (RIGHT == matrix[i + 1][j] && UP != (flag[i + 1][j] & UP)) {
					--res;
					DfsArea(matrix, i + 1, j, TOR, UP, flag);
				}
			}
			else if (TOU == direct && i > 0) {
				
				if (LEFT == matrix[i - 1][j] && DOWN != (flag[i - 1][j] & DOWN)) {
					--res;
					DfsArea(matrix, i - 1, j, TOR, DOWN, flag);
				}
				else if (RIGHT == matrix[i - 1][j] && DOWN != (flag[i - 1][j] & DOWN)) {
					--res;
					DfsArea(matrix, i - 1, j, TOL, DOWN, flag);
				}
			}
			else if (TOR == direct && j + 1 < col) {			
				if (LEFT == matrix[i][j + 1] && UP != (flag[i][j + 1] & UP)) {
					--res;
					DfsArea(matrix, i, j + 1, TOU, UP, flag);
				}
				else if (RIGHT == matrix[i][j + 1] && DOWN != (flag[i][j + 1] & DOWN)) {
					--res;
					DfsArea(matrix, i, j + 1, TOD, DOWN, flag);
				}
			}
			else if (TOL == direct && j > 0) {
				
				if (LEFT == matrix[i][j - 1] && DOWN != (flag[i][j - 1] & DOWN)) {
					--res;
					DfsArea(matrix, i, j - 1, TOD, DOWN, flag);
				}
				else if (RIGHT == matrix[i][j - 1] && UP != (flag[i][j - 1] & UP)) {
					--res;
					DfsArea(matrix, i, j - 1, TOU, UP, flag);
				}
			}
		}

		static void main() {
			/*result = 5*/vector<vector<char>> case1 = { { '/', '\\' }, { '\\', '/' } }; 
			/*result = 4*/vector<vector<char>> case2 = { { '\\', '\\' },{ '/', '\\' } };
			/*result = 4*/vector<vector<char>> case3 = { { '\\', '\\' },{ '\\', '/' } };
			/*result = 6*/vector<vector<char>> case4 = { { '\\', '\\' , '\\' },{ '\\', '/', '/' },{ '\\', '/', '/' } };
			/*result = 4*/vector<vector<char>> case5 = { { '\\' }, { '\\' },{ '\\' } };
			/*result = 4*/vector<vector<char>> case6 = { { '/' },{ '/' },{ '/' } };

			MyIsland* pIns = new MyIsland;
			int result = pIns->CountArea(case1);

			result = pIns->CountArea(case2);
			result = pIns->CountArea(case3);
			result = pIns->CountArea(case4);
			result = pIns->CountArea(case5);
			result = pIns->CountArea(case6);
		}
	};
}

/*********************uber begin************************/

using namespace UBER;
using namespace BFS;
using namespace DFS;
using namespace TREE;
using namespace BIT;
using namespace SORT;
using namespace GREEDY;
using namespace HEAP;
using namespace STACK;
using namespace BACKTRACK;
using namespace DP;
using namespace BS;
using namespace STRING;
using namespace MATH;
using namespace LLIST;
using namespace MYTEST;
using namespace GG;
using namespace AIR;
using namespace AM;
using namespace OOD;
using namespace EB;

int test(int* a, int &b, int c[]) {
	int result = *a + b;
	c[0] = 1;
	return result;
}

/*respondent, manager, and director begin*/ 
void Employee::ReceiveCall(Call* incall){
}

void Employee::HandledCall(Call* incall) {
	free = true;
}

void Employee::NotHandledCall(Call* incall) {
	incall->rank++;
	callhandle->dispatchCall(incall);
	free = true;

	callhandle->getNextCall(this);
}

Employee* CallHandler::getCallHandler(Call* incall){
	Employee* emp = NULL;
	for (int rank = incall->rank; rank < LEVEL; ++rank){
		for (auto item : emplevels[rank])
			if (item->free)
				return item;
	}

	return emp;
}

void CallHandler::dispatchCall(Call* incall){
	Employee* emp = getCallHandler(incall);

	if (NULL == emp)
		callque.push(incall);
	else
		emp->ReceiveCall(incall);
}
/*respondent, manager, and director end*/

/*file system begin*/
string Entry::getFullPath() {
	 if (parent == NULL) return name;
	 else return parent->getName() + "/" + name;
}


int Directory::getSize() {
	int ret = 0;
	for (auto it : contents)
		ret += it->getSize();
	return ret;
}
/*file system end*/

class TestTT {
public:
	
	int i;
	int & j;
};


class TestPoint
{
public:
	void show() { cout << "TestPoint::show()" << endl; }
	TestPoint() { cout << "TestPoint::TestPoint():" << this << endl; }
	~TestPoint() { cout << "TestPoint::~TestPoint():" << this << endl; }
	TestPoint(TestPoint&other){ cout << "TestPoint::TestPoint(TestPoint&other):" << this << endl; }

	TestPoint& operator = (const TestPoint&other) {
		return *this;

	}

	void testconst1()
	{
		if (pInst == nullptr)
			this->pInst = new TestPoint();
	}

	void testconst() const
	{
		if (pInst == nullptr)
			this->pInst = new TestPoint();
	}


	mutable TestPoint* pInst;
};

class TestisBst {
public:
	bool isBst(const vector<int>& nums) {
		return Bst(nums, 0, INT_MIN, INT_MAX) == nums.size();
	}

	int Bst(const vector<int>& nums, int index, int minval, int maxval) {
		if (index < nums.size() && nums[index] >= minval && nums[index] <= maxval)
			return Bst(nums, Bst(nums, index + 1, minval, nums[index]), nums[index], maxval);

		return index;
	}

	void test()
	{
		vector<int> nums1 = { 1, 2, 3 };
		vector<int> nums2 = { 3, 2, 1 };
		vector<int> nums3 = { 2, 1, 3 };

		vector<int> nums4 = { 4, 2, 1, 3 };

		cout << isBst(nums1) << endl;
		cout << isBst(nums2) << endl;
		cout << isBst(nums3) << endl;
		cout << isBst(nums4) << endl;
	}

	static void main() {
		TestisBst* pins = new TestisBst();
		pins->test();
	}
};

namespace STL_TEST{
	class Widget
	{
	public:
		Widget() { cout << "Widget()" << endl; }
		Widget(double weight) { val = weight;  cout << "Widget(double weight)" << endl; }
		~Widget(){ cout << "Widget()" << endl; }
		
		Widget& operator = (double weight) { val = weight; cout << "operator =" << endl; return *this; }
		Widget(const Widget& other) { val = other.val;  cout << "Widget(const Widget& other)" << endl; }

	private:
		double val;
	};

	template<typename MapType, typename KeyArgType, typename ValueArgType>
	typename MapType::iterator
		efficientAddOrUpdate(MapType& m,
		const KeyArgType& k,
		const ValueArgType& v)
	{
		typename MapType::iterator lb =				// find where k is or should
			m.lower_bound(k);						// go; see page 7 for why
		// "typename" is needed
		// here 

		if (lb != m.end() &&						// if lb points to a pair
			!(m.key_comp()(k, lb->first))) {	// whose key is equiv to k...
			lb->second = v;							// update the pair's value
			return lb;								// and return an iterator
		}											// to that pair
		else {
			typedef typename MapType::value_type MVT;
			return m.insert(lb, MVT(k, v));			// add pair(k, v) to m and
		}											// return an iterator to the
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	{
		char* testcc1 = "hello";
		char* testcc2 = "hello";
		string testk12 = "";
		string testk1("test test1");

		testk12 += testk1[0];
		stringstream streamkk(testk1);

		string outk1;
		while (streamkk >> outk1)
			cout << outk1 << endl;
		
		EB::EB_main();
		VM::VM_Main();
		AIR::main();

		TestisBst::main();
		set<string*, less<string*>, allocator<string*>> ssp; // ssp = “set of string ptrs”

		TestPoint kk;

		kk.testconst();
		ssp.insert(new string("Anteater"));
		ssp.insert(new string("Wombat"));
		ssp.insert(new string("Lemur"));
		ssp.insert(new string("Penguin"));

		for (set<string*>::const_iterator i = ssp.begin(); i != ssp.end(); ++i)
			cout << (*i)->substr(0) << endl;

		//copy(ssp.begin(), ssp.end(), ostream_iterator<string>(cout, "\n"));
		vector<int> testdel = { 1, 2, 6, 6, 5, 6, 7 };
		vector<bool> testde2(10);
		string kktest;

		cout << testdel.max_size() << "," << sizeof(testdel) << endl;
		cout << kktest.max_size() << "," << sizeof(kktest) << endl;
		testdel.erase(remove(testdel.begin(), testdel.end(), 6), testdel.end());
		auto_ptr<TestPoint> p1(new TestPoint);
		cout << p1.get() << endl;
		auto_ptr <TestPoint> p2(p1);
		cout << p2.get() << endl;
		p2->show();

		vector<auto_ptr<TestPoint>> widgets;
		//widgets.push_back(p2);
		//cout << p2.get() << endl;
	}

	cout << "TestTT:" << sizeof(TestTT) << endl;
	UBER::MyIsland::main();
	
	TREE::main();
	{
		char *test = "*test 0123456 kk";
		int istan = -3;
		/*char ddkk1[] = "123";
		char ddkk2[] = "123456789";
		char ddkk3[] = "12";
		char ddkk4[] = "1";*/

		char* ddkk[5] = { "123", "123456789", "12", "1", "1" };

		int amout1, amout2;
		char stan[100];
		memset(stan, 0x00, sizeof(stan));
		for (int i = 0; i < 5; ++i)
		{
			amout1 = 0, amout2 = 0;
			amout1 = atoi(ddkk[i]) / 100;
			amout2 = atoi(ddkk[i]) % 100;

			memset(stan, 0x00, sizeof(stan));
			sprintf(stan, "%05d.%02d", amout1, amout2);
		}

		istan <<= 1;
		

		//sprintf(stan, "%-5.2f,%-5.2f,%-5.2f,%-5.2f", ddkk1, ddkk2, ddkk3, ddkk4);
		memset(stan, 0x00, sizeof(stan));
		sscanf(test, "%*s %s", stan);
		sscanf(test, "%*s %d", &istan);
		printf("%5.5s,%08.8s,%-8.8s:end\n",test, test,test);
#if 0
		string str(100000000, 'a');

		time_t t1 = time(0);
		for (int i = 0; i < str.length(); ++i) {
			char tmp = str[i];
		}

		time_t t2 = time(0);

		long seconds = difftime(t2, t1);
		cout << seconds << endl;

		time_t t3 = time(0);
		int len = str.length();
		for (int i = 0; i < len; ++i) {
			char tmp = str[i];
		}

		time_t t4 = time(0);

		long seconds2 = difftime(t4, t3);
		cout << seconds2 << endl;
#endif
	}

	GG::Solution218::main();
	int a, b = 1;
	Solution333::main(&a, b);
	NV::main();
	TW::main();
	DP::Solution300::main();
	AM::main();
	Solution186::main();

	GG::Codec297::main();
	Sys::main();
	VM::main();
	
	printf("1=%0.7f\n", 0.55);
	printf("2=%.07f\n", 0.55);
	printf("3=%.7f\n", 0.55);

	printf("%.6f\n", 0.5555555f);
	printf("%.5f\n", 0.555555f);
	printf("%.4f\n", 0.55555f);
	printf("%.3f\n", 0.5555f);
	printf("%.2f\n", 0.555f);
	printf("%.1f\n", 0.55f);

	float aa1 = 0.54;
	std::cout << std::fixed << std::setprecision(1) << aa1;
	int aa = 1;
	int bb = 2;
	int cc[2] = { 0 };

	test(&aa, bb, cc);
	cout << __cplusplus << endl;
	GG::main();
	MyClass::main();
	Solution24::main();
	Solution149::main();
	Solution166::main();
	Solution76::main();
	Solution28::main();
	Solution29::main();
	Solution322::main();
	Solution93::main();
	Solution84::main();
	Solution85::main();
	//Solution239::main();
	GG::Solution313::main();
	//Solution321::main();
	Solution164::main();
	//Solution318::main();
	Solution137::main();
	Solution187::main();
	Solution236::main();
	Solution94::main();
	Solution105::main();
	Solution114::main();
	Solution106::main();
	Solution109::main();
	DFS::Solution257::main();
	Solution301::main();
	Solution126::main();
	Solution199::main();
	Solution107::main();
	Solution111::main();
	Solution102::main();
	Solution101::main();
	//GG::Solution310::main();
	//GG::Solution133::main();
	//Codec297::main();
	//LRUCache146::main();
	//GG::Solution128::main();
	GG::Solution200::main();
	GG::Solution200::main();
	Solution130::main();
	//MedianFinder295::main();
	//BSTIterator173::main();
	Twitter355::main();
	//PeekingIterator284::main();
	Stack225::main();
	MinStack155_2::main();
	GG::MinStack155::main();
	//Solution329::main();
	Solution210::main();
	Solution207::main();
	//Solution336::main();
	//Solution212::main();
	WordDictionary211::main();
	//Trie208::main();
	//Solution218::main();
	//Solution327::main();
	//Solution315::main();
	SummaryRanges352::main();
	Solution220::main();
	SnakeGame::main();

	return 0;
}

#if 0
.Customer Obsession
.Dive Deep
.Think Big
.Ownership

{/*preparation*/
 1. Go over CRACKING the CODING INTERVIEW
	 http://www.hawstein.com/posts/ctci-solutions-contents.html
 2. System Design
	 1) 7.1 Deck of Cards :
	 2) Parking lot
	 3) Tiny URL
	 4) Elevator
 3. Example for every leadership principle
 4. LC AM tag
 5. http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=273331&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%255B3046%255D%255Bvalue%255D%3D5%26searchoption%255B3046%255D%255Btype%255D%3Dradio&page=1
 6. Design pattern


	 http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=209651&extra=page%3D7%26filter%3Dsortid%26sortid%3D192%26sortid%3D192&mobile=2
 Example for leadership :
1. Customer Obsession
Customer wants to switch part of transaction to other bank due to cost reason.They
dont want to change the preprocesing and worry about the feasiblity and complecity
the transfer.Which may have impact on current transaction.When PM talked with me about
it.I investigate the current design and new bank specification, list out all the possibility
and steps that will need for the transfer and let client know where is risk for this transfer.
PM try to show them our analysis and I did some demo at the same time.Finally they accept
our proposal and start the work order for the transfer.

2. Ownership
Customer wants a new bank interface to handle some of the transaction, but you know, both the
front - end and back - end are coming from the 3rd party, only the gateway, which can be seen as middleware
is from our company.And the 3rd party doesnt want to provide the sample trace in our format.Even
I tried to make out the mapping information 3rd party still dont want to confirm.
At this point, I gave cutomer to some suggestions : one is using the real bank link connection for testing,
second based on our previous experience, I initial the mapping informaiton and then disscuss with the client.
third, when I fininshed the implementation, I'll release it to our QA and them as well.
Finnally we make a great progress on this project.Expecially during the testing, based on the real trace,
3rd party begin to check it and make some change in their side.

3. Invent and Simplify
Design one new preprocess module to handle the message from the front - end.
After investigation, only this customer uses this framework and the existing preprocess
modules have lots of depandency due to the legacy reason.So I talked to the manager to use
the same interface but new logic to simplify the implementation.Manage totally agrees with me.
Use the way, when the new module is released to QA, there is no big issue found in their testing.
And the delivery date is one week before the deadline.Customer is very satisfied because they
have more time for their testing in the lab.

4. Are Right, A Lot
(i.e.there were a number of possible solutions).How did you decide the best way forward ?
In Leica, we start a new project, build a new system from the scratch.After investigation and
analysis, I suggest the team be build the new UI interface because in the old system.It's a little bit
complicate due to legacy reason.When I talked to the PM about this design and he said we
should keep the UI interface the same as old.We discuss lots about this.And both agree that
it's hard change the customer's behaviour.And use PM's suggestion. After this new product came out,
when some old customer swith to this new product, they feel great because the new operation is
almost the same as old one.

5. Learn and Be Curious

6. Hire and Develop the Best

7. Insist on the Highest Standards

8. Think Big

9. Bias for Action

10. Frugality

11. Earn Trust

12. Dive Deep

13. Have Backbone; Disagree and Commit

14. Deliver Results


•Give me an example of a time when something you tried to accomplish and failed.
(at career start, try to take ownership of something but fail due to deep knowledge of the who framework.
At career start, I just to prove myselft.So I aks PM to allocate one of the project to me.
At that time, based on my understanding, I thought that project will be easy for me.
When I looking into the design document and the implementation.And talked it with some
senior member, I found it's hard for me to delivery on time. When I realized that, I talked to PM
and asks for more time.At the same time, I asked some help from the other members.
And finally delivery the project on shedule.
Sometime you may fail something, but try your best and overcome it and you'll learn lots from that
especially in your career startup)

•Give me an example of when you showed initiative and took the lead.
(When I joinde N*S, which provide payment terminal for one of the major bank.
They are before the production for one new model.Although, there are some tools
for the automatically testing in development team.But I think it's not enough and efficiency is a little
bit low especially before the production stage.So I talked to PM and asked him to add some extral functions
for current testing in development team. When he heard about this, he's very happy because every one in the 
team is busy and this is the right time for me to do this job. 
Based on the current logic, I create some funtionality for the volumn testing. When we run this new funcions 
in the some midnights, we caught some crash problem in the volume testing.
Based on the system log, we make quick fix. At last, this product will delivery on time without any serious bugs.)

•Give me an example of a time when you motivated others.
•Tell me about a time when you delegated a project effectively.
(Cutomer need new feature and need to negotiate with 3rd party)
•Give me an example of a time when you used your fact - finding skills to solve a problem.
(Volume testing and crash.)
Focus communication, don't go too one sided.
}

Responsibilities:
Design, develop, and manage highly available and scalable systems
Monitor site reliability, availability, and performance
Scale infrastructure and implement new solutions
Take ownership of the features / services you work on - from development through deployment and verification, to adding everyday monitoring
Willing to be part of a regular on call rotation
Identify technical requirements in product meetings and assist the business team with realistic project planning
Requirements :
Strong coding skills; Java is our language of choice, as it is primarily used by the Infrastructure Team
Familiarity with MySQL
Some monitoring tools skills; we currently use Kibana and Wavefront for metrics
Superior problem - solving skills
Experience with any of the following open source services : Redis, Memecache, Kafka
Bachelor's degree, or above, in computer science or other engineering discipline, or equivalent work experience
Nice to have :
Interest in learning new technologies
Experience with a cloud platform : AWS, Google Cloud, Rackspace, ect.
Experience with Docker and some orchestration technologies; Kubernetes, Swarm, ect.
Experience with scalable and highly available distributed systems
Past exposure to Android based clients or Netty framework
Previous experience in payments industry

#endif


#if 0
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=273331&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%255B3046%255D%255Bvalue%255D%3D5%26searchoption%255B3046%255D%255Btype%255D%3Dradio&page=1
system desin
1. design library, track records of books, CDs(cc150)

2. chess game

http ://amitcodes.com/2014/02/04/object-oriented-design-for-chess-game/

http://stackoverflow.com/questions/4168002/object-oriented-design-for-a-chess-game

3. hotel management system(similar to online reader system in cc150, libary contains rooms, active room, active user)

4. online booking system(cc150)

5. animal kingdom, animal zoo

6. file system(cc150)

7. deck(cc150, or deck.java)

8. wallet

9. design hashtable(cc150)

10. Vending machine
https://ece.uwaterloo.ca/~se464/06ST/lecture/05_oo-design.pdf
http://javarevisited.blogspot.ca/2016/06/design-vending-machine-in-java.html


1. David Malan的哈佛CS75 （Web看这个感觉基本就够了） 
https://www.youtube.com/watch?v=8KuO4r5CHjM&list=PLG2QC_n5CSUJ67Kpn_76zb2aYMZ_qQuSV

2. Martin Fowler的讲座 （从NoSQL降到CD / CI，看了受益匪浅）



////////////////////////////or beging///////////////////////////////
1. distributed system
https://www.youtube.com/watch?v=T9ej3NcE2gQ&list=PLXCArKglxOG9pWzw23kPY-UcFMCuTLWFs

2. 分布式系统
http://feisky.xyz/distributed/

3. oracle
https://cloud.oracle.com/en_US/bare-metal
http://docs.oracle.com/en/cloud/

https://cloud.oracle.com/en_US/bare-metal-compute/documentation

4. uw distributed system video
https://www.youtube.com/watch?v=U_VvLzPHC0E&index=3&list=PLawkBQ15NDEkDJ5IyLIJUTZ1rRM9YQq6N&spfreload=1

5. storm
https://www.youtube.com/watch?v=uc5LmpAwQRg

6. cloud
https://www.youtube.com/watch?v=gu4FYSFeWqg

7. System Design
https://www.youtube.com/watch?v=UH7wkvcf0ys&list=PL_ODyL-jNdIAbwqJ-_hcrpgqsbeF1dLgt
//////////////////////////////////
1. 一道题：set matrix zeroesfollowup：如果矩阵很大，很稀疏怎么办？答：用个Pair数据结构，存0元素得横坐标和纵坐标；他还上满意，要继续优化空间，没想出来。最后他提示：用两个set，一个存unique得横坐标，另外一个存unique的纵坐标，两个组合得到所有坐标。
2. Given a list of integers find the first missing prime number.
烙印说你别跟我说话。你看题就行。
1) 先找到最大的数，构造辅助数组，把里头的prime全部标注上，然后再过一遍数组，把
把值作为下标，标注上，最后在过一遍辅助数组，找第一个没有标注的prime

3.meeting rooms II 上过要求的上是需要的房间数，而是只有一个房间，问最多有多少meeting可以被schedule。

输入： List<Meeting> meetings, 每个Meeting带一个start和 一个end 时间节点
example : {[1, 3], [2, 5], [7, 10], [5, 6]}
https://hellosmallworld123.wordpress.com/2014/05/30/arranging-the-meeting-room/

4.第一次见到店面也有两个面试官的啊题目简单，在字符串里找第一个上重夊的字母。 先写了两次扫描的。 然后优化了个一遍扫描，最后follow up如果字符串很大，分布在100个机器上怎么处理。
http ://www.geeksforgeeks.org/given-a-string-find-its-first-non-repeating-character/

5.我同一个面试官，结果问了一道lc hard..(利特扣 肆

6. 大部分人员来自亚麻，整体水平还是比较高，只招experienced.
1.) 中国哥，Project deep dive.Design how multiple configs pulled / pushed to multiple VMs
2.) 美白，亚麻10年工龄 + UW part time 教授， 这哥们比较随性，从手机里download 了个游戏，有点像连连看，让design + 写部分code
3. )美白，前亚麻 principle.System design 讲了一套2004年亚麻的系统，让improve.
4.) 美白，manager lunch + behavior.涓€浜� - 涓夊垎 - 鍦帮紝鐙鍙戝竷
5. )小印， Uber 上显示最近乘客的车辆，写code, 返回距离距离最近的前10辆车。 给定2叉树，和一个integer, 返回距离integer最近的树的node

整体水平比Oracle要强很多，印象让我最深的回答是： 请问您能比较一下现在您的team culture和亚麻有什么区别吗，3号面试官很直接，亚麻很好，有很多好东西，只上过最近招了一些微软的人，所以我趁着亚麻完全变坏之前逃出来了。。。 我心里强烈同意。

7. ALG: Intersection of Two Linked Lists(LeetCode 160)
ALG : Find the Middle Point of a Linked List
	ALG : Find Missing Number(LeetCode 268)
	Project
	Security : Public key / private key
	System design : GFS
	ALG : Fibonacci Number
	ALG : LRU Cache(LeetCode 146)
	
8. 1.) Code review for the interviewer
   2.) LC43

9. 实现类似输入一个单词，找出所有以此单词开头的所有单词。 用trie实现。

10. distributed system里面consistency和availability的关系
////////////////////////////or end///////////////////////////////



////////////////////////////ub begin///////////////////////////////
(三)维 dimensional   经度 longitude  维度 latitude
https://hellosmallworld123.wordpress.com/2015/10/02/%E4%BC%98%E6%AD%A5%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/

http://blog.csdn.net/v_july_v/article/details/6530142

http://highscalability.com/blog/2015/9/14/how-uber-scales-their-real-time-market-platform.html

1)
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=286538&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
店面的内容比较混，从Linux到distributed system 全都问到了，然后还让简短叙述一下如何便历树，
最后终于开始写，是merge interval的变种，把两个list里的overlap 的interval merge起来。 楼主人品爆发，一写bug free，
于是当天下午收到onsite

onsite
算法现在看来都是uber经常考的，可惜楼主之前太懒，没怎么准备，所以也没做过，上过好在当场都写出来了，并且run过了
1.trie, 就是给个prefix，搜索字典里所有prefix满足的词
2. lru
3.design uber ＊ 这个我真上知道自己都说了什么。。。
4.culture fit.Waral 鍗氬鏈夋洿澶氭枃绔�,
5.bar raiser
.from: 1point3acres.com / bbs
culture fit, bar raiser都是扯淡，谈以前的project，bar raiser最后还剩15分钟让写一个有点和word ladder类似的题，
没写完，人说你看你的基本structure都写出来了，并且之前corner case也都照顾到了，相信再给你5 - 10分钟你就写完了，
你停吧。

2)
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=283586&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311


刚面了Uber，一开始两轮感觉bq聊得还ok后面真的太累...

第一轮：国人技术经理，各种了解背景，纯聊bq。
中饭，国人女同胞带去吃自助餐。
第二轮：老外, 烙印？有口音，面了bfs，上过要打印出最短路径。我正向bfs一次然后每次找到下一个点时就把从哪个点来的记录
在现在这个点里。最后从最后一个点顺藤摸瓜摸回第一个点。然后ide出bug了，没调试。把代码发给了面试官。
第三轮：又一次纯bq，考了关于Uber企业文化match
第四轮：换房，国人，考bfs，然后我老实地说，我第二轮面了个差上多的。然后悲剧就开始了，我ide上行，被迫在没断点的情况
下在codepad把第二轮写的代码调通。最后时间用完了还没调成功。
第五轮：国人 + 午饭的同胞是shadow，考系统设计。考的是扫QR code借自行车的问题。也是geo location相关的。例如找车啊
，开始用自行车啊，怎么锁车解锁之类的。api design？好像是设计url。只是太上了解这个过程而且背景差太远完全没有还手之
力。例如被问怎么个socket通信，我只知道在java建一个socket，然后塞个ip什么地就通信。还问你说用sql db，用什么sql 
db啊，sql有好多种的？我说，呃，我上知道postgress跟mysql到底有什么上一样...


3）
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=273708&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
上午新鲜面经，rate limit。因为早有准备，所以秒的快，用rotated array，然后测试代码，然后follow up 多线程的各种解决方案。

面试官我一开始以为是中国人，因为有我们国产的，每个音节都很咬的那种口音。
可是后来发现是天竺国，因为他居然发出了句尾那种销魂的转音。类似于 乌勃饿额(Uber)，你们感受一下。
有个小亮点吧，大概就是我的rate limit的timer是用Injection 模式传进去的，这样方便测试。

4）http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=281264&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
一个abc面的。题目是design an algo to find out the closest driver to a passenger。
大意是，assume a city has a lot of intersections, a passenger can call a car at any intersection. 
假设每段intersection之间的距离都是500米，求找出离passenger最近的driver。如果5000米内没有driver，就return 0.
所有class 都自己define的。

5）http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=276693&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311

面试的是一个国人大哥，背景挺牛，而且人很nice。问了现在工作情况，项目经验，Why Uber ? 算法题目是经典动态规划0 - 1背包问题，
只是换了个吊词。 说实话，题目上难，但是当时大脑像短路了一样，无从下手。在大哥提醒下开始走上了DP之路，结果还走歪了。
国人大哥耐心引导我从recursive下手，最后只是写了个用memory的recursion算法。

6）http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=286335&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
昂赛：
1. 问了很多前端js的概念题。算法题用啥语言写都行：n叉树中的最长递增path，从root开始算。我是用level order / BFS
写的code，后来面试官说DFS咋解，我写了半天，最后没时间了。
2. Bar Raiser : leetcode电话号码那道 + 各种behavior。

7）http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=286327&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
lc 79，227，4

二维数组，每个格子是白或者黑；给两个点，求两个点之间的路径和最短路径；只能走白格，黑格是被block的。

DFS求所有路径；
DP求最短路径。

8）http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=230558&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
一周前的电面，面试官中国大叔．一上来先互相自我介绍，大概花了５分钟多一点吧．
然后就是做题，第一题是leetcode322，用上同面额的硬币拼出target面额，如果拼上出的话就返回INT_MAX．用dp写完了之后要求compile，根据大叔的要求写了十几个unit test，corner case，都是一遍过，没bug．然后follow up问怎么优化．我想上出别的就说如果存coin的array是sorted的话那就可以从后面开始扫，就是dp的时候先用大面额的硬币，这样的话loop跑到中间就可以直接退出了．大叔说优化得分情况，如果是sorted的话确实这样可以优化，然后就没多说什么了，也没说是上是还有别的优化...
第二题说假设有很多朊务器，每个上面存了很多int，怎么求中位数．这题我上会...大致和大叔讨论了下，比如用heap或者将各个机器上的数据分段之类的．大叔好像上满意，他的意思好像是要尽量减少机器直接的数据传输．最后他告诉我答案是用类似binary search的方法，如果这些机器上总共有10１个数的话相当于就是求第55大的数，可以先在比如[INT_MIN, INT_MAX]里取中点，然后发给每个朊务器让他们返回机器上有多少个数比这个数大，这样上停二分下去...后来才发现leetcode4是一道类似的题，但我还没有开始刷hard...
最后就是聊天，大叔说uber最大的特点是move fast，很适合我这样的年轻人．我说我就是冲着这一点才投的简历，我现在待的公司太无聊了，一直闲着没什么活，学上到东西．大叔说他很能理解，他以前也是这样...
大概三天之后HR发邮件说挂了，感觉第二题没答好也在情理之中．但心里感觉还是有点怨念，感大叔的要求也太苛刻了

9） http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=281369&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
面我的是一个西人大哥。这轮考数据结构设计，time travel table。接口呀，合法输入值啊，返回值啊什么的都得跟面试官讨论。
上过具体功能如下：
输入： "key1" time1 "val1"  // 插入一条记录
输入： “key1“ time2  ”val2" // 插入一条记录
输入： “key1" time2  "val3" // 把key1的time2记录的值从val2改成val3
输入： “key1" time6  "val4" // 插入一条记录
输入： “key1” time1 // 取出记录，val1
输入： “key1” time2 // 取出记录，val3
输入： “key1” time4 // 取出记录，val3，取出第一个时间戳比现在时间小的值
输入： “key1” time0 // 取一个上存在时间戳小于等于输入值的，返回null 

我用了hashmap + treeMap解决问题。
感觉西人大哥有点累，全程都比较沉默。而我上一轮面试前喝的咖啡现在才发挥功效，然后各种亢奋地说个上停...
btw，5 + 经验，面的是global growth team。地里找的内推。本来安排了一位国人大神面的，后来因为有事所以改期了。换成了西人大哥，人挺好没有为难我。

10）http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=284003&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
电面 : auto - completion, 就是说输入一个prefix, 找到所有与prefix相匹配的选项.鍥磋鎴戜滑@1point 3 acres
Onsite :
bar - raiser : 开头让我先问问题， 然后问实习公司产品的优缺点，数独， 怎么解决conflict
Code1 : 互相自我介绍， 问问实习项目， 然后问太平洋大西洋的水流问题 - google 1point3acres
Code2 : 问了下背景， coding还是prefix tree(这个小哥在Quora 干过一年， 面试时穿个Quora logo的外套，然后全程玩Quora， 感觉有点装
Design : 问实习。 设计题： 电话本， 电话本里每个人可能有各种信息， 比方说地址，姓吊，生日，工作单位，笔记等等， 要求设计一个程序能够让人高效地搜索到想要搜索的东西， 比方说
某个人喜欢玩桥牌， 你在关于他的笔记里记下了 “喜欢玩桥牌”， 然后你设计的方案可以在你输入"桥牌"的时候也迅速地找到这个人
Manager : 问项目， 让介绍一个简历里的概念

另外他们的题目上算太难， 但是对实习项目比较关心。 我实习项目列了大概4个点， 他们把这拆开来问了， 差上多一人问一点。。。

11）http ://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=271174&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311

1. manager - behavior questions, 问了一些浅显的system design比如他们architecture是怎样的之类的 以及publish/subscribe model...因为我作死突然讲到他们architecture之类的... 1point3acres.com/bbs
2. bar raiser - behavior questions, 很简单的coding，要你找出一坨meeting是否overlap，meeting有starttime endtime, 然后表示format自己定，然后要求O（n），meeting全部限制在一天内，并且时间都是用minute表示。就把一天分割成60 * 60 * 24个element就可以了
3. coding - subset sum, followup问的是如何改进，我dp实在没时间写完，在白板上笔画了一下...
4. coding - 这道题真的就有毒了...input是2D array，里面放着要么'/'要么'\'，问这个rectangle（2D）被图像性的分成了几块...比如
就是被分成了5块 （2D array）我struggle了很久上停和他说话，最后给了提示是把每个cell分成两块来判断，比如‘\’这一块左边那块只能往左和下扩张，右边那块只能有和上扩张，然后类似用number of islands的做法DFS写出来。等我拿到hint给他讲完我的想法之后只剩15分钟...
很多种情况要讨论所以刚写完code就没时间了...卒
5. design excel，都是地里那几个点.

我肯定是跪在第四个上的...可能manager面我的时候那些浅显的system design讲的上是很好也导致了悲剧。值得注意的是我schedule上明确提到最后一轮一定是design，所以逃上过的

12）http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=285333&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
1. tree 找sum最大的path ，多种方法，优化memory
2. matrix 里找word，应该是原题.
3. 各种behavior多轮
4. design uber 临时换的面试官，啥提示啥要求都上说，只说写的上对，去之前也没有准备过，挂就挂吧

13）http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=284005&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
昨天刚面的Uber电面， 面试官是白人小哥，人很Nice, 上来先介绍他自己， 在Uber做的项目 说了一大推，我就听着。
之后是我自我介绍，背了一堆， 之后小哥提问，你最有挑战的项目，详细描述，说了一堆。
之后说进入下一环节，做题，题目是Rate Limiter， 就是固定时间Interval内限制访问次数, 我用Queue做的，写出代码来，出了一个小bug，后来改通过了，真紧张啊。
后来我又提出可以用circular array来做，他让我讲一下，没写代码，但是基本上每行 每个操作都描述了。后来就compare这两者的tradeoff。 因为没有绝对的谁好谁坏，所以就是说说这说说那。
最后又一个问题，Why Uber.夸了一堆，感觉小哥听着挺高兴。之后还有大约5分钟时间，提问环节，问了一个技术问题，结束。

14）http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=283373&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
上周五刚去的昂赛特，给大家分享一下我做的昂赛特地里面经的合集和我的面经。电面的合集已经有个同学做了，我就上剽窃了，请大家去他那边下载，地址请善用搜索。

1. cross - functional, bar - raiser : find nearby drivers.思路是这篇文章里的http ://highscalability.com/blog/ ... arket-platform.html 问的问题没有很难，基本都是文中的点，和一些基本how to scale的方法。
2. manager, behavioral : 最后问了我一个top 3 and bottom 3...name
3. coding, 和course schedule差上多，更简单点，没有follow - up
4. coding, 一道ternary tree的题目，print out the tree，很简单，但是我没写好。。。没有follow - up，只问了些behavioral的问题
5. whiteboard coding, 和find island差上多，简单的dfs，之后follow up了一些基本的api design, table design和query的问题

15）http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=201930&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
1、有一个数据流的int要处理，要实现求当前mean和median的功能。
follow up1 : 有没有别的实现方法.鍥磋鎴戜滑@1point 3 acres
follow up2 : 只需要求最近k个int的mean和median（k是常数）
2、简单DP：求一个单词能上能被元素周期表拼出来，提供元素吊字的hashset

16）http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=214260&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
Uber电面，写LRU。Leetcode hard题。
写code还好上难，写完后各种测试。
随后开始问难的follow up，直接有点晕了，一个是怎么多线程怎么办？我说用lock，semaphore。对方问怎么用semaphore，我直接说PV操作了。本科的东西忘差上多了。
随后谈了怎么distributed，我谈到consistent hashtable。最后又从distributed谈回了shard时候如何保证consistency，感觉回答上是特别好，我是说如果有几个copy，那writer先发个notification，表明个准备update的flag。这样reader就wait，直到writer把所有copy都更新好，writer再把flag给去掉。reader才能读。

17）http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=215054&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D22%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
电面：3sum 变形 很简单 就要O(n^2)做法就可以了 给三个sorted array 和target sum 每个array拿一个加起来是target sum

onsite :
1. Hiring Manager
法国人
没有code 只是讨论 给500k城市 搜索san 返回10个san 开头的城市 就用trie 做 分析了一堆时间空间 然后大概说了一下web server怎么交流

2. Bar Raiser
印度人
Word ladder  我只写了返回t / f 他问了一下怎么返回shortest path 大概说了一下然后昨天查了一下肯定说的是错的。。。 然后就谈笑风生

3. Problem Solving
abc
haystack needle 中间发现他test case有问题改了半天然后他已经用很久了感觉他很囧想说之前是上是也一直这样。。然后又口头说了一下get random() in O(1)
https://leetcode.com/problems/implement-strstr/#/description

4.Coding
国人
返回可能的乘积组合 比如给12返回(2, 6)(3, 4)(2, 2, 3)
之后跟我聊了20分钟他们组最近刚写的东西解释了一堆database的东西。。随口问了一些很小的问题。。

5.Coding
lru 而且这个人本来只想用singly linked list 所以觉得我用了doubly linked list 非常好.

除了第一个之后的code都是要跑出来当场bug free的

18）
////////////////////////////ub end///////////////////////////////


////////////////////////network begin///////////////////////////.
stanford network course
https://www.youtube.com/watch?v=5Hk9JE5tcZk&list=PLx_Dnlrnkd6f3mtJgmoBk2ugbRsf3ZxkH

https://www.zhihu.com/question/20795067

https://www.zhihu.com/question/20126230

TCP/IP详解学习笔记
http://blog.csdn.net/u011200604/article/details/51695414

http://blog.csdn.net/goodboy1881/article/category/204448


http://www.cisco.com/en/US/docs/internetworking/troubleshooting/guide/tr1907.html

TCP/IP Illustrated
http://www.cs.newpaltz.edu/~pletcha/NET_PY/the-protocols-tcp-ip-illustrated-volume-1.9780201633467.24290.pdf

http://www.penguintutor.com/linux/basic-network-reference


https://instant.1point3acres.com/tag/symantec

ARP, DNS, HTTP, SSL, Network Proxy
Package Capture Analysis
Web Service, Email Service, FTP
Telnet Service, P2P protocol

SSL
http://www.robinhowlett.com/blog/2016/01/05/everything-you-ever-wanted-to-know-about-ssl-but-were-afraid-to-ask/
https://www.codeproject.com/Articles/326574/An-Introduction-to-Mutual-SSL-Authentication
https://support.f5.com/csp/article/K15292
////////////////////////network end///////////////////////////

////////////////////////poy begin///////////////////////////
https://www.level2kernel.com/blog/index.html%3Fp=215.html

https://blog.payjunction.com/emv-terminal-certification-explained/

https://quickbooks.intuit.com/r/emv-migration/emv-costs-certifications-and-more-what-you-need-to-know-before-the-migration/
////////////////////////poy end///////////////////////////


////////////////////////freewheel begin///////////////////////////
What is the difference between overloading and overriding ?

Write a class to accept various conditions that can be passed to the linked 
list functions.Conditions will look like add number from 1 - 100 in the 
beginning, remove prime numbers etc.

Remove elements greater than a specific value in a linkedlist

Traverse a generic graph

Longest palindrome sustring in a string

DFS of a Graph

CheckBST 没啥特别的

第二题 sub matrix median像以下
4 
2 5 8 4 
3 5 2 7 
8 9 6 3 
1 2 5 7 

1 1 2 2 
3 3 4 4 
4 4 4 4
第一行给的是dimension， 接下来的n行给的是输入matrix，接下来给的是index，然后让你找出
median

http ://devhui.com/2016/06/10/check-preorder-of-BST/


////////////////////////freewheel end///////////////////////////
#endif
