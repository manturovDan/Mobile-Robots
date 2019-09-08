namespace MatrixR {
	struct Line {
		int elemsc; //count of elems
		int nzelems; //count of non zero elems
		int *row;
	};

	Line* inputM(int &);
	void outputM(const char *, Line *, int);
	int getNum(char *, char*, int &);
	bool evenDNum(int);
	Line *filterM(Line *, int, int &);
	int compLines(const void *, const void *);
	void sortM(Line *, int);
	//Line *erase(Line *&row, int rows);
}