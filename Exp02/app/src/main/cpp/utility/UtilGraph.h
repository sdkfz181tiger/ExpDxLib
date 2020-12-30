#ifndef _UTILGRAPH_H_
#define _UTILGRAPH_H_

#include "Utility.h"

class UtilGraph {

private:
	map<string, int> graphMap;

public:
	UtilGraph();

	~UtilGraph();

	static UtilGraph *getInstance();

	void destroyInstance();

	bool init();

	int createGraph(const string &fileName);
};

#endif // _UTILGRAPH_H_