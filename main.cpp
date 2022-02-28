#include "header.h"
int main()
{
    bool file_error; //false if file was not opened or has an error

    literal_ptr literal_list = NULL;  //contains every unique literal
    literal_ptr solution_list = NULL; //The printed solution
    term_ptr expression = NULL;       //contains every term
    bool satisfiable;

    file_error = open_file(literal_list, expression); //builds the lists

    
    if (file_error == false)
    {
        allFalse(expression);
        satisfiable = get_solutions(expression, solution_list, literal_list);
        if (satisfiable)
        {
            sort(solution_list); //sorts the solution into alphabetical order
            print_solution(solution_list);
        }
        else
        {
            cout << "unsatisfiable";
        }
    }

    return 0;
}
