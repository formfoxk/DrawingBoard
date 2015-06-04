#pragma once
#include "afxcmn.h"


// CDlgEraser 대화 상자입니다.

class CDlgEraser : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgEraser)

public:
	CDlgEraser(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgEraser();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETERASERSIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_nEraserSize;
	CSpinButtonCtrl m_spEraser;
	virtual BOOL OnInitDialog();
};
