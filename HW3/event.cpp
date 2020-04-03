#include <iostream>
#include <string>
using namespace std; //COMMENT OUT LATER

//Every Event has a name
class Event {
public:
    Event(string name) {
        m_name = name;
    }
    virtual ~Event() {} //Is specialised in subclasses 

    string name() const { //Returns name of event
        return m_name;
    }
    virtual bool isSport() const { //Default returns true, since most events are sport events
        return true;
    }
    virtual string need() const = 0; //Returns what the event needs, diff based on event so pure virtual
private:
    string m_name;
};

class BasketballGame : public Event {
public:
    BasketballGame(string name) : Event(name) {}
    virtual ~BasketballGame() { //Add to base class destructor
        cout << "Destroying the " << Event::name() << " basketball game" << endl;
    }
    virtual string need() const { //Redef pure virtual need in Event
        return "hoops";
    }
};

class HockeyGame : public Event {
public:
    HockeyGame(string name) : Event(name) {}
    virtual ~HockeyGame() { //Add to base class destructor
        cout << "Destroying the " << Event::name() << " hockey game" << endl;
    }

    virtual string need() const { //Redef pure virtual need in Event
        return "ice";
    }
};

class Concert : public Event {
public:
    Concert(string name, string genre) : Event(name) {
        m_genre = genre;
    }
    virtual ~Concert() { //Add genre to base class destructor
        cout << "Destroying the " << Event::name() << " " << this->m_genre << " concert" << endl;
    }

    virtual string need() const { //Redef pure virtual need in Event
        return "a stage";
    }
    virtual bool isSport() const { //Not a sport, so redef pure virtual need in event
        return false;
    }
private:
    string m_genre;
};


/*void display(const Event* e)
{
    cout << e->name() << ": ";
    if (e->isSport())
        cout << "(sport) ";
    cout << "needs " << e->need() << endl;
}

int main()
{
    Event* events[4];
    events[0] = new BasketballGame("Lakers vs. Suns");
    // Concerts have a name and a genre.
    events[1] = new Concert("Banda MS", "banda");
    events[2] = new Concert("KISS", "hard rock");
    events[3] = new HockeyGame("Kings vs. Flames");

    cout << "Here are the events." << endl;
    for (int k = 0; k < 4; k++)
        display(events[k]);

    // Clean up the events before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete events[k];
} */