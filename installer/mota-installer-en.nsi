; Mota Compiler Installer Script (Simple English Version)
; Using NSIS (Nullsoft Scriptable Install System)

!define PRODUCT_NAME "Mota Compiler"
!define PRODUCT_VERSION "0.2.0"
!define PRODUCT_PUBLISHER "Mota Development Team"
!define PRODUCT_WEB_SITE "https://github.com/eachcan/mota"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\mota.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; Set compression method
SetCompressor lzma

; Modern UI
!include "MUI2.nsh"

; Installer properties
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "mota-installer-v${PRODUCT_VERSION}.exe"
InstallDir "$PROGRAMFILES\Mota"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

; Request administrator privileges
RequestExecutionLevel admin

; Interface settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Installation pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "LICENSE"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!define MUI_FINISHPAGE_RUN "$INSTDIR\mota.exe"
!define MUI_FINISHPAGE_RUN_PARAMETERS "--help"
!define MUI_FINISHPAGE_RUN_TEXT "Run Mota to view help information"
!insertmacro MUI_PAGE_FINISH

; Uninstallation pages
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; Version information
VIProductVersion "0.2.0.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "${PRODUCT_NAME}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "Mota Configuration File Compiler"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "${PRODUCT_PUBLISHER}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" ""
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "© 2024 Mota Development Team"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "${PRODUCT_NAME} Installer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${PRODUCT_VERSION}"

Section "Main Program" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  
  ; Install main program and DLLs
  File "..\bin\mota.exe"
  File "..\mota-install\*.dll"
  
  ; Install directories
  SetOutPath "$INSTDIR\mota-include"
  File /r "..\mota-include\*.*"
  
  SetOutPath "$INSTDIR\template"
  File /r "..\template\*.*"
  
  SetOutPath "$INSTDIR\examples"
  File /r "..\examples\*.*"
  
  ; Create Start Menu shortcuts
  CreateDirectory "$SMPROGRAMS\Mota"
  CreateShortCut "$SMPROGRAMS\Mota\Mota Compiler.lnk" "$INSTDIR\mota.exe" "--help"
  CreateShortCut "$SMPROGRAMS\Mota\Examples.lnk" "$INSTDIR\examples"
  CreateShortCut "$SMPROGRAMS\Mota\Uninstall Mota.lnk" "$INSTDIR\uninst.exe"
  
  ; Create Desktop shortcut (optional)
  CreateShortCut "$DESKTOP\Mota Compiler.lnk" "$INSTDIR\mota.exe" "--help"
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\Mota\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\mota.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\mota.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  
  ; Add to system PATH (simple append)
  ReadRegStr $0 HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "PATH"
  WriteRegExpandStr HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "PATH" "$0;$INSTDIR"
  
  ; Set MOTA_INCLUDE environment variable
  WriteRegExpandStr HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "MOTA_INCLUDE" "$INSTDIR\mota-include"
  
  ; Notify system that environment variables have changed
  SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=5000
SectionEnd

; Uninstaller
Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) has been successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  ; Note: PATH cleanup is complex and risky, so we skip it in this simple version
  ; Users can manually remove the path if needed
  
  ; Remove MOTA_INCLUDE environment variable
  DeleteRegValue HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "MOTA_INCLUDE"
  
  SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=5000
  
  ; Delete files
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\mota.exe"
  Delete "$INSTDIR\*.dll"
  
  ; Delete directories
  RMDir /r "$INSTDIR\mota-include"
  RMDir /r "$INSTDIR\template"
  RMDir /r "$INSTDIR\examples"
  
  ; Delete shortcuts
  Delete "$SMPROGRAMS\Mota\Mota Compiler.lnk"
  Delete "$SMPROGRAMS\Mota\Examples.lnk"
  Delete "$SMPROGRAMS\Mota\Website.lnk"
  Delete "$SMPROGRAMS\Mota\Uninstall Mota.lnk"
  Delete "$DESKTOP\Mota Compiler.lnk"
  
  RMDir "$SMPROGRAMS\Mota"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd 