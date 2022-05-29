#include "Utils.h"

namespace CSV {

	icsvStream* csvOpenRead(const string fileName) {
		icsvStream* stream = new ifstream(fileName, ifstream::in);

		return stream;
	}

	string csvReadLine(icsvStream* stream) {
		if(!stream->is_open()) { return ""; }

		string tmp, line = "";

		if(stream->operator>>(tmp)) {
			getline(stream, line);
		}

		return line;

	}

}