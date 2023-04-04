HOOK(void, __fastcall, _ResolutionChange, 0x1402B7CD0, __int64 width, int height, char a3, char a4)
{
	WRITE_MEMORY(0x140CCD1C0, double, (double)width / (double)height); // pass_adjust_screen
	original_ResolutionChange(width, height, a3, a4);
}

extern "C"
{
	void __declspec(dllexport) Init()
	{
		INSTALL_HOOK(_ResolutionChange);
	}

	void __declspec(dllexport) OnResize(IDXGISwapChain* swapChain)
	{
		DXGI_SWAP_CHAIN_DESC desc;
		swapChain->GetDesc(&desc);

		WRITE_MEMORY(0x1414ABFF8, double, (double)desc.BufferDesc.Width / (double)desc.BufferDesc.Height); // fbAspectRatio
		WRITE_MEMORY(0x1414ABFEC, uint32_t, desc.BufferDesc.Width); // fbWidth
		WRITE_MEMORY(0x1414ABFF0, uint32_t, desc.BufferDesc.Height); // fbHeight

		WRITE_MEMORY(0x1414AC020, double, (double)desc.BufferDesc.Width / (double)desc.BufferDesc.Height); // unk
		WRITE_MEMORY(0x1414AC014, uint32_t, desc.BufferDesc.Width); // unk
		WRITE_MEMORY(0x1414AC018, uint32_t, desc.BufferDesc.Height); // unk

		WRITE_MEMORY(0x14CBFF3B0, float, (double)desc.BufferDesc.Width / (double)desc.BufferDesc.Height); // uiAspectRatio
		WRITE_MEMORY(0x14CBFF3B4, float, (double)desc.BufferDesc.Width / (double)desc.BufferDesc.Height); // uiAspectRatio2 (???)
		WRITE_MEMORY(0x14CBFF3C4, float, desc.BufferDesc.Width); // uiWidth
		WRITE_MEMORY(0x14CBFF3C8, float, desc.BufferDesc.Height); // uiHeight
	}
}
