// ControlDlg.cpp : implementation file
//

#include "pch.h"
#include "ValveControl.h"
#include "afxdialogex.h"
#include "ControlDlg.h"
#include <NIDAQmx.h>
#include <stdio.h>
#include <math.h>

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

#define PI	3.1415926535

UINT DAQThread(LPVOID pParam);
int32 CVICALLBACK DoneCallback(TaskHandle taskHandle, int32 status, void* callbackData);
// ControlDlg dialog

IMPLEMENT_DYNAMIC(ControlDlg, CDialogEx)

ControlDlg::ControlDlg(CWnd * pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, intSlider(0)
	, fVolts(1.0)
	, csInput(_T("1.0"))
{

}

ControlDlg::~ControlDlg()
{
}

void ControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, ctrlSlider);
	DDX_Slider(pDX, IDC_SLIDER1, intSlider);
	DDX_Control(pDX, IDC_INPUT, ctrlInput);
	DDX_Text(pDX, IDC_INPUT, csInput);
}


BEGIN_MESSAGE_MAP(ControlDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_START, &ControlDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &ControlDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// ControlDlg message handlers

void ControlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	fVolts = ctrlSlider.GetPos() / 4.0f;
	CString str;
	str.Format(_T("%.1f"), fVolts);
	ctrlInput.SetWindowTextW(str);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL ControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	ctrlSlider.SetRange(4, 20, true);
	
	ctrlSlider.SetPos(4);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

UINT DAQThread(LPVOID pParam) {
	USES_CONVERSION;
	ControlDlg* dialog = (ControlDlg*)pParam;
	int32       error = 0;
	TaskHandle  taskHandle = 0;
	char        errBuff[2048] = { '\0' };



	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk(DAQmxCreateTask("", &taskHandle));
	DAQmxErrChk(DAQmxCreateAOVoltageChan(taskHandle, "Dev1/ao0", "", -10.0, 10.0, DAQmx_Val_Volts, NULL));
	//DAQmxErrChk(DAQmxCfgSampClkTiming(taskHandle, "", 1000.0, DAQmx_Val_Rising, DAQmx_Val_ContSamps, 1000));

	DAQmxErrChk(DAQmxRegisterDoneEvent(taskHandle, 0, DoneCallback, NULL));

	/*********************************************/
	// DAQmx Write Code
	/*********************************************/
	//DAQmxErrChk(DAQmxWriteAnalogF64(taskHandle, 1000, 0, 10.0, DAQmx_Val_GroupByChannel, data, NULL, NULL));
	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxErrChk(DAQmxStartTask(taskHandle));
	while (dialog->bStart) {
		DAQmxErrChk(DAQmxWriteAnalogScalarF64(taskHandle, 0, 10.0, dialog->fVolts, NULL));
		Sleep(100);
	}
	DAQmxStopTask(taskHandle);
	DAQmxClearTask(taskHandle);
	return 0;

Error:
	if (DAQmxFailed(error))
		DAQmxGetExtendedErrorInfo(errBuff, 2048);
		const wchar_t* unicode = A2W(errBuff);

	if (taskHandle != 0) {
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(taskHandle);
		DAQmxClearTask(taskHandle);
	}
	if (DAQmxFailed(error))
		AfxMessageBox(unicode);
	printf("End of program, press Enter key to quit\n");
	getchar();
	return 0;
}

int32 CVICALLBACK DoneCallback(TaskHandle taskHandle, int32 status, void* callbackData)
{
	USES_CONVERSION;
	int32   error = 0;
	char    errBuff[2048] = { '\0' };

	// Check to see if an error stopped the task.
	DAQmxErrChk(status);

Error:
	if (DAQmxFailed(error)) {
		DAQmxGetExtendedErrorInfo(errBuff, 2048);
		DAQmxClearTask(taskHandle);
		const wchar_t* unicode = A2W(errBuff);
		AfxMessageBox(unicode);
	}
	return 0;
}

void ControlDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	UpdateData(true);
	float val = _ttof(csInput);
	if ( val < 1.0 || val > 5.0) {
		AfxMessageBox(_T("Please enter a number between 1.0 and 5.0"));
		
		return;
	}
	fVolts = val;
	CString str;
	str.Format(_T("%.1f"), fVolts);
	ctrlSlider.SetPos(int(fVolts * 4));
	
}



void ControlDlg::OnBnClickedStart()
{
	bStart = true;
	AfxBeginThread(DAQThread, (LPVOID)this);
}

void ControlDlg::OnBnClickedStop()
{
	bStart = false;
}
