#pragma once
#include "Element.h"
#include <cliext/list>

using namespace System;
using namespace cliext;
using namespace System::Runtime::Serialization;

namespace Sketcher
{
	[Serializable]
	public ref class Sketch
	{
	private:
		[NonSerialized]
		list<Element^>^ elements;

		array<Element^>^ elementArray;			//нужен т.к. контейнер не сериализуемый поумолчанию

	public:
		bool saved;		//индикатор того что файл был сохранён однажды.

		Sketch(): elementArray(nullptr), saved(true)
			{elements = gcnew list<Element^>();}

		[OnSerializing]
		void ListToArray(StreamingContext context)
		{
			elementArray = elements->to_array();
		}

		[OnDeserialized]
		void ArrayToList(StreamingContext context)
		{
			elements = gcnew list<Element^>(elementArray);
			elementArray = nullptr;
		}

		void Push_front(Element^ element)
		{
			elements->push_front(element);
		}

		Sketch^ operator+= (Element^  element)
		{
			elements->push_back(element);
			return this;
		}

		Sketch^ operator-=(Element^ element)
		{
			elements->remove(element);
			return this;
		}

		void Draw(Graphics^ g)
		{
			for each(Element^ element in elements)
				element->Draw(g);
		}

		Element^ HitElement(Point p)	// Find element under the point p
		{
			for (auto riter = elements->rbegin(); riter != elements->rend() ; ++riter)
			{
				if((*riter)->Hit(p))
					return *riter;
			}
			return nullptr;
		}
	};
}
/*
	Для того чтобы эскиз был сериализуемым, все элементы в эскизе должны быть сериализуемыми.
*/