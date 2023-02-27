//https://zhuanlan.zhihu.com/p/358732734

#include "CHCV.h"
#include "CHTime.h"
#include <iostream>
#include <thread>
#include "CHClock.h"

//String img_path = "../res/test.jpg";
std::string img_path = "../res/1.png";
std::string winName = "OpenCV";

//ͼ���ȡ����ʾ
void test();
//ͼ��,mat ����
void test2();
//play video
void test3();

//cv time
void testTime();

//���߳���Ⱦ
void case0();


int main(int argc, char** argv) {
	std::cout << "start!\n";

	//while (1) {
	//	printf("%lld\n", chtime.getTImeMicros());
	//	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//}

	//testTime();

	//std::thread([] { test2(); }).detach();
	//case0();
	//test();
	//test2();
	//test3();

	CHClock ch_clock;
	ch_clock.test();
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	std::cout << "end!\n";
	return 0;
}

void testTime() {
	CHTime chtime;
	chtime.pt("start ");
	//cv::Mat img(cv::Size(4096, 3000), CV_8UC3, cv::Scalar(255, 0, 0)); //���ݱ仯��
	cv::Mat img(cv::Size(4096, 3000), CV_8UC3); //���ݱ仯��
	chtime.pt("1 ");
	cv::putText(img, chtime.gt(), cv::Point(100, 100), cv::FONT_HERSHEY_DUPLEX, 2.0, cv::Scalar(0, 0, 255), 2); //���ݱ仯��
	chtime.pt("2 ");
	img.setTo(cv::Scalar(0, 255, 0)); //���ݱ仯�� 10ms
	chtime.pt("3 ");
	img.setTo(cv::Scalar(0, 0, 255));
	chtime.pt("4 ");
	img.setTo(cv::Scalar(0, 0, 255));
	chtime.pt("5 ");
	img.setTo(cv::Scalar(255, 0, 0));
	chtime.pt("6 ");
	cv::imshow("img", img); //��ʾ35ms
	chtime.pt("end");
	cv::imshow("img", img);
	chtime.pt("end");
	cv::imshow("img", img);
	chtime.pt("end");
	cv::imshow("img", img);
	chtime.pt("end");
	cv::waitKey(5000);
};

void test3() {
	// init video capture with video 
	cv::VideoCapture capture("D:/data/ws/cpp/ConsoleApplication/res/in.mkv");
	if (!capture.isOpened())
	{
		// error in opening the video file 
		std::cout << "Unable to open file!" << std::endl;
		return;
	}

	// get default video FPS 
	double fps = capture.get(cv::CAP_PROP_FPS);

	// get total number of video frames 
	int num_frames = int(capture.get(cv::CAP_PROP_FRAME_COUNT));
	//std::cout << fps;
	std::cout << num_frames;

	cv::Mat frame;
	while (true)
	{
		capture >> frame;
		if (frame.empty()) {
			std::cout << "get frame error.\n";
			return;
		}
		imshow("play video", frame);
		cv::waitKey(30); //30ms
	}

}

void test2() {

	//cv::Mat img = cv::imread("D:/workspace/cpp/cvcuda/res/test.jpg", cv::IMREAD_GRAYSCALE);
	//cv::Mat img = cv::imread("D:/workspace/cpp/cvcuda/res/test.jpg", cv::IMREAD_COLOR);
	cv::Mat img(cv::Size(480, 360), CV_8UC3, cv::Scalar(255, 0, 0));
	//cv::Mat img(cv::Size(4096, 3000), CV_8UC3, cv::Scalar(255, 0, 0));

	//cv::cuda::GpuMat dst, src;
	//src.upload(img);

	//cv::Ptr<cv::cuda::CLAHE> ptr_clahe = cv::cuda::createCLAHE(5.0, cv::Size(8, 8));
	//ptr_clahe->apply(src, dst);

	//cv::Mat result;
	//dst.download(result);
	//cv::imshow("result", result);


	CHTime chtime;
	while (1)
	{

		cv::imshow("img", img);
		//img.release();

		////mat���浽�ļ�
		//cv::FileStorage storage("test.txt", cv::FileStorage::WRITE);
		//storage << "img" << img;
		//storage.release();

		////���ļ��ж�ȡmat
		//cv::FileStorage storage("test.txt", cv::FileStorage::READ);
		//storage["img"] >> img;
		//storage.release();

		////���浽ָ����ʽͼƬ
		//cv::imwrite("img.png", img);
		//break;

		cv::waitKey(33);
	}
}

void test() {
	using namespace cv;
	//Mat src = imread(img_path, IMREAD_GRAYSCALE); //���ɻҶ�ͼ
	Mat src = imread(img_path);
	if (src.empty())
	{
		std::cout << "Did not find the image" << std::endl;
		return;
	}
	namedWindow(winName, WINDOW_KEEPRATIO);
	//namedWindow("hello", WINDOW_NORMAL);
	//namedWindow("hello", WINDOW_AUTOSIZE);
	//namedWindow("hello", WINDOW_FREERATIO);
	//namedWindow("hello", WINDOW_GUI_NORMAL);

	resizeWindow(winName, 400, 300);
	moveWindow(winName, 200, 100);

	//imshow(winName, src);

	CHCV chcv(src, winName);
	chcv.f_paint();
	//chcv.change();
	//chcv.f_mat();
	//chcv.f_camera();
	//chcv.f_histogram();
	//chcv.f_histogram3();
	//chcv.f_count();
	//chcv.f_koutu();
	//chcv.f_work();
}

#include "CHCreate.h"
#include "CHShow.h"

void case0() {
	std::atomic_bool runFlag = true;
	std::mutex mtx;
	std::condition_variable cvar;
	std::deque<FrameCache> frameCaches;

	CHCreate ch_create;
	CHShow ch_show;
	ch_create.run(runFlag, frameCaches, mtx, cvar);
	ch_show.run(runFlag, frameCaches, mtx, cvar);
	ch_create.detach();
	ch_show.detach();

	std::this_thread::sleep_for(std::chrono::milliseconds(50000));
	runFlag = false;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}