#include <iostream>
using namespace std;
class A {
public:
    int* pointer;
    A() :pointer(new int(1)) {
        std::cout << "����" << pointer << std::endl;
    }
    A(A& a) :pointer(new int(*a.pointer)) {
        std::cout << "����" << pointer << std::endl;
    } // ������Ķ��󿽱�
    A(A&& a) :pointer(a.pointer) {
        a.pointer = nullptr;
        std::cout << "�ƶ�" << pointer << std::endl;
    }
    ~A() {
        std::cout << "����" << pointer << std::endl;
        delete pointer;
    }
};
// ��ֹ�������Ż�
A return_rvalue(bool test) {
    A a, b;
    if (test) return a; // �ȼ��� static_cast<A&&>(a);
    else return b;     // �ȼ��� static_cast<A&&>(b);
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
    std::cout << "��ֵ" << std::endl;
}
void reference(int&& v) {
    std::cout << "��ֵ" << std::endl;
}
template <typename T>
void pass(T&& v) {
    std::cout << "��ͨ����:";
    reference(v); // ʼ�յ��� reference(int&)
}
int main() {
    std::cout << "������ֵ:" << std::endl;
    pass(1); // 1����ֵ, ���������ֵ

    std::cout << "������ֵ:" << std::endl;
    int l = 1;
    pass(std::move(l)); // l ����ֵ, �����ֵ

    return 0;
}