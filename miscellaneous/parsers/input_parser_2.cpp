const int bufferSize = 1 << 12;
class InParser {
public:
	InParser(const char* filename) {
		file = fopen(filename, "r");
		buffer = new char[bufferSize];
		index = bufferSize - 1;
	}

	template<typename T>
	InParser& operator >>(T& n) {
		static char ch;
		do {
			ch = __getchar();
		} while (ch < '0' || ch > '9');
		for (n = 0; '0' <= ch && ch <= '9'; ch = __getchar()) {
			n = 10 * n + (ch - '0');
		}
		return *this;
	}
private:
	FILE* file;
	char* buffer;
	int index = bufferSize;
	inline char __getchar() {
		if (++index == bufferSize) {
			index = 0;
			int aux = fread(buffer, 1, bufferSize, file);
			while (aux < bufferSize) {
				buffer[aux++] = ' ';
			}
		}
		return buffer[index];
	}
};
