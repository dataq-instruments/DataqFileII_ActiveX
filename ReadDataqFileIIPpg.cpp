// ReadDataqFileIIPpg.cpp : Implementation of the CReadDataqFileIIPropPage property page class.

#include "stdafx.h"
#include "DataqFileII.h"
#include "ReadDataqFileIIPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CReadDataqFileIIPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CReadDataqFileIIPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CReadDataqFileIIPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CReadDataqFileIIPropPage, "DATAQFILEII.ReadDataqFileIIPropPage.1",
	0xb2662edc, 0xaf70, 0x4e96, 0x82, 0x19, 0x51, 0x80, 0x52, 0x1f, 0x55, 0xae)


/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIIPropPage::CReadDataqFileIIPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CReadDataqFileIIPropPage

BOOL CReadDataqFileIIPropPage::CReadDataqFileIIPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_READDATAQFILEII_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIIPropPage::CReadDataqFileIIPropPage - Constructor

CReadDataqFileIIPropPage::CReadDataqFileIIPropPage() :
	COlePropertyPage(IDD, IDS_READDATAQFILEII_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CReadDataqFileIIPropPage)
	//}}AFX_DATA_INIT

	SetHelpInfo(_T("Names to appear in the control"), _T("DATAQFILEII.HLP"), 0);
}


/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIIPropPage::DoDataExchange - Moves data between page and properties

void CReadDataqFileIIPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CReadDataqFileIIPropPage)
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIIPropPage message handlers
