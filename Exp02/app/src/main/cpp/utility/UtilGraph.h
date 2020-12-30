#ifndef _UTILGRAPH_H_
#define _UTILGRAPH_H_

#include "Utility.h"

class UtilGraph {

private:
	map<string, int> graphMap;
	map<string, vector<int>> divMap;

public:
	UtilGraph();

	~UtilGraph();

	static UtilGraph *getInstance();

	void destroyInstance();

	bool init();

	int createGraph(const string &fileName);

	const vector<int> *createDivGraph(const string &fileName, const string &animName,
									  int total, int rows, int cols, int w, int h);
};

#endif // _UTILGRAPH_H_