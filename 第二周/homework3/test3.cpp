#include<iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap(0);
    if (!cap.isOpened()){
	cout << "error" << endl;
	waitKey(0);
	return 0;
    }
    int w = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_WIDTH));
    int h = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    Size videoSize(w, h);
    VideoWriter writer("RecordVideo.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25,  videoSize);
    Mat frame;
    int key;
    char startOrStop = 1;
    char flag = 0;
    while (1){
	   cap >> frame;
	   key = waitKey(100);
	   if (key == 32)
	   startOrStop = 1 - startOrStop;
	   if (startOrStop == 0){
	   flag = 1;
	}
	if (key == 27){
	   break;
	}
	if(startOrStop == 0 && flag==1){
	   writer << frame;
	   cout << "recording" << endl;
	}
	   else if (startOrStop == 1){
	   flag = 0;
	   cout << "end recording" << endl;
	}
	imshow("picture", frame);
    }
    cap.release();
    writer.release();
    destroyAllWindows();
    return 0;
}
