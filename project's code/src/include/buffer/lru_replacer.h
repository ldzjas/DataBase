/**
 * lru_replacer.h
 *
 * Functionality: The buffer pool manager must maintain a LRU list to collect
 * all the pages that are unpinned and ready to be swapped. The simplest way to
 * implement LRU is a FIFO queue, but remember to dequeue or enqueue pages when
 * a page changes from unpinned to pinned, or vice-versa.
 */

#pragma once

#include "buffer/replacer.h"

#include <memory>
#include <unordered_map>
#include <mutex>

namespace scudb {

    template <typename T> class LRUReplacer : public Replacer<T> {
        struct node {
            node() = default;
            explicit node(T d, node* p = nullptr) : data(d), pre(p) {}
            T data;
            node* pre = nullptr;
            node* next = nullptr;
        };
    public:
        // do not change public interface
        LRUReplacer();

        ~LRUReplacer();

        LRUReplacer(const LRUReplacer&) = delete;
        LRUReplacer& operator=(const LRUReplacer&) = delete;

        void Insert(const T& value);

        bool Victim(T& value);

        bool Erase(const T& value);

        size_t Size();


    private:
      // add your member variables here
        node* head_;
        node* tail_;
        std::unordered_map<T, node*> table_;
        mutable std::mutex mutex_;
        size_t size_;
    };

} // namespace scudb
