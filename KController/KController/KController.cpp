/*
* Projet de fin d'√©tudes LastProject de
* Adrien Broussolle
* Camille Darcy
* Guillaume Demurger
* Sylvain Fay-Chatelard
* Anthony Fourneau
* Aur√®le Lenfant
* Adrien Madouasse
*
* Copyright (C) 2013 Universit√© Paris-Est Marne-la-Vall√©e
*
* FreeStroke is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
*/
// KController.cpp†: dÈfinit le point d'entrÈe pour l'application.
/*
 * Projet de fin d'√©tudes LastProject de
 * Adrien Broussolle
 * Camille Darcy
 * Guillaume Demurger
 * Sylvain Fay-Chatelard
 * Anthony Fourneau
 * Aur√®le Lenfant
 * Adrien Madouasse
 *
 * Copyright (C) 2010 Universit√© Paris-Est Marne-la-Vall√©e 
 *
 * FreeStroke is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */
#include "stdafx.h"
#include "KController.h"
#include "kcontrollerserver.h"
#include "kinect.h"
#include "serverutils.h"
#include "tcpserver.h"
#include "udpserver.h"

#include <codecvt>
#include <fstream>
#include <shlobj.h>
#include <string.h>

#define ID_LIST     1
#define ID_TEXT     2
#define ID_BUTTON	3

#define IDC_MAIN_BUTTON	1001
#define MAX_LOADSTRING 100

#define FOLDER_CONF L"\\FreeSoft\\FreeStroke\\"
#define FILE_CONF L"config.txt"
#define FILE_CONF_PATH L"\\FreeSoft\\FreeStroke\\config.txt"

// Variables globales†:
HINSTANCE hInst;								// instance actuelle
TCHAR szTitle[MAX_LOADSTRING];					// Le texte de la barre de titre
TCHAR szWindowClass[MAX_LOADSTRING];			// le nom de la classe de fenÍtre principale
// PrÈ-dÈclarations des fonctions incluses dans ce module de code†:
void drawBitmap(HWND hWnd, HBITMAP hBmp, int xPos, int yPos);
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD dwEvent;
HANDLE ghEvents[3];
KControllerServer srv;
static HWND hWnd;
int nCmdShow;
string* name;
unsigned short udpPort = 0;
unsigned short tcpPort = 0;
static int color = IDB_RED;

Kinect *kinect;

/*!< The current state of the controller */
State state;


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       pNCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	state = State::DISCONNECTED;

	name = new string();
	loadConf();

	MSG msg;
	HACCEL hAccelTable;

	nCmdShow = pNCmdShow;

	// Initialise les chaÓnes globales
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_KCONTROLLER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Effectue l'initialisation de l'application†:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

#ifdef KINECT
	NuiSetDeviceStatusCallback(statusProc, NULL);
#endif
	kinect = new Kinect();

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KCONTROLLER));
	srv.init(name, &hWnd, kinect, udpPort, tcpPort);
	statusProc(true, NULL, NULL, NULL);

	ghEvents[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ghEvents[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ghEvents[2] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ghEvents[3] = CreateEvent(NULL, FALSE, FALSE, NULL);

	
	// Boucle de messages principale†:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	delete kinect;

	return (int) msg.wParam;
}


//
//  FONCTION†: MyRegisterClass()
//
//  BUT†: inscrit la classe de fenÍtre.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KCONTROLLER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_KCONTROLLER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FONCTION†: InitInstance(HINSTANCE, int)
//
//   BUT†: enregistre le handle de l'instance et crÈe une fenÍtre principale
//
//   COMMENTAIRES†:
//
//        Dans cette fonction, nous enregistrons le handle de l'instance dans une variable globale, puis
//        crÈons et affichons la fenÍtre principale du programme.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Stocke le handle d'instance dans la variable globale

	hWnd = CreateWindow(szWindowClass, szTitle, WS_MINIMIZEBOX | WS_OVERLAPPED&~WS_MAXIMIZE  | WS_SYSMENU | WS_CAPTION,
		300, 200, 200, 320, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FONCTION†: (HWND, UINT, WPARAM, LPARAM)
//
//  BUT†:  traite les messages pour la fenÍtre principale.
//
//  WM_COMMAND	- traite le menu de l'application
//  WM_PAINT	- dessine la fenÍtre principale
//  WM_DESTROY	- gÈnËre un message d'arrÍt et retourne
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND  labelName, txtName, labelUdp, txtUdp, labelTcp, txtTcp, buttonApply;
	static HBITMAP pngRed = NULL, pngOrange = NULL, pngGreen = NULL;
	int wmId, wmEvent, cxChar, cyChar, width, height ;
	TCHAR text1[] = TEXT ("Port TCP :");
	TCHAR text2[] = TEXT ("Port UDP :");
	TCHAR textBtn[] = TEXT ("Appliquer");
	TCHAR labelContentName[] = TEXT ("Nom :");
	LPTSTR tcpContent, udpContent, nameContent;
	int xBmp = 53;
	int yBmp = 210;
	
	HGDIOBJ hfDefault=GetStockObject(DEFAULT_GUI_FONT);

	switch (message)
	{
	case WM_CREATE:
		cxChar = LOWORD (GetDialogBaseUnits ()) ;
		cyChar = HIWORD (GetDialogBaseUnits ()) ;

		RECT rect;
		if(GetWindowRect(hWnd, &rect))
		{
		    width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}
		
		labelName = CreateWindow(TEXT ("static"), NULL,
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			cxChar, cyChar, 
			width-30, cyChar,
			hWnd, (HMENU) ID_TEXT,
			(HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE),
			NULL);
		txtName = CreateWindow(TEXT ("edit"), NULL,
			WS_CHILD | WS_VISIBLE | SS_LEFT| WS_BORDER,
			cxChar, cyChar+30, 
			width-30, cyChar+4,
			hWnd, (HMENU) ID_TEXT,
			(HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE),
			NULL);

		labelUdp = CreateWindow(TEXT ("static"), NULL,
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			cxChar, cyChar+60, 
			width-30, cyChar,
			hWnd, (HMENU) ID_TEXT,
			(HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE),
			NULL);
		txtUdp = CreateWindow(TEXT ("edit"), NULL,
			WS_CHILD | WS_VISIBLE | SS_LEFT| WS_BORDER,
			cxChar, cyChar+90, 
			width-30, cyChar+4,
			hWnd, (HMENU) ID_TEXT,
			(HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE),
			NULL);
		
		labelTcp = CreateWindow(TEXT ("static"), NULL,
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			cxChar, cyChar+120, 
			width-30, cyChar,
			hWnd, (HMENU) ID_TEXT,
			(HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE),
			NULL);
		txtTcp = CreateWindow(TEXT ("edit"), NULL,
			WS_CHILD | WS_VISIBLE | SS_LEFT| WS_BORDER,
			cxChar, cyChar+150, 
			width-30, cyChar+4,
			hWnd, (HMENU) ID_TEXT,
			(HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE),
			NULL);
		
		buttonApply = CreateWindowEx(NULL, 
			L"BUTTON",
			L"OK",
			WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
			cxChar, cyChar+180, 
			width-30, cyChar+4,
			hWnd,
			(HMENU)IDC_MAIN_BUTTON,
			GetModuleHandle(NULL),
			NULL);

		// Set the text
		SetWindowText(labelName, labelContentName);
		SetWindowText(labelTcp, text1);
	    SetWindowText(labelUdp, text2);
		SetWindowText(buttonApply, textBtn);
		
		nameContent = new TCHAR[6];
		
		// Replace the default codecvt<char, char, mbstate_t>.
		//std::locale l = cout.getloc();
		//locale loc(l, new codecvt());
		// TODO Bug
		wsprintf(nameContent, L"%s", wstring(name->begin(), name->end()).c_str());
		SetWindowText(txtName, nameContent);

		udpContent = new TCHAR[6];
		wsprintf(udpContent, L"%d", udpPort);
		SetWindowText(txtUdp, udpContent);
		
		tcpContent = new TCHAR[6];
		wsprintf(tcpContent, L"%d", tcpPort);
		SetWindowText(txtTcp, tcpContent);
		
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// Analyse les sÈlections de menu†:
		switch (wmId)
		{
		case IDC_MAIN_BUTTON:
			{
				// TODO Check accent
				TCHAR tmpName[128];
				GetWindowText(txtName, tmpName, 128);

				wstring ws(tmpName);
				*name = string(ws.begin(), ws.end());

				TCHAR udp[6];
				TCHAR tcp[6];
				GetWindowText(txtUdp, udp, 6);
				GetWindowText(txtTcp, tcp, 6);

				int c = wcslen(udp);
				c = wcslen(tcp);

				if (wcslen(udp) > 0 &&  wcslen(tcp) > 0)
				{
					udpPort = (unsigned short)_wtoi(udp);
					tcpPort = (unsigned short)_wtoi(tcp);

					if (udpPort > 1 && udpPort < 65535 && tcpPort > 1 && tcpPort < 65535)
					{
						srv.changePort(tcpPort, udpPort);

						saveConf();
					}
				}
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case CHANGE_STATE:				
			switch (lParam)
			{
			case State::CONNECTED:
				color = IDB_GREEN;
				break;
			case State::WAITING:
				color = IDB_ORANGE;
				break;
			case State::DISCONNECTED:
			default:
				color = IDB_RED;
				break;
			}

			SendMessage(hWnd, WM_PRINT, NULL, NULL);

			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PRINT:
	{
		cyChar = HIWORD (GetDialogBaseUnits()) ;
		switch (color)
		{
		case IDB_GREEN:
			pngGreen = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GREEN));
			if (pngRed != NULL)
			{
				DeleteObject(pngRed);
				pngRed = NULL;
			}
			if (pngOrange != NULL)
			{
				DeleteObject(pngOrange);
				pngOrange = NULL;
			}
			drawBitmap(hWnd, pngGreen, xBmp, cyChar+yBmp);
			break;
		case IDB_ORANGE:
			pngOrange = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_ORANGE));
			if (pngGreen != NULL)
			{
				DeleteObject(pngGreen);
				pngGreen = NULL;
			}
			if (pngRed != NULL)
			{
				DeleteObject(pngRed);
				pngRed = NULL;
			}
			drawBitmap(hWnd, pngOrange, xBmp, cyChar+yBmp);
			break;
		case IDB_RED:
		default:
			pngRed = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_RED));
			if (pngGreen != NULL)
			{
				DeleteObject(pngGreen);
				pngGreen = NULL;
			}
			if (pngOrange != NULL)
			{
				DeleteObject(pngOrange);
				pngOrange = NULL;
			}
			drawBitmap(hWnd, pngRed, xBmp, cyChar+yBmp);
			break;
		}
		break;
	}
	case WM_DESTROY: 
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void drawBitmap(HWND hWnd, HBITMAP hBmp, int xPos, int yPos)
{
    HDC hDC = GetDC(hWnd);
    HDC hdcMem = CreateCompatibleDC(hDC);
    SelectObject(hdcMem, hBmp);
    BitBlt(hDC, xPos, yPos, 200, 50, hdcMem, 0, 0, SRCCOPY);
}

void CALLBACK statusProc(HRESULT pHrStatus, const OLECHAR* pInstanceName, const OLECHAR* pUniqueDeviceName, void* pUserData)
{
	if (SUCCEEDED(pHrStatus))      
	{          
		// Initialize the Kinect sensor identified by the instanceName parameter.
		#if defined KINECT
		if (!kinect->isInitialized() && kinect->init())
		{
			state = State::WAITING;
			srv.start();
		}
		else
		{
			state = State::DISCONNECTED;
			srv.stop();
			kinect->close();
		}
		#else
			kinect->init();
			srv.start();
		#endif
	}      
	else      
	{
		// Uninitialize the Kinect sensor identified by the instanceName parameter.
		state = State::DISCONNECTED;
		srv.stop();
		
		#if defined KINECT
			kinect->close();
		#endif
	}
}

void saveConf()
{
	TCHAR szPath[MAX_PATH];
	if (SUCCEEDED( SHGetFolderPath( hWnd, CSIDL_COMMON_APPDATA , NULL, 0, szPath ) ) )
	{
		wstring filePath(szPath);
		filePath.append(FOLDER_CONF);
		wstring folder = wstring(filePath.begin(), filePath.end());
		filePath.append(FILE_CONF);

		ofstream file;
		file.open(filePath);
		if(file.fail())
		{
			SHCreateDirectoryEx(NULL, folder.c_str(), NULL);
			file.open(filePath);
		}
		if (file.is_open())
		{
			file << (*name) << endl;
			file << udpPort << endl;
			file << tcpPort;
			file.close();
		}
	}
}

void loadConf()
{
	TCHAR szPath[MAX_PATH];
	if (SUCCEEDED( SHGetFolderPath( hWnd, CSIDL_COMMON_APPDATA , NULL, 0, szPath ) ) )
	{
		wstring filePath(szPath);
		filePath.append(FOLDER_CONF);
		filePath.append(FILE_CONF);

		ifstream file;
		file.open(filePath);
		if (file.is_open())
		{
			file >> (*name);
			file >> udpPort;
			file >> tcpPort;
			file.close();
		}
		else
		{
			*name = "KController \0";
			udpPort = DEFAULT_PORT;
			tcpPort = DEFAULT_PORT;
		}
	}
	else
	{
		*name = "KController \0";
		udpPort = DEFAULT_PORT;
		tcpPort = DEFAULT_PORT;
	}
}