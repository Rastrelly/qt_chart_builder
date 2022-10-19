#include "stdafx.h"
#include "chartManager.h"

chartManager::chartManager()
{
	chartPoints.clear();
	calcExtremes();
}

void chartManager::addPoint(dataPoint pt)
{
	chartPoints.push_back(pt);
	calcExtremes();
}

void chartManager::setPoint(int id, dataPoint pt)
{
	if (id<getChartSize())
	  chartPoints[id]=pt;
	calcExtremes();
}

void chartManager::removePoint(int id)
{
	chartPoints.erase(chartPoints.begin()+id);
	calcExtremes();
}

void chartManager::calcExtremes()
{
	l = -1; r = 1; b = -1; t = 1;
	if (getChartSize() > 0)
	{
		l = getPointX(0);
		r = getPointX(0);
		b = getPointY(0);
		t = getPointY(0);
		for (int i = 0; i < getChartSize(); i++)
		{
			if (getPointX(i)<=l) l = getPointX(i);
			if (getPointX(i)>=r) r = getPointX(i);
			if (getPointY(i)<=b) b = getPointY(i);
			if (getPointY(i)>=t) t = getPointY(i);
		}
	}
}

void chartManager::sortByX()
{
	//using selection sorting
	int l = getChartSize();
	if (l > 1)
	{

		for (int i = 0; i < l - 1; i++)
		{
			int min_index = i;
			for (int j = i + 1; j < l; j++)
			{
				if (chartPoints[j].x < chartPoints[min_index].x)
				{
					min_index = j;
				}
			}
			if (min_index != i)
			{
				dataPoint buf = chartPoints[i];
				chartPoints[i] = chartPoints[min_index];
				chartPoints[min_index] = buf;
			}
		}

	}
}

void chartManager::move(int dir)
{
	int l = getChartSize();
	int i = getSelPoint();

	if (((i + dir) >= 0) && ((i + dir) <= (l - 1)))
	{
		dataPoint buf = chartPoints[i];
		chartPoints[i] = chartPoints[i + dir];
		chartPoints[i + dir] = buf;
	}
}