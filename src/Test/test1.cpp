#if 1//运行前改成1
#include<opencv2/opencv.hpp>
#include<stdlib.h>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	cap.open(0); //打开摄像头,笔记本自带有一个摄像头，但设备号为1，更改为0即可打开双目摄像头，默认情况电脑自带摄像头索引为0，外置为1.2.3，所以有点奇怪
	//cap.open("http://192.168.1.100:8080/?action=stream?dummy=param.mjpg");
	if (!cap.isOpened())//如果视频不能正常打开则返回
		return -1;
	cvWaitKey(30);
	Mat frame;//用于保存每一帧图像
	cap >> frame;
	imshow("【双目原始视图】", frame);
	cvWaitKey(300);
	//system("C:\\\"Program Files (x86)\"\\\"CHUSEI 3D Webcam\"\\\"CHUSEI 3D Webcam.exe\"");

	char buf[30] = { 0 }; //保存路径变量

	while (1)
	{
		cap >> frame;          //等价于cap.read(frame);
		if (frame.empty())     //如果某帧为空则退出循环
			break;

		imshow("【双目原始视图】", frame);    //显示双目原始图像  原始分辨率为 640*480

		Mat DoubleImage;

		resize(frame, DoubleImage, Size(640, 240), (0, 0), (0, 0), INTER_AREA);   // 纵向分辨率缩小一半
		imshow("【双目缩小视图】", DoubleImage);  //显示图像


		Mat	LeftImage = DoubleImage(Rect(0, 0, 320, 240));      //分割得到左视图
		Mat RightImage = DoubleImage(Rect(320, 0, 320, 240));   //分割得到右视图

		imshow("【左视图】", LeftImage);         //显示左视图
		imshow("【右视图】", RightImage);        //显示右视图

		char c = cvWaitKey(30);
		if (c == 27)//Esc键退出
		{
			break;
		}

		static int i = 9;
		if (13 == char(c))
		{
			sprintf(buf, ".\\picture\\left_%d.png", i);  //保存左视图
			cout << buf;
			imwrite(buf, LeftImage);



			sprintf(buf, ".\\picture\\right_%d.png", i);  //保存右视图
			imwrite(buf, RightImage);



			sprintf(buf, ".\\picture\\total_%d.png", i);  //保存整体图像
			imwrite(buf, DoubleImage);
			i++;
		}

	}
	cap.release();//释放资源
}


#endif