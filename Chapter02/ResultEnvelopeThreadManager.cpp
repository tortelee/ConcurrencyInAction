// 在一个原来的项目中，使用单线程。我们为了提高速度，发现有些部分可以使用多线程。
// 其中过程的流程是
// 1，计算一些点的值， 
// 2， 将这些点的值写入unv 文件中。 
// 3，将模型的信息也卸任unv文件中。 
// 其中第2 3 步同时都依赖写文件，他们操作同一个文件，最好一次只执行一个。 
// 1 2是有先后顺序的，必须先1 然后再2。 但是3是完全独立的。 
// 请问，这里面的几个关系，需要在多线程中也要处理。请问，需要几个线程？ 
// 线程间的依赖怎么解决？

// 在这个场景中，你可以使用三个线程来并行处理任务。具体的线程分配和依赖关系如下：

// 线程1：计算点的值。
// 线程2：将点的值写入 UNV 文件。
// 线程3：将模型的信息写入 UNV 文件


#include <thread>
#include <mutex>
#include <condition_variable>

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> points;
mutex mtx;
condition_variable conditionVar;
bool pointsCalculated = false;
bool modelInfoWritten  = false;

void calculatePoints()
{
    this_thread::sleep_for(chrono::seconds(1));
    {
        lock_guard<mutex> lock(mtx);
        points = {1, 2, 3, 4, 5};
        pointsCalculated = true;
    }

    conditionVar.notify_all();
}

void writePointsToFile(const string& filename)
{
    unique_lock<mutex> lock(mtx);
    conditionVar.wait(lock, [] { return pointsCalculated && modelInfoWritten; });
    
    // Write points to file
    ofstream file(filename, ios::app);
    if(file.is_open())
    {
        for(auto point : points)
        {
            file << "Points "<< point << endl;
        }
        file.close();
    }

}

void writeModelInfoToFile(const string& filename)
{

    this_thread::sleep_for(chrono::seconds(10));

    // Write model info to file
    ofstream file(filename, ios::app);
    if(file.is_open())
    {
        file << "Model Info ..." << endl;
        file.close();
    }

    {
        lock_guard<mutex> lock(mtx);
        modelInfoWritten = true;
    }

    conditionVar.notify_all();
}

// int main()
// {
//     string filename = "output.unv";

//     thread t1(calculatePoints);
//     thread t2(writePointsToFile, filename);
//     thread t3(writeModelInfoToFile, filename);

//     t1.join();
//     t2.join();
//     t3.join();

//     cout << "All threads completed execution" << endl;

//     return 0;
// }

//是的，lock_guard 在内存顺序中相当于 acquire 和 release 操作的组合