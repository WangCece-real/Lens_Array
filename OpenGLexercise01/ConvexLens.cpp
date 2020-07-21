#include "ConvexLens.h"



ConvexLens::ConvexLens(glm::vec3 _position, float _focalLength):
	positionX(_position.x),
	positionY(_position.y),
	positionZ(_position.z),
	focalLength(_focalLength)
{

}




ConvexLens::~ConvexLens()
{
}



//float* ConvexLens::ImageFormationxy(float _object[], unsigned int _arrLength)
//{	//计算出成像的坐标，返回坐标数组
//	float Image[] = {0.0f};
//	float DistO = 0;	//声明物距
//	float Ratio = 0;
//	for (int i = 0; i < _arrLength; i += 3)
//	{
//		if (Ratio == 0)
//		{
//			float DistO;
//			DistO = _object[i + 2] - positionZ;
//			if (DistO < 0) DistO = -DistO; 	//计算出物距
//			Ratio = DistO / 
//		}
//		Image[i] = (positionX - _object[i]) / Ratio + positionX;	//计算坐标变化
//		Image[i+1] = (positionY - _object[i+1]) / Ratio + positionY;
//		Image[i+2] = (positionZ - _object[i+2]) / Ratio + positionZ;
//	}
//	return Image;
//}

