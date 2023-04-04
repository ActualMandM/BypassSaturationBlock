uint32_t width;
uint32_t height;

void changeAspect()
{
	double aspect = (double)width / (double)height;

	WRITE_MEMORY(0x1414ABFE0, uint32_t, 18);

	// idk which one of these correlate to 18
	WRITE_MEMORY(0x140BF7D94, uint32_t, width, height);
	WRITE_MEMORY(0x140BF7E28, uint32_t, width, height);
	WRITE_MEMORY(0x140BF7E3C, uint32_t, width, height);

	/*
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
	*/

	WRITE_MEMORY(0x1414AC020, double, aspect);
}

/*
	somewhere during pass_sprite (sub_1404DAA00) it gets cropped to 16:9
*/

HOOK(void, __fastcall, _ResolutionChange, 0x1402C27E0, __int64 a1, int a2, int a3, char a4)
{
	printf("[DivaUltrawide] sub_1402C27E0 called: %dx%d\n", a2, a3);
	width = a2;
	height = a3;

	WRITE_MEMORY(0x140CCD1C0, double, (double)width / (double)height);
	changeAspect();
	original_ResolutionChange(a1, a2, a3, a4);
}

extern "C"
{
	void __declspec(dllexport) Init()
	{
		WRITE_MEMORY(0x140BF7D94, uint32_t, 3440, 1440);
		WRITE_MEMORY(0x140BF7E28, uint32_t, 3440, 1440);
		WRITE_MEMORY(0x140BF7E3C, uint32_t, 3440, 1440);

		//INSTALL_HOOK(_ResolutionChange);
	}
}
