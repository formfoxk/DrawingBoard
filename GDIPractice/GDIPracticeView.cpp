
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
		ON_COMMAND(ID_FILE_NEW, &CGDIPracticeView::OnFileNew)
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

		ON_WM_LBUTTONDBLCLK()
		ON_WM_RBUTTONUP()
		
	END_MESSAGE_MAP()

	// CGDIPracticeView ����/�Ҹ�

	CGDIPracticeView::CGDIPracticeView()
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
		m_nPenSize = 1;
		m_colorPen = RGB(0,0,0); 
		m_nDrawMode =  POLY_MODE;
		m_nEraserSize = 2;
		m_bLButtonDown = false;
		newFileDown = false;
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
		CClientDC dc(this);			//Client DC�� ��´�.

		// Client Rect�� ��´�.
		CRect rClientRect;
		GetClientRect(&rClientRect);

		// Bitmap ����
		Bitmap mBitmap(rClientRect.Width(), rClientRect.Height());

		// Graphics�� ��´�.
		Graphics graphics(dc);

		// ��Ʈ���� �޸� ������ �׸� �׷��� ����
		Graphics memGraphics(&mBitmap);

		// ȭ���� ��� �������� �׸��� ���� �귯��
		SolidBrush drawBrush(Color(255,255,255));

		// ������ �÷� ����
		Color drawColor(255,0,0,0);

		// �� ����
		Pen drawPen(drawColor, 1);
		drawPen.SetStartCap(LineCapRound);
		drawPen.SetEndCap(LineCapRound);

		// bitmap�� ������� ĥ�Ѵ�(line���� ��� �̹����� ���� ������)
		memGraphics.FillRectangle(&drawBrush, 0,0,rClientRect.Width(), rClientRect.Height());

		int componentSize = m_components.GetSize();
		CString str;
		str.Format(_T("size : %d\n"), componentSize);
		TRACE(str);
		for (int i = 0; i < componentSize; i++)
		{
			// ������Ʈ�� �� ����
			drawColor.SetFromCOLORREF(m_components.GetAt(i)->m_colorPen);
			drawPen.SetColor(drawColor);
			drawPen.SetWidth((float)m_components.GetAt(i)->m_nPenSize);

			// ���� ����
			CDrawComponent *component = m_components.GetAt(i);

			switch (component->m_nDrawMode)
			{
				// ���찳�� ���
			case DRAW_NONE:
				{
					// ���� �귯�� ���� ������� ����
					drawBrush.SetColor(drawColor);

					// ���찳�� ����� ��ǥ�� ���������� �ٽ� �׸���.
					int pointSize = component->m_points.GetSize();
					for (int j = 0; j < pointSize; j++)
					{
						// ����� ���찳 �簢���� �׸���. 
						memGraphics.FillRectangle(&drawBrush, component->m_points.GetAt(j).X, component->m_points.GetAt(j).Y,
							component->m_nEraserSize * 2, component->m_nEraserSize * 2);
					}
					break;
				}
			case LINE_MODE:
				memGraphics.DrawLine(&drawPen, component->m_ptStart.x, component->m_ptStart.y,
					component->m_ptEnd.x, component->m_ptEnd.y);
				break;
			case RECT_MODE:
			{
				// ���� �Ʒ�
				if(component->m_ptStart.x < component->m_ptEnd.x && component->m_ptStart.y < component->m_ptEnd.y)
					memGraphics.DrawRectangle(&drawPen, component->m_ptStart.x, component->m_ptStart.y,
					component->m_ptEnd.x - component->m_ptStart.x, component->m_ptEnd.y - component->m_ptStart.y);
				// ���� ��
				else if(component->m_ptStart.x < component->m_ptEnd.x && component->m_ptStart.y > component->m_ptEnd.y)
					memGraphics.DrawRectangle(&drawPen, component->m_ptStart.x, component->m_ptEnd.y,
					component->m_ptEnd.x - component->m_ptStart.x, component->m_ptStart.y - component->m_ptEnd.y);
				// ���� �Ʒ�
				else if(component->m_ptStart.x > component->m_ptEnd.x && component->m_ptStart.y < component->m_ptEnd.y)
					memGraphics.DrawRectangle(&drawPen, component->m_ptEnd.x, component->m_ptStart.y,
					component->m_ptStart.x - component->m_ptEnd.x, component->m_ptEnd.y - component->m_ptStart.y);
				// ���� ��
				else
					memGraphics.DrawRectangle(&drawPen, component->m_ptEnd.x, component->m_ptEnd.y,
					component->m_ptStart.x - component->m_ptEnd.x, component->m_ptStart.y - component->m_ptEnd.y);

				break;
			}
			case CIRCLE_MODE:
				memGraphics.DrawEllipse(&drawPen, component->m_ptStart.x, component->m_ptStart.y,
					component->m_ptEnd.x - component->m_ptStart.x, component->m_ptEnd.y - component->m_ptStart.y);
				break;
			case FREE_MODE:
				if (component->m_points.GetSize() > 1)
				{
					// �������� ���� �������� ���������� �ϳ��� �׸���.
					int pointSize = component->m_points.GetSize();
					for (int j = 1; j < pointSize; j++)
						memGraphics.DrawLine(&drawPen, component->m_points.GetAt(j - 1).X, component->m_points.GetAt(j - 1).Y,
						component->m_points.GetAt(j).X, component->m_points.GetAt(j).Y);
				}
				break;
			case POLY_MODE:
			{
				int pointSize = component->m_points.GetSize();
				for (int j = 1; j < pointSize; j++)
					memGraphics.DrawLine(&drawPen, component->m_points.GetAt(j-1).X, component->m_points.GetAt(j-1).Y,
					component->m_points.GetAt(j).X, component->m_points.GetAt(j).Y);

				// ó�� ���� ���������� �̾��ش�.
				memGraphics.DrawLine(&drawPen, component->m_points.GetAt(component->m_points.GetSize() - 1).X,
					component->m_points.GetAt(component->m_points.GetSize() - 1).Y,
					component->m_points.GetAt(0).X, component->m_points.GetAt(0).Y);

				break;
			}
			default:
				break;
			}
		}

		//���� �׸��� �ִ� ��

		drawColor.SetFromCOLORREF(m_colorPen);
		drawPen.SetColor(drawColor);
		drawPen.SetWidth(m_nPenSize);

		// ���� ��ư Ŭ���� || ���찳�ΰ�� | �ٰ����� ���(����)
		if (m_nDrawMode == DRAW_NONE || m_nDrawMode == POLY_MODE || m_bLButtonDown)
		{
			switch (m_nDrawMode)
			{
			case DRAW_NONE:
				{
					// �귯�� ��� ����
					drawColor.SetFromCOLORREF(RGB(255, 255, 255));
					drawBrush.SetColor(drawColor);
					// �� �÷� ������ ����
					drawColor.SetFromCOLORREF(RGB(0, 0, 0));
					drawPen.SetColor(drawColor);
					drawPen.SetWidth(1);

					int pointSize = m_points.GetSize()-1;
					for (int i = 0; i < pointSize; i++)
					{
						memGraphics.FillRectangle(&drawBrush, m_points.GetAt(i).X, m_points.GetAt(i).Y,
							m_nEraserSize * 2, m_nEraserSize * 2);
					}
					memGraphics.FillRectangle(&drawBrush, m_points.GetAt(m_points.GetSize() - 1).X, m_points.GetAt(m_points.GetSize() - 1).Y,
						m_nEraserSize * 2, m_nEraserSize * 2);
					memGraphics.DrawRectangle(&drawPen, m_points.GetAt(m_points.GetSize() - 1).X, m_points.GetAt(m_points.GetSize() - 1).Y,
						m_nEraserSize * 2, m_nEraserSize * 2);

					break;
				}
			case LINE_MODE:
				memGraphics.DrawLine(&drawPen, m_ptPrev.x, m_ptPrev.y,
					m_ptDrawing.x, m_ptDrawing.y);
				break;
			case RECT_MODE:
			{
				memGraphics.DrawRectangle(&drawPen, m_ptPrev.x, m_ptPrev.y,
					m_ptDrawing.x - m_ptPrev.x, m_ptDrawing.y - m_ptPrev.y);

				// ���� �Ʒ�
				if(m_ptPrev.x < m_ptDrawing.x && m_ptPrev.y < m_ptDrawing.y)
					memGraphics.DrawRectangle(&drawPen, m_ptPrev.x, m_ptPrev.y,
					m_ptDrawing.x - m_ptPrev.x, m_ptDrawing.y - m_ptPrev.y);
				// ���� ��
				else if(m_ptPrev.x < m_ptDrawing.x && m_ptPrev.y > m_ptDrawing.y)
					memGraphics.DrawRectangle(&drawPen, m_ptPrev.x, m_ptDrawing.y,
					m_ptDrawing.x - m_ptPrev.x, m_ptPrev.y - m_ptDrawing.y);
				// ���� �Ʒ�
				else if(m_ptPrev.x > m_ptDrawing.x && m_ptPrev.y < m_ptDrawing.y)
					memGraphics.DrawRectangle(&drawPen, m_ptDrawing.x, m_ptPrev.y,
					m_ptPrev.x - m_ptDrawing.x, m_ptDrawing.y - m_ptPrev.y);
				// ���� ��
				else
					memGraphics.DrawRectangle(&drawPen, m_ptDrawing.x, m_ptDrawing.y,
					m_ptPrev.x - m_ptDrawing.x, m_ptPrev.y - m_ptDrawing.y);

				break;
			}
			case CIRCLE_MODE:
				memGraphics.DrawEllipse(&drawPen, m_ptPrev.x, m_ptPrev.y,
					m_ptDrawing.x - m_ptPrev.x, m_ptDrawing.y - m_ptPrev.y);
				break;
			case FREE_MODE:
				if (m_points.GetSize() > 1)
				{
					for (int i = 1; i < m_points.GetSize(); i++)
						memGraphics.DrawLine(&drawPen, m_points.GetAt(i - 1).X, m_points.GetAt(i - 1).Y,
						m_points.GetAt(i).X, m_points.GetAt(i).Y);
				}
				break;
			case POLY_MODE:
				if (m_points.GetSize() > 1)
				{
					for (int i = 1; i < m_points.GetSize(); i++)
						memGraphics.DrawLine(&drawPen, m_points.GetAt(i-1).X, m_points.GetAt(i-1).Y,
						m_points.GetAt(i).X, m_points.GetAt(i).Y);

					// ó�� ���� ���������� �̾��ش�.
					memGraphics.DrawLine(&drawPen, m_points.GetAt(m_points.GetSize() - 1).X, m_points.GetAt(m_points.GetSize() - 1).Y,
						m_ptDrawing.x, m_ptDrawing.y);
				}
				else if (m_points.GetSize() == 1)
					memGraphics.DrawLine(&drawPen, m_points.GetAt(0).X, m_points.GetAt(0).Y, m_ptDrawing.x, m_ptDrawing.y);
				break;
			default:
				break;
			}
		}
		graphics.DrawImage(&mBitmap, 0, 0);
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
	
	void CGDIPracticeView::OnFileNew()
	{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		m_components.RemoveAll();
		newFileDown = true;
		Invalidate(false);
	}

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
		m_ptDrawing = point;

		// �������� ���
		if (m_bLButtonDown && m_nDrawMode == FREE_MODE)
			m_points.Add(Point(point.x,point.y));

		// ���찳 �� ���
		if (m_nDrawMode == DRAW_NONE)
		{
			m_ptPrev = CPoint(point.x - (m_nEraserSize), point.y - (m_nEraserSize));
			m_points.Add(Point(m_ptPrev.x, m_ptPrev.y));
		}

		// ���¹ٿ� ���� ��ǥ ���
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		CString strMousePos;
		strMousePos.Format(_T("x : %d, y : %d"), point.x, point.y);
		pFrame->m_wndStatusBar.SetPaneText(4, strMousePos);

		Invalidate(false);

		CView::OnMouseMove(nFlags, point);
	}


	void CGDIPracticeView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		// �׸��� ����� ���
		if (m_nDrawMode == DRAW_NONE) return;

		// ������ �Ǵ� �ٰ����� ���
		if (m_nDrawMode == FREE_MODE || m_nDrawMode == POLY_MODE)
			m_points.Add(Point(point.x, point.y));

		// ���� ���콺�� ��ǥ ����
		m_ptPrev= point;
		m_ptDrawing = point;

		// ���� ��ư Ŭ�� ��
		m_bLButtonDown = true;

		Invalidate(false);
		CView::OnLButtonDown(nFlags, point);
	}


	void CGDIPracticeView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		// �׸��� ����� ���
		if (m_nDrawMode == DRAW_NONE) return;
		
			// ���� ��ư�� ������ ���
			m_bLButtonDown = false;
		// �ٰ����� �ƴ� ���
		if (m_nDrawMode != POLY_MODE)
		{

			// ���� ��ǥ ����
			m_ptCurr = point;

			// �׸���� ����
			CDrawComponent *component = new CDrawComponent;
			component->m_nPenSize = m_nPenSize;
			component->m_colorPen = m_colorPen;
			component->m_nEraserSize = m_nEraserSize;
			component->m_nDrawMode = m_nDrawMode;
			component->m_ptStart = m_ptPrev;
			component->m_ptEnd = m_ptCurr;
			component->m_points.Copy(m_points);

			// �׸� ������ҵ鿡 �߰�
			m_components.Add(component);

			// ��ǥ�� ��� ����
			m_points.RemoveAll();
		}

		Invalidate(false);
		CView::OnLButtonUp(nFlags, point);
	}
	
	void CGDIPracticeView::OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		// ���� ��ư Ŭ�� �������� ����
		m_bLButtonDown = false;

		// �׸���� ����
		CDrawComponent *component = new CDrawComponent;
		component->m_nPenSize = m_nPenSize;
		component->m_colorPen = m_colorPen;
		component->m_nEraserSize = m_nEraserSize;
		component->m_nDrawMode = m_nDrawMode;
		component->m_ptStart = m_ptPrev;
		component->m_ptEnd = m_ptCurr;
		component->m_points.Copy(m_points);

		// �׸� ������ҵ鿡 �߰�
		m_components.Add(component);

		// ��ǥ�� ��� ����
		m_points.RemoveAll();

		Invalidate(false);

		CView::OnLButtonDblClk(nFlags, point);
	}

	void CGDIPracticeView::OnRButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

		// ���ʹ�ư�� ������ ���
		if (m_bLButtonDown) return;
		
		// ���� �׸� ��� ����
		m_nPrevDrawMode = m_nDrawMode;

		// ���찳 ��� ��ȯ
		m_nDrawMode = DRAW_NONE;

		// ���� ��ǥ ����(���찳 �簢���� �׸��� ���� ���찳 �����ŭ ��ǥ�� �����ؼ� ����)
		m_ptPrev = CPoint(point.x - (m_nEraserSize), point.y - (m_nEraserSize));

		// ���� ��ǥ ����
		m_points.Add(Point(m_ptPrev.x, m_ptPrev.y));

		Invalidate(false);
		CView::OnRButtonDown(nFlags, point);
	}

	void CGDIPracticeView::OnRButtonUp(UINT nFlags, CPoint point)
	{
		// ���ʹ�ư�� ������ ���
		if (m_bLButtonDown) return;

		// ���ʹ�ư�� �������� ���� �׸����� ����
		m_nDrawMode = m_nPrevDrawMode;
	
		// ���� ��ǥ ����(���찳 �簢���� �׸��� ���� ���찳 �����ŭ ��ǥ�� �����ؼ� ����)
		m_ptPrev = CPoint(point.x - (m_nEraserSize), point.y - (m_nEraserSize));

		CDrawComponent * component = new CDrawComponent;
		component->m_colorPen = RGB(255, 255, 255);
		component->m_nEraserSize = m_nEraserSize;
		component->m_nDrawMode = DRAW_NONE;
		component->m_ptStart = m_ptPrev;
		component->m_points.Copy(m_points);

		// �׸� ������ҵ鿡 �߰�
		m_components.Add(component);

		// ��ǥ�� ��� ����
		m_points.RemoveAll();

		Invalidate(false);
		CView::OnRButtonUp(nFlags, point);
	}





