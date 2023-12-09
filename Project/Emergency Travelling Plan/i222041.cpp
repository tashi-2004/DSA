/*
Tashfeen Abbasi 
i22-2041 
DS-D
Data Structures Final project- Fall 23
1) My c++ code implements a program for user registration and login.
2) It is followed by an emergency travel planner using graph-based BFS traversal.
3) The user class handles user registration and login with password validation.
4) The Graph class represents a city network, allowing the addition of road and aerial connections.
5) The main function presents a menu for user registration/login and initiates the emergency travel planner,
   including graph creation, traversal, and calculation of minimum days required to travel between cities using
   BFS with road limits.
*/


#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include <conio.h>//For Getch for security, hiding password
using namespace std;
//``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
//````````````````````````````````````````````````````````````` CLASS USER ````````````````````````````````````````````````````````````
//``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
class user
{
private:
    string name;
    long long int id;
    string password;
public:
    user();
    user(string n, int i);
    void setName(string newName);
    void setId(int newId);
    void setPassword(string newPassword);
    string getName() const;
    int getId() const;
    string getPassword() const;
    bool check_reg_password(const string& password);
    string get_password();
    void registration();
    bool check_username(string s);
    bool login(string username, string pass);
};


// DEFAULT CONSTRUCTOR
user::user()
{
    name = "";
    id = 0;;
    password = "";
}


// PARAMETERIZED CONSTRUCTOR
user::user(string n, int i)
{
    this->name = n;
    this->id = i;
}




//`````````` SETTERS  ```````
void user::setName(string newName)
{
    name = newName;
}




void user::setId(int newId)
{
    id = newId;
}




void user::setPassword(string newPassword)
{
    password = newPassword;
}




//```````` GETTERS ```````````
string user::getName() const
{
    return name;
}




int user::getId() const
{
    return id;
}




string user::getPassword() const
{
    return password;
}





//``````````` CHECKING PASSWORD ```````````````
bool user::check_reg_password(const string& password)
{
    int length = password.length();

    if (length < 6)
    {
        cout << "Enter a password of length 6 or above " << endl << endl;
        return false;
    }
    else
    {
        bool upper_case = false;
        bool lower_case = false;
        bool digits = false;
        bool special = false;

        for (int i = 0; i < length; i++)
        {
            //Assci Apply ki yaha aur phr compare
            if (password[i] >= 65 && password[i] < 91)
            {
                upper_case = true;
            }

            if (password[i] >= 97 && password[i] <= 122)
            {
                lower_case = true;
            }

            if ((password[i] >= 33 && password[i] <= 47) || (password[i] >= 58 && password[i] <= 64) || (password[i] >= 91 && password[i] <= 96) || (password[i] >= 123 && password[i] <= 126))
            {
                special = true;
            }

            if (password[i] >= 48 && password[i] <= 57)
            {
                digits = true;
            }
        }

        if (upper_case && lower_case && digits && special)
        {
            return true;
        }
        else
        {
            cout << "Password must contain at least one uppercase letter, one lowercase letter, one digit, and one special character." << endl << endl;
            return false;
        }
    }
}




//```````````` GET PASSWORD  ````````````
string user::get_password()
{
    string password;
    while (true)
    {
        cout << "Enter the password: ";
        getline(cin, password);
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
        if (check_reg_password(password))
        {
            return password;
        }
    }
}





//``````````````` REGISTRATION ``````
void user::registration()
{
    //username stored in username.txt
    ofstream file_user("username.txt");
    if (file_user.is_open())
    {
        file_user << name << endl;
        file_user.close();
    }
    password = get_password();
    //password ko password.txt ma store
    ofstream file_pass("password.txt");
    if (file_pass.is_open())
    {
        file_pass << password << endl;
        file_pass.close();
    }
}





//```````````` CHECK USERNAME  ````````````````
bool user::check_username(string s)
{
    ifstream file("username.txt");
    if (file.is_open())
    {
        string file_username;
        while (getline(file, file_username))
        {
            if (s == file_username)
            {
                file.close();
                return true;
            }
        }
        file.close();
    }
    else
    {
        cout << "Failed to open the username file." << endl;
    }
    return false;
}






//`````````````` `` LOGIN ``````````````````````
bool user::login(string username, string pass)
{
    ifstream user_file("username.txt");
    ifstream pass_file("password.txt");

    if (!user_file.is_open() || !pass_file.is_open())
    {
        cout << "\t\t\t\t\tError opening username or password file." << endl;
        return false;
    }

    string file_username, file_password;
    bool found = false;

    while (getline(user_file, file_username) && getline(pass_file, file_password))
    {
        if (username == file_username && pass == file_password)
        {
            cout << endl;
            cout << "\t\t\t\t\tLogin Successful!!" << endl;
            found = true;
            system("cls");
            system("pause");
        }
    }
    user_file.close();
    pass_file.close();
    if (!found)
    {
        cout << endl;
        cout << "\t\t\t\tIncorrect username or password. Login failed :( " << endl;
    }
    return found;
}








//``````````````````` Read Password ```````````````````
string read_pass()
{
    char check;
    string pwd;
    for (;;)
    {
        check = _getch();
        if (check == '\r')
        {
            break;
        }
        if (check == '\b')
        {
            if (!pwd.empty())
            {
                pwd.pop_back();
                cout << "\b \b" << endl;
            }
        }
        else
        {
            pwd.push_back(check);
            cout << '*';
        }
    }
    return pwd;
}






//``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
//```````````````````````````````````````````````````````````` CLASS NODE ``````````````````````````````````````````````````````
//``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
struct Node
{
    Node* next;
    int data;
    Node(int d)
    {
        data = d;
        next = nullptr;
    }
};






//```````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
//```````````````````````````````````````````````````````````` CLASS GRAPH ``````````````````````````````````````````````````````
//```````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
class Graph
{
    int total_cities;
    Node** road_conn;
    Node** aerial_conn;
public:
    Graph();
    Graph(int c);
    void add_road(int origin, int destination);
    void add_aerial(int o, int d);
    void graph_print();
    void BFS(int start, bool* visited, Graph& g);
    void BFS_Graph(Graph& g);
    int minDaysToTravel(int start, int end);
};




// Default Constructor
Graph::Graph()
{
    total_cities = 0;
    road_conn = nullptr;
    aerial_conn = nullptr;
}





// Parameterized Constructor
Graph::Graph(int c)
{
    total_cities = c;
    road_conn = new Node * [total_cities];
    aerial_conn = new Node * [total_cities];
    for (int i = 0; i < total_cities; i++)
    {
        road_conn[i] = nullptr;
        aerial_conn[i] = nullptr;
    }
}





// Add Road
void Graph::add_road(int origin, int destination)
{
    int t_roads = 0;
    Node* curr_road = road_conn[origin];
    while (curr_road != nullptr)
    {
        t_roads++;
        curr_road = curr_road->next;
    }
    if (t_roads >= 6)
    {
        cout << "Cannot add more road connections for city " << origin << ". Limit reached." << endl;
        return;
    }

    // Add road connection
    Node* new_node = new Node(destination);
    new_node->next = road_conn[origin];
    road_conn[origin] = new_node;
}





// Add Aerial
void Graph::add_aerial(int o, int d)
{
    Node* new_node = new Node(d);
    new_node->next = aerial_conn[o];
    aerial_conn[o] = new_node;
}





// Graph printing
void Graph::graph_print()
{
    for (int i = 0; i < total_cities; i++)
    {
        //Aerial
        cout << "Aerial connection of city " << i << ": ";
        Node* aerial_current = aerial_conn[i];
        while (aerial_current != nullptr)
        {
            cout << aerial_current->data << " ";
            aerial_current = aerial_current->next;
            if (aerial_current != nullptr)
            {
                //Using this arrow when there are 2 cities in same they use arrow
                cout << "--> ";
            }
        }
        cout << endl;
    }
}





// Breadth-First Search Traversal
void Graph::BFS(int start, bool* visited, Graph& g)
{
    queue<int> q1;
    q1.push(start);
    visited[start] = true;




    while (!q1.empty())
    {
        int curr_city = q1.front();
        q1.pop();
        cout << curr_city << " ";
        // Traverse road connections
        Node* curr_road = g.road_conn[curr_city];
        while (curr_road != nullptr)
        {
            int parosi_city = curr_road->data;
            if (!visited[parosi_city])
            {
                q1.push(parosi_city);
                visited[parosi_city] = true;
            }
            curr_road = curr_road->next;
        }




        // Traverse aerial connections
        Node* curr_air = g.aerial_conn[curr_city];
        while (curr_air != nullptr)
        {
            int parosi_city = curr_air->data;
            // The traveler reaches the other destination of the aerial route by the end of the same day
            if (!visited[parosi_city])
            {
                q1.push(parosi_city);
                visited[parosi_city] = true;
            }
            curr_air = curr_air->next;
        }
    }
}





//BFS Graph
void Graph::BFS_Graph(Graph& g)
{
    int total_cities = g.total_cities;
    bool* already_visited = new bool[total_cities] {false};

    for (int i = 0; i < total_cities; ++i)
    {
        if (!already_visited[i])
        {
            BFS(i, already_visited, g);
        }
    }
    delete[] already_visited;
    cout << endl;
}






// Function to find the minimum days using BFS with road limit
int Graph::minDaysToTravel(int start, int end)
{
    queue<int> q1;



    bool* already_visited = new bool[total_cities] {false};
    int* din = new int[total_cities] {0};
    q1.push(start);
    already_visited[start] = true;
    while (!q1.empty())




    {
        int currentCity = q1.front();
        q1.pop();
        // Traverse road connections with limit
        int t_roads = 0;
        Node* curr_road = road_conn[currentCity];
        while (curr_road != nullptr)
        {
            int parosi_city = curr_road->data;





            if (!already_visited[parosi_city])
            {
                q1.push(parosi_city);
                already_visited[parosi_city] = true;
                din[parosi_city] = din[currentCity] + 1;
                t_roads++;
            }
            curr_road = curr_road->next;
            // Break if the road limit is reached
            if (t_roads >= 6)
            {
                break;
            }
        }
        // Traverse aerial connections




        Node* curr_air = aerial_conn[currentCity];
        while (curr_air != nullptr)
        {
            int parosi_city = curr_air->data;
            // The traveler reaches the other destination of the aerial route by the end of the same day
            if (!already_visited[parosi_city])
            {
                q1.push(parosi_city);
                already_visited[parosi_city] = true;
                din[parosi_city] = din[currentCity] + 1;
            }
            curr_air = curr_air->next;
        }
    }




    int final = din[end];
    delete[] already_visited;
    delete[] din;
    already_visited = nullptr;
    din = nullptr;
    return final;
}







//``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
//```````````````````````````````````````````````````````` INT MAIN `````````````````````````````````````````````````````````````
//````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
int main()
{
    cout << "\033[38;5;85m";
    cout << "\t\t\t\t\t\t_________________" << endl;
    cout << "\t\t\t\t\t\t|     MENU      |" << endl;
    cout << "\t\t\t\t\t\t|_______________|" << endl;
    cout << endl;
    cout << "____________________________" << endl;
    cout << "|   Select From The List   |" << endl;
    cout << "|__________________________|" << endl;
    cout << "|    1: REGISTER           |" << endl;
    cout << "|__________________________|" << endl;
    cout << "|    2: LOGIN              |" << endl;
    cout << "|__________________________|" << endl;
    cout << "|    3: EXIT               |" << endl;
    cout << "|__________________________|" << endl;
    cout << endl;
    int choice = 0;
    cout << "Enter: ";
    cin >> choice;
    cin.ignore();





    string user_name = "";
    int user_id = 0;
    string password;
    //Registration ka liya
    if (choice == 1)
    {
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Enter your name    : ";
        getline(cin, user_name);
        cout << endl;
        cout << "Enter your ID      : ";
        while (!(cin >> user_id))
        {
            cout << endl;
            cout << "Enter a valid ID: ";
            cin.clear();
            while (cin.get() != '\n')
            {
                continue;
            }
        }
        cin.ignore();



        cout << endl;
        user u1(user_name, user_id);
        u1.registration();
        system("cls");
        system("pause");
        cout << "____________________________" << endl;
        cout << "|   Select From The List   |" << endl;
        cout << "|__________________________|" << endl;
        cout << "|    1: REGISTER           |" << endl;
        cout << "|__________________________|" << endl;
        cout << "|    2: LOGIN              |" << endl;
        cout << "|__________________________|" << endl;
        cout << "|    3: EXIT               |" << endl;
        cout << "|__________________________|" << endl;
        cout << endl;
        cout << "Enter: ";
        cin >> choice;
        cin.ignore();
    }
    //Login kay liya
    if (choice == 2)
    {
        //goto ka l1
    l1:
        string username, password;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Enter your username: ";
        getline(cin, username);
        cout << endl;
        cout << "Enter your password: ";
        password = read_pass();
        cout << endl;
        user u1;
        //Agr login hta tou wrna else
        if (u1.login(username, password))
        {
            cout << "\t\t\t\t\t_________________________________" << endl;
            cout << "\t\t\t\t\t|   Emergency Travelling Plan   |" << endl;
            cout << "\t\t\t\t\t|_______________________________|" << endl;
            cout << endl << endl;
            //creating Graph




            cout << "______________________" << endl;
            cout << "|   Graph Creation   |" << endl;
            cout << "|____________________|" << endl;
            cout << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            int test_case;
            //Test case
            cout << "Enter The Number Of Test Cases: ";
            while (!(cin >> test_case))
            {
                cout << endl;
                cout << "Enter valid test case         : ";
                cin.clear();
                while (cin.get() != '\n')
                {
                    continue;
                }
            }
            cin.ignore();





            for (int i = 1; i <= test_case; i++)
            {
                cout << endl << endl;
                int t_cities;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cout << "Enter Number Of Total Cities                 : ";
                //Total Cities
                while (!(cin >> t_cities) || t_cities <= 0)
                {
                    cout << endl;
                    cout << "Enter number of total cities (greater than 0): ";
                    cin.clear();
                    while (cin.get() != '\n')
                    {
                        continue;
                    }
                }
                Graph g1(t_cities);
                cout << endl;
                int aerial_routes;
                //Aerial Routes
                do
                {
                    cout << endl;
                    cout << "Enter Number Of Aerial Routes                : ";
                    while (!(cin >> aerial_routes) || aerial_routes <= 0 || aerial_routes > t_cities)
                    {
                        cout << endl;
                        cout << "Enter aerial routes b/w (1 to " << t_cities << ")             : ";
                        cin.clear();
                        while (cin.get() != '\n')
                        {
                            continue;
                        }
                    }
                } while (aerial_routes > t_cities);
                cout << endl;
                //Origin and designation of aerials
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                for (int j = 0; j < aerial_routes; ++j)
                {
                    int origin, destination;
                    cout << "Enter Origin (O) & Destination (D) through Aerials (O & D): ";
                    while (!(cin >> origin >> destination) || cin.peek() != '\n')
                    {
                        cout << endl;
                        cout << "Enter valid origin & destination (two numbers separated by a space): ";
                        cin.clear();
                        while (cin.get() != '\n')
                        {
                            continue;
                        }
                    }
                    cout << endl;
                    g1.add_aerial(origin, destination);
                }
                cout << endl;



                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                g1.graph_print();
                cout << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                //Traversal
                cout << "___________________" << endl;
                cout << "|  BFS Traversal  |" << endl;
                cout << "|_________________|" << endl;
                cout << endl;
                g1.BFS_Graph(g1);
                cout << endl << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cout << "_________________________________________________________" << endl;
                cout << "|  Minimum Days Requied to travel from City 1 to City " << t_cities << " |" << endl;
                cout << "|_______________________________________________________|" << endl;
                int origin = 0;
                int N = t_cities - 1;//It is the designation
                int min_days = g1.minDaysToTravel(origin, N);
                cout << "Minimum days required to travel from City 1 to City " << t_cities << ":  " << min_days << endl;
            }
        }
        //Wapis l1 sy agy
        else
        {
            goto l1;
        }
    }
}
















/* All code in one cpp and with perfect spaces

#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include <conio.h>//For Getch for security, hiding password
using namespace std;
//``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
//````````````````````````````````````````````````````````````` CLASS USER ````````````````````````````````````````````````````````````
//``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
class user
{
private:
    string name;
    long long int id;
    string password;
public:
    user();
    user(string n, int i);
    void setName(string newName);
    void setId(int newId);
    void setPassword(string newPassword);
    string getName() const;
    int getId() const;
    string getPassword() const;
    bool check_reg_password(const string& password);
    string get_password();
    void registration();
    bool check_username(string s);
    bool login(string username, string pass);
};
// DEFAULT CONSTRUCTOR
user::user()
{
    name = "";
    id = 0;;
    password = "";
}
// PARAMETERIZED CONSTRUCTOR
user::user(string n, int i)
{
    this->name = n;
    this->id = i;
}
//`````````` SETTERS  ```````
void user::setName(string newName)
{
    name = newName;
}

void user::setId(int newId)
{
    id = newId;
}

void user::setPassword(string newPassword)
{
    password = newPassword;
}

//```````` GETTERS ```````````
string user::getName() const
{
    return name;
}


int user::getId() const
{
    return id;
}

string user::getPassword() const
{
    return password;
}

//``````````` CHECKING PASSWORD ```````````````
bool user::check_reg_password(const string& password)
{
    int length = password.length();

    if (length < 6)
    {
        cout << "Enter a password of length 6 or above " << endl << endl;
        return false;
    }
    else
    {
        bool upper_case = false;
        bool lower_case = false;
        bool digits = false;
        bool special = false;

        for (int i = 0; i < length; i++)
        {
            //Assci Apply ki yaha aur phr compare
            if (password[i] >= 65 && password[i] < 91)
            {
                upper_case = true;
            }

            if (password[i] >= 97 && password[i] <= 122)
            {
                lower_case = true;
            }

            if ((password[i] >= 33 && password[i] <= 47) || (password[i] >= 58 && password[i] <= 64) || (password[i] >= 91 && password[i] <= 96) || (password[i] >= 123 && password[i] <= 126))
            {
                special = true;
            }

            if (password[i] >= 48 && password[i] <= 57)
            {
                digits = true;
            }
        }

        if (upper_case && lower_case && digits && special)
        {
            return true;
        }
        else
        {
            cout << "Password must contain at least one uppercase letter, one lowercase letter, one digit, and one special character." << endl << endl;
            return false;
        }
    }
}
//```````````` GET PASSWORD  ````````````
string user::get_password()
{
    string password;
    while (true)
    {
        cout << "Enter the password: ";
        getline(cin, password);
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
        if (check_reg_password(password))
        {
            return password;
        }
    }
}
//``````````````` REGISTRATION ``````
void user::registration()
{
    //username stored in username.txt
    ofstream file_user("username.txt");
    if (file_user.is_open())
    {
        file_user << name << endl;
        file_user.close();
    }
    password = get_password();
    //password ko password.txt ma store
    ofstream file_pass("password.txt");
    if (file_pass.is_open())
    {
        file_pass << password << endl;
        file_pass.close();
    }
}
//```````````` CHECK USERNAME  ````````````````
bool user::check_username(string s)
{
    ifstream file("username.txt");
    if (file.is_open())
    {
        string file_username;
        while (getline(file, file_username))
        {
            if (s == file_username)
            {
                file.close();
                return true;
            }
        }
        file.close();
    }
    else
    {
        cout << "Failed to open the username file." << endl;
    }
    return false;
}

//`````````````` `` LOGIN ``````````````````````
bool user::login(string username, string pass)
{
    ifstream user_file("username.txt");
    ifstream pass_file("password.txt");

    if (!user_file.is_open() || !pass_file.is_open())
    {
        cout << "\t\t\t\t\tError opening username or password file." << endl;
        return false;
    }

    string file_username, file_password;
    bool found = false;

    while (getline(user_file, file_username) && getline(pass_file, file_password))
    {
        if (username == file_username && pass == file_password)
        {
            cout << endl;
            cout << "\t\t\t\t\tLogin Successful!!" << endl;
            found = true;
            system("cls");
            system("pause");
        }
    }
    user_file.close();
    pass_file.close();
    if (!found)
    {
        cout << endl;
        cout << "\t\t\t\tIncorrect username or password. Login failed :( " << endl;
    }
    return found;
}
//``````````````````` Read Password ```````````````````
string read_pass()
{
    char check;
    string pwd;
    for (;;)
    {
        check = _getch();
        if (check == '\r')
        {
            break;
        }
        if (check == '\b')
        {
            if (!pwd.empty())
            {
                pwd.pop_back();
                cout << "\b \b" << endl;
            }
        }
        else
        {
            pwd.push_back(check);
            cout << '*';
        }
    }
    return pwd;
}
//``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
//```````````````````````````````````````````````````````````` CLASS NODE ``````````````````````````````````````````````````````
//``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
struct Node
{
    Node* next;
    int data;
    Node(int d)
    {
        data = d;
        next = nullptr;
    }
};
//```````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
//```````````````````````````````````````````````````````````` CLASS GRAPH ``````````````````````````````````````````````````````
//```````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
class Graph
{
    int total_cities;
    Node** road_conn;
    Node** aerial_conn;
public:
    Graph();
    Graph(int c);
    void add_road(int origin, int destination);
    void add_aerial(int o, int d);
    void graph_print();
    void BFS(int start, bool* visited, Graph& g);
    void BFS_Graph(Graph& g);
    int minDaysToTravel(int start, int end);
};

// Default Constructor
Graph::Graph()
{
    total_cities = 0;
    road_conn = nullptr;
    aerial_conn = nullptr;
}
// Parameterized Constructor
Graph::Graph(int c)
{
    total_cities = c;
    road_conn = new Node * [total_cities];
    aerial_conn = new Node * [total_cities];
    for (int i = 0; i < total_cities; i++)
    {
        road_conn[i] = nullptr;
        aerial_conn[i] = nullptr;
    }
}
// Add Road
void Graph::add_road(int origin, int destination)
{
    int t_roads = 0;
    Node* curr_road = road_conn[origin];
    while (curr_road != nullptr)
    {
        t_roads++;
        curr_road = curr_road->next;
    }
    if (t_roads >= 6)
    {
        cout << "Cannot add more road connections for city " << origin << ". Limit reached." << endl;
        return;
    }

    // Add road connection
    Node* new_node = new Node(destination);
    new_node->next = road_conn[origin];
    road_conn[origin] = new_node;
}
// Add Aerial
void Graph::add_aerial(int o, int d)
{
    Node* new_node = new Node(d);
    new_node->next = aerial_conn[o];
    aerial_conn[o] = new_node;
}
// Graph printing
void Graph::graph_print()
{
    for (int i = 0; i < total_cities; i++)
    {
        //Aerial
        cout << "Aerial connection of city " << i << ": ";
        Node* aerial_current = aerial_conn[i];
        while (aerial_current != nullptr)
        {
            cout << aerial_current->data << " ";
            aerial_current = aerial_current->next;
            if (aerial_current != nullptr)
            {
                //Using this arrow when there are 2 cities in same they use arrow
                cout << "--> ";
            }
        }
        cout << endl;
    }
}
// Breadth-First Search Traversal
void Graph::BFS(int start, bool* visited, Graph& g)
{
    queue<int> q1;
    q1.push(start);
    visited[start] = true;
    while (!q1.empty())
    {
        int curr_city = q1.front();
        q1.pop();
        cout << curr_city << " ";
        // Traverse road connections
        Node* curr_road = g.road_conn[curr_city];
        while (curr_road != nullptr)
        {
            int parosi_city = curr_road->data;
            if (!visited[parosi_city])
            {
                q1.push(parosi_city);
                visited[parosi_city] = true;
            }
            curr_road = curr_road->next;
        }

        // Traverse aerial connections
        Node* curr_air = g.aerial_conn[curr_city];
        while (curr_air != nullptr)
        {
            int parosi_city = curr_air->data;
            // The traveler reaches the other destination of the aerial route by the end of the same day
            if (!visited[parosi_city])
            {
                q1.push(parosi_city);
                visited[parosi_city] = true;
            }
            curr_air = curr_air->next;
        }
    }
}
//BFS Graph
void Graph::BFS_Graph(Graph& g)
{
    int total_cities = g.total_cities;
    bool* already_visited = new bool[total_cities] {false};

    for (int i = 0; i < total_cities; ++i)
    {
        if (!already_visited[i])
        {
            BFS(i, already_visited, g);
        }
    }
    delete[] already_visited;
    cout << endl;
}

// Function to find the minimum days using BFS with road limit
int Graph::minDaysToTravel(int start, int end)
{
    queue<int> q1;
    bool* already_visited = new bool[total_cities] {false};
    int* din = new int[total_cities] {0};
    q1.push(start);
    already_visited[start] = true;
    while (!q1.empty())
    {
        int currentCity = q1.front();
        q1.pop();
        // Traverse road connections with limit
        int t_roads = 0;
        Node* curr_road = road_conn[currentCity];
        while (curr_road != nullptr)
        {
            int parosi_city = curr_road->data;
            if (!already_visited[parosi_city])
            {
                q1.push(parosi_city);
                already_visited[parosi_city] = true;
                din[parosi_city] = din[currentCity] + 1;
                t_roads++;
            }
            curr_road = curr_road->next;
            // Break if the road limit is reached
            if (t_roads >= 6)
            {
                break;
            }
        }
        // Traverse aerial connections
        Node* curr_air = aerial_conn[currentCity];
        while (curr_air != nullptr)
        {
            int parosi_city = curr_air->data;
            // The traveler reaches the other destination of the aerial route by the end of the same day
            if (!already_visited[parosi_city])
            {
                q1.push(parosi_city);
                already_visited[parosi_city] = true;
                din[parosi_city] = din[currentCity] + 1;
            }
            curr_air = curr_air->next;
        }
    }
    int final = din[end];
    delete[] already_visited;
    delete[] din;
    already_visited = nullptr;
    din = nullptr;
    return final;
}

//``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
//```````````````````````````````````````````````````````` INT MAIN `````````````````````````````````````````````````````````````
//````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
int main()
{
    cout << "\033[38;5;85m";
    cout << "\t\t\t\t\t\t_________________" << endl;
    cout << "\t\t\t\t\t\t|     MENU      |" << endl;
    cout << "\t\t\t\t\t\t|_______________|" << endl;
    cout << endl;
    cout << "____________________________" << endl;
    cout << "|   Select From The List   |" << endl;
    cout << "|__________________________|" << endl;
    cout << "|    1: REGISTER           |" << endl;
    cout << "|__________________________|" << endl;
    cout << "|    2: LOGIN              |" << endl;
    cout << "|__________________________|" << endl;
    cout << "|    3: EXIT               |" << endl;
    cout << "|__________________________|" << endl;
    cout << endl;
    int choice = 0;
    cout << "Enter: ";
    cin >> choice;
    cin.ignore();
    string user_name = "";
    int user_id = 0;
    string password;
    //Registration ka liya
    if (choice == 1)
    {
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Enter your name    : ";
        getline(cin, user_name);
        cout << endl;
        cout << "Enter your ID      : ";
        while (!(cin >> user_id))
        {
            cout << endl;
            cout << "Enter a valid ID: ";
            cin.clear();
            while (cin.get() != '\n')
            {
                continue;
            }
        }
        cin.ignore();
        cout << endl;
        user u1(user_name, user_id);
        u1.registration();
        system("cls");
        system("pause");
        cout << "____________________________" << endl;
        cout << "|   Select From The List   |" << endl;
        cout << "|__________________________|" << endl;
        cout << "|    1: REGISTER           |" << endl;
        cout << "|__________________________|" << endl;
        cout << "|    2: LOGIN              |" << endl;
        cout << "|__________________________|" << endl;
        cout << "|    3: EXIT               |" << endl;
        cout << "|__________________________|" << endl;
        cout << endl;
        cout << "Enter: ";
        cin >> choice;
        cin.ignore();
    }
    //Login kay liya
    if (choice == 2)
    {
        //goto ka l1
    l1:
        string username, password;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Enter your username: ";
        getline(cin, username);
        cout << endl;
        cout << "Enter your password: ";
        password = read_pass();
        cout << endl;
        user u1;
        //Agr login hta tou wrna else
        if (u1.login(username, password))
        {
            cout << "\t\t\t\t\t_________________________________" << endl;
            cout << "\t\t\t\t\t|   Emergency Travelling Plan   |" << endl;
            cout << "\t\t\t\t\t|_______________________________|" << endl;
            cout << endl << endl;
            //creating Graph
            cout << "______________________" << endl;
            cout << "|   Graph Creation   |" << endl;
            cout << "|____________________|" << endl;
            cout << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            int test_case;
            //Test case
            cout << "Enter The Number Of Test Cases: ";
            while (!(cin >> test_case))
            {
                cout << endl;
                cout << "Enter valid test case         : ";
                cin.clear();
                while (cin.get() != '\n')
                {
                    continue;
                }
            }
            cin.ignore();
            for (int i = 1; i <= test_case; i++)
            {
                cout << endl << endl;
                int t_cities;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cout << "Enter Number Of Total Cities                 : ";
                //Total Cities
                while (!(cin >> t_cities) || t_cities <= 0)
                {
                    cout << endl;
                    cout << "Enter number of total cities (greater than 0): ";
                    cin.clear();
                    while (cin.get() != '\n')
                    {
                        continue;
                    }
                }
                Graph g1(t_cities);
                cout << endl;
                int aerial_routes;
                //Aerial Routes
                do
                {
                    cout << endl;
                    cout << "Enter Number Of Aerial Routes                : ";
                    while (!(cin >> aerial_routes) || aerial_routes <= 0 || aerial_routes > t_cities)
                    {
                        cout << endl;
                        cout << "Enter aerial routes b/w (1 to " << t_cities << ")             : ";
                        cin.clear();
                        while (cin.get() != '\n')
                        {
                            continue;
                        }
                    }
                } while (aerial_routes > t_cities);
                cout << endl;
                //Origin and designation of aerials
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                for (int j = 0; j < aerial_routes; ++j)
                {
                    int origin, destination;
                    cout << "Enter Origin (O) & Destination (D) through Aerials (O & D): ";
                    while (!(cin >> origin >> destination) || cin.peek() != '\n')
                    {
                        cout << endl;
                        cout << "Enter valid origin & destination (two numbers separated by a space): ";
                        cin.clear();
                        while (cin.get() != '\n')
                        {
                            continue;
                        }
                    }
                    cout << endl;
                    g1.add_aerial(origin, destination);
                }
                cout << endl;

                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                g1.graph_print();
                cout << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                //Traversal
                cout << "___________________" << endl;
                cout << "|  BFS Traversal  |" << endl;
                cout << "|_________________|" << endl;
                cout << endl;
                g1.BFS_Graph(g1);
                cout << endl << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cout << "_________________________________________________________" << endl;
                cout << "|  Minimum Days Requied to travel from City 1 to City " << t_cities << " |" << endl;
                cout << "|_______________________________________________________|" << endl;
                int origin = 0;
                int N = t_cities - 1;//It is the designation
                int min_days = g1.minDaysToTravel(origin, N);
                cout << "Minimum days required to travel from City 1 to City " << t_cities << ":  " << min_days << endl;
            }
        }
        //Wapis l1 sy agy
        else
        {
            goto l1;
        }
    }
}



*/