#include <iostream>
#include<opencv2/opencv.hpp>
#include <windows.h>
#include <math.h>

using namespace cv;
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int xx1, yy1, xx2, yy2;

void on_mouse(int event, int x, int y, int flags, void* img)
{
	static int count = 0;
    if (event == CV_EVENT_LBUTTONDOWN)
    {
		printf("(%d, %d)\n", x, y);
		if (count == 0) {
			xx1 = x;
			yy1 = y;
			count++;
		} else {
			xx2 = x;
			yy2 = y;
			float distance = sqrt((xx1 - xx2) * (xx1 - xx2) + (yy1 - yy2) * (yy1 - yy2)) * 2.2;
			printf("%f\n", distance);
			count = 0;
			char cmd[100] = {0};
			sprintf(cmd, "adb shell input swipe 320 410 320 410 %d", int(distance));
			system(cmd);
			Sleep(1000);
			system("adb shell screencap -p /sdcard/1.png");
			system("adb pull /sdcard/1.png .");
			IplImage *img2 = cvLoadImage("1.png", 1);
			IplImage *desc;
			CvSize sz;
			sz.width = 720;
			sz.height = 1280;
			desc = cvCreateImage(sz, img2->depth, img2->nChannels);
			cvResize(img2, desc, CV_INTER_CUBIC);
			cvShowImage("src", desc);
		}
    }
}

int main(int argc, char** argv) {
	cvNamedWindow("src", 1);
	system("adb shell screencap -p /sdcard/1.png");
	system("adb pull /sdcard/1.png .");
	IplImage *img = cvLoadImage("1.png", 1);
	IplImage *desc;
	CvSize sz;
	sz.width = 720;
	sz.height = 1280;
	desc = cvCreateImage(sz, img->depth, img->nChannels);
	cvResize(img, desc, CV_INTER_CUBIC);
	cvSetMouseCallback("src", on_mouse, desc);
	cvShowImage("src", desc);
	waitKey(0);
	return 0;
}
