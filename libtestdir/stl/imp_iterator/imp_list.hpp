#include "imp_list.h"

/*************************node***************************/
template<typename T>
node<T>::node() : next(nullptr) {}

template<typename T>
node<T>::node(T val, node* p) : value(val), next(p) {}

/*************************imp_list***********************/
template<typename T>
imp_list<T>::imp_list()
{
  head = nullptr;
  tail = nullptr;
  size = 0;
}

template<typename T>
void imp_list<T>::push_back(const T &value)
{
  // 从链表尾部插入元素
  if (head == nullptr)
  {
    head = new node<T>(value);
    tail = head;
  }
  else
  {
    tail->next = new node<T>(value);
    tail = tail->next;
  }
  size++;
}
// 打印链表元素
template<typename T>
void imp_list<T>::print(std::ostream &os) const
{
  for (node<T>* ptr = head; ptr != tail->next; ptr = ptr->next)
  {
    os << ptr->value << std::endl;
  }
}

template<typename T>
typename imp_list<T>::iterator imp_list<T>::begin() const
{
  return list_iterator(head);
}

template<typename T>
typename imp_list<T>::iterator imp_list<T>::end() const
{
  return list_iterator(tail->next);
}

/*************************list_iterator******************/
template<typename T>
class imp_list<T>::list_iterator
{
  private:
    // 指向list容器中的某个元素的指针
    node<T>* ptr;

  public:
    list_iterator(node<T>* p = nullptr) : ptr(p) {}

    // 重载++、--、*、->等运算符
    // 返回引用，方便通过*it来修改对象
    T& operator*() const
    {
      return ptr->value;
    }

    node<T>* operator->() const
    {
      return ptr;
    }

    // ++i
    list_iterator& operator++()
    {
      ptr = ptr->next;
      return *this;
    }

    // i++
    list_iterator operator++(int)
    {
      node<T>* tmp = ptr;
      // this是指向list_iterator的常量指针,
      // 因此*this就是list_iterator对象，
      // 前置++已经重载过了
      ++(*this);
      return list_iterator(tmp);
    }

    bool operator==(const list_iterator &t) const
    {
      return t.ptr == this->ptr;
    }

    bool operator!=(const list_iterator &t) const
    {
      return t.ptr != this->ptr;
    }
};
