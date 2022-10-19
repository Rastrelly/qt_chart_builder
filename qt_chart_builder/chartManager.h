#pragma once
#include <vector>

struct dataPoint
{
	float x, y;
};

class chartManager
{
private:
	std::vector<dataPoint> chartPoints;
	int selPoint;
	float l, r, b, t;
	bool callRefresh;

public:
	chartManager();
	void addPoint(dataPoint pt);
	void setPoint(int id, dataPoint pt);
	void removePoint(int id);
	void clearChart() { chartPoints.clear(); }
	void sortByX();
	int getChartSize() { return chartPoints.size(); }
	dataPoint getPoint(int id) { return chartPoints[id]; }
	float getPointX(int id) { return chartPoints[id].x; }
	float getPointY(int id) { return chartPoints[id].y; }
	void move(int dir);

	void SetSelPoint(int val) { selPoint = val; }
	int getSelPoint() { return selPoint; }
	void calcExtremes();
	float getL() { return l; }
	float getR() { return r; }
	float getB() { return b; }
	float getT() { return t; }

	void setCallRefresh(bool val) { callRefresh = val; }
	bool getCallRefresh() { return callRefresh; }
};

