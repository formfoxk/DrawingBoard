#pragma once

class CDrawComponent
{
public:
	CDrawComponent(void);
	~CDrawComponent(void);

	// 팬 크기 조절 변수
	int m_nPenSize;

	// 팬 색상 변경 변수
	COLORREF m_colorPen;

	// 지우개 크기 조절 변수
	int m_nEraserSize;
	
	// 도형의 종류 저장 변수
	int m_nDrawMode;

	// 시작점과 끝점(선,원,사각형)
	CPoint m_ptStart;
	CPoint m_ptEnd;

	// 다각형
	CArray<Point, Point> m_points;
};

