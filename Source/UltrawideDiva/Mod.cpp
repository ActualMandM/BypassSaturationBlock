uint32_t width = 3440;
uint32_t height = 1440;

double aspect = (double)width / (double)height;

extern "C" __declspec(dllexport) void Init()
{
	WRITE_MEMORY(0x140CCD140, float, (float)aspect);
	WRITE_MEMORY(0x140CCD1C0, double, aspect);
}

extern "C" __declspec(dllexport) void OnResize()
{
	WRITE_MEMORY(0x1414ABFEC, uint32_t, width);
	WRITE_MEMORY(0x1414AC014, uint32_t, width);
	WRITE_MEMORY(0x1417594A8, uint32_t, width);

	WRITE_MEMORY(0x1414AC020, double, aspect);
}
