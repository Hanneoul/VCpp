#include <iostream>
#include <chrono>
#include <cmath>
#include <conio.h>

int main(void)
{
    std::chrono::system_clock::time_point start;
    std::chrono::duration<double> sec;
    bool checkTime = false;

    while (true)
    {
        char c;
        
        if (_kbhit()) {        //키보드 입력 확인 (true / false)
            if (checkTime == false)
            {
                checkTime = true;
                start = std::chrono::system_clock::now();
            }
            c = _getch();      // 방향키 입력시 224 00이 들어오게 되기에 앞에 있는 값 224를 없앰
            if (c == 27) {    // -32로 입력되면
                exit(1);
            }
        }

        if (checkTime)
        {
            sec = std::chrono::system_clock::now() - start;
        }       

        start = std::chrono::system_clock::now();

        sec = std::chrono::system_clock::now() - start;
        std::cout << "for문을 돌리는데 걸리는 시간(초) : " << sec.count() << "seconds" << std::endl;
    }
    
    
    return 0;
}