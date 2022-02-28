#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//A literal is any singleton term, such as an X or Y'
struct literal
{
    bool truth;
    literal *next = NULL; //points to the next literal
    char symbol;
};

//Contains a list of literals.
struct term
{
    literal *head = NULL; //a linked list of literals.
    term *next = NULL;    //points to its next term
    bool truth;           //entire term has a truth value
};

typedef literal *literal_ptr; //Ease of use for literal and term typed pointers
typedef term *term_ptr;

const int ASCII_A = 97;
const int ASCII_Z = 122;

void insert_tail(literal_ptr &head, literal new_literal);
void end_navigator(literal_ptr head, literal_ptr &current); //Functions for the literal linked list
bool contains(literal_ptr head, literal new_literal);

void insert_tail(term_ptr &head, term new_term);
void end_navigator(term_ptr head, term_ptr &current); //Functions for the term linked list
bool contains(term_ptr head);

bool open_file(literal_ptr &literal_list, term_ptr &expression); //opens the file

bool get_solutions(term_ptr, literal_ptr &, literal_ptr &);
void restoreTruth(term_ptr&, term_ptr&);

literal_ptr remove_tail(literal_ptr &head);
literal_ptr get_literals(term_ptr &);
bool charInArray(char, char[]);

bool evaluate(term_ptr expression, literal_ptr& solutionList);

void allFalse(term_ptr &);
void print_solution(literal_ptr &);
void add_tail(literal_ptr &literalList, literal_ptr &add);

void swap(literal_ptr &t1, literal_ptr &t2);
void sort(literal_ptr &head);


#endif