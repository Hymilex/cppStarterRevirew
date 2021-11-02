#include <iostream>
#include <opencv2/opencv.hpp>


int main()
{
	cv::Mat src, dst;
	src = cv::imread("fengbaobao.png");
	dst = src.clone();
	//±éÀúÏñËØ
	for (int col = 0; col < dst.cols; col++)
	{
		for (int row = 0; row < dst.rows;row++)
		{
			cv::Vec3b bgr = src.at<cv::Vec3b>(row, col);
			bgr[0] = static_cast<uchar>(255 - bgr[0]);
			bgr[1] = static_cast<uchar>(255 - bgr[1]);
			bgr[2] = static_cast<uchar>(255 - bgr[2]);
			dst.at<cv::Vec3b>(row, col) = bgr;
		}
	}

	cv::imshow("src", src);
	cv::imshow("dst", dst);
	cv::waitKey();
	return 0;
}