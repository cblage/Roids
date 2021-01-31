// This file is part of CGLib.
//
// CGLib is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// CGLib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CGLib; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
// Copyright 2007 Carlos Martinho

#ifndef IUPDATE_LISTENER_H
#define IUPDATE_LISTENER_H

namespace cg
{

    /** cg::IUpdateListener is the callback interface for update step.
	 */
    class IUpdateListener
    {
    public:
        virtual void update(unsigned long elapsed_millis) = 0;
    };

} // namespace cg

#endif // IUPDATE_LISTENER_H
