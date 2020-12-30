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

	// Create animation
	this->createDivGraph("images/c_bone_16.png", "bone", 5, 5, 5, 16, 16, 0, 4);
	this->createDivGraph("images/c_chi_16.png", "chi_front", 25, 5, 5, 16, 16, 0, 4);
	this->createDivGraph("images/c_chi_16.png", "chi_back", 25, 5, 5, 16, 16, 5, 9);
	this->createDivGraph("images/c_chi_16.png", "chi_right", 25, 5, 5, 16, 16, 10, 14);
	this->createDivGraph("images/c_chi_16.png", "chi_left", 25, 5, 5, 16, 16, 15, 19);
	this->createDivGraph("images/c_chi_16.png", "chi_dead", 25, 5, 5, 16, 16, 20, 24);
	this->createDivGraph("images/c_bozu_16.png", "bozu_front", 25, 5, 5, 16, 16, 0, 4);
	this->createDivGraph("images/c_bozu_16.png", "bozu_back", 25, 5, 5, 16, 16, 5, 9);
	this->createDivGraph("images/c_bozu_16.png", "bozu_right", 25, 5, 5, 16, 16, 10, 14);
	this->createDivGraph("images/c_bozu_16.png", "bozu_left", 25, 5, 5, 16, 16, 15, 19);
	this->createDivGraph("images/c_bozu_16.png", "bozu_dead", 25, 5, 5, 16, 16, 20, 24);
	this->createDivGraph("images/c_kobo_16.png", "kobo_front", 25, 5, 5, 16, 16, 0, 4);
	this->createDivGraph("images/c_kobo_16.png", "kobo_back", 25, 5, 5, 16, 16, 5, 9);
	this->createDivGraph("images/c_kobo_16.png", "kobo_right", 25, 5, 5, 16, 16, 10, 14);
	this->createDivGraph("images/c_kobo_16.png", "kobo_left", 25, 5, 5, 16, 16, 15, 19);
	this->createDivGraph("images/c_kobo_16.png", "kobo_dead", 25, 5, 5, 16, 16, 20, 24);
	this->createDivGraph("images/c_tanu_16.png", "tanu_front", 25, 5, 5, 16, 16, 0, 4);
	this->createDivGraph("images/c_tanu_16.png", "tanu_back", 25, 5, 5, 16, 16, 5, 9);
	this->createDivGraph("images/c_tanu_16.png", "tanu_right", 25, 5, 5, 16, 16, 10, 14);
	this->createDivGraph("images/c_tanu_16.png", "tanu_left", 25, 5, 5, 16, 16, 15, 19);
	this->createDivGraph("images/c_tanu_16.png", "tanu_dead", 25, 5, 5, 16, 16, 20, 24);

	return true;
}

int UtilGraph::getGraph(const string &fileName) {
	if (0 < graphMap.count(fileName)) return graphMap.find(fileName)->second;
	return this->createGraph(fileName);
}

const vector<int> &UtilGraph::getDivGraph(const string &frameName) {
	if (0 < divMap.count(frameName)) return divMap.find(frameName)->second;
	return divMap.find("bone")->second;
}

int UtilGraph::createGraph(const string &fileName) {
	int graph = LoadGraph(fileName.c_str());
	if (graph == -1) return -1;
	graphMap.insert(make_pair(fileName, graph));
	return graph;
}

void UtilGraph::createDivGraph(const string &fileName, const string &frameName,
							   int total, int rows, int cols, int w, int h,
							   int from, int to) {
	int graphs[total];
	int result = LoadDivGraph(fileName.c_str(), total, cols, rows, w, h, graphs);
	if (result == -1) return;
	vector<int> frames = {};
	for (int i = from; i <= to; i++) frames.push_back(graphs[i]);
	divMap.insert(make_pair(frameName, frames));
}