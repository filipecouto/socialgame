row([R|_], 0, R).
row([_|M], I, R):- I2 is I-1, row(M, I2, R).

cell(M, (X, Y), R):- row(M, Y, R2), row(R2, X, R).

solve(_, (X, Y), (X, Y), [], _).
solve(M, (XF, YF), (XA, YA), Path, Walked):-
								up(M, (XF, YF), (XA, YA), Path, [(XA,YA)|Walked]);
								right(M, (XF, YF), (XA, YA), Path, [(XA,YA)|Walked]);
								down(M, (XF, YF), (XA, YA), Path, [(XA,YA)|Walked]);
								left(M, (XF, YF), (XA, YA), Path, [(XA,YA)|Walked]).

test(M, (XF, YF), (X, Y), [(X,Y)|Path], Walked):-
								cell(M, (X, Y), C),
								C=0,
								not(member((X,Y), Walked)),
								solve(M, (XF, YF), (X, Y), Path, Walked).

left(M, (XF, YF), (XA, YA), Path, Walked):-
							X is XA-1,
							test(M, (XF, YF), (X, YA), Path, Walked).
right(M, (XF, YF), (XA, YA), Path, Walked):-
							X is XA+1,
							test(M, (XF, YF), (X, YA), Path, Walked).
up(M, (XF, YF), (XA, YA), Path, Walked):-
							Y is YA-1,
							test(M, (XF, YF), (XA, Y), Path, Walked).
down(M, (XF, YF), (XA, YA), Path, Walked):-
							Y is YA+1,
							test(M, (XF, YF), (XA, Y), Path, Walked).