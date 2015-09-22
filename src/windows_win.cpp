#include <nan.h>

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#include <list>

#include <stdio.h>
#include <stdlib.h>
#include <psapi.h>
#include <string>

#include <sstream>

#include <vector>

#include <iostream>
#include <fstream>

using namespace std;

using v8::Local;
using v8::FunctionTemplate;
using v8::Number;
using v8::Handle;
using v8::Object;
using v8::String;
using v8::Array;

using Nan::GetFunction;
using Nan::New;
using Nan::Set;
using Nan::True;
using Nan::False;
using Nan::Export;

#define WINDOWZ_HANDLE(name) HWND name = (HWND)info[0]->Uint32Value();
#define WINDOWZ_HANDLE2(name) HWND name = (HWND)info[1]->Uint32Value();

BOOL IsTaskbarWindow(HWND hwnd) {
  if (IsWindowVisible(hwnd) && GetParent(hwnd) == 0) {
    bool bNoOwner = (GetWindow(hwnd, GW_OWNER) == 0);
    int lExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    if (!bNoOwner) return FALSE;
    if ((((lExStyle & WS_EX_TOOLWINDOW) == 0))) {
        return TRUE;
    }
  }

  return FALSE;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
  if (!IsTaskbarWindow(hwnd)) {
    return TRUE;
  }

  std::list<Local<Object>> *windows = (std::list<Local<Object>>*)lParam;
  Local<Object> obj = New<Object>();

  DWORD processID;
  char title[1024];
  DWORD threadID = GetWindowThreadProcessId(hwnd, &processID);
  GetWindowText(hwnd, title, sizeof(title));

  Set(obj, New<String>("threadID").ToLocalChecked(), New<Number>((unsigned int)threadID));
  Set(obj, New<String>("processID").ToLocalChecked(), New<Number>((unsigned int)processID));
  Set(obj, New<String>("handle").ToLocalChecked(), New<Number>((unsigned int)hwnd));
  Set(obj, New<String>("title").ToLocalChecked(), New<String>(title).ToLocalChecked());

  (*windows).push_back(obj);
  return TRUE;
}

NAN_METHOD(getAll) {
  std::list<Local<Object>> windows;

  EnumWindows(EnumWindowsProc, (LPARAM)&windows);

  Local<Array> returnValue = New<Array>();

  int i = 0;
  for (std::list<Local<Object>>::iterator it=windows.begin(); it != windows.end(); ++it) {
      returnValue->Set(i, *it);
      i++;
  }

  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(getCurrent) {
  Local<Object> returnValue = New<Object>();

  Set(returnValue, New<String>("processID").ToLocalChecked(), New<Number>((unsigned int)  GetCurrentProcessId()));

  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(getTitle) {
  WINDOWZ_HANDLE(hwnd)

  char title[1024];
  GetWindowText(hwnd, title, sizeof(title));

  info.GetReturnValue().Set(New<String>(title).ToLocalChecked());
  // If hebrew is not working
  //NanReturnValue(New(*NanAsciiString(title)));
}

NAN_METHOD(minimize) {
  WINDOWZ_HANDLE(hwnd)

  ShowWindow(hwnd, SW_MINIMIZE);
}

NAN_METHOD(show) {
  WINDOWZ_HANDLE(hwnd)

  ShowWindow(hwnd, SW_SHOW);
}

NAN_METHOD(maximize) {
  WINDOWZ_HANDLE(hwnd)

  ShowWindow(hwnd, SW_MAXIMIZE);
}

NAN_METHOD(isForeground) {
  WINDOWZ_HANDLE(hwnd)

  info.GetReturnValue().Set(GetForegroundWindow() == hwnd ? True() : False());
}

NAN_METHOD(isMinimized) {
  WINDOWZ_HANDLE(hwnd)

  info.GetReturnValue().Set(IsIconic(hwnd) ? True() : False());
}

NAN_METHOD(setTopMost) {
  WINDOWZ_HANDLE(hwnd)

  SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);
}

NAN_METHOD(close) {
  WINDOWZ_HANDLE(hwnd)

  ShowWindow(hwnd, SW_HIDE);
}

NAN_METHOD(setToForeground) {
  WINDOWZ_HANDLE(hwnd)

  ShowWindow(hwnd, 4);
  SetForegroundWindow(hwnd);
}

NAN_METHOD(activate) {
  WINDOWZ_HANDLE(hwnd)
  int result;

  if (hwnd != GetForegroundWindow()) {
    DWORD lForeThreadID = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
    DWORD lThisThreadID = GetWindowThreadProcessId(hwnd, NULL);

    if (IsIconic(hwnd)) {
      ShowWindow(hwnd, SW_RESTORE);
    } else {
      ShowWindow(hwnd, SW_SHOW);
    }

    if (lForeThreadID != lThisThreadID) {
      AttachThreadInput(lForeThreadID, lThisThreadID, TRUE);
      result = SetForegroundWindow(hwnd);
      AttachThreadInput(lForeThreadID, lThisThreadID, FALSE);
    } else {
      result = SetForegroundWindow(hwnd);
    }
  }
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rc;
      HDC hdc;
      TCHAR greeting[] = _T("Hello, World!");

	switch (uMsg)
	{
	case WM_PAINT:
          hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rc);
                 SetBkColor(hdc, 0x000000ff); // red
          // Here your application is laid out.
          // For this introduction, we just print out "Hello, World!"
          // in the top left corner.
          TextOut(hdc,
              5, 5,
              greeting, _tcslen(greeting));
          // End application specific layout section.

          EndPaint(hWnd, &ps);
          break;
	case WM_NCRBUTTONDOWN:
  	  break;
	case WM_RBUTTONDOWN:
	  break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATE:
	case WM_ACTIVATEAPP:
	case WM_SIZE:
	case WM_NCCALCSIZE:
	case WM_NCACTIVATE:
	  return 0;

	default:
  //ostringstream stros;
  //stros << uMsg;
	//MessageBox(NULL, stros.str().c_str(), "asd2", MB_OK);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

NAN_METHOD(setParent) {
  WINDOWZ_HANDLE(child)
  WINDOWZ_HANDLE2(parent)

  HWND result = SetParent(child, parent);

  if (result == NULL) {
    info.GetReturnValue().Set(New<Number>(GetLastError()));
  } else {
    info.GetReturnValue().Set(New<Number>((unsigned int) result));
  }
}

NAN_METHOD(createDesktopWindow) {
  HMODULE hInstance = GetModuleHandle(NULL);

  WNDCLASS wc = {0};
  wc.lpfnWndProc = (WNDPROC)MainWndProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = "NachosDesktopWClass";
  ATOM className = RegisterClass(&wc);

  HWND hwnd = CreateWindowEx(
    NULL, //WS_EX_TOOLWINDOW,
    MAKEINTATOM(className),
    "NachosDesktop",
    WS_POPUP,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    300,
    200,
    nullptr,
    nullptr,
    hInstance,
    nullptr);

      ShowWindow(hwnd, 4);
          UpdateWindow(hwnd);


MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    info.GetReturnValue().Set(New<Number>((unsigned int)hwnd));
}

NAN_MODULE_INIT(init) {
  NAN_EXPORT(target, getAll);
  NAN_EXPORT(target, getTitle);
  NAN_EXPORT(target, setToForeground);
  NAN_EXPORT(target, minimize);
  NAN_EXPORT(target, activate);
  NAN_EXPORT(target, show);
  NAN_EXPORT(target, maximize);
  NAN_EXPORT(target, isForeground);
  NAN_EXPORT(target, isMinimized);
  NAN_EXPORT(target, setTopMost);
  NAN_EXPORT(target, close);
  NAN_EXPORT(target, getCurrent);
  NAN_EXPORT(target, createDesktopWindow);
  NAN_EXPORT(target, setParent);
}

NODE_MODULE(windows, init)