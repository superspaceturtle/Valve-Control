#pragma once
#include "afxdialogex.h"


// ControlDlg dialog

class ControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ControlDlg)

public:
	ControlDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ControlDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl ctrlSlider;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int intSlider;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	BOOL bStart;
	float fVolts;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	CEdit ctrlInput;
	CString csInput;
};
