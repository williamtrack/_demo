#include "CHRegex.h"
#include <iostream>
#include <regex>

void CHRegex::test()
{
	using namespace std;
	//cout << regex_match("123", regex("\\d*")) << endl;

	string str = "Hello_2018_2020";
	smatch result;
	regex pattern("(.{5})_(\\d{4})"); //ƥ��5�����ⵥ�ַ� + �»��� + 4������
	regex pattern2("_(\\d{4})"); //ƥ��5�����ⵥ�ַ� + �»��� + 4������

	//�ж��Ƿ�һ��
	//if (regex_match(str, result, pattern))
	//{
	//	cout << "match num:" << result.size() << endl;
	//	for (int i = 0; i < result.size(); i++) {
	//		cout << result[i] << endl;
	//		//cout << result.str(i) << endl; //�����ʾ��ʽ2
	//	}
	//	//����ƥ������Hello_2018
	//	//��һ��ƥ������ݣ�Hello  //?
	//	//�ڶ���ƥ������ݣ�2018   //?
	//}

	//����Ѱ��
	//if (regex_search(str, result, pattern))
	//{
	//	cout << "search num:" << result.size() << endl;
	//	for (int i = 0; i < result.size(); i++) {
	//		cout << result[i] << endl;
	//	}
	//}

	//���Ѱ��
	for (sregex_iterator it(str.begin(), str.end(), pattern2), end_it; it != end_it; ++it) { //end_it��һ���յ�����
		cout << it->str() << endl;
	}
}
