:- use_module('solver.pl').
:- include('TestFormulas.pl').

sat(FormulaName,Assignment) :-
    call(FormulaName,Formula),
    solve(Formula,Assignment),!.
