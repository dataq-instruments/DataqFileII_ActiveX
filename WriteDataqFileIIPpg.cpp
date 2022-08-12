// WriteDataqFileIIPpg.cpp : Implementation of the CWriteDataqFileIIPropPage property page class.

#include "stdafx.h"
#include "DataqFileII.h"
#include "WriteDataqFileIIPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CWriteDataqFileIIPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CWriteDataqFileIIPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CWriteDataqFileIIPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWriteDataqFileIIPropPage, "DATAQFILEII.WriteDataqFileIIPropPage.1",
	0xd2ea1e60, 0xc4f7, 0x4c26, 0xbe, 0xa3, 0xcd, 0x5d, 0x35, 0xcb, 0xf8, 0xe8)


/////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIIPropPage::CWriteDataqFileIIPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CWriteDataqFileIIPropPage

BOOL CWriteDataqFileIIPropPage::CWriteDataqFileIIPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_WRITEDATAQFILEII_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIIPropPage::CWriteDataqFileIIPropPage - Constructor

CWriteDataqFileIIPropPage::CWriteDataqFileIIPropPage() :
	COlePropertyPage(IDD, IDS_WRITEDATAQFILEII_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CWriteDataqFileIIPropPage)
	//}}AFX_DATA_INIT

	SetHelpInfo(_T("Names to appear in the control"), _T("DATAQFILEII.HLP"), 0);
}


/////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIIPropPage::DoDataExchange - Moves data between page and properties

void CWriteDataqFileIIPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CWriteDataqFileIIPropPage)
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIIPropPage message handlers
