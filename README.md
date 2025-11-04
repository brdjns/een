# een

een is a very minimal unit-testing "framework" written in C and
implemented in a single header file. It's handy when you want some
real simple unit tests for a small project.  een is derived from
[Minctest](https://github.com/codeplea/minctest).

een implements assertion and equality functions. It tracks and times
how many tests pass and fail. Failed tests also display which line the
failing test code was on.

## Features

- ISO C99 with no dependencies
- Single header file
- Reports file and line number for failed assertions
- Reports run-time for each test
- Tests continue even after an assertion fails
- Assertions for float, integer, and string equality

## Example

```c
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
```

That produces the following output:

```sh
            test1:
             -- pass: 1                    fail: 0                    time: 12ms
            test2:
             -- pass: 3                    fail: 0                    time: 0ms
    ALL TESTS PASSED (4/4)
```

### Hints

All functions and variables start with the letter 'l'.

## License

een is released under the terms of the Zlib license.
