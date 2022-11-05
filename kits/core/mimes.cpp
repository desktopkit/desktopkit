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
#include <QMimeDatabase>
#include <QMimeType>
#include <QFileInfo>

const std::string
DesktopKit::Core::Mimes::getType(const std::string &filename)
{
    QFileInfo info( QString::fromStdString(filename) );
    bool isApp = false;
    if ( info.isDir() ) {
        QString apprun = QString("%1/AppRun").arg( QString::fromStdString(filename) );
        if ( QFile::exists(apprun) ||
             info.suffix() == QString::fromUtf8("app") ) { isApp = true; }
    } else if ( info.suffix() == QString::fromUtf8("AppImage") ) { isApp = true; }
    if (isApp) { return QString::fromUtf8("application/x-executable").toStdString(); }
    return QMimeDatabase().mimeTypeForFile( QString::fromStdString(filename) ).name().toStdString();
}
