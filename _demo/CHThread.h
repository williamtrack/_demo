#pragma once

#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>

#include <future>

class CHThread
{
public:
	void test();
	static void t1(); //��̬��test���ܹ�����?
	static void t2();
	static void t3();
	static void t4();
private:
	static int cnt;  //��̬���Ա�����������涨��
	static std::mutex mtx;
};

//namespace CONSTANT {
//	static int cnt = 20; //int cnt; //error ͷ�ļ����ܶ�����ͨ����, ���������Ե������ӱ���
//	static std::mutex m;
//}