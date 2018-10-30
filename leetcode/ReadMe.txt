========================================================================
    CONSOLE APPLICATION : leetcode Project Overview
========================================================================

AppWizard has created this leetcode application for you.

This file contains a summary of what you will find in each of the files that
make up your leetcode application.


leetcode.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

leetcode.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

leetcode.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named leetcode.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////

https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=443563&extra=page%3D2%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311%26orderby%3Ddateline

1. Cross-functional: 
- 如果你很有钱，让你成为airbnb的host你会做成什么样？
- 说一件你克服困难才完成的project
- 你admire的同事或者同学是谁？
- 一件让你最有成就感的事？


2. Experience
- 基本就是解释清楚一个你以前做过的project，最好选那种比较有技术难度，然后你用了有趣的技术或者算法来解决。
. 一亩-三分-地，独家发布

3. Coding. 留学申请论坛-一亩三分地
- File System，刚开始不需要写callback，让我完成create，update和get，并且写unit tests。callback和面经里的不一样，需要传入两个参数(currentPath, value)，然后client会通过extends你提供的callback 接口来customize callback function。 
在java其实就是写一个class implement Runnable，我当时不知道，现查的。。 可以参考https://stackoverflow.com/questi ... le-with-a-parameter
.本文原创自1point3acres论坛

4. Lunch 
- 其实是一个跟面试官们social的好时机，别闷着吃，我跟小哥吃饭的时候，下午即将面我的engineer也join进来，聊了一大堆，下午他面我的时候其实互相已经很了解了，沟通也很轻松。. 牛人云集,一亩三分地
. from: 1point3acres 

5. Cross-functional: 
- 你如果让你的manager知道和赞许你一个默默无闻工作的同事？
- 你最崇拜的人，不限同事
- 你如何理解airbnb的mission？


6. Design
- RSS reader，之前的qps和storage 计算很重要，决定你设计一个什么样的系统。


7. Coding
- flight cost， 我刚说了可以bfs，但是面试官问我有没有更好的，感觉他想要Dijkstra，就写了Dijkstra， 所以这个算法一定要滚瓜烂熟。需要输出路径和min cost.留学论坛-一亩-三分地


一点点题外话：airbnb的面试准说难也难，说容易也容易。 难在有些题其实算法难度还是有点高的，而且做题的时候刨去跟面试官说思路和写test case的时间，基本也就20-30min的时间写code，所有几乎需要一遍过bug free，根本没有改bug的时间。容易在题目都在题库里，花点时间，每道题弄明白写个至少两遍肯定没问题。然后airbnb很看重Cross-functional，所以感觉还是需要花点时间准备几个跟题目相关的story，老美都喜欢听story，你懂得。

补充RSS：刚开始有1000个用户，1000个provider，设计这个Rss reader，让每个用户每次刷新开始看到最近刚更新的的news，后来用户增长到10K, 100K, 系统怎么scale。其实就是设计Twitter/facebook news feed。

RSS的重点在于你需要计算QPS和需要多大的storage，这样你就知道你需要用SQL还是NOSQL，需不需要sharding，需不需要memcache。面试官当时问我用户增长到10M的时候，我设计的那个table会最先出问题，问得很仔细。

-----------------------------------------------------------------------------------------------------
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=437174&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3090%5D%5Bvalue%5D%3D1%26searchoption%5B3090%5D%5Btype%5D%3Dradio%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311%26orderby%3Ddateline

Wizard面经题
BFS写了输出最小cost之后她让输出路径

Coding 1: missing
Coding 2: File system，地里有原题
Culture Fit 两轮
午饭. 1point3acres
Experience: 问的非常细
design: flight ticket booking from scratch.

------------------------------------------------------------------------------------------------------
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=428194&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3090%5D%5Bvalue%5D%3D1%26searchoption%5B3090%5D%5Btype%5D%3Dradio%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311%26orderby%3Ddateline

1. coding， Palindrome Pairs
2. coding， 8 puzzles，但是和地里面镜不太一样，要oo design，就是design game board，实现几个function，比如move，最后说能不能实现个function，check当前的board state有没有解，用bfs做的，但是前面耽误时间有点多，有个bug，最后没做完，挂点一。
3. 聊以前的project，没啥好说的。
中午吃完，国人兄弟，瞎聊了些有的没的。
下午一来，两轮X functional
最后一轮 系统设计 让design他们家的搜索页，就是user给一些filter，显示filter后的listings，然后每个listing还可以再点进去看listing的细节。没太搞懂到底想问什么，扯了些db schema design，sharding， denormalization。。。后来提示问用过elastic search没，确实没用过，可能是想问index table? 挂点二。

----------------------------------------------------------------------------------------------------------
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=427067&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3090%5D%5Bvalue%5D%3D1%26searchoption%5B3090%5D%5Btype%5D%3Dradio%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311%26orderby%3Ddateline

昂塞也比较标准，我要求直接在西雅图面就不去总部了，一共无论，两轮coding，都是面经题，一轮系统设计：翻译系统，我一会儿仔细讲下，两轮cross functional就是各种behavior问题
1. coding按照面经准备就好，我不确定要求是不是要bug-free但是我都是一边过的，大概20分钟写完所有然后纯聊天20分钟。有个小插曲，第二轮coding我给了个非标准答案用了treemap偷懒，结果面完所有之后被要求加面一轮电面因为给的答案用的datastructure太高级，面试官不确定考察到没到基础能力，也不想挂我，结果加面一轮，也是面经题，加面做完跟我说我是他见过做的最快的（有答案在旁边能不快么OTL)。所以整体感觉因为有面经所以很好过，尽量讲清楚思路就好，就算遇到给的答案不同，讲清楚了对方也很讲道理不会直接挂掉。
2. cross-functional: 基本就是聊天，尽量准备一些非专业的故事，中心思想就是喜欢旅游，喜欢不同文化，觉得气床是可以分享不同文化的平台这类东西。。
3.系统设计翻译系统，我看了所有气床的面经包括他公司blog上关于翻译系统的设计，感觉都没讲很清楚，所以虽然准备了但是感觉还是有点迷糊，当然我也没在气床工作过不具体了解他们的翻译系统，只是刚好我曾经做过app的localization（就是翻译各种语言给app store这样不同国家的人下载的版本就是那个语言的版本），所以面试的时候我是结合自己工作经验做的介绍，以及一些如何做网站翻译的扩展设计（气床的产品主要还是网站，当然现在也有手机端app，手机端的方法跟我做过的应该是一样的），以下只是我个人的理解，大部分也得到面试官的认可所以应该比较接近他们的系统。面试之后还跟他聊了一些他们翻译系统平时的用法和我给的方法的差别（下面会说）

翻译系统大体分为三个部分: 1. UI (front end)， 2. translation service (middle layer), 3. translator portal，这三部分在一起最后会做出完整的version (web/app)发给client，要么是给app store的app package，要么是转换成网页发给用户（或者CDN for scalability reason). 1point3acres
1) UI部分: front-end developer和designer通常不用去理会如何翻译，他们主要做的是修改ui，这个过程中可能会增加，修改，删除一些文字（比如一个按键的label，比如增加新的网页和目录的标题etc)，他们的任务是确定网页和app这些UI用主语言（比如英语）是没问题的，通常这些修改之后，会提交给translation service...提交的东西你可以理解成是一整套resource文件，里面包含所有的ui相关的文字资料，标注了这是哪个Version，有哪些ui (key-value, where key represent ui variable name like "agreeButtonText", value represents actual text in English "Agree"），通常每个修改还会带一条介绍帮助翻译更好的理解语境，比如叫description里面会写这句话是当用户同意某个条款的时候点击同意的，这样翻译的人就会翻译成（同意，认同之类的），有些语言会有多义词所以这条解释很重要
2) translation service: 当文字修改发给这个service，他负责三个部分，一个从resource文件中找出新版本中被改变的文字信息，比如有几行条款文字改了，或者一些button的文字改了，第二部分是把这些信息汇总（tokenlize)然后发给 Translator portal，可以理解成一个接受各种key-value pair的工具或者翻译平台，实际翻译发生在那里， 第三部分是当信息被翻译之后，汇总并声称新的resource文件给每个需要的语言，比如一开始只有en-us.resource，翻译之后这个Service会生成zh-cn.resource (中文），es-es.resource （西班牙语）。汇总后会连同这些语言一起发布这个版本的网页或者app (之后就是发布端了这里就不多讲）
3) translator portal: 每个公司做多语言产品都必然会雇佣一些翻译来翻译它的产品，所以会有一个翻译平台，翻译的人不需要真实了解或者使用这个产品，他们需要的只是拿到一些词汇和语境介绍，然后给出相关语言的翻译，当translation service给了一系列需要翻译的词汇之后，这个平台会收录整理排序这些词汇（有些词汇可能是一样的，有些词汇可能更重要更急需比如一些legal文件更新），然后翻译的人从这个平台拿词，根据介绍翻译好然后发回去，通常可能会有一些PM或者designer会尝试把翻译好的版本自己测试一遍确定读起来通顺没问题，这要看公司的要求和产品重要性了。. 牛人云集,一亩三分地
. visit 1point3acres for more.
上面这三部分基本构成了一套翻译系统，其实没太多系统设计的概念，关于手机端，最后会生成一个主的package 已经所有语言的Resource file发给store然后store负责转换语言生成新的package给不同语言的用户。网络段会有区别，可以理解成这个网页会根据不同的域名比如airbnb.jp跟Server索取日语版的网页，这时候server会有自己的一套生成系统自动提取翻译好的日语词汇安在对应的ui上 (eg.一个button叫agreButton, text = "$agreeButtonText"，他会自己找jp resource里agreeButtonText对应的值，日语的“同意”），生成网页后发给Client；Scale的考虑可以有cache这些网页到CDN, browser cache or even server cache，来缓解read-load...这里就用基本系统设计概念扩展就好了。.本文原创自1point3acres论坛

大体就是这些，入职之后通常会去旧金山总部为期3周的bootcamp选组，还没确定是否接，但是整体体验不错，是个氛围很好的公司
----------------------------------------------------------------------------------------------------
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=425749&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3090%5D%5Bvalue%5D%3D1%26searchoption%5B3090%5D%5Btype%5D%3Dradio%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311%26orderby%3Ddateline

一个我用的是bit masking来做的dynamic programming: Count ways to assign unique cap to every person.

第二个我有点忘了，和concatenate words什么的有关系。就是给你一个list of words，然后让你去找所有这个list里面的concatenated words. 比如说input是["cats","catsdogcats","dog"]，然后output是["catsdogcats"］这样。
https://leetcode.com/problems/concatenated-words/description/
http://www.cnblogs.com/grandyang/p/6254527.html

design就是有点天马行空的给定一个主题聊。好像那个小哥特别特别看database joining/indexing performance，反复针对几个专有名词让我define，比如说什么叫indexing, database reverse indexing, 怎么样的sql是有好的performance的sql language。问的都是我不太会的，最后感觉都快哭了他也没有要停下来让我说其他的意思。。。最后还是我把所有想说的说了，然后接了一句that's all I know.... 这个小哥才开始往其他方向问问题。整个过程非常不互动，就是他一个问题接一个问题，而且我回答了以后他也没有给我反馈，也没告诉我这么说对还是不对。。好几次说完我就停在那里等他下一个要问的问题。 来源一亩.三分地论坛. 

experience和cross-functional就没什么好讲的。中午吃完饭（没有吃饱！！！）就很放飞自我，笑点很低，面试的时候偶尔也会说几个冷笑话这样，感觉自己还挺尬的。

---------------------------------------------------------------------------------------------------------
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=410883&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3090%5D%5Bvalue%5D%3D1%26searchoption%5B3090%5D%5Btype%5D%3Dradio%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311%26orderby%3Ddateline

LC饿饿溜变型，没啥难点，秒过，按照Discussion里Vote最高的解法做的。
面试官问了我 LRU Cache，这道题我其实没准备好，只能用点套路先套路一下面试官，不知道是不是要用double linked list。
https://leetcode.com/problems/lru-cache/description/
还有flight tickets问题，面经老题，网上相关资料很多，多看看老冯自己搞的视频这种老题应该难度不太大。
BQ问的几个问题：

1. 你是如何帮助别人的啊

2. 遇到tough问题怎么解决

3. 和Manager冲突怎么办
这些都很简单，套路一下呗。

---------------------------------------------------------------------------------------------------------
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=406366&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3090%5D%5Bvalue%5D%3D1%26searchoption%5B3090%5D%5Btype%5D%3Dradio%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311%26orderby%3Ddateline

1. alien dictionary 过。正常
. 一亩-三分-地，独家发布
2. round sum 讲大概思路，写，过。正常
. 一亩-三分-地，独家发布
3. newsfeed design. 这个人明显对index 很感兴趣。顺着他意思说就好，有多少说多少。他很感兴趣。还引进他所遇到的问题，甚至都没有说push 或者pull model。

4. translation system. 中国人。一进来一股油烟味。房间小，熏得我不行。安慰自己。他说Google待过两年，Twitter呆了一点时间，然后在airbnb呆了快三年。上来问我experience, 说完Phd 和工作经验 （底层相关的）鄙视我的 experience， 立马觉得不对头了。当时应该立马中断和他的面试。明显bias. 有什么了不起的吗？后面就更搞了。非常arrogant. 尽力回忆吧。

说自己想问这四个大块（frontend engineer, translation service, user experience and deployment). 然后说好一个个来。感觉，哎，不错。还满organized的。然后开讲。然后问题来了。几乎不让你讲，要按他的思路。不是他要的关键词，一律不听。摇头。关键问题是，他用自己蹩脚的英文，没法问清楚自己想问的问题。搞个半天人家才知道他要干嘛。这个其实之前有面经也反映这个情况我当时看面经没在意。应该是不是那个candidate的问题，没听清人家说什么。果不期然，人家估计说的就是这个家伙。然后意外的又来了，我竟然音乐问到大蒜洋葱的味道。OMG! no excuse. seriously，这么小的房间，身上味道我忍了， 你打个这么味道大的嗝， 中午吃的是什么东西啊！我继续忍。他本来想问说http request里的 field有什么信息。花了很久时间， 问的问题，我不记得了，他问的问题是其他的。I'am sure. 然后他好不容易，问，user web brower type 这个link, 发生了什么？我就问，are we still talking about the translation system or you want me to talk more about anything happened during the request process? 继续摇头。不听。好吧。然后还有个地方，说API怎么设计，前一分钟还在讲前端的哦。后来莫名其妙地要说 translation service那里去。我说我们frontend 端讲完了吗？因为之前还在给他讲 JS template system 怎么用library call to decouple from the translation service. 我继续澄清，你是说这个API? 设计还是这个library API底层具体的Restful API？还有几处 都这样的情况。overall, 不让我讲大概框架，说好一个个来， 然后又莫名其妙的乱跳，一些workflow 莫名其妙地跳出来，我几次想跟他澄清，他很固执，自大。I seriously doubt his capability to explain his questions well. 看起来很organize, 但是脑子里其实就是一个浆糊。而且非常bossy. 关键是，你最终答出他想要的，他根本没有任何positive yes, 或者反应。非常奇葩。这个面经反应真的不是一例了。不知道什么样的人才和他对得上。很怀疑这种style和personality的人，很可能在google带不下去才去twitter, airbnb. 
. visit 1point3acres for more.
强烈建议，以后要是碰到这个人或者这种人，立即要求换人。如果你care 这个公司。这个（种）人绝对80%会fail 你。好事者可以翻以前的类似面经。

5. experience interview. 没什么说的。国人。google 待过的。不怎么care 你所说的。关注的是底层的，我不是与 airbnb 相关的application/cluster service 方面的。自从遇到前面那个中国面试官，我也不怎么care了。估计都这副德行。
. Waral 博客有更多文章,
6&7 。cross fucntion interview. 没什么奇葩事情。

说完面试，说中饭。问黑人小妹，有 dessert不？人家说，只有friday 才有。WHAT!!!! 这是过年才有好吃的吗？
然后回去，问recuiter, 车费怎么报销？ 她说我们不报销车费。 bay area的都不报销。妈呀！你早说！我乘的UberX过来的，来回也近百刀了。虽然我不care, 但是这是迄今为止，第一家公司，连车费都不报销的！人家来面面，还要自己掏腰包！这公司到底多缺钱，这点小钱也扣嘛？而且， 在里面的员工好像没有好多traffic补贴的。btw. . 围观我们@1point 3 acres
另外，面试过程中，我说好饿哦。然后带去kitchen, 水果饼干一个都没有，只有在下面厨子里的什么小玩意分散状的snack. OMG。要是饿了，空气床的员工们都是怎么生活的？
. 1point3acres
anyway, recuiter 告知挂了 （可想而知）。暗自庆幸，省得我拒你。而且那个recuiter, 打个电话只告诉你not move forward, 本来想多聊聊。人家就说you are strong candidate, （u估计都这么告知）， looking for stronger architectural skill。扯淡。你那些所谓的员工都不知道自己在干嘛吧。whatever. 

中国人很多，去面的中国人更多，因为题库很稳定的原因吧。没事去面面行。但是如果真的找工作，还是看看面经，考虑考虑吧。

----------------------------------------------------------------------------------------------------
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=358532&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3090%5D%5Bvalue%5D%3D1%26searchoption%5B3090%5D%5Btype%5D%3Dradio%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311%26orderby%3Ddateline

1. 流水问题，问的非常细，各种变化，以及打印结果,两边是墙， 不是墙，以及打印
2. 最便宜的机票 
3. experience
4. 两轮 x-function
5. 设计： 翻译系统
翻译系统，这个地里提到几次，我讲一下我的理解吧（个人理解，可能全错），主要考的是怎么管理这个流程， 包括UI developer， translator，怎么提速
原题的意思是设计翻译起床家的page，只翻译dev加的content（label，disclaimer。。）， 不翻译user content。我的理解是translator最好可以在page里翻译这样可以直接看到效果
1. 页面上应该有要I18N的词或句子
2. translator怎么能方便的去翻译
3. 什么样的管理流程

第一道题：给定4*4的矩阵，15个方格内有数字，1-15，另有一个为空，问是否存在一种方法可以从给定的初始状态移动到目标状态。空格只能和上下左右位置交换
直接用广搜做出来，跑过了case，然后给面试官讲了A*算法，没有实现
第二道题：IP地址压缩，给定一个IP地址范围，压缩成尽可能少CIDR表示，这道题应该比较高频了，提前练一下比较好，第一次写比较难写对。
follow up：如果给定的地址范围中有某些地址不能用，应该如何实现。我说基于前面的解法，切割成连续的部分分别调用即可

----------------------------------------------------------------------------------------------------
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=327027&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3090%5D%5Bvalue%5D%3D1%26searchoption%5B3090%5D%5Btype%5D%3Dradio%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311%26orderby%3Ddateline

第一轮Coding: 一个游戏叫做Shut the box, 大家可以wiki下游戏规则。游戏做出以后，模拟运行1000遍看下成功率，然后想办法提高成功率。我的优化是先拿最大的数字，试了下概率提高了很多。

第二轮Coding: 面经上游的File System, 推荐大家用Trie, 我用了HashMap，Callback那部分写的有点复杂，勉强写出来。

第三轮Design: 面经上的翻译系统。主要问的是整体的System Design, 我的解法是先估算出所有翻译的容量，估算出来才几百兆，所以都可以存到Cache里面。然后Frontend server每个instance用memcache, Backend Server用shared Redis，Frontend 如果cache里找不到再call backend。面试官问的最tricky的是如果翻译更新了，如何迅速更新cache，我说用pubsub先broadcast给Backend，Backend更新好了Redis再broadcast给Frontend。面试官感觉对我的design非常满意，半个小时不到就结束了，然后开始愉快的吹水。

第四轮Design: 巨坑的一道题目，是面试官最近刚解决的问题。题目背景：有很多data scientists，每天要运行很多的SQL Query来Calculate metrics, 很多metrics都是重复的，或者和别人的很接近，如何整合所有的计算。我毫无头绪，乱扯先规范所有的SQL QUERY，然后把SQL Query转换成Map Reduce Jobs, 每天全体运行一次，这样Input tables可以重用之类的。感觉完全没有答道面试管想要的方向。

第五轮Cross functional: 一个一脸Bitch的亚洲女engineer, 问了一大堆恶心的behavior questions, 比如如何给同事提供不好的feedback，最近作过很bold的事情。有哪件事你最近改变了看法，我说Trump当总统；最开始以为天塌了，想要离开美国了，现在发现这是一个wake up call, 周围的人都开始关注政治了，所以长期是有利的。然后又扯到了新的退税法案，我说新的退税法案只对富人有利，穷人只是眼前小利，到时候spending cut穷人的小利全吐出来，然后面试官竟然问我有没有采取什么行动，比如捐款给穷人，问的我一脸懵逼。。。最后还和我在新的itemized deduction问题争论了半天，面试竟然能变成政治讨论会，我也是彻底醉了。。。 

第六轮Cross functional:一个很和蔼的亚洲男Product Manager，问了人生的终极理想，今年的目标，今年的目标和终极理想是否挂钩之类的问题。

第七轮experience: 水的一笔，我不停地讲，面试官不停的点头。

---------------------------------------------------------------------------------------------------------
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=325445&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3090%5D%5Bvalue%5D%3D1%26searchoption%5B3090%5D%5Btype%5D%3Dradio%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311%26orderby%3Ddateline

1. flight ticket. 注意，要打印出flight路径。. From 1point 3acres bbs
2. 新题。投两个骰子，从1-9里面选出几个数字，加和为这两个骰子的和。
比如第一次，两个骰子为3，5，那么我们可以选出几个数字，加和为8. 假设我们选1和7.. 留学申请论坛-一亩三分地
第二次，两个骰子为4，6，那么第一次1和7选了，这次不能再选了。我们可以选4和6.
第三次，做同样的事情
。。。。
怎样找到一个最优解，使得我们胜率最大？胜利的定义是所有1-9的数都取了。
3. Google reader design. 问了如何提高database读取的效率，详细问了denormalization, 以及瓶颈在哪，怎么解决。
4. lunch.1point3acres网
5. experience. 选以前的一个项目讲就好。
6. cross function
7. cross function
cross function的问题基本都是面经里面的，强烈建议都做一遍。什么你为组里sacrifice过啥啊，why bnb啊，你自己的性格是啥啊，host别人的经历啊，谁对你有过深刻影响啊。
说几个新的：
- 谈谈你认为bnb的core value是啥？你自己的性格和这个core value如何吻合？（变了个方式问）. 围观我们@1point 3 acres
- 如果让你去做experience，即为别人provide一个experience, 你会选哪里？
- 谁曾经让你比较有归属感？

----------------------------------------------------------------------------------------------------------
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=315207&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3089%5D%5Bvalue%5D%5B3%5D%3D3%26searchoption%5B3089%5D%5Btype%5D%3Dcheckbox%26searchoption%5B3090%5D%5Bvalue%5D%3D1%26searchoption%5B3090%5D%5Btype%5D%3Dradio%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311%26orderby%3Ddateline

ONSITE面试全华班。。。
sys design: RSS News feed, design database schema 面试华人大哥，很NICE，这轮没啥问题.
coding 1: Alien dict,  国人女生，非常NICE，面完很愉快聊了会天
coding 2: Sliding game, 国人大哥， 这轮黑了， (8 Puzzle, 也是地里以前原题)这题难度不小，所以不敢怠慢赶快敲代码编译通过，以为这下可以长舒一口气了，谁知道梦魇才开始。大哥说我准备的test case不够多，你来现场再搜几个不能solve的， google了几个运行了也没问题。大哥继续问怎样从OOP角度优化代码，最后二十分钟就纠结在这了，最后反馈是这边挂了
