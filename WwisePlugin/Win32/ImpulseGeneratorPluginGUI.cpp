// [wp-enhanced template] **Do not delete this line**

#include "ImpulseGeneratorPluginGUI.h"

AK_WWISE_PLUGIN_GUI_WINDOWS_BEGIN_POPULATE_TABLE(PropTable)
// [PropertyTable]
// [/PropertyTable]
AK_WWISE_PLUGIN_GUI_WINDOWS_END_POPULATE_TABLE()

ImpulseGeneratorPluginGUI::ImpulseGeneratorPluginGUI()
{
}

ADD_AUDIOPLUGIN_CLASS_TO_CONTAINER(
    ImpulseGenerator,            // Name of the plug-in container for this shared library
    ImpulseGeneratorPluginGUI,   // Authoring plug-in class to add to the plug-in container
    ImpulseGeneratorSource       // Corresponding Sound Engine plug-in class
);

// [wp-enhanced] Uncomment the following lines if you want to use a custom GUI
// HINSTANCE ImpulseGeneratorPluginGUI::GetResourceHandle() const
// {
//     AFX_MANAGE_STATE( AfxGetStaticModuleState() );
//     return AfxGetStaticModuleState()->m_hCurrentResourceHandle;
// }
//  
// bool ImpulseGeneratorPluginGUI::GetDialog( AK::Wwise::Plugin::eDialog in_eDialog, UINT & out_uiDialogID, AK::Wwise::Plugin::PopulateTableItem *& out_pTable ) const
// {
//     AKASSERT( in_eDialog == AK::Wwise::Plugin::SettingsDialog );
//  
//     out_uiDialogID = IDD_DIALOG1;
//     out_pTable = PropTable;
//  
//     return true;
// }
//  
// bool ImpulseGeneratorPluginGUI::WindowProc( AK::Wwise::Plugin::eDialog in_eDialog, HWND in_hWnd, uint32_t in_message, WPARAM in_wParam, LPARAM in_lParam, LRESULT & out_lResult )
// {
//     switch ( in_message )
//     {
//     case WM_INITDIALOG:
//         m_hwndPropView = in_hWnd;
//         break;
//     case WM_DESTROY:
//         m_hwndPropView = NULL;
//         break;
//     }
//     out_lResult = 0;
//     return false;
// }