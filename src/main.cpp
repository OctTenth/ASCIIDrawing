#include "Converter.hpp"

int main(int argc, char **argv) {
	std::ofstream file(".\\MonaLisa.txt");

	Converter conv(MediaType::PICTURE, argv[1], 450, 800, std::atof(argv[2]));
	// conv.showOnTerminal();

	conv.writeToFile(file);
}