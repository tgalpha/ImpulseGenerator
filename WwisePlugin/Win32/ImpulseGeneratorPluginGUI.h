#pragma once
// [wp-enhanced template] **Do not delete this line**

#include "../ImpulseGeneratorPlugin.h"
#include "../resource.h"

class ImpulseGeneratorPluginGUI final
	: public AK::Wwise::Plugin::PluginMFCWindows<>
	, public AK::Wwise::Plugin::GUIWindows
{
public:
	ImpulseGeneratorPluginGUI();

	HINSTANCE GetResourceHandle() const override;

	bool GetDialog(
		AK::Wwise::Plugin::eDialog in_eDialog,
		UINT& out_uiDialogID,
		AK::Wwise::Plugin::PopulateTableItem*& out_pTable
	) const override;

	bool WindowProc(
		AK::Wwise::Plugin::eDialog in_eDialog,
		HWND in_hWnd,
		uint32_t in_message,
		WPARAM in_wParam,
		LPARAM in_lParam,
		LRESULT& out_lResult
	) override;

private:
	HWND m_hwndPropView = nullptr;
};
