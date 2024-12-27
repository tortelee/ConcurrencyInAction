#include <iostream>
#include <thread>
#include <string>

using namespace std;

void hello(string words)
{
    std::cout << "Hello Concurrent World\n";
    std::cout << words << std::endl;
}

int main()
{
    string words = "I am the input the parameter";
    thread t(hello, words);
    t.join();

    return 0;
}