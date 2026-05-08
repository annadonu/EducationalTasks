#include "lru_cache.h"

void LRUCache::deleteOldest()
{
    if(!unpinned_.empty())
    {
        map_.erase(unpinned_.back().key);
        unpinned_.pop_back();
    }
}

LRUCache::LRUCache(size_t capacity): capacity_(capacity) {}

size_t LRUCache::size() const { return map_.size(); }

size_t LRUCache::capacity() const { return capacity_; }

void LRUCache::clear() noexcept
{
    map_.clear();
    unpinned_.clear();
    pinned_.clear();
}

std::optional<int> LRUCache::get(const std::string& key)
{
    auto currentEl = map_.find(key);

    if(currentEl == map_.end())
    {
        return std::nullopt;
    }
    else
    {
        if(!currentEl->second.pinned)
        {
            Node temp = *currentEl->second.iter;
            unpinned_.erase(currentEl->second.iter);
            unpinned_.push_front(temp);
            currentEl->second.iter = unpinned_.begin();
        }
        return currentEl->second.iter->value;
    }
}

bool LRUCache::put(const std::string& key, int value)
{
    if(capacity_ == 0)
    {
        return false;
    }
    else
    {
        auto currentEl = map_.find(key);

        if(currentEl != map_.end())
        {
            if(!currentEl->second.pinned)
            {
                unpinned_.erase(currentEl->second.iter);
                unpinned_.push_front({key, value});
                currentEl->second.iter = unpinned_.begin();
            }
            else
            {
                currentEl->second.iter->value = value;
            }
            return false;
        }
        else
        {
            if(size() >= capacity_)
                deleteOldest();

            if(size() >= capacity_)
            {
                return false;
            }
            else
            {
                unpinned_.push_front({key, value});
                map_[key] = {unpinned_.begin(), false};
                return true;
            }
        }
    }
}

bool LRUCache::erase(const std::string& key)
{
    auto currentEl = map_.find(key);

    if(currentEl == map_.end())
    {
        return false;
    }
    else
    {
        if(currentEl->second.pinned)
            pinned_.erase(currentEl->second.iter);
        else
            unpinned_.erase(currentEl->second.iter);
        map_.erase(currentEl);
        return true;
    }
}

bool LRUCache::pin(const std::string& key)
{
    auto currentEl = map_.find(key);

    if(currentEl == map_.end() || currentEl->second.pinned)
    {
        return false;
    }
    else
    {
        Node temp = *currentEl->second.iter;
        unpinned_.erase(currentEl->second.iter);
        pinned_.push_back(temp);

        currentEl->second.iter = --pinned_.end();
        currentEl->second.pinned = true;
        return true;
    }
}

bool LRUCache::unpin(const std::string& key)
{
    auto currentEl = map_.find(key);

    if(currentEl == map_.end() || !currentEl->second.pinned)
    {
        return false;
    }
    else
    {
        Node temp = *currentEl->second.iter;
        pinned_.erase(currentEl->second.iter);
        unpinned_.push_front(temp);

        currentEl->second.iter = unpinned_.begin();
        currentEl->second.pinned = false;
        return true;
    }
}

void LRUCache::merge(LRUCache& other)
{
    if(this == &other)
    {
        return;
    }
    else
    {
        for(auto listIter = other.unpinned_.rbegin();
            listIter != other.unpinned_.rend(); ++listIter)
        {
            if(map_.find(listIter->key) == map_.end())
            {
                unpinned_.push_front(*listIter);
                map_[listIter->key] = {unpinned_.begin(), false};
            }
        }
        for(auto listIter = other.pinned_.rbegin();
            listIter != other.pinned_.rend(); ++listIter)
        {
            if(map_.find(listIter->key) == map_.end())
            {
                pinned_.push_front(*listIter);
                map_[listIter->key] = {pinned_.begin(), true};
            }
        }

        while(size() > capacity_)
            deleteOldest();

        other.clear();
    }
}
