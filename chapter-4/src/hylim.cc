
#include "hylimt.h"

void templateTest()
{
    BankUser<float> user_float(0.f);
    std::cout << user_float.Deposit(1.0f) << std::endl;

    BankUser<double> user_double(0.0);
    std::cout << user_double.Deposit(1.0) << std::endl;

    auto p1 = HYPair<int, float>{5, 8.7f};
    auto p2 = make_HYPair(5, 8.7f);
    auto p3 = make_HYPair<int, float>(5, 8.7f);
    std::cout << "p1 :" << p1.first << "," << p1.second << "\n"
              << "p2 :" << p2.first << "," << p2.second << "\n"
              << "p3 :" << p3.first << "," << p3.second << std::endl;

    FreeData<> freeData;
    // 1,2.1f,"Hello world!"
    HYTuple<int,float,std::string> hyTuple(1,2.1f,"Hello world!");

}

int main(int argc, const char *argv[])
{

    return 0;
}