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

cmake_minimum_required(VERSION 3.5)

project(DesktopKit VERSION 1.0.0)

include(GNUInstallDirs)

add_subdirectory(kits/core)

install(FILES README.md LICENSE
        DESTINATION ${CMAKE_INSTALL_DOCDIR}-${PROJECT_VERSION})
