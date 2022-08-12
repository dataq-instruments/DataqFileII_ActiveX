#if !defined(AFX_READDATAQFILEIICTL_H__BB5EDC8E_2260_4A30_B35B_63CE37A6D35D__INCLUDED_)
#define AFX_READDATAQFILEIICTL_H__BB5EDC8E_2260_4A30_B35B_63CE37A6D35D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ReadDataqFileIICtl.h : Declaration of the CReadDataqFileIICtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CReadDataqFileIICtrl : See ReadDataqFileIICtl.cpp for implementation.

class CReadDataqFileIICtrl : public COleControl
{
	DECLARE_DYNCREATE(CReadDataqFileIICtrl)

// Constructor
public:
	CLog m_Log;
	CReadDataqFileIICtrl();

private:
    char logmsg[128];

	char WindaqFilePath[512];
	BOOL bChanged;
	BOOL bFileOK;

	char ChannelAnnotation [256][40]; 
	HANDLE myhEventBuffer;
	long * mypEventBuffer;
	long EventCount;

	HANDLE myhCommentBuffer;
	char * mypCommentBuffer;

	long lmyWindaqFileHeaderSize;
	HFILE hWindaq;
	OFSTRUCT OpenBuff;
	CString cWindaqFilePath;
	char dummy[16];
	long ErrCode;
	long EventMarker;
	BOOL bDynamicFile;
	
	double SampleRate;
	BOOL bUseUTC;
	long lFilePosition, lOldFilePosition;
	int iTotalADChannel;
	int iActualTotalADChannel;
	int TotalDataPoints;
	BOOL bHiRes;
	BOOL bStart, bScaled;
	CODASHDR254 myFileCodasHdr254;
	BOOL bUseBegTime;
	BOOL bHasEvent;
	BOOL bHasChannelAnnotation;
	short AvancedOptions;

	CODASHDRCIRC myFileCodasHdrCirc; 
	BOOL bWDC;
	int WinDaqCircState;
	long Wdc1stScan;
	long WdcScanBeforeWrapAround;
	long WdcScanAfterWrapAround;
	long Wdc1stData;
	BOOL bWdcHasRemoteStorage;
	BOOL bWdcEventInRemoteStorageChannel;
	int bWdcRemoteStorageChannelIdx;
	DWORD acslim;
	UINT nacs;
	HANDLE acshdl;
	long (*acsbf)[2];
	DWORD evflim;
	UINT nevf;
	HANDLE evfhdl;
	long * evfbf;
	long evmknx; /* value of pos for next marked point */
	int evmknv; /* flag bits for next marked point */
	long stmpev; /* NEV if have no partially-processed timestamp */
	DWORD evfpn; /* trailer file index of next marked point rel to events */
	long evmkns; /* value of processed timestamp for use by evftrp */
	DWORD evmkn; /* # of event marker doublewords in trailer */

	BOOL CReadDataqFileIICtrl::acstrt(long evtpnt,long astamp);
	void PASCAL trlrmk(int trlrdir);
	int sprintime(char far *timbuf,long timesec);
	void AfxMessageBox2(char * s, long a, long b);
	void AfxMessageBox2(char * s, long a);
	void AfxMessageBox2(char * s, double f);
	void AfxMessageBox2(char * s);
	int ReadRawData(short * dest, long count);
	int iDebug;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadDataqFileIICtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CReadDataqFileIICtrl();

	DECLARE_OLECREATE_EX(CReadDataqFileIICtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CReadDataqFileIICtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CReadDataqFileIICtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CReadDataqFileIICtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CReadDataqFileIICtrl)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CReadDataqFileIICtrl)
	afx_msg BSTR GetBeginTime();
	afx_msg short GetChannelCount();
	afx_msg long GetCurrentLocation();
	afx_msg BSTR GetEndTime();
	afx_msg long GetEventCount();
	afx_msg BSTR GetFileName();
	afx_msg void SetFileName(LPCTSTR lpszNewValue);
	afx_msg long GetLastErrorCode();
	afx_msg long GetTotalScans();
	afx_msg long GetTotalDataPoints();
	afx_msg long GetFileType();
	afx_msg double GetSampleRate();
	afx_msg short GetAvandedOptions();
	afx_msg void SetAvandedOptions(short nNewValue);
	afx_msg void Close();
	afx_msg BSTR EUTag(short Channel);
	afx_msg VARIANT GetData(long Count, short Method);
	afx_msg void GetDataEx(double FAR* Buffer, long Count);
	afx_msg long GetDataExB(short FAR* Buffer, long Count);
	afx_msg double GetIntrcpt(short Index);
	afx_msg double GetSlope(short Index);
	afx_msg void GoToEventMarker(long Event, short Channel);
	afx_msg void GoToMark(long Mark, short Channel);
	afx_msg BSTR Location2Time(long scan);
	afx_msg BSTR MapErrMessage(long errcode);
	afx_msg void MoveTo(long Offset, short Origin);
	afx_msg void Open();
	afx_msg long GoToTime(double Time);
	afx_msg BSTR GetEventDTStamp(long idx);
	afx_msg long GetEventLocation(long idx);
	afx_msg BSTR GetUserChnAn(short Channel);
	afx_msg BSTR GetEventComment(long idx);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CReadDataqFileIICtrl)
	void FireControlError(long Code)
		{FireEvent(eventidControlError,EVENT_PARAM(VTS_I4), Code);}
	void FireEndOfFile()
		{FireEvent(eventidEndOfFile,EVENT_PARAM(VTS_NONE));}
	void FireFileError(long Code)
		{FireEvent(eventidFileError,EVENT_PARAM(VTS_I4), Code);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CReadDataqFileIICtrl)
	dispidBeginTime = 1L,
	dispidChannelCount = 2L,
	dispidCurrentLocation = 3L,
	dispidEndTime = 4L,
	dispidEventCount = 5L,
	dispidFileName = 6L,
	dispidLastErrorCode = 7L,
	dispidTotalScans = 8L,
	dispidTotalDataPoints = 9L,
	dispidFileType = 10L,
	dispidSampleRate = 11L,
	dispidAvandedOptions = 12L,
	dispidClose = 13L,
	dispidEUTag = 14L,
	dispidEventDTStamp = 27L,
	dispidEventLocation = 28L,
	dispidGetData = 15L,
	dispidGetDataEx = 16L,
	dispidGetDataExB = 17L,
	dispidGetIntrcpt = 18L,
	dispidGetSlope = 19L,
	dispidGoToEventMarker = 20L,
	dispidGoToMark = 21L,
	dispidLocation2Time = 22L,
	dispidMapErrMessage = 23L,
	dispidMoveTo = 24L,
	dispidOpen = 25L,
	dispidUserChnAn = 29L,
	dispidEventComment = 30L,
	dispidGoToTime = 26L,
	eventidControlError = 1L,
	eventidEndOfFile = 2L,
	eventidFileError = 3L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READDATAQFILEIICTL_H__BB5EDC8E_2260_4A30_B35B_63CE37A6D35D__INCLUDED)
