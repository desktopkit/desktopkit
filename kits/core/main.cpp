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
    std::cout << "BaseDir::getApplicationsPaths:" << std::endl;
    for ( auto &dir : BaseDir::getApplicationsPaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "BaseDir::getDataPaths:" << std::endl;
    for ( auto &dir : BaseDir::getDataPaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "BaseDir::getFontsPaths:" << std::endl;
    for ( auto &dir : BaseDir::getFontsPaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "BaseDir::getColorProfilesPaths:" << std::endl;
    for ( auto &dir : BaseDir::getColorProfilesPaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "BaseDir::getIconsPaths:" << std::endl;
    for ( auto &dir : BaseDir::getIconsPaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "BaseDir::getPixmapsPaths:" << std::endl;
    for ( auto &dir : BaseDir::getPixmapsPaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "BaseDir::getMimeGenericIconsPaths:" << std::endl;
    for ( auto &dir : BaseDir::getMimeGenericIconsPaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "BaseDir::getMimeGlobsPaths:" << std::endl;
    for ( auto &dir : BaseDir::getMimeGlobsPaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "BaseDir::getMimeTypePaths:" << std::endl;
    for ( auto &dir : BaseDir::getMimeTypePaths() ) { std::cout << dir << std::endl; }
    std::cout << std::endl;

    std::cout << "BaseDir::getCachePath: " << BaseDir::getCachePath() << std::endl;
    std::cout << "BaseDir::getConfigPath: " << BaseDir::getConfigPath() << std::endl;
    std::cout << "BaseDir::getDataPath: " << BaseDir::getDataPath() << std::endl;
    std::cout << "BaseDir::getDesktopPath: " << BaseDir::getDesktopPath() << std::endl;
    std::cout << "BaseDir::getDocumentsPath: " << BaseDir::getDocumentsPath() << std::endl;
    std::cout << "BaseDir::getDownloadPath: " << BaseDir::getDownloadPath() << std::endl;
    std::cout << "BaseDir::getMusicPath: " << BaseDir::getMusicPath() << std::endl;
    std::cout << "BaseDir::getPicturesPath: " << BaseDir::getPicturesPath() << std::endl;
    std::cout << "BaseDir::getTempPath: " << BaseDir::getTempPath() << std::endl;
    std::cout << "BaseDir::getThumbnailsPath: " << BaseDir::getThumbnailsPath() << std::endl;
    std::cout << "BaseDir::getTrashPath: " << BaseDir::getTrashPath() << std::endl;
    std::cout << "BaseDir::getVideosPath: " << BaseDir::getVideosPath() << std::endl;
    std::cout << "Mime::getType: " << Mime::getType("core-test") << std::endl;
    std::cout << std::endl;

    std::cout << "Mime::getGenericIcons:" << std::endl;
    for ( auto &mime : Mime::getGenericIcons() ) { std::cout << mime.key << " : " << mime.value << std::endl; }
    std::cout << std::endl;

    std::cout << "Mime::getIcons:" << std::endl;
    for ( auto &mime : Mime::getIcons() ) { std::cout << mime.key << " : " << mime.value << std::endl; }
    std::cout << std::endl;

    std::cout << "Mime::getGlobs:" << std::endl;
    for ( auto &mime : Mime::getGlobs() ) { std::cout << mime.key << " : " << mime.value << std::endl; }
    std::cout << std::endl;

    return 0;
}
