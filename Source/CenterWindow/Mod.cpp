void CenterWindow()
{
	const HWND hWnd = *reinterpret_cast<HWND*>(0x1411481F8);

	RECT windowRect, clientRect;
	GetWindowRect(hWnd, &windowRect);
	GetClientRect(hWnd, &clientRect);

	LONG windowWidth = windowRect.right - windowRect.left;
	LONG windowHeight = windowRect.bottom - windowRect.top;

	const LONG clientWidth = clientRect.right - clientRect.left;
	const LONG clientHeight = clientRect.bottom - clientRect.top;

	const LONG deltaX = windowWidth - clientWidth;
	const LONG deltaY = windowHeight - clientHeight;

	LONG windowX = windowRect.left - (deltaX / 2);
	LONG windowY = windowRect.right - (deltaY / 2);
	windowWidth += deltaX;
	windowHeight += deltaY;

	const HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);
	MONITORINFO monitorInfo{ sizeof(monitorInfo) };
	if (GetMonitorInfoA(hMonitor, &monitorInfo))
	{
		LONG curWidth = monitorInfo.rcWork.right - monitorInfo.rcWork.left;
		LONG curHeight = monitorInfo.rcWork.bottom - monitorInfo.rcWork.top;

		windowX = monitorInfo.rcWork.left;
		windowY = monitorInfo.rcWork.top;

		if (windowWidth > curWidth)
		{
			curWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
			windowX = monitorInfo.rcMonitor.left;
		}

		if (windowHeight > curHeight)
		{
			curHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;
			windowY = monitorInfo.rcMonitor.top;
		}

		windowX += (curWidth - windowWidth) / 2;
		windowY += (curHeight - windowHeight) / 2;
	}

	SetWindowPos(
		hWnd,
		HWND_TOP,
		windowX,
		windowY,
		windowWidth,
		windowHeight,
		SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOOWNERZORDER);
}

// 0x1402B7FC7
HOOK(bool, __fastcall, _WindowPos1, 0x1402B7E60, int a1, int a2)
{
	bool result = original_WindowPos1(a1, a1);
	CenterWindow();
	return result;
}

// 0x1402C8A5F
HOOK(char, __fastcall, _WindowPos2, 0x1402C8980, HWND *a1)
{
	char result = original_WindowPos2(a1);
	CenterWindow();
	return result;
}

extern "C" __declspec(dllexport) void Init()
{
	if (!sigValid)
	{
		versionWarning(TEXT(MOD_NAME));
		return;
	}

	INSTALL_HOOK(_WindowPos1);
	INSTALL_HOOK(_WindowPos2);
}
