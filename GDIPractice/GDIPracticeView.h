
// GDIPracticeView.h : CGDIPracticeView 클래스의 인터페이스
//

#pragma once
#include "atltypes.h"
#include "CDlgPen.h"
#include "CDlgEraser.h"
#include "MainFrm.h"
#include "CDrawComponent.h"

class CGDIPracticeView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGDIPracticeView();
	DECLARE_DYNCREATE(CGDIPracticeView)

// 특성입니다.
public:
	CGDIPracticeDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGDIPracticeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

// 사용자 멤버 변수
private:
	// 도형의 종류를 지정하기 위한 열거형 상수를 생성한다.
	enum DRAW{DRAW_NONE, LINE_MODE, RECT_MODE, CIRCLE_MODE, FREE_MODE, POLY_MODE};

	// 도형의 종류 변수
	int m_nDrawMode;

	// 이전 도형의 종류 변수
	int m_nPrevDrawMode;

	// 팬 크기 조절 변수
	int m_nPenSize;

	// 팬 색상 변경 변수
	COLORREF m_colorPen;

	// 지우개 크기 조절 변수
	int m_nEraserSize;
	
	// 버튼이 한번 클릭되었는지 확인하는 변수
	bool m_bFirst;

	// 왼쪽 마우스 버튼을 클릭했는지 확인하는 변수
	bool m_bLButtonDown;

	// 모든 도형 요소들이 저장되는 배열
	CArray<CDrawComponent*, CDrawComponent*> m_components;

	// 다각형,자유선,지우개 좌표로 사용하는 포인트 배열
	CArray<Point, Point> m_points;

	// 도형 그리기 위한 현재와 이전의 좌표 저장 변수
	CPoint m_ptPrev;
	CPoint m_ptCurr;

	// 현재 그리고 있는 좌표
	CPoint m_ptDrawing;

	bool newFileDown;
public:
	// 메시지 처리 함수
	afx_msg void OnPenSize();
	afx_msg void OnPenColor();
	afx_msg void OnEraserSize();

	// [도형] 메뉴의 메뉴 항목을 선택하면 메뉴 항목에 맞는 도형의 종류가 선택되도록 한다.
	afx_msg void OnUpdateDrawLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawRect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawFree(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawPoly(CCmdUI *pCmdUI);

	// 각 메뉴 항목 선택시 Status Bar에 선택된 메뉴가 표시되도록 한다.
	afx_msg void OnDrawLine();
	afx_msg void OnDrawRect();
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawFree();
	afx_msg void OnDrawPoly();
	
	// 마우스 이동 메시지 핸들러 함수를 구현 
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	// 왼쪽 마우스가 눌러졌을 때 메시지 핸들러 함수
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	// 오른쪽 마우스가 눌러졌을 때 메시지 핸들러 함수
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnFileNew();
};

#ifndef _DEBUG  // GDIPracticeView.cpp의 디버그 버전
inline CGDIPracticeDoc* CGDIPracticeView::GetDocument() const
   { return reinterpret_cast<CGDIPracticeDoc*>(m_pDocument); }
#endif

