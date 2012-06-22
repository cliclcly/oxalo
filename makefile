OBJECTS = main.o
			
DEVIL = c:\\devIL\\lib\\devIL.lib \
		c:\\devIL\\lib\\ILU.lib \
		c:\\devIL\\lib\\ILUT.lib
OPENGL = -lopengl32 -lglu32 C:\\minGw\\lib\\glut32.lib
ENGINE = libengine.dll

CXX = g++
CXXFLAGS = -Ic:\\devIL\\include


cube : engine $(OBJECTS)
	cd engine && $(MAKE)
	g++ -enable-auto-import -Wall -o oxalo.exe $(OBJECTS) $(ENGINE) -lm $(OPENGL)
	
engine :
	cd engine && $(MAKE)
	
.PHONY : clean
clean :
	cd engine && make clean
	del $(OBJECTS)
	del oxalo.exe