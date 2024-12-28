// This file contains some examples about std::bind

#include <iostream>
#include <functional>

using namespace std;

void printSum(int a, int b)
{
    cout<<"Sum is "<<a + b<<endl; 
}

class hello
{
public:
    void sayHello() const
    {
        cout<<"Hello"<<endl;
    }
};

int main()
{
    auto bindFunction = bind(printSum,1,2);
    bindFunction();

    auto bindFunction2 = bind(printSum, placeholders::_1, 10);
    bindFunction2(5);

    std::function<void (const hello&)> f = &hello::sayHello;
    hello h;
    f(h);

    std::function<void (hello*)> f2 = std::bind(&hello::sayHello, placeholders::_1);
    f2(&h);

}