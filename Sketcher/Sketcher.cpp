// Sketcher.cpp: главный файл проекта.
#include "stdafx.h"
#include "Form1.h"
/*
	Щелкните правой кнопки мыши по Form1.h в окне редактора и выберите Посмотреть код.
	Все обработчики событий являются делегатами.
*/
using namespace Sketcher;

[STAThreadAttribute]
int main(array<System::String ^> ^args)		//ОТСЮДА НАЧИНАЕТ ПРИЛОЖЕНИЯ
{
	Application::EnableVisualStyles();	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::SetCompatibleTextRenderingDefault(false);	//Определят как должен отображатся текст в новых элементах управления:
	//false -- задаёт исспользования класса TextRenderer,	true -- задаёт ичпользования класса Graphics.

	
	Application::Run(gcnew Form1());	// Создание главного окна и его запуск
	return 0;
}
