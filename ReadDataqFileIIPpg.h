#if !defined(AFX_READDATAQFILEIIPPG_H__FFC8D7A4_0738_4E65_B073_041DC24CE7F8__INCLUDED_)
#define AFX_READDATAQFILEIIPPG_H__FFC8D7A4_0738_4E65_B073_041DC24CE7F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ReadDataqFileIIPpg.h : Declaration of the CReadDataqFileIIPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIIPropPage : See ReadDataqFileIIPpg.cpp.cpp for implementation.

class CReadDataqFileIIPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CReadDataqFileIIPropPage)
	DECLARE_OLECREATE_EX(CReadDataqFileIIPropPage)

// Constructor
public:
	CReadDataqFileIIPropPage();

// Dialog Data
	//{{AFX_DATA(CReadDataqFileIIPropPage)
	enum { IDD = IDD_PROPPAGE_READDATAQFILEII };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CReadDataqFileIIPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READDATAQFILEIIPPG_H__FFC8D7A4_0738_4E65_B073_041DC24CE7F8__INCLUDED)
