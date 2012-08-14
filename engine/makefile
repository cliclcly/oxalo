OBJECTS = eEngineClass.o eAbstractKeyboardHandler.o eAbstractObject.o \
			eCamera.o eObjectHandler.o eMessage.o ePolygon.o \
			eAttribute.o eDebug.o eComponent.o ePlayer.o eTerrainChunk.o \
			ePlatform.o genericEnemy.o eAIs.o eAnimationObject.o eXMLParser.o \
			eTextObject.o
DEVIL = c:\\devIL\\lib\\devIL.lib \
		c:\\devIL\\lib\\ILU.lib \
		c:\\devIL\\lib\\ILUT.lib
OPENGL = -lopengl32 -lglu32 C:\\minGw\\lib\\glut32.lib
			
CXX = g++
CXXFLAGS = -Ic:\\devIL\\include

engine : $(OBJECTS)
	g++ -Wl,--enable-auto-import -shared -o ../libengine.dll $(OBJECTS)  $(OPENGL) $(DEVIL)
	
$(OBJECTS) : %.o: %.cpp %.h
	$(CXX) -c $(CXXFLAGS) $< -o $@
			
.PHONY : clean
clean :
	del $(OBJECTS)