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

	Line* inputM(int &);
	void printTable(Line *);
	
}