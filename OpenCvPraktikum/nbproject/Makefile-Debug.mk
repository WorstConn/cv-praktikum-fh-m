#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Test/ATest.o \
	${OBJECTDIR}/Helper/FileManager.o \
	${OBJECTDIR}/Modifier/ImageModificator.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/Control/RecorderCtl.o \
	${OBJECTDIR}/Test/WindowManagerTest.o \
	${OBJECTDIR}/Input/AInputHandler.o \
	${OBJECTDIR}/Modifier/HsvModifier.o \
	${OBJECTDIR}/Test/MainTest.o \
	${OBJECTDIR}/Test/Prak3A8.o \
	${OBJECTDIR}/View/WindowManager.o \
	${OBJECTDIR}/Modifier/ScaleModificator.o \
	${OBJECTDIR}/Output/VideoOutput.o \
	${OBJECTDIR}/CvVideoCapture.o \
	${OBJECTDIR}/Input/ImageSequenceInput.o \
	${OBJECTDIR}/Output/ImageListOutput.o \
	${OBJECTDIR}/Input/ImageInput.o \
	${OBJECTDIR}/Helper/CvHelper.o \
	${OBJECTDIR}/Output/Output.o \
	${OBJECTDIR}/View/AAction.o \
	${OBJECTDIR}/View/Window.o \
	${OBJECTDIR}/Input/InputHandler.o \
	${OBJECTDIR}/View/AImageAction.o \
	${OBJECTDIR}/Helper/MyMath.o \
	${OBJECTDIR}/Modifier/CompositeModificator.o \
	${OBJECTDIR}/Modifier/BgFgSegmModificator.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -std=gnu++0x -fPIC
CXXFLAGS=-m64 -std=gnu++0x -fPIC

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/lib -L/usr/lib -L/usr/lib/fakenect -L/usr/lib/X11 `pkg-config --libs opencv` `pkg-config --libs libfreenect` `pkg-config --libs gl` `pkg-config --libs glu` `pkg-config --libs x11`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/opencvpraktikum

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/opencvpraktikum: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/opencvpraktikum ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Test/ATest.o: Test/ATest.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/ATest.o Test/ATest.cpp

${OBJECTDIR}/Helper/FileManager.o: Helper/FileManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/FileManager.o Helper/FileManager.cpp

${OBJECTDIR}/Modifier/ImageModificator.o: Modifier/ImageModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/ImageModificator.o Modifier/ImageModificator.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/Control/RecorderCtl.o: Control/RecorderCtl.cpp 
	${MKDIR} -p ${OBJECTDIR}/Control
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Control/RecorderCtl.o Control/RecorderCtl.cpp

${OBJECTDIR}/Test/WindowManagerTest.o: Test/WindowManagerTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/WindowManagerTest.o Test/WindowManagerTest.cpp

${OBJECTDIR}/Input/AInputHandler.o: Input/AInputHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/Input
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input/AInputHandler.o Input/AInputHandler.cpp

${OBJECTDIR}/Modifier/HsvModifier.o: Modifier/HsvModifier.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/HsvModifier.o Modifier/HsvModifier.cpp

${OBJECTDIR}/Test/MainTest.o: Test/MainTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/MainTest.o Test/MainTest.cpp

${OBJECTDIR}/Test/Prak3A8.o: Test/Prak3A8.cpp 
	${MKDIR} -p ${OBJECTDIR}/Test
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Test/Prak3A8.o Test/Prak3A8.cpp

${OBJECTDIR}/View/WindowManager.o: View/WindowManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/View
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/View/WindowManager.o View/WindowManager.cpp

${OBJECTDIR}/Modifier/ScaleModificator.o: Modifier/ScaleModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/ScaleModificator.o Modifier/ScaleModificator.cpp

${OBJECTDIR}/Output/VideoOutput.o: Output/VideoOutput.cpp 
	${MKDIR} -p ${OBJECTDIR}/Output
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Output/VideoOutput.o Output/VideoOutput.cpp

${OBJECTDIR}/CvVideoCapture.o: CvVideoCapture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/CvVideoCapture.o CvVideoCapture.cpp

${OBJECTDIR}/Input/ImageSequenceInput.o: Input/ImageSequenceInput.cpp 
	${MKDIR} -p ${OBJECTDIR}/Input
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input/ImageSequenceInput.o Input/ImageSequenceInput.cpp

${OBJECTDIR}/Output/ImageListOutput.o: Output/ImageListOutput.cpp 
	${MKDIR} -p ${OBJECTDIR}/Output
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Output/ImageListOutput.o Output/ImageListOutput.cpp

${OBJECTDIR}/Input/ImageInput.o: Input/ImageInput.cpp 
	${MKDIR} -p ${OBJECTDIR}/Input
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input/ImageInput.o Input/ImageInput.cpp

${OBJECTDIR}/Helper/CvHelper.o: Helper/CvHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/CvHelper.o Helper/CvHelper.cpp

${OBJECTDIR}/Output/Output.o: Output/Output.cpp 
	${MKDIR} -p ${OBJECTDIR}/Output
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Output/Output.o Output/Output.cpp

${OBJECTDIR}/View/AAction.o: View/AAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/View
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/View/AAction.o View/AAction.cpp

${OBJECTDIR}/View/Window.o: View/Window.cpp 
	${MKDIR} -p ${OBJECTDIR}/View
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/View/Window.o View/Window.cpp

${OBJECTDIR}/Input/InputHandler.o: Input/InputHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/Input
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input/InputHandler.o Input/InputHandler.cpp

${OBJECTDIR}/View/AImageAction.o: View/AImageAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/View
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/View/AImageAction.o View/AImageAction.cpp

${OBJECTDIR}/Helper/MyMath.o: Helper/MyMath.cpp 
	${MKDIR} -p ${OBJECTDIR}/Helper
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helper/MyMath.o Helper/MyMath.cpp

${OBJECTDIR}/Modifier/CompositeModificator.o: Modifier/CompositeModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/CompositeModificator.o Modifier/CompositeModificator.cpp

${OBJECTDIR}/Modifier/BgFgSegmModificator.o: Modifier/BgFgSegmModificator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Modifier
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DTRY_KINECT -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/libfreenect -I/usr/include/GL -I/usr/include/libusb-1.0 -I/usr/include/X11 `pkg-config --cflags opencv` `pkg-config --cflags libfreenect` `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags x11`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/Modifier/BgFgSegmModificator.o Modifier/BgFgSegmModificator.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/opencvpraktikum

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
