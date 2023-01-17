#include <iostream>
#include <type_traits>

/**
 * 按值传递，val时全新对象
 * 推到出的结果都是没有修饰的类型，数组转为指针，修饰指针指向内容不变的const不忽略
 *
 */
template<typename T>
void fun_normal(T val){
    std::cout << __PRETTY_FUNCTION__  << std::endl;
}

/**
 * 引用时，会去除引用，保留const信息
 *
 */
template<typename T>
void fun_ref(T& val){
    std::cout << __PRETTY_FUNCTION__  << std::endl;
}

/**
 * 万能引用，原类型信息被编译在T内
 * 右值使用原类型表示如：int
 * 左值使用原类型引用，如：int&
 *
 */
template<typename T>
void fun_universe(T&& val){
    std::cout << __PRETTY_FUNCTION__  << std::endl;
}

int main(){
    int val = 1;
    const int c_val = 1;
    const int& cr_val = val;
    int arr_val[2]{1,2};
    const int* const cp_val  = nullptr;
    fun_normal(val);   // int
    fun_normal(c_val); // int
    fun_normal(cr_val);// int
    fun_normal(1);    // int
    fun_normal(arr_val); // int*
    fun_normal(cp_val); // const int*

    fun_ref(val);   // int
    fun_ref(c_val); // const int
    fun_ref(cr_val);// const int
    // fun_ref(1); // 不可传递
    fun_ref(arr_val);// int[2]
    fun_ref(cp_val);// const int* const

    fun_universe(val);   // int&
    fun_universe(c_val); // const int&
    fun_universe(cr_val);// const int&
    fun_universe(1);    // int

    fun_universe("Hello");


}