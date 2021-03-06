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

#ifndef SONETTO_INPUTMANAGER_H
#define SONETTO_INPUTMANAGER_H

#include <SDL/SDL.h>
#include <OgreSingleton.h>
#include "SonettoPrerequisites.h"
#include "SonettoPlayerInput.h"
#include "SonettoJoystick.h"
#include "SonettoScriptInputHandler.h"

namespace Sonetto
{
    /** Class responsible for managing input resources

        From this class, you can get Sonetto::PlayerInput instances, which you
        can use for retrieving input from joysticks and keyboard.
    */
    class SONETTO_API InputManager : public Ogre::Singleton<InputManager>
    {
    public:
        /** Constructor

        @param
            players Number of PlayerInputs to be created
        */
        InputManager(uint32 players);

        /// Destructor
        ~InputManager();

        /** Overrides standard Singleton retrieval

        @remarks
            Warning: These comments below were copied straight from Ogre3D code.
            Why do we do this? Well, it's because the Singleton
            implementation is in a .h file, which means it gets compiled
            into anybody who includes it. This is needed for the
            Singleton template to work, but we actually only want it
            compiled into the implementation of the class based on the
            Singleton, not all of them. If we don't change this, we get
            link errors when trying to use the Singleton-based class from
            an outside dll.
        @param
            This method just delegates to the template version anyway,
            but the implementation stays in this single compilation unit,
            preventing link errors.
        */
        static InputManager &getSingleton();

        /** Overrides standard Singleton retrieval

        @remarks
            Warning: These comments below were copied straight from Ogre3D code.
            Why do we do this? Well, it's because the Singleton
            implementation is in a .h file, which means it gets compiled
            into anybody who includes it. This is needed for the
            Singleton template to work, but we actually only want it
            compiled into the implementation of the class based on the
            Singleton, not all of them. If we don't change this, we get
            link errors when trying to use the Singleton-based class from
            an outside dll.
        @param
            This method just delegates to the template version anyway,
            but the implementation stays in this single compilation unit,
            preventing link errors.
        */
        static InputManager *getSingletonPtr();

        /** Initializes InputManager

        @remarks
            On Linux builds, this method takes no parameters
        @param
            hWnd Window handle (HWND) to be used with DirectInput.
        */
        void initialize();

        /** Updates all PlayerInputs.

            This is called by Kernel::run(), so you
            don't have to worry about it.
        */
        void update();

        /** Retrieves a PlayerInput given its index

        @remarks
            Be careful not to access an index greater than
            or equal to getPlayerNum().
        */
        PlayerInput *getPlayer(uint32 id);

        /// Retrieves the number of PlayerInputs in the manager
        inline uint32 getPlayerNum() const { return mPlayerNum; }

        /** Gets a joystick to be used by a PlayerInput

        @see
            Joystick
        */
        JoystickPtr _getJoystick(uint32 id);

        /// Returns the number of currently plugged joysticks
        uint32 getJoystickNum() const { return mJoysticks.size(); }

        /// Checks whether the joystick of the given ID is being used by a PlayerInput or not
        bool isJoystickAssigned(uint32 id) const;

        /** Directly checks a physical keyboard key state

            This method is intended mainly for debugging, when user configuration is something
            that should be avoided. It returns the state of a given keyboard key.
        @param
            key Key to be checked.
        */
        inline KeyState getDirectKeyState(uint16 key) const { return mKeyboardStates[key]; }

    private:
        /// Vector of Joystick shared pointers
        typedef std::vector<JoystickPtr> JoystickPtrVector;

        /// PlayerInput vector
        PlayerInputVector mPlayers;

        /// Number of player inputs
        uint32 mPlayerNum;

        /** Vector of Joystick shared pointers

        @see
            _getJoystick()
        */
        JoystickPtrVector mJoysticks;

        /// Whether this singleton is initialized or not
        bool mInitialized;

        /** Keyboard keystates

        @see
            getDirectKeyState()
        */
        KeyState mKeyboardStates[SDLK_LAST + 1];

        ScriptInputHandler mScriptInputHandler;
    };
} // namespace

#endif
