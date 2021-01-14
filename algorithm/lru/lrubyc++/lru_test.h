// We can use stl container list as a double
// ended queue to store the cache keys, with
// the descending time of reference from front
// to back and a set container to check presence
// of a key. But to fetch the address of the key
// in the list using find(), it takes O(N) time.
// This can be optimized by storing a reference
//	 (iterator) to each key in a hash map.
#include <list>
#include <unordered_map>
#include <iostream>
using namespace std;

class LRUCache
{
  // Store keys of cache
  list<int> dq;

  // Store reference of key in cache
  unordered_map<int, list<int>::iterator> ma;
  // Maxinum capacity of cache
  int csize;

  public:
    LRUCache(int n);
    void refer(int x);
    void display();
};
