namespace MatrixR {
	struct nzel {
		int number;
		int position;
		nzel *next;
	};

	struct Line {
		int elemsc; //count of elems
		int nzelems; //count of non zero elems
		int number;
		nzel *row;
		Line *nextRow;
	};

	int inputM(Line *&, int &, int &);
	void printTable(Line *);
	void outputM(Line *, int, int);
	
}