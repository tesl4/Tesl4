#include <ctime>
#pragma once
class CTimeMgr
{
	clock_t		m_currentRuntime;	//���� ���ø����̼��� ���� �ð�(ms)
	
	float m_delta;
	float m_deltaNor;
	float m_minDelta;	//�ּ� ƽ ����(�ִ� FPS ���ѿ� �ʿ��� ���� ��, 1000/capfps)
	float m_timer;

	int m_fps;

	INT64 m_PerformanceCntr;

public:
	CTimeMgr();
	~CTimeMgr();
	
	UINT TimeUpdate();
	void CapFPS(int _capVal);

	float GetDelta();
	float GetDeltaMS();

};

