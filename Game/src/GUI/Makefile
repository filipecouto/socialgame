OBJ = Widget.o WidgetContainer.o Window.o LinearContainer.o TextWidget.o ButtonWidget.o TextBoxWidget.o Gui.o

GUI.a :	$(OBJ) IWidgetContainer.h
	ar rcs $@ $(OBJ)
	
obj/%.o : %.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<
	
clean :
	rm *.o