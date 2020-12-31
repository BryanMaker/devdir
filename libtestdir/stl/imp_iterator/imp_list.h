// Implement elementary list container
#ifndef CPP_PRIMER_IMP_LIST_H
#define CPP_PRIMER_IMP_LIST_H

#include <iostream>

template<typename T> 
class node
{
  public:
    T value;
    node* next;

    node();
    node(T val, node* p = nullptr);
};

template<typename T>
class imp_list
{
  private:
    node<T>* head;
    node<T>* tail;
    int size;

  private:
    class list_iterator;

  public:
    // 类型别名
    typedef list_iterator iterator;
    imp_list();

    // 从链表尾部插入元素
    void push_back(const T &value);
    // 打印链表元素
    void print(std::ostream &os = std::cout) const;
    
  public:
    // 操作迭代器的方法
    // 返回链表头部指针
    iterator begin() const;
    // 返回链表尾部指针
    iterator end() const;
};
#endif
