#pragma once
#include "afxcmn.h"


// CDlgPen ��ȭ �����Դϴ�.

class CDlgPen : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPen)

public:
	CDlgPen(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgPen();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETPENSIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
//	CSpinButtonCtrl m_spPen;
//	UINT m_nPenSize;
	virtual BOOL OnInitDialog();
//	UINT m_spPen;
	UINT m_nPenSize;
	CSpinButtonCtrl m_spPen;
};
