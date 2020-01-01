#include "pch.h"
#include "CRecevice.h"




void CRecevice::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	char buf[1024];							//用于暂时存放接收的信息
	memset(buf,0,1024);						//buf填充0
	ReceiveFrom(buf,1024,NULL,NULL,0);		//从网卡中获取接收到的信息
	CString buf_string;
	buf_string.Format(TEXT("%s"),buf);		//将char数组转换成CString
	SendMessage(AfxGetMainWnd()->m_hWnd,MYSMG,0,(LPARAM)&buf_string);

	CSocket::OnReceive(nErrorCode);
}
