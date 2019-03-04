% 151044042  Elif Seyma ARMAGAN 


flight(istanbul, izmir, 3).
flight(istanbul, ankara, 5).
flight(istanbul, trabzon, 3).

flight(edirne, edremit, 5).

flight(edremit, edirne, 5).
flight(edremit, erzincan, 7).

flight(erzincan, edremit, 7).

flight(izmir, istanbul, 3).
flight(izmir, ankara, 6).
flight(izmir, antalya, 1).

flight(antalya, izmir, 1).
flight(antalya, diyarbakir, 5).

flight(trabzon, istanbul, 3).
flight(trabzon, ankara, 2).


flight(ankara, istanbul, 5).
flight(ankara, izmir, 6).
flight(ankara, konya, 8).
flight(ankara, trabzon, 2).

flight(konya, kars, 5).
flight(konya, ankara, 8).
flight(konya, diyarbakir, 1).

flight(diyarbakir, antalya, 5).
flight(diyarbakir, konya, 1).

flight(kars, konya, 5).
flight(kars,gaziantep, 3).

flight(gaziantep, kars, 3).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%% PART 1 %%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


flightPlan(X, Y, W, _) :- flight(X, Y, W).
flightPlan(X, Y, W, V) :- 
    	not(member(X, V)),
        flight(X, Z, W1),
        not(member(Z, V)),
        flightPlan(Z, Y, W2, [X|V]), X \== Y, W is W1 + W2.

route(X, Y, W) :-  flightPlan(X, Y, W, []).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%% PART 2 %%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


findLength(Start, Finish, Length, _) :-
	flight(Start, Finish, Length), !.
	
findLength(Start, Finish, Length, Visited) :-
    not(member(Start, Visited)),
	flight(Start, X, Y),
	findLength(X, Finish, Y1, [Start | Visited]),
	Length is Y + Y1.

findMin(Start, Finish, Length) :-
	findLength(Start, Finish, Length, []).

minl([Only], Only).
minl([Head|Tail], Minimum) :-
  minl(Tail, TailMin),
  Minimum is min(Head, TailMin).

croute(Start, Finish, Length) :- 
    findall(Length, findMin(Start, Finish, Length), Lengths),
    minl(Lengths, Min),
    Length is Min.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%% PART 3 %%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


when(a, 10).
when(b, 12).
when(c, 11).
when(d, 16).
when(e, 17).
when(f, 15).
when(g, 9).

where(a, 101).
where(b, 104).
where(c, 102).
where(d, 103).
where(e, 103).
where(f, 101).
where(g, 104).

enroll(1, a).
enroll(1, b).
enroll(2, a).
enroll(3, b).
enroll(4, c).
enroll(5, d).
enroll(6, d).
enroll(6, a).
enroll(7, f).
enroll(7, b).
enroll(8, a).
enroll(8, g).
enroll(9, b).
enroll(9, c).
enroll(10, g).
enroll(10, f).
enroll(11, d).
enroll(11, c).


% part 3.0  (schedule)


%eklenen sessionlar
  %-f ve g session i
  %f start time 15, g start time 9

%eklendikleri roomlar
  % f - 101 sinifinda
  % g - 104 sinifinda


%eklenen attendee ler
  %7,8,9,10,11  
  %7 F
  %7 B
  %8 A
  %8 G
  %9 B
  %9 C
  %10  G
  %10  F
  %11  D
  %11  C


% part 3.1  (schedule)

schedule(Student, Class, Time) :-
  enroll(Student, Temp),
  where(Temp, Class), 
  when(Temp, Time).


% part 3.2  (usage)

usage(Class, Time) :- 
  where(Temp, Class), 
  when(Temp, Time).


% part 3.3  (conflict)

timeConflict(Course1, Course2) :-
  when(Course1, Time1),
  when(Course2, Time2),
  Time1 == Time2.

classConflict(Course1, Course2) :- 
  where(Course1, Class1),
  where(Course2, Class2),
  Class1 == Class2.

conflict(Course1, Course2) :-
  not((not(classConflict(Course1, Course2)),
  not(timeConflict(Course1, Course2)))).


% part 3.4  (meet)

meet(Attandee1, Attandee2) :-
  enroll(Attandee1, Class1),
  where(Class1, Room1),
  enroll(Attandee2, Class2),
  where(Class2, Room2),
  Class1 == Class2,
  Room1 == Room2, 
  !.



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%% PART 4 %%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% part 4.1  (union)
% union([1,2,3,4],[1,a,b,4],A).

union([],Set, Set).

union([Set1 | Set2], Temp, Result) :- 
  member(Set1, Temp), 
  union(Set2, Temp, Result),
  !.

union([Set1 | Set2], Temp, [Set1 | Result]) :- \+ 
  member(Set1, Temp), 
  union(Set2, Temp, Result),
  !.


% part 4.2  (intersection)
% intersect([1,2,3,4],[1,a,b,4],A).


intersect([], _, []).

intersect([Set1 | Set2], Temp, [Set1 | Result]) :- 
  member(Set1, Temp), 
  intersect(Set2, Temp, Result),
  !.

intersect([Set1 | Set2], Temp, Result) :- 
  \+ member(Set1, Temp), 
  intersect(Set2, Temp, Result),
  !.


% part 4.3  (flatten)

myAppend([], List1, List1).
myAppend([Head | Rests], List1, [Head | List2]) :- 
  myAppend(Rests,List1,List2).


flatten([], []) :- !. 
flatten([Head | Rests], Flattened) :-
  !,  
  flatten(Head, TempHead),
  flatten(Rests, TempRest), 
  myAppend(TempHead, TempRest, Flattened).

flatten(Item, [Item]).