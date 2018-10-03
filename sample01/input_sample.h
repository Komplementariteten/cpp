//
// Created by Will nicht on 26.07.18.
//

#ifndef CPP_INPUT_SAMPLE_H
#define CPP_INPUT_SAMPLE_H

#include <iostream>
#include <string>
#include <map>
#include <cctype>


enum class Kind: char {
    name, number, end,
    plus='+', minus='-', mul='*', div='/', print=';', assign='=', lp='(', rp=')'
};

struct Token {
    Kind kind;
    std::string string_value;
    double number_value;
};

double exprs(bool get);
double prim(bool get);
double term(bool get);
void calculate();

// Error Handling
double error(const std::string& s);


class input_sample {
public:
    input_sample(std::istream& s): ip{&s}, owns{false}{}
    input_sample(std::istream* p): ip{p}, owns{true} {}

    ~input_sample() {close();}

    Token get();
    const Token& current() { return ct; }

    void set_input(std::istream& s) {close(); ip=&s; owns= false;}
    void set_input(std::istream* p) {close(); ip=p; owns= true;}
private:
    void close() { if(owns) delete ip; }

    std::istream* ip;
    bool owns;
    Token ct {Kind::end};
};

#endif //CPP_INPUT_SAMPLE_H
