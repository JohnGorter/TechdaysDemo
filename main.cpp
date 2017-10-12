#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* args[])
{
    VideoCapture cap("1.mp4"); 
    Mat frame, frame2, frame3, frame4, frame5;
    for(;;){
        cap >> frame >> frame2;

        if (frame2.empty()){
            cap.set(CAP_PROP_POS_FRAMES, 0);
            continue;
        }
        cvtColor(frame, frame, CV_RGB2GRAY);
        blur(frame, frame, Size(2, 2));
        cvtColor(frame2, frame2, CV_RGB2GRAY);
        blur(frame2, frame2, Size(2, 2));

        absdiff(frame, frame2, frame3); 
        threshold(frame3, frame4, 20, 255, CV_THRESH_BINARY); 
        dilate(frame4, frame5, Mat(), Point(-1, -1), 3); 

        int percent = countNonZero(frame5) * 100 / (frame.cols * frame.rows); 
        cout << percent << endl;

        ostringstream s; 
        s << percent << "%"; 

        putText(frame, s.str(), Point(20, 20), 2, 1, Scalar(255, 255, 255));

        imshow("m", frame); 
        imshow("m2", frame2); 
        imshow("m3", frame3); 
        imshow("m4", frame4); 
        imshow("m5", frame5); 
        waitKey(15); 
    }
    cap.release(); 
    destroyAllWindows(); 
}