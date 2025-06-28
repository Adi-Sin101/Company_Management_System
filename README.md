# Company Management System

A console-based C++ application to manage a company's recruitment and employee data. The project allows you to add, search, and display candidates and employees, compare candidate skills to company requirements, and maintain records using file input/output.

## Features

- **Candidate Management**
  - Add new candidates with skills and education details.
  - Compare candidates' skills to company requirements and update their hiring status.
  - Display, search, and persist all candidate records.
  - Mark candidates as "Hired", "Rejected", or "Applied".
- **Employee Management**
  - Add new employees with department and position details.
  - Display and search all employee records.
- **Company Requirements**
  - Define required skills or attributes for hiring.
  - Input and store requirements for future candidate comparisons.
- **File Handling**
  - Persist candidate records to `candidate.txt`.
  - Load candidate records on program startup.
- **Menu-Driven Interface**
  - User-friendly console menu for all major operations.

## Technologies Used

- **Language:** C++
- **Standard Libraries:** `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<sstream>`
- **No external dependencies**

## Project Structure

- `project.cpp` - Main source file containing all logic (classes, main function, file I/O).

### Key Classes

- `AbstractPerson` - Base class for both candidates and employees.
- `Candidate` - Inherits from `AbstractPerson`, adds education, skills, status, and file I/O.
- `Employee` - Inherits from `AbstractPerson`, adds department, position, and file I/O.
- `Company` - Manages collections of candidates and employees, requirements, and business logic.

## How It Works

1. **Startup**: Loads existing candidate data from `candidate.txt`.
2. **Main Menu** (Examples):
    - 1. Add Candidate
    - 2. Compare Candidates to Requirements
    - 3. Display Hired Candidates
    - 4. Display Rejected Candidates
    - 5. Display All Candidates
    - 6. Add Employee
    - 7. Display All Employees
    - 8. Search Candidate/Employee by ID
    - 9. Exit
3. **Data Persistence**: Candidate information is saved and loaded from `candidate.txt`.

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++, clang++)
- Console/terminal

### Compilation

```bash
g++ -std=c++11 project.cpp -o company_management
```

### Usage

```bash
./company_management
```

Follow the on-screen menu prompts to interact with the system.

## Example

```text
Company Management System
1. Add Candidate
2. Compare Candidates to Requirements
3. Display Hired Candidates
4. Display Rejected Candidates
5. Display All Candidates
6. Add Employee
7. Display All Employees
8. Search Employee/Candidate by ID
9. Exit
Enter your choice: 
```


**Author:** [Adi-Sin101](https://github.com/Adi-Sin101)
