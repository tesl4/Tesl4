#include <ctime>
#pragma once
class CTimeMgr
{
	clock_t		m_deltaMS;			//���� ������Ʈ�� ���� ������Ʈ������ �ð�(millisec)
	clock_t		m_totalRuntimeMS;	//���� ���ø����̼��� ���� �ð�(ms)

	UINT m_minDeltaMS;	//�ּ� ƽ ����(�ִ� FPS ���ѿ� �ʿ��� ���� ��, 1000/capfps)

	float m_deltaNor;
	float m_timer;
	float m_minDeltaNor;			//���� ������Ʈ�� ���� ������Ʈ������ �ð�(millisec)

	int m_fps;

public:
	CTimeMgr();
	~CTimeMgr();
	
	UINT TimeUpdate();
	void CapFPS(int _capVal);
};

