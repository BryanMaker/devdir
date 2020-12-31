#include "imp_list.h"
#include "imp_list.hpp"
#include <string>

struct student
{
  std::string name;
  int age;

  student(std::string n, int a):name(n), age(a){}

  // 重载输出操作
  friend std::ostream &operator<<(std::ostream &os, const student &stu)
  {
    os << stu.name << " " << stu.age;
    return os;
  }
};

int main()
{
  imp_list<student> l;
  // 结构体临时变量传递给push_back函数
  l.push_back(student("bob", 1));
  l.push_back(student("allen", 2));
  l.push_back(student("anna", 3));
  l.print();

  for (imp_list<student>::iterator it = l.begin(); it != l.end(); it++)
  {
    std::cout << *it << std::endl;
    *it = student("wengle", 18);
  }

  for (imp_list<student>::iterator it = l.begin(); it != l.end(); it++)
  {
    std::cout << *it << std::endl;
    *it = student("wengle", 18);
  }

  return 0;
}
