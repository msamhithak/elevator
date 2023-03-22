#include<iostream>
#include<windows.h>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> source_floors_Up;
vector<int> source_floors_Down;




int current_floor = 0;
void start_Lift(int);
void get_userInput();

class floor {

    public:
    int current;
    int destination;
    int up;
    int down;

    floor(){
        this -> current = 0;
        this -> destination = 0;
        this -> up = 0;
        this -> down = 0;
    }
};


class Node {

    public:

    int current;
    int destination;
    int priority;
    int up;
    int down;
    Node* next;
    Node* prev;

};
Node* up_direction = NULL;
Node* down_direction = NULL;

void PrintList(Node* head){

    Node* temp = head;
    if(temp == NULL)
        cout << "List is empty" << endl;
    while(temp != NULL){

        cout << temp -> destination << endl;
        temp = temp -> next;
    }
}
//pushing the element into the up_request queue
void push_up(int destination,int priority)
{

    Node** head = &up_direction;
    if (up_direction == NULL){

        Node* new_node = new Node();
        new_node -> destination = destination;

        new_node -> priority = priority;
        new_node -> up = 1;
        new_node -> down = 0;
        new_node -> next = NULL;
        new_node -> prev = NULL;
        *head = new_node;
        //(*head) -> up = 1;

    }
    else {

        Node* new_node = new Node();
        new_node -> destination = destination;
        new_node -> up = 1;
        new_node -> down = 0;
        new_node -> priority = priority;

        if (up_direction -> priority > priority){
            new_node -> next = *head;
            (*head) -> prev = new_node;
            new_node -> prev = NULL;
            *head = new_node;
        }
        else{
            Node* temp = *head;
            while((temp -> next != NULL) && (temp -> next -> priority < priority)){

                temp = temp -> next;
            }
            new_node -> next = temp -> next;
            if (temp -> next != NULL){

                temp -> next -> prev = new_node;
            }

            temp -> next = new_node;
            new_node -> prev = temp;
        }
    }

}
//Pushing the floor element to the down queue...
void push_down(int destination,int priority)
{

    Node** head = &down_direction;
    if (down_direction == NULL){

        Node* new_node = new Node();
        new_node -> destination = destination;


        new_node -> priority = priority;
        new_node -> down = 1;
        new_node -> up = 0;
        new_node -> next = NULL;
        new_node -> prev = NULL;
        *head = new_node;
        //(*head) -> down = 1;


    }
    else {

        Node* new_node = new Node();
        new_node -> destination = destination;
        new_node -> down = 1;
        new_node -> up = 0;
        new_node -> priority = priority;

        if (down_direction -> priority < priority){
            new_node -> next = *head;
            (*head) -> prev = new_node;
            new_node -> prev = NULL;
            *head = new_node;
        }
        else{
            Node* temp = *head;
            while((temp -> next != NULL) && (temp -> next -> priority > priority)){

                temp = temp -> next;
            }
            new_node -> next = temp -> next;
            if (temp -> next != NULL){

                temp -> next -> prev = new_node;
            }

            temp -> next = new_node;
            new_node -> prev = temp;
        }
    }

}

Node* pop(Node** head){

    if (head == NULL){
        cout << "error no person" << endl;
    }
    else{

            if ((*head) -> next == NULL)
                return NULL;

            else{

            *head = (*head) -> next;
            (*head) -> prev = NULL;

            return *head;

        }

    }

}

bool isEmpty(Node** head){

    if (*head == NULL)
        return true;
    else
        return false;
}


void requests(floor* new_floor){

    //cout << "New-floor up : " << new_floor -> up << endl;

    if (new_floor -> up == 1){
        int priority = new_floor -> destination;
        //cout << "Priority : " << priority << endl;
        push_up(new_floor-> destination,priority);
    }
    else {
        int priority = new_floor -> destination;
        push_down(new_floor-> destination,priority);
    }



}

void get_userInput()
{
    char ch;
    do{

        floor* new_floor = new floor();
        cout << "Enter current floor number : ";
        cin >> new_floor -> current;
        cout << "Enter destination floor number : ";
        cin >> new_floor -> destination;
        cout << "Direction (up/down) : ";
        string temp_direction;
        cin >> temp_direction;
        if (temp_direction.compare("up")==0){


            new_floor -> up = 1;
            source_floors_Up.push_back(new_floor -> current);
        }
        else if (temp_direction.compare("down")==0){


            new_floor -> down = 1;
            source_floors_Down.push_back(new_floor -> current);
        }
        else{
            cout << "Invalid input type.. try again" << endl;
        }

        requests(new_floor);


        cout << "Another input : (Y/N) : ";
        cin >> ch;

    }while(ch != 'N');


    sort(source_floors_Up.begin(),source_floors_Up.end(),greater<int>());
    sort(source_floors_Down.begin(),source_floors_Down.end());

    start_Lift(current_floor);
}


void start_Lift(int dup_curr){

    Node* current_direction = up_direction;

    if (current_direction == NULL){

        current_direction = down_direction;

    }

    while(current_direction != NULL){

    int temp = dup_curr;

    if (current_direction -> up == 1){





        while(true){


            if ((temp > source_floors_Up.back()) && !(source_floors_Up.empty())){

                while(temp != source_floors_Up.back()){

                    cout << "\nCurrent floor - " << temp;
                    temp--;
                    Sleep(2000);
                }
                dup_curr = temp;
            }


            cout << "\nCurrent floor - " << dup_curr;
            Sleep(2000);
            if (dup_curr == source_floors_Up.back()){

                cout << "\nDoors opening --- Please Enter";
                while(true){

                    if(dup_curr != source_floors_Up.back())
                        break;

                    source_floors_Up.pop_back();
                }
            }
            if (up_direction -> destination == dup_curr){
                cout << " \nDoors opening --- Please exit";

                while(true){

                    if (up_direction == NULL)
                        break;


                    if(up_direction -> destination != dup_curr)
                        break;

                    up_direction = pop(&up_direction);

                }
                temp = dup_curr;
                current_direction = up_direction;



            }


            if (current_direction == NULL)
                break;

            dup_curr++;


    }

    }
    else if(current_direction -> down == 1) {




        while(true){




            if ((temp < source_floors_Down.back()) && (!(source_floors_Down.empty()))){

                while(temp != source_floors_Down.back())
                {
                    cout << "\nCurrent floor - " << temp;
                    Sleep(2000);
                    temp++;
                }
                dup_curr = temp;
            }

            cout << "\nCurrent floor - " << dup_curr;
            Sleep(2000);

            if (source_floors_Down.back() == dup_curr){

                cout << "\nDoors opening --- please enter";
                while(true){

                    if(source_floors_Down.back() != dup_curr)
                        break;
                    source_floors_Down.pop_back();
                }
            }


            if (down_direction -> destination == dup_curr){



                cout << "\nDoors opening --- please exit";

                while(true){

                    if(down_direction == NULL)
                        break;

                    if(down_direction -> destination != dup_curr)
                        break;
                    down_direction = pop(&down_direction);
                }
                current_direction = down_direction;
                temp = dup_curr;
            }



            if (current_direction == NULL)
                break;

            dup_curr--;

        }
    }


    if (isEmpty(&current_direction)){



        current_direction = down_direction;

            if (current_direction == NULL){

                current_direction = up_direction;

                if (current_direction == NULL){

                    cout << "\n\nLift is in halt position at " << dup_curr << endl;
                    cout << "----- User Input -----" << endl;
                    break;
                }

            }


    }


    }



    current_floor = dup_curr;



}



int main()
{

    cout << " ----------------Elevator operations ---------------------" << endl;


    while(true)
        get_userInput();


    return 0;
}
