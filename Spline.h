#pragma once
#include <vector>
#include <cmath>
#define INTERVAL 200

struct MYPOINT
{
	double x, y ,z;
	int run,wait;
};


//
std::vector<MYPOINT> convert2d(double temp_ry,double temp_rx,std::vector<MYPOINT> point,double DSPL_OVERRIDE,double ox,double oy);



class SPLINE {

public:
	std::vector<double> spline_u;
	//std::vector<std::vector<MYPOINT>>  spine_point_all;//���ߵ�
	MYPOINT begin_k1;//��㵼ʸ
	MYPOINT end_k1;//�յ㵼ʸ
	//�յĹ��캯����������Ժ����setVertex�����ò�ֵ��
	SPLINE()
	{

	}
	//���ò�ֵ��
	void setVertex(std::vector<MYPOINT> point, int interval_ = INTERVAL);
	//point_x��ֵ��x���꣬point_y��ֵ��y����

	//���ߵ㵼ʸ
	std::vector<MYPOINT> daoshi;
	//��õ�
	std::vector<MYPOINT> get_point();
	//�ƶ���ֵ��
	std::vector<MYPOINT> spine_modify(int begin, int end, int choice, MYPOINT new_position);
	std::vector<MYPOINT> spline_create(int i = 2);
	int interval;
private:
	std::vector<MYPOINT> m_aVertex;//��ֵ��,��ĿΪnum
	std::vector<double> distance;//�ҳ�(num-1)
	std::vector<double> distance_sum_n;
	std::vector<double> canshu_u;//��ֵ��Ĳ���ֵ(num)
	std::vector<double> delta;//delta(num-1)
	std::vector<MYPOINT> all_point;//���ߵ�

	std::vector<std::vector<double>>  matrix_m;
	std::vector<std::vector<double>>  matrix_right;

	//��ֵ�㵼ʸ
	std::vector<std::vector<double>>  daoshi_vec;
	std::vector<MYPOINT> _p;




	std::vector<double> m_Cx;//ÿ����ֵ��ĵ�ʸ��x
	std::vector<double> m_Cy;//ÿ����ֵ��ĵ�ʸ��y
	std::vector<double> m_Cz;//ÿ����ֵ��ĵ�ʸ��z



private:
	//�淶�����ҳ�������
	void canshuhua();

	void settheM(int condition);

	void getdaoshi();

	void Tridia(int n, int k, std::vector<std::vector<double>>&dia, std::vector<std::vector<double>>&t,
		int iflag);

	//////////////////////////////////////////////////////////////////////////
	//���к������ھ������ã����ڴ�д�����������������ռ任ʱ��
	//////////////////////////////////////////////////////////////////////////


	void GetSplineDerivat(int i, double u, int j, MYPOINT &p)
	{
		int n = m_aVertex.size();
		double u1 = u;
		std::vector<double> tx(4);
		std::vector<double> ty(4);
		std::vector<double> tz(4);

		tx[0] = m_aVertex[i].x;
		tx[1] = m_Cx[i];
		tx[2] = 2 / delta[i] * (3 / delta[i] * (m_aVertex[i + 1].x - tx[0]) - 2 * tx[1] - m_Cx[i + 1]);
		tx[3] = 6 / delta[i] / delta[i] * (-2 / delta[i] * (m_aVertex[i + 1].x - tx[0]) + tx[1] + m_Cx[i + 1]);


		ty[0] = m_aVertex[i].y;
		ty[1] = m_Cy[i];
		ty[2] = 2 / delta[i] * (3 / delta[i] * (m_aVertex[i + 1].y - ty[0]) - 2 * ty[1] - m_Cy[i + 1]);
		ty[3] = 6 / delta[i] / delta[i] * (-2 / delta[i] * (m_aVertex[i + 1].y - ty[0]) + ty[1] + m_Cy[i + 1]);

		tz[0] = m_aVertex[i].z;
		tz[1] = m_Cz[i];
		tz[2] = 2 / delta[i] * (3 / delta[i] * (m_aVertex[i + 1].z - tz[0]) - 2 * tz[1] - m_Cz[i + 1]);
		tz[3] = 6 / delta[i] / delta[i] * (-2 / delta[i] * (m_aVertex[i + 1].z - tz[0]) + tz[1] + m_Cz[i + 1]);

		GetCubicCuvValue(i, tx, ty,tz, u1, j, p);
	}


	//////////////////////////////////////////////////////////////////////////
	//���к������ھ������ã����ڴ�д�����������������ռ任ʱ��
	//////////////////////////////////////////////////////////////////////////
	void GetCubicCuvValue(int i, std::vector<double> &tx, std::vector<double> &ty, std::vector<double> &tz,double u,
		int j, MYPOINT &p)
	{
		double pjx = 0, pjy = 0,pjz=0;
		double du = u - canshu_u[i];
		double fj = 4 - j;
		for (int k = 3; k >= j; k--)
		{
			pjx = (pjx / fj)*du + tx[k];
			pjy = (pjy / fj)*du + ty[k];
			pjz= (pjz / fj)*du + tz[k];
			fj = fj - 1;
		}
		p.x = pjx;
		p.y = pjy;
		p.z = pjz;
	}

	//SPLINE(std::vector<double> point_x, std::vector<double> point_y, int interval_ = INTERVAL);

};

