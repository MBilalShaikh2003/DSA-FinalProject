#include <iostream>
#include <string>
using namespace std;

struct Record {
    string name;
    Record* next;
    Record* prev;
};

struct FavRecord {
    string name;
    FavRecord* next;
};

struct Rating {
    float rate;
    string sname;
    Rating* next;
};

Rating* head1 = NULL;
FavRecord* front =  NULL;
FavRecord* rear =  NULL;
int count = 0;

void insertMusic(Record** head) {
    Record* ptr = new Record;
    cout << "Enter Music Name: ";
    cin >> ptr->name;
    ptr->next =  NULL;
    ptr->prev =  NULL;

    if (*head ==  NULL) {
        *head = ptr;
        (*head)->next = *head;
        (*head)->prev = *head;
    } else {
        Record* last = (*head)->prev;
        last->next = ptr;
        ptr->prev = last;
        ptr->next = *head;
        (*head)->prev = ptr;
    }
    count++;
}

void displayMusic(Record** head) {
    if (*head ==  NULL) {
        cout << "Music list is empty" << endl;
        return;
    }
    Record* temp = *head;
    do {
        cout << "Music: " << temp->name << endl;
        temp = temp->next;
    } while (temp != *head);
}

void deleteMusic(Record** head) {
    if (*head ==  NULL) {
        cout << "Music list is empty" << endl;
        return;
    }

    string x;
    cout << "Enter the name of the music to remove: ";
    cin >> x;

    Record* curr = *head;
    Record* prev =  NULL;

    do {
        if (curr->name == x) {
            if (curr == *head) {
                *head = curr->next;
            }
            if (curr->next) {
                curr->next->prev = curr->prev;
            }
            if (curr->prev) {
                curr->prev->next = curr->next;
            }
            delete curr;
            count--;
            cout << "Music \"" << x << "\" deleted" << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != *head);

    cout << "Music \"" << x << "\" not found" << endl;
}

void playMusic(Record** head) {
    if (*head ==  NULL) {
        cout << "Music list is empty" << endl;
        return;
    }
    cout << "Now playing: " << (*head)->name << endl;
}

void playNext(Record** head) {
    if (*head ==  NULL) {
        cout << "Music list is empty" << endl;
        return;
    }
    *head = (*head)->next;
    cout << "Now playing: " << (*head)->name << endl;
}

void playPrev(Record** head) {
    if (*head ==  NULL) {
        cout << "Music list is empty" << endl;
        return;
    }
    *head = (*head)->prev;
    cout << "Now playing: " << (*head)->name << endl;
}

void emptyList(Record** head) {
    if (*head ==  NULL) {
        cout << "Music list is already empty" << endl;
        return;
    }
    Record* curr = *head;
    while (curr->next != *head) {
        Record* temp = curr->next;
        delete curr;
        curr = temp;
    }
    delete curr;
    *head =  NULL;
    cout << "Music list emptied" << endl;
    count = 0;
}

void totalSongs() {
    cout << "Total Songs in PlayList are " << count << endl;
}

void searchMusic(Record** head) {
    if (*head ==  NULL) {
        cout << "Music list is empty" << endl;
        return;
    }

    string x;
    cout << "Enter the name of the music to search: ";
    cin >> x;

    Record* curr = *head;
    do {
        if (curr->name == x) {
            cout << "Music \"" << x << "\" found" << endl;
            return;
        }
        curr = curr->next;
    } while (curr != *head);

    cout << "Music \"" << x << "\" not found" << endl;
}

void addToFavorite(Record** head) {
    if (*head ==  NULL) {
        cout << "Music list is empty" << endl;
        return;
    }

    string x;
    cout << "Enter the name of Music to add to favorites: ";
    cin >> x;
    Record* curr = *head;
    do {
        if (curr->name == x) {
            FavRecord* node = new FavRecord;
            node->name = x;
            node->next =  NULL;
            if (front ==  NULL) {
                front = rear = node;
            } else {
                rear->next = node;
                rear = node;
            }
            cout << "Music \"" << x << "\" added to favorites" << endl;
            return;
        }
        curr = curr->next;
    } while (curr != *head);
    cout << "Music \"" << x << "\" not found" << endl;
}

void showFavorite() {
    if (front ==  NULL) {
        cout << "Queue Empty Of Favorite Songs" << endl;
        return;
    }
    FavRecord* temp = front;
    cout << "Favorite Songs:" << endl;
    while (temp !=  NULL) {
        cout << temp->name << endl;
        temp = temp->next;
    }
}

bool search(Record** head, string x) {
    Record* curr = *head;
    do {
        if (curr->name == x) {
            return true;
        }
        curr = curr->next;
    } while (curr != *head);
    return false;
}

void rateSong(Record** head) {
    if (*head ==  NULL) {
        cout << "Music list is empty" << endl;
        return;
    }
    string songname;
    cout << "Enter Name of the Song: " << endl;
    cin >> songname;
    bool x = search(head, songname);
    if (x) {
        float rate;
        cout << "Enter Rating of the Song " << songname << " between 1.0 to 10.0: ";
        cin >> rate;
        if (rate >= 1.0 && rate <= 10.0) {
            Rating* newNode = new Rating;
            newNode->sname = songname;
            newNode->rate = rate;
            newNode->next =  NULL;

            if (head1 ==  NULL) {
                head1 = newNode;
            } else {
                Rating* temp = head1;
                while (temp->next !=  NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
            cout << "Rating for the song " << songname << " is " << rate << endl;
        } else {
            cout << "Invalid rating! Rating should be between 1.0 and 10.0." << endl;
        }
    } else {
        cout << "This Song is not in the PlayList" << endl;
    }
}

void viewRating() {
    if (head1 ==  NULL) {
        cout << "No Songs Have Been Rated" << endl;
        return;
    }
    Rating* temp = head1;
    cout << "Rated Songs:" << endl;
    while (temp !=  NULL) {
        cout << temp->sname << ": " << temp->rate << endl;
        temp = temp->next;
    }
}

int main() {
    Record* head =  NULL;
    int choice;

    do {
        cout << "\nEnter 1 to Add Music\n"
             << "Enter 2 to Display Music List\n"
             << "Enter 3 to Delete a Music\n"
             << "Enter 4 to Play a Music\n"
             << "Enter 5 to Play Next Music\n"
             << "Enter 6 to Play Previous Music\n"
             << "Enter 7 to Empty Music List\n"
             << "Enter 8 to Get Total Songs In Music List\n"
             << "Enter 9 to Search The Songs By Name In Music List\n"
             << "Enter 10 to Add to Favorites\n"
             << "Enter 11 to Display Favorites\n"
             << "Enter 12 to Rate a Song\n"
             << "Enter 13 to View Rating of a Song\n"
             << "Enter 0 to Exit\n"
             << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                insertMusic(&head);
                break;
            case 2:
                displayMusic(&head);
                break;
            case 3:
                deleteMusic(&head);
                break;
            case 4:
                playMusic(&head);
                break;
            case 5:
                playNext(&head);
                break;
            case 6:
                playPrev(&head);
                break;
            case 7:
                emptyList(&head);
                break;
            case 8:
                totalSongs();
                break;
            case 9:
                searchMusic(&head);
                break;
            case 10:
                addToFavorite(&head);
                break;
            case 11:
                showFavorite();
                break;
            case 12:
                rateSong(&head);
                break;
            case 13:
                viewRating();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 0);

    return 0;
}

