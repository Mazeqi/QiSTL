#include <iostream>
using namespace std;
class A {
public:
    int* pointer;
    A() :pointer(new int(1)) {
        std::cout << "构造" << pointer << std::endl;
    }
    A(A& a) :pointer(new int(*a.pointer)) {
        std::cout << "拷贝" << pointer << std::endl;
    } // 无意义的对象拷贝
    A(A&& a) :pointer(a.pointer) {
        a.pointer = nullptr;
        std::cout << "移动" << pointer << std::endl;
    }
    ~A() {
        std::cout << "析构" << pointer << std::endl;
        delete pointer;
    }
};
// 防止编译器优化
A return_rvalue(bool test) {
    A a, b;
    if (test) return a; // 等价于 static_cast<A&&>(a);
    else return b;     // 等价于 static_cast<A&&>(b);
}
//int main() {
//    A obj = return_rvalue(false);
//    std::cout << "obj:" << std::endl;
//    std::cout << obj.pointer << std::endl;
//    std::cout << *obj.pointer << std::endl;
//    return 0;
//}


//-----------------------------------------------------

void reference(int& v) {
    std::cout << "左值" << std::endl;
}
void reference(int&& v) {
    std::cout << "右值" << std::endl;
}
template <typename T>
void pass(T&& v) {
    std::cout << "普通传参:";
    reference(v); // 始终调用 reference(int&)
}
int main() {
    std::cout << "传递右值:" << std::endl;
    pass(1); // 1是右值, 但输出是左值

    std::cout << "传递左值:" << std::endl;
    int l = 1;
    pass(std::move(l)); // l 是左值, 输出左值

    return 0;
}