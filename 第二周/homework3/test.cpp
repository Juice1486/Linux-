#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  

int main(int argc,char *argv[]){  
        cv::Mat image;  
	image=cv::imread("/home/zhangtao/Documents/homework3/1.jpg");    
        cv::namedWindow("img");  
	cv::imshow("img",image);  
	cv::waitKey();  
	return 0;  
}
