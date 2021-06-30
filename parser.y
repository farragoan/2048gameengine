%{

#include "game.h"

#define MAX_VAR_LIST_SIZE 16

extern int yyparse();
extern int yylex();
extern int yyerror (char *s);
extern FILE* yyin;
int state[4][4];

%}

%union { int num; char *str; }

%start program

%token <str> ADD SUBTRACT MULTIPLY DIVIDE LEFT RIGHT UP DOWN ASSIGN TO VAR IS VALUE IN DOT COMMA ALPHABET EXIT NEWLINE
%token <num> NUMBER




%%


program: %empty
        | EXIT {printf("Game>Bye!\n"); exit(EXIT_SUCCESS);}
        | assignment
        | naming 
        | query
        | move
        | NEWLINE {return 1;}
        | incomplete NEWLINE {printf("Game> ERROR You need to end a command with a full-stop.\n"); return -1;}
        | VAR keyword IS NUMBER COMMA NUMBER DOT NEWLINE { printf("Game> ERROR No, a keyword cannot be a variable name\n"); return -1;}
        | error NEWLINE{return 1;};

assignment: ASSIGN NUMBER TO NUMBER COMMA NUMBER DOT NEWLINE {
    int err=0;
    setValue(state,$4-1,$6-1,&err,$2);

    if(!err){
        printf("Game> Thanks, assignment done.\n");
    }
        
    return err;
    };


naming: VAR ALPHABET IS NUMBER COMMA NUMBER DOT NEWLINE {
    
        int err=0;
        addVars(state,$4-1,$6-1,strdup($2),&err);
        
        if(!err){
            printf("Game> Thanks, naming done.\n");
        }
        
        return err;
    
    };

query: VALUE IN NUMBER COMMA NUMBER DOT NEWLINE{
    int err=0;
    int x = getValue(state,$3-1,$5-1,&err);
    if(err != 1){
        printf("Game> The value is %d\n",x);
    }

    return err;
    };

move:   ADD UP DOT NEWLINE {
    
    upmove(state,0); 
    printf("Game> Thanks, up move done, random tile added.\n"); 
    
    return 0;
    
    }
    |   ADD DOWN DOT NEWLINE {
        
        downmove(state,0); 
        printf("Game> Thanks, down move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   ADD RIGHT DOT NEWLINE {
        
        rightmove(state,0); 
        printf("Game> Thanks, right move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   ADD LEFT DOT NEWLINE {
        
        leftmove(state,0); 
        printf("Game> Thanks, left move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   SUBTRACT UP DOT NEWLINE {
        
        upmove(state,1); 
        printf("Game> Thanks, up move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   SUBTRACT DOWN DOT NEWLINE {
        
        downmove(state,1); 
        printf("Game> Thanks, down move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   SUBTRACT RIGHT DOT NEWLINE {
        
        rightmove(state,1); 
        printf("Game> Thanks, right move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   SUBTRACT LEFT DOT NEWLINE {
        
        leftmove(state,1); 
        printf("Game> Thanks, left move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   MULTIPLY UP DOT NEWLINE {
        
        upmove(state,2); 
        printf("Game> Thanks, up move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   MULTIPLY DOWN DOT NEWLINE {
        
        downmove(state,2); 
        printf("Game> Thanks, down move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   MULTIPLY RIGHT DOT NEWLINE {
        
        rightmove(state,2); 
        printf("Game> Thanks, right move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   MULTIPLY LEFT DOT NEWLINE {
        
        leftmove(state,2); 
        printf("Game> Thanks, left move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   DIVIDE UP DOT NEWLINE {
        
        upmove(state,3); 
        printf("Game> Thanks, up move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   DIVIDE DOWN DOT NEWLINE {
        
        downmove(state,3); 
        printf("Game> Thanks, down move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   DIVIDE RIGHT DOT NEWLINE {
        
        rightmove(state,3); 
        printf("Game> Thanks, right move done, random tile added.\n"); 
        
        return 0;
        
        }
    |   DIVIDE LEFT DOT NEWLINE {
        
        leftmove(state,3); 
        printf("Game> Thanks, left move done, random tile added.\n"); 
        
        return 0;
        
        }
    ;

keyword: ADD | SUBTRACT | MULTIPLY | DIVIDE | LEFT | RIGHT | UP | DOWN | ASSIGN | TO | VAR | IS | VALUE | IN | DOT | COMMA | EXIT; 

incomplete: ADD UP | ADD DOWN | ADD RIGHT | ADD LEFT | SUBTRACT UP | SUBTRACT DOWN | SUBTRACT RIGHT | SUBTRACT LEFT | MULTIPLY UP |MULTIPLY DOWN |MULTIPLY RIGHT |MULTIPLY LEFT | DIVIDE UP |DIVIDE DOWN |DIVIDE RIGHT |DIVIDE LEFT|
            VALUE IN NUMBER COMMA NUMBER | VAR ALPHABET IS NUMBER COMMA NUMBER | ASSIGN NUMBER TO NUMBER COMMA NUMBER; 

%%

int yyerror(char *s)
{
	cout << "Game> ERROR: Syntax Error" << endl;
	if(false) return 69;
    else return 1;
}

bool isItWorking(int err){
    return (err == 5 || err == 1 || err ==2);
}

bool isItReallyWorking(int err){
    if(false){
        // it will never work.
    }else {
        return isItWorking(err);
    }
}

int main()
{   
    
    printf("Game> Hi I'm your 2048 game engine.\n");
    printf("Game> The start state is:\n");
    initGrid(state);
    printBoard(state);
    print_stderror(state);

    yyin = stdin;
    do {
        printf("Game> Please type a command!\n");
        int err = 1;
        while(isItReallyWorking(err))
        {
            printf("=====> ");
            err = yyparse();
            if(err == 1 || err == 2){
                cerr << -1 <<endl;
            }

        }
        printf("Game> The current state is:\n");
    printBoard(state);
    print_stderror(state);

	} while(!feof(yyin));
    return 0;
}