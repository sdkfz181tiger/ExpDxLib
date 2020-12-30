#include "UtilGraph.h"

// Singleton Object
static UtilGraph *selfUtilGraph = nullptr;

UtilGraph::UtilGraph() {
	LOGD("Util", "UtilGraph()\n");
}

UtilGraph::~UtilGraph() {
	LOGD("Util", "~UtilGraph()\n");
}

UtilGraph *UtilGraph::getInstance() {
	if (selfUtilGraph) return selfUtilGraph;
	selfUtilGraph = new UtilGraph();
	if (selfUtilGraph && selfUtilGraph->init()) return selfUtilGraph;
	DX_SAFE_DELETE(selfUtilGraph);
	return nullptr;
}

void UtilGraph::destroyInstance() {
	if (!selfUtilGraph) return;

	delete (selfUtilGraph);
	selfUtilGraph = nullptr;
}

bool UtilGraph::init() {
	LOGD("Util", "UtilGraph::init()\n");
	return true;
}

int UtilGraph::createGraph(const string &fileName) {
	if (0 < graphMap.count(fileName)) return graphMap.find(fileName)->second;
	int graph = LoadGraph(fileName.c_str());
	if (graph == -1) return -1;
	graphMap.insert(make_pair(fileName, graph));
	return graph;
}