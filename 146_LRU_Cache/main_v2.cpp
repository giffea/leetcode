#include <list>
#include <unordered_map>
using namespace std;

struct Data {
    int value;
    list<int>::iterator it;

    Data(int value, list<int>::iterator it)
        : value(value)
        , it(it)
    { }
};

class LRUCache {
public:
    LRUCache(int capacity)
        : capacity(capacity)
    {
        cache.reserve(capacity);
    }

    int get(int key) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            touch(it);
            return it->second.value;
        }

        return -1;
    }

    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            it->second.value = value;
            touch(it);
        }
        else {
            if (cache.size() == capacity) {
                cache.erase(history.back());
                history.pop_back();
            }

            history.emplace_front(key);
            cache.emplace(key, Data{value, history.begin()});
        }
    }

    void touch(unordered_map<int, Data>::iterator it) {
        int key = it->first;
        history.erase(it->second.it);
        history.emplace_front(key);
        it->second.it = history.begin();
    }

private:
    int capacity;
    unordered_map<int, Data> cache;
    list<int> history;  // store keys
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */