#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <mutex>
#include "ColorAdjustInterface.h"

using namespace std;
using namespace cv;

class RegionType
{
public:
	enum RegionMode
	{
		UNSELECT = 0,
		SELECT = 1,
		EDIT = 2,
		SCALE = 3,
		ROTATE = 4,
	};

	vector<Point2i> points;

	CCalibTool *calitool;
	vector<int> black_region;
	vector<int> black_rim;
	vector<int> white_rim;
	bool disable_flag;
	bool ring_flag;

	Mat alpha_map;
	Mat grid_pic;

	int width, height;
	CColorAdjust* whole_map;

	RegionMode regionMode;

	unsigned char* storage_bulk;

	Mat unselect_marker;
	Mat select_marker;
	RegionType(int w, int h);
	RegionType(int len, unsigned char *bulk);

	void LoadResource();
	void UpdateGridPic();
	void UpdateAlphaMap();
	void SetColorAdjust(CColorAdjust* ca);
	bool IsInnerPoint(int x, int y);
	
	int EditPos(int x, int y);
	
	void Translate(int x, int y);

	~RegionType();

	void OutputStorageBulk(int *len, unsigned char** bulk);

	int center_x, center_y;

	vector<Point2i> init_points;
	void PutCenter();
	void GetCenter(int* x, int* y);
	void InitScaleRotatePoints();
	void MoveScaleRotateCenterTo(int x, int y);
	void ScaleRegion(double scale_x, double scale_y);
	void RotateRegion(double angle);
	bool IsNearCenter(int x, int y);
private:
	int calcDisLinePoint(Point2i p0, Point2i p1, int x, int y, double *r);
};


class LeftRegion : public RegionType
{
public:
	LeftRegion(int w, int h);
};

class RightRegion : public RegionType
{
public:
	RightRegion(int w, int h);
};

class TopRegion : public RegionType
{
public:
	TopRegion(int w, int h);
};

class BottomRegion : public RegionType
{
public:
	BottomRegion(int w, int h);
};

class RectRegion : public RegionType
{
public:
	RectRegion(int w, int h);
};

class EllipseRegion : public RegionType
{
public:
	EllipseRegion(int w, int h);
};
