// Sketcher.cpp: ������� ���� �������.
#include "stdafx.h"
#include "Form1.h"
/*
	�������� ������ ������ ���� �� Form1.h � ���� ��������� � �������� ���������� ���.
	��� ����������� ������� �������� ����������.
*/
using namespace Sketcher;

[STAThreadAttribute]
int main(array<System::String ^> ^args)		//������ �������� ����������
{
	Application::EnableVisualStyles();	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::SetCompatibleTextRenderingDefault(false);	//��������� ��� ������ ����������� ����� � ����� ��������� ����������:
	//false -- ����� �������������� ������ TextRenderer,	true -- ����� ������������� ������ Graphics.

	
	Application::Run(gcnew Form1());	// �������� �������� ���� � ��� ������
	return 0;
}
