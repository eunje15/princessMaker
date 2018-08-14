#pragma once
#include "gameNode.h"

//�ݹ��Լ� == �Լ�������
typedef void(*CALLBACK_FUNCTION)(void);

//���θ� �ϸ� �� ������ �־ �˷��帮�� �Խ��ϴ�
//<functional> �̶� ���̺귯���� �ִµ�
//���⿡ std::Function, std::bind, std::move ���
//��ɾ �����ϴµ�
//���� �ݹ��Լ��� �Լ��������ε� ����ȭ �Ǿ��ֱ� ������
//�Ϲ����� ������� �Ű������� �������� ����
//������ ��ų� ���̺귯���� ����ϰԵǸ� �Ű������� ����Ҽ��ִ�
//�����غ� ����� �����غ��� �ٶ�~

//����1 �Ƹ����Ѱ� ����
//����2 �ǿܷ� �� �����ϰ� �Ǵ°� ����

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;	//��ư ������ �̳ѹ�

	const char* _imageName;		//�̹��� �̸�
	image* _image;				//�̹���
	RECT _rc;					//��Ʈ

	float _x, _y;				//���� ��ġ

	POINT _btnDownFramePoint;	//��ư �̹��� ��������ġ
	POINT _btnUpFramePoint;

	CALLBACK_FUNCTION _callbackFunction;	//�ݹ��Լ�
public:
	button();
	~button();

	HRESULT init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction);

	void release();
	void update();
	void render();
};

