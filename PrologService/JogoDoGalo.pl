line([1, 2, 3]).
line([4, 5, 6]).
line([7, 8, 9]).

line([1, 4, 7]).
line([2, 5, 8]).
line([3, 6, 9]).

line([1, 5, 9]).
line([3, 5, 7]).

player(1,x).
player(2,o).

getSymbol(Player,Symbol):-player(Player,Symbol).

symbolExists(Symbol,Pos,Game):-
	nth1(Pos,Game,Aux),
	Aux==Symbol.

win(Game,Player):-
	getSymbol(Player,Symbol),
	line([Pos1,Pos2,Pos3]),
	symbolExists(Symbol,Pos1,Game),
	symbolExists(Symbol,Pos2,Game),
	symbolExists(Symbol,Pos3,Game),
	!.

move([z,B,C,D,E,F,G,H,I],Symbol,[Symbol,B,C,D,E,F,G,H,I],1).
move([A,z,C,D,E,F,G,H,I],Symbol,[A,Symbol,C,D,E,F,G,H,I],2).
move([A,B,z,D,E,F,G,H,I],Symbol,[A,B,Symbol,D,E,F,G,H,I],3).
move([A,B,C,z,E,F,G,H,I],Symbol,[A,B,C,Symbol,E,F,G,H,I],4).
move([A,B,C,D,z,F,G,H,I],Symbol,[A,B,C,D,Symbol,F,G,H,I],5).
move([A,B,C,D,E,z,G,H,I],Symbol,[A,B,C,D,E,Symbol,G,H,I],6).
move([A,B,C,D,E,F,z,H,I],Symbol,[A,B,C,D,E,F,Symbol,H,I],7).
move([A,B,C,D,E,F,G,z,I],Symbol,[A,B,C,D,E,F,G,Symbol,I],8).
move([A,B,C,D,E,F,G,H,z],Symbol,[A,B,C,D,E,F,G,H,Symbol],9).

willItWin(Game):-
	move(Game,x,GameAux,_),
	player(Player,x),
	win(GameAux,Player).

computerNextMove(Game,Pos):-
	move(Game,o,GameAux,Pos),
	player(Player,o),
	win(GameAux,Player),!.

computerNextMove(Game,Pos):-
	move(Game,o,GameAux,Pos),
	not(willItWin(GameAux)),!.

computerNextMove(Game,Pos):-
	move(Game,o,_,Pos).

computerNextMove(Game,Pos):-
	not(member(z,Game)),!,
	Pos=0.
