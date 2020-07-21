#pragma once
#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "LensArray.h"
#include "Len.h"

#include <vector>
#include <algorithm>


//#include <string>
class ManageLensArray
{
public:
	ManageLensArray();

	//想办法让球变成椭球
	void sphere2Ellip(LensArray * _rebuild_lens_array, float _xlabelRatio, float _ylabelRatio);

	//用于在改变之后更新重建数据
	void upDate(LensArray * _imageLensArray, LensArray * _rebuildLensArray);

	~ManageLensArray();
};

class Xsort
{
public:
	bool operator()(glm::vec3 &p1, glm::vec3 &p2)
	{
		return p1.x > p2.x;
	}

};
class Ysort
{
public:
	bool operator()(glm::vec3 &p1, glm::vec3 &p2)
	{
		return p1.y > p2.y;
	}

};
class Zsort
{
public:
	bool operator()(glm::vec3 &p1, glm::vec3 &p2)
	{
		return p1.z > p2.z;
	}
};


