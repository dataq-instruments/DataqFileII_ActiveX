#define ANHM 6 /* maximum chars for annotation in header */
#define VWIN 32 /* max # of windows in VGA CODAS header */
#define HB 4 /* data file byte index of hdrcmn structure */
#define THERM1 0x8000 /* special value of dacoff for thermocouple type 1 */
#define DIFFR 0x4000 /* bit in dacoff for differential in expanded header */
#define DGINP 0x2000 /* bit in dacoff for digital input in expanded header */
#define NONLN 0x1000 /* bit in dacoff for nonlinear nonthermocouple channel */
#define LSTPT 0x800 /* bit in dacoff for last point instead of combining */
#define CRULE 0x700 /* bits in dacoff for acquisition method */
#define CRFRQ 0x400 /* CRULE value for frequency */
#define CRMIN 0x200 /* CRULE value for minimum */
#define CRMAX 0x100 /* CRULE value for maximum */

typedef struct winfmt { /* screen window format */
   unsigned char omax; /* max # of overlapping waveforms/window */
   unsigned char tmax; /* max # of time windows per data window */
   unsigned char dmax; /* max # of data windows (affects scale) */
   unsigned char orient; /* 0 for horiz scroll, 1 for vert */
} WINFMT;

typedef struct chinfo { /* information about each channel in file */
   float fscale; /* # of data windows from - to + full scale A/D */
   float foffset; /* part of - to + full scale A/D to add to data */
   double slope; /* slope converts 14-bit data to engr units */
   double intrcpt; /* engr units intercept for data value of 0 */
   char an[ANHM]; /* engineering unit strings, 6 chars max */
   unsigned char nxtchn; /* next logical channel to scan */
   unsigned char rdgppt; /* # readings averaged per file data pt */
   unsigned short pchn: 8; /* phys chn # (1-31), bit 6 = differential */
   unsigned short gaincd: 4; /* gain code for 1,2,5,10,50,100,500,1000,4,8,20,200 */
   unsigned short mvfscd: 4; /* mV full scale code for 5000,10000,2500,2048,1280 */
   unsigned short dacoff; /* D/A converter offset */
} CHINFO;

typedef struct hdrcmn {
   unsigned char chnbeg; /* 4 file byte index of start of charray */
   unsigned char chnsiz; /* 5 # of bytes per charray entry */
   short hdrsiz; /* 6..7 header bytes = 1156 for WFS codas compatiblilty */
   unsigned long datbyt; /* 8..11 # data bytes before trailer */
   unsigned long evtbyt; /* 12..15 # event marker & time stamp bytes */
   unsigned short anfbyt; /* 16..17 # of acquisition annotation function bytes */
   short fvres; /* 18..19 height of full-screen window in lines */
   short fhres; /* 20..21 width of full-screen window in pixels */
   short curpix; /* 22..23 cursor position relative to center of screen */
   struct winfmt vidfmt; /* 24..27 video window format */
   double intrvl; /* 28..35 time between samples on a channel */
   long begtime; /* 36..39 time acquistion opened file, sec since 1/1/70 */
   long endtime; /* 40..43 time when file trailer was written */
   long compress; /* 44..47 compression factor */
   long curpnt; /* 48..51 cursor position */
   long mrkpnt; /* 52..55 time marker position */
   unsigned short pretrig; /* 56..57 pretrigger points */
   unsigned short postrig; /* 58..59 postrigger points */
   short xycleft; /* 60..61 left cursor limit for xy */
   short xycright; /* 62..63 right cursor limit for xy */
   unsigned char fkeys; /* 64
      bit 0 F1 on
      bit 1 F2 on
      bit 2 F3 on
      bit 3 F4 on
      bit 4 F5 on
      bit 5 ALT-F2 baseline
      bit 6 scroll lock on
      bit 7 event markers on
      */
   unsigned char lmkeys; /* 65
      bit  0   ALT-G key grids enabled
      bit  1   U key user annotation enabled
      bits 2-3 L key, 0=none, 1=limits&frq, 2=acqasg&limits&frq, 3=acqasg
      bits 4-5 state of M key selection, 0=mid, 1=min, 2=max, 3=max/min
      bits 6-7 reserved for future use
      */
   char chnnm; /* 66 selected window number - 1, -1 for none */
   unsigned char pwkeys; /* 67
      bits 0-3 state of P key selection
      bits 4-5 state of T key, 0=filename,1=start time,2=end time,3=time/div
      bit 6 set if last scroll direction was reverse
      bit 7 W set for window-oriented scrolling
      */
   unsigned char vc[VWIN]; /* 68..99 chan - 1 for window = o + omax*(t + tmax*d) */
   unsigned short reserved: 1; /* 100 for future use */
   unsigned short data16: 1; /*  file contains 16-bit data & all marks in trailer */
   unsigned short tctyp:2; /*  thermocouple type, 0=K, 1=J, 2=T */
   unsigned short trigmux: 4; /*  multiplexer number for trigger channel */
   unsigned short autotrig: 1; /* 101 oscilloscope mode auto triggers at screen end */
   unsigned short pchan0: 1; /* lowest physical channel is number 0 instead of 1 */
   unsigned short f3sel: 2; /* live display 0=TBF,1=DATA-TM,2=%CHANGE,3=SLOPETM */
   unsigned short f4sel: 2; /* marker display type 0=SEC, 1=SMP, 2=Hz, 3=C/M */
   unsigned short packed: 1; /* file is packed using .rdgppt fields */
   unsigned short f4mag: 1; /* set to display magnitude instead of decibels */
   unsigned short fftfmin: 13; /* 102 lowest frequency index for fft display */
   unsigned short fftwpwr2: 1; /* set for windowed power-of-2 fft */
   unsigned short wintyp: 2; /* data window 0=none,1=hanning,2=Hamming,3=Blackman */
   unsigned short frqavp2: 4; /* 104 fftfrqav + 2 or 4 - fftxzoom */
   unsigned short frqwin: 4; /* size - 1 of moving window for frequency averaging */
   unsigned short trigchan: 4; /* 105 trigger channel source */
   unsigned short erasebar: 1; /* 1 for erase bar on */
   unsigned short dispmode: 2; /* 0=scroll,1=freeze,2=triggered sweep,3=freeze */
   unsigned short trgslope: 1; /* 1 for negative trigger slope */
   short trglevel: 16; /* 106..107 triggered sweep level */
   unsigned short xystripe: 6; /* 107 # of 1/16 screen stripes used for xy */
   unsigned short curnum: 2; /* 0=data cursror, 1=left limit, 2=right limit */
   unsigned short hysteres: 4; /* 109 trigger hysteresis,bits 2-0 AT-CODSAS pen width */
   unsigned short remevenb: 1; /* remote events enabled */
   unsigned short remstenb: 1; /* remote storage enabled */
   unsigned short remevneg: 1; /* remote events triggered on - slope */
   unsigned short remstneg: 1; /* remote storage triggered on - slope */
} HDRCMN;
