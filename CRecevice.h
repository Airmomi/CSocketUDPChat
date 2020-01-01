#pragma once
#include <afxsock.h>

#define MYSMG WM_USER+1

class CRecevice :
	public CSocket
{
public:
//	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

