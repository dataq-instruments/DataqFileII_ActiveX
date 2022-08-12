// WriteDataqFileIICtl.cpp : Implementation of the CWriteDataqFileIICtrl ActiveX Control class.

#include "stdafx.h"
#include "DataqFileII.h"
#include "WriteDataqFileIICtl.h"
#include "WriteDataqFileIIPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CWriteDataqFileIICtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CWriteDataqFileIICtrl, COleControl)
	//{{AFX_MSG_MAP(CWriteDataqFileIICtrl)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CWriteDataqFileIICtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CWriteDataqFileIICtrl)
	DISP_PROPERTY_EX(CWriteDataqFileIICtrl, "ChannelCount", GetChannelCount, SetChannelCount, VT_I2)
	DISP_PROPERTY_EX(CWriteDataqFileIICtrl, "FileName", GetFileName, SetFileName, VT_BSTR)
	DISP_PROPERTY_EX(CWriteDataqFileIICtrl, "SampleRate", GetSampleRate, SetSampleRate, VT_R8)
	DISP_FUNCTION(CWriteDataqFileIICtrl, "AddComment", AddComment, VT_I2, VTS_BSTR)
	DISP_FUNCTION(CWriteDataqFileIICtrl, "Close", Close, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CWriteDataqFileIICtrl, "EUCal", EUCal, VT_EMPTY, VTS_R8 VTS_R8 VTS_I2)
	DISP_FUNCTION(CWriteDataqFileIICtrl, "EUTag", EUTag, VT_EMPTY, VTS_BSTR VTS_I2)
	DISP_FUNCTION(CWriteDataqFileIICtrl, "InsertEventMarker", InsertEventMarker, VT_I2, VTS_BOOL)
	DISP_FUNCTION(CWriteDataqFileIICtrl, "MapErrMessage", MapErrMessage, VT_BSTR, VTS_I4)
	DISP_FUNCTION(CWriteDataqFileIICtrl, "Open", Open, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CWriteDataqFileIICtrl, "SaveData", SaveData, VT_EMPTY, VTS_VARIANT)
	DISP_FUNCTION(CWriteDataqFileIICtrl, "SaveDataEx", SaveDataEx, VT_EMPTY, VTS_PI2 VTS_I4)
	DISP_PROPERTY_PARAM(CWriteDataqFileIICtrl, "UserChnAn", GetUserChnAn, SetUserChnAn, VT_BSTR, VTS_I2)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CWriteDataqFileIICtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CWriteDataqFileIICtrl, COleControl)
	//{{AFX_EVENT_MAP(CWriteDataqFileIICtrl)
	EVENT_CUSTOM("ControlError", FireControlError, VTS_I2)
	EVENT_CUSTOM("DataError", FireDataError, VTS_I4)
	EVENT_CUSTOM("FileError", FireFileError, VTS_I4)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

BEGIN_PROPPAGEIDS(CWriteDataqFileIICtrl, 1)
	PROPPAGEID(CWriteDataqFileIIPropPage::guid)
END_PROPPAGEIDS(CWriteDataqFileIICtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWriteDataqFileIICtrl, "DATAQFILEII.WriteDataqFileIICtrl.1",
	0x4054eb5a, 0xfb35, 0x496c, 0xb1, 0xf3, 0xe4, 0xb0, 0x58, 0x48, 0x49, 0x2c)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CWriteDataqFileIICtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DWriteDataqFileII =
		{ 0xd394116c, 0xda78, 0x45fd, { 0xa1, 0xe9, 0x58, 0xa3, 0xec, 0x1b, 0x6e, 0xbe } };
const IID BASED_CODE IID_DWriteDataqFileIIEvents =
		{ 0xea13d939, 0xcce5, 0x4112, { 0xac, 0x5f, 0x28, 0xdd, 0x2e, 0x16, 0xd6, 0x75 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwWriteDataqFileIIOleMisc =
	OLEMISC_INVISIBLEATRUNTIME |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CWriteDataqFileIICtrl, IDS_WRITEDATAQFILEII, _dwWriteDataqFileIIOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIICtrl::CWriteDataqFileIICtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CWriteDataqFileIICtrl

BOOL CWriteDataqFileIICtrl::CWriteDataqFileIICtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_WRITEDATAQFILEII,
			IDB_WRITEDATAQFILEII,
			afxRegApartmentThreading,
			_dwWriteDataqFileIIOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIICtrl::CWriteDataqFileIICtrl - Constructor

CWriteDataqFileIICtrl::CWriteDataqFileIICtrl()
{
	InitializeIIDs(&IID_DWriteDataqFileII, &IID_DWriteDataqFileIIEvents);
	int i;
	char * ptr;

	iDebug = GetPrivateProfileInt("Global", "Debug", 0, "TPDATAQ.INI");

	ptr = (char *)&myFileCodasHdr254;
	for (i=0; i<sizeof(myFileCodasHdr254); i++)
		ptr[i]=0;

	for (i=0; i<256; i++) ChannelAnnatation [256][0]=0;


	hWindaq=INVALID_HANDLE_VALUE;	

	//sprintf (WindaqFilePath, "C:\\Sample.wdq");
	//iTotalADChannel=1;
	TotalDataPoints=0;
	bLock=FALSE;

	myFileCodasHdr254.header[0]=1;
	myFileCodasHdr254.hdrc.datbyt=TotalDataPoints;


	myFileCodasHdr254.hdrc.chnbeg=HB+sizeof(hdrcmn);
	myFileCodasHdr254.hdrc.chnsiz=sizeof(chinfo);
	myFileCodasHdr254.hdrc.hdrsiz=sizeof(myFileCodasHdr254);
	myFileCodasHdr254.hdrc.intrvl=(double)1./(double)1000.;
	myFileCodasHdr254.hdrc.evtbyt=0;
	myFileCodasHdr254.hdrc.anfbyt=0;
	myFileCodasHdr254.hdrc.fvres=400;
	myFileCodasHdr254.hdrc.fhres=640;
	myFileCodasHdr254.hdrc.vidfmt.omax=1;
	myFileCodasHdr254.hdrc.vidfmt.tmax=1;
	myFileCodasHdr254.hdrc.vidfmt.dmax=1;
	myFileCodasHdr254.hdrc.vidfmt.orient=0;
	myFileCodasHdr254.hdrc.compress=1;
	myFileCodasHdr254.hdrc.mrkpnt=0;
	myFileCodasHdr254.hdrc.fkeys=0x57;
	myFileCodasHdr254.hdrc.lmkeys=7; //5 
	myFileCodasHdr254.hdrc.chnnm=-1;
	myFileCodasHdr254.hdrc.pwkeys=0xb0;
	myFileCodasHdr254.vbflags=(unsigned short)0x8001;
	
	for (i=0; i<VWIN; i++)
		myFileCodasHdr254.hdrc.vc[i]=(unsigned char)i;


	for (i=0; i<254; i++){
		sprintf (myFileCodasHdr254.cary[i].an, "Volt");
		myFileCodasHdr254.cary[i].fscale=1.0;
		myFileCodasHdr254.cary[i].foffset=0.0;
		myFileCodasHdr254.cary[i].intrcpt=0.0;
		myFileCodasHdr254.cary[i].slope=10./8192.;
	}

	myhEventBuffer=GlobalAlloc(GMEM_MOVEABLE|GMEM_NODISCARD|GMEM_ZEROINIT, 8192*sizeof(long)); 
	if (myhEventBuffer!=NULL) 
		mypEventBuffer=(long *) GlobalLock (myhEventBuffer);
	else
		mypEventBuffer=(long *)NULL;

	EventCntr=0;

	myhCommentBuffer=GlobalAlloc(GMEM_MOVEABLE|GMEM_NODISCARD|GMEM_ZEROINIT, 8192*sizeof(char)); 
	if (myhCommentBuffer!=NULL) 
		mypCommentBuffer=(char *) GlobalLock (myhCommentBuffer);
	else
		mypCommentBuffer=(char *)NULL;

	CommentCntr=0;
}


/////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIICtrl::~CWriteDataqFileIICtrl - Destructor

CWriteDataqFileIICtrl::~CWriteDataqFileIICtrl()
{
	if (myhEventBuffer!=NULL){
		GlobalUnlock(myhEventBuffer);
		GlobalFree (myhEventBuffer);
	}
	if (myhCommentBuffer!=NULL){
		GlobalUnlock(myhCommentBuffer);
		GlobalFree (myhCommentBuffer);
	}
	Close();
}


/////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIICtrl::OnDraw - Drawing function

void CWriteDataqFileIICtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
CDC * pBackUpDC;
CBitmap * pBitmapOld=(CBitmap *)NULL;
CBrush myBrush;
CPen myNullPen;

	CBitmap * myBitMap = new CBitmap;
	CBitmap * oldBitmap;
	myBitMap->LoadBitmap(IDB_WRITEDATAQFILEII);

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
	CString cstr="WriteDataqFile Control";
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
// CWriteDataqFileIICtrl::DoPropExchange - Persistence support

void CWriteDataqFileIICtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	double newValue;

	// TODO: Call PX_ functions for each persistent custom property.
	PX_String (pPX, _T("FileName"), cWindaqFilePath, _T("C:\\Sample.wdq"));
	PX_Long (pPX, "ChannelCount", iTotalADChannel, 1);
	PX_Double (pPX, "SampleRate", newValue, 1000.);

	if (pPX->IsLoading()){
		if (newValue>0.0) 	
			myFileCodasHdr254.hdrc.intrvl=1/newValue;

		if (iTotalADChannel<1) iTotalADChannel=1;
		if (iTotalADChannel>250) iTotalADChannel= 250;

		myFileCodasHdr254.header[0]=(unsigned short)iTotalADChannel;
	}

}


/////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIICtrl::OnResetState - Reset control to default state

void CWriteDataqFileIICtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}


/////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIICtrl::AboutBox - Display an "About" box to the user

void CWriteDataqFileIICtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_WRITEDATAQFILEII);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIICtrl message handlers

void CWriteDataqFileIICtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

short CWriteDataqFileIICtrl::AddComment(LPCTSTR Comment) 
{
	if (bAllowComment){
		sprintf (&mypCommentBuffer[CommentCntr], "%s", Comment);
		PrevCommentCntr=CommentCntr;
		CommentCntr +=strlen (&mypCommentBuffer[CommentCntr])+1;
		bAllowComment=false;
		return 0;
	}
	return 1;
}

short CWriteDataqFileIICtrl::GetChannelCount() 
{
	return (short)iTotalADChannel;
}

void CWriteDataqFileIICtrl::SetChannelCount(short nNewValue) 
{
	if (nNewValue>0) iTotalADChannel=nNewValue;
	SetModifiedFlag();
}

void CWriteDataqFileIICtrl::Close() 
{
	int i;
	short sTemp;
	unsigned long ByteWritten;

	if (hWindaq!=INVALID_HANDLE_VALUE){
		if (iTotalADChannel<16)
			myFileCodasHdr254.hdrc.vidfmt.dmax=(unsigned char)iTotalADChannel;
		else
			myFileCodasHdr254.hdrc.vidfmt.dmax=16;

		myFileCodasHdr254.hdrc.datbyt=TotalDataPoints;
		//find out user annotation size
		for (sTemp=0, i=0; i<iTotalADChannel; i++){
			sTemp=sTemp + strlen(ChannelAnnatation [i])+1;
		}

		//sTemp is the size of annotation block, which will be used to calculate the offset of the comment event markers
		
		//Event markers
		for (i=0; i<EventCntr; i++){
			if ((mypEventBuffer[i]&0xffff0000)==0x80000000){
				mypEventBuffer[i] &= 0xffff; //Extract only the offset
				mypEventBuffer[i] =sTemp+mypEventBuffer[i];
				mypEventBuffer[i] |= 0x80000000;
			}
		}

		WriteFile(hWindaq, (char *)mypEventBuffer, EventCntr*sizeof(long), &ByteWritten, (LPOVERLAPPED) NULL);
		
		//Annotation

		for (sTemp=0, i=0; i<iTotalADChannel; i++){
			WriteFile(hWindaq, (char *) ChannelAnnatation [i], strlen(ChannelAnnatation [i])+1, &ByteWritten, (LPOVERLAPPED) NULL);
			sTemp=sTemp + strlen(ChannelAnnatation [i])+1;
		}

		myFileCodasHdr254.hdrc.anfbyt=sTemp;
		//AfxMessageBox2("evtbyt",(long)myFileCodasHdr254.hdrc.evtbyt);
		//AfxMessageBox2("datbyt",(long)myFileCodasHdr254.hdrc.datbyt);
		//AfxMessageBox2("anfbyt",(long)myFileCodasHdr254.hdrc.anfbyt);

		//Comment
		WriteFile(hWindaq, (char *)mypCommentBuffer, CommentCntr, &ByteWritten, (LPOVERLAPPED) NULL);


		SetFilePointer(hWindaq, 0, NULL, FILE_BEGIN);
		if (WriteFile(hWindaq, (char *)&myFileCodasHdr254, sizeof(CODASHDR254), &ByteWritten, (LPOVERLAPPED) NULL)==0)
			FireFileError(GetLastError());

   		CloseHandle(hWindaq);
		hWindaq=INVALID_HANDLE_VALUE;
   	}
	bLock=FALSE;
}

void CWriteDataqFileIICtrl::EUCal(double Max, double Min, short Index) 
{
	if (Index<0 && Index>240) return;
	myFileCodasHdr254.cary[Index].intrcpt=(Max+Min)/2;
	myFileCodasHdr254.cary[Index].slope=((Max-Min)/2)/8192.;

}

void CWriteDataqFileIICtrl::EUTag(LPCTSTR Unit, short Index) 
{
	int i;
	char c;
	for (i=0; i<6; i++){
		c=(char)Unit[i];
		myFileCodasHdr254.cary[Index].an[i]=c;
	}
}

BSTR CWriteDataqFileIICtrl::GetFileName() 
{
	CString strResult = cWindaqFilePath;

	return strResult.AllocSysString();
}

void CWriteDataqFileIICtrl::SetFileName(LPCTSTR lpszNewValue) 
{
	cWindaqFilePath = lpszNewValue;

	/*int length=strResult.GetLength();
	if (length>250) length=250;
	for (i=0; i<length; i++)
		WindaqFilePath[i]=strResult[i];
	WindaqFilePath[i]=0;
	strlwr(WindaqFilePath);*/

	bLock=FALSE;
	TotalDataPoints=0;
	SetModifiedFlag();
}

short CWriteDataqFileIICtrl::InsertEventMarker(BOOL TimeStamp) 
{
	/*Must call AddComment before each InsertEventMarker!*/
	if (TimeStamp){
		if (iTotalADChannel>0 && EventCntr<8000){
			mypEventBuffer[EventCntr++]=TotalDataPoints/(iTotalADChannel*2);
			mypEventBuffer[EventCntr++]=GetTickCount()/1000-BeginTime;
			if (bAllowComment==false) {/*meaning there is a comment!*/
			    mypEventBuffer[EventCntr++]=PrevCommentCntr | 0x80000000; /*CommentCntr is in terms of offset*/
				myFileCodasHdr254.hdrc.evtbyt +=12;
			}
			else{
				myFileCodasHdr254.hdrc.evtbyt +=8;
			}
		}
	}
	else{
		if (iTotalADChannel>0 && EventCntr<8000){
			
			mypEventBuffer[EventCntr++]=/*watch for the sign!*/-(TotalDataPoints/(iTotalADChannel*2));
			if (bAllowComment==false){ /*meaning there is a comment!*/
			    mypEventBuffer[EventCntr++]=CommentCntr| 0x80000000;  //Must have comment!
			    myFileCodasHdr254.hdrc.evtbyt +=8;
			}
			else myFileCodasHdr254.hdrc.evtbyt +=4;
		}
	}

	bAllowComment=true;
	bMarkData=true;
	mypCommentBuffer[CommentCntr]=0;
	return 0;
}

BSTR CWriteDataqFileIICtrl::MapErrMessage(long errcode) 
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

void CWriteDataqFileIICtrl::Open() 
{
	int i,j;
	bLock=FALSE;

	if (hWindaq!=INVALID_HANDLE_VALUE){
   		CloseHandle(hWindaq);
		hWindaq=INVALID_HANDLE_VALUE;
   	}

	int length=cWindaqFilePath.GetLength();
	if (length>250) {
		FireFileError(-250);
		return;
	}
	for (i=0; i<length; i++)
		WindaqFilePath[i]=cWindaqFilePath[i];
	WindaqFilePath[i]=0;

	bHiRes = FALSE;
	for (j = length - 1; j >= 0 && WindaqFilePath[j] != '\\'; j--)
		if (WindaqFilePath[j] == '.') {
			if (!stricmp(WindaqFilePath + j,".WDH"))
				bHiRes = TRUE;
			break;
		}
	
	hWindaq=CreateFile(WindaqFilePath,
		GENERIC_WRITE, 
		FILE_SHARE_READ,
		NULL,
		CREATE_NEW,
		FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);

	if (hWindaq==INVALID_HANDLE_VALUE){
		FireFileError(GetLastError());
   	}

	myFileCodasHdr254.hdrc.begtime=time (NULL);  
	BeginTime=GetTickCount()/1000;

	CommentCntr=EventCntr=0;
	mypEventBuffer[EventCntr++]=0;
	mypEventBuffer[EventCntr++]=0;
	myFileCodasHdr254.hdrc.evtbyt =8;
	myFileCodasHdr254.hdrc.data16 = bHiRes;
	//myFileCodasHdr254.hdrc.lmkeys=2|myFileCodasHdr254.hdrc.lmkeys;
	//myFileCodasHdr254.hdrc.evtbyt =0;
	bAllowComment=true;
	bMarkData=false;
}

double CWriteDataqFileIICtrl::GetSampleRate() 
{
	return 1/myFileCodasHdr254.hdrc.intrvl;
}

void CWriteDataqFileIICtrl::SetSampleRate(double newValue) 
{
	if (newValue>0.0) 	
		myFileCodasHdr254.hdrc.intrvl=1/newValue;
	SetModifiedFlag();
}

void CWriteDataqFileIICtrl::SaveData(const VARIANT FAR& Data) 
{
	int iTotal, iChannel;
	unsigned long ByteWritten;
	char HUGEP * ptr;
	
	if (Data.vt!=VT_I2+VT_ARRAY) {
		FireDataError(-2000);
		return;
	}

	myFileCodasHdr254.hdrc.endtime=time (NULL);  

	
	switch(Data.parray->cDims){
	case 2:
		iTotal=Data.parray->rgsabound[0].cElements-Data.parray->rgsabound[0].lLbound;
		iChannel=Data.parray->rgsabound[1].cElements-Data.parray->rgsabound[1].lLbound;
		break;
	case 1:
		iTotal=Data.parray->rgsabound[0].cElements-Data.parray->rgsabound[0].lLbound;
		iChannel=1;
		break;
	default:
		FireDataError(-2000);
		return;
	}

	ptr=(char HUGEP *)Data.parray->pvData;

	if (bMarkData){
		bMarkData=false;
		ptr [0] |=3; //Mark an event marker on first channel
	}

	if (iTotal<=0) {
		FireDataError(-2000);
		return;
	}
	if (iChannel<=0) {
		FireDataError(-2000);
		return;
	}

	if (bLock){
		if (iChannel!=iTotalADChannel)
			FireDataError(-2000);
	}
	else{
		bLock=TRUE;
		iTotalADChannel=iChannel;
		myFileCodasHdr254.header[0]=(unsigned short)iTotalADChannel;
		SetFilePointer(hWindaq, 0, NULL, FILE_BEGIN);
		if (WriteFile(hWindaq, (char *)&myFileCodasHdr254, sizeof(CODASHDR254), &ByteWritten, (LPOVERLAPPED)NULL)==0){
			FireFileError(GetLastError());
			Close();
		}
	}

	
	if (WriteFile(hWindaq, ptr, (long)iTotal*(long)iChannel*(long)sizeof(short), &ByteWritten, (LPOVERLAPPED)NULL)==0){
		FireFileError(GetLastError());
		Close();
		return;
	}
	else if (ByteWritten!=(unsigned long)iTotal*(unsigned long)iChannel*(unsigned long)sizeof(short)){
		Close();
		FireFileError(GetLastError());
		return;
	}
	

	TotalDataPoints+=(long)iTotal*(long)iChannel*(long)sizeof(short);
	FlushFileBuffers(hWindaq); //Commit the file
	bMarkData=false;

}

void CWriteDataqFileIICtrl::SaveDataEx(short FAR* Buffer, long iTotal) 
{
	char * ptr=(char HUGEP *)Buffer;
	unsigned long ByteWritten;

	if (iTotal<=0) {
		FireDataError(-2000);
		return;
	}


	if (!bLock){
		bLock=TRUE;
		myFileCodasHdr254.header[0]=(unsigned short) iTotalADChannel;
		SetFilePointer(hWindaq, 0, NULL, FILE_BEGIN);
		if (WriteFile(hWindaq, (char *)&myFileCodasHdr254, sizeof(CODASHDR254), &ByteWritten, (LPOVERLAPPED)NULL)==0){
			FireFileError(GetLastError());
			Close();
		}
	}

	if (bMarkData){
		bMarkData=false;
		Buffer [0] |=3; //Mark an event marker on first channel
	}
	myFileCodasHdr254.hdrc.endtime=time (NULL);  
	
	if (WriteFile(hWindaq, ptr, iTotal*sizeof(short), &ByteWritten, (LPOVERLAPPED)NULL)==0){
		FireFileError(GetLastError());
		Close();
		return;
	}
	else if (ByteWritten!=iTotal*sizeof(short)){
		Close();
		FireFileError(GetLastError());
		return;
	}
	

	TotalDataPoints+=iTotal*sizeof(short);
	FlushFileBuffers(hWindaq); //Commit the file
	bMarkData=false;

}

BSTR CWriteDataqFileIICtrl::GetUserChnAn(short Chn) 
{
	CString strResult = ChannelAnnatation [Chn];

	return strResult.AllocSysString();
}

void CWriteDataqFileIICtrl::SetUserChnAn(short Chn, LPCTSTR lpszNewValue) 
{
	int i;
    for (i=0; i<31; i++){
		ChannelAnnatation [Chn][i]=lpszNewValue[i];
	}

	ChannelAnnatation [Chn][i]=0;
	SetModifiedFlag();
}

void CWriteDataqFileIICtrl::AfxMessageBox2 (char * s, long a, long b)
{
	char msg[128];
	if (iDebug==0) return;
	sprintf(msg, "%s %ld %ld", s,a,b);
	if (iDebug==2) AfxMessageBox (msg);
}

void CWriteDataqFileIICtrl::AfxMessageBox2 (char * s, long a)
{
	char msg[128];
	if (iDebug==0) return;
	sprintf(msg, "%s %ld", s,a);
	if (iDebug==2) AfxMessageBox (msg);
}


void CWriteDataqFileIICtrl::AfxMessageBox2 (char * s, double f)
{
	char msg[128];
	if (iDebug==0) return;
	sprintf(msg, "%s %f", s, f);
	if (iDebug==2) AfxMessageBox (msg);
}

void CWriteDataqFileIICtrl::AfxMessageBox2 (char * s)
{
	if (iDebug==0) return;
	if (iDebug==2) AfxMessageBox (s);
}

