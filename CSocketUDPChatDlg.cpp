
// CSocketUDPChatDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CSocketUDPChat.h"
#include "CSocketUDPChatDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCSocketUDPChatDlg 对话框



CCSocketUDPChatDlg::CCSocketUDPChatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CSOCKETUDPCHAT_DIALOG, pParent)
	, m_open_port(44333)
	, m_recv(_T(""))
	, m_send(_T(""))
	, m_target_ip(_T(""))
	, m_target_port(44333)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_string_target_ip = _T("");
	m_int_target_port = 0;
	m_int_local_port = 0;
	recevice = NULL;
}

void CCSocketUDPChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_OPEN_PORT, m_open_port);
	//  DDV_MinMaxUInt(pDX, m_open_port, 1, 65535);
	DDX_Text(pDX, IDC_RECV, m_recv);
	DDX_Text(pDX, IDC_SEND, m_send);
	DDX_Text(pDX, IDC_Target_IP, m_target_ip);
	//  DDX_Text(pDX, IDC_Target_port, m_target_port);
	//  DDV_MinMaxUInt(pDX, m_target_port, 1, 65535);
	//  DDX_Control(pDX, IDC_BUTTON_SEND, m_contorl_send);
	DDX_Text(pDX, IDC_OPEN_PORT, m_open_port);
	DDX_Text(pDX, IDC_Target_port, m_target_port);
	DDX_Control(pDX, IDC_RECV, m_control_recv);
}

BEGIN_MESSAGE_MAP(CCSocketUDPChatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONFIRM, &CCSocketUDPChatDlg::OnBnClickedButtonConfirm)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CCSocketUDPChatDlg::OnBnClickedButtonSend)
	ON_MESSAGE(MYSMG,MessageDeal)
END_MESSAGE_MAP()


// CCSocketUDPChatDlg 消息处理程序

BOOL CCSocketUDPChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCSocketUDPChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCSocketUDPChatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCSocketUDPChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCSocketUDPChatDlg::OnBnClickedButtonConfirm()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	struct in_addr addr;

	if (inet_pton(AF_INET,CStringA(m_target_ip),&addr)!=1) 
	{
		MessageBox(_T("错误的ip地址！"),_T("错误"),MB_OK);
	}
	else 
	{
		if (m_target_port < 1 || m_target_port>65535) 
		{
			MessageBox(_T("错误的目标端口！(1<=端口号<=65535)"), _T("错误"), MB_OK);
		}
		else
		{
			if (m_open_port < 1 || m_open_port>65535)
			{
				MessageBox(_T("错误的本地开放端口！(1<=端口号<=65535)"), _T("错误"), MB_OK);
			}
			else
			{
				//绑定端口和IP
				if (InitSock())
				{
					//使发送按钮生效
					m_string_target_ip = m_target_ip;
					m_int_target_port = m_target_port;
					m_int_local_port = m_open_port;
					GetDlgItem(IDC_BUTTON_SEND)->SetWindowText(_T("发送信息"));
					GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
				}
			}
		}
	}
}


void CCSocketUDPChatDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//发送数据
	CSocket send_socket;
	send_socket.Create(0,SOCK_DGRAM,NULL);
	send_socket.SendTo(m_send, m_send.GetLength(), m_int_target_port, m_string_target_ip,0);
	send_socket.Close();
	//刷新聊天区域并清空输入内容
	m_CTime_time = CTime::GetCurrentTime();
	CString buf = m_CTime_time.Format("%Y年%m月%d日 %X 发送信息:");
	m_recv += buf;
	m_recv += "\r\n";
	m_recv += m_send;
	m_recv += "\r\n";
	m_send = "";
	UpdateData(FALSE);
	m_control_recv.LineScroll(m_control_recv.GetLineCount()-1,0);
	//将焦点设置为输入信息窗口
	GetDlgItem(IDC_SEND)->SetFocus();

}

LRESULT CCSocketUDPChatDlg::MessageDeal(WPARAM wParam, LPARAM lParam)
{
	m_CTime_time = CTime::GetCurrentTime();
	CString buf = m_CTime_time.Format("%Y年%m月%d日 %X 收到信息:");
	m_recv += buf;
	m_recv += "\r\n";
	m_recv +=  *(CString*)lParam;
	m_recv += "\r\n";
	UpdateData(FALSE);
	m_control_recv.LineScroll(m_control_recv.GetLineCount() - 1, 0);

	return 0;
}


// 绑定本地端口
bool CCSocketUDPChatDlg::InitSock()
{
	// TODO: 在此处添加实现代码.
	if (recevice != NULL)
	{
		delete recevice;
	}
	recevice = new CRecevice();
	if (!recevice->Create(m_open_port, SOCK_DGRAM, NULL))
	{
		MessageBox(_T("绑定本地端口失败，请更换本地端口"), _T("信息"), MB_OK);
		return FALSE;
	}
	else {
		MessageBox(_T("绑定本地端口成功"), _T("信息"), MB_OK);
		return TRUE;
	}

}
