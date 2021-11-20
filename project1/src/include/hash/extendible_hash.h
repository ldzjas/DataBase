/*
 * extendible_hash.h : implementation of in-memory hash table using extendible
 * hashing
 *
 * Functionality: The buffer pool manager must maintain a page table to be able
 * to quickly map a PageId to its corresponding memory location; or alternately
 * report that the PageId does not match any currently-buffered page.
 */

#pragma once

#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <mutex>
#include <memory>

#include "hash/hash_table.h"

namespace scudb {

template <typename K, typename V>
class ExtendibleHash : public HashTable<K, V> {
	struct Bucket {
		int localDepth;
		std::map<K, V> items;
		explicit Bucket(int depth) :localDepth(depth) {};
		size_t id = 0;
  };
public:
  // constructor
  ExtendibleHash(size_t size);
  // helper function to generate hash addressing
  size_t HashKey(const K &key) const;
  // helper function to get global & local depth
  int GetGlobalDepth() const;
  int GetLocalDepth(int bucket_id) const;
  int GetNumBuckets() const;
  // lookup and modifier
  bool Find(const K &key, V &value) override;
  bool Remove(const K &key) override;
  void Insert(const K &key, const V &value) override;

private:
  // add your own member variables here
	int globalDepth;
	size_t bucketMaxSize;
	int numBuckets;
	std::vector<std::shared_ptr<Bucket>> bucketTable;
	std::shared_ptr<Bucket> split(std::shared_ptr<Bucket>&);
	std::mutex mutex;
	int getBucketIndex(const K& key) const;
	int bucket_count;
};
} // namespace scudb
