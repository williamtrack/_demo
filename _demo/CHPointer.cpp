#include "CHPointer.h"

#include <memory>
#include <iostream>


class Bar { public: ~Bar() { std::cout << "destroying"; } };

void CHPointer::test()
{
	////declare
	////way 1
	//auto p1 = std::make_shared<char>(5); //�������+1
	//std::cout << p1.use_count() << std::endl;

	////way 2
	//char* sp1 = new char[3];
	//memset(sp1, 'a', sizeof(char) * 3);


	//std::shared_ptr<char> sp2(p1); //�����ü���+1
	//std::cout << sp2.use_count() << std::endl;
	//sp2.get()[2] = 'b';
	//printf("%c\n", sp2.get()[2]);
	//std::shared_ptr<char> sp3(p1); //�����ü���+1
	//std::cout << sp2.use_count() << std::endl;

	//swap reset
	auto sp1 = std::make_shared<Bar>(); //+1
	std::shared_ptr<Bar> sp2;
	auto sp3 = sp1; //+1
	//auto sp3(sp1);
	std::cout << "initially, sp1.count = " << sp1.use_count() << ",sp2.count = " << sp2.use_count() << ",sp3.count = " << sp3.use_count() << std::endl;
	sp1.swap(sp2);
	std::cout << "after swapping, sp1.count = " << sp1.use_count() << ",sp2.count = " << sp2.use_count() << ",sp3.count = " << sp3.use_count() << std::endl;
	//����֮��sp3�ļ�������Ӱ�졣��sp1���㣬sp2�ļ��������sp1ԭ���ļ�������bar��swapǰ��û������
	sp3.reset();
	std::cout << "after reset, sp1.count = " << sp1.use_count() << ",sp2.count = " << sp2.use_count() << ",sp3.count = " << sp3.use_count() << std::endl;
	//sp2������һ sp3�ļ�����Ϊ0
	std::cin.get();
}

void CHPointer::test2()
{
    std::unique_ptr<int> up1(new int(11));   // �޷����Ƶ�unique_ptr
    //unique_ptr<int> up2 = up1;        // err, ����ͨ������
    std::cout << *up1 << std::endl;   // 11

    std::unique_ptr<int> up3 = std::move(up1);    // ����p3�����ݵ�Ψһ��unique_ptr

    std::cout << *up3 << std::endl;   // 11
    //std::cout << *up1 << std::endl;   // err, ����ʱ����
    up3.reset();            // ��ʽ�ͷ��ڴ�
    up1.reset();            // ���ᵼ������ʱ����
    //std::cout << *up3 << std::endl;   // err, ����ʱ����

    std::unique_ptr<int> up4(new int(22));   // �޷����Ƶ�unique_ptr
    up4.reset(new int(44)); //"��"��̬����
    std::cout << *up4 << std::endl; // 44

    up4 = nullptr;//��ʽ������ָ����ͬʱ����ָ���Ϊ��ָ�롣��up4.reset()�ȼ�

    std::unique_ptr<int> up5(new int(55));
    int* p = up5.release(); //ֻ���ͷſ���Ȩ�������ͷ��ڴ�
    std::cout << *p << std::endl;
    //cout << *up5 << endl; // err, ����ʱ����
    delete p; //�ͷŶ�����Դ
}
