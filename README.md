FreeStroke
==========

Shortcuts with your body.
http://freestroke.fr

# What is this?

This is a gesture recognition project using the Kinect, written in C++. It is based on kinecgest project from http://github.com/fyhuang/kinectgest/

# Basic usage

After compiling FreeStroke and KController, run KController on a Windows environement after installing the Kinect SDK 1.6, then start FreeStroke.

# Compiling

- KController 

There are two version of the KController, one in C++ using a Win32 project and another in C#.

You must install the Kinect SDK 1.6 from Microsoft before compiling any KController project.

We used Visual Studio 2012 ultimate to compile the code.

- FreeStroke

You must install Qt 4.8 to compile the project.

If you're on Windows open the file FreeStroke/project/Win32 and setup the compile location on this directory.
If you're on OSX open the file FreeStroke/project/mac and setup the compile location on this directory.
If you're on Linux open the file FreeStroke/project/linux and setup the compile location on this directory.

# Running

There are three projects included: FreeStroke, and two versions of a controller.

FreeStroke can be run on Windows, OSX and Linux.

Both controller must be run on Windows because of the Kinect SDK.
