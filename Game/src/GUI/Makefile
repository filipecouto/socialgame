OBJ = Widget.o WidgetContainer.o LinearContainer.o TextWidget.o ButtonWidget.o TextBoxWidget.o Gui.o

GUI.a :	$(OBJ) IWidgetContainer.h
	ar rcs $@ $(OBJ)
	
clean :
	rm *.o