#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <iostream>
#include <fstream>

namespace CSV {

	using namespace std;

	using icsvStream=ifstream;

	icsvStream* csvOpenRead(const string fileName);

	string csvReadLine(icsvStream* stream);

}

#endif