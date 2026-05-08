#ifndef SAFE_ARITHMETIC_H_
#define SAFE_ARITHMETIC_H_

#include <cstddef>
#include <list>
#include <optional>
#include <string>
#include <unordered_map>

class LRUCache
{
public:
    explicit LRUCache(size_t capacity);

    size_t size() const;
    size_t capacity() const;

    void clear() noexcept;

    std::optional<int> get(const std::string& key);
    bool put(const std::string& key, int value);
    bool erase(const std::string& key);

    bool pin(const std::string& key);
    bool unpin(const std::string& key);

    void merge(LRUCache& other);

private:
    size_t capacity_;

    struct Node
    {
        std::string key;
        int value;
    };

    struct MapValue
    {
        std::list<Node>::iterator iter;
        bool pinned;
    };

    std::unordered_map<std::string, MapValue> map_;
    std::list<Node> unpinned_;
    std::list<Node> pinned_;

    void deleteOldest();
};

#endif  // SAFE_ARITHMETIC_H_

