// ReadDataqFileIICtl.cpp : Implementation of the CReadDataqFileIICtrl ActiveX Control class.

#include "stdafx.h"
#include "log.h"
#include "DataqFileII.h"
#include "ReadDataqFileIICtl.h"
#include "ReadDataqFileIIPpg.h"
#define MAXCOMMENTBUFFER 327680
#define MAXEVENTBUFFER 24576
#define MKB 2 /* chndat data bit indicating time or event marker */
#define CH1 1 /* chndat data bit for event instead of time marker */
#define BPP 2
#define NEV (long)0x80000000L /* no event marker (file must have user anno) */

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CReadDataqFileIICtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CReadDataqFileIICtrl, COleControl)
	//{{AFX_MSG_MAP(CReadDataqFileIICtrl)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CReadDataqFileIICtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CReadDataqFileIICtrl)
	DISP_PROPERTY_EX(CReadDataqFileIICtrl, "BeginTime", GetBeginTime, SetNotSupported, VT_BSTR)
	DISP_PROPERTY_EX(CReadDataqFileIICtrl, "ChannelCount", GetChannelCount, SetNotSupported, VT_I2)
	DISP_PROPERTY_EX(CReadDataqFileIICtrl, "CurrentLocation", GetCurrentLocation, SetNotSupported, VT_I4)
	DISP_PROPERTY_EX(CReadDataqFileIICtrl, "EndTime", GetEndTime, SetNotSupported, VT_BSTR)
	DISP_PROPERTY_EX(CReadDataqFileIICtrl, "EventCount", GetEventCount, SetNotSupported, VT_I4)
	DISP_PROPERTY_EX(CReadDataqFileIICtrl, "FileName", GetFileName, SetFileName, VT_BSTR)
	DISP_PROPERTY_EX(CReadDataqFileIICtrl, "LastErrorCode", GetLastErrorCode, SetNotSupported, VT_I4)
	DISP_PROPERTY_EX(CReadDataqFileIICtrl, "TotalScans", GetTotalScans, SetNotSupported, VT_I4)
	DISP_PROPERTY_EX(CReadDataqFileIICtrl, "TotalDataPoints", GetTotalDataPoints, SetNotSupported, VT_I4)
	DISP_PROPERTY_EX(CReadDataqFileIICtrl, "FileType", GetFileType, SetNotSupported, VT_I4)
	DISP_PROPERTY_EX(CReadDataqFileIICtrl, "SampleRate", GetSampleRate, SetNotSupported, VT_R8)
	DISP_PROPERTY_EX(CReadDataqFileIICtrl, "AvandedOptions", GetAvandedOptions, SetAvandedOptions, VT_I2)
	DISP_FUNCTION(CReadDataqFileIICtrl, "Close", Close, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CReadDataqFileIICtrl, "EUTag", EUTag, VT_BSTR, VTS_I2)
	DISP_FUNCTION(CReadDataqFileIICtrl, "GetData", GetData, VT_VARIANT, VTS_I4 VTS_I2)
	DISP_FUNCTION(CReadDataqFileIICtrl, "GetDataEx", GetDataEx, VT_EMPTY, VTS_PR8 VTS_I4)
	DISP_FUNCTION(CReadDataqFileIICtrl, "GetDataExB", GetDataExB, VT_I4, VTS_PI2 VTS_I4)
	DISP_FUNCTION(CReadDataqFileIICtrl, "GetIntrcpt", GetIntrcpt, VT_R8, VTS_I2)
	DISP_FUNCTION(CReadDataqFileIICtrl, "GetSlope", GetSlope, VT_R8, VTS_I2)
	DISP_FUNCTION(CReadDataqFileIICtrl, "GoToEventMarker", GoToEventMarker, VT_EMPTY, VTS_I4 VTS_I2)
	DISP_FUNCTION(CReadDataqFileIICtrl, "GoToMark", GoToMark, VT_EMPTY, VTS_I4 VTS_I2)
	DISP_FUNCTION(CReadDataqFileIICtrl, "Location2Time", Location2Time, VT_BSTR, VTS_I4)
	DISP_FUNCTION(CReadDataqFileIICtrl, "MapErrMessage", MapErrMessage, VT_BSTR, VTS_I4)
	DISP_FUNCTION(CReadDataqFileIICtrl, "MoveTo", MoveTo, VT_EMPTY, VTS_I4 VTS_I2)
	DISP_FUNCTION(CReadDataqFileIICtrl, "Open", Open, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CReadDataqFileIICtrl, "GoToTime", GoToTime, VT_I4, VTS_R8)
	DISP_PROPERTY_PARAM(CReadDataqFileIICtrl, "EventDTStamp", GetEventDTStamp, SetNotSupported, VT_BSTR, VTS_I4)
	DISP_PROPERTY_PARAM(CReadDataqFileIICtrl, "EventLocation", GetEventLocation, SetNotSupported, VT_I4, VTS_I4)
	DISP_PROPERTY_PARAM(CReadDataqFileIICtrl, "UserChnAn", GetUserChnAn, SetNotSupported, VT_BSTR, VTS_I2)
	DISP_PROPERTY_PARAM(CReadDataqFileIICtrl, "EventComment", GetEventComment, SetNotSupported, VT_BSTR, VTS_I4)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CReadDataqFileIICtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CReadDataqFileIICtrl, COleControl)
	//{{AFX_EVENT_MAP(CReadDataqFileIICtrl)
	EVENT_CUSTOM("ControlError", FireControlError, VTS_I4)
	EVENT_CUSTOM("EndOfFile", FireEndOfFile, VTS_NONE)
	EVENT_CUSTOM("FileError", FireFileError, VTS_I4)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

BEGIN_PROPPAGEIDS(CReadDataqFileIICtrl, 1)
	PROPPAGEID(CReadDataqFileIIPropPage::guid)
END_PROPPAGEIDS(CReadDataqFileIICtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CReadDataqFileIICtrl, "DATAQFILEII.ReadDataqFileIICtrl.1",
	0xfedab90, 0x783, 0x46d5, 0x8e, 0x45, 0xf, 0xc4, 0x4b, 0x46, 0xa0, 0xb9)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CReadDataqFileIICtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DReadDataqFileII =
		{ 0xa554de2c, 0xebee, 0x4608, { 0x89, 0x27, 0x53, 0xf9, 0xd4, 0x5e, 0xc1, 0x97 } };
const IID BASED_CODE IID_DReadDataqFileIIEvents =
		{ 0x145ce69f, 0xcd75, 0x4ef7, { 0xb8, 0x4a, 0xcc, 0xb5, 0x84, 0x53, 0x78, 0xa8 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwReadDataqFileIIOleMisc =
	OLEMISC_INVISIBLEATRUNTIME |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CReadDataqFileIICtrl, IDS_READDATAQFILEII, _dwReadDataqFileIIOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIICtrl::CReadDataqFileIICtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CReadDataqFileIICtrl

BOOL CReadDataqFileIICtrl::CReadDataqFileIICtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_READDATAQFILEII,
			IDB_READDATAQFILEII,
			afxRegApartmentThreading,
			_dwReadDataqFileIIOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIICtrl::CReadDataqFileIICtrl - Constructor

CReadDataqFileIICtrl::CReadDataqFileIICtrl():m_Log("ReadDataqFileII.log")
{
	InitializeIIDs(&IID_DReadDataqFileII, &IID_DReadDataqFileIIEvents);

	int i;

	hWindaq=NULL;
	bUseUTC=FALSE;
	AvancedOptions=0;
	lmyWindaqFileHeaderSize=0;
	//WindaqFilePath[0]=0;
	lFilePosition=0;
	iTotalADChannel=0;
	TotalDataPoints=0;
	//bScaled=TRUE;
	SampleRate=0;
	ErrCode=0;
	bHiRes=FALSE;
	EventCount=0;
	myFileCodasHdr254.hdrc.anfbyt=0;
	myFileCodasHdr254.hdrc.intrvl=0;
	for (i=0; i<256; i++) {
		ChannelAnnotation[i][0]=0;
		ChannelAnnotation[i][39]=0;
	}

	bFileOK=false;

	iDebug = GetPrivateProfileInt("Global", "Debug", 0, "TPDATAQ.INI");

	myhEventBuffer=GlobalAlloc(GMEM_MOVEABLE|GMEM_NODISCARD|GMEM_ZEROINIT, MAXEVENTBUFFER*sizeof(long)); 
	if (myhEventBuffer!=NULL) 
		mypEventBuffer=(long *) GlobalLock (myhEventBuffer);
	else
		mypEventBuffer=(long *)NULL;

	myhCommentBuffer=GlobalAlloc(GMEM_MOVEABLE|GMEM_NODISCARD|GMEM_ZEROINIT, MAXCOMMENTBUFFER*sizeof(char)); 
	if (myhCommentBuffer!=NULL) 
		mypCommentBuffer=(char *) GlobalLock (myhCommentBuffer);
	else
		mypCommentBuffer=(char *)NULL;

	AfxMessageBox2("Constructor");
}


/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIICtrl::~CReadDataqFileIICtrl - Destructor

CReadDataqFileIICtrl::~CReadDataqFileIICtrl()
{
	if (bHiRes) {
		GlobalUnlock(acshdl);
		GlobalFree(acshdl);
		acshdl=NULL;
		acsbf=NULL;
		acslim=0;
		GlobalUnlock(evfhdl);
		GlobalFree(evfhdl);
		evfhdl=NULL;
		evfbf=NULL;
		evflim=0;
	}

	GlobalUnlock(myhEventBuffer);	
	GlobalFree (myhEventBuffer);

	GlobalUnlock(myhCommentBuffer);	
	GlobalFree (myhCommentBuffer);

	if (hWindaq!=NULL){
   		_lclose(hWindaq);
		hWindaq=NULL;
   	}
	AfxMessageBox2("Destructor");
}


/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIICtrl::OnDraw - Drawing function

void CReadDataqFileIICtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
CDC * pBackUpDC;
CBitmap * pBitmapOld=(CBitmap *)NULL;
CBrush myBrush;
CPen myNullPen;

	CBitmap * myBitMap = new CBitmap;
	CBitmap * oldBitmap;
	myBitMap->LoadBitmap(IDB_READDATAQFILEII);

    pBackUpDC = new CDC;
    pBackUpDC->CreateCompatibleDC(pdc);
	
	myBrush.CreateSolidBrush(0xc0c0c0); 
	myNullPen.CreatePen(PS_SOLID, 1, (COLORREF)0x000000);

    CPen * pPenOldChart = pdc->SelectObject(&myNullPen);
    CBrush * pBrushOldChart = pdc->SelectObject(&myBrush);  	
	oldBitmap=pBackUpDC->SelectObject(myBitMap);

	LOGFONT LogFont={0};
	CFont * pPrintFont = new CFont;  
	LogFont.lfHeight= 16;
	LogFont.lfQuality=PROOF_QUALITY; 
	lstrcpy(LogFont.lfFaceName, "Arial");
	pPrintFont->CreateFontIndirect(&LogFont);
	CFont * pOldFont= pdc->SelectObject(pPrintFont);

	pdc->SetBkColor((COLORREF)0xc0c0c0);
	
	pdc->FillRect(rcBounds, &myBrush);

	pdc->BitBlt(rcBounds.left+2,(rcBounds.top+rcBounds.bottom)/2-8,rcBounds.left+18,rcBounds.top+18,pBackUpDC,0,0,SRCCOPY);
	CString cstr="ReadDataqFile Control";
	pdc->TextOut(rcBounds.left+20,(rcBounds.top+rcBounds.bottom)/2-8,cstr);

	pdc->MoveTo(rcBounds.left,rcBounds.top);
	pdc->LineTo(rcBounds.right-1,rcBounds.top);
	pdc->LineTo(rcBounds.right-1,rcBounds.bottom-1);
	pdc->LineTo(rcBounds.left,rcBounds.bottom-1);
	pdc->LineTo(rcBounds.left,rcBounds.top);	
	
	pBackUpDC->SelectObject(oldBitmap);
	pdc->SelectObject(pPenOldChart);
    pdc->SelectObject(pBrushOldChart);
	pdc->SelectObject(pOldFont);
	delete pBackUpDC;
}


/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIICtrl::DoPropExchange - Persistence support

void CReadDataqFileIICtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Bool (pPX, "ScaledData", bScaled, FALSE);

	PX_String (pPX, _T("FileName"), cWindaqFilePath, _T("C:\\Sample.wdq"));

}


/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIICtrl::OnResetState - Reset control to default state

void CReadDataqFileIICtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}


/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIICtrl::AboutBox - Display an "About" box to the user

void CReadDataqFileIICtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_READDATAQFILEII);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIICtrl message handlers

void CReadDataqFileIICtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

BSTR CReadDataqFileIICtrl::GetBeginTime() 
{
	char cTemp[64];
	sprintime(cTemp, myFileCodasHdr254.hdrc.begtime);
	CString strResult = cTemp;

	return strResult.AllocSysString();
}

short CReadDataqFileIICtrl::GetChannelCount() 
{
	if (bFileOK){ 
		if (bWdcHasRemoteStorage && bWDC) 
			return iTotalADChannel-1;
		else
			return iTotalADChannel;
	}
	else 
		return 0;
}

void CReadDataqFileIICtrl::Close() 
{
	if (hWindaq!=NULL){
   		_lclose(hWindaq);
		hWindaq=NULL;
		if (bHiRes) {
			GlobalUnlock(acshdl);
			GlobalFree(acshdl);
			acshdl=NULL;
			acsbf=NULL;
			acslim=0;
			GlobalUnlock(evfhdl);
			GlobalFree(evfhdl);
			evfhdl=NULL;
			evfbf=NULL;
			evflim=0;
		}
   	}
	bStart=FALSE;
}

long CReadDataqFileIICtrl::GetCurrentLocation() 
{
	return lOldFilePosition;
}

BSTR CReadDataqFileIICtrl::EUTag(short Channel) 
{
	CString strResult;
	char * pchar;
	

	strResult="xxxxx";
	pchar=strResult.GetBuffer(6);
	sprintf(pchar, "%4s", myFileCodasHdr254.cary[Channel].an);

	return strResult.AllocSysString();
}

BSTR CReadDataqFileIICtrl::GetEndTime() 
{
	char cTemp[64];
	sprintime(cTemp, myFileCodasHdr254.hdrc.endtime);
	CString strResult = cTemp;

	return strResult.AllocSysString();
}


long CReadDataqFileIICtrl::GetEventCount() 
{
	return EventCount;
}

BSTR CReadDataqFileIICtrl::GetEventDTStamp(long idx) 
{
	int nEC;
	long * pLong;
	int idx_e;
	char cTemp[64];
	long mylong;

	if (idx<0 || idx>=EventCount || bWDC){
		FireControlError(ErrCode=-3000);
		CString strResult;
		return strResult.AllocSysString();
	}
	else{
		pLong = (signed long*)mypEventBuffer;
		nEC=0;
		for (idx_e=0; idx_e<MAXCOMMENTBUFFER;){
			if (nEC==idx) break;
			if (pLong[idx_e++]>=0){
				idx_e++; //We have the DTStamp
			}

			if (bHiRes){
				mylong=myFileCodasHdr254.hdrc.datbyt/2;
				mylong=-mylong;
			}
			else{
				mylong=-TotalDataPoints;
			}
			if (pLong[idx_e]<=mylong){
				idx_e++; //skip the comment pointer
			}
			nEC++;
		}

		if (pLong[idx_e++]>=0&&(!bHiRes || !(pLong[idx_e-1]%iTotalADChannel))){
			sprintime(cTemp, myFileCodasHdr254.hdrc.begtime+pLong[idx_e]);
			CString strResult = cTemp;

			return strResult.AllocSysString();
		}
		else{
			FireControlError(ErrCode=-3001);
			CString strResult;
			return strResult.AllocSysString();
		}
	}
}

long CReadDataqFileIICtrl::GetEventLocation(long idx) 
{
	int nEC;
	long * pLong;
	int idx_e;
	long mylong;


	if (idx<0 || idx>=EventCount || bWDC){
		FireControlError(ErrCode=-3000);
		if (bHiRes)
			return 0x80000000;
		else
			return -1;
	}
	else{
		pLong = (long*)mypEventBuffer;
		nEC=0;
		//iDebug=2;
		AfxMessageBox2("idx=", (long)idx);
		for (idx_e=0; idx_e<MAXEVENTBUFFER;){
			AfxMessageBox2("idx_e", (long)idx_e);
			if (nEC==idx) break;
			if (pLong[idx_e++]>=0&&(!bHiRes||!(pLong[idx_e-1]%iTotalADChannel))){
				AfxMessageBox2("We have the DTStamp", (long)pLong[idx_e]);
				idx_e++; //We have the DTStamp
			}
			if (bHiRes){
				mylong=myFileCodasHdr254.hdrc.datbyt/2;
				mylong=-mylong;
			}
			else{
				mylong=-TotalDataPoints;
			}
			if (pLong[idx_e]<=mylong){
				AfxMessageBox2("mylong", mylong);
				AfxMessageBox2("skip the comment pointer", (long)pLong[idx_e]);
				idx_e++; //skip the comment pointer
			}
			nEC++;
		}
		//iDebug=0;
		AfxMessageBox2("GetEventLocation=", (long)(pLong[idx_e]&0x7fffffff));
		
			
		if (bHiRes)
			return pLong[idx_e]; /* raw trailer value including sign & chan */
		else
			return abs(pLong[idx_e]);
	}

}

BSTR CReadDataqFileIICtrl::GetFileName() 
{
	CString strResult = cWindaqFilePath;;
	return strResult.AllocSysString();
}

void CReadDataqFileIICtrl::SetFileName(LPCTSTR lpszNewValue) 
{
	cWindaqFilePath = lpszNewValue;

	ErrCode=0;
	SampleRate=0;
	iTotalADChannel=0;
	TotalDataPoints=0;

	SetModifiedFlag();
	AfxMessageBox2 ((char *)lpszNewValue);
}

long CReadDataqFileIICtrl::GetFileType() 
{
	// TODO: Add your property handler here

	long i=0;
	if (bHiRes) i=i|2;
	if (bWDC) i=i|4;
	if (bUseBegTime) i=i|8;
	i=i|(WinDaqCircState & 0x7)<<4;
	if (bHasEvent) i=i|0x10;
	if (bHasChannelAnnotation) i=i|0x20;

	return i;
}

int CReadDataqFileIICtrl::ReadRawData(short * pshort, long Count)
{
	HANDLE myhDataBuffer;  
	short *mypDataBuffer; 
	short *tempshort;
	char *pchar;
	char *tempchar;
	int iMoveSize, i;

	tempshort=pshort;

	if (bWDC){
		AfxMessageBox2 ("WDC format");
		if (bWdcHasRemoteStorage){
			AfxMessageBox2("bWdcHasRemoteStorage=", (long)bWdcHasRemoteStorage);
			//We need to skip the last channel!
			myhDataBuffer=GlobalAlloc(GMEM_MOVEABLE|GMEM_NODISCARD|GMEM_ZEROINIT, (Count*iTotalADChannel)*2);
			if (myhDataBuffer==NULL) {
				return -1;
			}  
			tempshort= mypDataBuffer=(short *) GlobalLock (myhDataBuffer);


			if (lOldFilePosition>WdcScanBeforeWrapAround){ 
				AfxMessageBox2 ("No chance to overwrap!");
				//No chance to overwrap!
				_lread(hWindaq, mypDataBuffer, iTotalADChannel*Count*2);
			}
			else{
				if ((lOldFilePosition+Count)>=WdcScanBeforeWrapAround){
					AfxMessageBox2("Wrap around!");
					_lread(hWindaq, tempshort, iTotalADChannel*(WdcScanBeforeWrapAround-lOldFilePosition)*2);
					_llseek(hWindaq,lmyWindaqFileHeaderSize, FILE_BEGIN);
					tempshort+=iTotalADChannel*(WdcScanBeforeWrapAround-lOldFilePosition)*2;
					_lread(hWindaq, tempshort, iTotalADChannel*(Count-WdcScanBeforeWrapAround+lOldFilePosition)*2);
					AfxMessageBox2("New Location=", (long)_llseek(hWindaq,0,FILE_CURRENT));
				}
				else{
					AfxMessageBox2 ("No overwrap!");
					_lread(hWindaq, mypDataBuffer, iTotalADChannel*Count*2);
					//AfxMessageBox2("New Location=", (long)_llseek(hWindaq,0,FILE_CURRENT));
				}
			}

			//Copy the data, skipping the remote channel, to the user array
			AfxMessageBox2 ("Extract the real channels!");

			iMoveSize=iActualTotalADChannel*2;
			AfxMessageBox2 ("iMoveSize", (long)iMoveSize);
			AfxMessageBox2 ("Count", (long)Count);
			tempchar= (char*)mypDataBuffer;
			pchar=(char *)pshort;
			for (i=0; i<Count; i++){
				//Move all ad channels
				memmove (pchar, tempchar, iMoveSize);
				
				//Skip the remote channel
				pchar+=iMoveSize;  
				tempchar+=iMoveSize+2; //skip the remote channel
			}

			GlobalUnlock(myhDataBuffer);
			GlobalFree (myhDataBuffer);

		}
		else{
			AfxMessageBox2 ("lOldFilePosition", (long)lOldFilePosition);
			AfxMessageBox2 ("WdcScanBeforeWrapAround", (long)WdcScanBeforeWrapAround);
			if (lOldFilePosition>WdcScanBeforeWrapAround){ 
				AfxMessageBox2 ("No chance to overwrap!");
				//No chance to overwrap!
				_lread(hWindaq, pshort, iTotalADChannel*Count*2);
			}
			else{
				if ((lOldFilePosition+Count)>=WdcScanBeforeWrapAround){
					AfxMessageBox2("Wrap around!");
					_lread(hWindaq, pshort, iTotalADChannel*(WdcScanBeforeWrapAround-lOldFilePosition)*2);
					_llseek(hWindaq,lmyWindaqFileHeaderSize, FILE_BEGIN);
					pshort+=iTotalADChannel*(WdcScanBeforeWrapAround-lOldFilePosition)*2;
					_lread(hWindaq, pshort, iTotalADChannel*(Count-WdcScanBeforeWrapAround+lOldFilePosition)*2);
					AfxMessageBox2("New Location=", (long)_llseek(hWindaq,0,FILE_CURRENT));
				}
				else{
					AfxMessageBox2 ("No overwrap!");
					_lread(hWindaq, pshort, iTotalADChannel*Count*2);
					//AfxMessageBox2("New Location=", (long)_llseek(hWindaq,0,FILE_CURRENT));
				}
			}
		}
	}
	else{
		AfxMessageBox2 ("WDQ format");

		_lread(hWindaq, pshort, iTotalADChannel*Count*2);
	}

	return Count;
}

VARIANT CReadDataqFileIICtrl::GetData(long RequestCount, short Method) 
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	if (iTotalADChannel<=0) {
		AfxMessageBox2("ChannelCount<=0 @ GetData");
		return vaResult;
	}
    
	SAFEARRAY * psa;
	SAFEARRAYBOUND rgsabound[2];
	short * pshort;
	double *pdouble;
	int i, iChn;
	long Count=RequestCount; 
	HANDLE myhDataBuffer;  
	short *mypDataBuffer; 

	AfxMessageBox2("Current Location=", (long)_llseek(hWindaq,0,FILE_CURRENT));
	AfxMessageBox2("iTotalADChannel=", (long)iTotalADChannel);
	AfxMessageBox2("TotalDataPoints=", (long)TotalDataPoints);
	AfxMessageBox2("RequestCount=", (long)RequestCount);
	AfxMessageBox2("lFilePosition=", (long)lFilePosition);
	AfxMessageBox2("iActualTotalADChannel=", (long)iActualTotalADChannel);

	if (bDynamicFile){
		AfxMessageBox2("Dynamic File!");
		long lCurrent =  _llseek(hWindaq,0,FILE_CURRENT);
		long lTemp = _llseek(hWindaq,0,FILE_END);

		lTemp=lTemp-lmyWindaqFileHeaderSize;
		if (lTemp<0) lTemp=0;
		
		TotalDataPoints=lTemp/(2l*(long)iTotalADChannel);
		
		//char s [64];
		//sprintf (s, "%ld", TotalDataPoints);
		AfxMessageBox2("DynamicFile: TotalDataPts per Channel =", (long)TotalDataPoints);

		_llseek(hWindaq,lCurrent,FILE_BEGIN);
	}

	if ((lFilePosition+Count)>TotalDataPoints) {
		Count= TotalDataPoints-lFilePosition;
		FireEndOfFile();
		ErrCode=-1;
	}

	
	if (Count<0) {
		AfxMessageBox2("Negative ScanCount");
		return vaResult;
	}
	if (Count==0){
		AfxMessageBox2("Zero ScanCount");
		return vaResult;
	}

	lOldFilePosition=lFilePosition;
	lFilePosition=lFilePosition+Count;

	if (Method==0){
		AfxMessageBox2 ("Binary format");
		rgsabound[0].lLbound=0;
		if (bWDC && bWdcHasRemoteStorage){
			rgsabound[0].cElements=iTotalADChannel-1;
		}
		else{
			rgsabound[0].cElements=iTotalADChannel;
		}
		rgsabound[1].lLbound=0;
		rgsabound[1].cElements=RequestCount;

		psa=SafeArrayCreate(VT_I2,2,rgsabound);
		pshort=(short HUGEP *)psa->pvData;
		vaResult.vt=VT_I2+VT_ARRAY;	
		vaResult.parray=psa;
		
		if (ReadRawData(pshort, Count)==-1)	FireControlError(ErrCode=-9999);

	}
	else{
		AfxMessageBox2("Scaled Readings");
		myhDataBuffer=GlobalAlloc(GMEM_MOVEABLE|GMEM_NODISCARD|GMEM_ZEROINIT, (Count*iTotalADChannel)*sizeof(double));
		if (myhDataBuffer==NULL) {
			AfxMessageBox2("Failed to allocate buffer");
			return vaResult;
		}  
		
		rgsabound[0].lLbound=0;
		if (bWDC && bWdcHasRemoteStorage){
			rgsabound[0].cElements=iTotalADChannel-1;
		}
		else{
			rgsabound[0].cElements=iTotalADChannel;
		}
		rgsabound[1].lLbound=0;
		rgsabound[1].cElements=Count;
		psa=SafeArrayCreate(VT_R8,2,rgsabound);
		pdouble=(double HUGEP *)psa->pvData;
		vaResult.vt=VT_R8+VT_ARRAY;		
		vaResult.parray=psa;
           
		mypDataBuffer=(short *) GlobalLock (myhDataBuffer);

		//Read Count*iTotalADChannel data to mypDataBuffer
		if (ReadRawData(mypDataBuffer, Count)==-1)	{
			AfxMessageBox2("Failed to read raw data");
			FireControlError(ErrCode=-9999);
		}

		AfxMessageBox2("iActualTotalADChannel=", (long)iActualTotalADChannel);
		for (iChn=0; iChn<iActualTotalADChannel;iChn++){  
			AfxMessageBox2("iChn", (long)iChn);
			AfxMessageBox2("slope", (double)myFileCodasHdr254.cary[iChn].slope);
			AfxMessageBox2("intrcpt", (double)myFileCodasHdr254.cary[iChn].intrcpt);
		} 

		if (bHiRes){
			AfxMessageBox2("**** HiRes");
			for (i=0, iChn=0; i<Count*iActualTotalADChannel;i++){  
				int iTemp=mypDataBuffer[i]; 
				pdouble[i]=((double)iTemp * myFileCodasHdr254.cary[iChn].slope)/(double)4.0 + myFileCodasHdr254.cary[iChn].intrcpt;
				iChn++;
				if (iChn==iActualTotalADChannel) iChn=0;
			}  
		}
		else{
			for (i=0, iChn=0; i<Count*iActualTotalADChannel;i++){  
				int iTemp=mypDataBuffer[i]>>2; 
				//AfxMessageBox2("iTemp", (long)iTemp);
				pdouble[i]=(double)iTemp * myFileCodasHdr254.cary[iChn].slope + myFileCodasHdr254.cary[iChn].intrcpt;
				iChn++;
				if (iChn==iActualTotalADChannel) iChn=0;
			}  
		}
		GlobalUnlock(myhDataBuffer);
		GlobalFree (myhDataBuffer);
	}


	return vaResult;
}

void CReadDataqFileIICtrl::GetDataEx(double FAR* Buffer, long Count) 
{
	int i, iChn;
	HANDLE myhDataBuffer;  
	short *mypDataBuffer;  
	
	if (bDynamicFile){
		long lCurrent =  _llseek(hWindaq,0,FILE_CURRENT);
		long lTemp = _llseek(hWindaq,0,FILE_END);

		lTemp=lTemp-lmyWindaqFileHeaderSize;
		if (lTemp<0) lTemp=0;
		
		TotalDataPoints=lTemp/(2l*(long)iTotalADChannel);

		_llseek(hWindaq,lCurrent,FILE_BEGIN);
	}

	if (Count<=0) {
		FireControlError(ErrCode=-2000);
		
		return;
	}
	if ((lFilePosition+Count)>TotalDataPoints) {
		Count= TotalDataPoints-lFilePosition;
		ErrCode=-2001;
		FireEndOfFile();
	}
	lOldFilePosition=lFilePosition;
	lFilePosition=lFilePosition+Count;

	myhDataBuffer=GlobalAlloc(GMEM_MOVEABLE|GMEM_NODISCARD, (Count*iTotalADChannel)*2);
	if (myhDataBuffer==NULL) {
		FireControlError(ErrCode=-9999);
		
		return;
	}  
	
	mypDataBuffer=(short *) GlobalLock (myhDataBuffer);

	//Read Count*iTotalADChannel data to mypDataBuffer
	if (ReadRawData(mypDataBuffer, Count)==-1)	FireControlError(ErrCode=-9999);

	if (bHiRes){
		AfxMessageBox2("**** HiRes");
		for (i=0, iChn=0; i<Count*iActualTotalADChannel;i++){  
			int iTemp=mypDataBuffer[i]; 
			Buffer[i]=((double)iTemp * myFileCodasHdr254.cary[iChn].slope)/(double)4.0 + myFileCodasHdr254.cary[iChn].intrcpt;
			iChn++;
			if (iChn==iActualTotalADChannel) iChn=0;
		}  
	}
	else{
		for (i=0, iChn=0; i<Count*iActualTotalADChannel;i++){  
			int iTemp=mypDataBuffer[i]>>2;
			
			Buffer[i]=((double)iTemp * (double)myFileCodasHdr254.cary[iChn].slope) + (double)myFileCodasHdr254.cary[iChn].intrcpt;
			//AfxMessageBox2 ("Buffer", (double)Buffer[i]);
			iChn++;
			if (iChn==iActualTotalADChannel) iChn=0;
		}  
	}
	GlobalUnlock(myhDataBuffer);
	GlobalFree (myhDataBuffer);



}

long CReadDataqFileIICtrl::GetDataExB(short FAR* Buffer, long Count) 
{
	int i;

	if (bDynamicFile){
		long lCurrent =  _llseek(hWindaq,0,FILE_CURRENT);
		long lTemp = _llseek(hWindaq,0,FILE_END);

		lTemp=lTemp-lmyWindaqFileHeaderSize;
		if (lTemp<0) lTemp=0;
		
		TotalDataPoints=lTemp/(2l*(long)iTotalADChannel);

		_llseek(hWindaq,lCurrent,FILE_BEGIN);
	}

	if (Count<=0 || iTotalADChannel <=0) {
		FireControlError(ErrCode=-2000);
		
		return 0;
	}
	if ((lFilePosition+Count)>TotalDataPoints) {
		Count= TotalDataPoints-lFilePosition;
		ErrCode=-2001;
		FireEndOfFile();
	}

	lOldFilePosition=lFilePosition;
	lFilePosition=lFilePosition+Count;

	//Read Count*iTotalADChannel data to mypDataBuffer
	if ((i=ReadRawData(Buffer, Count))==-1)	FireControlError(ErrCode=-9999);


	return Count;

}

double CReadDataqFileIICtrl::GetIntrcpt(short Index) 
{
	if (Index<0 || Index>254) return 0.0;
	return myFileCodasHdr254.cary[Index].intrcpt;
}

double CReadDataqFileIICtrl::GetSlope(short Index) 
{
	if (Index<0 || Index>254) return 0.0;
	return myFileCodasHdr254.cary[Index].slope;;
}

void CReadDataqFileIICtrl::GoToEventMarker(long Event, short Channel) 
{
	if (bWDC) return;
	if (hWindaq==NULL) return;
	if (Event==0) return;
	//if (lOldFilePosition>=TotalDataPoints) return;
	if (Channel<0) return;
	if (Channel>=iTotalADChannel) return;

	HANDLE myhDataBuffer;  
	short *mypDataBuffer;
	long EventCount=0;

	myhDataBuffer=GlobalAlloc(GMEM_MOVEABLE|GMEM_NODISCARD, (iTotalADChannel)*2);
	if (myhDataBuffer==NULL) {
		FireControlError(ErrCode=-9999);
		return;
	}  
      
	mypDataBuffer=(short *) GlobalLock (myhDataBuffer);

	if (Event>0){
		lOldFilePosition++;

		if (_llseek(hWindaq, lmyWindaqFileHeaderSize+(lOldFilePosition) * (long)iTotalADChannel *2, FILE_BEGIN)==HFILE_ERROR){
			FireFileError(ErrCode=GetLastError());
		}

		while (EventCount!=Event){
			if (_lread(hWindaq, (void *)mypDataBuffer, (unsigned int) (iTotalADChannel*2))!=(unsigned int)iTotalADChannel*2){
				lOldFilePosition=lFilePosition=TotalDataPoints;
				FireEndOfFile();
				goto got_eof;
			}
			if (lFilePosition>TotalDataPoints){
				lOldFilePosition=lFilePosition=TotalDataPoints;
				FireEndOfFile();
				goto got_eof;
			}

			if (mypDataBuffer[Channel] & 0x0002){ 
				EventCount++;
				if (EventCount==Event) {
					goto got_it;
				}
			}
			lOldFilePosition ++;
			lFilePosition=lOldFilePosition;
		}

got_it:
got_eof:
		if (_llseek(hWindaq, lmyWindaqFileHeaderSize+lOldFilePosition * (long)iTotalADChannel *2, FILE_BEGIN)==HFILE_ERROR){
			FireFileError(ErrCode=GetLastError());
		}
	}
	else{
		lOldFilePosition=lOldFilePosition-2;
		if (lOldFilePosition<=0) {
			lFilePosition=lOldFilePosition=0;
			goto got_it2;
		}

		while (EventCount!=abs(Event)){
			if (_llseek(hWindaq, lmyWindaqFileHeaderSize+(lOldFilePosition) * (long)iTotalADChannel *2, FILE_BEGIN)==HFILE_ERROR){
				AfxMessageBox2("Drops out!");
				FireFileError(ErrCode=GetLastError());
			}
			
			if (_lread(hWindaq, mypDataBuffer, (unsigned int) iTotalADChannel*2)!=(unsigned int)iTotalADChannel*2){
				lOldFilePosition=lFilePosition=0;
				goto got_it2;
			}

			if (lFilePosition>TotalDataPoints){
				lOldFilePosition=lFilePosition=0;
				goto got_it2;
			}

			if (mypDataBuffer[Channel] & 0x0002){ 
				EventCount++;
				if (EventCount==abs(Event)) {
					goto got_it2;
				}
			}
			lOldFilePosition=lOldFilePosition-1;
			lFilePosition=lOldFilePosition;
			if (lOldFilePosition<=0) {
				lFilePosition=lOldFilePosition=0;
				goto got_it2;
			}

		}

got_it2:
		if (_llseek(hWindaq, lmyWindaqFileHeaderSize+lOldFilePosition * (long)iTotalADChannel *2, FILE_BEGIN)==HFILE_ERROR){
			FireFileError(ErrCode=GetLastError());
		}

	}

	GlobalUnlock(myhDataBuffer);
	GlobalFree (myhDataBuffer);


}

void CReadDataqFileIICtrl::GoToMark(long Event, short Channel) 
{
	// TODO: Add your dispatch handler code he	if (hWindaq==NULL) return;
	if (Event==0) return;
	if (bWDC) return;
	//if (lOldFilePosition>=TotalDataPoints) return;
	if (Channel<0) return;
	if (Channel>=iTotalADChannel) return;

	HANDLE myhDataBuffer;  
	short *mypDataBuffer;
	long EventCount=0;

	myhDataBuffer=GlobalAlloc(GMEM_MOVEABLE|GMEM_NODISCARD, (iTotalADChannel)*2);
	if (myhDataBuffer==NULL) {
		FireControlError(ErrCode=-9999);
		return;
	}  
      
	mypDataBuffer=(short *) GlobalLock (myhDataBuffer);

	if (Event>0){
		lOldFilePosition++;

		if (_llseek(hWindaq, lmyWindaqFileHeaderSize+(lOldFilePosition) * (long)iTotalADChannel *2, FILE_BEGIN)==HFILE_ERROR){
			FireFileError(ErrCode=GetLastError());
		}

		while (EventCount!=Event){
			if (_lread(hWindaq, mypDataBuffer, (unsigned int) iTotalADChannel*2)!=(unsigned int)iTotalADChannel*2){
				lOldFilePosition=lFilePosition=TotalDataPoints;
				FireEndOfFile();
				goto got_eof;
			}

			if (mypDataBuffer[Channel] & 0x0003){ 
				EventCount++;
				if (EventCount==Event) {
					goto got_it;
				}
			}
			lOldFilePosition ++;
			lFilePosition=lOldFilePosition;
		}

got_it:
got_eof:
		if (_llseek(hWindaq, lmyWindaqFileHeaderSize+lOldFilePosition * (long)iTotalADChannel *2, FILE_BEGIN)==HFILE_ERROR){
			FireFileError(ErrCode=GetLastError());
		}
	}
	else{
		lOldFilePosition=lOldFilePosition-2;
		if (lOldFilePosition<=0) {
			lFilePosition=lOldFilePosition=0;
			goto got_it2;
		}

		while (EventCount!=abs(Event)){
			if (_llseek(hWindaq, lmyWindaqFileHeaderSize+(lOldFilePosition) * (long)iTotalADChannel *2, FILE_BEGIN)==HFILE_ERROR){
				FireFileError(ErrCode=GetLastError());
			}
			
			if (_lread(hWindaq, mypDataBuffer, (unsigned int) iTotalADChannel*2)!=(unsigned int)iTotalADChannel*2){
				lOldFilePosition=lFilePosition=0;
				goto got_it2;
			}

			if (mypDataBuffer[Channel] & 0x0003){ 
				EventCount++;
				if (EventCount==abs(Event)) {
					goto got_it2;
				}
			}
			lOldFilePosition=lOldFilePosition-1;
			lFilePosition=lOldFilePosition;
			if (lOldFilePosition<=0) {
				lFilePosition=lOldFilePosition=0;
				goto got_it2;
			}

		}

got_it2:
		if (_llseek(hWindaq, lmyWindaqFileHeaderSize+lOldFilePosition * (long)iTotalADChannel *2, FILE_BEGIN)==HFILE_ERROR){
			FireFileError(ErrCode=GetLastError());
		}

	}

	GlobalUnlock(myhDataBuffer);
	GlobalFree (myhDataBuffer);

}

long CReadDataqFileIICtrl::GetLastErrorCode() 
{
	return ErrCode;
}

BSTR CReadDataqFileIICtrl::Location2Time(long scan) 
{
	static double remaining_f;
	long * pLong;
	int idx_e;
	char cTemp[64];
	long begtime =myFileCodasHdr254.hdrc.begtime; 
	long scan_offset;
	long prevscan=0;
	long prevstamp=0;
	double f;
	int nEC;
	long mylong;

	if (bHiRes) {
		mylong=myFileCodasHdr254.hdrc.datbyt/2;
		mylong=-mylong;
	}
	else
		mylong=-TotalDataPoints;

	scan_offset=scan;

	
	//iDebug=2;
	if (scan==-1){
		sprintf(cTemp, "%f", remaining_f);
		CString strResult = cTemp;

		return strResult.AllocSysString();
	}
	if (scan==-2){
		bUseUTC=true;
		sprintf(cTemp, "UTC");
		CString strResult = cTemp;

		return strResult.AllocSysString();
	}
	if (scan==-3){
		bUseUTC=false;
		sprintf(cTemp, "Local");
		CString strResult = cTemp;

		return strResult.AllocSysString();
	}
	//iDebug=1;
	//AfxMessageBox2("Location2Time=", (long)scan);
	if (begtime==0 && SampleRate>0.0){
		begtime =myFileCodasHdr254.hdrc.endtime-long(TotalDataPoints/SampleRate);
		AfxMessageBox2("use endtime to calculate begtime");
	}
	AfxMessageBox2("begtime", (long)begtime);
	
	if (scan>=TotalDataPoints){
		
		FireControlError(ErrCode=-3000);
		CString strResult;
		return strResult.AllocSysString();
	}

	//iDebug=2;

	if (bHiRes){
		for (idx_e=0, nEC=0; idx_e<(int)nacs; nEC++){
			if (nEC==(int)nacs) {
				AfxMessageBox2("   Reached end of events");
				AfxMessageBox2("   scan=", (long)scan_offset);
				AfxMessageBox2("   prevscan=", (long)prevscan);
				AfxMessageBox2("   prevstamp=", (long)prevstamp);
				break;	
			}
			if (abs(acsbf[idx_e][0])>scan*iTotalADChannel) {
				AfxMessageBox2("   Found it", (long)abs(acsbf[idx_e][0]));
				AfxMessageBox2("   scan=", (long)scan_offset);
				AfxMessageBox2("   prevscan=", (long)prevscan);
				AfxMessageBox2("   prevstamp=", (long)prevstamp);
				break; 
			}
			if (acsbf[idx_e][0]>=0 && !(acsbf[idx_e][0]%iTotalADChannel)){
				prevscan=acsbf[idx_e][0]/iTotalADChannel; 
				prevstamp=acsbf[idx_e++][1];
				AfxMessageBox2("idx_e = ",(long)idx_e);
			}
		}
	}
	else {
		pLong = (signed long*)mypEventBuffer;
		//AfxMessageBox2("MAXEVENTBUFFER=", (long)MAXEVENTBUFFER);
		for (idx_e=0, nEC=0; idx_e<MAXEVENTBUFFER; nEC++){
			//AfxMessageBox2("idx_e=", (long)idx_e);
			//AfxMessageBox2("scan=", (long)scan);
			//AfxMessageBox2("pLong[idx_e]=", (long)pLong[idx_e]);
			if (nEC==EventCount) {
				AfxMessageBox2("   Reached end of events");
				AfxMessageBox2("   scan=", (long)scan_offset);
				AfxMessageBox2("   prevscan=", (long)prevscan);
				AfxMessageBox2("   prevstamp=", (long)prevstamp);
				break;
			}
			if (abs(pLong[idx_e])>scan) {
				AfxMessageBox2("   Found it", (long)abs(pLong[idx_e]));
				AfxMessageBox2("   scan=", (long)scan_offset);
				AfxMessageBox2("   prevscan=", (long)prevscan);
				AfxMessageBox2("   prevstamp=", (long)prevstamp);
				break; 
			}
			if (pLong[idx_e++]>=0){
				//we only capture the scan and stamp when stamp is available
				prevscan=abs(pLong[idx_e-1]); 
				prevstamp=pLong[idx_e++];
			}
			if (pLong[idx_e]<=mylong){
				idx_e++; //skip the comment pointer
				AfxMessageBox2("   Skip");
			}
		}

	}
	f= (double)(scan_offset - prevscan)*myFileCodasHdr254.hdrc.intrvl;

	sprintime(cTemp, prevstamp + (long)f);
	remaining_f=f-(long)f;
	
	AfxMessageBox2(cTemp);
	//sprintf (cTemp1,"%f",f-(long)f);
	//sprintf (cTemp2, "%s %s", cTemp, cTemp1);
	CString strResult = cTemp;
	//iDebug=0;
	return strResult.AllocSysString();
}

BSTR CReadDataqFileIICtrl::MapErrMessage(long errcode) 
{
	char sTemp[64]="";
	if (errcode>0){
		CString strResult="File access error, please check Microsoft's GetLastError()";
		return strResult.AllocSysString();
	}
	switch(errcode){
	case -250: 
		sprintf (sTemp, "File path exceed 250 chars");
		break;
	case -29:
		sprintf (sTemp, "Invalid WWB file");
		break;
	case -99999:
		sprintf (sTemp, "Invalid sample rate");
		break;
	case -2000:
		sprintf (sTemp, "Invalid parameter(s)");
		break;
	case -9999:
		sprintf (sTemp, "Failed to allocate memory for the transfer");
		break;
	case -3000:
		sprintf (sTemp, "Event index out of the range");
		break;
	case -3001:
		sprintf (sTemp, "Requested event info not available");
		break;
	default:
		sprintf (sTemp, "Unknown error");
		break;
	}
	CString strResult=sTemp;
	return strResult.AllocSysString();

}

void CReadDataqFileIICtrl::MoveTo(long Offset, short Origin) 
{
	long FPointer;
	AfxMessageBox2("MoveTo", Offset, (long)Origin);
	if (Origin==0){
		if (hWindaq!=NULL && Offset>=0){
			//From the beginning!
			lFilePosition= Offset; //*2 makes it 16-bit alignment

			if (lFilePosition>TotalDataPoints) {
				if (Wdc1stScan>0)
					lFilePosition=Wdc1stScan-1;
				else
					lFilePosition=TotalDataPoints;
				_llseek(hWindaq, lmyWindaqFileHeaderSize+lFilePosition * (long)iTotalADChannel*2, FILE_BEGIN);
				FireEndOfFile();
				ErrCode=-9999;
			}
			else{
				if(lFilePosition>WdcScanBeforeWrapAround){
					//Warps around!
					FPointer=lFilePosition-WdcScanBeforeWrapAround;
					_llseek(hWindaq, lmyWindaqFileHeaderSize + FPointer * (long)iTotalADChannel*2, FILE_BEGIN);
				}
				else{
					_llseek(hWindaq, lmyWindaqFileHeaderSize + Wdc1stData+lFilePosition * (long)iTotalADChannel*2, FILE_BEGIN);
				}

				FireEndOfFile();
				ErrCode=-9999;
			}
			lOldFilePosition=lFilePosition;
		}
	}
	else{
		long l;
		if (hWindaq!=NULL){
			l=lOldFilePosition+Offset;

			if (l>TotalDataPoints) {
				if (Wdc1stScan>0)
					lFilePosition=Wdc1stScan-1;
				else
					lFilePosition=TotalDataPoints;
				_llseek(hWindaq, lmyWindaqFileHeaderSize+lFilePosition * (long)iTotalADChannel*2, FILE_BEGIN);
				FireEndOfFile();
				ErrCode=-9999;
			}
			else{
				if (l<=0) {
					lFilePosition=0;
				}
				else lFilePosition=l;

				if(lFilePosition>WdcScanBeforeWrapAround){
					//Warps around!
					FPointer=lFilePosition-WdcScanBeforeWrapAround;
					if (_llseek(hWindaq, lmyWindaqFileHeaderSize + FPointer * (long)iTotalADChannel*2, FILE_BEGIN)==HFILE_ERROR)
						FireFileError(ErrCode=GetLastError());
				}
				else{
					if (_llseek(hWindaq, lmyWindaqFileHeaderSize + Wdc1stData+lFilePosition * (long)iTotalADChannel*2, FILE_BEGIN)==HFILE_ERROR)
						FireFileError(ErrCode=GetLastError());
				}

			}
		}
		lOldFilePosition=lFilePosition;
	}


}

void CReadDataqFileIICtrl::Open() 
{
	int i, j;
	char c;
	long * pLong;
	int idx_e;
	
	bFileOK=FALSE;

	bDynamicFile=FALSE;
	if (hWindaq!=NULL){
   		_lclose(hWindaq);
		hWindaq=NULL;
		if (bHiRes) {
			GlobalUnlock(acshdl);
			GlobalFree(acshdl);
			acshdl=NULL;
			acslim=0;
			GlobalUnlock(evfhdl);
			GlobalFree(evfhdl);
			evfhdl=NULL;
			evflim=0;
		}
   	}

	bHasEvent=FALSE;
	bHasChannelAnnotation=FALSE;

	memset(mypCommentBuffer, 0, MAXCOMMENTBUFFER*sizeof(char));
	memset(mypEventBuffer, 0, MAXEVENTBUFFER*sizeof(long));

	for (i=0; i<256; i++) {
		ChannelAnnotation[i][0]=0;
		ChannelAnnotation[i][39]=0;
	}

	bChanged=FALSE;
	
	int length=cWindaqFilePath.GetLength();
	if (length>250) {
		FireFileError(ErrCode=-250);
		return;
	}
	for (i=0; i<length; i++)
		WindaqFilePath[i]=cWindaqFilePath[i];
	WindaqFilePath[i]=0;
	
   	hWindaq=OpenFile(WindaqFilePath,
   	&OpenBuff,
   	OF_READ|OF_SHARE_DENY_NONE);
   	if (hWindaq==HFILE_ERROR){
		AfxMessageBox2 ("Failed to open file");
		FireFileError(ErrCode=GetLastError());
		
		hWindaq=NULL;  
		lmyWindaqFileHeaderSize=0;
   	}
	else{
		AfxMessageBox2("File opened");

		//Check Circ first!
   			
		_lread(hWindaq, &myFileCodasHdrCirc, sizeof(CODASHDRCIRC));

		if (myFileCodasHdrCirc.hdrc.hdrsiz>1156)
   			iTotalADChannel=myFileCodasHdrCirc.header[0] &0xff;       //We are dealing with big header
   		else
   			iTotalADChannel=myFileCodasHdrCirc.header[0] &0x1f;		


		if (iTotalADChannel<=0){
			AfxMessageBox2("WinDaq file corrupted: iTotalADChannel=", (long)iTotalADChannel);
			FireFileError(ErrCode=-29);
			return;

		}

		TotalDataPoints=myFileCodasHdrCirc.hdrc.datbyt/(2l*(long)iTotalADChannel);
		AfxMessageBox2("iTotalADChannel", (long)iTotalADChannel);
		AfxMessageBox2("TotalDataPoints", (long)TotalDataPoints);

		if (TotalDataPoints<=0){
			AfxMessageBox2("WinDaq file corrupted: TotalDataPoints=", (long)TotalDataPoints);
			FireFileError(ErrCode=-29);
			return;
		}

		if ((myFileCodasHdrCirc.hdrc.lmkeys & 0xC0) == 0xC0){
			bWDC=true;
			WinDaqCircState=2; //WinDaq/Circ acq complete
			Wdc1stScan=MAKELONG(myFileCodasHdrCirc.hdrc.pretrig , myFileCodasHdrCirc.hdrc.postrig);

			Wdc1stData=Wdc1stScan*iTotalADChannel*2;
			AfxMessageBox2("WinDaq/Circ acq complete", Wdc1stScan);
		}
		else if ((myFileCodasHdrCirc.hdrc.lmkeys & 0xC0) == 0x80){
			bWDC=true;
			WinDaqCircState=1; //WinDaq/Circ wrapped but incomplete
			Wdc1stScan=MAKELONG(myFileCodasHdrCirc.hdrc.pretrig , myFileCodasHdrCirc.hdrc.postrig);
			Wdc1stData=Wdc1stScan*iTotalADChannel*2;
			AfxMessageBox2("WinDaq/Circ wrapped but incomplete", Wdc1stScan);

		}
		else if ((myFileCodasHdrCirc.hdrc.lmkeys & 0xC0) == 0x40){
			AfxMessageBox2("WinDaq Circ first pass");
			bWDC=true;
			WinDaqCircState=0; //WinDaq/Circ first pass
			Wdc1stScan=0;
			Wdc1stData=0;

		}
		else{
			AfxMessageBox2("Not Widnaq/Circ");
			Wdc1stScan=0;
			Wdc1stData=0;
			bWDC=false;
		}

		AfxMessageBox2("Wdc1stScan=", Wdc1stScan);
		AfxMessageBox2("Wdc1stData=", Wdc1stData);

		WdcScanBeforeWrapAround=TotalDataPoints-Wdc1stScan;
		AfxMessageBox2("ScanBeforeWrapAround=", WdcScanBeforeWrapAround);

		WdcScanAfterWrapAround=Wdc1stScan;
		AfxMessageBox2("ScanAfterWrapAround=", WdcScanAfterWrapAround);

		if (Wdc1stScan>TotalDataPoints){
			AfxMessageBox2("WinDaq file corrupted: Wdc1stScan=", (long)Wdc1stScan);
			FireFileError(ErrCode=-29);
			return;
		}

		
		if (bWDC){
			lmyWindaqFileHeaderSize=0x600;
			//myFileCodasHdrCirc.hdrc.endtime
			if (myFileCodasHdrCirc.hdrc.begtime!=0){ 
				AfxMessageBox2("Use BegTime");
				bUseBegTime=true;
			}
			else{
				AfxMessageBox2("Use EndTime");
				myFileCodasHdrCirc.hdrc.begtime = myFileCodasHdrCirc.hdrc.endtime
					-(long)((double)(myFileCodasHdrCirc.hdrc.datbyt/(2l*(long)myFileCodasHdrCirc.header[0] &0xff)) //Number of channels
					*myFileCodasHdrCirc.hdrc.intrvl);
				bUseBegTime=false;
			}

			if (myFileCodasHdrCirc.hdrc.remstenb){
				AfxMessageBox2("Has remote storage channel");
				bWdcHasRemoteStorage=true;
				iActualTotalADChannel=iTotalADChannel-1;
				if (myFileCodasHdrCirc.hdrc.remevenb){
					AfxMessageBox2("Event is embeded in remote storage channel");
					bWdcEventInRemoteStorageChannel=true;
				}
				//The remote channel is always the last one!
				if (myFileCodasHdrCirc.cary[iTotalADChannel-1].pchn!=0x49){
					iActualTotalADChannel=iTotalADChannel;
					bWdcHasRemoteStorage=false;
					bWdcEventInRemoteStorageChannel=false;
					AfxMessageBox2("RemoteChannel doesn't have the signature");
				}
			}
			else{
				AfxMessageBox2("No remote storage channel");
				bWdcHasRemoteStorage=false;
				iActualTotalADChannel=iTotalADChannel;
				bWdcEventInRemoteStorageChannel=false;
			}
		}	
		else iActualTotalADChannel=iTotalADChannel;

		_llseek(hWindaq,0,FILE_BEGIN);

   		if (_lread(hWindaq, &myFileCodasHdr254, sizeof(CODASHDR254))<sizeof(CODASHDR29)){
			FireFileError(ErrCode=-29);
			
   			_lclose(hWindaq);
			hWindaq=NULL;	
			lmyWindaqFileHeaderSize=0;
		} 
		else{
			AfxMessageBox2("Read WWB header");
			bFileOK=TRUE;
			lmyWindaqFileHeaderSize=(long)myFileCodasHdr254.hdrc.hdrsiz;

			AfxMessageBox2("WWB Header size", lmyWindaqFileHeaderSize);
			if (myFileCodasHdr254.hdrc.intrvl> 0.0){

				AfxMessageBox2("Valid sample rate");

				SampleRate=1/myFileCodasHdr254.hdrc.intrvl;
				_llseek(hWindaq,lmyWindaqFileHeaderSize,0);
				lFilePosition=0;
				if (myFileCodasHdr254.hdrc.hdrsiz>1156)
   					iTotalADChannel=myFileCodasHdr254.header[0] &0xff;       //We are dealing with big header
   				else
   					iTotalADChannel=myFileCodasHdr254.header[0] &0x1f;

				if (myFileCodasHdr254.hdrc.begtime!=0){ 
					bUseBegTime=true;
				}
				else{
					myFileCodasHdr254.hdrc.begtime = myFileCodasHdr254.hdrc.endtime
						-(long)((double)(myFileCodasHdr254.hdrc.datbyt/(2l*(long)myFileCodasHdr254.header[0] &0xff)) //Number of channels
						*myFileCodasHdr254.hdrc.intrvl);
					bUseBegTime=false;
				}
				
				bHiRes=myFileCodasHdr254.hdrc.data16;
				AfxMessageBox2 ("HiRes=", (long)bHiRes);

				TotalDataPoints=myFileCodasHdr254.hdrc.datbyt/(2l*(long)iTotalADChannel);
				AfxMessageBox2("WWB Total data scans", (long)TotalDataPoints);

				if (TotalDataPoints==0){ //This is a corrupted file or the file is being recorded
					long lTemp = _llseek(hWindaq,0,FILE_END);

					lTemp=lTemp-lmyWindaqFileHeaderSize;
					if (lTemp<0) lTemp=0;
					
					bDynamicFile=TRUE;

					TotalDataPoints=lTemp/(2l*(long)iTotalADChannel);
    
					_llseek(hWindaq,lmyWindaqFileHeaderSize,0);
				}
				else if (bWDC){ //WDC doesn't have event/comment/user annotation
					EventCount=0;
					AfxMessageBox2("WDC: Set file pointer to", lmyWindaqFileHeaderSize+Wdc1stData);
					_llseek(hWindaq,lmyWindaqFileHeaderSize+Wdc1stData,0);
				}
				else{
					/*Now to check Event Count*/
					AfxMessageBox2("Construct event marker buffer");
					EventCount=0;
					if (bHiRes) {
						acshdl=GlobalAlloc(GMEM_MOVEABLE|GMEM_NODISCARD|GMEM_ZEROINIT, MAXEVENTBUFFER*2*sizeof(long));
						if (acshdl!=NULL) {
							acsbf=(long (far *)[2]) GlobalLock (acshdl);
							acslim=MAXEVENTBUFFER;
						}
						else {
							acsbf=(long (far *)[2])NULL;
							acslim = 0;
						}
						evfhdl=GlobalAlloc(GMEM_MOVEABLE|GMEM_NODISCARD|GMEM_ZEROINIT, MAXEVENTBUFFER*sizeof(long));
						if (evfhdl!=NULL) {
							evfbf=(long *) GlobalLock (evfhdl);
							evflim=MAXEVENTBUFFER;
						}	
						else {
							evfbf=(long *)NULL;
							evflim = 0;
						}
						nacs = 0;
						nevf = 0;
						evfpn = 0;
						evmkns = 0;
						evmkn = 0;
					}
					if (myFileCodasHdr254.hdrc.evtbyt>0){
						AfxMessageBox2("Found events!");
						bHasEvent=TRUE;
						_llseek(hWindaq,lmyWindaqFileHeaderSize + myFileCodasHdr254.hdrc.datbyt,0);
						i=_lread(hWindaq, mypEventBuffer, min(myFileCodasHdr254.hdrc.evtbyt, MAXEVENTBUFFER*sizeof(long)));

						long mylong;
						//iDebug=2;
						if (i>3){

							pLong = (signed long*)mypEventBuffer;
							for (idx_e=0; idx_e<i/4;){
								//Note: Element 6 = myFileCodasHdr254.hdrc.datbyt
								if (pLong[idx_e++]>=0 && (!bHiRes || 
									!(pLong[idx_e-1]%iTotalADChannel))){ /* ch 1 */
									idx_e++; //We have the DTStamp
									if (bHiRes) {
										if ((DWORD)nacs >= acslim) {
											acslim *= 2;
											GlobalUnlock(acshdl);
											if ((acshdl = GlobalReAlloc(acshdl,acslim*(2*sizeof(long)),GMEM_MOVEABLE))
												== NULL) {
												GlobalUnlock(acshdl);
												GlobalFree(acshdl);
												acshdl = NULL;
												AfxMessageBox2((char *)"Not enough memory for acquisition starts.");
												FireControlError(ErrCode=-3001);
												return;
											}
											else
												acsbf = (long (far *)[2])GlobalLock(acshdl);
										}
										acsbf[nacs][0] = pLong[idx_e - 2];
										acsbf[nacs++][1] = pLong[idx_e - 1] + myFileCodasHdr254.hdrc.begtime;
										AfxMessageBox2("(char *)acsbf[nacs] = ",acsbf[nacs-1][0],acsbf[nacs-1][1]);
									}
								}
								if (bHiRes){
									mylong=myFileCodasHdr254.hdrc.datbyt/2; //For HiRes files, in Equations 1, 2, and 3 above, "(2(number of channels acquired))" should be omitted from the equation 
									mylong=-mylong;
								}
								else{
									mylong=-TotalDataPoints;
								}

								if (pLong[idx_e]<=mylong){
									idx_e++; //skip the comment pointer
								}
								else if (bHiRes){
									if ((DWORD)nevf >= evflim) {
										evflim *= 2;
										GlobalUnlock(evfhdl);
										if ((evfhdl = GlobalReAlloc(evfhdl,evflim*sizeof(UINT),GMEM_MOVEABLE))
											== NULL) {
											GlobalUnlock(evfhdl);
											GlobalFree(evfhdl);
											evfhdl = NULL;
											AfxMessageBox2((char *)"Not enough memory for event marks.");
											FireControlError(ErrCode=-3002);
											return;
										}
										else
											evfbf = (long *)GlobalLock(evfhdl);
									}
									evfbf[nevf++] = idx_e - 1;
								}
								EventCount++;
							}
						}
						//iDebug=0;
					}

					if (myFileCodasHdr254.hdrc.anfbyt>0){
						bHasChannelAnnotation=TRUE;
						AfxMessageBox2("Found Channel Annotation!");
						_llseek(hWindaq,lmyWindaqFileHeaderSize + myFileCodasHdr254.hdrc.datbyt + myFileCodasHdr254.hdrc.evtbyt,0);
						for (i=0; i<iTotalADChannel; i++){
							for (j=0; j<40; j++){
								if (_lread(hWindaq, &c, 1)==1){
									ChannelAnnotation [i][j]= c; 
									if (c==0) break;
								}
								else break;
							}

						}
					}

					_llseek(hWindaq,lmyWindaqFileHeaderSize + myFileCodasHdr254.hdrc.datbyt + myFileCodasHdr254.hdrc.evtbyt +myFileCodasHdr254.hdrc.anfbyt,0);
					
					i=_lread(hWindaq, mypCommentBuffer, MAXCOMMENTBUFFER);
					AfxMessageBox2("Read comments");
					_llseek(hWindaq,lmyWindaqFileHeaderSize,0);
					AfxMessageBox2("Reset the file point to the beginning of the file");

				}

				//char s[128];
				//sprintf (s, "Total: %ld", TotalDataPoints);
				AfxMessageBox2 ("TotalDataPoints", (long)TotalDataPoints);
    
				bStart=TRUE;
			}
			else{
				AfxMessageBox2("Invalid sample rate");
				FireFileError(ErrCode=-99999);
				
   				_lclose(hWindaq);
				hWindaq=NULL;	
				lmyWindaqFileHeaderSize=0;	
				SampleRate=0.0;
			}

		}
	}

}

double CReadDataqFileIICtrl::GetSampleRate() 
{
	if (bStart){
		return SampleRate;
	}
	return 0.0;
}


long CReadDataqFileIICtrl::GetTotalScans() 
{
	if (bFileOK) 
		return TotalDataPoints;
	else 
		return 0;
}

BSTR CReadDataqFileIICtrl::GetUserChnAn(short Chn) 
{
	if (bWDC){
		CString strResult;
		return strResult.AllocSysString();
	}

	if (Chn<0 || Chn>255) Chn=0;
	CString strResult = ChannelAnnotation [Chn];
	
	return strResult.AllocSysString();
}

long CReadDataqFileIICtrl::GetTotalDataPoints() 
{
	if (bFileOK) 
		return TotalDataPoints;
	else 
		return 0;
}

void CReadDataqFileIICtrl::AfxMessageBox2 (char * s, long a, long b)
{
	if (iDebug==0) return;
	sprintf(logmsg, "%s %ld %ld", s,a,b);
	m_Log.LogMessage(logmsg);
	if (iDebug==2) AfxMessageBox (logmsg);
}

void CReadDataqFileIICtrl::AfxMessageBox2 (char * s, long a)
{
	if (iDebug==0) return;
	sprintf(logmsg, "%s %ld", s,a);
	m_Log.LogMessage(logmsg);
	if (iDebug==2) AfxMessageBox (logmsg);
}


void CReadDataqFileIICtrl::AfxMessageBox2 (char * s, double f)
{
	if (iDebug==0) return;
	sprintf(logmsg, "%s %f", s, f);
	m_Log.LogMessage(logmsg);
	if (iDebug==2) AfxMessageBox (logmsg);
}

void CReadDataqFileIICtrl::AfxMessageBox2 (char * s)
{
	if (iDebug==0) return;
	m_Log.LogMessage(s);
	if (iDebug==2) AfxMessageBox (s);
}

/* Convert time in sec since 1970 UTC into local MM-DD-YY HH:MM:SS string. */
int CReadDataqFileIICtrl::sprintime(char *timbuf,long timesec)
{
   struct tm *t;
   time_t newtime;
   static char szFmtDateTime[] =  "%02d-%02d-%02d %02d:%02d:%02d" ;

#define FIX1970 0

   newtime = (time_t)(timesec + FIX1970);
	if (bUseUTC)
		t = gmtime(&newtime);
	else
		t = localtime(&newtime);
   return wsprintf(timbuf,szFmtDateTime,
      t->tm_mon + 1,t->tm_mday,t->tm_year % 100,
      t->tm_hour,t->tm_min,t->tm_sec);

}

BSTR CReadDataqFileIICtrl::GetEventComment(long idx) 
{
	int nEC;
	long * pLong;
	long mylong;
	int idx_e;
	char cTemp[64];

	if (idx<0 || idx>=EventCount || bWDC){
		FireControlError(ErrCode=-3000);
		CString strResult="na";
		return strResult.AllocSysString();
	}
	else{
		pLong = (long*)mypEventBuffer;

		nEC=0;
				
		for (idx_e=0; idx_e<MAXEVENTBUFFER;){
			if (nEC==idx) break;
			if (pLong[idx_e++]>=0){
				AfxMessageBox2("We have the DTStamp",(long)pLong[idx_e]);
				idx_e++; //We have the DTStamp
				//Now idx_e points to comment
			}
			else{
				AfxMessageBox2("We have NO DTStamp");
				//Now idx_e points to comment
			}

			if (bHiRes){
				mylong=myFileCodasHdr254.hdrc.datbyt/2;
				mylong=-mylong;
			}
			else{
				mylong=-TotalDataPoints;
			}

			if (pLong[idx_e]<=mylong){
				AfxMessageBox2("We have the comment",(long)pLong[idx_e]);
				
				idx_e++; //skip the comment pointer
			}
			nEC++;
		}

			
			
			
		if (pLong[idx_e++]>=0 && (!bHiRes || !(pLong[idx_e-1]%iTotalADChannel))){
			idx_e++; //We skip the DTStamp
		}

		if (bHiRes){
			mylong=myFileCodasHdr254.hdrc.datbyt/2;
			mylong=-mylong;
		}
		else{
			mylong=-TotalDataPoints;
		}

		if (pLong[idx_e]<=mylong){

			
			sprintf(cTemp, "%s", &mypCommentBuffer[(pLong[idx_e] & 0xffff) - myFileCodasHdr254.hdrc.anfbyt]);
			CString strResult = cTemp;

			return strResult.AllocSysString();
		}
		else{
			FireControlError(ErrCode=-3001);
			CString strResult ="*";
			return strResult.AllocSysString();
		}
		//iDebug=0;
	}
}


long CReadDataqFileIICtrl::GoToTime(double Time) 
{

	return 0;
}

short CReadDataqFileIICtrl::GetAvandedOptions() 
{

	return AvancedOptions;
}

void CReadDataqFileIICtrl::SetAvandedOptions(short nNewValue) 
{
	AvancedOptions=nNewValue;
	SetModifiedFlag();
}

/*
Return TRUE if the trailer event point and absolute timestamp are a valid
pair instead of including a peak on a channel other than the first.
*/
BOOL CReadDataqFileIICtrl::acstrt(long evtpnt,long astamp)
{
   UINT low; /* index for mark at point <= evtpnt */
   UINT high; /* index for mark at point > evtpnt */
   UINT mid; /* index of mark being tested */
   long midpnt; /* point number for mark being tested */

   low = 0;
   high = nacs;
   while (low + 1 < high) { /* more marks need to be tested */
      mid = (UINT)((low + high) >> 1);
      midpnt = acsbf[mid][0]*iTotalADChannel;
      if (evtpnt < midpnt)
         high = mid;
      else {
         low = mid;
         if (evtpnt == midpnt)
            break;
      }
   }
   return evtpnt == acsbf[low][0]*iTotalADChannel /* is index of a start */
      && astamp == (long)(acsbf[low][1] - myFileCodasHdr254.hdrc.begtime);
}

/*
Get previous or next mark in trailer starting at file index evfpn,
and update evmknx, evmknv, and stmpev.
*/
void CReadDataqFileIICtrl::trlrmk(int trlrdir)
{
   long evt;

   evmknv = 0;
   if (trlrdir < 0)
      while (evfpn > 0) {
         if (stmpev != NEV && stmpev < 0) { /* have pending valley output */
            evmknx = -stmpev;
            evmknv = MKB;
            stmpev = NEV;
            return;
         }
         evfpn--; /* to next event, stamp, or ptr */
         evt = mypEventBuffer[evfpn];
         if (evt >= 0) {
            if (evt % iTotalADChannel) {
               if (stmpev != NEV) { /* already have possible stamp */
                  evmknx = stmpev; /* prev was a peak */
                  evmknv = MKB | CH1;
                  evfpn++; /* try evt again as a timestamp */
                  stmpev = NEV;
                  return;
               }
               stmpev = evt; /* this might be a timestamp */
            }
            else { /* do binary search to see if this is an acq start */
               if (acstrt(evt,stmpev)) { /* evt is an acq start */
                  evmknx = evt;
                  evmknv = MKB | CH1;
                  stmpev = NEV;
                  return;
               }
               if (stmpev != NEV) { /* possible stamp is really a peak */
                  evmknx = stmpev;
                  evmknv = MKB | CH1;
                  evfpn ++; /* examine evt again as a timestamp */
                  stmpev = NEV;
                  return;
               }
               stmpev = evt; /* this is a timestamp */
            }
         }
         else if (evt > (-(TotalDataPoints*iTotalADChannel))) { /* not comment */
            if (stmpev != NEV) {
               evmknx = stmpev; /* prev was a peak */
               evmknv = MKB | CH1;
               stmpev = evt; /* save for later output, - shows not stamp */
               return;
            }
            else {
               evmknx = -evt;
               evmknv = MKB;
               stmpev = NEV;
               return;
            }
         }
         else {
            if (stmpev != NEV) {
               evmknx = stmpev; /* prev was a peak */
               evmknv = MKB | CH1;
               stmpev = NEV;
               return;
            }
         }
      } /* while (evfpn > 0) */
   else
      while (evfpn < evmkn) {
         evt = mypEventBuffer[evfpn];
         evfpn++; /* to next event, stamp, or ptr */
         if (evt >= 0) { /* start acq point # */
            if (stmpev != NEV) { /* expecting time stamp */
               stmpev = NEV; /* skip over it and continue */
               return;
            }
            else {
               evmknx = evt;
               evmknv = MKB | CH1;
               if (!(evt % iTotalADChannel)) /* positive-going mark in channel 1 */
                  evmkns = stmpev = evt; /* move evfpn past timestamp */
               else
                  return;
            }
         }
         else if (evt > (-(TotalDataPoints*iTotalADChannel))) {
            evmknx = -evt;
            evmknv = MKB;
            evmkns = stmpev = NEV;
            return;
         }
      } /* while (evfpn < evmkn) */
}
