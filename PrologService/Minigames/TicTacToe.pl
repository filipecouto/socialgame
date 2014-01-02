% Possible Winning States
line([1, 2, 3]).
line([4, 5, 6]).
line([7, 8, 9]).

line([1, 4, 7]).
line([2, 5, 8]).
line([3, 6, 9]).

line([1, 5, 9]).
line([3, 5, 7]).

% Checks if a player is in a certain position
isPlayerInPosition(Player,Pos,Game):-
	nth1(Pos,Game,Aux),
	Aux==Player.

% Tests all the possibilities to see if the player is the winner
win(Game,Player):-
	line([Pos1,Pos2,Pos3]),
	isPlayerInPosition(Player,Pos1,Game),
	isPlayerInPosition(Player,Pos2,Game),
	isPlayerInPosition(Player,Pos3,Game),
	!.

% All the possible moves for the computer
move([z,B,C,D,E,F,G,H,I],Symbol,[Symbol,B,C,D,E,F,G,H,I],1).
move([A,z,C,D,E,F,G,H,I],Symbol,[A,Symbol,C,D,E,F,G,H,I],2).
move([A,B,z,D,E,F,G,H,I],Symbol,[A,B,Symbol,D,E,F,G,H,I],3).
move([A,B,C,z,E,F,G,H,I],Symbol,[A,B,C,Symbol,E,F,G,H,I],4).
move([A,B,C,D,z,F,G,H,I],Symbol,[A,B,C,D,Symbol,F,G,H,I],5).
move([A,B,C,D,E,z,G,H,I],Symbol,[A,B,C,D,E,Symbol,G,H,I],6).
move([A,B,C,D,E,F,z,H,I],Symbol,[A,B,C,D,E,F,Symbol,H,I],7).
move([A,B,C,D,E,F,G,z,I],Symbol,[A,B,C,D,E,F,G,Symbol,I],8).
move([A,B,C,D,E,F,G,H,z],Symbol,[A,B,C,D,E,F,G,H,Symbol],9).

% Checks if the player will win if a move is made
willPlayerWin(Game):-
	move(Game,x,GameAux,_),
	win(GameAux,x).

% All the testing possibilities for the computer move
% Computer is the first playing
computerNextMove([z,z,z,z,z,z,z,z,z],Pos):-
	P is random(9),
	Pos is P+1,!.

% Moves to a place where it can immediately win
computerNextMove(Game,Pos):-
	move(Game,o,GameAux,Pos),
	win(GameAux,o),!.

% Moves to a place where the player isn't going to win in the next round
computerNextMove(Game,Pos):-
	move(Game,o,GameAux,Pos),
	not(willPlayerWin(GameAux)),!.

% Moves to any free place
computerNextMove(Game,Pos):-
	move(Game,o,_,Pos).

% If there's no free place, calls it a draw
computerNextMove(Game,Pos):-
	not(member(z,Game)),!,
	Pos=0.

% The is the only predicate to be called from the outside
% as the Return will have either the winners (x or o) or
% the computer next move (1 .. 9) or
% a draw (0).
tictactoe(Game,Return):-
	win(Game,x),!,Return=x;
	win(Game,o),!,Return=o;
	computerNextMove(Game,Return).

% Tells who's going to play first
whoIsFirst(Return):-
	R is random(2),
	Return is R+1.
