/*-----------------------------------------------------------------------------
This source file is part of Sonetto RPG Engine.

Copyright (C) 2007,2008 Arthur Carvalho de Souza Lima, Guilherme Prá Vieira


Sonetto RPG Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Sonetto RPG Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA or go to
http://www.gnu.org/copyleft/lesser.txt
-----------------------------------------------------------------------------*/

#ifndef SONETTO_SCRIPTFILESERIALIZER_H
#define SONETTO_SCRIPTFILESERIALIZER_H

#include <OgreSerializer.h>

namespace Sonetto {
    class ScriptFile; // Forward declaration

    class ScriptFileSerializer : public Ogre::Serializer
    {
    public:
        ScriptFileSerializer();
        virtual ~ScriptFileSerializer();

        // void exportScriptFile(const ScriptFile *pFile,
        //      const Ogre::String &fileName);
        void importScriptFile(Ogre::DataStreamPtr &stream,
                ScriptFile *pDest);
    };


} // namespace Sonetto

#endif //SONETTO_SCRIPTFILESERIALIZER_H
