#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <opencv2\opencv.hpp>
#include <Windows.h>

enum MediaType {
	NULLTYPE = 0,
	PICTURE,
	VIDEO
};


class Converter {
public:
	Converter() = default;
	Converter(MediaType mt, std::string path, int showHeight = 30, int showWidth = 120, double fontRatio = 0.55);
	void writeToFile(std::ofstream &os);
	void writeToFile(std::string dir);
	void showOnTerminal(std::ostream &os = std::ref(std::cout));
	~Converter() { mediaType == PICTURE ? pic.~Mat() : video.~VideoCapture(); };
private:
	MediaType mediaType;
	cv::Mat pic;
	cv::VideoCapture video;
	int showHeight, showWidth;
	double fontRatio = 0.55;
	Converter(cv::Mat matpic, int sh, int sw, double fr);
	void writeToStream(std::ostream &os);
};
