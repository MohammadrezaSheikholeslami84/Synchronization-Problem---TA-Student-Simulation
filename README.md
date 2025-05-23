# 🧑‍🏫 Synchronization Problem – TA-Student Simulation

This project simulates a classic **synchronization problem** involving a **Teaching Assistant (TA)** and multiple **students** using **POSIX threads, semaphores, and mutexes** in C. 


---

## 📋 Problem Statement

A TA helps students with their programming assignments. However:

- The TA can only help **one student at a time**.
- If no students are present, the TA sleeps.
- There are only **5 chairs** in the waiting area.
- When a student arrives:
  - If a chair is available, they wait.
  - If no chair is available, they leave.
- When a waiting student is helped:
  - The TA wakes up (if asleep), and helps them.
  - After help, the student leaves and another student (if any) is helped.

---

## 🧵 Threads Used

- **1 TA Thread** – Handles helping students.
- **10 Student Threads** – Each simulates a student attempting to get help.

---

## 🔧 Technologies

- **C Programming Language**
- **POSIX Threads (pthreads)**
- **Semaphores (`<semaphore.h>`)**
- **Mutex (`<pthread.h>`)**
- **GCC/Linux Environment**

---

## 📌 Example Output
```bash
TA is sleeping...
Student 1 is waiting. Chairs left: 4
Student 0 is waiting. Chairs left: 3
Student 2 is waiting. Chairs left: 2
Student 7 is waiting. Chairs left: 1
Student 6 is waiting. Chairs left: 0
Student 8 left (no chair available).
Student 5 left (no chair available).
Student 4 left (no chair available).
Student 3 left (no chair available).
TA is helping student 1
Student 9 is waiting. Chairs left: 0
TA has finished helping student 1
TA is sleeping...
TA is helping student 0
Student 1 has received help.
TA has finished helping student 0
TA is sleeping...
Student 0 has received help.
TA is helping student 2
TA has finished helping student 2
TA is sleeping...
TA is helping student 7
Student 2 has received help.
TA has finished helping student 7
TA is sleeping...
Student 7 has received help.
TA is helping student 6
TA has finished helping student 6
TA is sleeping...
TA is helping student 9
Student 6 has received help.
TA has finished helping student 9
TA is sleeping...
Student 9 has received help.
Program terminated.
