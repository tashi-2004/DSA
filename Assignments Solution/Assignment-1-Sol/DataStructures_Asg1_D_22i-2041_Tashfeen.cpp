/*
Tashfeen Abbasi
i22-2041
DS-D
Assignment 1
Question 1
For ctime I have taken help.
*/
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
struct Post
{
public:
    int ID;
    string text;
    string time_stamp;
    Post* next;
    Post();
    Post(string t);
};
//``````````````````````````````````````````` POST ```````````````````````````````````````
Post::Post()
{
    ID = 0;
    text = "";
    time_stamp = "";
    next = nullptr;
}
Post::Post(string t)
{
    srand(time(0));
    // ID = rand() % 9000 + 1000; Agr aisay kro ga tou wo sb ko 1 hae random number generate karay ga
    text = t;
    // time
    time_t curr;
    struct tm timeInfo;
    time(&curr);
    localtime_s(&timeInfo, &curr);
    char timestampBuffer[20];
    strftime(timestampBuffer, sizeof(timestampBuffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
    time_stamp = timestampBuffer;
    next = nullptr;
}
//`````````````````````````````````````````` FEED `````````````````````````````````
class Feed
{
    Post* head;
public:
    Feed();
    void insert_post(Post p1);
    void display_feed();
    bool edited_feed(int id, string s);
    void search_post(string s);
    void delete_post(int id);
    void display_latest();
    void display_oldest();
};
//```````````````````````````````````````` CONSTRUCTOR ``````````````````````````````
Feed::Feed()
{
    head = nullptr;
}
//``````````````````````````````````````` INSERT POST ````````````````````````````````
void Feed::insert_post(Post p1)
{
    Post* newPost = new Post(p1);
    if (!head)
    {
        newPost->next = head;
        head = newPost;
    }
    else
    {
        Post* curr = head;
        while (curr->next)
        {
            curr = curr->next;
        }
        newPost->next = curr->next;
        curr->next = newPost;
    }
}
//```````````````````````````````````````` DISPLAY FEED ``````````````````````````````````
void Feed::display_feed()
{
    Post* current = head;
    while (current != nullptr)
    {
        cout << "Post ID  : " << current->ID << endl;
        cout << "Text     : " << current->text << endl;
        cout << "Timestamp: " << current->time_stamp << endl;
        current = current->next;
        cout << endl;
    }
}
//````````````````````````````````````````` EDITED POST `````````````````````````````````
bool Feed::edited_feed(int id, string s)
{
    Post* pre = nullptr;
    Post* curr = head;
    while (curr != nullptr && curr->ID != id)
    {
        pre = curr;
        curr = curr->next;
    }
    if (curr == nullptr)
    {
        cout << "Post with ID " << id << " not found in the list." << endl << endl;

        return false;

    }
    curr->text = s;
    //time
    time_t currTime;
    struct tm timeInfo;
    time(&currTime);
    localtime_s(&timeInfo, &currTime);
    char timestampBuffer[20];
    strftime(timestampBuffer, sizeof(timestampBuffer), "%Y-%m-%d %H:%M:%S", &timeInfo);


    curr->time_stamp = timestampBuffer;
    if (pre != nullptr)
    {
        pre->next = curr->next;
    }
    else
    {
        head = curr->next;
    }
    Post* newPrev = nullptr;
    Post* newCurr = head;
    while (newCurr != nullptr && newCurr->time_stamp < curr->time_stamp)
    {
        newPrev = newCurr;
        newCurr = newCurr->next;
    }
    if (newPrev != nullptr)
    {
        newPrev->next = curr;
    }
    else
    {
        head = curr;
    }
    curr->next = newCurr;
    return true;
}
//````````````````````````````````````` SEARCH ````````````````````````````````````````````
void Feed::search_post(string s)
{
    Post* curr = head;
    bool found = false;
    while (curr)
    {
        if (curr->text == s)
        {
            found = true;
            cout << "Post ID  : " << curr->ID << endl;
            cout << "Text     : " << curr->text << endl;
            cout << "Timestamp: " << curr->time_stamp << endl;
            cout << endl;
        }
        curr = curr->next;
    }
    if (!found)
    {
        cout << "Text " << s << " not found in any posts." << endl << endl;
    }
    cout << "---------------------------------------------" << endl;
    return;
}

//``````````````````````````````````````` DELETE ``````````````````````````````````````````````
void Feed::delete_post(int id)
{
    Post* pre = nullptr;
    Post* curr = head;
    while (curr->next != nullptr && curr->ID != id)
    {
        pre = curr;
        curr = curr->next;
    }
    if (curr == nullptr)
    {
        cout << "Post of " << id << " not found :) " << endl;
        return;
    }
    if (pre != nullptr)
    {
        pre->next = curr->next;
    }
    else
    {
        head = curr->next;
    }
    delete curr;
    cout << "Post of ID " << id << "  is deleted :) " << endl << endl;
}
//``````````````````````````````````````````` LATEST ``````````````````````````````````````
void Feed::display_latest()
{
    int total_posts = 0;
    Post* curr = head;
    while (curr != nullptr)
    {
        total_posts++;
        curr = curr->next;
    }

    Post** posts = new Post * [total_posts];
    curr = head;
    int index = 0;
    while (curr != nullptr)
    {
        posts[index++] = curr;
        curr = curr->next;
    }

    for (int i = total_posts - 1; i >= 0; i--)
    {
        cout << "Post ID  : " << posts[i]->ID << endl;
        cout << "Text     : " << posts[i]->text << endl;
        cout << "Timestamp: " << posts[i]->time_stamp << endl;
        cout << endl;
    }

    delete[] posts;
}
//``````````````````````````````````````````````` OLDEST `````````````````````````````````````
void Feed::display_oldest()
{
    int total_posts = 0;
    Post* curr = head;
    while (curr != nullptr)
    {
        total_posts++;
        curr = curr->next;
    }

    Post** posts = new Post * [total_posts];
    curr = head;
    int index = 0;
    while (curr != nullptr)
    {
        posts[index++] = curr;
        curr = curr->next;
    }

    for (int i = 0; i < total_posts; i++)
    {
        cout << "Post ID  : " << posts[i]->ID << endl;
        cout << "Text     : " << posts[i]->text << endl;
        cout << "Timestamp: " << posts[i]->time_stamp << endl;
        cout << endl;
    }

    delete[] posts;
}
//```````````````````````````````````````````` USER MAIN ```````````````````````````````````````
int main()
{
    cout << "\033[1;36m";
    cout << "\t\t\t\t\t_____________________" << endl;
    cout << "\t\t\t\t\t| Social Media Feed |" << endl;
    cout << "\t\t\t\t\t|___________________|" << endl;
    cout << endl;
    Feed f1;
    Post p1("Hello World");
    Post p2("How is everyone doing today");
    Post p3("Oh World");
    Post p4("Nice World");
    Post p5("No to World");
    Post p6("Yes to World");
    Post p7("Bye to World");
    Post p8("Good Bye to World");
    Post p9("I should be going, see you guys later");
    Post p10("Bye");

    p1.ID = rand() % 9000 + 1000;
    p2.ID = rand() % 9000 + 1000;
    p3.ID = rand() % 9000 + 1000;
    p4.ID = rand() % 9000 + 1000;
    p5.ID = rand() % 9000 + 1000;
    p6.ID = rand() % 9000 + 1000;
    p7.ID = rand() % 9000 + 1000;
    p8.ID = rand() % 9000 + 1000;
    p9.ID = rand() % 9000 + 1000;
    p10.ID = rand() % 9000 + 1000;
    f1.insert_post(p1);
    cout << "---------------------------------------------------" << endl;
    f1.insert_post(p2);
    f1.insert_post(p3);
    f1.insert_post(p4);
    f1.insert_post(p5);
    f1.insert_post(p6);
    f1.insert_post(p7);
    f1.insert_post(p8);
    f1.insert_post(p9);
    f1.insert_post(p10);
    f1.display_feed();
    cout << "---------------------------------------------------" << endl;
    int id;
    cout << "Enter the ID of the post to be edited: ";
    cin >> id;
    cin.ignore();
    cout << endl;
    string a;
    cout << "Enter the text for your edited post: ";
    getline(cin, a);
    cout << endl;
    cout << "---------------------------------------------------" << endl;
    f1.edited_feed(id, a);
    f1.display_feed();
    cout << "---------------------------------------------------" << endl;
    string t;
    cout << "Enter the text you want to search: ";
    getline(cin, t);
    cout << endl;
    cout << "---------------------------------------------------" << endl;
    f1.search_post(t);
    f1.display_feed();
    cout << "---------------------------------------------------" << endl;
    int deleted;
    cout << "Enter the ID you want to delete: ";
    cin >> deleted;
    cin.ignore();
    f1.delete_post(deleted);
    f1.display_feed();
    cout << "---------------------------------------------------" << endl;
    cout << "________________________" << endl;
    cout << "| Posts (Latest first) |" << endl;
    cout << "|______________________|" << endl;
    cout << endl;
    cout << " " << endl;
    f1.display_latest();

    cout << "---------------------------------------------------" << endl;
    cout << "________________________" << endl;
    cout << "| Posts (Oldest first) |" << endl;
    cout << "|______________________|" << endl;
    cout << endl;
    f1.display_oldest();

    return 0;
}
//```````````````````````````````````````````` HARDCODE MAIN ```````````````````````````````````````
//int main()
//{
//    cout << "\033[1;36m";
//    cout << "\t\t\t\t\t_____________________" << endl;
//    cout << "\t\t\t\t\t| Social Media Feed |" << endl;
//    cout << "\t\t\t\t\t|___________________|" << endl;
//    cout << endl;
//    Feed f1;
//    Post p1("Hello World");
//    Post p2("How is everyone doing today");
//    Post p3("Oh World");
//    Post p4("Nice World");
//    Post p5("No to World");
//    Post p6("Yes to World");
//    Post p7("Bye to World");
//    Post p8("Good Bye to World");
//    Post p9("I should be going, see you guys later.");
//    Post p10("Bye");
//    p1.ID = rand() % 9000 + 1000;
//    p2.ID = rand() % 9000 + 1000;
//    p3.ID = rand() % 9000 + 1000;
//    p4.ID = rand() % 9000 + 1000;
//    p5.ID = rand() % 9000 + 1000;
//    p6.ID = rand() % 9000 + 1000;
//    p7.ID = rand() % 9000 + 1000;
//    p8.ID = rand() % 9000 + 1000;
//    p9.ID = rand() % 9000 + 1000;
//    p10.ID = rand() % 9000 + 1000;
//    f1.insert_post(p1);
//    cout << "---------------------------------------------------" << endl;
//    f1.insert_post(p2);
//    f1.insert_post(p3);
//    f1.insert_post(p4);
//    f1.insert_post(p5);
//    f1.insert_post(p6);
//    f1.insert_post(p7);
//    f1.insert_post(p8);
//    f1.insert_post(p9);
//    f1.insert_post(p10);
//    cout << "Displaying the entire feed:" << endl;
//    f1.display_feed();
//    cout << "---------------------------------------------------" << endl;
//    string searchKeyword = "World";
//    cout << "Searching for Posts containing the word '" << searchKeyword << "':" << endl;
//    f1.search_post(searchKeyword);
//    int postIdToEdit;
//    cout << "Enter the ID of the post to be edited: ";
//    cin >> postIdToEdit;
//    cin.ignore();
//    string editedText;
//    cout << "Enter the new text for the edited post: ";
//    getline(cin, editedText);
//    cout << "---------------------------------------------------" << endl;
//    f1.edited_feed(postIdToEdit, editedText);
//    cout << "Updated feed:" << endl;
//    f1.display_feed();
//    cout << "---------------------------------------------------" << endl;
//    cout << "Displaying all Posts in chronological order (Oldest first):" << endl;
//    f1.display_oldest();
//    cout << "---------------------------------------------------" << endl;
//    string searchKeywordToDelete = "guys";
//    cout << "Searching for Posts containing the word '" << searchKeywordToDelete << "' to delete:" << endl;
//    f1.search_post(searchKeywordToDelete);
//    int postIdToDelete;
//    cout << "Enter the ID of the post to delete: ";
//    cin >> postIdToDelete;
//    cin.ignore();
//    f1.delete_post(postIdToDelete);
//    cout << "Deleted post with ID " << postIdToDelete << "." << endl;
//    cout << "Updated feed after deletion:" << endl;
//    f1.display_feed();
//    cout << "---------------------------------------------------" << endl;
//    cout << "Displaying all Posts in reverse chronological order (Newest first):" << endl;
//    f1.display_latest();
//    cout << "---------------------------------------------------" << endl;
//
//    return 0;
//}
