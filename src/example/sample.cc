#include "example/sample.h"

namespace Example
{

void method1(void)
{
    int a = 0;
    for (int i = 0; i < 1000; i++)
    {
        a *= 2;
    }
    (void)a;
}

void method2(void)
{
    int a = 0;
    for (int i = 0; i < 1000; i++)
    {
        a *= 2;
    }
    (void)a;
}

} // namespace Example
