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

	int getGraph(const string &fileName);

	const vector<int> &getDivGraph(const string &frameName);

private:
	int createGraph(const string &fileName);

	void createDivGraph(const string &fileName, const string &frameName,
						int rows, int cols, int w, int h, int from, int to);
};

#endif // _UTILGRAPH_H_