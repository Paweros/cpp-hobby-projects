#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

bool won;
bool lost;

bool charinstr (char c, string s)
{
    for (unsigned int i = 0; i < s.length(); i++)
    {
        if (c == s[i]) return 1;
    }
    return 0;
}

class Level
{
private:
    int ht;
    int ln;
    int px;
    int py;
    char* tile;
    string message;
    string commands;
public:
    Level (string file = "")
    {
        bool hasfile = (file != "");
        ifstream fin;
        if (hasfile)
        {
            fin.open(file);
            getline(fin,message);
            fin >> commands;
            fin >> ht;
            fin >> ln;
        }
        else
        {
            ht = 0;
            ln = 0;
        }
        tile = (char*) malloc(ht*ln);
        for (int i = 0; i < ht; i++)
        {
            for (int ii = 0; ii < ln; ii++)
            {
                if(hasfile&&!fin.eof())
                {
                    fin >> tile[ln*i + ii];
                    if (tile[ln*i + ii] == 'P')
                    {
                        tile[ln*i + ii] = '.';
                        px = ii;
                        py = i;
                    }
                }

                else
                    tile[ln*i + ii] = 0;
            }
        }
        fin.close();
    }

    ~Level()
    {
        free(tile);
    }
    void printMessage();

    void printCommands();

    void draw();

    bool fall();

    bool action();

    bool step (bool isBonus);

    bool play();
};

void Level::printMessage()
{
    cout << message << endl;
}

void Level::printCommands()
{
    cout << "Available commands:";
    for(unsigned int i = 0; i < commands.length(); i++)
    {
        cout << " " << commands[i];
        if (i < commands.length()-1) cout << ",";
    }
    cout << endl;
}

void Level::draw ()
{
    for(int i = 0; i < ht; i++)
    {
        cout << endl;
        for(int ii = 0; ii < ln; ii++)
        {
            if (i == py && ii == px)
                cout << "P";
            else
            {
                switch (tile[i*ln+ii])
                {
                    case ('.'):
                    {
                        cout << " ";
                        break;
                    }
                    case ('0'):
                    {
                        cout << (char)176;
                        break;
                    }
                    case ('1'):
                    {
                        cout << (char)178;
                        break;
                    }
                    case ('y'):
                    {
                        cout << "y";
                        break;
                    }
                    case ('W'):
                    {
                        cout << (char)219;
                        break;
                    }
                    case ('>'):
                    {
                        cout << ">";
                        break;
                    }
                    case ('<'):
                    {
                        cout << "<";
                        break;
                    }
                    case ('V'):
                    {
                        cout << "V";
                        break;
                    }
                    case ('^'):
                    {
                        cout << "^";
                        break;
                    }
                    case ('a'):
                    {
                        cout << "a";
                        break;
                    }
                    case ('+'):
                    {
                        cout << "+";
                        break;
                    }
                    default:
                    {
                        cout << "X";
                        break;
                    }
                }
            }
        }
    }
    cout << endl;
}

bool Level::fall()
{
    if (tile[(py+1)*ln+px]=='y')
    {
        return 1;
    }
    else if (charinstr(tile[(py+1)*ln+px],".0"))
    {
        py++;
        return fall();
    }
    return 0;
}

bool Level::action()
{
    for(int i = 0; i < ht * ln; i++)
    {
        switch(tile[i])
        {
            case('0'):
            {
                tile[i] = '1';
                break;
            }
            case('1'):
            {
                tile[i] = '0';
                break;
            }
            case('>'):
            {
                if (tile[i+1]=='.')
                {
                    tile[i+1]=')';
                }
                tile[i]='.';
                if (tile[i+1]=='<')
                {
                    tile[i]='<';
                    tile[i+1]=')';
                }
                break;
            }
            case(')'):
            {
                tile[i]='>';
                break;
            }
            case('<'):
            {
                if (tile[i-1]=='.')
                {
                    tile[i-1]='<';
                }
                if (tile[i-1]=='>')
                {
                    tile[i-1]='*';
                }
                tile[i]='.';
                break;
            }
            case('V'):
            {
                if (tile[i+ln]=='.')
                {
                    tile[i+ln]='U';
                }
                tile[i]='.';
                if (tile[i+ln]=='^')
                {
                    tile[i]='^';
                    tile[i+ln]='U';
                }
                break;
            }
            case('U'):
            {
                tile[i]='V';
                break;
            }
            case('^'):
            {
                if (charinstr(tile[i-ln],".<>"))
                {
                    tile[i-ln]='^';
                }
                if (tile[i-ln]=='V')
                {
                    tile[i-ln]='*';
                }
                tile[i]='.';
                break;
            }
        }
    }
    switch (tile[py * ln + px])
    {
        case 'a':
        {
            cout << "New command: 'a' - move 'P' to the left." << endl;
            commands += "a";
            tile[py * ln + px] = '.';
            break;
        }
        case '+':
        {
            cout << "New command: '+' - your next two commands are treated as a single move." << endl;
            cout << "Example: '+dd' will move the letter 'P' two spaces to the right" << endl;
            cout << "Use that to bypass that nasty switch wall before it turns on!" << endl;
            commands += "+";
            tile[py * ln + px] = '.';
            break;
        }
        default:
        {
            if(charinstr(tile[py * ln + px],"1<>^V"))
                return 1;
            break;
        }
    }
    return 0;
}

bool Level::step(bool isBonus = false)
{
    char c;
    cin >> c;
    if(!charinstr(c,commands + "\n"))
    {
        cout << "Unknown command" << endl;
        return 1;
    }
    switch (c)
    {
        case ('w'):
        {
            if (charinstr(tile[(py-1)*ln+px],"W1"))
                break;
            py--;
            break;
        }
        case ('a'):
        {
            if (charinstr(tile[(py)*ln+px-1],"W1"))
                break;
            px--;
            break;
        }
        case ('s'):
        {
            if (charinstr(tile[(py+1)*ln+px],"W1"))
                break;
            py++;
            break;
        }
        case ('d'):
        {
            if (charinstr(tile[(py)*ln+px+1],"W1"))
                break;
            px++;
            break;
        }
        case ('+'):
        {
            if(!isBonus)
            {
                step(true);
            }
            step(true);
            break;
        }
    }
    return 0;
}

bool Level::play()
{
    won = false;
    lost = false;
    printMessage();
    while(!won&&!lost)
    {
        printCommands();
        draw();
        while(step())
        {
            draw();
        }
        if (action())
        {
            draw();
            cout << "Try again!" << endl;
            return 0;
        }
        won = fall();
    }
    printCommands();
    draw();
    cout << "Level complete!" << endl;
    return 1;
}

void chartest()
{
    for(int i=0;i < 256;i++)
    {
        cout << i << ":" << (char)i << endl;
    }
}


    int LEVELS = 12;
    int STARTLEVEL = LEVELS;
int main()
{

    //chartest();
    string file;
    int lvl =STARTLEVEL;
    while(lvl<=LEVELS)
    {
        stringstream ss;
        ss << "level" << lvl;
        ss >> file;
        cout << endl << "Loading level " << lvl << endl;
        Level* b = new Level (file);
        lvl += b->play();
        delete(b);
    }
    cout << "Congratulations! Game complete!" << endl;
    return 0;
}
