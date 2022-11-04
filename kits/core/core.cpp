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

#include <QString>
#include <QDebug>

const std::string
DesktopKit::Core::Common::getEnv(const std::string &key)
{
    QString value;
    if ( !key.empty() ) { value = qgetenv( key.c_str() ); }
    return value.toStdString();
}

bool
DesktopKit::Core::Common::setEnv(const std::string &key,
                                 const std::string &value)
{
    if ( key.empty() ) { return false; }
    return qputenv( key.c_str(), value.c_str() );
}

const std::vector<std::string>
DesktopKit::Core::BaseDir::getApplicationsPaths()
{
    std::vector<std::string> paths;
    return paths;
}

const std::string
DesktopKit::Core::BaseDir::getCachePath()
{
    QString path;
    return path.toStdString();
}

const std::string
DesktopKit::Core::BaseDir::getConfigPath()
{
    QString path;
    return path.toStdString();
}

const std::string
DesktopKit::Core::BaseDir::getDataPath()
{
    QString path;
    return path.toStdString();
}

const std::vector<std::string>
DesktopKit::Core::BaseDir::getDataPaths()
{
    std::vector<std::string> paths;
    return paths;
}

const std::string
DesktopKit::Core::BaseDir::getDesktopPath()
{
    QString path;
    return path.toStdString();
}

const std::string
DesktopKit::Core::BaseDir::getDocumentsPath()
{
    QString path;
    return path.toStdString();
}

const std::string
DesktopKit::Core::BaseDir::getDownloadPath()
{
    QString path;
    return path.toStdString();
}

const std::vector<std::string>
DesktopKit::Core::BaseDir::getFontsPaths()
{
    std::vector<std::string> paths;
    return paths;
}

const std::vector<std::string>
DesktopKit::Core::BaseDir::getIconsPaths()
{
    std::vector<std::string> paths;
    return paths;
}

const std::vector<std::string>
DesktopKit::Core::BaseDir::getMimeGenericPaths()
{
    std::vector<std::string> paths;
    return paths;
}

const std::vector<std::string>
DesktopKit::Core::BaseDir::getMimeGlobPaths()
{
    std::vector<std::string> paths;
    return paths;
}

const std::vector<std::string>
DesktopKit::Core::BaseDir::getMimeTypePaths()
{
    std::vector<std::string> paths;
    return paths;
}

const std::string
DesktopKit::Core::BaseDir::getMoviesPath()
{
    QString path;
    return path.toStdString();
}

const std::string
DesktopKit::Core::BaseDir::getMusicPath()
{
    QString path;
    return path.toStdString();
}

const std::string
DesktopKit::Core::BaseDir::getPicturesPath()
{
    QString path;
    return path.toStdString();
}

const std::vector<std::string>
DesktopKit::Core::BaseDir::getPixmapPaths()
{
    std::vector<std::string> paths;
    return paths;
}

const std::string
DesktopKit::Core::BaseDir::getStatePath()
{
    QString path;
    return path.toStdString();
}

const std::string
DesktopKit::Core::BaseDir::getTempPath()
{
    QString path;
    return path.toStdString();
}

const std::string
DesktopKit::Core::BaseDir::getThumbnailsPath()
{
    QString path;
    return path.toStdString();
}

const std::string
DesktopKit::Core::BaseDir::getTrashPath()
{
    QString path;
    return path.toStdString();
}
