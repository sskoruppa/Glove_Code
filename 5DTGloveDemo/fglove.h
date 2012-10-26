/*--------------------------------------------------------------------------*/
// fglove.h
//
// 5DT Data Glove driver SDK
// Version 2.1
//
// Copyright (C) 2000-2005, 5DT <Fifth Dimension Technologies>
// http://www.5dt.com/
/*--------------------------------------------------------------------------*/

#pragma once

/*--------------------------------------------------------------------------*/

//--8<--- SNIP BEGIN
// Release versions of this driver should have everything between "SNIP BEGIN"
// and "SNIP END" pairs chopped out.
// Also, all FGLOVEAPI should be snipped out.

#include <string>

//#define GLOVE_DEMO

#ifdef WIN32
#define FGLOVEAPI __declspec( dllexport )
#else
#define FGLOVEAPI
#endif

#ifndef LPVOID
#define LPVOID void*
#endif

#ifndef SOCKET
#define SOCKET unsigned int
#endif

#ifndef HANDLE
#define HANDLE void*
#endif

// Uncomment the debug level you want -
#define USER_DEBUG 0	// level 0 = user debug
#define DEV_DEBUG 1 	// level 1 = development debug

#define DEBUG_LEVEL USER_DEBUG
//#define DEBUG_LEVEL DEV_DEBUG

#define VENDOR_ID_5DT 0x5d70

// Glove type / capability defines for DG14 Ultra
#define DG14U_R			0x00
#define DG14U_L			0x01
#define DG14U_RW		0x02
#define DG14U_LW		0x03
#define DG14U_RW_SLAVE	0x06
#define DG14U_LW_SLAVE	0x07
#define DG5U_R			0x10
#define DG5U_L			0x11
#define DG5U_RW			0x12
#define DG5U_LW			0x13
#define DG5U_RW_SLAVE	0x16
#define DG5U_LW_SLAVE	0x17
#define DG14U_INFO		0x80		// Mask for info packet
#define MASK_WIRELESS	0x02

// License flag defines
#define LIC_KAYDARA		0x01
#define LIC_MAX			0x02
#define LIC_MAYA		0x04
#define LIC_XSI			0x08
#define LIC_UNIX		0x10

// The packet size for DG14 Ultra
#define PACKET_SIZE_DG14U	29
// Serial Number length
#define LENGTH_SERIAL_NUMBER 11
// Length of date strings
#define LENGTH_DATE 8

#ifdef WIN32
// Network defines
#define NETWORK_REQUESTUPDATE "UPDATE_REQUEST"
#define NETWORK_REQUESTGLOVEINFO "GLOVEINFO_REQUEST"
#define NETWORK_ACKNOWLEDGE "ACKNOWLEDGE"
#define NETWORK_REQUESTDISCONNECT "DISCONNECT_REQUEST"
#define NETWORK_CONNECTACCEPT "CONNECTION_ACCEPTED"
#define NETWORK_CONNECTREJECT "CONNECTION_REJECTED"

enum EfdRecvState
{
	STATE_REQUESTNONE,			// No requests (used only at init)
	STATE_REQUESTSETUP,			// Request for a glove initial setup packet
	STATE_REQUESTDATA,			// A data packet request state.
	STATE_REQUESTDISCONNECT,	// Request for disconnect
};

enum EfdNetworkType
{
	FD_NONE,
	FD_SERVER,
	FD_CLIENT,
	FD_DISCONNECTED
};

// The network packet for the glove
typedef struct
{
	unsigned short	usHeader;
	unsigned short	usVersion;
	unsigned int	uiSequence;
	int				nGloveType;
	int				nGloveHand;
	int				nCurrentGesture;
	unsigned char	acSerialNumber[11];
	unsigned short	pRaw[18];
	unsigned short	pCalibLow[18];
	unsigned short	pCalibHigh[18];
	unsigned short	usFooter;
} GloveNetPacket;

// This packet is used to setup the initial parameters for this glove from a glove host.
typedef struct
{
	int		nSensors;
	float	fSensorMax;
	float	fSensorScaled;
	float	fUpperThr;
	float	fLowerThr;
	int		nGestures;
	int		nGestIndex;
} GloveSetupPacket;
#endif

/*--------------------------------------------------------------------------*/
//--8<--- SNIP END

enum EfdGloveHand
{
	FD_HAND_LEFT,   // left-handed glove
	FD_HAND_RIGHT   // right-handed glove
};

enum EfdGloveTypes
{
	FD_GLOVENONE,   // no glove
	FD_GLOVE5U,		// DG5 Ultra serial
	FD_GLOVE5UW,	// DG5 Ultra serial, wireless
	FD_GLOVE5U_USB,	// DG5 Ultra USB
	FD_GLOVE7,      // 7-sensor
	FD_GLOVE7W,     // 7-sensor, wireless
	FD_GLOVE16,     // 16-sensor
	FD_GLOVE16W,    // 16-sensor, wireless
	FD_GLOVE14U,	// DG14 Ultra serial
	FD_GLOVE14UW,	// DG14 Ultra serial, wireless
	FD_GLOVE14U_USB	// DG14 Ultra USB
};

enum EfdSensors
{
	FD_THUMBNEAR=0,
	FD_THUMBFAR,
	FD_THUMBINDEX,
	FD_INDEXNEAR,
	FD_INDEXFAR,
	FD_INDEXMIDDLE,
	FD_MIDDLENEAR,
	FD_MIDDLEFAR,
	FD_MIDDLERING,
	FD_RINGNEAR,
	FD_RINGFAR,
	FD_RINGLITTLE,
	FD_LITTLENEAR,
	FD_LITTLEFAR,
	FD_THUMBPALM,
	FD_WRISTBEND,
	FD_PITCH,
	FD_ROLL
};

/*--------------------------------------------------------------------------*/

typedef struct
{
//--8<--- SNIP BEGIN

	std::string		m_sPortName;				// port name the glove is currently connected on
	int				m_nGloveHand;				// Left or right handed glove
	int				m_nGloveType;				// Type of currently connected glove
	int				m_nSensors;					// Number of sensors (18 for now, regardless of glove type)
	unsigned short	*m_pSensorRaw;				// Raw (A/D) sensor values
	unsigned short	*m_pUpperCal, *m_pLowerCal;	// Upper & lower calibration values
	float			*m_pSensorMax;				// Max scaled sensor value
	float			*m_pSensorScaled;			// Scaled sensor values
	float			*m_pUpperThr, *m_pLowerThr;	// Upper & lower thresholds for gesture recognition
	int				m_nGestures;				// Number of gesture that are currently defined
	char			**m_ppGestTable;			// Gesture definition table
	int				m_nGestIndex;				// Internal gesture counter
	int				m_aGestBuffer[4];			// Internal gesture buffer
	int				m_nCurrGesture;				// Current gesture being performed

#ifdef WIN32
	HANDLE			m_idComDev;					// Windows handle to comms device
	HANDLE			m_hThread;					// Windows handle to comms threat...ummm thread
	//DCB				m_dcb;						// private; for port info
#endif

#ifdef UNIX
	pthread_t		m_hThread;					// Posix thread handle
	int				m_idComDev;					// File handle for device
	struct termios	m_tty;						// port info
	struct termios	m_ttyBefore;				// port info
	char			m_buf[16384];				// read-ahead buffer
	int				m_iBufBegin;				// read-ahead buffer info
	int				m_iBufEnd;					// read-ahead buffer info
#endif

	unsigned char	m_aInfo[32];				// Glove info data block
	bool			m_bNewData;					// New data available indicator
	void			*m_pCallbackFunc;			// New data arrived callback function
	LPVOID			m_pCallbackParam;			// Callback function parameters
	float			m_fPacketTime;				// Last packet period or 1/Instant packet rate
	int				m_iPacketRate;				// Packet rate over a second period
	bool			m_bPauseUpdateThread;		// Are we updating firmware
	void			*m_pCompanion;				// Wireless companion glove
	unsigned short	m_usVersion;				// USB Version number
	bool			m_bAutoCalibrate;			// Auto calibration on/off
	
	// Wireless stuff
	bool			m_bIsCompanion;				// IS this glove a companion ?
	bool			m_bHasCompanion;			// Does this glove own a companion wireless glove?
	bool			m_bOpenCompanion;			// Is the companion glove open?
	int				m_nPort;					// The COM port number that this glove is on - for wireless use only
	
	/* USB Stuff */
	unsigned short	m_usVID;					// USB Vendor ID
	unsigned short	m_usPID;					// USB Product ID
	char			m_sSerialNumber[LENGTH_SERIAL_NUMBER+1];		// The serial number string
	char			m_sDOB[LENGTH_DATE+1];		// The Date of Birth string
	char			m_sDOS[LENGTH_DATE+1];		// The Date of Shipping string

	/*/ Network stuff /*/
#ifdef WIN32
	SOCKET			m_NetSock;					// The socket.
	SOCKET			m_aClientSocket[64];		// An array of client sockets
	HANDLE			m_ahServerThread[64];		// A handle to the server thread.
	HANDLE			m_hServerListenThread;		// A handle to the server listen thread.
	HANDLE			m_hClientThread;			// A handle to the client thread.
	HANDLE			m_hTimeoutThread;			// A handle to the time out thread.
	HANDLE			m_hMutexRXState;			// A handle for the mutual exclusion for the receive state.
	HANDLE			m_hMutexNetActive;			// A handle for the mutual exclusion for the network.
	float			m_fUpdateRate;				// The rate at which network updates should be checked for (Hz).
	float			m_afClientIdleTime[64];		// An array of client idle times.
	float			m_fServerIdleTime;			// The server idle time.
	EfdRecvState	m_RcvState;					// The current receive state.
	EfdNetworkType	m_NetType;					// Is this a client or a server?
	bool			m_bNetActive;				// Is the network active? This MUST be set to false initially.
	unsigned int	m_uiSeqNum;					// The current packet number.
	unsigned int	m_uiCurClient;				// The current client number.
	unsigned int	m_uiMaxClients;				// The maximum number of clients that may connect to the server.
	unsigned int	m_uiNumClients;				// The current number of connected clients.
#endif

	/*License stuff*/
	bool			m_bLicKaydara;
	bool			m_bLicMax;
	bool			m_bLicMaya;
	bool			m_bLicXSI;
	bool			m_bLicUnix;
	bool			m_bHaveLicenses;
//--8<--- SNIP END
	// The contents of this struct are platform-dependent and subject to
	// change. You should not manipulate the contents of this struct directly.

	/*New stuff*/
//	HWND			m_hWnd;
//	HDEVNOTIFY		m_hDevNotify;

} fdGlove;

/*--------------------------------------------------------------------------*/

FGLOVEAPI fdGlove *fdOpen(char *pPort);	
//FGLOVEAPI fdGlove *fdOpen(char *pPort, bool bOnlyAllowSingleConnection = false);	
FGLOVEAPI int   fdClose(fdGlove *pFG);
FGLOVEAPI int   fdGetGloveHand(fdGlove *pFG);
FGLOVEAPI int   fdGetGloveType(fdGlove *pFG);
FGLOVEAPI int   fdGetNumSensors(fdGlove *pFG);
FGLOVEAPI void  fdGetSensorRawAll(fdGlove *pFG, unsigned short *pData);
FGLOVEAPI unsigned short fdGetSensorRaw(fdGlove *pFG, int nSensor);
FGLOVEAPI void  fdSetSensorRawAll(fdGlove *pFG, unsigned short *pData);
FGLOVEAPI void  fdSetSensorRaw(fdGlove *pFG, int nSensor, unsigned short nRaw);
FGLOVEAPI void  fdGetSensorScaledAll(fdGlove *pFG, float *pData);
FGLOVEAPI float fdGetSensorScaled(fdGlove *pFG, int nSensor);
FGLOVEAPI int   fdGetNumGestures(fdGlove *pFG);
FGLOVEAPI int   fdGetGesture(fdGlove *pFG);
FGLOVEAPI void  fdGetCalibrationAll(fdGlove *pFG, unsigned short *pUpper, unsigned short *pLower);
FGLOVEAPI void  fdGetCalibration(fdGlove *pFG, int nSensor, unsigned short *pUpper, unsigned short *pLower);
FGLOVEAPI void  fdSetCalibrationAll(fdGlove *pFG, unsigned short *pUpper, unsigned short *pLower);
FGLOVEAPI void  fdSetCalibration(fdGlove *pFG, int nSensor, unsigned short nUpper, unsigned short nLower);
FGLOVEAPI void  fdResetCalibration(fdGlove *pFG, int nSensor);
FGLOVEAPI void  fdResetCalibration(fdGlove *pFG);
FGLOVEAPI void  fdGetSensorMaxAll(fdGlove *pFG, float *pMax);
FGLOVEAPI float fdGetSensorMax(fdGlove *pFG, int nSensor);
FGLOVEAPI void  fdSetSensorMaxAll(fdGlove *pFG, float *pMax);
FGLOVEAPI void  fdSetSensorMax(fdGlove *pFG, int nSensor, float fMax);
FGLOVEAPI void  fdGetThresholdAll(fdGlove *pFG, float *pUpper, float *pLower);
FGLOVEAPI void  fdGetThreshold(fdGlove *pFG, int nSensor, float *pUpper, float *pLower);
FGLOVEAPI void  fdSetThresholdAll(fdGlove *pFG, float *pUpper, float *pLower);
FGLOVEAPI void  fdSetThreshold(fdGlove *pFG, int nSensor, float fUpper, float fLower);
FGLOVEAPI void  fdGetGloveInfo(fdGlove *pFG, unsigned char *pData);
FGLOVEAPI void  fdGetDriverInfo(fdGlove *pFG, unsigned char *pData);
FGLOVEAPI void	fdSetCallback(fdGlove *pFG,void *pFunc, LPVOID param);
FGLOVEAPI void	fdRemoveCallback(fdGlove *pFG);
FGLOVEAPI int	fdGetPacketRate(fdGlove *pFG);
FGLOVEAPI bool	fdNewData(fdGlove *pFG);
FGLOVEAPI int	fdGetFWVersionMajor(fdGlove *pFG);
FGLOVEAPI int	fdGetFWVersionMinor(fdGlove *pFG);
FGLOVEAPI bool	fdGetAutoCalibrate(fdGlove *pFG);
FGLOVEAPI bool	fdSetAutoCalibrate(fdGlove *pFG, bool bAutoCalibrate);
FGLOVEAPI bool	fdSaveCalibration(fdGlove *pFG, const char *pFileName);
FGLOVEAPI bool	fdLoadCalibration(fdGlove *pFG, const char *pFileName);
FGLOVEAPI int	fdScanUSB(unsigned short *aPID, int &nNumMax);
FGLOVEAPI int	fdScanUSB();

//--8<--- SNIP BEGIN
// Don't want the user to see these global babies
static bool		g_bSecondWireless[10];			// Static value to indicate presence of second glove
static void		*g_ppWireless[10];				// Other wireless glove pointer
// These are functions we do not want the user to see (just yet...)
FGLOVEAPI fdGlove *fdOpen(char *pPort);
FGLOVEAPI float fdGetPacketTime(fdGlove *pFG);
FGLOVEAPI int	fdUpdateFirmware(fdGlove *pFG);
FGLOVEAPI bool	fdCheckWireless(char *pPort);
FGLOVEAPI bool	fdGetSerialNumber(fdGlove *pFG, char *pData);
// Restricted Info functions
FGLOVEAPI bool	fdGetDOB(fdGlove *pFG, char *pData);
FGLOVEAPI bool	fdGetDOS(fdGlove *pFG, char *pData);
// License functions
FGLOVEAPI bool	fdCheckLicenseKaydara(fdGlove *pFG);
FGLOVEAPI bool	fdCheckLicenseMax(fdGlove *pFG);
FGLOVEAPI bool	fdCheckLicenseMaya(fdGlove *pFG);
FGLOVEAPI bool	fdCheckLicenseXSI(fdGlove *pFG);
FGLOVEAPI bool	fdCheckLicenseUnix(fdGlove *pFG);
FGLOVEAPI bool	fdUpdateLicense(fdGlove *pFG, unsigned char ucByte);
FGLOVEAPI bool	fdSetLicense(fdGlove *pFG, unsigned char ucFlags);
FGLOVEAPI bool	fdClearLicense(fdGlove *pFG);
void fdSetDriverDefaults(fdGlove *pFG);
fdGlove *InitGloveStruct(void);

#ifdef WIN32
// Network functions
FGLOVEAPI bool fdStartServer(fdGlove *pFG, float fRate, unsigned int uPort, unsigned int uiMaxClients);
FGLOVEAPI fdGlove *fdStartClient(float fRate, unsigned int uPort, const char *szServerName);
FGLOVEAPI bool fdStopServer(fdGlove *pFG);
FGLOVEAPI bool fdStopClient(fdGlove **ppFG);
FGLOVEAPI void fdNetworkActivate(fdGlove *pFG);
FGLOVEAPI void fdNetworkDeactivate(fdGlove *pFG);
FGLOVEAPI bool const fdIsNetworkRunning(const fdGlove *pFG);
FGLOVEAPI EfdNetworkType const fdGetNetworkType(const fdGlove *pFG);
FGLOVEAPI unsigned int const fdGetNumClients(const fdGlove *pFG);
#endif

//--8<--- SNIP END