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
#include <QDir>
#include <QSettings>

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

const std::vector<DesktopKit::Core::Mime::MimeItem>
DesktopKit::Core::Mime::getItems(bool incAlias,
                                 bool incGlobs,
                                 bool incApps)
{
    std::vector<DesktopKit::Core::Mime::MimeItem> result;

    for ( auto &item : findMimeItems(getIcons(), incAlias, incGlobs, incApps) ) {
        if ( containsMimeItem(result, item.type) ) { continue; }
        result.push_back(item);
    }
    for ( auto &item : findMimeItems(getGenericIcons(), incAlias, incGlobs, incApps) ) {
        if ( containsMimeItem(result, item.type) ) { continue; }
        result.push_back(item);
    }
    return result;
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
DesktopKit::Core::Mime::getAlias()
{
    std::vector<DesktopKit::Core::Mime::IconItem> result;
    for ( auto &file : DesktopKit::Core::BaseDir::getMimeAliasPaths() ) {
        for ( auto &mime : getMimeIconsFromFile(file, " ") ) {
            if ( containsIconItem(result, mime.key) ) { continue; }
            result.push_back(mime);
        }
    }
    return result;
}

const std::vector<DesktopKit::Core::Mime::AppItem>
DesktopKit::Core::Mime::getAppsInfo()
{
    std::vector<DesktopKit::Core::Mime::AppItem> result;
    for ( auto &file : DesktopKit::Core::BaseDir::getMimeAppsInfoPaths() ) {
        for ( auto &mime : getMimeIconsFromFile(file, "=") ) {
            if ( containsAppItem(result, mime.key) ) { continue; }
            DesktopKit::Core::Mime::AppItem item;
            item.key = mime.key;
            QStringList apps = QString::fromStdString(mime.value).split(";", QT_SKIP_EMPTY);
            for (auto &app : apps) { item.apps.push_back( app.toStdString() ); }
            result.push_back(item);
        }
    }
    return result;
}

const std::vector<std::string>
DesktopKit::Core::Mime::getAppsForMime(const std::string &mime)
{
    std::vector<std::string> result;
    for ( auto &item : getAppsInfo() ) {
        if (item.key == mime) {
            for (auto &app : item.apps) {
                if ( containsInStrings(result, app) ) { continue; }
                result.push_back(app);
            }
            break;
        }
    }
    return result;
}

const std::string
DesktopKit::Core::Mime::getIconForMime(const std::string &mime)
{
    std::string icon;
    icon = getValueFromIconItems(getIcons(), mime);
    if ( icon.empty() ) { icon = getValueFromIconItems(getGenericIcons(), mime); }
    if ( icon.empty() ) { // TODO: should probably check if it's an alias before giving up?
    }
    // TODO: add fallback
    return icon;
}

const std::vector<std::string>
DesktopKit::Core::Mime::getApplications()
{
    std::vector<std::string> result;
    for ( auto &path : DesktopKit::Core::BaseDir::getApplicationsPaths() ) {
        QStringList filter;
        filter << "*.desktop" << "*.app" << "*.AppDir" << "*.AppImage";
        QDir dir( QString::fromStdString(path) );
        for ( auto &app : dir.entryList(filter) ) { result.push_back( QString("%1/%2").arg(dir.absolutePath(),
                                                                                           app).toStdString() ); }
    }
    return result;
}

const std::vector<DesktopKit::Core::Mime::DesktopItem>
DesktopKit::Core::Mime::getApplicationItems()
{
    std::vector<DesktopKit::Core::Mime::DesktopItem> result;
    for ( auto &file : getApplications() ) {
        DesktopKit::Core::Mime::DesktopItem item;
        QFileInfo info( QString::fromStdString(file) );
        if ( info.exists() &&
             info.isFile() &&
             info.suffix() == "desktop")
        { // TODO: .desktop
            QSettings ini(info.absoluteFilePath(), QSettings::IniFormat);
            ini.beginGroup("Desktop Entry");
            item.name = ini.value("Name").toString().toStdString();
            item.comment = ini.value("Comment").toString().toStdString();
            item.icon = ini.value("Icon").toString().toStdString();
            if ( ini.value("TryExec").isValid() ) {
                item.exec = ini.value("TryExec").toString().toStdString();
            } else {
                item.exec = ini.value("Exec").toString().toStdString();
            }
            ini.endGroup();
            if ( !item.name.empty() && !item.exec.empty() ) { result.push_back(item); }
        } else if ( DesktopKit::Core::BaseDir::isAppDir(file) ) {
            // TODO: .AppDir
        }
    }
    return result;
}

const std::vector<DesktopKit::Core::Mime::IconItem>
DesktopKit::Core::Mime::getMimeIconsFromFile(const std::string &filename,
                                             const std::string &splitter)
{
    std::vector<DesktopKit::Core::Mime::IconItem> result;
    QFile file( QString::fromStdString(filename) );
    if ( !file.open(QIODevice::ReadOnly|QIODevice::Text) ) { return result; }
    QTextStream s(&file);
    while ( !s.atEnd() ) {
        QStringList line = s.readLine().split(QString::fromStdString(splitter), QT_SKIP_EMPTY);
        if (line.count() != 2 && line.count() != 3) { continue; }
        int keyIndex = line.count() == 3 ? 1 : 0;
        int valueIndex = line.count() == 3 ? 2 : 1;
        QString key = line.at(keyIndex).trimmed();
        QString value = line.at(valueIndex).trimmed();
        if (value == "__NOGLOBS__") { continue; }
        if ( !key.isEmpty() && !value.isEmpty() ) {
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
DesktopKit::Core::Mime::containsInStrings(const std::vector<std::string> &items,
                                          const std::string &search)
{
    for (auto &item : items) {
        if (item == search) { return true; }
    }
    return false;
}

bool
DesktopKit::Core::Mime::containsIconItem(const std::vector<DesktopKit::Core::Mime::IconItem> &items,
                                         const std::string &search,
                                         bool searchInKey)
{
    for (auto &item : items) {
        if (searchInKey && item.key == search) { return true; }
        else if (!searchInKey && item.value == search) { return true; }
    }
    return false;
}

bool
DesktopKit::Core::Mime::containsAppItem(const std::vector<DesktopKit::Core::Mime::AppItem> &items,
                                        const std::string &search)
{
    for (auto &item : items) {
        if (item.key == search) { return true; }
    }
    return false;
}

bool
DesktopKit::Core::Mime::containsMimeItem(const std::vector<DesktopKit::Core::Mime::MimeItem> &items,
                                         const std::string &search)
{
    for (auto &item : items) {
        if (item.type == search) { return true; }
    }
    return false;
}

const std::string
DesktopKit::Core::Mime::getValueFromIconItems(const std::vector<DesktopKit::Core::Mime::IconItem> &items,
                                              const std::string &key)
{
    for (auto &item : items) {
        if (item.key == key) { return item.value; }
    }
    return std::string();
}

const std::string
DesktopKit::Core::Mime::getKeyFromIconItems(const std::vector<DesktopKit::Core::Mime::IconItem> &items,
                                            const std::string &value)
{
    for (auto &item : items) {
        if (item.value == value) { return item.key; }
    }
    return std::string();
}

const std::vector<DesktopKit::Core::Mime::MimeItem>
DesktopKit::Core::Mime::findMimeItems(const std::vector<DesktopKit::Core::Mime::IconItem> &items,
                                      bool incAlias,
                                      bool incGlobs,
                                      bool incApps)
{
    std::vector<DesktopKit::Core::Mime::MimeItem> result;
    for (auto &item : items) {
        if ( containsMimeItem(result, item.key) ) { continue; }
        DesktopKit::Core::Mime::MimeItem mime;
        mime.type = item.key;
        mime.icon = item.value;
        if ( mime.type.empty() || mime.icon.empty() ) { continue; }
        if (incAlias) {
            for ( auto &alias : getAlias() ) {
                if (alias.value == item.key) { mime.alias.push_back(alias.key); }
            }
        }
        if (incGlobs) {
            for ( auto &glob : getGlobs() ) {
                if ( glob.key == item.key ||
                     containsInStrings(mime.alias,
                                       glob.key) ) { mime.files.push_back(glob.value); }
            }
        }
        if (incApps) {
            for ( auto &app : getAppsInfo() ) {
                if ( app.key == item.key ||
                     containsInStrings(mime.alias,
                                       app.key) )
                {
                    for (auto &desktop : app.apps) { mime.apps.push_back(desktop); }
                }
            }
        }
        result.push_back(mime);
    }
    return result;
}
