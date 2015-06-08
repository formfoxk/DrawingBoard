#pragma once

class CDrawComponent
{
public:
	CDrawComponent(void);
	~CDrawComponent(void);

	// �� ũ�� ���� ����
	int m_nPenSize;

	// �� ���� ���� ����
	COLORREF m_colorPen;

	// ���찳 ũ�� ���� ����
	int m_nEraserSize;
	
	// ������ ���� ���� ����
	int m_nDrawMode;

	// �������� ����(��,��,�簢��)
	CPoint m_ptStart;
	CPoint m_ptEnd;

	// �ٰ���
	CArray<Point, Point> m_points;
};

