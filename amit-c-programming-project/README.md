# 🎓 Student Database Management System in C

A simple **Student Database Management System** implemented in C using **singly linked lists** for dynamic storage.

---

## 🚀 Features
- Add a new student record (ID, year, 3 courses with grades)
- Delete a student record by ID
- Search and display student details
- Display list of all student IDs
- Check if a student ID exists
- Get total number of students in the database
- Prevent adding beyond maximum capacity

---

## 🛠️ Tech Stack
- **Language:** C
- **Data Structure:** Singly Linked List
- **Design:** Modular (`.c` and `.h` files for separation)

---

## 📂 Project Structure
```
├── data.c              # Predefined student data
├── data.h
├── main.c              # Entry point
├── SDB.c               # Database functions
├── SDB.h
├── SDBAPP.c            # Application interface
├── singleLinkedList.c  # Linked list implementation
├── singleLinkedList.h
├── STD.h               # Standard type definitions
```

---

## ▶️ How to Run
```bash
gcc main.c data.c SDB.c SDBAPP.c singleLinkedList.c -o studentDB
./studentDB
```

---

## 📌 Example Output
```
Options: 
To add entry, enter 1
To get used size in database, enter 2
To read student data, enter 3
To get the list of all student IDs, enter 4
To check if ID is existed, enter 5
To delete student data, enter 6
To check if database is full, enter 7
To exit, enter 0
Select What You Want :
```


---

## ✨ Author
Developed by **Hussain kamel** 🚀
