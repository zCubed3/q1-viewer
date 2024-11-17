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

#include "quake_pak.hpp"


qvQuakePak::Status qvQuakePak::OpenPakFromFile(const char* pFilePath, u32 flags) {
    if (pFilePath == nullptr) {
        return Status::FILE_PATH_NULL;
    }

    if (pFile != nullptr) {
        return Status::FILE_ALREADY_OPEN;
    }

    pFile = fopen(pFilePath, "rb");

    if (pFile == nullptr) {
        // TODO: Communicate it was missing, invalid, etc!
        return Status::FILE_OPEN_FAILED;
    }

    u32 itemsRead = fread(reinterpret_cast<void*>(&pakHeader), sizeof(pakHeader), 1, pFile);

    if (itemsRead <= 0) {
        return Status::HEADER_TOO_SMALL;
    }

    if (pakHeader.magic != HEADER_MAGIC) {
        return Status::HEADER_INVALID_MAGIC;
    }

    // If not lazy load, then immediately load the entire file table
    this->entryCount = pakHeader.ftabLen / sizeof(FileEntry);

    if (!(flags & OpenFlags::LAZY_OPEN)) {
        return ReadPakEntries();
    }

    return Status::OK;
}

qvQuakePak::Status qvQuakePak::GetEntryByIndex(u32 index, qvQuakePak::FileEntry& entry) {
    if (index >= this->entryCount) {
        return Status::INDEX_OUT_OF_BOUNDS;
    }

    entry = pakEntries[index];
    return Status::OK;
}

u32 qvQuakePak::GetEntryCount() const {
    return this->entryCount;
}

qvQuakePak::Status qvQuakePak::ReadPakEntries() {
    if (this->entryCount == 0) {
        return Status::PAK_IS_EMPTY;
    }

    // TODO: Let the user clear the entries?
    if (this->pakEntries != nullptr) {
        return Status::OK;
    }

    fseek(pFile, this->pakHeader.ftabOffset, SEEK_SET);

    pakEntries = new FileEntry[entryCount];

    // TODO: Check for OOM?

    u32 readCount = fread(reinterpret_cast<void*>(this->pakEntries), sizeof(FileEntry), this->entryCount, pFile);

    if (readCount != entryCount) {
        return Status::PAK_ENTRY_LEN_MISMATCH;
    }

    return Status::OK;
}

