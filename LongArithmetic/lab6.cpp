#include "BigInt.hpp"
#include <iostream>
#include <string>
#include <chrono>

using duration_t = std::chrono::microseconds;
int main(){
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    std::string str1, str2;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t res_time = 0;
    char op;
    while(std::cin >> str1 >> str2 >> op){
        start = std::chrono::system_clock::now();
        TBigInt num1(str1);
        TBigInt num2(str2);
        switch(op) {
            case '+':
                std::cout << num1 + num2 << '\n';
                break;

            case '-':
                if (num1 < num2)
                    std::cout << "Error" << '\n';
                else
                    std::cout << num1 - num2 << '\n';
                break;

            case '*':
                std::cout << num1 * num2 << '\n';
                break;

            case '/':
                if(num2 == TBigInt(0)){
                    std::cout << "Error" << '\n';
                }
                else{
                    std::cout << num1 / num2 << '\n';
                }
                break;

            case '^':
                if (num1 == TBigInt(0)) {
                    if (num2 == TBigInt(0))
                        std::cout << "Error" << '\n';
                    else
                        std::cout << "0" << '\n';
                } else if (num1 == TBigInt(1)) {
                    std::cout << "1" << '\n';
                } else
                    std::cout << num1.Power(num2) << '\n';
                break;
            case '<':
                if(num1 < num2)
                    std::cout << "true" << '\n';
                else 
                    std::cout << "false" << '\n';
                break;

            case '>':
                if (num1 > num2)
                    std::cout << "true" << '\n';
                else
                    std::cout << "false" << '\n';
                break;

            case '=':
                if(num1 == num2)
                    std::cout << "true" << '\n';
                else 
                    std::cout << "false" << '\n';
                break;
        }

        
    }
    end = std::chrono::system_clock::now();
    res_time += std::chrono::duration_cast<duration_t>( end - start ).count();
    std::cout << "Time: " << res_time << "*10^-6 seconds" <<'\n'; 
    return 0;
}