#pragma once
#include "afxcmn.h"


// CDlgPen 대화 상자입니다.

class CDlgPen : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPen)

public:
	CDlgPen(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgPen();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETPENSIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	CSpinButtonCtrl m_spPen;
//	UINT m_nPenSize;
	virtual BOOL OnInitDialog();
//	UINT m_spPen;
	UINT m_nPenSize;
	CSpinButtonCtrl m_spPen;
};
