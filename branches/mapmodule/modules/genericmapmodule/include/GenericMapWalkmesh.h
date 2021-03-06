/*-----------------------------------------------------------------------------
Copyright (c) 2009, Sonetto Project Developers
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1.  Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
2.  Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
3.  Neither the name of the Sonetto Project nor the names of its contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
-----------------------------------------------------------------------------*/

#ifndef GENERICMAPMODULE_WALKMESH_H
#define GENERICMAPMODULE_WALKMESH_H

#include <vector>
#include <OgreVector3.h>
#include "GenericMapPrerequisites.h"

namespace GenericMapModule
{
    class Walkmesh
    {
    public:
        struct Triangle
        {
            Triangle() {}

            Ogre::Vector3 vertices[3];
            uint32 edgeLinks[3];

            uint32 groundType;
            uint32 battleBackground;
        };

        typedef std::vector<Triangle> TriangleVector;

        Walkmesh() {}
        ~Walkmesh() {}

        inline const Ogre::Vector3 &getTriangleVertex(uint32 triID,
                size_t vertexIndex) const
        {
            assert(triID != 0);
            return triangles[triID - 1].vertices[vertexIndex];
        }

        inline uint32 getEdgeLink(uint32 triID,size_t edgeIndex) const
        {
            assert(triID != 0);
            return triangles[triID - 1].edgeLinks[edgeIndex];
        }

        inline uint32 getGroundType(uint32 triID) const
        {
            assert(triID != 0);
            return triangles[triID - 1].groundType;
        }

        inline uint32 getBattleBackground(uint32 triID) const
        {
            assert(triID != 0);
            return triangles[triID - 1].battleBackground;
        }

        TriangleVector triangles;
    };
} // namespace

#endif
