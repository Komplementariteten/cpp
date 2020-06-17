//
// Created by Will nicht on 18.05.20.
//

#include <iostream>
#include <thread>
#include <vector>
#include <future>

class Vehicle
{
public:
    Vehicle() : _id(0) {}
    void addID(int id) { _id = id; }
    void printID()
    {
        std::cout << "Vehicle ID=" << _id << std::endl;
    }
    void operator()()
    {
        std::cout << "Vehicle object has been created \n" << std::endl;
    }
private:
    int _id;
};

void threadFunction() {
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    std::cout << "Thread (" << std::this_thread::get_id() << ") is done!" << std::endl;
}
void threadFunctionEven()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work
    std::cout << "Even thread\n";
}
void threadFunctionOdd()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work
    std::cout << "Odd thread\n";
}

void threadFunction2() {
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    std::cout << "Thread (" << std::this_thread::get_id() << ") for the first time is done!" << std::endl;

    std::this_thread::sleep_for(std::chrono::microseconds(50));
    std::cout << "Thread (" << std::this_thread::get_id() << ") for the second time is done!" << std::endl;
}

void divideByNumber(std::promise<double> &&prms, double num, double denom)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
    try
    {
        if (denom == 0)
            throw std::runtime_error("Exception from thread: Division by zero!");
        else
            prms.set_value(num / denom);
    }
    catch (...)
    {
        prms.set_exception(std::current_exception());
    }
}

void printHello()
{
    // perform work
    std::cout << "Hello from Worker thread #" << std::this_thread::get_id() << std::endl;
}

int main(){
    unsigned int nunmber_cores = std::thread::hardware_concurrency();
    std::cout << "Thead id=" << std::this_thread::get_id() << std::endl;
    std::cout << "System has " << nunmber_cores << std::endl;

    std::cout << std::endl << "/////////////////////////////////////////////" << std::endl << std::endl;

    std::thread t(threadFunction);
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    std::cout << "Main is done waiting" << std::endl;
    t.join();

    std::cout << std::endl << "/////////////////////////////////////////////" << std::endl << std::endl;

    std::thread t2(threadFunction2);
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    std::cout << "Main is done waiting first time" << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    std::cout << "Main is done waiting second time" << std::endl;
    t2.join();

    std::cout << std::endl << "/////////////////////////////////////////////" << std::endl << std::endl;

    std::thread t3(threadFunction2);
    t3.join();
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    std::cout << "Main is done waiting first time" << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    std::cout << "Main is done waiting second time" << std::endl;

    std::cout << std::endl << "/////////////////////////////////////////////" << std::endl << std::endl;

    std::thread t4(threadFunction);
    t4.detach();
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    std::cout << "Main is done waiting first time" << std::endl;

    std::cout << std::endl << "/////////////////////////////////////////////" << std::endl << std::endl;

    for(int i = 0; i < 6; i++) {
        if(i % 2 == 0){
            std::thread tl(threadFunctionEven);
            tl.detach();
        } else {
            std::thread tl(threadFunctionOdd);
            tl.detach();
        }

    }

    // ensure that main does not return before the threads are finished
    std::this_thread::sleep_for(std::chrono::milliseconds(5)); // simulate work

    std::cout << "End of main is reached" << std::endl;

    std::cout << std::endl << "/////////////////////////////////////////////" << std::endl << std::endl;

    std::thread tf1( (Vehicle()) ); // Add an extra pair of parantheses

    std::thread tf2 = std::thread( Vehicle() ); // Use copy initialization

    std::thread tf3{ Vehicle() };// Use uniform initialization with braces

    tf1.join();
    tf2.join();
    tf3.join();

    std::cout << std::endl << "/////////////////////////////////////////////" << std::endl << std::endl;

    int id = 0; // Define an integer variable

    // starting a first thread (by reference)
    auto f0 = [&id]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "a) ID in Thread (call-by-reference) = " << id << std::endl;
    };
    std::thread tl1(f0);

    // starting a second thread (by value)
    std::thread tl2([id]() mutable {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "b) ID in Thread (call-by-value) = " << id << std::endl;
    });

    // increment and print id in main
    ++id;
    std::cout << "c) ID in Main (call-by-value) = " << id << std::endl;

    // wait for threads before returning
    tl1.join();
    tl2.join();

    std::cout << std::endl << "55/////////////////////////////////////////////" << std::endl << std::endl;

    // create thread
    Vehicle v1, v2;
    std::thread tv1 = std::thread(&Vehicle::addID, v1, 1); // call member function on object v
    std::thread tv2 = std::thread(&Vehicle::addID, &v2, 2); // call member function on object v

    // wait for thread to finish
    tv1.join();
    tv2.join();

    // print Vehicle id
    v1.printID();
    v2.printID();

    std::cout << std::endl << "/////////////////////////////////////////////" << std::endl << std::endl;

    // create thread
    std::shared_ptr<Vehicle> vr(new Vehicle);
    std::thread tvv = std::thread(&Vehicle::addID, vr, 1); // call member function on object v

    std::shared_ptr<Vehicle> vr2 = std::make_shared<Vehicle>();
    std::thread tvv2 = std::thread(&Vehicle::addID, vr2, 1); // call member function on object v

    // wait for thread to finish
    tvv.join();
    tvv2.join();

    // print Vehicle id
    vr->printID();
    vr2->printID();

    std::cout << std::endl << "/////////////////////////////////////////////" << std::endl << std::endl;

    // create threads
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 5; ++i)
    {
        // copying thread objects causes a compile error
        /*
        std::thread t(printHello);
        threads.push_back(t);
        */

        // moving thread objects will work
        threads.emplace_back([i]() {

            // wait for certain amount of time
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * i));

            // perform work
            std::cout << "Hello from Worker thread #" << i << std::endl;
        });
    }

    // do something in main()
    std::cout << "Hello from Main thread #" << std::this_thread::get_id() << std::endl;

    // call join on all thread objects using a range-based loop
    for (auto &t : threads)
        t.join();


    std::cout << std::endl << "FOTURE AND PROMISE /////////////////////////////////////////////" << std::endl << std::endl;

    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();

    // start thread and pass promise as argument
    double num = 42.0, denom = 0.0;
    std::thread tp(divideByNumber, std::move(prms), num, denom);

    // retrieve result within try-catch-block
    try
    {
        double result = ftr.get();
        std::cout << "Result = " << result << std::endl;
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
    }

    // thread barrier
    tp.join();


    std::cout << std::endl << "FOTURE AND PROMISE /////////////////////////////////////////////" << std::endl << std::endl;

    return 0;
}