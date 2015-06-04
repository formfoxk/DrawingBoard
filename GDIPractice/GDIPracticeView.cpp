
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

	// CGDIPracticeView 생성/소멸

	CGDIPracticeView::CGDIPracticeView()
	{
		// TODO: 여기에 생성 코드를 추가합니다.
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
		// TODO: CREATESTRUCT cs를 수정하여 여기에서
		//  Window 클래스 또는 스타일을 수정합니다.

		return CView::PreCreateWindow(cs);
	}

	// CGDIPracticeView 그리기

	void CGDIPracticeView::OnDraw(CDC* pDC)
	{
		// Pen 설정
		CPen pen, *oldPen;		
		pen.CreatePen(PS_SOLID, m_nPenSize, m_colorPen);	//Pen 객체 생성
		oldPen = pDC->SelectObject(&pen);					//Pen 객체 등록	

		switch(m_nDrawMode)
		{
		case LINE_MODE :					// 직선 그리기
			//마지막 직선 그림
			pDC->MoveTo(m_ptCurr);
			pDC->LineTo(m_ptPrev);
			break;
		case CIRCLE_MODE :					// 원 그리기
			pDC->Ellipse(m_ptCurr.x, m_ptCurr.y, m_ptPrev.x, m_ptPrev.y);
			break;
		case RECT_MODE :					// 사각형 그리기
			pDC->Rectangle(m_ptCurr.x, m_ptCurr.y, m_ptPrev.x, m_ptPrev.y);
			break;
		case POLY_MODE :					// 다각형 그리기
			//배열에 저장한 순서대로 연결해 마지막 다각형 그리기
			pDC->Polygon(m_ptData, m_nCount);
			break;
		}
		//이전 pen으로 설정
		pDC->SelectObject(oldPen);	
		// Pen 객제 제거
		pen.DeleteObject();
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
		CClientDC dc(this);				//클라이언트 객체 얻음

		// Pen 설정
		CPen pen, *oldPen;		
		pen.CreatePen(PS_SOLID, m_nPenSize, m_colorPen);	//Pen 객체 생성
		oldPen = dc.SelectObject(&pen);						//Pen 객체 등록	

		dc.SetROP2(R2_NOTXORPEN);			//R2_NOTXORPEN으로 설정

		switch(m_nDrawMode)
		{
		case LINE_MODE :						//직선 그리기
			if (m_bLButtonDown)
			{
				dc.MoveTo(m_ptCurr);
				dc.LineTo(m_ptPrev);			//이전 직선 지움
				dc.MoveTo(m_ptCurr);
				dc.LineTo(point);				//현재 직선 그림
				m_ptPrev = point;				//이전 점에 현재 점을 저장
			}
			break;

		case CIRCLE_MODE :						//원 그리기
			if (m_bLButtonDown)
			{
				dc.Ellipse(m_ptCurr.x, m_ptCurr.y, m_ptPrev.x, m_ptPrev.y);
				dc.Ellipse(m_ptCurr.x, m_ptCurr.y, point.x, point.y);
				m_ptPrev = point;				//이전 점에 현재 점을 저장
			}
			break;
		case RECT_MODE :						// 사각형 그리기
			if (m_bLButtonDown)
			{
				dc.Rectangle(m_ptCurr.x, m_ptCurr.y, m_ptPrev.x, m_ptPrev.y);
				dc.Rectangle(m_ptCurr.x, m_ptCurr.y, point.x, point.y);
				m_ptPrev = point;				//이전 점에 현재 점을 저장
			}
			break;
		case FREE_MODE :						// 자유선 그리기
			if (m_bLButtonDown)
			{
				dc.MoveTo(m_ptPrev);
				dc.LineTo(point);				//현재 직선 그림
				m_ptPrev = point;				//이전 점에 현재 점을 저장
			}
		case POLY_MODE :						// 다각형 그리기
			if (!m_bFirst)
			{
				dc.MoveTo(m_ptCurr);
				dc.LineTo(m_ptPrev);
				dc.MoveTo(m_ptCurr);
				dc.LineTo(point);
				m_ptPrev = point;				//이전 점에 현재 점을 저장
			}
			break;
		}
		//이전 pen으로 설정
		dc.SelectObject(oldPen);	

		//pen 객체 삭제
		pen.DeleteObject();						

		// 메인프레임의 포인터 얻음
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

		CString strPoint;
		strPoint.Format(_T("마우스 위치 x : %d, y : %d"), point.x, point.y);

		// 새로 추가한 팬에 마우스 위치 출력
		pFrame->m_wndStatusBar.SetPaneText(1, strPoint);	


		CView::OnMouseMove(nFlags, point);
	}


	void CGDIPracticeView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
		case LINE_MODE :			//직선그리기
		case CIRCLE_MODE :			//원 그리기
		case RECT_MODE :			//사각형 그리기
		case FREE_MODE :			//자유선 그리기
			if (m_bFirst)
			{
				m_bLButtonDown = true; 			//왼쪽버튼이 눌림
				m_ptCurr = m_ptPrev = point; 	//시작점과 이전 점에 현재 점을 저장
				m_bFirst = false;				//처음 그리는 것 -> false
				break;
			}
		case POLY_MODE :			//다각형 그리기
			if (m_bFirst)		
				m_bFirst=false;			//처음 그리는 것 -> false
			m_ptCurr = m_ptPrev = point;		//시작점과 이전 점에 현재 점을 저장
			m_ptData[m_nCount] = point;		//현재 점을 저장
			m_nCount++;			//카운트 증가
			break;
		}


		CView::OnLButtonDown(nFlags, point);
	}


	void CGDIPracticeView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		if (m_bLButtonDown)			//왼쪽 마우스 버튼이 눌린 상태이면
		{
			//그리기 모드가 직선 그리기, 원 그리기 이면
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
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		// 다각형 그리기
		if(m_nDrawMode == POLY_MODE)
		{
			if( !m_bFirst )			// 처음 그리는 것이 아니면
			{	
				// 배열에 현재 점을 저장하고 카운트 증가
				m_ptData[m_nCount] = point;
				m_nCount++;
				// 체크변수 초기화 => 다시 다각형을 그리기 위해
				m_bFirst = TRUE;

				CClientDC dc(this);				//클라이언트 객체 얻음
				// Pen 설정
				CPen pen, *oldPen;		
				pen.CreatePen(PS_SOLID, m_nPenSize, m_colorPen);	//Pen 객체 생성
				oldPen = dc.SelectObject(&pen);					//Pen 객체 등록	

				dc.SetROP2(R2_NOTXORPEN);			//R2_NOTXORPEN으로 설정

				dc.Polygon(m_ptData, m_nCount);

				//이전 pen으로 설정
				dc.SelectObject(oldPen);	
				// Pen 객제 제거
				pen.DeleteObject();
			}
		}


		CView::OnRButtonDown(nFlags, point);
	}
