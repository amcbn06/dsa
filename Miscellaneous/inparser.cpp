const int bufferSize = 1 << 12;
class InParser {
public:
	InParser(const char* filename) {
		file = fopen(filename, "r");
		buffer = new char[bufferSize];
		index = bufferSize - 1;
	}

	InParser& operator >>(int& n) {
		char ch;
		do {
			ch = getChar();
		} while (!isdigit(ch) && ch != '-');
		int sgn = 1;
		if (ch == '-') {
			sgn = -1;
			ch = getChar();
		}
		n = 0;
		do {
			n = 10 * n + (ch - '0');
			ch = getChar();
		} while (isdigit(ch));
		n *= sgn;
		return *this;
	}
private:
	FILE* file;
	char* buffer;
	int index = bufferSize;
	inline char getChar() {
		if (++index == bufferSize) {
			index = 0;
			int aux = fread(buffer, 1, bufferSize, file);
			while (aux < bufferSize) {
				buffer[aux++] = ' ';
			}
		}
		return buffer[index];
	}
} fin("aventura.in");
