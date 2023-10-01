#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Forward declaration of AbstractPerson
class AbstractPerson;

// Define a FriendClass
class FriendClass
{
public:
    static void displayPersonInfo(const AbstractPerson &person);
};

// Abstract base class
class AbstractPerson
{
protected:
    string name;
    int age;
    string contact;

public:
    AbstractPerson(const string &name, int age, const string &contact)
        : name(name), age(age), contact(contact) {}

    virtual string getName() const = 0;
    virtual int getAge() const = 0;
    virtual string getContact() const = 0;
    virtual void display() const = 0;

    // Friend declaration for FriendClass
    friend class FriendClass;
};

class Candidate : public AbstractPerson
{
private:
    string education;
    vector<string> skills;
    int numSkills;
    string status;
    int id;
    static int nextId;

public:
    Candidate(const string &name, int age, const string &contact, const string &education, const vector<string> &skills, int numSkills)
        : AbstractPerson(name, age, contact), education(education), skills(skills), numSkills(numSkills), status("Applied"), id(nextId++) {}



    string getName() const override
    {
        return name;
    }

    int getAge() const override
    {
        return age;
    }

    string getContact() const override
    {
        return contact;
    }

    int getId() const
    {
        return id;
    }

    void setId(int newId)
    {
        id = newId;
    }

    bool meetsRequirements(const vector<string> &compReq) const
    {
        bool hasSkill = false;
        for (const string &req : compReq)
        {
            for (const string &skill : skills)
            {
                if (req == skill)
                {
                    hasSkill = true;
                    break;
                }
            }
        }
        return hasSkill;
        }

    void setStatus(const string &newStatus)
    {
        status = newStatus;
    }

    string getStatus() const
    {
        return status;
    }

    void display() const override
    {
        cout << "Candidate Information:" << endl;
        cout << "Name: " << name << "\nAge: " << age << "\nContact: " << contact << endl;
        cout << "ID: " << id << "\nEducation: " << education << "\nSkills: ";
        for (const string &skill : skills)
        {
            cout << skill << " ";
        }
        cout << "\nStatus: " << status << endl;
    }
    void file_output()const
    {
        ofstream out("candidate.txt",ios ::app);

        out <<name << "\n";
        out << id << " " << age <<" "<< status <<endl;
        out<<contact<<endl;
        out <<education << endl;
        for (const string &skill : skills)
        {
            out <<" "<< skill ;
        }
        out<<endl;
    }
};

int Candidate::nextId = 1;

class Employee : public AbstractPerson
{
private:
    string department;
    string position;
    int id;
    static int nextId;

public:
    Employee() : AbstractPerson("", 0, ""), department(""), position(""), id(nextId++) {}

    Employee(const string &name, int age, const string &contact, const string &department, const string &position)
        : AbstractPerson(name, age, contact), department(department), position(position), id(nextId++) {}



    string getName() const override
    {
        return name;
    }

    int getAge() const override
    {
        return age;
    }

    string getContact() const override
    {
        return contact;
    }

    int getId() const
    {
        return id;
    }

    void setId(int newId)
    {
        id = newId;
    }

    void display() const override
    {
        cout << "Employee Information:" << endl;
        cout << "Name: " << name << "\nAge: " << age << "\nContact: " << contact << endl;
        cout << "ID: " << id << "\nDepartment: " << department << "\nPosition: " << position << endl;
    }

    // Overloaded << operator as a friend function for Employee
    friend ostream &operator<<(ostream &os, const Employee &employee);
};

int Employee::nextId = 1;

// Define the << operator overload for Employee
ostream &operator<<(ostream &os, const Employee &employee)
{
    os << "Employee Information:" << endl;
    os << "Name: " << employee.getName() << "\nAge: " << employee.getAge() << "\nContact: " << employee.getContact() << endl;
    os << "ID: " << employee.getId() << "\nDepartment: " << employee.department << "\nPosition: " << employee.position << endl;
    return os;
}

// FriendClass implementation
void FriendClass::displayPersonInfo(const AbstractPerson &person)
{
    person.display();
}

class Company
{
private:
    string name;
    Candidate *candidates[100]; // Assuming a maximum of 100 candidates
    Employee employees[100];    // Assuming a maximum of 100 employees
    int numCandidates;
    int numEmployees;
    vector<string> compReq;

public:
    Company(const string &name) : name(name), numCandidates(0), numEmployees(0)
    {
        for (int i = 0; i < 100; ++i)
        {
            candidates[i] = nullptr;
        }
    }
    void setReq(const vector<string> &compreq)
    {
        this->compReq = compreq;
    }

    void addCandidate(const Candidate &candidate)
    {
        if (numCandidates < 100)
        {
            candidates[numCandidates++] = new Candidate(candidate);
        }
        else
        {
            cout << "Cannot add more candidates. Maximum limit reached." << endl;
        }
    }

    Candidate *searchCandidateById(int id)
    {
        for (int i = 0; i < numCandidates; ++i)
        {
            if (candidates[i] != nullptr && candidates[i]->getId() == id)
            {
                return candidates[i];
            }
        }
        return nullptr;
    }

    void addEmployee(const Employee &employee)
    {
        if (numEmployees < 100)
        {
            employees[numEmployees++] = employee;
        }
        else
        {
            cout << "Cannot add more employees. Maximum limit reached." << endl;
        }
    }

    Employee *searchEmployeeById(int id)
    {
        for (int i = 0; i < numEmployees; ++i)
        {
            if (employees[i].getId() == id)
            {
                return &employees[i];
            }
        }
        return nullptr;
    }

    void compareCandidatesToRequirements()
    {
        cout << "Hiring decisions:" << endl;
        for (int i = 0; i < numCandidates; ++i)
        {
            if (candidates[i] != nullptr && candidates[i]->meetsRequirements(compReq))
            {
                Employee newEmployee(candidates[i]->getName(), candidates[i]->getAge(), candidates[i]->getContact(), "Department", "Position");
                addEmployee(newEmployee);
                candidates[i]->setStatus("Hired");
                cout << "Hired: " << candidates[i]->getName() << endl;
            }
            else if (candidates[i] != nullptr)
            {
                candidates[i]->setStatus("Rejected");
                cout << "Not Hired: " << candidates[i]->getName() << endl;
            }
        }
    }

    void displayHiredCandidates() const
    {
        cout << "Hired Candidates:" << endl;
        for (int i = 0; i < numCandidates; ++i)
        {
            if (candidates[i] != nullptr && candidates[i]->getStatus() == "Hired")
            {
                candidates[i]->display();
                cout << "------------------------------" << endl;
            }
        }
    }

    void displayRejectedCandidates() const
    {
        cout << "Rejected Candidates:" << endl;
        for (int i = 0; i < numCandidates; ++i)
        {
            if (candidates[i] != nullptr && candidates[i]->getStatus() == "Rejected")
            {
                candidates[i]->display();
                cout << "------------------------------" << endl;
            }
        }
    }

    void displayAllCandidates() const
    {
        cout << "All Candidates:" << endl;
        for (int i = 0; i < numCandidates; ++i)
        {
            if (candidates[i] != nullptr)
            {
                candidates[i]->display();
                cout << "------------------------------" << endl;
            }
        }
    }
    void file_all_candidates() const
    {
        ofstream output("candidate.txt");
        output.close();
        for (int i = 0; i < numCandidates; ++i)
        {
            if (candidates[i] != nullptr)
            {
                candidates[i]->file_output();
            }
        }
    }
    void displayAllEmployees() const
    {
        cout << "All Employees:" << endl;
        for (int i = 0; i < numEmployees; ++i)
        {
            cout << employees[i]; // Using the overloaded << operator
            cout << "------------------------------" << endl;
        }
    }

    ~Company()
    {
        for (int i = 0; i < numCandidates; ++i)
        {
            delete candidates[i];
        }
    }
    friend void pre_calculation(Company &myCompany);
};
void pre_calculation(Company &myCompany)
{
    ifstream in1("candidate.txt"); // file input
    string sk;                     //
    string details;                //
    string name, contact, education;
    string status;
    while (getline(in1, name) && getline(in1, details) && getline(in1, contact) && getline(in1, education) && getline(in1, sk) && in1.eof() == 0)
    {
        istringstream in_details(details);
        istringstream in_skill(sk);
        int id, age;
        vector<string> skills; // Assuming a maximum of 10 skills
        int numSkills = 0;
        in_details >> id;
        in_details >> age;
        in_details>> status;
        in_skill.ignore(1);
        while (in_skill.eof() == 0)
        {
            string temp_skill;
            in_skill >> temp_skill;
            in_skill.ignore(1);
            skills.push_back(temp_skill);
            numSkills++;
        }
        Candidate newCandidate(name, age, contact, education, skills, numSkills);
        newCandidate.setStatus(status); // Set the initial status
        newCandidate.setId(id);            // Set the ID for the candidate
        myCompany.addCandidate(newCandidate);
    }
    in1.close();
}
template<class T1>
vector<T1> Input_rec (T1 demo)
{
    vector<T1> req;
    T1 r1="Programming";
    T1 r2="Problem_Solving";
    T1 r3="Communication";
    req.push_back(r1);
    req.push_back(r2);
    req.push_back(r3);
    return req;
}
int main()
{
    Company myCompany("ABC Inc.");
    vector<string>companyRequirements ;
    string s="Input";
    companyRequirements = Input_rec(s);
    myCompany.setReq(companyRequirements);
    pre_calculation(myCompany); // file input
    int choice;
    do
    {
        cout << "Company Management System" << endl;
        cout << "1. Add Candidate" << endl;
        cout << "2. Compare Candidates to Requirements" << endl;
        cout << "3. Display Hired Candidates" << endl;
        cout << "4. Display Rejected Candidates" << endl;
        cout << "5. Display All Candidates" << endl;
        cout << "6. Add Employee" << endl;
        cout << "7. Display All Employees" << endl;
        cout << "8. Search Employee/Candidate by ID" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int id;
            string name, contact, education;
            int age;
            vector<string> skills; // Assuming a maximum of 10 skills
            int numSkills = 0;
            cout << "Enter candidate ID: ";
            cin >> id;
            cout << "Enter candidate name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter candidate age: ";
            cin >> age;
            cout << "Enter candidate contact: ";
            cin.ignore();
            getline(cin, contact);
            cout << "Enter candidate education: ";
            getline(cin, education);
            cout << "Enter candidate skills (one per line, enter 'Done' to finish):" << endl;
            while (numSkills < 10)
            {
                string skill;
                getline(cin, skill);
                if (skill == "Done")
                {
                    break;
                }
                skills.push_back(skill);
                numSkills++;
            }
            Candidate newCandidate(name, age, contact, education, skills, numSkills);
            newCandidate.setStatus("Applied"); // Set the initial status
            newCandidate.setId(id);            // Set the ID for the candidate
            myCompany.addCandidate(newCandidate);
            cout << "Candidate added successfully!" << endl;
            break;
        }
        case 2:
        {
            myCompany.compareCandidatesToRequirements();
            break;
        }
        case 3:
        {
            myCompany.displayHiredCandidates();
            break;
        }
        case 4:
        {
            myCompany.displayRejectedCandidates();
            break;
        }
        case 5:
        {
            myCompany.displayAllCandidates();
            break;
        }
        case 6:
        {
            int id;
            string name, contact, department, position;
            int age;
            cout << "Enter employee ID: ";
            cin >> id;
            cout << "Enter employee name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter employee age: ";
            cin >> age;
            cout << "Enter employee contact: ";
            cin.ignore();
            getline(cin, contact);
            cout << "Enter employee department: ";
            getline(cin, department);
            cout << "Enter employee position: ";
            getline(cin, position);
            Employee newEmployee(name, age, contact, department, position);
            newEmployee.setId(id); // Set the ID for the employee
            myCompany.addEmployee(newEmployee);
            cout << "Employee added successfully!" << endl;
            break;
        }
        case 7:
        {
            myCompany.displayAllEmployees();
            break;
        }
        case 8:
        {
            int searchId;
            cout << "Enter ID to search (0 to exit): ";
            cin >> searchId;
            if (searchId == 0)
            {
                break;
            }
            AbstractPerson *foundPerson = nullptr;
            Candidate *foundCandidate = myCompany.searchCandidateById(searchId);
            if (foundCandidate)
            {
                foundPerson = foundCandidate;
            }
            else
            {
                Employee *foundEmployee = myCompany.searchEmployeeById(searchId);
                if (foundEmployee)
                {
                    foundPerson = foundEmployee;
                }
            }
            if (foundPerson)
            {
                cout << "Person found by ID " << searchId << ":" << endl;
                FriendClass::displayPersonInfo(*foundPerson); // Using FriendClass to display person info
                cout << "------------------------------" << endl;
            }
            else
            {
                cout << "No person found with ID " << searchId << endl;
            }
            break;
        }
        case 9:
        {
            cout << "Exiting Placement Management System. Goodbye!" << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);
    myCompany.file_all_candidates();
    return 0;
}
