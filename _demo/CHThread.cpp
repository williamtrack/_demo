#include "CHThread.h"

#include <future>

int CHThread::cnt = 20;
std::mutex CHThread::mtx;
using namespace std;

std::condition_variable condition;


//set_value ֻ�ܱ�����һ��
void Thread_Fun1(std::promise<int>& p)
{
	//Sleep(3000);
	std::this_thread::sleep_for(std::chrono::seconds(3)); //�߳�����3s
	int iVal = 123;
	std::cout << "��������(int)��" << iVal << std::endl;
	//��������iVal
	p.set_value(iVal); //�þ�˵������ʱ������join
}

void Thread_Fun2(std::future<int>& f)
{
	//����������ֱ���յ��������std::promise�����������
	auto iVal = f.get();		//iVal = 233

	std::cout << "�յ�����(int)��" << iVal << std::endl;
}

void Thread_Fun4(promise<int>& p) {
	std::this_thread::sleep_for(std::chrono::seconds(2)); //�߳�����
	int iVal = 233;
	p.set_value(iVal); //�þ�˵������ʱ������join
}

void Thread_Fun3()
{
	promise<int> pr1;
	future<int> fu1 = pr1.get_future();
	thread t_temp(Thread_Fun4, ref(pr1));
	cout << "�յ�����(int)��" << fu1.get() << endl; //��getʱ����Ҫ��ǰ���ú�thread4
	t_temp.join();

	////��������iVal
	//p.set_value(iVal); //�þ�˵������ʱ������join
}



void CHThread::test()
{
	std::cout << "main pid: " << std::this_thread::get_id() << std::endl;
	//// === join&detach //��������
	//std::thread th1(t1);
	//std::thread th2(t2);
	//printf("%u\n", th1.get_id());
	//printf("%u\n", th2.get_id());
	//th1.join(); //����
	//th2.join(); //����
	//th2.detach(); //����

	//// === lockGuard //������
	//std::thread th3(t3);
	//std::thread th4(t4);
	//th3.detach();
	//th4.detach();

	//// === promise&future //ͬ����
	//std::promise<int> pr1;
	////����һ��std::future����fu1����ͨ��std::promise��get_future()������pr1��
	//std::future<int> fu1 = pr1.get_future();
	////����һ���߳�t1��������Thread_Fun1������pr1�����߳�����ִ��
	//std::thread t1(Thread_Fun1, std::ref(pr1));
	////����һ���߳�t2��������Thread_Fun2������fu1�����߳�����ִ��
	//std::thread t2(Thread_Fun2, std::ref(fu1));
	////�������߳̽���
	//t1.join(); 
	//t2.detach();

	//// ===ͬ����
	//thread t1(Thread_Fun3);
	//t1.detach();


	// ===wait_for
	std::atomic_bool runFlag = true;
	bool wakeFlag = false;

	std::thread([&]() {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		wakeFlag = true;
		//condition.notify_one();
		condition.notify_all();
		}).detach();

		std::unique_lock<std::mutex> lck(mtx);
		while (runFlag) {
			//�жϳ�ʱ, ����1
			//�����;�˳��򷵻�true; ����ﵽʱ����򷵻�false,
			if (!condition.wait_until(lck, std::chrono::system_clock::now() += std::chrono::seconds(5), [&] {
				if (wakeFlag) {
					std::cout << "wake\n";
					return true;
				}
				return false;
				}
			))
				std::cout << "out of time.\n";

			////����2
			////���һ��������Ԥ������������wait_for��ʱ��
			////���Ⱦͻ��ж������������������������false����ô������ȴ�
			////����ڳ�ʱ֮ǰ���յ���һ��notify, ��ô�����ٴ�ִ�����Ԥ�������������ж�
			////��ʱ��ʱ����ִ��������������������Ͳ����ٽ��еȴ�, ����notify�˴���ִ��3��
			//bool out = false;
			//condition.wait_for(lck, std::chrono::seconds(5), [&] {
			//	std::cout << "condition" << std::endl;
			//	if (wakeFlag) {
			//		std::cout << "wake\n";
			//		out = false;
			//		return true;
			//	}
			//	else {
			//		out = true;
			//		return false;
			//	}
			//	}
			//);
			//if (out) {
			//	std::cout << "out of time\n";
			//	break;
			//}

			////����3, �и��ʼٻ���, �������ڳ�ʱ�ж�? ֻ�������̵߳ȴ�����
			//if (condition.wait_for(lck, std::chrono::seconds(4)) == std::cv_status::timeout) {
			//	std::cout << "timeout.\n"; //�и��ʼٻ���,����no_timeout
			//	break;
			//}

			wakeFlag = false;
			//runFlag = false;

		}
		std::cout << "end\n";
}



void CHThread::t1()
{
	for (int i = 0; i < 10; ++i) {
		printf("t1 tread\n");
		Sleep(100);
	}
	std::cout << std::this_thread::get_id() << std::endl;
}

void CHThread::t2()
{
	for (int i = 0; i < 10; ++i) {
		printf("t2 tread\n");
		Sleep(100);
	}
	std::cout << std::this_thread::get_id() << std::endl;
}



//lock_guard��������;����, ֻ��ͨ������ʱ����

void CHThread::t3()
{
	while (cnt > 0)
	{
		//std::lock_guard<std::mutex> lk(mtx);
		//mtx.lock();
		std::unique_lock<std::mutex> lock(mtx);
		if (cnt > 0)
		{
			//sleep(1);
			--cnt;
			printf("t3: ");
			std::cout << cnt << std::endl;
		}
		if (cnt < 12) {
			lock.unlock();
			std::cout << "unlock\n ";
		}
		//mtx.unlock();
	}
}
void CHThread::t4()
{
	while (cnt > 0)
	{
		//std::lock_guard<std::mutex> lk(mtx);
		//m.lock();
		std::unique_lock<std::mutex> lock(mtx);
		if (cnt > 3)
		{
			--cnt;
			printf("t4: ");
			std::cout << cnt << std::endl;
		}
		lock.unlock();
		//m.unlock();
	}

	//// Thread gubbins
	//std::mutex _mutex;
	//std::condition_variable _fullBuf;
	//std::condition_variable _empty;
	//std::unique_lock<std::mutex> lock(_mutex);
	//_fullBuf.wait(lock);
}
