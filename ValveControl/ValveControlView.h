
// ValveControlView.h : interface of the CValveControlView class
//

#pragma once
#include "ControlDlg.h"

class CValveControlView : public CView
{
protected: // create from serialization only
	CValveControlView() noexcept;
	DECLARE_DYNCREATE(CValveControlView)

// Attributes
public:
	CValveControlDoc* GetDocument() const;
	ControlDlg* m_pControlDlg;
	int slider;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CValveControlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in ValveControlView.cpp
inline CValveControlDoc* CValveControlView::GetDocument() const
   { return reinterpret_cast<CValveControlDoc*>(m_pDocument); }
#endif

