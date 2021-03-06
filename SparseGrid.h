//We need a hash table:
//We can either use
// a) Google's sparsehash dense_hash_map, or
// b) Boost's unordered_map, or
// c) the C++11 std::unordered_map  (if using nvcc with -std=c++11)
// Option (a) seems fastest. To speed up (b) or (c), use a "greedy" custom allocator to prevent threads getting in each others way to access memory to grow the map??

#define USE_GOOGLE_SPARSEHASH

#pragma once
#include <stdint.h>

#ifdef USE_GOOGLE_SPARSEHASH
#include <boost/functional/hash.hpp>
#include <google/dense_hash_map>
struct SparseGridEq
{
  bool operator()(const int64_t a, const int64_t b) const
  {
    return a==b;
  }
};
typedef google::dense_hash_map<int64_t, int, boost::hash<int64_t>, SparseGridEq> SparseGridMap;
typedef google::dense_hash_map<int64_t, int, boost::hash<int64_t>, SparseGridEq>::iterator SparseGridIter;

class SparseGrid {
public:
  int backgroundCol;
  SparseGridMap mp;
  SparseGrid() {
    backgroundCol=-1; //Indicate that no "null vector" is needed
    mp.set_empty_key(-1); // dense_hash_map needs an empty key that will not be used as a real key
  }
};
#else
#include <boost/unordered_map.hpp>
typedef boost::unordered_map<int64_t,int> SparseGridMap;
typedef boost::unordered_map<int64_t,int>::iterator SparseGridIter;

class SparseGrid {
public:
  int backgroundCol; //Set to -1 when no "null vector" is needed
  SparseGridMap mp;
  SparseGrid() {
    backgroundCol=-1; //Indicate that no "null vector" is needed
  }
};
#endif
