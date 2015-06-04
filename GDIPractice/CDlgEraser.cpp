// CDlgEraser.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GDIPractice.h"
#include "CDlgEraser.h"
#include "afxdialogex.h"


// CDlgEraser 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgEraser, CDialogEx)

CDlgEraser::CDlgEraser(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgEraser::IDD, pParent)
	, m_nEraserSize(2)
{

}

CDlgEraser::~CDlgEraser()
{
}

void CDlgEraser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ERASER, m_nEraserSize);
	DDX_Control(pDX, IDC_SPIN_ERASER, m_spEraser);
}


BEGIN_MESSAGE_MAP(CDlgEraser, CDialogEx)
END_MESSAGE_MAP()


// CDlgEraser 메시지 처리기입니다.


BOOL CDlgEraser::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_spEraser.SetRange(2,20);

	return TRUE;
}
