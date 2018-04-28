#pragma once
#include <cliext/vector>

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;			//��� �������� DashStyle
using namespace cliext;
using namespace System::Runtime::Serialization;

namespace Sketcher
{
	[Serializable]
	public ref class Element abstract
	{
	protected:
		[NonSerialized]
		Pen^ pen;
		float penWidth;			//����� ��������� ���������
		DashStyle dashStyle;	//������� pen �.�. pen �������������.

		Point position;		//��� �������� ����� ��������� ������������ �����, ��������� � ����� position.
		Color color;		//���� ������
		System::Drawing::Rectangle boundRec;	//�������������� �������������
		Color highlightColor;		//���� ���������

	public:
		property bool highlighted;		//������������� ������ ��� ���
		Element() : highlightColor(Color::Magenta) {   highlighted = false;  }
		property System::Drawing::Rectangle bound
		{
			System::Drawing::Rectangle get() { return boundRec; }
		}
		bool Hit(Point p)		//�������� �������� �� ����� � ������� ��� ��������������� ��������������.
		{
			return boundRec.Contains(p);	//���� p ��������� ������ boundRec, �������������� true ����� false.
			//������� Conpains() ������� ������ ��������� System::Drawing::Recangle.
		}
		void Move(int dx, int dy)
		{
			position.Offset(dx, dy);	//���������� dx � dy � ����������� �����.
			boundRec.X += dx;
			boundRec.Y += dy;
		}

		virtual void Draw(Graphics^ g) abstract;
	};


	[Serializable]
	public ref class Line: Element
	{
	protected:
		Point end;

	public:
		Line(Color color, Point start, Point end,  float penWidth, DashStyle style)
		{
			pen = gcnew Pen(color, penWidth);
			pen->DashStyle = style;
			this->color = color;
			position = start;
			//this->end = end;
			this->end = end - Size(start);
			boundRec = System::Drawing::Rectangle(
				Math::Min(position.X, end.X),	//X ���������� ������ �������� ����
				Math::Min(position.Y, end.Y),	//Y ���������� ������ �������� ����
				Math::Abs(position.X - end.X),	//������
				Math::Abs(position.Y - end.Y)	//������
				);
			
			//if(boundRec.Width < 2) boundRec.Width = 2;
			//if(boundRec.Height < 2) boundRec.Height = 2;

			boundRec.Inflate(safe_cast<int>(penWidth), safe_cast<int>(penWidth));
			//����������� ������ �� �������� ������� ��������� �� ���� � �����, � �� ������ �� �� ����� �
			//���� �� �������� ������� ���������. ����� ������� ������ � ������ ������������� �� ��� ������ ����.
		}

		virtual void Draw(Graphics^ g) override
		{
			pen->Color = (highlighted ? highlightColor : color);
			g->TranslateTransform(safe_cast<float>(position.X), safe_cast<float>(position.Y));
			g->DrawLine(pen, 0, 0, end.X, end.Y);
			g->ResetTransform();
			//��� g->DrawLine(pen, position, end);		//������� = 1
		}

		[OnSerializing]
		void SavePenAttributes(StreamingContext context)
		{
			penWidth = pen->Width;
			dashStyle = pen->DashStyle;
		}

		[OnDeserialized]
		void CreatePen(StreamingContext context)
		{
			pen = gcnew Pen(color, penWidth);
			pen->DashStyle = dashStyle;
		}
	};


	[Serializable]
	public ref class Rectangle: Element
	{
	protected:
		int width;
		int height;

	public:
		Rectangle(Color color, Point p1, Point p2, float penWidth, DashStyle style)
		{
			pen = gcnew Pen(color, penWidth);
			pen->DashStyle = style;
			this->color = color;
			position = Point(Math::Min(p1.X, p2.X), Math::Min(p1.Y, p2.Y));		//����� ������� ���� boundRec
			width = Math::Abs(p1.X - p2.X);
			height = Math::Abs(p1.Y - p2.Y);
			boundRec = System::Drawing::Rectangle(position, Size(width, height));
			//������ System::Drawing::Size ������������� ������ � ������ ��������������.

			boundRec.Inflate(safe_cast<int>(penWidth), safe_cast<int>(penWidth));
		}

		virtual void Draw(Graphics^ g) override
		{
			pen->Color = highlighted ? highlightColor : color;
			g->TranslateTransform(safe_cast<float>(position.X), safe_cast<float>(position.Y));
			g->DrawRectangle(pen, 0, 0, width, height);
			g->ResetTransform();
			//��� g->DrawRectangle(pen, position.X, position.Y, width, height);
		}

		[OnSerializing]
		void SavePenAttributes(StreamingContext context)
		{
			penWidth = pen->Width;
			dashStyle = pen->DashStyle;
		}

		[OnDeserialized]
		void CreatePen(StreamingContext context)
		{
			pen = gcnew Pen(color, penWidth);
			pen->DashStyle = dashStyle;
		}
	};


	[Serializable]
	public ref class Circle: Element
	{
	protected:
		int width;
		int height;

	public:
		Circle(Color color, Point center, Point circum, float penWidth, DashStyle style)
		{
			pen = gcnew Pen(color, penWidth);
			pen->DashStyle = style;
			this->color = color;
			int radius = safe_cast<int>(Math::Sqrt(
					(center.X-circum.X)*(center.X-circum.X) + (center.Y-circum.Y)*(center.Y-circum.Y)
				));
			position = Point(center.X - radius, center.Y - radius);
			width = height = 2*radius;
			boundRec = System::Drawing::Rectangle(position, Size(width, height));

			boundRec.Inflate(safe_cast<int>(penWidth), safe_cast<int>(penWidth));
		}

		virtual void Draw(Graphics^ g) override
		{
			pen->Color = highlighted ? highlightColor : color;
			g->TranslateTransform(safe_cast<float>(position.X), safe_cast<float>(position.Y));
			g->DrawEllipse(pen, 0, 0, width, height);
			g->ResetTransform();
			//������� ������ ���������� � ����� ������� ���� boundRec � ����� �������� ����������.
			//��� ����� �� ��������� ������ ���������:	g->DrawEllipse(pen, position.X, position.Y, width, height);
		}

		[OnSerializing]
		void SavePenAttributes(StreamingContext context)
		{
			penWidth = pen->Width;
			dashStyle = pen->DashStyle;
		}

		[OnDeserialized]
		void CreatePen(StreamingContext context)
		{
			pen = gcnew Pen(color, penWidth);
			pen->DashStyle = dashStyle;
		}
	};


	[Serializable]
	public ref class Curve : Element
	{
	private:
		[NonSerialized]
		vector<Point>^ points;		//���� �������� ���������� � � � �� ��������� �����, � �� ���� �����.

		array<Point>^ pointsArray;		//��� ������������ ��������� points.

	public:
		Curve(Color color, Point p1, Point p2, float penWidth, DashStyle style): pointsArray(nullptr)
		{
			pen = gcnew Pen(color, penWidth);
			pen->DashStyle = style;
			this->color = color;
			points = gcnew vector<Point>();
			position = p1;
			points->push_back(p2 - Size(position));

			// Find the minimum and maximum coordinates
			int minX = p1.X < p2.X ? p1.X : p2.X;
			int minY = p1.Y < p2.Y ? p1.Y : p2.Y;
			int maxX = p1.X > p2.X ? p1.X : p2.X;
			int maxY = p1.Y > p2.Y ? p1.Y : p2.Y;
			
			//int width = Math::Max(2, maxX - minX);
			//int height = Math::Max(2, maxY - minY);
			//boundRec = System::Drawing::Rectangle(minX, minY, width, height);

			int width = maxX - minX;
			int height = maxY - minY;
			boundRec = System::Drawing::Rectangle(minX, minY, width, height);

			boundRec.Inflate(safe_cast<int>(penWidth), safe_cast<int>(penWidth));
		}

		// Add a point to the curve
		void Add(Point p)
		{
			points->push_back(p - Size(position));

			// Modify the bounding rectangle to accommodate the new point
			int penWidth(safe_cast<int>(pen->Width));        // Pen width as an integer
			boundRec.Inflate(-penWidth, -penWidth);         // Reduce the rectangle by the pen width

			//��������� ������� boundRec ��� ���������� ����� �����
			if(p.X < boundRec.X)
			{
				boundRec.Width = boundRec.Right - p.X;
				//Rectangle.Right -- ����� ���������� � ����� ������� ������� � ������.
				boundRec.X = p.X;
			}
			else if(p.X > boundRec.Right)
				boundRec.Width = p.X - boundRec.Left;
				//Rectangle.Left -- ���������� � ������ ����.

			if(p.Y < boundRec.Y)
			{
				boundRec.Height = boundRec.Bottom - p.Y;
				//Ractangle.Bottom -- ����� ��������� y ������ �������� ���� � ������.
				boundRec.Y = p.Y;
			}
			else if(p.Y > boundRec.Bottom)
				boundRec.Height = p.Y - boundRec.Top;
				//Rectangle.Top -- ���������� � �������� ����.

			boundRec.Inflate(penWidth, penWidth);          // Inflate the rectangle by the pen width
		}

		virtual void Draw(Graphics^ g) override
		{
			pen->Color = highlighted ? highlightColor : color;
			g->TranslateTransform(safe_cast<float>(position.X), safe_cast<float>(position.Y));
			Point previous(0, 0);
			//Point previous(position);
			//Point temp;
			for each(Point p in points)
			{
				g->DrawLine(pen, previous, p);
				previous = p;
				//temp = position + Size(p);
				//g->DrawLine(pen, previous, temp);
				//previous = temp;
			}
			g->ResetTransform();
		}

		[OnSerializing]
		void SavePenAndVectorData(StreamingContext context)
		{
			penWidth = pen->Width;
			dashStyle = pen->DashStyle;
			pointsArray = points->to_array();
		}

		[OnDeserialized]
		void RestorePenAndVectorData(StreamingContext context)
		{
			pen = gcnew Pen(color, penWidth);
			pen->DashStyle = dashStyle;
			points = gcnew vector<Point>(pointsArray);
			pointsArray = nullptr;
		}
	};


	[Serializable]
	public ref class TextElement : Element
	{
	protected:
		String^ text;
		[NonSerialized]
		SolidBrush^ brush;
		Font^ font;

	public:
		TextElement(Color color, Point p, String^ text, Font^ font)
		{
			this->color = color;
			brush = gcnew SolidBrush(color);
			position = p;
			this->text = text;
			this->font = font;
			int height = font->Height;            
			int width = static_cast<int>(font->Size*text->Length); // Width of string
				//font->Size -- ������ ����� �.
			boundRec = System::Drawing::Rectangle(position, Size(width, height));
			boundRec.Inflate(2,2);               // ���� ����������� ��������� ����� ��� p, q, ...
		}

		virtual void Draw(Graphics^ g) override
		{
			brush->Color = highlighted ? highlightColor : color;
			g->TranslateTransform(safe_cast<float>(position.X),
				safe_cast<float>(position.Y));
			g->DrawString(text, font, brush, Point(0, 0));
			g->ResetTransform();
		}

		[OnDeserialized]
		void CreateBrush(StreamingContext context)
		{
			brush = gcnew SolidBrush(color);
		}
	};

}