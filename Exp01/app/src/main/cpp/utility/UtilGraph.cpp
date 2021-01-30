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

	// JSON
	const string fullPath = UtilJNI::getInstance()->getFilePath() + "index.json";
	const json jObj = UtilJson::getInstance()->loadJson(fullPath.c_str());
	const json jArr = jObj["sprite_sheets"];
	for (json obj : jArr) {
		const string fileName = obj["file_name"];
		const string frameName = obj["frame_name"];
		const int rows = obj["rows"];
		const int cols = obj["cols"];
		const int w = obj["w"];
		const int h = obj["h"];
		const int from = obj["from"];
		const int to = obj["to"];
		this->createDivGraph(fileName.c_str(), frameName.c_str(),
							 rows, cols, w, h, from, to);
	}
	return true;
}

int UtilGraph::getGraph(const string &fileName) {
	if (0 < graphMap.count(fileName)) return graphMap.find(fileName)->second;
	return this->createGraph(fileName);
}

const vector<int> &UtilGraph::getDivGraph(const string &frameName) {
	if (0 < divMap.count(frameName)) return divMap.find(frameName)->second;
	return divMap.find("egg_hop")->second;
}

int UtilGraph::createGraph(const string &fileName) {
	int graph = LoadGraph(this->getLocalPath(fileName).c_str());
	if (graph == -1) return -1;
	graphMap.insert(make_pair(fileName, graph));
	return graph;
}

void UtilGraph::createDivGraph(const string &fileName, const string &frameName,
							   int rows, int cols, int w, int h, int from, int to) {
	int total = rows * cols;
	int graphs[total];
	int result = LoadDivGraph(this->getLocalPath(fileName).c_str(),
							  total, cols, rows, w, h, graphs);
	if (result == -1) return;
	vector<int> frames = {};
	for (int i = from; i <= to; i++) frames.push_back(graphs[i]);
	divMap.insert(make_pair(frameName, frames));
}

string UtilGraph::getLocalPath(const string &fileName) {
	return UtilJNI::getInstance()->getFilePath().c_str() + fileName;
}