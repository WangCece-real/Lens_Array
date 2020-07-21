#include "ManageLensArray.h"



ManageLensArray::ManageLensArray()
{
}

void ManageLensArray::sphere2Ellip(LensArray * _rebuild_lens_array, float _xlabelRatio, float _ylabelRatio)
{
	/*
	_rebuild_len ��͸������
	_xlabelRatio ��x���� ��Բ����/Բ�뾶
	_ylabelRatio ��y���� ��Բ����/Բ�뾶
	���ã�����͸��λ�ã�������Ӧ͸���ĵ�λ��
	*/
	for (vector<vector<Len>>::iterator it = _rebuild_lens_array->m_lensArrayData.begin(); it != _rebuild_lens_array->m_lensArrayData.end(); it++)
	{
		for (vector<Len>::iterator itl = it->begin(); itl != it->end(); itl++)
		{
			//����ÿһ��͸��
			//��͸����Ӧ�ĵ�Ӧ��Ҫ�ı�ľ���
			if (itl->m_Image.empty())
			{
				//���͸����Ӧ������Ϊ�գ��������͸��
				cout << "͸������Ϊ�գ�������͸�����ݵ���" << endl;
				continue;
			}
			//ת����λ�� - ת��ǰ��λ��
			vector<glm::vec3> sortPos = itl->m_Image;
			int Im_index = sortPos.size() / 2;
			sort(sortPos.begin(), sortPos.end(), Xsort());
			//float tempXDist = itl->m_Image[0].x * _xlabelRatio - itl->m_Image[0].x;
			float tempXDist = sortPos[Im_index].x * _xlabelRatio - sortPos[Im_index].x;
			sort(sortPos.begin(), sortPos.end(), Ysort());
			//float tempYDist = itl->m_Image[0].y * _ylabelRatio - itl->m_Image[0].y;
			float tempYDist = sortPos[Im_index].y * _ylabelRatio - sortPos[Im_index].y;
			//����zֵ��С����ÿһ��͸������������
			//float tempV = itl->m_Image[0].z - itl->m_Position.z;
			sort(sortPos.begin(), sortPos.end(), Zsort());
			float tempV = sortPos[Im_index].z - itl->m_Position.z;
			float tempU = 1 / (1 / itl->m_foLength - 1 / tempV);
			//͸����ƫ����
			glm::vec3 tempLenMove;
			tempLenMove.x = tempXDist * (tempU / (tempU + tempV));
			tempLenMove.y = tempYDist * (tempU / (tempU + tempV));
			tempLenMove.z = 0.0f;
			itl->m_Position += tempLenMove;
			////����ÿһ����ĸı���
			//for (vector<glm::vec3>::iterator itp = itl->m_Image.begin(); itp != itl->m_Image.end(); itp++)
			//{
			//	//����͸���е�ÿһ��������
			//	itp->x = itp->x * _xlabelRatio;
			//	itp->y = itp->y * _ylabelRatio;
			//}
			cout << "͸�����ݵ�������" << endl;
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
