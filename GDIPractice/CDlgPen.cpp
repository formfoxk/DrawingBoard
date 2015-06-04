// CDlgPen.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GDIPractice.h"
#include "CDlgPen.h"
#include "afxdialogex.h"


// CDlgPen 대화 상자입니다.

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


// CDlgPen 메시지 처리기입니다.


BOOL CDlgPen::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_spPen.SetRange(1,10);

	return true;
}
