#include <iostream>

int main()
{
    // create lambdas
    int id = 0; // Define an integer variable

    //auto f0 = []() { std::cout << "ID = " << id << std::endl; }; // Error: 'id' cannot be accessed

    id++;
    auto f1 = [id]() { std::cout << "ID = " << id << std::endl; }; // OK, 'id' is captured by value

    id++;
    auto f2 = [&id]() { std::cout << "ID = " << id << std::endl; }; // OK, 'id' is captured by reference

    //auto f3 = [id]() { std::cout << "ID = " << ++id << std::endl; }; // Error, 'id' may not be modified

    auto f4 = [id]() mutable { std::cout << "ID = " << ++id << std::endl; }; // OK, 'id' may be modified

    // execute lambdas
    f1();
    f2();
    f4();

    // create lambda
    auto f = [](const int id) { std::cout << "ID = " << id << std::endl; }; // ID is passed as a parameter

    // execute function object and pass the parameter
    f(id);

    std::cout << std::endl << "/////////////////////////////////////////////" << std::endl << std::endl;

    id = 0; // Define an integer variable

    // capture by reference (immutable)
    auto fc0 = [&id]() { std::cout << "a) ID in Lambda = " << id << std::endl; };

    // capture by value (mutable)
    auto fc1 = [id]() mutable { std::cout << "b) ID in Lambda = " << ++id << std::endl; };
    fc1(); // call the closure and execute the code witin the Lambda
    std::cout << "c) ID in Main = " << id << std::endl;

    // capture by reference (mutable)
    auto fc2 = [&id]() mutable { std::cout << "d) ID in Lambda = " << ++id << std::endl; };
    fc2();
    std::cout << "e) ID in Main = " << id << std::endl;

    // pass parameter
    auto fc3 = [](const int id) { std::cout << "f) ID in Lambda = " << id << std::endl; };
    fc3(++id);

    // observe the effect of capturing by reference at an earlier point in time
    fc0();
    return 0;
}