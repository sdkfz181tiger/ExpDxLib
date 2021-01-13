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
	this->createDivGraph("images/s_bone.png", "bone_f", 1, 5, 16, 16, 0, 4);
	// Chicken
	this->createDivGraph("images/s_chi.png", "chi_f", 5, 5, 16, 16, 0, 4);
	this->createDivGraph("images/s_chi.png", "chi_b", 5, 5, 16, 16, 5, 9);
	this->createDivGraph("images/s_chi.png", "chi_r", 5, 5, 16, 16, 10, 14);
	this->createDivGraph("images/s_chi.png", "chi_l", 5, 5, 16, 16, 15, 19);
	this->createDivGraph("images/s_chi.png", "chi_d", 5, 5, 16, 16, 20, 24);
	this->createDivGraph("images/s_chi.png", "chi_i1", 9, 5, 16, 16, 25, 29);
	this->createDivGraph("images/s_chi.png", "chi_i2", 9, 5, 16, 16, 30, 34);
	this->createDivGraph("images/s_chi.png", "chi_i3", 9, 5, 16, 16, 35, 39);
	this->createDivGraph("images/s_chi.png", "chi_i4", 9, 5, 16, 16, 40, 44);
	// Hiyo
	this->createDivGraph("images/s_hiyo.png", "hiyo_f", 5, 5, 9, 9, 0, 4);
	this->createDivGraph("images/s_hiyo.png", "hiyo_b", 5, 5, 9, 9, 5, 9);
	this->createDivGraph("images/s_hiyo.png", "hiyo_r", 5, 5, 9, 9, 10, 14);
	this->createDivGraph("images/s_hiyo.png", "hiyo_l", 5, 5, 9, 9, 15, 19);
	this->createDivGraph("images/s_hiyo.png", "hiyo_d", 5, 5, 9, 9, 20, 24);
	this->createDivGraph("images/s_hiyo.png", "hiyo_i1", 7, 5, 9, 9, 25, 29);
	this->createDivGraph("images/s_hiyo.png", "hiyo_i2", 7, 5, 9, 9, 30, 34);
	// Osho
	this->createDivGraph("images/s_osho.png", "osho_f", 5, 5, 16, 16, 0, 4);
	this->createDivGraph("images/s_osho.png", "osho_b", 5, 5, 16, 16, 5, 9);
	this->createDivGraph("images/s_osho.png", "osho_r", 5, 5, 16, 16, 10, 14);
	this->createDivGraph("images/s_osho.png", "osho_l", 5, 5, 16, 16, 15, 19);
	this->createDivGraph("images/s_osho.png", "osho_d", 5, 5, 16, 16, 20, 24);
	// Kobo
	this->createDivGraph("images/s_kobo.png", "kobo_f", 5, 5, 16, 16, 0, 4);
	this->createDivGraph("images/s_kobo.png", "kobo_b", 5, 5, 16, 16, 5, 9);
	this->createDivGraph("images/s_kobo.png", "kobo_r", 5, 5, 16, 16, 10, 14);
	this->createDivGraph("images/s_kobo.png", "kobo_l", 5, 5, 16, 16, 15, 19);
	this->createDivGraph("images/s_kobo.png", "kobo_d", 5, 5, 16, 16, 20, 24);
	// Tanu
	this->createDivGraph("images/s_tanu.png", "tanu_f", 5, 5, 16, 16, 0, 4);
	this->createDivGraph("images/s_tanu.png", "tanu_b", 5, 5, 16, 16, 5, 9);
	this->createDivGraph("images/s_tanu.png", "tanu_r", 5, 5, 16, 16, 10, 14);
	this->createDivGraph("images/s_tanu.png", "tanu_l", 5, 5, 16, 16, 15, 19);
	this->createDivGraph("images/s_tanu.png", "tanu_d", 5, 5, 16, 16, 20, 24);

	return true;
}

int UtilGraph::getGraph(const string &fileName) {
	if (0 < graphMap.count(fileName)) return graphMap.find(fileName)->second;
	return this->createGraph(fileName);
}

const vector<int> &UtilGraph::getDivGraph(const string &frameName) {
	if (0 < divMap.count(frameName)) return divMap.find(frameName)->second;
	return divMap.find("bone_f")->second;
}

int UtilGraph::createGraph(const string &fileName) {
	int graph = LoadGraph(fileName.c_str());
	if (graph == -1) return -1;
	graphMap.insert(make_pair(fileName, graph));
	return graph;
}

void UtilGraph::createDivGraph(const string &fileName, const string &frameName,
							   int rows, int cols, int w, int h, int from, int to) {
	int total = rows * cols;
	int graphs[total];
	int result = LoadDivGraph(fileName.c_str(), total, cols, rows, w, h, graphs);
	if (result == -1) return;
	vector<int> frames = {};
	for (int i = from; i <= to; i++) frames.push_back(graphs[i]);
	divMap.insert(make_pair(frameName, frames));
}