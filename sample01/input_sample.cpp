//
// Created by Will nicht on 26.07.18.
//

#include "input_sample.h"

// Global deklarations
input_sample ts {std::cin};
std::map<std::string, double> table;
int error_count = 0;

// Handling the Stuff
double prim(bool get) {
    if(get) ts.get();
    switch (ts.current().kind) {
        case Kind::number:{
            double v = ts.current().number_value;
            ts.get();
            return v;
        }
        case Kind::name: {
            double& v = table[ts.current().string_value];
            if (ts.get().kind == Kind::assign) v = exprs(true);
            return v;
        }
        case Kind::minus: {
            return -prim(true);
        }
        case Kind::lp:
        {
            auto e = exprs(true);
            if (ts.current().kind != Kind::rp) return error("')' expected");
            ts.get();
            return e;
        }
        default:
            return error("primary expected");
    }
}
double term(bool get) {
    double left = prim(get);

    for(;;) {
        switch (ts.current().kind){
            case Kind::mul:
                left *= term(true);
                break;
            case Kind::div:
                if(auto d = prim(true)) {
                    left /= d;
                    break;
                }
                return error("divide by 0");
            default:
                return left;
        }
    }
}

double exprs(bool get){
    double left = term(get);
    for(;;) {
        switch (ts.current().kind){
            case Kind::plus:
                left += term(true);
                break;
            case Kind::minus:
                left -= term(true);
                break;
            default:
                return left;
        }
    }
}

void calculate() {
    for(;;) {
        ts.get();
        if(ts.current().kind == Kind::end) break;
        if(ts.current().kind == Kind::print) continue;
        std::cout << exprs(false) << '\n';
    }
}
Token input_sample::get() {
    char ch = 0;
    *ip >> ch;

    switch (ch) {
        case 0:
            return ct={Kind::end};
        case ';':
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return ct= {static_cast<Kind>(ch)};
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            ip->putback(ch);
            *ip >> ct.number_value;
            ct.kind=Kind::number;
            return ct;
        default:
            if(isalpha(ch)){
                ip->putback(ch);
                *ip >> ct.string_value;
                ct.kind = Kind::name;
                return ct;
            }
            error("bad token");
            return ct={Kind::print};
    }
}
double error(const std::string& s){
    error_count++;
    std::cerr << "error: " << '\n';
    return 1;
}
