#pragma once
class CWorkInfo
{
public:
	CWorkInfo(void);
	~CWorkInfo(void);
	void init();
public:
	CString strSignal;//�ź�����
	CString strTitle;//�ź���д,����������
	CString strUnit;//��λ
	CString strFilter;//�˲�����
	double leftLimit;//��߽�
	double rightLimit;//�ұ߽�
	int trackNum;//�����,0:���һ��1�������
	//PS_SOLID /* ��*/
	//PS_DASH  /* -------  */
	//PS_DOT  /* .......  */
	//PS_DASHDOT  /* _._._._  */
	//PS_DASHDOTDOT  /* _.._.._  */
	int lineType;//����
	int lineWidth;//�߿�
	COLORREF curveColor; //��ɫ
};

