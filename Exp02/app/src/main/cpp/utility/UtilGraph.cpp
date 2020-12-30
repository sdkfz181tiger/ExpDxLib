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

const vector<int> *UtilGraph::createDivGraph(const string &fileName, const string &animName,
											 int total, int rows, int cols, int w, int h) {
	if (0 < divMap.count(animName)) return &divMap.find(animName)->second;
	int graph[total];
	int result = LoadDivGraph(fileName.c_str(), total, cols, rows, w, h, graph);
	if (result == -1) return nullptr;
	vector<int> graphs;
	graphs.reserve(total);
	for (int i = 0; i < total; i++) {
		graphs.push_back(graph[i]);
	}
	divMap.insert(make_pair(animName, graphs));
	return &divMap.find(animName)->second;
}