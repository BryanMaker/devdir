#include "lru_test.h"

// Declare the size
LRUCache::LRUCache(int n)
{
  csize = n;
}

// Refers key x with in the LRU cache
void LRUCache::refer(int x)
{
  // Not present in cache
  if (ma.find(x) == ma.end())
  {
    // Cache is full
    if (dq.size() == (long unsigned int)csize)
    {
      // Delete least recently used element
      int last = dq.back();

      // Pops the last element
      dq.pop_back();

      // Erease the last
      ma.erase(last);
    }
  }
  // Present in cache
  else
  {
    dq.erase(ma[x]);
  }

  // Update reference
  dq.push_front(x);
  ma[x] = dq.begin();
}

// Function to display contents of cache
void LRUCache::display()
{
  // Iterate in the deque and print
  // all the element in it
  for (auto it = dq.begin(); it != dq.end(); it++)
  {
    cout << (*it) << " ";
  }
  cout << endl;
}
