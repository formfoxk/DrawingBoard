#pragma once
#include "afxcmn.h"


// CDlgEraser ��ȭ �����Դϴ�.

class CDlgEraser : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgEraser)

public:
	CDlgEraser(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgEraser();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETERASERSIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_nEraserSize;
	CSpinButtonCtrl m_spEraser;
	virtual BOOL OnInitDialog();
};
