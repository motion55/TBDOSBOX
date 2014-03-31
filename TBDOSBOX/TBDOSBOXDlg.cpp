
// TBDOSBOXDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TBDOSBOX.h"
#include "TBDOSBOXDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////
// Constants 

const TCHAR * kpcTrayNotificationMsg_ = _T("TBDosBox tray notification");

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTBDOSBOXDlg dialog


CTBDOSBOXDlg::CTBDOSBOXDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTBDOSBOXDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bMinimized_ = 0;
	m_pTrayIcon_ = 0;
	m_nTrayNotificationMsg_ = RegisterWindowMessage(kpcTrayNotificationMsg_);
}

void CTBDOSBOXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESOLUTION, m_cResolution);
	DDX_Control(pDX, IDC_PIXEL_SCALING, m_cPixelScaling);
}

BEGIN_MESSAGE_MAP(CTBDOSBOXDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_ST_RESTORE, OnSTRestore)
	ON_COMMAND(IDC_ST_EXIT, OnSTExit)
END_MESSAGE_MAP()


// CTBDOSBOXDlg message handlers

BOOL CTBDOSBOXDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTBDOSBOXDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		// Decide if minimize state changed
		bool bOldMin = m_bMinimized_;
		if (nID == SC_MINIMIZE) {
			m_bMinimized_ = true;
		}
		else if (nID == SC_RESTORE) {
			m_bMinimized_ = false;
		}

		CDialogEx::OnSysCommand(nID, lParam);

		if (bOldMin != m_bMinimized_) {
			// Minimize state changed.  Create the systray icon and do 
			// custom taskbar button handling.
			SetupTrayIcon();
			SetupTaskBarButton();
		}
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTBDOSBOXDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTBDOSBOXDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTBDOSBOXDlg::SetupTrayIcon()
{
	if (m_bMinimized_ && (m_pTrayIcon_ == 0))
	{
		m_pTrayIcon_ = new CSystemTray;
		m_pTrayIcon_->Create(0, m_nTrayNotificationMsg_, _T("TBDosBox"),
			m_hIcon, IDR_SYSTRAY_MENU);
	}
	else
	{
		delete m_pTrayIcon_;
		m_pTrayIcon_ = 0;
	}
}

void CTBDOSBOXDlg::SetupTaskBarButton()
{
	if (m_bMinimized_) {
		ShowWindow(SW_HIDE);
	}
	else {
		ShowWindow(SW_SHOW);
	}
}

void CTBDOSBOXDlg::OnSTRestore()
{
	ShowWindow(SW_RESTORE);
	m_bMinimized_ = false;
	SetupTrayIcon();
	SetupTaskBarButton();
}

void CTBDOSBOXDlg::OnSTExit()
{
	OnCancel();
}
