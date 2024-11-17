// ===================================================================================
//
// Copyright (C) 2024 Liam Reese
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// ===================================================================================

#ifndef QUAKE1VIEWER_QUAKE_IDENT_HPP
#define QUAKE1VIEWER_QUAKE_IDENT_HPP

#include <common.hpp>

#include <cassert>
#include <cstring>

constexpr u32 qvEncodeMagic32(const char* pIdent) {
    u32 value = 0;

    value |= pIdent[0] & 0x000000FF;
    value |= (pIdent[1] << 8) & 0x0000FF00;
    value |= (pIdent[2] << 16) & 0x00FF0000;
    value |= (pIdent[3] << 24) & 0xFF000000;

    return value;
}

#endif //QUAKE1VIEWER_QUAKE_IDENT_HPP
