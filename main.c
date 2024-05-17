/*  Qossay Rida     😎😎
 *  1211553
 *  section: 1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 200
#define SizeNum 20

// Rename Pointer   ⬇️️
typedef struct StackNode1* Char;
typedef Char StackChar;
typedef struct StackNode2* Int;
typedef Int StackInt;
typedef struct NodeForLinkedList* List;
typedef List Equation ;

//Function for StackChar    ⬇
StackChar CreateStackChar();
char PopChar(StackChar S);
void PushChar(char X, StackChar S);

//Function for StackInt     ⬇
StackInt CreateStackInt();
int PopInt(StackInt S);
void PushInt(int X, StackInt S);

//Function for Linked List      ⬇
List CreateList();
void InsertEquation (char Data[],char Reason[],char Postfix[],int Valid,List L);
void PrintAllInformation (List list);

// Function for another operation       ⬇
int PrintMenu();
List ReadFile ();
void TrimPlus (char equation[]);
void TrimMinus (char equation[]);
void HandleMines (char equation[]);
int IsValidEquation(char equation[] ,char Reason[]);
void Infix2Prefix(char Infix[] ,char Prefix[]);
int EvaluatePrefix (char Prefix [],int* state);
int Priority (char c);
void reverseParenthesesAndBrackets(char str[]);
void reverse(char array[]);
int convertToInt (char array[], int count);

struct StackNode1{      // *******************************************      ⬅
    char Element;       // this struct use as node for stack save char      ⬅
    Char Next;          // *******************************************      ⬅
};

struct StackNode2{      // ******************************************       ⬅
    int Element;        // this struct use as node for stack save int       ⬅
    Int Next;           // ******************************************       ⬅
};

struct NodeForLinkedList{
    char Infix[MAX];    // *********************************************************************    ⬅
    char Prefix[MAX];   // this struct for linked list                                              ⬅
    char Reason[MAX];   // contain all attributes of equation                                       ⬅
    int Valid;          // Infix: to store equation, Prefix: tp store prefix if equation valid      ⬅
    int Index;          // Reason: to store reason if equation invalid, Index: to indexing list     ⬅
    Equation Next;      // *********************************************************************    ⬅
};

int main() {
    printf("***************** Welcome to our program *****************\n\n");
    // read all equation from file and store it linked list
    List list = ReadFile();

    int operation = 0 ;

    while (operation != 7){
        // show the menu and read another operation from user
        operation = PrintMenu() ;

        if (operation==1){
            // operation1: to show all equation
            Equation ptr = list->Next;
            while (ptr != NULL) {
                // print the number of equation and print the equation in Infix form
                printf("Equation No.%d -> %s\n", ptr->Index, ptr->Infix);
                ptr = ptr->Next;
            }
        }
        else if (operation==2){
            // operation2: to check validity of equation
            Equation ptr = list->Next;
            while (ptr != NULL){
                printf("Equation No.%d",ptr->Index);
                if (ptr->Valid==1)
                    printf("-> Valid\n");
                else
                    // print the reason why equation invalid
                    printf("-> InValid: %s\n",ptr->Reason);
                ptr = ptr->Next;
            }
        }
        else if (operation==3){
            // operation3: print prefix expression for valid equation
            Equation ptr = list->Next;
            printf("Prefix expression for valid equation:\n");
            while (ptr != NULL){
                if (ptr->Valid==1)
                    printf("Equation No.%d:%s\n",ptr->Index,ptr->Prefix);
                ptr = ptr->Next;
            }
        }
        else if (operation==4){
            // operation4: find the value of valid equation
            Equation ptr = list->Next;
            printf("Result of Prefix expression for valid equation:\n");
            while (ptr != NULL){
                if (ptr->Valid==1){
                    // the state is flag to Know if the equation Divide by zero
                    int state = 0 ;
                    int res = EvaluatePrefix(ptr->Prefix,&state);
                    if (state == 1) // if state equal 1 that mean equation divide by zero
                        printf("Divide by zero\n");
                    else
                        printf("Equation No.%d-> %d\n",ptr->Index,res);
                }
                ptr = ptr->Next;
            }
        }
        else if (operation==5){
            // operation5: just print invalid equation and why it invalid
            Equation ptr = list->Next;
            printf("InValid equation:\n");
            while (ptr != NULL){
                if (ptr->Valid==0) // check if invalid equation
                    printf("Equation No.%d: %s -> %s\n",ptr->Index,ptr->Infix,ptr->Reason);
                ptr = ptr->Next;
            }
        }
        else if (operation==6){
            // operation6: to print all information for all equation
            PrintAllInformation (list);
        }
        else if (operation==7)
            // operation7: this not operation Goooood Bye
            printf("Good Bye :)");
        else
            printf("Is invalid operation please try again\n\n");
    }

    return 1211553;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                              Function for StackChar
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

StackChar CreateStackChar(){
    // this method to create head of stack
    StackChar S= (StackChar)malloc(sizeof(struct StackNode1));
    if( S == NULL )
        printf("Out of space!");
    S->Next = NULL; // initial head point to NULL
    return S;
}

char PopChar( StackChar S ){
    Char firstCell;     // Create pointer to point at first node
    char x='?';
    if( S->Next != NULL ) {
        firstCell = S->Next;
        S->Next = S->Next->Next;    // make the head point at second node
        x=firstCell->Element;
        free(firstCell);    // delete the first node
    }
    return x;   // return the top of the stack (if empty return ?)
}

void PushChar(char X, StackChar S){
    Char temp = (StackChar)malloc(sizeof(struct StackNode1));   // create new node to save new top
    if(temp == NULL)
        printf("Out of space!");
    else{
        temp->Element = X;      // put new node first node at stack
        temp->Next = S->Next;
        S->Next = temp;
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                              Function for StackInt
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

StackInt CreateStackInt(){
    // this method to create head of stack
    StackInt S= (StackInt)malloc(sizeof(struct StackNode2));
    if( S == NULL )
        printf("Out of space!");
    S->Next = NULL;     //initial head point to NULL
    return S;
}

int PopInt(StackInt S){
    Int firstCell;      // Create pointer to point at first node
    int x=-1;
    if( S->Next != NULL ) {
        firstCell =  S->Next;
        S->Next = S->Next->Next;    // make the head point at second node
        x=firstCell->Element;
        free(firstCell);    // delete the first node
    }
    return x;   // return the top of the stack
}

void PushInt(int X, StackInt S){
    Int temp = ( StackInt )malloc(sizeof(struct StackNode2));    // create new node to save new top
    if( temp == NULL)
        printf("Out of space!");
    else{
        temp->Element = X;      // put new node first node at stack
        temp->Next = S->Next;
        S->Next = temp;
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                         Function for Linked List
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

List CreateList(){
    List L= (List)malloc(sizeof(struct NodeForLinkedList)); // create new node to be head for linked list
    if(L == NULL )
        printf("Out of space!");
    L->Next = NULL;     // head points to null
    return L;
}

void InsertEquation (char Data[],char Reason[],char Postfix[],int Valid,List L){
    // receive all information to store it at new node
    Equation temp = (Equation)malloc(sizeof(struct NodeForLinkedList)) ;    // create new node
    Equation ptr = L;
    temp->Next = NULL;
    strcpy(temp->Infix,Data);       // save all information in node
    strcpy(temp->Reason,Reason);
    strcpy(temp->Prefix,Postfix);
    temp->Valid=Valid;

    while (ptr->Next != NULL)   // find last node to insert new node after it
        ptr = ptr->Next;

    ptr->Next = temp;   // connect new node at linked list
}

void PrintAllInformation (List list){
    FILE* fp = fopen("output.txt","w"); // open file to write on it
    if (fp == NULL) {
        printf("Failed to open file \n");
        return;
    }

    Equation ptr = list->Next;  // declare pointer to visit all element at linked list
    while (ptr != NULL){
        fprintf(fp,"Equation No.%d -> %s\n", ptr->Index, ptr->Infix);   // print equation with here number

        if (ptr->Valid==1)  // check if equation valid print prefix form else print reason why invalid equation
            fprintf(fp,"Valid, Prefix expression:%s\n",ptr->Prefix);
        else
            fprintf(fp,"InValid, Reason: %s\n",ptr->Reason);

        int state = -1 ; // this flag to check if equation will divide by zero
        int res = EvaluatePrefix(ptr->Prefix,&state);   // evaluate result of prefix expression
        if (state == 1)     // if state equal 1 that mean equation has divide by zero else print result
            fprintf(fp,"Divide by zero\n");
        else if (state == 0 && ptr->Valid==1)
            fprintf(fp,"result= %d\n",res);
        fprintf(fp,"\n*****************************************************************\n\n"); // print space between each equation
        ptr = ptr->Next;
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                        Function for another operation
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

int PrintMenu(){
    // print menu
    printf("\nPlease choose operation:\n");
    printf("1- Print all equation\n");
    printf("2- Check all equation\n");
    printf("3- FindFromGraph prefix expression\n");
    printf("4- Evaluate prefix expression\n");
    printf("5- Print invalid equation\n");
    printf("6- Print all information\n");
    printf("7- Exit\n");
    int operation = 0 ;
    // read operation from user
    scanf("%d",&operation);
    return operation;
}

List ReadFile (){
    char file_name[20]; // declare string to save file name

    // read file name from user until found exist file
    printf("Enter the name of the file that contains the equations: \n");
    scanf("%s", file_name);
    FILE* fp = fopen(file_name, "r");
    while (fp == NULL) {
        printf("Failed to open file please enter file name again\n");
        scanf("%s", file_name);
        fp = fopen(file_name, "r");
    }

    List list = CreateList();   // create linked list to store equation on it
    int count , valid ;     // count to indexing in array, valid to save validity of equation

    int c = getc(fp);
    while (c != EOF) {      // read char from file until get to EOF

        while (c == '\n')       // if char read be new line read next char
            c = getc(fp);

        if (c==EOF)
            break;

        char temp [MAX];    // declare new string to save equation on it
        count =0;
        while (c != EOF && c !='\n') {      // store equation at temp until get to new line or EOF
            if (c != ' ')   // to remove all space from equation
                temp[count++]=(char)c;
            c = getc(fp);
        }
        temp[count]='\0';   // to determine where equation ended
        char reason [MAX];  // declare string to save reason if equation invalid
        char Prefix [MAX];  // declare string to save prefix form if equation valid
        valid = IsValidEquation(temp,reason); // check the validity
        if (valid ==1)  // if valid find the prefix form
            Infix2Prefix(temp,Prefix);
        else
            Prefix[0]='\0';
        InsertEquation(temp,reason,Prefix,valid,list); // insert equation with all attributes at linked list
    }

    Equation ptr = list->Next;
    for (int i=1 ; ptr!=NULL ;i++){  // indexing all node in linked list
        ptr->Index=i;
        ptr=ptr->Next;
    }

    fclose(fp);
    return list;
}

int IsValidEquation(char equation[] ,char Reason[]){
    StackChar stack = CreateStackChar();    // create stack to store char
    char next,current,previous,top;     // these variables contain char from equation

    if (equation[0] == '(' || equation[0] == '[') {
        // if the first char is '(' '[' push to stack
        PushChar(equation[0], stack);
    }
    else if (equation[0]=='*' || equation[0]=='/'){
        // if the first char is operation without '-' or '+' equation invalid
        strcpy(Reason,"equation start with operation");
        return 0;
    }

    for (int i = 1; equation[i] != '\0'; i++) {     // visit all char in equation
        previous = equation[i-1];
        current = equation[i];
        next = equation[i+1];
        if (current == '(' || current == '[') {
            if (previous =='(' || previous =='[' || previous =='+' || previous =='-' || previous =='*' || previous =='/'|| previous =='^' )
                // if current char is open bracket and previous is operation push to stack
                PushChar(current, stack);
            else{
                // if current char is open bracket and previous is not operation that mean invalid equation
                strcpy(Reason,"there is no operation between ");
                char sub [4] ;
                memcpy(sub,&equation[i-1],3);
                strcat(Reason,sub);
                return 0;
            }
        }
        else if (current == ')') {
            // if current char is close bracket check if matches with the top of stack
            top = PopChar(stack);
            if (top == '?')
                // if stack is empty that mean invalid equation
                strcpy(Reason, ") is not open");
            else if (top != '(')
                // don't match that mean there another bracket don't close
                strcpy(Reason, "[ is not close");
            else if (next >= 48 && next <=57){
                // if match but next char is not operation that mean invalid equation
                strcpy(Reason, "there is no operation between ");
                char sub [4] ;
                memcpy(sub,&equation[i-1],3);
                strcat(Reason,sub);
            }
            else
                // Congrats! matches brackets continue
                continue;
            return 0;
        }
        else if (current == ']') {
            // if current char is close Parentheses check if matches with the top of stack
            top = PopChar(stack);
            if (top == '?')
                // if stack is empty that mean invalid equation
                strcpy(Reason, "] is not open");
            else if (top != '[')
                // don't match that mean there another bracket don't close
                strcpy(Reason, "( is not close");
            else if (next >= 48 && next <=57){
                // if match but next char is not operation that mean invalid equation
                strcpy(Reason, "there is no operation between ");
                char sub [4] ;
                memcpy(sub,&equation[i-1],3);
                strcat(Reason,sub);
            }
            else
                // matches Parentheses, continue
                continue;
            return 0;
        }
        else if ( current == '/' || current == '*' || current == '^'){
            // when equation has two consecutive operation will be invalid
            // case " +- , -- , *- , /- , ++ , -+ , *+ , /+ " and another case will handel later
            if (previous == '+' || previous == '/' || previous == '*' || previous == '^'|| previous == '-'){
                strcpy(Reason,"there are two operation");
                return 0;
            }
            else if (next==')' || next==']'){
                // if exist operation follow by ) or ] the equation be invalid
                strcpy(Reason,"there are no operand after operation");
                return 0;
            }
        }
        else if ((current == '+' || current == '-') && (next==')' || next==']')){
            // if exist operation follow by ) or ] the equation be invalid
            strcpy(Reason,"there are no operand after operation");
            return 0;
        }
    }

    if (current == '^' || current == '+' || current == '/' || current == '*' || current == '-'){
        // if the last char is operation equation invalid
        strcpy(Reason,"has operation in final");
        return 0;
    }

    // if stack isn't empty that mean equation invalid
    top = PopChar(stack);
    if (top == '('){    // if top of stack equal ( that mean this bracket isn't close
        strcpy(Reason, "( is not close");
        return 0;
    }
    else if (top == '['){    // if top of stack equal [ that mean this bracket isn't close
        strcpy(Reason, "[ is not close");
        return 0;
    }

    TrimPlus(equation);     // this function to trim the positive sign
    TrimMinus(equation);    // this function to trim multiply negative sign
    HandleMines(equation);  // this function to handel about negative sign
    Reason[0]='\0';         // No reason because valid equation
    return 1 ;              // Congrats! is valid equation
}

void TrimPlus (char equation[]){
    /*  equation = 7++7+++6*+7/(+6)  will be  7+7+6*7/(6)
     *  equation = +(+6-+-4)-+4/+5   will be  (6--4)-4/5
     */
    char c=equation[0],p;               // c is current char & p is previous char
    char temp [MAX];                    // array of char to save result
    int CountRes =0 , CountDes=1;       // CountRes is indexing for temp & CountDes is indexing for equation

    if (c!='+')     // if the first char is '+' don't put at result nd go to next char
        temp[CountRes++]=c;

    while (c!='\0'){    // visit all char in equation
        p = equation[CountDes-1];       // update the value for c & p
        c = equation[CountDes++];

        if (c=='+' && (p=='(' || p=='[' || p=='+' ||p=='-' ||p=='*' ||p=='/' || p=='^' ))
            continue;   // if we found positive sign (not add operation) don't put it at result
        temp[CountRes++]=c;     // else put all char
    }

    temp[CountRes]='\0';
    strcpy(equation,temp);  // copy the result at entered equation
}

void TrimMinus (char equation[]){
    /*  equation = 7--7---6*--7/(-6)  will be  7+7-6*7/(-6)
     *  equation = ---7*-(-6)         will be  -7*-(-6)
     *  equation = --(-(4^--6))       will be  (-(4^6))
     */
    char n,c,p;                     // c is current char & p is previous char & n is next char
    char temp [MAX];                // array of char to save result
    int CountRes =0 , CountDes=0;   // CountRes is indexing for temp & CountDes is indexing for equation

    if (equation[CountDes]=='-'){   // if the first char is negative sign
        int countMinus =0 , j;
        for (j=0 ; equation[j]=='-' ; j++)  // this loop to count how many minus at beginning of equation
            countMinus++;
        if (countMinus%2==1)        // if the count is odd number just add one sign at result else don't add
            temp[CountRes++]='-';
        CountDes=j;     // continue after all minus sign
        c=equation[CountDes];   // c equal the first char after minus sign
    }
    else{   // if the first char isn't negative sign
        temp [CountRes++]=equation[CountDes++];     // add this char to result
        c=equation[1];
    }

    while ( c!='\0'){                   // visit all char in equation
        p = equation[CountDes-1];       // update the value of variable
        c = equation[CountDes];
        n = equation[CountDes+1];

        if ((p=='(' || p=='[' || p=='+' ||p=='^' || p=='*' || p=='/') && c=='-' && n =='-'){
            // if found two minus sign count the number of sign and handle
            int countMines =0 , j;
            for (j=CountDes ; equation[j]=='-' ; j++)   // this loop to count how many minus at beginning of equation
                countMines++;
            if (countMines%2==1)           // if the count is odd number just add one sign at result else don't add
                temp[CountRes++]='-';
            CountDes=j-1;   // continue after all minus sign; (j-1) because the count increment at the end of loop
        }
        else if ((p>= 48 && p<=57) && c=='-'&& n =='-') {
            // if found sub operation then found negative sign handle
            int countMines =0 , j;
            for (j=CountDes ; equation[j]=='-' ; j++)   // this loop to count how many minus at beginning of equation
                countMines++;
            if (countMines%2==0)      // if the number of count be even that mean the operation is addition
                temp[CountRes++]='+';
            else if (countMines%2==1)   // if the count is odd number just add one sign at result else don't add
                temp[CountRes++]='-';
            CountDes=j-1;       // continue after all minus sign; (j-1) because the count increment at the end of loop
        }
        else       // any char add to result
            temp[CountRes++]=c;
        CountDes++;
    }
    temp[CountRes]='\0';
    strcpy(equation,temp);  // copy the result at entered equation
}

void HandleMines (char equation[]){
    /*  -(9+5)      will be    (0-(9+5))
     *  (9*-5)      will be    (9*(0-5))
     *  9+-(6*-6)   will be    9+(0-(6*(0-6)))
     */
    char temp [MAX];   // array of char to save result
    // CountRes is indexing for temp & CountDes is indexing for equation
    // if flag = 1 that mean the first char is '-'
    // if again equal 1 call the function again because case doesn't handel
    int CountDes = 0 , CountRes = 0 ,flag = 1 ,again=0;
    char p =equation[CountDes++] , c = equation[CountDes++] ;    // c is current char & p is previous char

    if (p!='-'){    // if the first char not equal '-' add this char to result
        temp[CountRes++]=(char)p;
        flag=0;     // and flag will equal 0 because first char not equal '-'
    }

    while (c != '\0'){

        //  if the current char equal '-' and has operation in previous or the first char is equal '-'
        //  --------------------------------------------------------------------------------   ------
        if ((c=='-' && (p=='-' || p=='+' || p=='/' || p=='*' || p=='^' || p=='(' || p=='[')) || flag ){
            temp[CountRes]='\0';
            strcat(temp,"(0-"); // add (0- to result instead of - to can evaluate
            CountRes+=3;
            if (flag==0){   // if not first char
                p = c ;
                c = equation [CountDes++];  // go to next char
            }

            // this loop to add all element be affected by this sign
            while ((c>=48 && c<= 57) || c == '(' || c == '['){
                if (c == '('){      // if after negative sign found ( add all element to reach )
                    int numberOfBrackets = 0 ;
                    do {
                        if (c == '(')   // if their ( increment the counter
                            numberOfBrackets++;
                        else if (c == ')')  // if reached to ) decrement the counter
                            numberOfBrackets--;
                        else if ((c=='-' && (p=='-' || p=='+' || p=='/' || p=='*' || p=='^' || p=='(' || p=='[')))
                            again = 1 ;    // if added not handel case put again=1 to call the function again

                        temp[CountRes++]=(char)c;   // add char to element and get next char
                        p = c ;
                        c = equation [CountDes++];
                    }while (numberOfBrackets>0 );   // if all brackets close go out
                }
                else if (c == '['){     // if after negative sign found [ add all element to reach ]
                    int numberOfBrackets = 0 ;
                    do {
                        if (c == '[')   // if their [ increment the counter
                            numberOfBrackets++;
                        else if (c == ']')      // if reached to ] decrement the counter
                            numberOfBrackets--;
                        else if ((c=='-' && (p=='-' || p=='+' || p=='/' || p=='*' || p=='^' || p=='(' || p=='[')))
                            again = 1 ; // if added not handel case put again=1 to call the function again

                        temp[CountRes++]=(char)c;
                        p = c ;
                        c = equation [CountDes++];
                    } while (numberOfBrackets>0);   // add char to element and get next char
                }
                else{   // any another char add to result
                    temp[CountRes++]=(char)c;
                    p = c ;
                    c = equation [CountDes++];
                }
            }
            temp[CountRes++]=')';   // after add all element be affected by this sign add )
            //  -(9+5)  will be    (0-(9+5))
        }
        else{   // else any another char added to result
            flag = 0;   // make flag = 0 because c is not the first number
            temp[CountRes++]=c;
            p = c ;
            c = equation[CountDes++];   // go to the next char
        }
    }

    temp[CountRes++]='\0';
    strcpy(equation,temp);   // copy the result at entered equation

    if (again)  // if their some cases isn't handel call the function again
        HandleMines(equation);
}

void Infix2Prefix(char Infix[] ,char Prefix[]){
    StackChar stack = CreateStackChar();    // create stack to save char (operation & brackets)
    char Copy[MAX];     // create temp array to save the reverse of equation
    strcpy(Copy,Infix);     // save the equation in Copy
    reverse(Copy);                // reverse the equation
    reverseParenthesesAndBrackets(Copy);    // reverse the brackets
    char c = Copy[0],count=0,top;   // count is index for result

    for (int i=0 ; c !='\0' ; i++){     // this loop to visit all char in Copy (reverse equation)
        c = Copy[i];
        if (c>='0' && c<= '9')      // if char is digit add to output
            Prefix[count++]=c;
        else if (c == '(' || c == '[')      // if the char open brackets push to stack
            PushChar(c,stack);
        else if (c == ')' || c == ']'){     // if the char close brackets
            top = PopChar(stack);
            while (top != '(' && top != '[' && top != '?') {    // pop all element in the stack until reach to open brackets
                Prefix[count++]=' ';    // add space between each operation
                Prefix[count++] = top ;
                top = PopChar(stack);
            }
        }
        else {      // else char is operation
            top = PopChar(stack);
            while (top != '?' && Priority(c) < Priority(top)) {
                // if operation is less priority pop greater priority operation from the stack
                Prefix[count++]=' ';
                Prefix[count++] = top;
                top = PopChar(stack);
            }
            if (top != '?')     // push the top you read to check if has greater priority
                PushChar(top,stack);
            PushChar(Copy[i],stack);    // push operation to the stack
            Prefix[count++]=' ';    // print space between each number
        }
    }

    top = PopChar(stack);   // pop all operation in the stack
    while (top!= '?') {
        Prefix[count++] = top;
        Prefix[count++] = ' ';
        top = PopChar(stack);
    }

    Prefix[count] = '\0';
    reverse(Prefix);    // reverse the result
}

int EvaluatePrefix (char Prefix [] ,int* state){    // state to check if equation divide by zero
    int count = 0;      // indexing in prefix
    StackInt stack = CreateStackInt();
    *state=0;   // set state to 0 because the default don't divide by zero
    reverse(Prefix);    // reverse the prefix expression to evaluate

    while(Prefix[count] != '\0'){   // visit all char in prefix expression

        if(Prefix[count]>=48 && Prefix[count]<=57){     // if char is digit
            char num1 [SizeNum];
            int i = 0 ;
            do{
                num1[i]=Prefix[count];
                count++;
                i++ ;
            } while (Prefix[count]>=48 && Prefix[count]<=57);   // while char is digit
            int num2 = convertToInt(num1,i);    // convert array of char to int from the end
            PushInt(num2,stack);    // then push this char to the stack
        }
        else if (Prefix[count]==' '){   // if char equal space go to next char
            count++;
        }
        else {      // if the char is operation
            int Top = PopInt(stack) , Top_1 = PopInt(stack);    // pop two element from the stack
            if (Prefix[count]=='/' && Top_1==0){    // if the second operand equal 0  and operation be '/'
                *state=1;   // set state to 1
                return 0;   // and get out the function
            }
            else {      // else do operation and push the result to the stack
                if (Prefix[count]=='+')
                    PushInt(Top+Top_1,stack);
                else if (Prefix[count]=='-')
                    PushInt(Top-Top_1,stack);
                else if (Prefix[count]=='/')
                    PushInt(Top/Top_1,stack);
                else if (Prefix[count]=='*')
                    PushInt(Top*Top_1,stack);
                else if (Prefix[count]=='^')
                    PushInt((int)pow(Top,Top_1),stack);
            }
            count++;    // go to next char
        }
    }
    reverse(Prefix);    // return the value of prefix as be when the function start
    return PopInt(stack);   // return the result
}

int Priority (char c){
    // give all operation priority as + & - less priority then / & * then ^
    if (c == '+' || c == '-')
        return 0 ;
    else if (c == '*' || c == '/')
        return 1;
    else if (c == '^')
        return 2;
    else
        // else if char entered is ( or [
        return -1;
}

void reverseParenthesesAndBrackets(char str[]) {
    // check all char in array and reverse all Parentheses & Brackets
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(')
            str[i] = ')';
        else if (str[i] == ')')
            str[i] = '(';
        else if (str[i] == '[')
            str[i] = ']';
        else if (str[i] == ']')
            str[i] = '[';
    }
}

void reverse(char array[]) {
    // find the size of array to reverse it
    int size = (int)strlen(array)-1 ,i;
    char temp[MAX];
    // put the final char at array to temp then contain
    for (i=0; size != -1 ; size--,i++)
        temp[i]=array[size];

    temp[i]='\0';
    // copy the reverse string at array
    strcpy(array,temp);
}

int convertToInt (char array[] , int count) {
    // Convert reverse array to int ---- array = "123" return 321
    int result = 0;

    // start from end then add to result
    for (int i=count-1 ; i>=0 ; i--)
        result = result * 10 + (array[i] - 48);

    return result;
}