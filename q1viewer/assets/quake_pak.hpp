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

#ifndef Q1_VIEWER_QUAKE_PAK_HPP
#define Q1_VIEWER_QUAKE_PAK_HPP

#include <common.hpp>

#include <assets/quake_ident.hpp>

#include <cstdio>

/// Wraps around a single Quake 1 PAK file
class qvQuakePak {
public:

#pragma pack(push, 1)

    struct Header final {
        u32 magic;
        u32 ftabOffset;
        u32 ftabLen;
    };

    struct FileEntry final {
        char name[56];
        u32 offset;
        u32 len;
    };

#pragma pack(pop)

protected:
    FILE* pFile = nullptr;

    Header pakHeader {};

    u32 entryCount = 0;
    FileEntry* pakEntries = nullptr;

public:
    /// Quake's 4-byte magic code for pak headers
    constexpr static u32 HEADER_MAGIC = qvEncodeMagic32("PACK");

    enum class Status : u32 {
        OK,

        /// Path string was nullptr
        FILE_PATH_NULL,

        /// File handle was not nullptr
        FILE_ALREADY_OPEN,

        /// Opening the file failed for an unknown reason
        FILE_OPEN_FAILED,

        /// Header was too short!
        HEADER_TOO_SMALL,

        /// Header magic is wrong!
        HEADER_INVALID_MAGIC,

        /// PAK has no entries
        PAK_IS_EMPTY,

        /// PAK entry count is wrong
        PAK_ENTRY_LEN_MISMATCH,

        INDEX_OUT_OF_BOUNDS,
    };

    enum OpenFlags : u32 {
        NONE = 0,

        LAZY_OPEN = 1 << 0,
    };

public:
    // TODO: Abstract the file buffer so in-memory paks can work!

    /// Opens a PAK file from a given path
    Status OpenPakFromFile(const char* pFilePath, u32 flags = OpenFlags::NONE);

    /// Gets a PAK entry from the given index
    Status GetEntryByIndex(u32 index, FileEntry& entry);

    /// Returns the number of entries within this PAK
    u32 GetEntryCount() const;

protected:
    /// Reads all entries within this PAK, doesn't re-allocate after initial read
    Status ReadPakEntries();
};


#endif //Q1_VIEWER_QUAKE_PAK_HPP
