#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>

using duration_t = std::chrono::microseconds;
int main(){
    unsigned int n, m, num, first;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    int64_t res_time = 0;
    std::cin >> n;
    if(n == 0){
        return 0;
    }
    std::cin >> first;
    std::cin >> m;

    std::vector<int> p(n,0);
    num = pow(first, n - 1);
    int i = n - 1;
    while(m > 0){
        int count = 0;
        while(m  >= num){
            ++count;
            m -= num;
        }
        p[i] = count;
        i -= 1;
        num = pow(first,i);
    }
    end = std::chrono::system_clock::now();
    res_time += std::chrono::duration_cast<duration_t>( end - start ).count();
    for (auto j : p){
        std::cout << j << '\n';
    }
    std::cout << "Time: " << res_time << "*10^-6 seconds" <<'\n'; 
    return 0;
}