
// TBDOSBOXDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "SystemTray.h"

// CTBDOSBOXDlg dialog
class CTBDOSBOXDlg : public CDialogEx
{
// Construction
public:
	CTBDOSBOXDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TBDOSBOX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	bool m_bMinimized_;
	CSystemTray* m_pTrayIcon_;
	UINT m_nTrayNotificationMsg_;
	void SetupTrayIcon();
	void SetupTaskBarButton();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSTRestore();
	afx_msg void OnSTExit();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cResolution;
	CComboBox m_cPixelScaling;
};
