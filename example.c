/* A simple example using een to test a couple of obvious cases. */

#include "een.h"

void test1(void)
{
  lok('a' == 'a');
}

void test2(void)
{
  lequal(5, 5);
  lfequal(5.5, 5.5);
  lsequal("abc", "abc");
}

int main(void)
{
  lrun("test1", test1);
  lrun("test2", test2);
  lresults();
  return lfails != 0;
}
