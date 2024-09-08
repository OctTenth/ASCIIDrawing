#pragma once

#include "Converter.hpp"

class Arg {
public:
	Arg() : inputPath(""), outputPath(""),
		  showHeight(30), showWidth(120), fontRatio(0.55), mt(NULLTYPE),
		  isInputSet(false), isOutputSet(false) {};
	Arg(char **argv);
private:
	std::string inputPath;
	std::string outputPath;
	int showHeight = 30, showWidth = 120;
	double fontRatio = 0.55;
	MediaType mt;
	struct {
		bool isInputSet  : 1;
		bool isOutputSet : 1;
	};
};