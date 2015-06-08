
// GDIPracticeView.cpp : CGDIPracticeView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
		// 표준 인쇄 명령입니다.
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

	// CGDIPracticeView 생성/소멸

	CGDIPracticeView::CGDIPracticeView()
	{
		// TODO: 여기에 생성 코드를 추가합니다.
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
		// TODO: CREATESTRUCT cs를 수정하여 여기에서
		//  Window 클래스 또는 스타일을 수정합니다.

		return CView::PreCreateWindow(cs);
	}

	// CGDIPracticeView 그리기

	void CGDIPracticeView::OnDraw(CDC* pDC)
	{
		CClientDC dc(this);			//Client DC를 얻는다.

		// Client Rect를 얻는다.
		CRect rClientRect;
		GetClientRect(&rClientRect);

		// Bitmap 생성
		Bitmap mBitmap(rClientRect.Width(), rClientRect.Height());

		// Graphics를 얻는다.
		Graphics graphics(dc);

		// 비트맵을 메모리 내에서 그릴 그래픽 생성
		Graphics memGraphics(&mBitmap);

		// 화면을 흰색 바탕으로 그리기 위한 브러쉬
		SolidBrush drawBrush(Color(255,255,255));

		// 검은색 컬러 지정
		Color drawColor(255,0,0,0);

		// 팬 생성
		Pen drawPen(drawColor, 1);
		drawPen.SetStartCap(LineCapRound);
		drawPen.SetEndCap(LineCapRound);

		// bitmap을 흰색으로 칠한다(line같은 경우 이미지가 남기 때문에)
		memGraphics.FillRectangle(&drawBrush, 0,0,rClientRect.Width(), rClientRect.Height());

		int componentSize = m_components.GetSize();
		CString str;
		str.Format(_T("size : %d\n"), componentSize);
		TRACE(str);
		for (int i = 0; i < componentSize; i++)
		{
			// 컴포넌트의 팬 설정
			drawColor.SetFromCOLORREF(m_components.GetAt(i)->m_colorPen);
			drawPen.SetColor(drawColor);
			drawPen.SetWidth((float)m_components.GetAt(i)->m_nPenSize);

			// 얕은 복사
			CDrawComponent *component = m_components.GetAt(i);

			switch (component->m_nDrawMode)
			{
				// 지우개인 경우
			case DRAW_NONE:
				{
					// 팬의 브러쉬 색을 흰색으로 변경
					drawBrush.SetColor(drawColor);

					// 지우개를 사용한 좌표를 순차적으로 다시 그린다.
					int pointSize = component->m_points.GetSize();
					for (int j = 0; j < pointSize; j++)
					{
						// 흰색의 지우개 사각형을 그린다. 
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
				// 우측 아래
				if(component->m_ptStart.x < component->m_ptEnd.x && component->m_ptStart.y < component->m_ptEnd.y)
					memGraphics.DrawRectangle(&drawPen, component->m_ptStart.x, component->m_ptStart.y,
					component->m_ptEnd.x - component->m_ptStart.x, component->m_ptEnd.y - component->m_ptStart.y);
				// 우측 위
				else if(component->m_ptStart.x < component->m_ptEnd.x && component->m_ptStart.y > component->m_ptEnd.y)
					memGraphics.DrawRectangle(&drawPen, component->m_ptStart.x, component->m_ptEnd.y,
					component->m_ptEnd.x - component->m_ptStart.x, component->m_ptStart.y - component->m_ptEnd.y);
				// 좌측 아래
				else if(component->m_ptStart.x > component->m_ptEnd.x && component->m_ptStart.y < component->m_ptEnd.y)
					memGraphics.DrawRectangle(&drawPen, component->m_ptEnd.x, component->m_ptStart.y,
					component->m_ptStart.x - component->m_ptEnd.x, component->m_ptEnd.y - component->m_ptStart.y);
				// 좌측 위
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
					// 자유선의 작은 선들을을 순차적으로 하나씩 그린다.
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

				// 처음 점과 마지막점을 이어준다.
				memGraphics.DrawLine(&drawPen, component->m_points.GetAt(component->m_points.GetSize() - 1).X,
					component->m_points.GetAt(component->m_points.GetSize() - 1).Y,
					component->m_points.GetAt(0).X, component->m_points.GetAt(0).Y);

				break;
			}
			default:
				break;
			}
		}

		//현재 그리고 있는 것

		drawColor.SetFromCOLORREF(m_colorPen);
		drawPen.SetColor(drawColor);
		drawPen.SetWidth(m_nPenSize);

		// 왼쪽 버튼 클릭시 || 지우개인경우 | 다각형인 경우(삭제)
		if (m_nDrawMode == DRAW_NONE || m_nDrawMode == POLY_MODE || m_bLButtonDown)
		{
			switch (m_nDrawMode)
			{
			case DRAW_NONE:
				{
					// 브러쉬 흰색 설정
					drawColor.SetFromCOLORREF(RGB(255, 255, 255));
					drawBrush.SetColor(drawColor);
					// 팬 컬러 검정색 설정
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

				// 우측 아래
				if(m_ptPrev.x < m_ptDrawing.x && m_ptPrev.y < m_ptDrawing.y)
					memGraphics.DrawRectangle(&drawPen, m_ptPrev.x, m_ptPrev.y,
					m_ptDrawing.x - m_ptPrev.x, m_ptDrawing.y - m_ptPrev.y);
				// 우측 위
				else if(m_ptPrev.x < m_ptDrawing.x && m_ptPrev.y > m_ptDrawing.y)
					memGraphics.DrawRectangle(&drawPen, m_ptPrev.x, m_ptDrawing.y,
					m_ptDrawing.x - m_ptPrev.x, m_ptPrev.y - m_ptDrawing.y);
				// 좌측 아래
				else if(m_ptPrev.x > m_ptDrawing.x && m_ptPrev.y < m_ptDrawing.y)
					memGraphics.DrawRectangle(&drawPen, m_ptDrawing.x, m_ptPrev.y,
					m_ptPrev.x - m_ptDrawing.x, m_ptDrawing.y - m_ptPrev.y);
				// 좌측 위
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

					// 처음 점과 마지막점을 이어준다.
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

	// CGDIPracticeView 인쇄
	BOOL CGDIPracticeView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 기본적인 준비
		return DoPreparePrinting(pInfo);
	}

	void CGDIPracticeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
	}

	void CGDIPracticeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄 후 정리 작업을 추가합니다.
	}


	// CGDIPracticeView 진단

#ifdef _DEBUG
	void CGDIPracticeView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CGDIPracticeView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CGDIPracticeDoc* CGDIPracticeView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIPracticeDoc)));
		return (CGDIPracticeDoc*)m_pDocument;
	}
#endif //_DEBUG

	// CGDIPracticeView 메시지 처리기
	
	void CGDIPracticeView::OnFileNew()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		m_components.RemoveAll();
		newFileDown = true;
		Invalidate(false);
	}

	void CGDIPracticeView::OnPenSize()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		CDlgPen *pdlgPen = new CDlgPen;
		if (pdlgPen->DoModal() == IDOK) {
			m_nPenSize = pdlgPen->m_nPenSize;
		}

	}

	void CGDIPracticeView::OnEraserSize()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		CDlgEraser *pdlgEraser = new CDlgEraser;
		if (pdlgEraser->DoModal() == IDOK) {
			m_nEraserSize = pdlgEraser->m_nEraserSize;
		}

	}

	void CGDIPracticeView::OnPenColor()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		CColorDialog crDlg;
		if (crDlg.DoModal() == IDOK) {
			m_colorPen = crDlg.GetColor();
		}
	}

	// [도형] 메뉴의 메뉴 항목을 선택하면 메뉴 항목에 맞는 도형의 종류가 선택되도록 한다.
	void CGDIPracticeView::OnUpdateDrawLine(CCmdUI *pCmdUI)
	{
		// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
		pCmdUI->SetCheck(m_nDrawMode == LINE_MODE ? 1 : 0);
	}

	void CGDIPracticeView::OnUpdateDrawRect(CCmdUI *pCmdUI)
	{
		// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
		pCmdUI->SetCheck(m_nDrawMode == RECT_MODE ? 1 : 0);
	}

	void CGDIPracticeView::OnUpdateDrawCircle(CCmdUI *pCmdUI)
	{
		// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
		pCmdUI->SetCheck(m_nDrawMode == CIRCLE_MODE ? 1 : 0);
	}

	void CGDIPracticeView::OnUpdateDrawFree(CCmdUI *pCmdUI)
	{
		// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
		pCmdUI->SetCheck(m_nDrawMode == FREE_MODE ? 1 : 0);
	}

	void CGDIPracticeView::OnUpdateDrawPoly(CCmdUI *pCmdUI)
	{
		// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
		pCmdUI->SetCheck(m_nDrawMode == POLY_MODE ? 1 : 0);
	}

	// 각 메뉴 항목 선택시 Status Bar에 선택된 메뉴가 표시되도록 한다.
	void CGDIPracticeView::OnDrawLine()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		m_nDrawMode = LINE_MODE;
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		// 그리기 모드 출력할 문자열 생성
		CString strDrawMode = (_T("직선 그리기"));
		// 상태바에 그리기 모드 출력
		pFrame->m_wndStatusBar.SetWindowText(strDrawMode);

	}

	void CGDIPracticeView::OnDrawRect()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		m_nDrawMode = RECT_MODE;
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		// 그리기 모드 출력할 문자열 생성
		CString strDrawMode = (_T("사각형 그리기"));
		// 상태바에 그리기 모드 출력
		pFrame->m_wndStatusBar.SetWindowText(strDrawMode);
	}

	void CGDIPracticeView::OnDrawCircle()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		m_nDrawMode = CIRCLE_MODE;
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		// 그리기 모드 출력할 문자열 생성
		CString strDrawMode = (_T("원 그리기"));
		// 상태바에 그리기 모드 출력
		pFrame->m_wndStatusBar.SetWindowText(strDrawMode);
	}

	void CGDIPracticeView::OnDrawFree()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		m_nDrawMode = FREE_MODE;
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		// 그리기 모드 출력할 문자열 생성
		CString strDrawMode = (_T("자유선 그리기"));
		// 상태바에 그리기 모드 출력
		pFrame->m_wndStatusBar.SetWindowText(strDrawMode);
	}

	void CGDIPracticeView::OnDrawPoly()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		m_nDrawMode = POLY_MODE;
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		// 그리기 모드 출력할 문자열 생성
		CString strDrawMode = (_T("다각형 그리기"));
		// 상태바에 그리기 모드 출력
		pFrame->m_wndStatusBar.SetWindowText(strDrawMode);
	}

	void CGDIPracticeView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		m_ptDrawing = point;

		// 자유선인 경우
		if (m_bLButtonDown && m_nDrawMode == FREE_MODE)
			m_points.Add(Point(point.x,point.y));

		// 지우개 인 경우
		if (m_nDrawMode == DRAW_NONE)
		{
			m_ptPrev = CPoint(point.x - (m_nEraserSize), point.y - (m_nEraserSize));
			m_points.Add(Point(m_ptPrev.x, m_ptPrev.y));
		}

		// 상태바에 현재 좌표 출력
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		CString strMousePos;
		strMousePos.Format(_T("x : %d, y : %d"), point.x, point.y);
		pFrame->m_wndStatusBar.SetPaneText(4, strMousePos);

		Invalidate(false);

		CView::OnMouseMove(nFlags, point);
	}


	void CGDIPracticeView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		// 그림을 지우는 경우
		if (m_nDrawMode == DRAW_NONE) return;

		// 자유선 또는 다각형인 경우
		if (m_nDrawMode == FREE_MODE || m_nDrawMode == POLY_MODE)
			m_points.Add(Point(point.x, point.y));

		// 현재 마우스의 좌표 저장
		m_ptPrev= point;
		m_ptDrawing = point;

		// 왼쪽 버튼 클릭 참
		m_bLButtonDown = true;

		Invalidate(false);
		CView::OnLButtonDown(nFlags, point);
	}


	void CGDIPracticeView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		// 그림을 지우는 경우
		if (m_nDrawMode == DRAW_NONE) return;
		
			// 왼쪽 버튼이 눌러진 경우
			m_bLButtonDown = false;
		// 다각형이 아닌 경우
		if (m_nDrawMode != POLY_MODE)
		{

			// 현재 좌표 저장
			m_ptCurr = point;

			// 그림요소 생성
			CDrawComponent *component = new CDrawComponent;
			component->m_nPenSize = m_nPenSize;
			component->m_colorPen = m_colorPen;
			component->m_nEraserSize = m_nEraserSize;
			component->m_nDrawMode = m_nDrawMode;
			component->m_ptStart = m_ptPrev;
			component->m_ptEnd = m_ptCurr;
			component->m_points.Copy(m_points);

			// 그림 구성요소들에 추가
			m_components.Add(component);

			// 좌표들 모두 삭제
			m_points.RemoveAll();
		}

		Invalidate(false);
		CView::OnLButtonUp(nFlags, point);
	}
	
	void CGDIPracticeView::OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		// 왼쪽 버튼 클릭 거짓으로 변경
		m_bLButtonDown = false;

		// 그림요소 생성
		CDrawComponent *component = new CDrawComponent;
		component->m_nPenSize = m_nPenSize;
		component->m_colorPen = m_colorPen;
		component->m_nEraserSize = m_nEraserSize;
		component->m_nDrawMode = m_nDrawMode;
		component->m_ptStart = m_ptPrev;
		component->m_ptEnd = m_ptCurr;
		component->m_points.Copy(m_points);

		// 그림 구성요소들에 추가
		m_components.Add(component);

		// 좌표들 모두 삭제
		m_points.RemoveAll();

		Invalidate(false);

		CView::OnLButtonDblClk(nFlags, point);
	}

	void CGDIPracticeView::OnRButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		// 왼쪽버튼이 눌러진 경우
		if (m_bLButtonDown) return;
		
		// 이전 그림 모드 저장
		m_nPrevDrawMode = m_nDrawMode;

		// 지우개 모드 전환
		m_nDrawMode = DRAW_NONE;

		// 현재 좌표 저장(지우개 사각형을 그리기 위해 지우개 사이즈만큼 좌표를 차감해서 저장)
		m_ptPrev = CPoint(point.x - (m_nEraserSize), point.y - (m_nEraserSize));

		// 현재 좌표 저장
		m_points.Add(Point(m_ptPrev.x, m_ptPrev.y));

		Invalidate(false);
		CView::OnRButtonDown(nFlags, point);
	}

	void CGDIPracticeView::OnRButtonUp(UINT nFlags, CPoint point)
	{
		// 왼쪽버튼이 눌러진 경우
		if (m_bLButtonDown) return;

		// 왼쪽버튼이 눌러지기 전의 그림모드로 변경
		m_nDrawMode = m_nPrevDrawMode;
	
		// 현재 좌표 저장(지우개 사각형을 그리기 위해 지우개 사이즈만큼 좌표를 차감해서 저장)
		m_ptPrev = CPoint(point.x - (m_nEraserSize), point.y - (m_nEraserSize));

		CDrawComponent * component = new CDrawComponent;
		component->m_colorPen = RGB(255, 255, 255);
		component->m_nEraserSize = m_nEraserSize;
		component->m_nDrawMode = DRAW_NONE;
		component->m_ptStart = m_ptPrev;
		component->m_points.Copy(m_points);

		// 그림 구성요소들에 추가
		m_components.Add(component);

		// 좌표들 모두 삭제
		m_points.RemoveAll();

		Invalidate(false);
		CView::OnRButtonUp(nFlags, point);
	}





