#include "CHMap.h"
#include <map>
#include <string>
#include <iostream>

void CHMap::test()
{
	using namespace std;
	map<int, int> list1;
	map<int, string> list2 = { {1,"java"},{2,"c++"},{3,"python"} };
	map<int, string> list3 = { pair<int,string>(1,"java"),{2,"c++"},{3,"python"} };
	
	//���Ԫ��
	//map��key��ֵ��Ψһ�ģ��������һ���Ѿ����ڵ�keyֵ�ᵼ��ԭ��ֵ�ĸ���
	list1.insert(pair<int, int>(0, 15));
	list1.insert({ 1,13 });
	list1.insert({ 2,200 });
	list1.insert({ 3,300 });
	list1.insert({ 4,400 });


	//ɾ��Ԫ��
	list1.erase(1);

	//����,������
	for (auto iter = list1.begin(); iter != list1.end(); ++iter) {
		cout << iter->first << "  " << iter->second << endl;
	}

	//����Ԫ�غ͸�ֵ 3�ַ���
	cout << list1[2]<<endl;
	cout << list1.at(3)<<endl;
	map<int, int>::iterator it = list1.find(4); //find���ص�����
	if (it != list1.end()) cout << it->first << ' ' << it->second << endl;

	//�����÷�
	map<string, int> map_1;
	map_1.clear();                //�������Ԫ��
	map_1.insert({ "a",10 });
	map_1.empty();                //���Ϊ�շ���1�����𷵻�0
	map_1.size();                 //����������Ԫ�ظ���
	map_1.max_size();             //���������������ɵ����Ԫ��
	map_1.end();				  //һ�����ڵ������ж��Ƿ��Ҳ���


	////���
	////��һ�֣���insert��������pair���ݣ�
	//map<int, string> my_map;
	//my_map.insert(pair<int, string>(1, "first"));
	//my_map.insert(pair<int, string>(2, "second"));

	////�ڶ��֣���insert��������value_type���ݣ�
	//my_map.insert(map<int, string>::value_type(1, "first"));
	//my_map.insert(map<int, string>::value_type(2, "second"));

	//map<int, string>::iterator it;           //����������
	//for (it = my_map.begin(); it != my_map.end(); it++)
	//	cout << it->first << it->second << endl;
}
