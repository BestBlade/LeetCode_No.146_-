/* ------------------------------------------------------------------|
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制 。
实现 LRUCache 类：

LRUCache(int capacity) 以正整数作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字-值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。
 

进阶：你是否可以在 O(1) 时间复杂度内完成这两种操作？

 

示例：

输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4
 

提示：

1 <= capacity <= 3000
0 <= key <= 3000
0 <= value <= 104
最多调用 3 * 104 次 get 和 put

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/lru-cache
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*
*
*	执行用时：120 ms, 在所有 C++ 提交中击败了93.53%的用户
*	内存消耗：40.9 MB, 在所有 C++ 提交中击败了30.32%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class LRUCache {
public:
    LRUCache(int capacity): cap(capacity) {
    }

    int get(int key) {
        //如果map中没有key的地址存在的话
        //说明当前结构体中没有与key相对应的value
        //返回-1
        if (map.find(key) == map.end()) {
            return -1;
        }
        //取出map中与key相对应的list地址中存放的pair<key,value>
        //pair<int,int> key_value = *map[key];
        auto key_value = *map[key];
        //从list中删除当前内容map[key]
        cache.erase(map[key]);
        //在list最前端存入，因为访问了一次
        cache.push_front(key_value);
        //将map[key]重定位为list的开始位置
        map[key] = cache.begin();
        //返回value
        return key_value.second;
    }

    void put(int key, int value) {
        //如果当前key不存在map中
        if (map.find(key) == map.end()) {
            //先判断list是否满了
            if (cache.size() == cap) {
                //如果满了
                //去除map中list尾端对应的key
                map.erase(cache.back().first);
                //将list尾端弹出
                cache.pop_back();
            }
        }
        //当前key存在map中的话
        else {
            //把list中key对应的pair<key,value>删去
            cache.erase(map[key]);
        }
        //在list头部添加当前的pair<key,value>
        cache.push_front({ key,value });
        //将key添加到map中，地址为list的begin
        map[key] = cache.begin();
    }
private:
    int cap;
    //建立一个列表存储key和value
    list<pair<int, int>> cache;
    //建立一个hash表存储key和其对应的list地址
    unordered_map<int, list<pair<int, int>>::iterator> map;
};
