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
#include <QMimeDatabase>
#include <QMimeType>
#include <QFileInfo>
#include <QTextStream>
#include <QtGlobal>

#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
#define QT_SKIP_EMPTY QString::SkipEmptyParts
#else
#define QT_SKIP_EMPTY Qt::SkipEmptyParts
#endif

const std::string
DesktopKit::Core::Mime::getType(const std::string &filename)
{
    QFileInfo info( QString::fromStdString(filename) );
    if ( DesktopKit::Core::BaseDir::isAppDir(filename) ||
         ( info.suffix() == QString::fromUtf8("app") && info.isDir() ) )
    { return QString::fromUtf8("application/x-executable").toStdString(); }
    return QMimeDatabase().mimeTypeForFile( QString::fromStdString(filename) ).name().toStdString();
}

const std::vector<DesktopKit::Core::Mime::IconItem>
DesktopKit::Core::Mime::getIcons()
{
    std::vector<DesktopKit::Core::Mime::IconItem> result;
    for ( auto &file : DesktopKit::Core::BaseDir::getMimeIconsPaths() ) {
        for ( auto &mime : getMimeIconsFromFile(file) ) {
            if ( containsIconItem(result, mime.key) ) { continue; }
            result.push_back(mime);
        }
    }
    return result;
}

const std::vector<DesktopKit::Core::Mime::IconItem>
DesktopKit::Core::Mime::getGenericIcons()
{
    std::vector<DesktopKit::Core::Mime::IconItem> result;
    for ( auto &file : DesktopKit::Core::BaseDir::getMimeGenericIconsPaths() ) {
        for ( auto &mime : getMimeIconsFromFile(file) ) {
            if ( containsIconItem(result, mime.key) ) { continue; }
            result.push_back(mime);
        }
    }
    return result;
}

const std::vector<DesktopKit::Core::Mime::IconItem>
DesktopKit::Core::Mime::getGlobs()
{
    std::vector<DesktopKit::Core::Mime::IconItem> result;
    for ( auto &file : DesktopKit::Core::BaseDir::getMimeGlobsPaths() ) {
        for ( auto &mime : getMimeIconsFromFile(file) ) {
            if ( containsIconItem(result, mime.key) ) { continue; }
            result.push_back(mime);
        }
    }
    return result;
}

const std::vector<DesktopKit::Core::Mime::IconItem>
DesktopKit::Core::Mime::getMimeIconsFromFile(const std::string &filename)
{
    std::vector<DesktopKit::Core::Mime::IconItem> result;
    QFile file( QString::fromStdString(filename) );
    if ( !file.open(QIODevice::ReadOnly|QIODevice::Text) ) { return result; }
    QTextStream s(&file);
    while ( !s.atEnd() ) {
        QStringList line = s.readLine().split(":", QT_SKIP_EMPTY);
        if (line.count() != 2 && line.count() != 3) { continue; }
        int keyIndex = line.count() == 3 ? 1 : 0;
        int valueIndex = line.count() == 3 ? 2 : 1;
        QString key = line.at(keyIndex).trimmed();
        key.replace("/", "-");
        QString value = line.at(valueIndex).trimmed();
        if (value == "__NOGLOBS__") { continue; }
        if ( !key.isEmpty() || !value.isEmpty() ) {
            DesktopKit::Core::Mime::IconItem mime;
            mime.key = key.toStdString();
            mime.value = value.toStdString();
            result.push_back(mime);
        }
    }
    file.close();
    return result;
}

bool
DesktopKit::Core::Mime::containsIconItem(const std::vector<IconItem> &items,
                                         const std::string &search,
                                         bool searchInKey)
{
    for (auto &item : items) {
        if (searchInKey && item.key == search) { return true; }
        else if (!searchInKey && item.value == search) { return true; }
    }
    return false;
}
