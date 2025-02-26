#pragma once

class CObj;
class CState
{
public:
	CState();
	virtual ~CState();

public:
	virtual void Enter() = 0;
	virtual void Execute() = 0;
	virtual void Exit() = 0;
};

 