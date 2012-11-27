/* 
	Copyright 2010 OpenRTMFP
 
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License received along this program for more
	details (or else see http://www.gnu.org/licenses/).

	This file is a part of Cumulus.
*/

#include "LUAMember.h"
#include "Peer.h"
#include "Util.h"

using namespace Cumulus;
using namespace std;

const char*		LUAMember::Name="LUAMember";


int LUAMember::Destroy(lua_State* pState) {
	SCRIPT_DESTRUCTOR_CALLBACK(Peer,LUAMember,member)
		delete &member;
	SCRIPT_CALLBACK_RETURN
}

int LUAMember::Release(lua_State* pState) {
	SCRIPT_CALLBACK(Peer,LUAMember,member)
		member.unsubscribeGroups();
	SCRIPT_CALLBACK_RETURN
}

int LUAMember::Get(lua_State *pState) {
	SCRIPT_CALLBACK(Peer,LUAMember,member)
		string name = SCRIPT_READ_STRING("");
		if(name=="id")
			SCRIPT_WRITE_STRING(Util::FormatHex(member.id,ID_SIZE).c_str())
		else if(name=="rawId")
			SCRIPT_WRITE_BINARY(member.id,ID_SIZE)
		else if(name=="release")
			SCRIPT_WRITE_FUNCTION(&LUAMember::Release);
	SCRIPT_CALLBACK_RETURN
}

int LUAMember::Set(lua_State *pState) {
	SCRIPT_CALLBACK(Peer,LUAMember,member)
		string name = SCRIPT_READ_STRING("");
		lua_rawset(pState,1); // consumes key and value
	SCRIPT_CALLBACK_RETURN
}
