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

#include "SonettoKernel.h"
#include "SonettoMapModule.h"
#include "GenericBootModule.h"

namespace BootModule
{
    // ----------------------------------------------------------------------
    // BootModule::GenericBootModule implementation
    // ----------------------------------------------------------------------
    GenericBootModule::GenericBootModule() : BootModule::BootModule()
    {
        mBgColor = Ogre::ColourValue(0.0f,0.0f,0.0f,1.0f);
    }
    // ----------------------------------------------------------------------
    GenericBootModule::~GenericBootModule() {}
    // ----------------------------------------------------------------------
    void GenericBootModule::initialize()
    {
        BootModule::initialize();

        #ifndef DEBUG
            Sonetto::Kernel &kernel = Sonetto::Kernel::getSingleton();

            kernel.setFading(Sonetto::Kernel::FAD_FADED_OUT);
            kernel.changeFading(Sonetto::Kernel::FAD_FADING_IN,1.0f);
        #else
            setActionNextModule();
        #endif
    }
    // ----------------------------------------------------------------------
    void GenericBootModule::update()
    {
        BootModule::update();

        #ifndef DEBUG
            Sonetto::Kernel &kernel = Sonetto::Kernel::getSingleton();

            if (kernel.getFadingState() == Sonetto::Kernel::FAD_FADED_IN)
            {
                setActionNextModule();
            }
        #endif
    }
    // ----------------------------------------------------------------------
    void GenericBootModule::deinitialize()
    {
        BootModule::deinitialize();
    }
    // ----------------------------------------------------------------------
    void GenericBootModule::halt()
    {
        BootModule::halt();
    }
    // ----------------------------------------------------------------------
    void GenericBootModule::resume()
    {
        BootModule::resume();
    }
    // ----------------------------------------------------------------------
    void GenericBootModule::setActionNextModule()
    {
        Sonetto::Kernel &kernel = Sonetto::Kernel::getSingleton();

        Sonetto::MapModule::StaticData.id =
                Sonetto::Database::getSingleton().system.startMap;

        #ifndef DEBUG
            kernel.setActionOnFadeEnd(Sonetto::Kernel::KA_CHANGE_MODULE,
                    Sonetto::Kernel::MA_CHANGE,Sonetto::Module::MT_MAP);
            kernel.changeFading(Sonetto::Kernel::FAD_FADING_OUT,1.0f);
        #else
            kernel.setAction(Sonetto::Kernel::KA_CHANGE_MODULE,
                    Sonetto::Kernel::MA_CHANGE,Sonetto::Module::MT_MAP);
        #endif
    }
} // namespace
