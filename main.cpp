#include <iostream>

#include "BigInt.hpp"

std::string ToString(bool value) {
    if (value) {
        return "True";
    }
    return "False";
}

bool pass_tests() {
    std::vector<bool> tests {
        BigInteger("1") + BigInteger("2") == BigInteger("3"),
        BigInteger("3") - BigInteger("2") == BigInteger("1"),
        BigInteger("2") * BigInteger("2") == BigInteger("4"),
        BigInteger("2") <= BigInteger("2"),
        BigInteger("3") > BigInteger("1"),
        BigInteger("111111111111111") + BigInteger("111111111111111") == BigInteger("222222222222222"),
        BigInteger("1000000000000") * BigInteger("100000000000") == BigInteger("100000000000000000000000"),
        BigInteger("-1") * BigInteger("1") == BigInteger("-1")
    };
    return std::find(tests.begin(), tests.end(), false) == tests.end();
}

int main(int argc, char *argv[]) {
    if (!pass_tests()){
        std::cout << "Program is incorrect";
        return 0;
    }
    if (argc == 4) {
        BigInteger first(argv[1]);
        BigInteger second(argv[3]);
        std::string operation (argv[2]);
        if (operation == "+") {
            std::cout << first + second;
        } else if (operation == "-") {
            std::cout << first - second;
        } else if (operation == "*") {
            std::cout << first * second;
        } else if (operation == "<") {
            std::cout << ToString(first < second);
        } else if (operation == "<=") {
            std::cout << ToString(first <= second);
        } else if (operation == "==") {
            std::cout << ToString(first == second);
        } else if (operation == ">=") {
            std::cout << ToString(first >= second);
        } else if (operation == ">") {
            std::cout << ToString(first > second);
        }  else {
            std::cout << "Operation is not recognized";
        }
    } else {
        std::cout << "Wrong number of arguments";
    }
    return 0;
}
