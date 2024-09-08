#include "Converter.hpp"

const std::array<char, 18> charaters = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'a',  'P', 'a'};
		/*{' ', '`', '.', '~', '^', '=', '?', '/', '(', '{', 'C', 'X', 'E', '0', '$', '#', 'W', '@'}*/
		 /*" `._~^=?/({CXE0$#W@"*/

cv::Size subwindowResize_kr(const cv::Size parent, const double sWHRatio) {
	const double pWHRatio = (double)parent.width / parent.height;

	if (pWHRatio > sWHRatio)
		return cv::Size(parent.height * sWHRatio, parent.height);
	else
		return cv::Size(parent.width, parent.width / sWHRatio);
}

Converter::Converter(MediaType mt, std::string path, int showHeight, int showWidth, double fontRatio)
	: mediaType(mt), showHeight(showHeight), showWidth(showWidth), fontRatio(fontRatio)
{
	if (mt == PICTURE) {
		video.~VideoCapture();
		pic = cv::imread(path, cv::IMREAD_GRAYSCALE);
		if (pic.data == nullptr) {
			std::cout << "[����] �޷���ͼƬ" << std::endl;
			std::exit(-1);
		}
		cv::Size sz(subwindowResize_kr(cv::Size(showWidth, showHeight), (double)pic.cols / pic.rows));
		(sz.width / fontRatio > showWidth) ? sz.height *= fontRatio : sz.width /= fontRatio;
		cv::resize(pic, pic, sz);
	}
	else {
		pic.~Mat();
		video = cv::VideoCapture(path);
		if (!video.isOpened()) {
			std::cout << "[����] �޷�����Ƶ" << std::endl;
			std::exit(-1);
		}
	}
}

Converter::Converter(cv::Mat matpic, int sh, int sw, double fr)
	: mediaType(PICTURE), showHeight(sh), showWidth(sw), fontRatio(fr)
{
	pic = matpic;
	cv::Size sz(subwindowResize_kr(cv::Size(showWidth, showHeight), (double)pic.cols / pic.rows));
	(sz.width / fontRatio > sw) ? sz.height *= fr : sz.width /= fr;
	cv::resize(pic, pic, sz);
}

void Converter::writeToStream(std::ostream &os) {
	std::string output;

	if (mediaType == PICTURE) {
		for (int row = 0; row < pic.rows; row++) {
			for (int col = 0; col < pic.cols; col++) {
				output.push_back(charaters[17 - static_cast<int>(pic.at<unsigned char>(row, col) / 255.0 * 17)]);
			}
			output.push_back('\n');
		}
		os << output;
	}

}

void Converter::writeToFile(std::ofstream &os) {
	if (mediaType == PICTURE)
		writeToStream(os);
	else {
		std::cout << "[����] ��Ƶ�ݲ�֧��д���ļ�" << std::endl;
	}
}

void Converter::showOnTerminal(std::ostream &os) {
	if (mediaType == PICTURE)
		writeToStream(os);
	else {
		cv::Mat frame;
		int fps = video.get(cv::CAP_PROP_FPS);
		while (true) {
			video >> frame;

			if (frame.data == nullptr)
				break;

			cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
			Converter frameconv(frame, showHeight, showWidth, fontRatio);
			frameconv.writeToStream(os);
			//Sleep(1000.0 / fps / 10);
		}
	}
}
