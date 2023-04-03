uint32_t width = 1920;
uint32_t height = 1080;

void changeAspect()
{
	double aspect = (double)width / (double)height;

	if (aspect != (16.0 / 9.0))
	{
		if (aspect > (16.0 / 9.0))
		{
			WRITE_MEMORY(0x1414ABFEC, uint32_t, width);
			WRITE_MEMORY(0x1414AC014, uint32_t, width);

			WRITE_MEMORY(0x1417594A8, uint32_t, width);
		}
		else
		{
			WRITE_MEMORY(0x1414ABFF0, uint32_t, height);
			WRITE_MEMORY(0x1414AC018, uint32_t, height);

			WRITE_MEMORY(0x1417594AC, uint32_t, height);
		}
	}

	WRITE_MEMORY(0x1414AC020, double, aspect);
}

// called on res change
HOOK(void, __fastcall, _1402C27E0, 0x1402C27E0, __int64 a1, int a2, int a3, char a4)
{
	printf("[DivaUltrawide] sub_1402C27E0 called: %dx%d\n", a2, a3);
	width = a2;
	height = a3;

	WRITE_MEMORY(0x140CCD1C0, double, (double)width / (double)height);

	original_1402C27E0(a1, a2, a3, a4);
}

/*
// called on boot, crashes atm
HOOK(void, __fastcall, _1402C0B60, 0x1402C0B60)
{
	printf("[DivaUltrawide] sub_1402C0B60 called\n");
	WRITE_MEMORY(0x140CCD1C0, double, 16.0 / 9.0);
	original_1402C0B60();
}

// unknown!
HOOK(void, __fastcall, _14041F200, 0x14041F200)
{
	printf("[DivaUltrawide] sub_14041F200 called\n");
	WRITE_MEMORY(0x140CCD140, float, 16.0f / 9.0f);
	original_14041F200();
}
*/

extern "C"
{
	void __declspec(dllexport) Init()
	{
		INSTALL_HOOK(_1402C27E0);
		//INSTALL_HOOK(_1402C0B60);
		//INSTALL_HOOK(_14041F200);
	}

	void __declspec(dllexport) OnResize()
	{
		changeAspect();
	}
}
