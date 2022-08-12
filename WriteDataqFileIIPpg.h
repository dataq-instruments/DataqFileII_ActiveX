#if !defined(AFX_WRITEDATAQFILEIIPPG_H__3E807CAF_AD5A_4143_8C4C_CE52E907DC2D__INCLUDED_)
#define AFX_WRITEDATAQFILEIIPPG_H__3E807CAF_AD5A_4143_8C4C_CE52E907DC2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// WriteDataqFileIIPpg.h : Declaration of the CWriteDataqFileIIPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIIPropPage : See WriteDataqFileIIPpg.cpp.cpp for implementation.

class CWriteDataqFileIIPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CWriteDataqFileIIPropPage)
	DECLARE_OLECREATE_EX(CWriteDataqFileIIPropPage)

// Constructor
public:
	CWriteDataqFileIIPropPage();

// Dialog Data
	//{{AFX_DATA(CWriteDataqFileIIPropPage)
	enum { IDD = IDD_PROPPAGE_WRITEDATAQFILEII };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CWriteDataqFileIIPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITEDATAQFILEIIPPG_H__3E807CAF_AD5A_4143_8C4C_CE52E907DC2D__INCLUDED)
