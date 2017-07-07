# wxAudioControls

This is a library of custom wxWidgets controls for use with audio applications.

It is used by some of the applications at https://github.com/Xangis for buttons,
knobs, and other GUI elements.

It is released under the terms of the MIT license.

# Building

This project depends on wxWidgets:

http://www.wxwidgets.org/

It also depends on RtMidi for the MIDI dialog:

http://www.music.mcgill.ca/~gary/rtmidi/

On Windows, use the Visual Studio project to build the library. You'll need to update
include paths for the wxWidgets and RtMidi libraries to match where they are on your
system.

On Linux, most projects just compile in the source files that they need.

# Development Status

I actively maintain this library because many of my applications depend on it.
