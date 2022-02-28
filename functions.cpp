#include "header.h"

//------------------------------------------------------------
// function name: sort
//
// Purpose: sorts a literal linked list alphabetically
//
// Inputs:  The array to be sorted
//
// Output:  The sorted array
//
// Description: Sorts the given linked list of literals into alphabetical order
//via a simple selection sort. The sort works by maintaining 2 pointers, both starting at the head
//The first traverses the list, swapping with the second each time nessisary. After a pass, the first
//pointer restarts at the front of the list, and the second pointer traverses an element, until the
//second pointer has traversed the entire list.
//------------------------------------------------------------
void sort(literal_ptr &head)
{

    int conversion1;
    int conversion2;
    char symb1;
    char symb2;
    literal_ptr first = head;
    literal_ptr second = head;

    while (second != NULL)
    {
        while (first != NULL)
        {

            symb1 = first->symbol; //extracts symbols so that they can be compared
            symb2 = second->symbol;
            conversion1 = (int)symb1;
            conversion2 = (int)symb2;

            if (conversion2 < conversion1) //Swaps the nodes if out of order
                swap(first, second);

            first = first->next; //Traverses to the next element
        }

        second = second->next;
        first = head;
    }

    return;
}

//------------------------------------------------------------
// function name: swap
//
// Purpose: swaps the contents of two pointers
//
// Inputs:  two pointers
//
//------------------------------------------------------------
void swap(literal_ptr &t1, literal_ptr &t2)
{

    char temp;
    temp = t1->symbol;

    t1->symbol = t2->symbol; //swaps the symbols of the two nodes
    t2->symbol = temp;

    bool temp_truth = t1->truth;

    t1->truth = t2->truth; //swaps the truth values of the two nodes
    t2->truth = temp_truth;

    return;
}

//------------------------------------------------------------
// function name: insert_tail
//
// Purpose: Adds a new literal to a linked list of literals
//
// Inputs:  The head of a linked list, and the new node to be added
//
// Output:  The head of the linked list, containing the new element
//          at the end of the list
//------------------------------------------------------------
void insert_tail(literal_ptr &head, literal new_literal)
{

    literal_ptr temp = new literal; //the new node to be inserted
    literal_ptr current = NULL;     //used to traverse the linked list

    if (head == NULL) //Case: list is empty, enter at head
    {
        head = temp;
        temp->next = NULL;
    }

    else
    {
        current = head;
        end_navigator(head, current); //sets a pointer to end of list
        current->next = temp;         //new literal made, and set to
        new_literal.next = NULL;
        temp->next = NULL;
    }

    temp->symbol = new_literal.symbol; //Insert values into the new node
    temp->truth = new_literal.truth;

    return;
}

//------------------------------------------------------------
// function name: end_navigator
//
// Purpose: sets a pointer to the end of a linked list of literals.
//
// Inputs:  The linked list and a pointer to be inserted.
//
// Output:  a pointer moved to the end of the list.
//------------------------------------------------------------
void end_navigator(literal_ptr head, literal_ptr &current)
{

    if (head->next != NULL)
        end_navigator(head->next, current); //traverse to the end

    else
        current = head; //case list is a singleton (pointer not moved)

    return;
}

//------------------------------------------------------------
// function name: contains
//
// Purpose: checks if a literal linked list already contains a given literal.
//
// Inputs:  The array to be checked
//
// Output:  true or false, for if the item was found
//------------------------------------------------------------
bool contains(literal_ptr head, literal new_literal)
{

    literal_ptr current = head;

    while (current != NULL)
    {
        if (current->symbol == new_literal.symbol) //checks each node for the duplicate
            return true;                           //returns true if a duplicate is found

        current = current->next;
    }

    return false;
}

//-----------------------------------------------------------------
//
//      The following functions are overloaded versions of the above
//      Functions, which manipulate linked lists of TERM elementes
//------------------------------------------------------------------
void insert_tail(term_ptr &head, term new_term)
{

    term_ptr temp = new term;
    term_ptr current = NULL;

    if (head == NULL)
    {

        //if list is empty, inserts at head.
        head = temp;
        temp->next = NULL;
    }

    else
    {
        current = head;
        end_navigator(head, current); //sets a pointer to end of list
        current->next = temp;         //new term made, and set to
        new_term.next = NULL;
        temp->next = NULL; //point to NULL
    }
    temp->head = new_term.head;

    return;
}

void end_navigator(term_ptr head, term_ptr &current)
{

    if (head->next != NULL)
        end_navigator(head->next, current);

    else
        current = head;

    return;
}

//-----------------------------------------------------------------
//
//      The following functions are overloaded versions of the above
//      Functions, which manipulate linked lists of TERM elementes
//------------------------------------------------------------------
/*
Name: open_file
     Reads contents of file and places them into linked list structures
     of literals and terms. File name based on user input. If error in file occurs
     returns error and program terminates.

    @param literal_list List of all the literals read from input
            expression: List of all terms
*/
bool open_file(literal_ptr &literal_list, term_ptr &expression)
{

    bool error = false; //sentinel for error in file
    int conversion;     //converting chars to ints
    char input;
    int literal_counter = 0; //Max 3 literals per term
    string file_name;

    ifstream my_file;
    cout << "enter the name of your file: ";
    cin >> file_name;
	
    my_file.open(file_name); //opening file name specified by user
    

    if (my_file.fail())
      {

	  cout << "could not open file" << endl;
	      error = true;
	 }

    else
    {
        my_file >> input; //expecting for first char to be (
        while (!my_file.eof() && error == false)
        {

            term new_term;
            literal_counter = 0;
            while (literal_counter < 3 && error == false) //do it 3 times, on the third time look for a closing bracket instead.
            {

                if (input != '(' && literal_counter == 0)
                {
                    cout << "Error, missing ( for an expression" << endl;
                    error = true;
                }
                else
                {
                    my_file >> input; //read a valid literal

                    literal new_literal; //creating a new literal instance
                    new_literal.symbol = input;

                    conversion = (int)input; //converting input from char to int

                    if (conversion < ASCII_A || ASCII_Z < conversion) //ascii value of character is not in range from a-z
                    {
                        cout << "Invalid formula";
                        error = true; //invalid literal
                    }

                    else
                    {
                        literal_counter++;
                        my_file >> input; //Expecting a + or ) if the last literal has been read

                        if (literal_counter == 3)
                        {
                            if (input == '\'')
                            {
                                my_file >> input; //Case 1: last literal is negated, expecting ) after
                                if (input != ')')
                                {
                                    error = true; // ) did not follow after literal and its negation
                                }
                                else
                                {

                                    new_literal.truth = false;

                                    if (!contains(literal_list, new_literal))
                                    {
                                        //adding unique literals only to literal list
                                        insert_tail(literal_list, new_literal);
                                    } //adding all literals to new_term list
                                    insert_tail(new_term.head, new_literal);
                                }
                            }
                            else if (input != ')') //Case 2: Last literal not negated, expecting )
                            {

                                error = true;
                            }
                            else
                            {

                                new_literal.truth = true;

                                if (!contains(literal_list, new_literal))
                                {
                                    //adding literal same process however truth = true
                                    insert_tail(literal_list, new_literal);
                                }
                                insert_tail(new_term.head, new_literal);
                            }
                        }
                        else
                        {

                            if (input == '\'') //Case 3: Not the last literal, and is being negated
                            {
                                my_file >> input;
                                if (input != '+') //Expecting a + after negation
                                {
                                    error = true;
                                }
                                else
                                {

                                    

                                    new_literal.truth = false;
                                    //Adding symbol with false truth
                                    if (!contains(literal_list, new_literal))
                                    {

                                        insert_tail(literal_list, new_literal);
                                    }
                                    insert_tail(new_term.head, new_literal);
                                }
                            }
                            else if (input != '+')
                            {
                                error = true; //no negate, expected +
                            }
                            else
                            {
                                //Case 4: Not the last literal, not being negated
                                new_literal.truth = true;
                                //Adding literal if unique
                                if (!contains(literal_list, new_literal))
                                {

                                    insert_tail(literal_list, new_literal);
                                }
                                insert_tail(new_term.head, new_literal);
                            }
                        }
                    }
                }
            }
            //Inserting a new term at the end of list of terms
            insert_tail(expression, new_term);
            my_file >> input;
        }
    }

    return error; //returning if errors are present or not with file
}
/*
    Name: print_solution
    Prints the solution list.
    @param solutionList List of all the literals in the solution.

    */
void print_solution(literal_ptr &solutionList) //function that prints the solution
{
    literal_ptr current; 

    //Current pointing to heawd of the literal list.
    current = solutionList; 
    
    //If the list is empty, it is satisfiable by nothing.
    if (current == NULL) // empty list
    {
        cout << "satisfiable by []" << endl;
        return;
    }
    else
    {
        cout << "satisfiable by [";

        //Print all the turth values of the literals. 
        while (current != NULL)
        {
            cout << current->symbol << '=' << std::boolalpha << current->truth; //placeholder variables, prints true if literal is true, false otherwise

            if (current->next != NULL)
            {
                cout << ' ';
            }
            current = current->next;
        }
        cout << ']' << endl;
    }
    return;
}
/*

    Name: allFalse
    Sets a list of terms all to false. 
    @param expression A list of terms.

*/
void allFalse(term_ptr &expression)
{
    term_ptr current = expression;
    while (current != NULL)
    {
        current->truth = false;
        current = current->next;
    }
    return;
}

/*
    Name: get_solution

    Gets the list of variables for the solution and the truth values that would
    satisfy the expression.
    This uses a "depth first" traversal, where it assumes a variable is true
    and then sees how far it can get by assuming all other variables are true,
    then recursively checks the false values. 
    example: {x} -> {x, y} -> {x, y`} -> {x'} -> {x', y} -> {x', y'}
    @param expression The expression containing all the terms to be processed.
    @param solutionList The linked list containing all the truth assignments for each variable
    @param literalList The list of all  unique literals in the expression.
    @return returns if a solution was reached in the case.
*/
bool get_solutions(term_ptr expression, literal_ptr &solutionList, literal_ptr &literalList)
{ 

    literal solution; //The literal for the solution. 
    solution.symbol = literalList->symbol; //Changes solution to current literal in literal list.
    solution.next = NULL;
    if (expression == NULL) //expression is empty  Base case
    {
        return true;
    }
    else
    {
        solution.truth = true; // Test if  current literal is true.
        insert_tail(solutionList, solution); 
         
        if (evaluate(expression, solutionList)) //If solution works, recurse back up. (bottom out)
        {
            return true;
        }
        else
        {
            if (literalList->next != NULL)
            {
                if (get_solutions(expression, solutionList, literalList->next))  //Returns true if this recursive path ever bottoms out as true.                                              
                {
                    return true;
                }
            }
            solutionList = remove_tail(solutionList);  //Path did not work out, remove literal that inserted.
            solution.truth = false; //Attempting the path with the variable set as false. 
            insert_tail(solutionList, solution);
            if(evaluate(expression, solutionList))
            {
                return true;
            }
            else
            {
                if (literalList->next != NULL)
                {
                    
                    if (get_solutions(expression, solutionList, literalList->next)) //Returns true if this recursive path ever bottoms out as true. 
                    {
                        return true;
                    }
                }
            }
            solutionList = remove_tail(solutionList); //Path did not work out, remove literal that inserted.
        }
    }
    return false;
}


/*
    Evaluates if a given solution list would solve the expression.
    @param expression expression to evaluate, list of terms in all of the expression. 
    @param solutionlist List of solutions to try. 
    @return returns if all of the expreession's terms can be all true.
*/

bool evaluate(term_ptr expression, literal_ptr& solutionList)
{
    // solution list contains {x = true}
    // first term of expression contains {x = true, y = true, z = true}
    // returns FALSE

    

    bool solutionFound; //Boolean if the solution works.
    term_ptr currentTerm; //Current term being evaluated.
    literal_ptr currentLiteral; //Current literal being compared.
    literal_ptr evaluateTerm; //Current literal in term being compared.
    currentTerm = expression; 
    solutionFound = true;
    //This loop continues until all terms in expression read or solution is not found.
    while((currentTerm != NULL) && solutionFound) 
    {  
        //moves to the literals inside of the first term
        evaluateTerm = currentTerm->head;       

        //This loop continues all the literals in the term has been evaluated or a mathc is found.
        while(evaluateTerm != NULL && currentTerm -> truth == false) 
        {
            currentLiteral = solutionList; 

            //This loop continues until all the literals have been read.  
            while((currentLiteral != NULL) && (currentTerm -> truth == false)) 
            {
                 //If literal in solution list matches, set term to true.
                if((evaluateTerm->symbol == currentLiteral->symbol) && (evaluateTerm->truth == currentLiteral->truth))
                {
                    currentTerm -> truth = true; 
                }
                currentLiteral = currentLiteral -> next;
            }
            evaluateTerm = evaluateTerm -> next;
        }
        if(currentTerm ->truth == false)
        {
           
            solutionFound = false;
        }
        currentTerm = currentTerm -> next; 
    }



    if (!solutionFound)
    {
        allFalse(expression); //helper function that will change all terms in the expression to false.
    }


    return solutionFound;
}
/*
    Remove the tail in a given literal list.
    @param head The head of the given list.
    @return The head of a list containing no
    */
literal_ptr remove_tail(literal_ptr &head)
{
    if (head == NULL)
        return NULL;

    if (head->next == NULL)
    {
        delete head;
        return NULL;
    }

    //Finds the second last literal.
    literal_ptr second_last = head;
    while (second_last->next->next != NULL)
        second_last = second_last->next;

    // Delete last node
    delete (second_last->next);

    // Change next of second last
    second_last->next = NULL;

    return head;
}
