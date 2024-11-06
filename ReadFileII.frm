VERSION 5.00
Object = "{AEAA9C62-8C52-11D3-ABFF-0040055DE809}#1.0#0"; "Dqchart.ocx"
Object = "{CD5C81BD-214B-4DBF-92BB-A4E9DCBDE0CF}#1.0#0"; "DataqFileII.ocx"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   7845
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8145
   LinkTopic       =   "Form1"
   ScaleHeight     =   7845
   ScaleWidth      =   8145
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command7 
      Caption         =   "Clear!"
      Height          =   495
      Left            =   5040
      TabIndex        =   17
      Top             =   6360
      Width           =   1695
   End
   Begin VB.ListBox List1 
      Height          =   3180
      Left            =   240
      TabIndex        =   16
      Top             =   4440
      Width           =   4575
   End
   Begin VB.CommandButton Command6 
      Caption         =   "GetData (Scaled)"
      Height          =   495
      Left            =   5040
      TabIndex        =   15
      Top             =   7080
      Width           =   1695
   End
   Begin VB.OptionButton Option6 
      Caption         =   "c:\remotechannel.wdc"
      Height          =   255
      Left            =   5040
      TabIndex        =   14
      Top             =   4680
      Width           =   2055
   End
   Begin VB.OptionButton Option5 
      Caption         =   "c:\withevents.wdc"
      Height          =   255
      Left            =   5040
      TabIndex        =   13
      Top             =   4320
      Width           =   2055
   End
   Begin VB.OptionButton Option4 
      Caption         =   "c:\sample.wdh"
      Height          =   255
      Left            =   5040
      TabIndex        =   12
      Top             =   3960
      Width           =   2055
   End
   Begin VB.OptionButton Option3 
      Caption         =   "c:\sample.wdq"
      Height          =   255
      Left            =   5040
      TabIndex        =   11
      Top             =   3600
      Width           =   2055
   End
   Begin VB.CommandButton Command5 
      Caption         =   "Open"
      Height          =   495
      Left            =   7320
      TabIndex        =   10
      Top             =   3120
      Width           =   735
   End
   Begin VB.OptionButton Option2 
      Caption         =   "c:\WdcNOCirc.wdc"
      Height          =   255
      Left            =   5040
      TabIndex        =   9
      Top             =   3240
      Width           =   2055
   End
   Begin VB.OptionButton Option1 
      Caption         =   "c:\WdcCirc.wdc"
      Height          =   255
      Left            =   5040
      TabIndex        =   8
      Top             =   2880
      Value           =   -1  'True
      Width           =   1935
   End
   Begin DATAQFILEIILib.ReadDataqFileII ReadDataqFile1 
      Left            =   4320
      Top             =   2760
      _Version        =   65536
      _ExtentX        =   1296
      _ExtentY        =   873
      _StockProps     =   0
   End
   Begin DQCHARTLib.DQChart DQChart1 
      Height          =   1815
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   7695
      _Version        =   65536
      _ExtentX        =   13573
      _ExtentY        =   3201
      _StockProps     =   0
   End
   Begin DQCHARTLib.DQChart DQChart2 
      Height          =   735
      Left            =   240
      TabIndex        =   7
      Top             =   2040
      Width           =   7695
      _Version        =   65536
      _ExtentX        =   13573
      _ExtentY        =   1296
      _StockProps     =   0
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Next EventMarker"
      Height          =   495
      Left            =   3000
      TabIndex        =   5
      Top             =   3720
      Width           =   1455
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Previous EventMarker"
      Height          =   495
      Left            =   240
      TabIndex        =   4
      Top             =   3720
      Width           =   1455
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Next Frame"
      Height          =   495
      Left            =   3000
      TabIndex        =   2
      Top             =   3120
      Width           =   1455
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Previous Frame"
      Height          =   495
      Left            =   240
      TabIndex        =   1
      Top             =   3120
      Width           =   1455
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      Caption         =   "File Pointer"
      Height          =   255
      Left            =   1800
      TabIndex        =   6
      Top             =   3240
      Width           =   1095
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Height          =   375
      Left            =   1800
      TabIndex        =   3
      Top             =   3720
      Width           =   1095
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command5_Click()
ReadDataqFile1.Close

If Option1.Value = True Then
    ReadDataqFile1.FileName = Option1.Caption
ElseIf Option2.Value = True Then
    ReadDataqFile1.FileName = Option2.Caption
ElseIf Option3.Value = True Then
    ReadDataqFile1.FileName = Option3.Caption
ElseIf Option4.Value = True Then
    ReadDataqFile1.FileName = Option4.Caption
ElseIf Option5.Value = True Then
    ReadDataqFile1.FileName = Option5.Caption
Else
    ReadDataqFile1.FileName = Option6.Caption
End If
ReadDataqFile1.Open                         'opens the file

End Sub

Private Sub Command6_Click()
d = ReadDataqFile1.GetData(10, FormatScaled)

If IsEmpty(d) Then
    List1.AddItem "Empty Array returned!"
Else
    cn = UBound(d, 1)
    rn = UBound(d, 2)
    
    
    For j = 0 To rn
        For i = 0 To cn
            List1.AddItem Format(d(i, j))
        Next
    Next
End If
End Sub

Private Sub Command7_Click()
List1.Clear
End Sub

'------------------------------------------------------------------------------------------
'This program demostrates how to play back (read) a regular (non-Pro+) WinDaq file via ActiveX
'------------------------------------------------------------------------------------------
Private Sub Form_Load()
DQChart2.MarkWdqEvent = True                'MarkWinDaq event markers in Chart2
DQChart2.Channel = 0                        'display only the first channel in Chart2
'By default, Chart1 will NOT mark WinDaq event Marker, and plots all (up to 16) channels
'Plot (ReadDataqFile1.GetData(1024, FormatBinary))

End Sub

Private Sub Command1_Click()
ReadDataqFile1.MoveTo -513, 1                     'moves one screen to the left...
Plot (ReadDataqFile1.GetData(513, FormatBinary))  '...and displays the data using subroutine plot

End Sub

Private Sub Command2_Click()
Plot (ReadDataqFile1.GetData(513, FormatBinary))  'moves and displays using subroutine plot one screen to the right (reads DQChart1.Xmax more data points and plots accordingly)

End Sub

Private Sub Command3_Click()
ReadDataqFile1.GoToEventMarker -1, 1                        'moves to the previous event marker (from current location)...
Plot (ReadDataqFile1.GetData(513, FormatBinary))  '...and displays the data using subroutine plot

End Sub

Private Sub Command4_Click()
ReadDataqFile1.GoToEventMarker 1, 1                         'moves to the next event marker (from current location)...
Plot (ReadDataqFile1.GetData(513, FormatBinary))  '...and displays the data using subroutine plot

End Sub

Sub Plot(v)
DQChart1.Chart (v)                                          'displays all (up to 16) channels
DQChart2.Chart (v)                                          'displays the first channel
Label1.Caption = ReadDataqFile1.CurrentLocation             'displays the current location in terms of offset from the beginning

End Sub

Private Sub ReadDataqFile1_ControlError(ByVal Code As Long)
i = 0
End Sub

Private Sub ReadDataqFile1_EndOfFile()
i = 0
End Sub

Private Sub ReadDataqFile1_FileError(ByVal Code As Long)
i = 0
End Sub
