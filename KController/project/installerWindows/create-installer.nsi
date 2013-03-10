; KController installer script.
; Thanks to Sylvain :-)

!include "MUI2.nsh"

SetCompressor /SOLID lzma

!define VERSION 0.0.1
!define PRODUCT_NAME "KController"
!define PUBLISHER_NAME "FreeSoft"

!define MUI_ICON "Icon.ico"
!define MUI_UNICON "Icon.ico"

!ifndef VERSION
!error "VERSION not defined"
!endif
!ifndef PRODUCT_NAME
!error "PRODUCT_NAME not defined"
!endif
!ifndef PUBLISHER_NAME
!error "PUBLISHER_NAME not defined"
!endif

Name "${PRODUCT_NAME} ${VERSION}"
OutFile "${PRODUCT_NAME}-${VERSION}-windows.exe"
InstallDir "$PROGRAMFILES\${PUBLISHER_NAME}\${PRODUCT_NAME}"
InstallDirRegKey HKCU "Software\${PUBLISHER_NAME}\${PRODUCT_NAME}" "InstallDir"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!define MUI_FINISHPAGE_RUN "$INSTDIR\KController.exe"
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"

; Copy lang file and release version
!system "copy ..\..\Release\${PRODUCT_NAME}.exe result\${PRODUCT_NAME}.exe"
!system "copy ..\..\Release\${PRODUCT_NAME}.exe ${PRODUCT_NAME}.exe"

Section "Program" main_section
	SetOutPath "$INSTDIR"
	SetCompress force
	File /r /x *.psd /x .svn /x .DS_Store result\*.*
	
	SetOutPath "$INSTDIR"
	WriteUninstaller "Uninstall.exe"
	WriteRegStr HKCU "Software\${PUBLISHER_NAME}\${PRODUCT_NAME}" "InstallDir" $INSTDIR
	WriteRegStr HKCU "Software\${PUBLISHER_NAME}\${PRODUCT_NAME}" "Version" ${VERSION}
	CreateDirectory "$SMPROGRAMS\${PUBLISHER_NAME}"
	CreateDirectory "$SMPROGRAMS\${PUBLISHER_NAME}\${PRODUCT_NAME}"
	CreateShortCut "$SMPROGRAMS\${PUBLISHER_NAME}\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\${PRODUCT_NAME}.exe"
	CreateShortCut "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\${PRODUCT_NAME}.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "DisplayName" "${PRODUCT_NAME}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "UninstallString" '"$INSTDIR\Uninstall.exe"'
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "NoModify" 1
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "NoRepair" 1
SectionEnd

Section "-CRT" crt_section
	GetTempFileName $0
	File /oname=$0 vcredist_x86.exe
	ExecWait "$0 /q"
	Delete $0
    GetTempFileName $1
	File /oname=$1 vcredist_x86_2012.exe
	ExecWait "$1 /q"
	Delete $1
SectionEnd

Section "Uninstall"
  Delete "$INSTDIR\Uninstall.exe"
  Delete "$SMPROGRAMS\${PUBLISHER_NAME}\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk"
  Delete "$DESKTOP\${PRODUCT_NAME}.lnk"
  RMDir /r "$INSTDIR"
  RMDir /r "$SMPROGRAMS\${PUBLISHER_NAME}"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
SectionEnd

Function VersionCheck
	Exch $0 ;second versionnumber
	Exch
	Exch $1 ;first versionnumber
	Push $R0 ;counter for $0
	Push $R1 ;counter for $1
	Push $3 ;temp char
	Push $4 ;temp string for $0
	Push $5 ;temp string for $1
	StrCpy $R0 "-1"
	StrCpy $R1 "-1"
 Start:
	StrCpy $4 ""
 DotLoop0:
	IntOp $R0 $R0 + 1
	StrCpy $3 $0 1 $R0
	StrCmp $3 "" DotFound0
	StrCmp $3 "." DotFound0
	StrCpy $4 $4$3
	Goto DotLoop0
 DotFound0:
	StrCpy $5 ""
 DotLoop1:
	IntOp $R1 $R1 + 1
	StrCpy $3 $1 1 $R1
	StrCmp $3 "" DotFound1
	StrCmp $3 "." DotFound1
	StrCpy $5 $5$3
	Goto DotLoop1
 DotFound1:
	Strcmp $4 "" 0 Not4
	StrCmp $5 "" Equal
	Goto Ver2Less
 Not4:
	StrCmp $5 "" Ver2More
	IntCmp $4 $5 Start Ver2Less Ver2More
 Equal:
	StrCpy $0 "0"
	Goto Finish
 Ver2Less:
	StrCpy $0 "1"
	Goto Finish
 Ver2More:
	StrCpy $0 "2"
 Finish:
	Pop $5
	Pop $4
	Pop $3
	Pop $R1
	Pop $R0
	Pop $1
	Exch $0
FunctionEnd

Function CheckInstalled
	ReadRegStr $0 HKCU "Software\${PUBLISHER_NAME}\${PRODUCT_NAME}" "Version"
	IfErrors notInstalled
	Push $0
	Push ${VERSION}
	Call VersionCheck
	Pop $1
	IntCmp $1 1 installedIsNewer installedIsSame installedIsOlder
 installedIsNewer:
	MessageBox MB_YESNO "Setup has detected that a version $0 is already installed$\nDo you want to downgrade to version ${VERSION} ?" IDYES uninstallPrevious
	Abort "Aborted!"
	Goto done
 installedIsSame:
	MessageBox MB_YESNO "Setup has detected that ${PRODUCT_NAME} is already installed$\nDo you want to re-install ?" IDYES uninstallPrevious
	Abort "Aborted!"
	Goto done
 installedIsOlder:
	MessageBox MB_YESNO "Setup has detected that version $0 is installed - do you want to upgrade to version ${VERSION} ?" IDYES uninstallPrevious
	Abort "Aborted!"
	Goto done
 uninstallPrevious:
	ExecWait '"$INSTDIR\Uninstall.exe" _?=$INSTDIR'
 notInstalled:
 done:
FunctionEnd

Function CheckDeps
	; always selected for now
	!insertmacro SelectSection ${crt_section}
FunctionEnd

Function .onInit
	Call CheckInstalled
	Call CheckDeps
FunctionEnd
