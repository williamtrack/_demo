#include "CHShow.h"
#include "CHtime.h"

void CHShow::run(std::atomic_bool& runFlag, std::deque<FrameCache>& frameCaches, std::mutex& mtx, std::condition_variable& cvar)
{
	m_thread = std::thread([&]() {
		CHTime chtime;
		for (int iter = 0; runFlag; iter++) {
			//std::cout << frameCaches.size() << std::endl;
			std::unique_lock<std::mutex> lock(mtx);
			//�������ȴ�create�̻߳���cvar
			while (frameCaches.empty()) {
				if (cvar.wait_for(lock, std::chrono::seconds(5)) == std::cv_status::timeout) {
					if (!runFlag) {
						std::cout << "timeout, quit.\n";
						break;
					}
					else {
						std::cout << "timeout, continue.\n";
						continue;
					}
				}
			}

			//ȡ����������ջ
			FrameCache frameCache = frameCaches.front();
			frameCaches.pop_front();
			lock.unlock();

			for (int view = 0; view < 1; view++) {
				//main�̲߳�Ҫȥ��cv::waitKey()����ᵼ�������̵߳�cv����ִ��
				cv::imshow("img", frameCache.imgs[view]);
				std::cout << "show ===\n";
			}
			cv::waitKey(1); //������Sleep(),������; ������waitKey()���ȴ�cv::imshow�������
		}
		cv::destroyAllWindows();
		std::cout << "show loop end.\n";
		}
	);
}
