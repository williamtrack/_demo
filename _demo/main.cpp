// ConsoleApplication.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "CHTime.h"
#include "CHThread.h"
#include "CHVector.h"
#include "CHPointer.h"
#include "CHTemplate.h"
#include "CHMap.h"
#include "CHRegex.h"
#include "CHKey.h"

#pragma comment(lib,"../x64/debug/dll.lib")  //lib代码配置, properties-linker-input
#include "../dll/CHDll.h"
//extern "C" __declspec(dllimport) void dlltest(char* str); //引入头文件或直接引入声明

//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"") //设置入口非console时添加 properties-linker-system-subsystem

using namespace std;

template <typename T, typename _Fn> T hhh(T _First, T _Last, _Fn _Func) {
	return _Func(_First, _Last);
}

int main()
{
	std::cout << "=== Hello World! ===\n";

	////=== input
	//int sum = 0,value = 0;
	//while (std::cin >> value) {
	//    sum += value;
	//} //input ctrl+z to end
	//std::cout << sum << std::endl;

	////=== lambda
	//int test = 100;
	//auto fun = [test](int a, int b) {if (a < test)return a + b; else return a - b; };
	//auto add = [](int a, int b) { return a + b; };
	//std::cout << add(10, 20);
	//std::cout << hhh(10, 20, [](int a, int b) {return a + b; });

	////=== 外部dll引入测试
	//char a[64] = "abc";
	//dlltest(a);
	//CHDll chdll;
	//chdll.setID(234);
	//chdll.getID();
	//auto b = 100;
	//printf("%d\n", b);

	////=== 外部lib引入, 多个lib函数有同名则引用第一个,和主工程同名则使用主工程
	CHTime chtime;
	//chtime.pt("test ");
	std::cout<<chtime.getTImeMicros()<<std::endl;
	//std::this_thread::sleep_for(std::chrono::microseconds(1000));//4ms误差
	std::cout<<chtime.getTImeMicros();
	test();

	////=== thread test
	//CHThread th;
	//th.test();

	//=== vector test
	//CHVector chvector;
	//chvector.test2();

	////=== shared_ptr test
	//CHPointer chPointer;
	//chPointer.test();

	////=== template
	//CHTemplate chtemplate;
	//chtemplate.test();

	////=== map test
	//CHMap chmap;
	//chmap.test();

	////=== regex
	//CHRegex chregex;
	//chregex.test();

	//uint8_t* p=0;
	//uint8_t a[10] = { 'a','b','c','a','b','c' };
	//p = a;
	//p[4] = '\0';
	//std::cout << p<<std::endl;
	//std::cout << p[1]<<std::endl;

	////=== 捕获键盘
	//CHKey chkey;
	//chkey.test();

	std::cout << "\n=== This is end! ===\n";
	system("pause");
}
