/******************************************************************************************
FileName		: Log.cpp
Author			: S.Karthiksundar
Date Of Creation: 17-Jan-99
comments		: This code is suppled as it is   blah - blah -blah ....
				  any comments/ suggestions / improvements be sent to 
				  drkar@hotmail.com - thanks for using this code :-)
Modification History :
Date             Modifications
Copyright		: S.Karthiksundar 
******************************************************************************************/


#include "stdafx.h"
#include "Log.h"
#include <afx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define CRLF "\x0d\x0a"

CRITICAL_SECTION LogCriticalSection;	// Protection from multiple threads 

// thread proc for warning message thread if the size of the log file exceeds 
// the user defined limit

UINT MessageBoxThreadProcFunc(LPVOID pParam);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLog::CLog(	CString strLogFileName,
			DWORD dwMaxFileLength/* = 1000*/,
			BOOL bDisplayLogSizeWarning /*= TRUE*/):m_strLogfileName(strLogFileName),
													m_bUseLog (TRUE),
													m_pLogFile (NULL),
													m_dwMaxLen(dwMaxFileLength),
													m_bDisplayDlg(bDisplayLogSizeWarning)
{
	ASSERT (!strLogFileName.IsEmpty());
	Initialize ();
}
// uncomment this constructor if u want to take the settings from registry etc..
// code guru has several registry classes derive a registry class for logging and
// save the values in the registry and use it ..

/*
CLog::CLog():m_bUseLog (TRUE),m_pLogFile (NULL),m_dwMaxLen(1000),m_bDisplayDlg(TRUE)
{
	CLogReg Reg;	here read the values from registry !!!
	Reg.GetUseLog  (m_bUseLog);
	Reg.GetLogSize (m_dwMaxLen);
	Reg.GetLogFile (m_strLogfileName);
	ASSERT (!m_strLogfileName.IsEmpty());
	Initialize ();
}
*/
// to be called by the constructor 

/*****************************************************************************************
Function Name : Initialize 
Purpose		  : function called by the constructors to initialize the object
Parameters    : none
Return Type   : void 
Date  		  : 17-Jan-99
Modification History:
*****************************************************************************************/
void CLog::Initialize ()
{
	InitializeCriticalSection(&LogCriticalSection);
	CFileException e;
	if (m_dwMaxLen == 0)	// if it is Zero there will be a deluge of errors !!
		m_dwMaxLen = 1000;
	m_dwMaxLen *= 1024;		// convert lenght supplied into kb's
	if (m_bUseLog)
	{
		m_pLogFile = new CFile();
		ASSERT (m_pLogFile != NULL);
		
		if (m_strLogfileName.IsEmpty ())
		{
			delete m_pLogFile;
			m_pLogFile = NULL;
			return;
		}
		if(!m_pLogFile->Open( m_strLogfileName,	CFile::modeCreate	 |	// if not there create it
												CFile::modeNoTruncate|	// Dont truncate 
												CFile::shareDenyNone |	// Let others also read
												CFile::modeWrite, &e ) )// Write into it
		{
			delete  m_pLogFile;
			m_pLogFile = NULL;	// we were not able to create the file so set ptr to NULL
		#ifdef _DEBUG   
			afxDump << "File could not be opened " << e.m_cause << "\n";
		#endif 
		// use these if u need  messages in different languages
		//CString strMessage,strHeading;
		//strMessage =("IDS_LOG_UNABLETO_OPEN_ERROR"); 
		//strHeading =("IDS_HEAD_BP_ERROR");
		//MessageBox(NULL,strMessage,strHeading,MB_OK);
		MessageBox(NULL,"Unable to open Log file for writing","Log",MB_OK);
		}
		if (m_pLogFile != NULL)
			m_pLogFile->SeekToEnd () ;
	}

}
CLog::~CLog()
{
	if (m_pLogFile != NULL)		
	{
		m_pLogFile->Close ();
		delete m_pLogFile;
		m_pLogFile = NULL;
	}
}

/*****************************************************************************************
Function Name : LogMessage 
Purpose		  : Log a Message 
Parameters    : UINT uMsgID
Return Type   : void 
Date  		  : 04-Nov-98
Modification History:
*****************************************************************************************/
void CLog::LogMessage (UINT uMsgID)
{
	if (!m_bUseLog)		// Does the user want a log ?
		return;
	if (m_pLogFile == NULL)		
		return;
	CString strMsg;
	if (strMsg.LoadString (uMsgID))	// Load the String from the string table
	{
		CTime tmTime = CTime::GetCurrentTime ();
		//strMsg =((tmTime.Format ("%m/%d/%y %H:%M:%S  ")) + strMsg +CRLF);
		strMsg =((tmTime.Format ("%H:%M:%S  ")) + strMsg +CRLF);
		m_pLogFile->Write (strMsg,strMsg.GetLength());
		DisplayWarningMessage();
	}
	else
		ASSERT (FALSE);
}

/*****************************************************************************************
Function Name : LogMessage 
Purpose		  : Log Message  with  a string
Parameters    : CString strMsg
Return Type   : void 
Date  		  : 04-Nov-98
Modification History:
*****************************************************************************************/
void CLog::LogMessage (CString strMsg)
{
	if (!m_bUseLog)
		return;
	if (m_pLogFile  == NULL)
		return;
	if (strMsg.IsEmpty ())
		return;
	CTime tmTime = CTime::GetCurrentTime();
	//strMsg =((tmTime.Format ("%m/%d/%y %H:%M:%S  ")) + strMsg +CRLF);
	strMsg =((tmTime.Format ("%H:%M:%S  ")) + strMsg +CRLF);
	m_pLogFile->Write (strMsg,strMsg.GetLength());
	DisplayWarningMessage();
}

/*****************************************************************************************
Function Name : DisplayWarningMessage
Purpose		  : Displays a Warning Message if file lenh excceds limit
Parameters    : none
Return Type   : void 
Date  		  : 05-Nov-98
Modification History:
*****************************************************************************************/
void CLog::DisplayWarningMessage()
{
	if (!m_bDisplayDlg)				// if a Warning Message Is already being shown
		return;						// dont populate the screen with more messages
	if(m_pLogFile == NULL)
		return;
	if (m_pLogFile->GetLength () <= m_dwMaxLen)		// Has file length exceded the limit?
		return;
	AfxBeginThread(MessageBoxThreadProcFunc,(LPVOID)&m_bDisplayDlg);
	m_bDisplayDlg = FALSE ;			// dont come back until user asks 
}

/*****************************************************************************************
Function Name : MessageBoxThreadProcFunc
Purpose		  : Message Box Thread function
Parameters    : LPVOID pParam
Return Type   : 
Date  		  : 09-Nov-98
Modification History:
*****************************************************************************************/
UINT MessageBoxThreadProcFunc(LPVOID pParam)
{	
	EnterCriticalSection(&LogCriticalSection);			// We are setting a variable here so
	BOOL *pbDisplayDlg = (BOOL*)pParam;
	(*pbDisplayDlg) = FALSE;							// take some precaution

	CString strMessage,strHeading;
	strMessage="Log file length has exceeded the maximum limit";//.LoadString("IDS_LOG_FILE_LEN_WARNING");
	strHeading="Log- Warning";//.LoadString("IDS_HEAD_BP_WARNING");

	if (MessageBox(NULL,strMessage,strHeading,MB_OKCANCEL) == IDOK)
	(*pbDisplayDlg) = TRUE;
	LeaveCriticalSection(&LogCriticalSection);
	return 0;
}

/*****************************************************************************************
Function Name : DeleteLogFile
Purpose		  : Deletes the Log File
Parameters    : None
Return Type   : BOOL 
Date  		  : 05-Nov-98
Modification History:
11/11/98		Converted Delete to Truncate the file to Zero length
*****************************************************************************************/
BOOL CLog::ClearLogFile()
{
	if (m_pLogFile != NULL)
		m_pLogFile->SetLength (0);				// The Log is gone !!!
	return TRUE;
}
