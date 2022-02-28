:- module( solver, %module solver and its corresponding predicates
    [ emptyFormula/1,
    assign/4,
    hasVariables/2,
    formulaReduce/2,
    emptyFormula/1,
    deleteFromList/3,
    solve/2,
    h_remove/2,
    removeSign/2
    ]
    ).


%Calls the formula reduce relation, F is a formula and N is the list of variables 
%where calling assign on all of them reduces the formula to an empty list.
solve(F,N):- formulaReduce(F, N).


%given a formula and a variable, removes the negation of the variable
%from every term, and removes every term that has said variable.
formulaReduce([], []).
formulaReduce(F, N):- hasVariables(F, [H|T]), assign(H, true, F, RF),  N = [+H|NV], formulaReduce(RF, NV).
formulaReduce(F, N):- hasVariables(F, [H|T]), assign(H, false, F, RF),  N = [-H|NV], formulaReduce(RF, NV).
emptyFormula([]).


%Given a formula, finds a list of variables that would solve the function, 
%using assign to remove terms until the formula is empty.
%Recursive details: 
%base case is when the list is empty, 
%and it does true/false until it finds a case where assign gives an empty list.
assign(_,_,[],[]).
assign(X,Y,L, R):- Y == true -> deleteFromList((-X), L, L2), exclude(member(+X), L2, R).
assign(X,Y,L, R):- Y == false -> deleteFromList((+X), L, L2), exclude(member(-X), L2, R). 


%Given a list, removes a single literal with a -sign from a term. 
%ex: [[+a,+b,-c]] -> [[+a,+b]]
deleteFromList(_, [], []).
deleteFromList(X, [H|T], R):- delete(H, X, H2), member(_,H2), R = [H2 | NT], deleteFromList(X, T, NT). 
 
%Given a list of lists, returns a single list containing all unique elements._
%ex: [[+a,+b,+c]] -> [a,b,c]
%Recursive details: Recurses to the end of the list before repetitively 
%removing the sign and appending the list element to the new list, before 
%performing a sort inorder to remove duplicate items.
hasVariables([], []).       
hasVariables([H|T], Vars) :- hasVariables(T, RT), removeSign(H,HR), append(RT, HR, UV), sort(UV, Vars).

%Given a list of veriables, returns a new list where each element has no sign.
removeSign([],[]).
removeSign([H|T],[X|Y]) :- h_remove(H,X), removeSign(T,Y).

%Removes the signs from a compound statment +a -> a
h_remove(X,Y):- term_to_atom(X,Atom), sub_atom(Atom,1,1,LengthAfter,Y).