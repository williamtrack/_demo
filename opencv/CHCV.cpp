#include "CHCV.h"
#include "arithmetic.h"

using namespace cv;
CHCV::CHCV(cv::Mat& src, std::string windows)
{
	this->src = src;
	this->winName = windows;
}

void CHCV::f_change()
{
	Mat gray, hsv;
	cvtColor(src, hsv, COLOR_BGR2HSV);
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("HSV", hsv);
	imshow("�Ҷ�", gray);
	//imwrite("./hsv.png", hsv);
	//imwrite("./gray.png", gray);
}

void CHCV::f_paint()
{
	Point start = Point(10, 100);
	Point end = Point(20, 200);
	line(src, start, end, Scalar(0, 0, 255));
	rectangle(src, Point(0, 0), Point(50, 25), Scalar(0, 0, 255), 5, LINE_4, 0); //����->����
	imshow("", src);
}

void CHCV::f_mat()
{
	//=====����=====
	//Ĭ�Ϲ��캯����ֵ���캯��
	cv::Mat img; //Ĭ�Ϲ��캯��

	//ֵ���캯��1
	cv::Mat img1(480, 640, CV_8UC3); //ͼ��ߣ��У�480-row�����У�640-col�� �������ͣ�CV_8UC3

	//ֵ���캯��2
	//cv::Scalar(B, G, R)���Ա�ʾ��ͨ����ɫ��������ʾΪ����ɫ
	cv::Mat img2(480, 640, CV_8UC3, cv::Scalar(255, 0, 0));

	//ֵ���캯��3
	//Ч��������һ��
	cv::Size sz3(480, 640);
	cv::Mat img3(sz3, CV_8UC3, cv::Scalar(255, 0, 0));

	//�������캯��1---�����Ծ�̬���ô��ݲ�����const &��
	cv::Mat img4(img3);

	//�������캯��2---ֻ��������Ȥ������----��Rect������
	//rect���Ͻǣ�100��100������߾�Ϊ200����x,y,width,height)
	cv::Rect rect(100, 100, 200, 200);
	cv::Mat img5(img3, rect);

	//�������캯��3--��ָ�����й���
	//��img3�п���0-239���Լ�0-319�е�img6
	cv::Range rows(0, 240);
	cv::Range cols(0, 320);
	cv::Mat img6(img3, rows, cols);

	//��̬���캯��
	cv::Mat img7 = cv::Mat::zeros(480, 640, CV_8UC3); //480��640�У�ֵȫΪ������顣
	cv::Mat img8 = cv::Mat::ones(480, 640, CV_64FC1); //ȫ1����
	cv::Mat img9 = cv::Mat::eye(480, 640, CV_16SC2); //��λ����

	//��ֵ
	img9.setTo(Scalar(255, 0, 0));

	//=====����Ԫ��======
	//ʹ��ʾ��

	//ֱ�ӷ���---ģ�庯��at<>()
	//��ͨ��, ����������������������¿�ͷ���ܵ����Ͷ�Ӧ��ϵ����
	cv::Mat img10 = cv::Mat::ones(100, 100, CV_32FC1);
	img10.at<float>(10, 10) = 100.0;
	float elemf = img10.at<float>(10, 10); //��ֵ
	printf("%f", elemf);

	//��ͨ��---Vec3b����̶�������
	//ע������֮��Ķ�Ӧ���̶�������Mat�Ĵ�����ĸ��һ�����
	cv::Mat img11(500, 500, CV_8UC3, cv::Scalar(255, 255, 0));
	Vec3b elem = img11.at<Vec3b>(10, 10);
	uchar elem_B = elem[0]; //��ɫͨ����ֵ---255

	Vec3b temp;
	for (int i = 0; i < img11.rows; ++i)
	{
		for (int j = 0; j < img11.cols; ++j)
		{
			temp = rainbow(img11.cols, j);
			//temp[0] = rand() % 255;
			//temp[1] = rand() % 255;
			//temp[2] = rand() % 255;
			img11.at<Vec3b>(i, j) = temp;
		}
	}
	imshow(winName, img11);

	//=======���ú���=====
	//��¡����
	cv::Mat img12(480, 640, CV_64FC3);
	cv::Mat img13 = img.clone();

	//����Ԫ��ֵ
	img13.setTo(cv::Scalar(1.0, 2.0, 3.0));

	//����ͨ����Ŀ
	size_t num_c = img13.channels();

	//���������С
	cv::Size sz = img13.size();

	//���������Ƿ�Ϊ��,Ϊ�շ���true
	bool e = img13.empty();

}

int CHCV::f_camera()
{
	VideoCapture capture;
	capture.open(0);  //����Ĭ������ͷ
	//VideoCapture cap(0);
	if (!capture.isOpened()) {
		std::cout << "video not opeSn.\n";
		return -1;
	}

	Mat frame;
	while (true)
	{
		capture >> frame;
		if (frame.empty()) {
			std::cout << "get frame error.\n";
			return -1;
		}
		imshow("��������ͷ", frame);
		waitKey(30); //30ms
	}
	return 0;

	////������ͼ��ÿһ�����أ������ BGR ֵ
	//for (int i = 0; i < frame.rows; i++) {
	//	for (int j = 0; j < frame.cols; j++) {
	//		Vec3b bgr = frame.at<Vec3b>(i, j);
	//		printf("b = %d, g = %d, r = %d\n", bgr[0], bgr[1], bgr[2]);
	//	}
	//}

}

int CHCV::f_histogram()
{
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	//������ȡֱ��ͼ����ر���
	Mat hist;  //���ڴ��ֱ��ͼ������
	const int channels[1] = { 0 };  //ͨ������
	float inRanges[2] = { 0,255 };
	const float* ranges[1] = { inRanges };  //���ػҶ�ֵ��Χ
	const int bins[1] = { 256 };  //ֱ��ͼ��ά�ȣ���ʵ�������ػҶ�ֵ�����ֵ
	calcHist(&gray, 1, channels, Mat(), hist, 1, bins, ranges);  //����ͼ��ֱ��ͼ

	//׼������ֱ��ͼ
	int width = 2;
	int hist_w = 512;
	int hist_h = 500;
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat()); //��һ��

	printf("%d~%d\n", hist.cols, hist.rows);
	for (int i = 0; i <= hist.rows; i++)
	{
		//printf("%d\n", cvRound(hist.at<float>(i - 1)));
		rectangle(histImage, Point(width * i, hist_h - 1),
			Point(width * i + 1, hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 255, 255), -1);
	}
	imshow(winName, histImage);
	//imshow("gray", gray);
	return 0;
}

int CHCV::f_histogram3()
{
	Mat dst;
	if (src.empty())
	{
		std::cout << "Did not find the image" << std::endl;
		return -1;
	}

	/// �ָ��3����ͨ��ͼ�� ( R, G �� B )
	std::vector<Mat> rgb_planes;
	split(src, rgb_planes);

	/// �趨bin��Ŀ
	int histSize = 256;

	/// �趨ȡֵ��Χ ( R,G,B) )
	float range[] = { 0, 255 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	/// ����ֱ��ͼ:
	calcHist(&rgb_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgb_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// ����ֱ��ͼ����
	int hist_w = 600; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));

	/// ��ֱ��ͼ��һ������Χ [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// ��ֱ��ͼ�����ϻ���ֱ��ͼ
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	/// ��ʾֱ��ͼ
	namedWindow("calcHist Demo", WINDOW_FREERATIO);
	imshow("calcHist Demo", histImage);
	return 0;
}

int CHCV::f_count()
{
	printf("%d~%d\n", src.cols, src.rows);

	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	resize(gray, gray, Size(500, 500)); //����ֱ���
	imshow(winName, gray);
	printf("type: %d\n", gray.type()); //mat����
	printf("%d~%d\n", gray.cols, gray.rows);

	clock_t start = clock();      //��ȡ��ǰϵͳʱ��
	//ͳ��
	int num = 0;
	for (int i = 0; i < gray.rows; i++) {
		for (int j = 0; j < gray.cols; j++) {
			if (0 <= gray.at<uchar>(i, j) && gray.at<uchar>(i, j) <= 10)num++;
		}
	}
	printf("num: %d\n", num);


	//mask
	Mat mask;
	//���涨�����ڵ�ֵ��Ϊ255������ʹ��Scalar()����ֵ
	inRange(gray, Scalar(0, 0, 0), Scalar(10, 0, 0), mask); //maskΪ��ֵͼ 0/255��CV_8UC
	printf("num: %f\n", sum(mask)[0] / 255/ gray.rows/ gray.cols); //��ͺ���
	namedWindow("mask", WINDOW_AUTOSIZE);
	imshow("mask", mask);

	//�����Сֵ
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	minMaxLoc(gray, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	printf("min: %.2f, max: %.2f \n", minVal, maxVal);
	printf("min loc: (%d, %d) \n", minLoc.x, minLoc.y);
	printf("max loc: (%d, %d)\n", maxLoc.x, maxLoc.y);

	//��ֵ�ͷ���
	Mat means, stddev;
	meanStdDev(src, means, stddev);
	printf("blue channel->> mean: %.2f, stddev: %.2f\n", means.at<double>(0, 0), stddev.at<double>(0, 0));
	printf("green channel->> mean: %.2f, stddev: %.2f\n", means.at<double>(1, 0), stddev.at<double>(1, 0));
	printf("red channel->> mean: %.2f, stddev: %.2f\n", means.at<double>(2, 0), stddev.at<double>(2, 0));
	clock_t end = clock();
	double programTimes = ((double)end - start) / CLOCKS_PER_SEC;
	printf("time: %f\n", programTimes);

	return 0;
}

int CHCV::f_koutu()
{
	resize(src, src, Size(400, 300));
	Mat image_hsv;
	cvtColor(src, image_hsv, COLOR_BGR2HSV);
	namedWindow("image_hsv", WINDOW_AUTOSIZE);
	moveWindow("image_hsv", 400, 200);
	imshow("image_hsv", image_hsv);
	Mat mask;
	//���涨�����ڵ�ֵ��Ϊ255������ʹ��Scalar()����ֵ
	inRange(image_hsv, Scalar(35, 43, 46), Scalar(99, 255, 255), mask);
	//maskΪ��ֵͼ��CV_8UC
	namedWindow("mask", WINDOW_AUTOSIZE);
	moveWindow("mask", 400, 200);
	imshow("mask", mask);
	Mat output;
	bitwise_and(src, src, output, mask); //and����
	namedWindow("output", WINDOW_AUTOSIZE);
	moveWindow("output", 400, 200);
	imshow("output", output);
	return 0;
}

int CHCV::f_work()
{
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	resize(gray, gray, Size(500, 500)); //����ֱ���
	imshow("gray", gray);
	printf("type: %d\n", gray.type()); //mat����
	printf("%d~%d\n", gray.cols, gray.rows);

	//mask
	Mat mask;
	//���涨�����ڵ�ֵ��Ϊ255������ʹ��Scalar()����ֵ
	inRange(gray, Scalar(200, 0, 0), Scalar(256, 0, 0), mask); //maskΪ��ֵͼ 0/255��CV_8UC
	printf("num: %f\n", sum(mask)[0] / 255 / gray.rows / gray.cols); //��ͺ���
	namedWindow("mask", WINDOW_AUTOSIZE);
	imshow("mask", mask);


	//������ȡֱ��ͼ����ر���
	Mat hist;  //���ڴ��ֱ��ͼ������
	const int channels[1] = { 0 };  //ͨ������
	float inRanges[2] = { 0,255 };
	const float* ranges[1] = { inRanges };  //���ػҶ�ֵ��Χ
	const int bins[1] = { 256 };  //ֱ��ͼ��ά�ȣ���ʵ�������ػҶ�ֵ�����ֵ
	calcHist(&gray, 1, channels, Mat(), hist, 1, bins, ranges);  //����ͼ��ֱ��ͼ

	//׼������ֱ��ͼ
	int width = 2;
	int hist_w = 512;
	int hist_h = 500;
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat()); //��һ��

	printf("%d~%d\n", hist.cols, hist.rows);
	for (int i = 0; i <= hist.rows; i++)
	{
		//printf("%d\n", cvRound(hist.at<float>(i - 1)));
		rectangle(histImage, Point(width * i, hist_h - 1),
			Point(width * i + 1, hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 255, 255), -1);
	}
	imshow("hist", histImage);

	return 0;
}
