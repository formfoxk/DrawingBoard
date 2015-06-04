// CDlgPen.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GDIPractice.h"
#include "CDlgPen.h"
#include "afxdialogex.h"


// CDlgPen ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgPen, CDialogEx)

CDlgPen::CDlgPen(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPen::IDD, pParent)
	, m_nPenSize(1)
{

}

CDlgPen::~CDlgPen()
{
}

void CDlgPen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_SPIN_PEN, m_spPen);
	//  DDX_Text(pDX, IDC_EDIT_PEN, m_nPenSize);
	//  DDX_Text(pDX, IDC_EDIT_PEN, m_spPen);
	DDX_Text(pDX, IDC_EDIT_PEN, m_nPenSize);
	DDX_Control(pDX, IDC_SPIN_PEN, m_spPen);
}


BEGIN_MESSAGE_MAP(CDlgPen, CDialogEx)
END_MESSAGE_MAP()


// CDlgPen �޽��� ó�����Դϴ�.


BOOL CDlgPen::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_spPen.SetRange(1,10);

	return true;
}
