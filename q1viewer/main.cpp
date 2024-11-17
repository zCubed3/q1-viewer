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

#include <iostream>

#include <assets/quake_pak.hpp>

int main() {
    qvQuakePak pak;

    qvQuakePak::Status status = pak.OpenPakFromFile("id1/PAK0.PAK");

    if (status != qvQuakePak::Status::OK)
        return (int) status;

    for (int e = 0; e < pak.GetEntryCount(); e++) {
        qvQuakePak::FileEntry entry;
        status = pak.GetEntryByIndex(e, entry);

        if (status != qvQuakePak::Status::OK)
            return (int) status;

        std::cout << "ENTRY " << e << ": " << entry.name << std::endl;
    }

    return (int) status;
}
