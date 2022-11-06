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
         info.suffix() == QString::fromUtf8("app") ||
         info.suffix() == QString::fromUtf8("AppImage"))
    { return QString::fromUtf8("application/x-executable").toStdString(); }
    return QMimeDatabase().mimeTypeForFile( QString::fromStdString(filename) ).name().toStdString();
}

const std::vector<DesktopKit::Core::Mime::Icon>
DesktopKit::Core::Mime::getGeneric()
{
    std::vector<std::string> types;
    std::vector<DesktopKit::Core::Mime::Icon> result;
    for ( auto &file : DesktopKit::Core::BaseDir::getMimeGenericPaths() ) {
        //qDebug() << "read mime generic" << QString::fromStdString(file);
        for ( auto &mime : getMimeIconsFromFile(file) ) {
            if ( DesktopKit::Core::Common::findStringInVector(types,
                                                              mime.type) ) { continue; }
            //qDebug() << "adding mime generic" << QString::fromStdString(mime.type) << QString::fromStdString(mime.icon);
            types.push_back(mime.type);
            result.push_back(mime);
        }
    }
    return result;
}

const std::vector<DesktopKit::Core::Mime::Suffix>
DesktopKit::Core::Mime::getGlobs()
{
    std::vector<DesktopKit::Core::Mime::Suffix> result;
    return result;
}

const std::vector<DesktopKit::Core::Mime::Icon>
DesktopKit::Core::Mime::getMimeIconsFromFile(const std::string &filename)
{
    std::vector<DesktopKit::Core::Mime::Icon> result;
    QFile file( QString::fromStdString(filename) );
    if ( !file.open(QIODevice::ReadOnly|QIODevice::Text) ) { return result; }
    QTextStream s(&file);
    while ( !s.atEnd() ) {
        QStringList line = s.readLine().split(":", QT_SKIP_EMPTY);
        if (line.count() != 2) { continue; }
        QString mimeName = line.at(0);
        mimeName.replace("/", "-");
        QString mimeIcon = line.at(1);
        if ( !mimeName.isEmpty() && !mimeIcon.isEmpty() ) {
            DesktopKit::Core::Mime::Icon mime;
            mime.type = mimeName.toStdString();
            mime.icon = mimeIcon.toStdString();
            result.push_back(mime);
        }
    }
    file.close();
    return result;
}

const std::vector<DesktopKit::Core::Mime::Suffix>
DesktopKit::Core::Mime::getMimeSuffixFromFile(const std::string &filename)
{
    std::vector<DesktopKit::Core::Mime::Suffix> result;
    if ( !QFile::exists( QString::fromStdString(filename) ) ) { return result; }
    return result;
}
