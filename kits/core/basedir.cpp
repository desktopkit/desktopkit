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
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

using namespace DesktopKit::Core;

const std::vector<std::string>
DesktopKit::Core::BaseDir::getApplicationsPaths()
{
    std::vector<std::string> paths;
    paths.push_back( QString("%1/Applications").arg( QDir::homePath() ).toStdString() );
    QStringList locations = QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation);
    for (int i = 0; i < locations.size(); ++i) { paths.push_back( locations.at(i).toStdString() );}
    QStringList bins = QString::fromStdString( Common::getEnv("PATH") ).split(":",
                                                                              Qt::SkipEmptyParts);
    for (int i = 0; i < bins.size(); ++i) { paths.push_back( bins.at(i).toStdString() );}
    return paths;
}

const std::string
DesktopKit::Core::BaseDir::getCachePath()
{
    return getPath(BaseDirPath::pathCache, "CACHE_HOME", ".cache");
}

const std::string
DesktopKit::Core::BaseDir::getConfigPath()
{
    return getPath(BaseDirPath::pathConfig, "CONFIG_HOME", ".config");
}

const std::vector<std::string>
DesktopKit::Core::BaseDir::getColorProfilesPaths()
{
    std::vector<std::string> paths;
    paths.push_back( QString("%1/.icc").arg( QDir::homePath() ).toStdString() );
    paths.push_back( QString("%1/.color/icc").arg( QDir::homePath() ).toStdString() );
    for ( auto &dir : getDataPaths() ) {
        QString path = QString("%1/color/icc").arg( QString::fromStdString(dir) );
        paths.push_back( path.toStdString() );
    }
    return paths;
}

const std::string
DesktopKit::Core::BaseDir::getDataPath()
{
    return getPath(BaseDirPath::pathData, "DATA_HOME", ".local/share");
}

const std::vector<std::string>
DesktopKit::Core::BaseDir::getDataPaths()
{
    std::vector<std::string> paths;
    QStringList locations = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
    for (int i = 0; i < locations.size(); ++i) { paths.push_back( locations.at(i).toStdString() );}
    return paths;
}

const std::string
DesktopKit::Core::BaseDir::getDesktopPath()
{
    return getPath(BaseDirPath::pathDesktop, "", "Desktop");
}

const std::string
DesktopKit::Core::BaseDir::getDocumentsPath()
{
    return getPath(BaseDirPath::pathDocuments, "", "Documents");
}

const std::string
DesktopKit::Core::BaseDir::getDownloadPath()
{
    return getPath(BaseDirPath::pathDownload, "", "Downloads");
}

const std::vector<std::string>
DesktopKit::Core::BaseDir::getFontsPaths()
{
    std::vector<std::string> paths;
    QStringList locations = QStandardPaths::standardLocations(QStandardPaths::FontsLocation);
    for (int i = 0; i < locations.size(); ++i) { paths.push_back( locations.at(i).toStdString() );}
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
DesktopKit::Core::BaseDir::getMusicPath()
{
    return getPath(BaseDirPath::pathMusic, "", "Music");
}

const std::string
DesktopKit::Core::BaseDir::getPicturesPath()
{
    return getPath(BaseDirPath::pathPictures, "", "Pictures");
}

const std::vector<std::string>
DesktopKit::Core::BaseDir::getPixmapsPaths()
{
    std::vector<std::string> paths;
    return paths;
}

const std::string
DesktopKit::Core::BaseDir::getTempPath()
{
    return getPath(BaseDirPath::pathTemp);
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

const std::string
DesktopKit::Core::BaseDir::getVideosPath()
{
    return getPath(BaseDirPath::pathVideos, "", "Videos");
}

const std::string
DesktopKit::Core::BaseDir::getPath(int type,
                                   const std::string &suffix,
                                   const std::string &fallback)
{
    QString path;

    if ( !suffix.empty() ) {
        path = QString::fromStdString( Common::getEnv( QString("DESKTOP_%1")
                                                       .arg( QString::fromStdString(suffix) )
                                                       .toStdString() ) );
        if ( path.isEmpty() ) {
            path = QString::fromStdString( Common::getEnv( QString("XDG_%1")
                                                           .arg( QString::fromStdString(suffix) )
                                                           .toStdString() ) );
        }
    }

    if ( path.isEmpty() && type >= 0) {
        QStandardPaths::StandardLocation location;
        switch (type) {
        case BaseDirPath::pathCache:
            location = QStandardPaths::CacheLocation;
            break;
        case BaseDirPath::pathConfig:
            location = QStandardPaths::ConfigLocation;
            break;
        case BaseDirPath::pathData:
            location = QStandardPaths::DataLocation;
            break;
        case BaseDirPath::pathDesktop:
            location = QStandardPaths::DesktopLocation;
            break;
        case BaseDirPath::pathDocuments:
            location = QStandardPaths::DocumentsLocation;
            break;
        case BaseDirPath::pathDownload:
            location = QStandardPaths::DownloadLocation;
            break;
        case BaseDirPath::pathVideos:
            location = QStandardPaths::MoviesLocation;
            break;
        case BaseDirPath::pathMusic:
            location = QStandardPaths::MusicLocation;
            break;
        case BaseDirPath::pathPictures:
            location = QStandardPaths::PicturesLocation;
            break;
        case BaseDirPath::pathTemp:
            location = QStandardPaths::TempLocation;
            break;
        default:
            location = QStandardPaths::HomeLocation;
        }
        QStringList locations = QStandardPaths::standardLocations(location);
        if (locations.size() > 0) { path = locations.at(0); }
    }

    if ( path.isEmpty() &&
         !fallback.empty() )
    {
        qDebug() << "path using fallback";
        path = QString("%1/%2").arg( QDir::homePath(),
                                     QString::fromStdString(fallback) ); }

    return path.toStdString();
}
