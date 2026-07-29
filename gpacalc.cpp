#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

struct subjNode
{
    int term;
    string cseCode;
    string cseName;
    float grade;
    float unit;
    float total;
    float GWA;
    subjNode *next = NULL;
};

class gpacalc
{
private:
    float CGWA;
    float TUnit;
    subjNode *MasterList;

public:
    gpacalc()
    {
        CGWA = 0;
        TUnit = 0;
    };
    float calcGWA();
    void printCGWA();
};
void gpacalc::printCGWA()
{
    subjNode *temp = MasterList;
    int count = 1;
    while (temp != NULL)
    {
        cout << left
             << setw(5) << count
             << setw(12) << temp->cseCode
             << setw(30) << temp->cseName
             << setw(8) << fixed << setprecision(1) << temp->unit
             << setw(8) << fixed << setprecision(2) << temp->grade
             << endl;

        temp = temp->next;
        count++;
    }
    cout << "==============================================================\n";
    cout << "Total Units : " << TUnit << endl;
    cout << "CGWA        : " << fixed << setprecision(2) << CGWA << endl;
    cout << "==============================================================\n";
}
float gpacalc::calcGWA()
{
    subjNode *course = NULL;
    subjNode *head = NULL;
    subjNode *temp = NULL;
    short numsub = 0, nTerm = 0;
    float summGU = 0, summUn = 0;

    cout << "Enter Number of Academic Term(s): ";
    cin >> nTerm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int x = 0; x < nTerm; x++)
    {
        cout << "Academic Term #" << (x) + 1 << endl;
        cout << "Enter Number of Courses: ";
        cin >> numsub;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (int i = 0; i < numsub; i++)
        {
            course = new subjNode;
            cout << "Enter course #" << (i) + 1 << " name: ";
            getline(cin, course->cseName);
            cout << "Enter course code: ";
            getline(cin, course->cseCode);
            cout << "Enter course unit(s): ";
            cin >> course->unit;
            cout << "Enter course grade: ";
            cin >> course->grade;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            course->total = (course->unit * course->grade);
            course->term = x + 1;
            course->next = NULL;
            if (head == NULL)
            {
                head = course;
                temp = head;
            }
            else
            {
                temp->next = course;
                temp = course;
            }
        }
    }

    temp = head;
    while (temp != NULL)
    {
        if (temp->unit > 0)
        {
            summGU += temp->total;
            summUn += temp->unit;
        }

        temp = temp->next;
    }

    CGWA = summGU / summUn;
    TUnit = summUn;
    MasterList = head;
    return CGWA;
}

int main()
{
    gpacalc TEST;
    float x = 0.0;
    cout << "GWA Calculator" << endl
         << "-----------------------------------------------" << endl;
    x = TEST.calcGWA();
    cout << x << endl
         << endl
         << endl;
    TEST.printCGWA();
    return 0;
}
