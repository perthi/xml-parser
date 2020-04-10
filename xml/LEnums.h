// -*- mode: c++ -*-

#pragma once


/* ****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
***************************************************************************** */

/* ****************************************************************************
******************************************************************************
*** This file is part of logmaster.                                        ***
*** Copyright (C) Per Thomas Hille <pth@embc.no>  http:///www.embc.no      ***
*** all rights reserved                                                    ***
***                                                                        ***
*** logmaster is free software: you can redistribute it and/or modify      ***
*** it under the terms of the Lesser GNU General Public License (LGPL)     ***
*** as published by the Free Software Foundation, either version 3 of the  ***
*** License, or (at your option) any later version.                        ***
***                                                                        ***
*** logmaster is distributed in the hope that it will be useful,           ***
*** but WITHOUT ANY WARRANTY; without even the implied warranty of         ***
*** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          ***
*** GNU General Public License for more details.                           ***
***                                                                        ***
*** You should have received a copy of the Lesser GNU General Public       ***
*** License along with logmaster in the README file in the source code     ***
*** directory. If not, see <http://www.gnu.org/licenses/>.                 ***
******************************************************************************
******************************************************************************/


	enum class  eLOGLEVEL
    {
        LOG_FORCE_DEBUG   =   0x20,     // 00100000
        LOG_DEBUG         =   0x10,     // 00010000
        LOG_INFO          =   0x08,     // 00001000
        LOG_WARNING       =   0x04,     // 00000100
        LOG_ERROR         =   0x02,     // 00000010
        LOG_FATAL         =   0x01,     // 00000001
        LOG_OFF           =   0x00,     // 00000000
        LOG_ALL           =   0xff      // 11111111
    };

