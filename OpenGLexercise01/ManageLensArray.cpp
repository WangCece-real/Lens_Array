#include "ManageLensArray.h"



ManageLensArray::ManageLensArray()
{
}

void ManageLensArray::sphere2Ellip(LensArray * _rebuild_lens_array, float _xlabelRatio, float _ylabelRatio)
{
	/*
	_rebuild_len ：透镜阵列
	_xlabelRatio ：x方向 椭圆长轴/圆半径
	_ylabelRatio ：y方向 椭圆短轴/圆半径
	作用：调整透镜位置，调整对应透镜的点位置
	*/
	for (vector<vector<Len>>::iterator it = _rebuild_lens_array->m_lensArrayData.begin(); it != _rebuild_lens_array->m_lensArrayData.end(); it++)
	{
		for (vector<Len>::iterator itl = it->begin(); itl != it->end(); itl++)
		{
			//遍历每一个透镜
			//该透镜对应的点应该要改变的距离
			if (itl->m_Image.empty())
			{
				//如果透镜对应的数据为空，跳过这个透镜
				cout << "透镜数据为空，跳过该透镜数据调整" << endl;
				continue;
			}
			//转变后的位置 - 转变前的位置
			vector<glm::vec3> sortPos = itl->m_Image;
			int Im_index = sortPos.size() / 2;
			sort(sortPos.begin(), sortPos.end(), Xsort());
			//float tempXDist = itl->m_Image[0].x * _xlabelRatio - itl->m_Image[0].x;
			float tempXDist = sortPos[Im_index].x * _xlabelRatio - sortPos[Im_index].x;
			sort(sortPos.begin(), sortPos.end(), Ysort());
			//float tempYDist = itl->m_Image[0].y * _ylabelRatio - itl->m_Image[0].y;
			float tempYDist = sortPos[Im_index].y * _ylabelRatio - sortPos[Im_index].y;
			//根据z值大小，对每一个透镜的坐标排序
			//float tempV = itl->m_Image[0].z - itl->m_Position.z;
			sort(sortPos.begin(), sortPos.end(), Zsort());
			float tempV = sortPos[Im_index].z - itl->m_Position.z;
			float tempU = 1 / (1 / itl->m_foLength - 1 / tempV);
			//透镜的偏移量
			glm::vec3 tempLenMove;
			tempLenMove.x = tempXDist * (tempU / (tempU + tempV));
			tempLenMove.y = tempYDist * (tempU / (tempU + tempV));
			tempLenMove.z = 0.0f;
			itl->m_Position += tempLenMove;
			////计算每一个点的改变量
			//for (vector<glm::vec3>::iterator itp = itl->m_Image.begin(); itp != itl->m_Image.end(); itp++)
			//{
			//	//遍历透镜中的每一个成像结果
			//	itp->x = itp->x * _xlabelRatio;
			//	itp->y = itp->y * _ylabelRatio;
			//}
			cout << "透镜数据调整结束" << endl;
		}
	}

}


void ManageLensArray::upDate(LensArray * _imageLensArray, LensArray * _rebuildLensArray)
{
	for (int i = 0; i < _imageLensArray->m_X; i++)
	{
		for (int j = 0; j < _imageLensArray->m_Y; j++)
		{
			_rebuildLensArray->m_lensArrayData[i][j].m_Image.clear();
			_rebuildLensArray->m_lensArrayData[i][j].lenImaging(_imageLensArray->m_lensArrayData[i][j].m_Image);
			//cout <<"("<< imageArr->m_lensArrayData[i][j].m_Position.x <<","
			//	<< imageArr->m_lensArrayData[i][j].m_Position.y <<","
			//	<< imageArr->m_lensArrayData[i][j].m_Position.z << ") "<<endl;
		}
	}

}

ManageLensArray::~ManageLensArray()
{
}
