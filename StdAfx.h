// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__84541056_C341_484F_A5DF_74901E47B0F0__INCLUDED_)
#define AFX_STDAFX_H__84541056_C341_484F_A5DF_74901E47B0F0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define UWM_SLIDER_PROGRESS              WM_USER + 100
#define UWM_SLIDER_VOLUME                WM_USER + 101
#define UWM_PLAYLIST_PLAY                WM_USER + 102
// #define UWM_SLIDER_BRIGHTNESS            WM_USER + 103
// #define UWM_SLIDER_CONTRAST              WM_USER + 104
// #define UWM_SLIDER_HUE                   WM_USER + 105
// #define UWM_SLIDER_SATURATION            WM_USER + 106
#define UWM_PLAYLIST_DLG_HIDE            WM_USER + 107
#define UWM_STARTUP_OPENFILE             WM_USER + 108
// #define UWM_VSETTINGS_DLG_HIDE           WM_USER + 109
#define UWM_VIEW_MPLAYER_PAUSE           WM_USER + 110
#define UWM_VIEW_MPLAYER_FULLSCREEN      WM_USER + 111
// #define UWM_STATUSBAR_INFO_SWAP          WM_USER + 112
#define UWM_LOG_DLG_HIDE                 WM_USER + 113

#define UWM_MPLAYER_STARTING             WM_USER + 200
#define UWM_MPLAYER_STARTPLAYING         WM_USER + 201
#define UWM_MPLAYER_FAILEDTOSTART        WM_USER + 202
#define UWM_MPLAYER_AUTOSTOPPED          WM_USER + 203
#define UWM_MPLAYER_STOPPED              WM_USER + 204
#define UWM_MPLAYER_LOG                  WM_USER + 205


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "memdc.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__84541056_C341_484F_A5DF_74901E47B0F0__INCLUDED_)
