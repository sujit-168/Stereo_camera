﻿#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture Camera(2);
    if (!Camera.isOpened())
    {
        cout << "Could not open the Camera " << endl;
        return -1;
    }
    Mat Fream;
    Camera >> Fream;
    //imshow("【双目视图】",Fream);
    Mat DoubleImage;
    system("/home/sujie/Stereo_cam/Camera_switch/camera_switch.sh");  //此处改成你的脚本存放绝对路径
    imshow("【双目视图】",Fream);
    while (true)
    {
        Camera >> Fream;
        if (Fream.empty()) break;
        resize(Fream, DoubleImage, Size(640, 240), (0, 0), (0, 0), INTER_AREA);
        imshow("【双目视图】", DoubleImage);
        Mat	LeftImage = DoubleImage(Rect(0, 0, 320, 240));
        Mat RightImage = DoubleImage(Rect(320, 0, 320, 240));

        imshow("【左视图】", LeftImage);
        imshow("【右视图】", RightImage);
        char key = waitKey(30);

        char c = cvWaitKey(30);
        if (c == 27)//Esc键退出
        {
            break;
        }
    }
    return 0;
}
