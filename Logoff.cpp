/*********************************************************************
Name: Logoff
Programmer: Brent T. Bishop
Date Begun: 08-13-2002
Date Finished: 08-14-2002
Version: 1.0

   Copyright (C) 2002  Brent T. Bishop

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

   If you find any bugs or if you implement some more functionality,
   please sent the updated code to me.

   EMAIL: brent.bishop@byu.net

*********************************************************************/

#define  ___Logoff_cpp___

// Includes...
#include "StdAfx.h"
#include "Logoff.h"


/*------------------------------------------------------------------*\
|  CLogoff() - Constructor
\*------------------------------------------------------------------*/

CLogoff::CLogoff( void ){

   // Variables...
   CHAR buffer[ 100 ];

   // Find out if OS is Windows NT/2000/XP...
   GetEnvironmentVariable( "OS", buffer, 100 );
   if( strcmp( "Windows_NT", buffer ) == 0 )
      _isWinNT = TRUE;
   else
      _isWinNT = FALSE;

}//end constructor CLogoff()


/*------------------------------------------------------------------*\
|  ~CLogoff() - Destructor
\*------------------------------------------------------------------*/

CLogoff::~CLogoff( void ){
}//end destructor ~CLogoff()


/*------------------------------------------------------------------*\
|  Logoff()
\*------------------------------------------------------------------*/

void CLogoff::Logoff( void ){
   ExitWindowsEx( EWX_LOGOFF, 0 );
}//end function Logoff()


/*------------------------------------------------------------------*\
|  Poweroff()
\*------------------------------------------------------------------*/

void CLogoff::Poweroff( void ){
   if( _isWinNT ) EnableShutdownPrivileges();
   // ExitWindowsEx( EWX_POWEROFF, 0 );
   // HOTFIX by Jason
   ExitWindowsEx(EWX_SHUTDOWN | EWX_POWEROFF | EWX_FORCE, 0);
   if( _isWinNT ) DisableShutdownPrivileges();
}//end function Poweroff()


/*------------------------------------------------------------------*\
|  Restart()
\*------------------------------------------------------------------*/

void CLogoff::Restart( void ){
   if( _isWinNT ) EnableShutdownPrivileges();
   ExitWindowsEx( EWX_REBOOT, 0 );
   if( _isWinNT ) DisableShutdownPrivileges();
}//end function Restart()


/*------------------------------------------------------------------*\
|  Shutdown()
\*------------------------------------------------------------------*/

void CLogoff::Shutdown( void ){
   if( _isWinNT ) EnableShutdownPrivileges();
   ExitWindowsEx( EWX_SHUTDOWN, 0 );
   if( _isWinNT ) DisableShutdownPrivileges();
}//end function Shutdown()


/*------------------------------------------------------------------*\
|  EnableShutdownPrivileges()
\*------------------------------------------------------------------*/

void CLogoff::EnableShutdownPrivileges( void ){

   // Variables...
   HANDLE token;
   TOKEN_PRIVILEGES privileges;

   // Get the current process token handle...
   if( !OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token ))
      AfxMessageBox( TEXT( "ERROR: Unable to open process token." ), NULL, MB_OK | MB_ICONERROR );

   // Get the LUID for shutdown privilege...
   LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[ 0 ].Luid );

   // Set parameters for AdjustTokenPrivileges...
   privileges.PrivilegeCount = 1;
   privileges.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;

   // Enable shutdown privilege...
   AdjustTokenPrivileges( token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0 );
   if( GetLastError() != ERROR_SUCCESS )
      AfxMessageBox( TEXT( "ERROR: Uanble to adjust token privileges." ), NULL, MB_OK | MB_ICONERROR );

}//end function EnableShutdownPrivileges()


/*------------------------------------------------------------------*\
|  DisableShutdownPrivileges()
\*------------------------------------------------------------------*/

void CLogoff::DisableShutdownPrivileges( void ){

   // Variables...
   HANDLE token;
   TOKEN_PRIVILEGES privileges;

   // Get the current process token handle...
   if( !OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token ))
      AfxMessageBox( TEXT( "ERROR: Unable to open process token." ), NULL, MB_OK | MB_ICONERROR );

   // Get the LUID for shutdown privilege...
   LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[ 0 ].Luid );

   // Set parameters for AdjustTokenPrivileges...
   privileges.PrivilegeCount = 1;
   privileges.Privileges[ 0 ].Attributes = 0;

   // Disable shutdown privilege...
   AdjustTokenPrivileges( token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0 );
   if( GetLastError() != ERROR_SUCCESS )
      AfxMessageBox( TEXT( "ERROR: Uanble to adjust token privileges." ), NULL, MB_OK | MB_ICONERROR );

}//end function DisableShutdownPrivileges()
