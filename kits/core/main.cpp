/*
#
# DesktopKit
# <https://desktopkit.org>
# <https://github.com/desktopkit>
#
# Copyright (c) 2022, Ole-André Rodlie <https://github.com/rodlie>
# All rights reserved.
#
# DesktopKit is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# DesktopKit is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#
*/

#include "core.h"

#include <iostream>

using namespace DesktopKit::Core;

int main()
{
    std::cout << "getApplicationsPaths:" << std::endl;
    for ( auto &dir : BaseDir::getApplicationsPaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "getDataPaths:" << std::endl;
    for ( auto &dir : BaseDir::getDataPaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "getFontsPaths:" << std::endl;
    for ( auto &dir : BaseDir::getFontsPaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "getColorProfilesPaths:" << std::endl;
    for ( auto &dir : BaseDir::getColorProfilesPaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "getCachePath: " << BaseDir::getCachePath() << std::endl;
    std::cout << "getConfigPath: " << BaseDir::getConfigPath() << std::endl;
    std::cout << "getDataPath: " << BaseDir::getDataPath() << std::endl;
    std::cout << "getDesktopPath: " << BaseDir::getDesktopPath() << std::endl;
    std::cout << "getDocumentsPath: " << BaseDir::getDocumentsPath() << std::endl;
    std::cout << "getDownloadPath: " << BaseDir::getDownloadPath() << std::endl;
    std::cout << "getMusicPath: " << BaseDir::getMusicPath() << std::endl;
    std::cout << "getPicturesPath: " << BaseDir::getPicturesPath() << std::endl;
    std::cout << "getTempPath: " << BaseDir::getTempPath() << std::endl;
    std::cout << "getThumbnailsPath: " << BaseDir::getThumbnailsPath() << std::endl;
    std::cout << "getTrashPath: " << BaseDir::getTrashPath() << std::endl;
    std::cout << "getVideosPath: " << BaseDir::getVideosPath() << std::endl;

    return 0;
}
