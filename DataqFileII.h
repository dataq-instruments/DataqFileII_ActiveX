#if !defined(AFX_DATAQFILEII_H__1A407510_BED1_4420_B01E_4343FEBCDDBD__INCLUDED_)
#define AFX_DATAQFILEII_H__1A407510_BED1_4420_B01E_4343FEBCDDBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DataqFileII.h : main header file for DATAQFILEII.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDataqFileIIApp : See DataqFileII.cpp for implementation.

class CDataqFileIIApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAQFILEII_H__1A407510_BED1_4420_B01E_4343FEBCDDBD__INCLUDED)
