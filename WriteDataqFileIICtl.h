#if !defined(AFX_WRITEDATAQFILEIICTL_H__4FAC400E_62D7_491B_85BF_8B089091B007__INCLUDED_)
#define AFX_WRITEDATAQFILEIICTL_H__4FAC400E_62D7_491B_85BF_8B089091B007__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// WriteDataqFileIICtl.h : Declaration of the CWriteDataqFileIICtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CWriteDataqFileIICtrl : See WriteDataqFileIICtl.cpp for implementation.

class CWriteDataqFileIICtrl : public COleControl
{
	DECLARE_DYNCREATE(CWriteDataqFileIICtrl)

// Constructor
public:
	CWriteDataqFileIICtrl();
	char WindaqFilePath[256];
	char ChannelAnnatation [256][32];

	long lmyWindaqFileHeaderSize;
	long BeginTime;
	
	HANDLE myhEventBuffer;
	long * mypEventBuffer;
	int EventCntr, CommentCntr, PrevCommentCntr;

	HANDLE myhCommentBuffer;
	char * mypCommentBuffer;
	BOOL bAllowComment;
	BOOL bMarkData;

	void AfxMessageBox2(char * s, long a, long b);
	void AfxMessageBox2(char * s, long a);
	void AfxMessageBox2(char * s, double f);
	void AfxMessageBox2(char * s);
	int iDebug;
	
	//HFILE hWindaq;
	HANDLE hWindaq;
	OFSTRUCT OpenBuff;
	CString cWindaqFilePath;	
	double SampleRate;
	long lFilePosition, lOldFilePosition;
	long iTotalADChannel, TotalDataPoints;
	BOOL bStart, bScaled;
	CODASHDR254 myFileCodasHdr254;  //Its size is 9256 bytes
	char dummy[16];
	BOOL bLock;

private:
	BOOL bHiRes;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWriteDataqFileIICtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CWriteDataqFileIICtrl();

	DECLARE_OLECREATE_EX(CWriteDataqFileIICtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CWriteDataqFileIICtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CWriteDataqFileIICtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CWriteDataqFileIICtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CWriteDataqFileIICtrl)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CWriteDataqFileIICtrl)
	afx_msg short GetChannelCount();
	afx_msg void SetChannelCount(short nNewValue);
	afx_msg BSTR GetFileName();
	afx_msg void SetFileName(LPCTSTR lpszNewValue);
	afx_msg double GetSampleRate();
	afx_msg void SetSampleRate(double newValue);
	afx_msg short AddComment(LPCTSTR Comment);
	afx_msg void Close();
	afx_msg void EUCal(double Max, double Min, short Index);
	afx_msg void EUTag(LPCTSTR Unit, short Index);
	afx_msg short InsertEventMarker(BOOL TimeStamp);
	afx_msg BSTR MapErrMessage(long errcode);
	afx_msg void Open();
	afx_msg void SaveData(const VARIANT FAR& Data);
	afx_msg void SaveDataEx(short FAR* Buffer, long Total);
	afx_msg BSTR GetUserChnAn(short Chn);
	afx_msg void SetUserChnAn(short Chn, LPCTSTR lpszNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CWriteDataqFileIICtrl)
	void FireControlError(short Code)
		{FireEvent(eventidControlError,EVENT_PARAM(VTS_I2), Code);}
	void FireDataError(long Code)
		{FireEvent(eventidDataError,EVENT_PARAM(VTS_I4), Code);}
	void FireFileError(long Code)
		{FireEvent(eventidFileError,EVENT_PARAM(VTS_I4), Code);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CWriteDataqFileIICtrl)
	dispidChannelCount = 1L,
	dispidFileName = 2L,
	dispidSampleRate = 3L,
	dispidAddComment = 4L,
	dispidClose = 5L,
	dispidEUCal = 6L,
	dispidEUTag = 7L,
	dispidInsertEventMarker = 8L,
	dispidMapErrMessage = 9L,
	dispidOpen = 10L,
	dispidSaveData = 11L,
	dispidSaveDataEx = 12L,
	dispidUserChnAn = 13L,
	eventidControlError = 1L,
	eventidDataError = 2L,
	eventidFileError = 3L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITEDATAQFILEIICTL_H__4FAC400E_62D7_491B_85BF_8B089091B007__INCLUDED)
