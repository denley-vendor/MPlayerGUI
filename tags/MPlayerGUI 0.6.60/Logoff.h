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

#ifndef  ___Logoff_h___
#define  ___Logoff_h___

// Enums...
enum CMD{ NONE, LOGOFF, POWEROFF, RESTART, SHUTDOWN };


// Class definition...
class CLogoff{

public:

   // Constructor...
   CLogoff ( void );
   // Destructor...
   ~CLogoff( void );

   // Public functions...
   void Logoff( void );
   void Poweroff( void );
   void Restart( void );
   void Shutdown( void );

private:

   // Data members...
   BOOL _isWinNT;

   // Private functions...
   void EnableShutdownPrivileges( void );
   void DisableShutdownPrivileges( void );

};//end class CLogoff

#endif  // ___Logoff_h___
