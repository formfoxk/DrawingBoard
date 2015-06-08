
// GDIPracticeView.h : CGDIPracticeView Ŭ������ �������̽�
//

#pragma once
#include "atltypes.h"
#include "CDlgPen.h"
#include "CDlgEraser.h"
#include "MainFrm.h"
#include "CDrawComponent.h"

class CGDIPracticeView : public CView
{
protected: // serialization������ ��������ϴ�.
	CGDIPracticeView();
	DECLARE_DYNCREATE(CGDIPracticeView)

// Ư���Դϴ�.
public:
	CGDIPracticeDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CGDIPracticeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

// ����� ��� ����
private:
	// ������ ������ �����ϱ� ���� ������ ����� �����Ѵ�.
	enum DRAW{DRAW_NONE, LINE_MODE, RECT_MODE, CIRCLE_MODE, FREE_MODE, POLY_MODE};

	// ������ ���� ����
	int m_nDrawMode;

	// ���� ������ ���� ����
	int m_nPrevDrawMode;

	// �� ũ�� ���� ����
	int m_nPenSize;

	// �� ���� ���� ����
	COLORREF m_colorPen;

	// ���찳 ũ�� ���� ����
	int m_nEraserSize;
	
	// ��ư�� �ѹ� Ŭ���Ǿ����� Ȯ���ϴ� ����
	bool m_bFirst;

	// ���� ���콺 ��ư�� Ŭ���ߴ��� Ȯ���ϴ� ����
	bool m_bLButtonDown;

	// ��� ���� ��ҵ��� ����Ǵ� �迭
	CArray<CDrawComponent*, CDrawComponent*> m_components;

	// �ٰ���,������,���찳 ��ǥ�� ����ϴ� ����Ʈ �迭
	CArray<Point, Point> m_points;

	// ���� �׸��� ���� ����� ������ ��ǥ ���� ����
	CPoint m_ptPrev;
	CPoint m_ptCurr;

	// ���� �׸��� �ִ� ��ǥ
	CPoint m_ptDrawing;

	bool newFileDown;
public:
	// �޽��� ó�� �Լ�
	afx_msg void OnPenSize();
	afx_msg void OnPenColor();
	afx_msg void OnEraserSize();

	// [����] �޴��� �޴� �׸��� �����ϸ� �޴� �׸� �´� ������ ������ ���õǵ��� �Ѵ�.
	afx_msg void OnUpdateDrawLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawRect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawFree(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawPoly(CCmdUI *pCmdUI);

	// �� �޴� �׸� ���ý� Status Bar�� ���õ� �޴��� ǥ�õǵ��� �Ѵ�.
	afx_msg void OnDrawLine();
	afx_msg void OnDrawRect();
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawFree();
	afx_msg void OnDrawPoly();
	
	// ���콺 �̵� �޽��� �ڵ鷯 �Լ��� ���� 
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	// ���� ���콺�� �������� �� �޽��� �ڵ鷯 �Լ�
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	// ������ ���콺�� �������� �� �޽��� �ڵ鷯 �Լ�
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnFileNew();
};

#ifndef _DEBUG  // GDIPracticeView.cpp�� ����� ����
inline CGDIPracticeDoc* CGDIPracticeView::GetDocument() const
   { return reinterpret_cast<CGDIPracticeDoc*>(m_pDocument); }
#endif

