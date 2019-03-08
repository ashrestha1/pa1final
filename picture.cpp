#include <iostream>
#include <fstream>
#include "picture.h"
#include "picture_pair.h"

using namespace std;

const char SPACE = ' ';

// Reads a char from ifstream
// Includes space but excludes newline
// Useful for reading character pictures
char get_ch(ifstream &in) {
	char c = '\0';
	while (in >> noskipws >> c && c == '\n')
		;

	return c;
}

Picture::Picture(const Picture& p) {

	width = p.width;
	height = p.height;

    pix = new char*[height];
	for (int row = 0; row < height; row++) {
		pix[row] = new char[width];

	}

	for (int rowInput = 0; rowInput < height; rowInput++) {

		for (int colInput = 0; colInput < width; colInput++) {

			pix[rowInput][colInput] = p.pix[rowInput][colInput];

		}
	}

}

Picture::Picture(const char* filename) {

	ifstream inFile;
	inFile.open(filename);

	inFile >> height >> width;
	pix = new char*[height];

	for (int i = 0; i < height; i++) {
		pix[i] = new char[width];
	}

	for (int rowRead = 0; rowRead < height; rowRead++) {

		for (int colRead = 0; colRead < width; colRead++) {
			pix[rowRead][colRead] = get_ch(inFile);
		}

	}

}

Picture::~Picture() {

	for (int rowRead = 0; rowRead < height; rowRead++) {

		delete[] pix[rowRead];
	}

	delete[] pix;

}
void Picture::frame(char symbol, int frame_width) {

	if (frame_width > 0) {

		height = height + (2 * frame_width);

		width = width + (2 * frame_width);

		char** pixFrame = new char*[height];

		for (int row = 0; row < height; row++) {
			pixFrame[row] = new char[width];

		}

		for (int picRow = 0; picRow < frame_width; picRow++) {

			for (int picCol = 0; picCol < width; picCol++) {
				pixFrame[picRow][picCol] = symbol;

				pixFrame[height - picRow - 1][picCol] = symbol;

			}

		}

		for (int picCol = 0; picCol < frame_width; picCol++) {

			for (int picRow = 0; picRow < height; picRow++) {
				pixFrame[picRow][picCol] = symbol;

				pixFrame[picRow][width - picCol - 1] = symbol;

			}

		}

		for (int row = frame_width; row < height - frame_width; row++) {

			for (int col = frame_width; col < width - frame_width; col++) {

				pixFrame[row][col] = pix[row - frame_width][col - frame_width];

			}
		}

		for (int rowRead = 0; rowRead < height - (2 * frame_width); rowRead++) {

			delete[] pix[rowRead];
		}

		delete[] pix;

		pix = pixFrame;

	}

	else {

		return;
	}

}

void Picture::draw() const {

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			cout << pix[row][col];
		}

		cout << endl;
	}

}

Picture::Picture(const Picture_Pair& pp) {

	if (pp.get_picture(0) == nullptr && pp.get_picture(1) == nullptr) {

		height = 0;
		width = 0;

		pix = new char*[height];

		for (int k = 0; k < height; k++) {

			pix[k] = new char[width];

		}

	}

	else if (pp.get_picture(0) == nullptr && pp.get_picture(1) != nullptr) {

		height = pp.get_picture(1)->height;
		width = pp.get_picture(1)->width;

		pix = new char*[height];

		for (int row = 0; row < height; row++) {

			pix[row] = new char[width];

		}

		for (int i = 0; i < height; i++) {

			for (int j = 0; j < width; j++) {

				pix[i][j] = pp.get_picture(1)->pix[i][j];

			}

		}

	}

	else if (pp.get_picture(1) == nullptr && pp.get_picture(0) != nullptr) {

		height = pp.get_picture(0)->height;
		width = pp.get_picture(0)->width;

		pix = new char*[height];

		for (int row = 0; row < height; row++) {

			pix[row] = new char[width];

		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {

				pix[i][j] = pp.get_picture(0)->pix[i][j];

			}

		}

	}

	else if (pp.get_picture(0) != nullptr && pp.get_picture(1) != nullptr) {

		height = pp.get_picture(0)->height;

		if (height < pp.get_picture(1)->height)
			height = pp.get_picture(1)->height;

		for (int i = 0; i < 2; i++)
			width += pp.get_picture(i)->width;

		pix = new char*[height];
		for (int row = 0; row < height; row++)

			pix[row] = new char[width];

		for (int i = 0; i < pp.get_picture(0)->height; i++) {
			for (int j = 0; j < pp.get_picture(0)->width; j++)

				pix[i][j] = pp.get_picture(0)->pix[i][j];

		}

		if (pp.get_picture(0)->height < pp.get_picture(1)->height) {
			for (int fill = height - pp.get_picture(0)->height; fill < height;
					fill++) {

				for (int fill2 = 0; fill2 < pp.get_picture(0)->width; fill2++) {

					pix[fill][fill2] = SPACE;

				}

			}
		}

		else if (pp.get_picture(1)->height < pp.get_picture(0)->height) {
			for (int fill = height - pp.get_picture(1)->height; fill < height;
					fill++) {

				for (int fill2 = pp.get_picture(1)->width; fill2 < width;
						fill2++) {

					pix[fill][fill2] = SPACE;

				}

			}
		}

		for (int next = 0; next < pp.get_picture(1)->height; next++) {
			for (int next2 = 0; next2 < pp.get_picture(1)->width; next2++) {

				pix[next][next2 + pp.get_picture(0)->width] =
						pp.get_picture(1)->pix[next][next2];

			}

		}

	}

}
