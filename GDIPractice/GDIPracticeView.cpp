
// GDIPracticeView.cpp : CGDIPracticeView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GDIPractice.h"
#endif

#include "GDIPracticeDoc.h"
#include "GDIPracticeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDIPracticeView

IMPLEMENT_DYNCREATE(CGDIPracticeView, CView)

	BEGIN_MESSAGE_MAP(CGDIPracticeView, CView)
		// ǥ�� �μ� ����Դϴ�.
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
		ON_COMMAND(ID_PEN_SIZE, &CGDIPracticeView::OnPenSize)
		ON_COMMAND(ID_PEN_COLOR, &CGDIPracticeView::OnPenColor)
		ON_COMMAND(ID_ERASER_SIZE, &CGDIPracticeView::OnEraserSize)
		ON_COMMAND(ID_DRAW_LINE, &CGDIPracticeView::OnDrawLine)
		ON_COMMAND(ID_DRAW_RECT, &CGDIPracticeView::OnDrawRect)
		ON_COMMAND(ID_DRAW_CIRCLE, &CGDIPracticeView::OnDrawCircle)
		ON_COMMAND(ID_DRAW_FREE, &CGDIPracticeView::OnDrawFree)
		ON_COMMAND(ID_DRAW_POLY, &CGDIPracticeView::OnDrawPoly)
		ON_UPDATE_COMMAND_UI(ID_DRAW_FREE, &CGDIPracticeView::OnUpdateDrawFree)
		ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CGDIPracticeView::OnUpdateDrawLine)
		ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, &CGDIPracticeView::OnUpdateDrawRect)
		ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CGDIPracticeView::OnUpdateDrawCircle)
		ON_UPDATE_COMMAND_UI(ID_DRAW_POLY, &CGDIPracticeView::OnUpdateDrawPoly)
		ON_WM_MOUSEMOVE()
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_RBUTTONDOWN()

	END_MESSAGE_MAP()

	// CGDIPracticeView ����/�Ҹ�

	CGDIPracticeView::CGDIPracticeView()
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
		m_nPenSize = 1;
		m_colorPen = RGB(0,0,0); 
		m_nDrawMode =  FREE_MODE;
		m_bLButtonDown = false;
	}

	CGDIPracticeView::~CGDIPracticeView()
	{
	}

	BOOL CGDIPracticeView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
		//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

		return CView::PreCreateWindow(cs);
	}

	// CGDIPracticeView �׸���

	void CGDIPracticeView::OnDraw(CDC* pDC)
	{
		// Pen ����
		CPen pen, *oldPen;		
		pen.CreatePen(PS_SOLID, m_nPenSize, m_colorPen);	//Pen ��ü ����
		oldPen = pDC->SelectObject(&pen);					//Pen ��ü ���	

		switch(m_nDrawMode)
		{
		case LINE_MODE :					// ���� �׸���
			//������ ���� �׸�
			pDC->MoveTo(m_ptCurr);
			pDC->LineTo(m_ptPrev);
			break;
		case CIRCLE_MODE :					// �� �׸���
			pDC->Ellipse(m_ptCurr.x, m_ptCurr.y, m_ptPrev.x, m_ptPrev.y);
			break;
		case RECT_MODE :					// �簢�� �׸���
			pDC->Rectangle(m_ptCurr.x, m_ptCurr.y, m_ptPrev.x, m_ptPrev.y);
			break;
		case POLY_MODE :					// �ٰ��� �׸���
			//�迭�� ������ ������� ������ ������ �ٰ��� �׸���
			pDC->Polygon(m_ptData, m_nCount);
			break;
		}
		//���� pen���� ����
		pDC->SelectObject(oldPen);	
		// Pen ���� ����
		pen.DeleteObject();
	}

	// CGDIPracticeView �μ�

	BOOL CGDIPracticeView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// �⺻���� �غ�
		return DoPreparePrinting(pInfo);
	}

	void CGDIPracticeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	}

	void CGDIPracticeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
	}


	// CGDIPracticeView ����

#ifdef _DEBUG
	void CGDIPracticeView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CGDIPracticeView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CGDIPracticeDoc* CGDIPracticeView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIPracticeDoc)));
		return (CGDIPracticeDoc*)m_pDocument;
	}
#endif //_DEBUG

	// CGDIPracticeView �޽��� ó����
	void CGDIPracticeView::OnPenSize()
	{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		CDlgPen *pdlgPen = new CDlgPen;
		if (pdlgPen->DoModal() == IDOK) {
			m_nPenSize = pdlgPen->m_nPenSize;
		}

	}

	void CGDIPracticeView::OnEraserSize()
	{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		CDlgEraser *pdlgEraser = new CDlgEraser;
		if (pdlgEraser->DoModal() == IDOK) {
			m_nEraserSize = pdlgEraser->m_nEraserSize;
		}

	}

	void CGDIPracticeView::OnPenColor()
	{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		CColorDialog crDlg;
		if (crDlg.DoModal() == IDOK) {
			m_colorPen = crDlg.GetColor();
		}
	}

	// [����] �޴��� �޴� �׸��� �����ϸ� �޴� �׸� �´� ������ ������ ���õǵ��� �Ѵ�.
	void CGDIPracticeView::OnUpdateDrawLine(CCmdUI *pCmdUI)
	{
		// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
		pCmdUI->SetCheck(m_nDrawMode == LINE_MODE ? 1 : 0);
	}

	void CGDIPracticeView::OnUpdateDrawRect(CCmdUI *pCmdUI)
	{
		// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
		pCmdUI->SetCheck(m_nDrawMode == RECT_MODE ? 1 : 0);
	}

	void CGDIPracticeView::OnUpdateDrawCircle(CCmdUI *pCmdUI)
	{
		// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
		pCmdUI->SetCheck(m_nDrawMode == CIRCLE_MODE ? 1 : 0);
	}

	void CGDIPracticeView::OnUpdateDrawFree(CCmdUI *pCmdUI)
	{
		// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
		pCmdUI->SetCheck(m_nDrawMode == FREE_MODE ? 1 : 0);
	}

	void CGDIPracticeView::OnUpdateDrawPoly(CCmdUI *pCmdUI)
	{
		// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
		pCmdUI->SetCheck(m_nDrawMode == POLY_MODE ? 1 : 0);
	}

	// �� �޴� �׸� ���ý� Status Bar�� ���õ� �޴��� ǥ�õǵ��� �Ѵ�.
	void CGDIPracticeView::OnDrawLine()
	{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		m_nDrawMode = LINE_MODE;
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		// �׸��� ��� ����� ���ڿ� ����
		CString strDrawMode = (_T("���� �׸���"));
		// ���¹ٿ� �׸��� ��� ���
		pFrame->m_wndStatusBar.SetWindowText(strDrawMode);

	}

	void CGDIPracticeView::OnDrawRect()
	{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		m_nDrawMode = RECT_MODE;
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		// �׸��� ��� ����� ���ڿ� ����
		CString strDrawMode = (_T("�簢�� �׸���"));
		// ���¹ٿ� �׸��� ��� ���
		pFrame->m_wndStatusBar.SetWindowText(strDrawMode);
	}

	void CGDIPracticeView::OnDrawCircle()
	{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		m_nDrawMode = CIRCLE_MODE;
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		// �׸��� ��� ����� ���ڿ� ����
		CString strDrawMode = (_T("�� �׸���"));
		// ���¹ٿ� �׸��� ��� ���
		pFrame->m_wndStatusBar.SetWindowText(strDrawMode);
	}

	void CGDIPracticeView::OnDrawFree()
	{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		m_nDrawMode = FREE_MODE;
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		// �׸��� ��� ����� ���ڿ� ����
		CString strDrawMode = (_T("������ �׸���"));
		// ���¹ٿ� �׸��� ��� ���
		pFrame->m_wndStatusBar.SetWindowText(strDrawMode);
	}

	void CGDIPracticeView::OnDrawPoly()
	{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		m_nDrawMode = POLY_MODE;
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		// �׸��� ��� ����� ���ڿ� ����
		CString strDrawMode = (_T("�ٰ��� �׸���"));
		// ���¹ٿ� �׸��� ��� ���
		pFrame->m_wndStatusBar.SetWindowText(strDrawMode);
	}

	void CGDIPracticeView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		CClientDC dc(this);				//Ŭ���̾�Ʈ ��ü ����

		// Pen ����
		CPen pen, *oldPen;		
		pen.CreatePen(PS_SOLID, m_nPenSize, m_colorPen);	//Pen ��ü ����
		oldPen = dc.SelectObject(&pen);						//Pen ��ü ���	

		dc.SetROP2(R2_NOTXORPEN);			//R2_NOTXORPEN���� ����

		switch(m_nDrawMode)
		{
		case LINE_MODE :						//���� �׸���
			if (m_bLButtonDown)
			{
				dc.MoveTo(m_ptCurr);
				dc.LineTo(m_ptPrev);			//���� ���� ����
				dc.MoveTo(m_ptCurr);
				dc.LineTo(point);				//���� ���� �׸�
				m_ptPrev = point;				//���� ���� ���� ���� ����
			}
			break;

		case CIRCLE_MODE :						//�� �׸���
			if (m_bLButtonDown)
			{
				dc.Ellipse(m_ptCurr.x, m_ptCurr.y, m_ptPrev.x, m_ptPrev.y);
				dc.Ellipse(m_ptCurr.x, m_ptCurr.y, point.x, point.y);
				m_ptPrev = point;				//���� ���� ���� ���� ����
			}
			break;
		case RECT_MODE :						// �簢�� �׸���
			if (m_bLButtonDown)
			{
				dc.Rectangle(m_ptCurr.x, m_ptCurr.y, m_ptPrev.x, m_ptPrev.y);
				dc.Rectangle(m_ptCurr.x, m_ptCurr.y, point.x, point.y);
				m_ptPrev = point;				//���� ���� ���� ���� ����
			}
			break;
		case FREE_MODE :						// ������ �׸���
			if (m_bLButtonDown)
			{
				dc.MoveTo(m_ptPrev);
				dc.LineTo(point);				//���� ���� �׸�
				m_ptPrev = point;				//���� ���� ���� ���� ����
			}
		case POLY_MODE :						// �ٰ��� �׸���
			if (!m_bFirst)
			{
				dc.MoveTo(m_ptCurr);
				dc.LineTo(m_ptPrev);
				dc.MoveTo(m_ptCurr);
				dc.LineTo(point);
				m_ptPrev = point;				//���� ���� ���� ���� ����
			}
			break;
		}
		//���� pen���� ����
		dc.SelectObject(oldPen);	

		//pen ��ü ����
		pen.DeleteObject();						

		// ������������ ������ ����
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

		CString strPoint;
		strPoint.Format(_T("���콺 ��ġ x : %d, y : %d"), point.x, point.y);

		// ���� �߰��� �ҿ� ���콺 ��ġ ���
		pFrame->m_wndStatusBar.SetPaneText(1, strPoint);	


		CView::OnMouseMove(nFlags, point);
	}


	void CGDIPracticeView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

		if (m_bFirst)
		{
			m_ptCurr = m_ptPrev = 0;
			m_bLButtonDown = false;
			m_bFirst = true;
			m_nCount = 0;
			for(int i = 0; i < 50; i++)
				m_ptData[i]=0;
		}

		switch(m_nDrawMode)
		{	
		case LINE_MODE :			//�����׸���
		case CIRCLE_MODE :			//�� �׸���
		case RECT_MODE :			//�簢�� �׸���
		case FREE_MODE :			//������ �׸���
			if (m_bFirst)
			{
				m_bLButtonDown = true; 			//���ʹ�ư�� ����
				m_ptCurr = m_ptPrev = point; 	//�������� ���� ���� ���� ���� ����
				m_bFirst = false;				//ó�� �׸��� �� -> false
				break;
			}
		case POLY_MODE :			//�ٰ��� �׸���
			if (m_bFirst)		
				m_bFirst=false;			//ó�� �׸��� �� -> false
			m_ptCurr = m_ptPrev = point;		//�������� ���� ���� ���� ���� ����
			m_ptData[m_nCount] = point;		//���� ���� ����
			m_nCount++;			//ī��Ʈ ����
			break;
		}


		CView::OnLButtonDown(nFlags, point);
	}


	void CGDIPracticeView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		if (m_bLButtonDown)			//���� ���콺 ��ư�� ���� �����̸�
		{
			//�׸��� ��尡 ���� �׸���, �� �׸��� �̸�
			if(m_nDrawMode != POLY_MODE)
			{
				m_bLButtonDown = false;
				m_bFirst = true;
			}
		}


		CView::OnLButtonUp(nFlags, point);
	}


	void CGDIPracticeView::OnRButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		// �ٰ��� �׸���
		if(m_nDrawMode == POLY_MODE)
		{
			if( !m_bFirst )			// ó�� �׸��� ���� �ƴϸ�
			{	
				// �迭�� ���� ���� �����ϰ� ī��Ʈ ����
				m_ptData[m_nCount] = point;
				m_nCount++;
				// üũ���� �ʱ�ȭ => �ٽ� �ٰ����� �׸��� ����
				m_bFirst = TRUE;

				CClientDC dc(this);				//Ŭ���̾�Ʈ ��ü ����
				// Pen ����
				CPen pen, *oldPen;		
				pen.CreatePen(PS_SOLID, m_nPenSize, m_colorPen);	//Pen ��ü ����
				oldPen = dc.SelectObject(&pen);					//Pen ��ü ���	

				dc.SetROP2(R2_NOTXORPEN);			//R2_NOTXORPEN���� ����

				dc.Polygon(m_ptData, m_nCount);

				//���� pen���� ����
				dc.SelectObject(oldPen);	
				// Pen ���� ����
				pen.DeleteObject();
			}
		}


		CView::OnRButtonDown(nFlags, point);
	}
