#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Task {
    string description;
    bool completed;
};

void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks in the list.\n";
        return;
    }

    cout << "\nTo-Do List:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". " << tasks[i].description;
        cout << " [" << (tasks[i].completed ? "Completed" : "Pending") << "]\n";
    }
}

void addTask(vector<Task>& tasks) {
    string desc;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, desc);
    tasks.push_back({desc, false});
    cout << "Task added successfully.\n";
}

void markCompleted(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to mark.\n";
        return;
    }

    int index;
    viewTasks(tasks);
    cout << "Enter task number to mark as completed: ";
    cin >> index;

    if (cin.fail() || index < 1 || index > tasks.size()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid task number.\n";
        return;
    }

    tasks[index - 1].completed = true;
    cout << "Task marked as completed.\n";
}

void removeTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to remove.\n";
        return;
    }

    int index;
    viewTasks(tasks);
    cout << "Enter task number to remove: ";
    cin >> index;

    if (cin.fail() || index < 1 || index > tasks.size()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid task number.\n";
        return;
    }

    tasks.erase(tasks.begin() + index - 1);
    cout << "Task removed.\n";
}

int main() {
    vector<Task> tasks;
    int choice;

    while (true) {
        cout << "\nTo-Do List Manager\n";
        cout << "1. View Tasks\n";
        cout << "2. Add Task\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1:
                viewTasks(tasks);
                break;
            case 2:
                addTask(tasks);
                break;
            case 3:
                markCompleted(tasks);
                break;
            case 4:
                removeTask(tasks);
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}
