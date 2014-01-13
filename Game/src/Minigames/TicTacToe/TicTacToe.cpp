#if _WIN32
#define GL_GLEXT_PROTOTYPES
#include <GL\glew.h>
#include <GL\glext.h>
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "glew32s.lib")
#endif
#include "TicTacToe.h"
#include "../../GameContext.h"

TicTacToeMinigame::TicTacToeMinigame(GameContext * context) : _context(context) {
	
}

std::string TicTacToeMinigame::getName() {
	return "Tic Tac Toe";
}

IMinigameInstance * TicTacToeMinigame::newGame() {
	return new TicTacToeInstance(_context);
}

void TicTacToeMinigame::TicTacToeInstance::draw() {
	camera.setUp();

	//PLANO DE BAIXO
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId1);
	glBegin(GL_QUADS);
		glTexCoord2f(1, 0);
		glVertex3i(-20, 0, 20);
		glTexCoord2f(0, 0);
		glVertex3i(20, 0, 20);
		glTexCoord2f(0, 1);
		glVertex3i(20, 0, -20);
		glTexCoord2f(1, 1);
		glVertex3i(-20, 0, -20);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
		glPushMatrix();
			//Right External Line
			drawLine();
		glPopMatrix();
		glPushMatrix();
			//Left External Line
			glTranslatef(9.8, 0, 0);
			drawLine();
		glPopMatrix();
		glPushMatrix();
			//Right Internal Line
			glTranslatef(3.3, 0, 0);
			drawLine();
		glPopMatrix();
		glPushMatrix();
			//Left Internal Line
			glTranslatef(6.7, 0, 0);
			drawLine();
		glPopMatrix();

		glPushMatrix();
			//Upper External Line
			glTranslatef(5, 14.8, 0);
			glRotatef(90, 0.0, 0.0, 1.0);
			drawLine(0.1);
		glPopMatrix();
		glPushMatrix();
			//Lower External Line
			glTranslatef(5, 5, 0);
			glRotatef(90, 0.0, 0.0, 1.0);
			drawLine(0.1);
		glPopMatrix();
		glPushMatrix();
			//Lower Internal Line
			glTranslatef(5, 5 + 3.3, 0);
			glRotatef(90, 0.0, 0.0, 1.0);
			drawLine(0.1);
		glPopMatrix();
		glPushMatrix();
			//Upper Internal Line
			glTranslatef(5, 5 + 6.7, 0);
			glRotatef(90, 0.0, 0.0, 1.0);
			drawLine(0.1);
		glPopMatrix();

		glPushMatrix();
			//Base
			glColor3f(0.3, 0.3, 0.3);
			glBegin(GL_QUADS);
			glVertex3i(-5, 0, -15);
			glVertex3i(-5, 10, -15);
			glVertex3i(5, 10, -15);
			glVertex3i(5, 0, -15);
			glEnd();
		glPopMatrix();
	glPopMatrix();
	
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			switch(matriz[i][j]) {
				case 'x':
					drawX(i,j);
					break;
				case 'o':
					drawO(i,j);
					break;
			}
		}
	}
	
	_gui->drawGui();
}

void TicTacToeMinigame::TicTacToeInstance::drawLine(GLfloat addZ){
	glColor3f(0.5, 0.1, 0.8);
	glBegin(GL_QUADS);
		glVertex3f(-5, 0, -15 - addZ);
		glVertex3f(-5, 10, -15 - addZ);
		glVertex3f(-4.8, 10, -15 - addZ);
		glVertex3f(-4.8, 0, -15 - addZ);
	glEnd();
}

void TicTacToeMinigame::TicTacToeInstance::drawX(int x, int y){
	glPushMatrix();
		glTranslatef(3.3 - (x * 3.3), 8.3 - (y * 3.3), -15.2);
		drawXLine(45);
		drawXLine(-90);
	glPopMatrix();
}

void TicTacToeMinigame::TicTacToeInstance::drawXLine(GLfloat ang){
	glColor3f(0.8, 0.6, 0.3);
	glRotatef(ang, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex3f(-0.25, 1, 0);
		glVertex3f(0.25, 1, 0);
		glVertex3f(0.25, -1, 0);
		glVertex3f(-0.25, -1, 0);
	glEnd();
}

void TicTacToeMinigame::TicTacToeInstance::drawO(int x, int y){
	glPushMatrix();
		glTranslatef(3.3 - (x * 3.3), 8.3 - (y * 3.3), -15.4);
		glColor3f(0.3, 0.3, 0.3);
		drawCircle(0.5);
		glTranslatef(0.0, 0.0, 0.2);
		glColor3f(0.3, 0.6, 0.8);
		drawCircle(1);
	glPopMatrix();
	
}

void TicTacToeMinigame::TicTacToeInstance::drawCircle(GLfloat radius){
	GLint numbSides = 100;
	GLfloat ang = 2 * M_PI / numbSides;
	GLint i;
	glBegin(GL_POLYGON);
		for(i=0; i<numbSides; i++) {
			glVertex3f(-radius * cos(i*ang),radius*sin(i*ang),0.0);
		}
	glEnd();
}

void TicTacToeMinigame::TicTacToeInstance::start() {
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			matriz[i][j] = 'z';
		}
	}
	mx = -17;
	my = 19;
	thing.x = thing.y = thing.vx = thing.vy = 0;
	camera.moveTo(0, 8, -28);
	camera.lookAt(0, 0, 0);
	textureId1 = _context->loadTexture("tictactoe_texture.jpg");
}

void TicTacToeMinigame::TicTacToeInstance::tick(int delta, int current) {
	camera.tick(delta, current);

	_gui->tick(delta,current);
	_gui->setDimensions(getViewportWidth(),getViewportHeight());
}

TicTacToeMinigame::TicTacToeInstance::TicTacToeInstance(GameContext * context) : _context(context) {
	for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++){
		keys[i] = false;
	}
	
	startNewGame();
	
	_gui = new Gui();
	_gui->setEventsListener(this);
}

void TicTacToeMinigame::TicTacToeInstance::finish() {
	_context->notifyMinigameFinished(this);
}

void TicTacToeMinigame::TicTacToeInstance::onKeyDown(int key, int special) {
	switch (key) {
		case 'w':
			keys[0] = true;
			break;

		case 'a':
			keys[1] = true;
			break;

		case 's':
			keys[2] = true;
			break;

		case 'd':
			keys[3] = true;
			break;
	}
}

void TicTacToeMinigame::TicTacToeInstance::onKeyUp(int key, int special) {
	switch (key) {
		case 'w':
			keys[0] = false;
			break;

		case 'a':
			keys[1] = false;
			break;

		case 's':
			keys[2] = false;
			break;

		case 'd':
			keys[3] = false;
			break;
	}
}

void TicTacToeMinigame::TicTacToeInstance::startNewGame(){
	//Communication
	string list = convertMatrizToPrologList();
	string resultJson = curl_httpget(server + "?Theme=TicTacToe&Function=First");
	cout << resultJson <<endl;
	rapidjson::Document d;
	d.Parse<0>(resultJson.c_str());
	string result = d["data"].GetString();
	//End of Communication
	
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			matriz[i][j]='z';
		}
	}
	
	ableToPlay = true;
	
	if(result == "2"){
		Game(convertMatrizToPrologList());
	}
}

bool TicTacToeMinigame::TicTacToeInstance::checkMatriz(int x, int y) {
	if(matriz[x][y] == 'z') return true;
	return false;
}

string TicTacToeMinigame::TicTacToeInstance::convertMatrizToPrologList(){
	return string("[")+matriz[0][0]+","+matriz[1][0]+","+matriz[2][0]+
		","+matriz[0][1]+","+matriz[1][1]+","+matriz[2][1]+
		","+matriz[0][2]+","+matriz[1][2]+","+matriz[2][2]+"]";
}

void TicTacToeMinigame::TicTacToeInstance::Game(string list){
	//Communication
	string resultJson = curl_httpget(server + "?Theme=TicTacToe&Function=Game&Params="+list);
	cout << resultJson <<endl;
	rapidjson::Document d;
	d.Parse<0>(resultJson.c_str());
	string result = d["data"].GetString();
	//End of Communication
	
	if(result == "x"){ //Player won
		endGame("Congratulations, you won!", true);
	}
	else if(result == "o"){ //Computer won
		endGame("Ohh, better luck next time :)", false);
	}
	else{
		int value = atoi(result.c_str());
		if(value == 0){ //Draw
			endGame("Give it another try, you're almost there =)", false);
		}
		else{ //Computer will play
			int positions[9][2] = { {0,0}, {1,0}, {2,0}, {0,1}, {1,1}, {2,1}, {0,2}, {1,2}, {2,2} };
			int x = positions[value-1][0];
			int y = positions[value-1][1];
			if(checkMatriz(x,y)){
				matriz[x][y] = 'o';
				
				//Communication
				resultJson = curl_httpget(server + "?Theme=TicTacToe&Function=Game&Params="+convertMatrizToPrologList());
				d.Parse<0>(resultJson.c_str());
				result = d["data"].GetString();
				//End of Communication
				
				if(result == "o"){ //Computer Won
					endGame("Ohh, better luck next time :)", false);
				}
				else if(result == "0"){ //Draw
					endGame("Give it another try, you're almost there =)", false);
				}
			}
		}
	}
}

void TicTacToeMinigame::TicTacToeInstance::endGame(string message, bool win){
	ableToPlay = false;
	Dialog * d = NULL;
	if(win){
		d = _gui->showMessage("endGameWithWin",message);
	}
	else {
		d = _gui->showYesNoCancelMessage("endGameWithLossOrDraw",message,"Restart","Finish","Cancel");
	}
}

bool TicTacToeMinigame::TicTacToeInstance::onDialogResult(Dialog * dialog, int buttonId) {
	dialog->hide();
	if (dialog->getId() == "endGameWithLossOrDraw") {
		switch (buttonId) {
			case Dialog::DIALOG_BUTTON_ID_POSITIVE:
				startNewGame();
				break;

			case Dialog::DIALOG_BUTTON_ID_NEGATIVE:
				finish();
				break;

			case Dialog::DIALOG_BUTTON_ID_NEUTRAL:
				finish();
				break;
		}
	}
	else if(dialog->getId() == "endGameWithWin") {
		if (buttonId == Dialog::DIALOG_BUTTON_ID_OK) {
			finish();
		}
	}

	return true;
}

bool TicTacToeMinigame::TicTacToeInstance::onWidgetClicked(Widget* widget)
{
	return true;
}


void TicTacToeMinigame::TicTacToeInstance::onMouseButton(int state, int button, int x, int y) {
	if (state == 0) {
		if (_gui->onMouseButtonDown(button, x, getViewportHeight()-y)) return;
	} else if (state == 1) {
		if (_gui->onMouseButtonUp(button, x, getViewportHeight()-y)) return;
	}
	int x1 = -1, y1 = -1;
	if (state == 1 && button==GLUT_LEFT_BUTTON && ableToPlay){
		if (mx >= 2.6 && mx <= 6.75 &&
			my >= 6 && my <= 13.3){
			printf("<-----------1---------->");
			x1 = 0; y1 = 0;
		}

		else if (mx >= -2.0 && mx <= 2.3 &&
			my >= 6 && my <= 13.3){
			printf("<-----------2---------->");
			x1 = 1; y1 = 0;
		}

		else if (mx >= -6.75 && mx <= -2.3 &&
			my >= 6 && my <= 13.3){
			printf("<-----------3---------->");
			x1 = 2; y1 = 0;
		}

		else if (mx >= 2.4 && mx <= 6.0 &&
			my >= -1.6 && my <= 5.4){
			printf("<-----------4---------->");
			x1 = 0; y1 = 1;
		}

		else if (mx >= -1.8 && mx <= 2.1 &&
			my >= -1.6 && my <= 5.4){
			printf("<-----------5---------->");
			x1 = 1; y1 = 1;
		}

		else if (mx >= -6.0 && mx <= -2.1 &&
			my >= -1.6 && my <= 5.4){
			printf("<-----------6---------->");
			x1 = 2; y1 = 1;
		}

		else if (mx >= 2.2 && mx <= 6.0 &&
			my >= -8.0 && my <= -2.1){
			printf("<-----------7---------->");
			x1 = 0; y1 = 2;
		}

		else if (mx >= -1.7 && mx <= 2.0 &&
			my >= -8.0 && my <= -2.1){
			printf("<-----------8---------->");
			x1 = 1; y1 = 2;
		}

		else if (mx >= -5.6 && mx <= -2.0 &&
			my >= -8.0 && my <= -2.1){
			printf("<-----------9---------->");
			x1 = 2; y1 = 2;
		}

		//printf("%f %f\n", mx, my);
		if(x1 != -1 && y1 != -1){
		      if(checkMatriz(x1,y1)){
			matriz[x1][y1] = 'x';			
			string list = convertMatrizToPrologList();
			Game(list);
		      }
		}
	}	
}

void TicTacToeMinigame::TicTacToeInstance::onMouseMove(int x, int y) {
	_gui->onMouseMove(x,y);
	mx = (GLfloat)x / getViewportWidth() * -40 + 20;
	my = (GLfloat)y / getViewportHeight() * -40 + 20;
}

TicTacToeMinigame::TicTacToeInstance::~TicTacToeInstance() {

}
