
// CSocketUDPChatDlg.h: 头文件
//

#pragma once
#include "CRecevice.h"


// CCSocketUDPChatDlg 对话框
class CCSocketUDPChatDlg : public CDialogEx
{
// 构造
public:
	CCSocketUDPChatDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSOCKETUDPCHAT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT MessageDeal(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConfirm();
	afx_msg void OnBnClickedButtonSend();
	// 本地开放端口
//	UINT m_open_port;
	// 聊天显示
	CString m_recv;
	// 需要发送的信息
	CString m_send;
	// 目标ip
	CString m_target_ip;
	// 目标开放端口
//	UINT m_target_port;
	// 控制发送按钮
//	CButton m_contorl_send;
	CString m_string_target_ip;
	int m_int_target_port;
	int m_int_local_port;
	// 本地开放端口
	UINT m_open_port;
	// 目标开放端口
	UINT m_target_port;
	// 绑定端口
	bool InitSock();
	CRecevice* recevice;
	CTime m_CTime_time;
	// 控制聊天窗口
	CEdit m_control_recv;
};
