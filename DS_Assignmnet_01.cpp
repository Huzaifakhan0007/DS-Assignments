#include <iostream>
#include <string>

using namespace std;

struct Task {
    int taskID;
    string description;
    int priority;
    Task* next;
};

class TaskManager {
private:
    Task* head;

public:
    TaskManager() {
        head = nullptr;
    }

    void addTask(int taskID, string description, int priority) {
        Task* newTask = new Task();
        newTask->taskID = taskID;
        newTask->description = description;
        newTask->priority = priority;
        newTask->next = nullptr;

        if (head == nullptr || head->priority < priority) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* current = head;
            while (current->next != nullptr && current->next->priority >= priority) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
        cout << "Task added successfully!\n";
    }

    void viewTasks() {
        if (head == nullptr) {
            cout << "No tasks in the list.\n";
            return;
        }
        Task* current = head;
        while (current != nullptr) {
            cout << "Task ID: " << current->taskID << " | Description: " << current->description
                 << " | Priority: " << current->priority << endl;
            current = current->next;
        }
    }

    void removeHighestPriorityTask() {
        if (head == nullptr) {
            cout << "No tasks to remove.\n";
            return;
        }
        Task* temp = head;
        head = head->next;
        cout << "Task with ID " << temp->taskID << " removed.\n";
        delete temp;
    }

    void removeTaskByID(int taskID) {
        if (head == nullptr) {
            cout << "No tasks to remove.\n";
            return;
        }

        if (head->taskID == taskID) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Task with ID " << taskID << " removed.\n";
            return;
        }

        Task* current = head;
        Task* prev = nullptr;
        while (current != nullptr && current->taskID != taskID) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Task with ID " << taskID << " not found.\n";
            return;
        }

        prev->next = current->next;
        delete current;
        cout << "Task with ID " << taskID << " removed.\n";
    }
};

void menu() {
    TaskManager manager;
    int choice, taskID, priority;
    string description;

    while (true) {
        cout << "\n--- Task Management Menu ---\n";
        cout << "1. Add a new task\n";
        cout << "2. View all tasks\n";
        cout << "3. Remove the highest priority task\n";
        cout << "4. Remove a task by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter task ID: ";
                cin >> taskID;
                cin.ignore();
                cout << "Enter task description: ";
                getline(cin, description);
                cout << "Enter task priority: ";
                cin >> priority;
                manager.addTask(taskID, description, priority);
                break;
            case 2:
                manager.viewTasks();
                break;
            case 3:
                manager.removeHighestPriorityTask();
                break;
            case 4:
                cout << "Enter task ID to remove: ";
                cin >> taskID;
                manager.removeTaskByID(taskID);
                break;
            case 5:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
