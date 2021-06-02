#include <unordered_map>
#include <memory>
using namespace std;

struct Node {
    Node(int key, int value) : key(key), value(value) {}

    shared_ptr<Node> pre = nullptr;
    shared_ptr<Node> next = nullptr;
    int key;
    int value;
};


class LRUCache {
public:
    LRUCache(int capacity) 
        : capacity(capacity)
        , head(make_shared<Node>(-1, -1))
        , tail(make_shared<Node>(-1, -1))
    {
        head->next = tail;
        tail->pre = head;
    }
    
    int get(int key) {
        // if found in cache, move history to most recently, return value
        auto it = cache.find(key);
        if (it != cache.end()) {
            move_to_tail(it->second);
            return it->second->value;
        }
        // if not found in cache, return -1
        else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        // if found in cache, update value and move history to most recently
        auto it = cache.find(key);
        if (it != cache.end()) {
            it->second->value = value;
            move_to_tail(it->second);
        }
        // if not found in cache, set value to move history to most recently
        else {
            // if cache is full, remove least recently used data from cache and history
            auto res = cache.emplace(key, make_shared<Node>(key, value));
            move_to_tail(res.first->second);

            if (cache.size() > capacity) {
                cache.erase(head->next->key);
                auto to_del = head->next;
                head->next = to_del->next;
                head->next->pre = head;
            }
        }
    }

private:
    void move_to_tail(shared_ptr<Node>& node) {
        if (node->next == tail) {
            return;
        }

        // if the node has pre & next, connect them
        if (node->pre && node->next) {
            node->pre->next = node->next;
            node->next->pre = node->pre;
        }
        
        // put the node to tail
        node->pre = tail->pre;
        node->next = tail;
        tail->pre->next = node;
        tail->pre = node;
    }

private:
    int capacity;

    // map[key] = Node
    unordered_map<int, shared_ptr<Node>> cache;

    // double link list of Node for record access history 
    //   (least recently used to most recently used)
    shared_ptr<Node> head;
    shared_ptr<Node> tail;
};

// V test: get non existed node

// V test: put a node when cache is empty
// V test: add new node to tail

// V test: put a node when cache is not empty (found/not_found)
// V test: move the only one node to tail
// V test: move one of multiple nodes to tail

// V test: get a existed node
// V test: phase out a node