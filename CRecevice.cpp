#include "pch.h"
#include "CRecevice.h"




void CRecevice::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	char buf[1024];							//������ʱ��Ž��յ���Ϣ
	memset(buf,0,1024);						//buf���0
	ReceiveFrom(buf,1024,NULL,NULL,0);		//�������л�ȡ���յ�����Ϣ
	CString buf_string;
	buf_string.Format(TEXT("%s"),buf);		//��char����ת����CString
	SendMessage(AfxGetMainWnd()->m_hWnd,MYSMG,0,(LPARAM)&buf_string);

	CSocket::OnReceive(nErrorCode);
}
