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
//{	//�������������꣬������������
//	float Image[] = {0.0f};
//	float DistO = 0;	//�������
//	float Ratio = 0;
//	for (int i = 0; i < _arrLength; i += 3)
//	{
//		if (Ratio == 0)
//		{
//			float DistO;
//			DistO = _object[i + 2] - positionZ;
//			if (DistO < 0) DistO = -DistO; 	//��������
//			Ratio = DistO / 
//		}
//		Image[i] = (positionX - _object[i]) / Ratio + positionX;	//��������仯
//		Image[i+1] = (positionY - _object[i+1]) / Ratio + positionY;
//		Image[i+2] = (positionZ - _object[i+2]) / Ratio + positionZ;
//	}
//	return Image;
//}

