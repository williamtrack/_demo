#pragma once
#include <conio.h>
#include <Windows.h>
#include <iostream>

class CHKey
{
public:
	void test() {
		char ch;
		while (1) {
			if (_kbhit()) {//����а������£���_kbhit()����������
				ch = _getch();//ʹ��_getch()������ȡ���µļ�ֵ
				std::cout << ch;
				if (ch == 27) {
					break;
				}//������ESCʱѭ����ESC���ļ�ֵʱ27.
			}
			Sleep(500);
		}
	}
};

