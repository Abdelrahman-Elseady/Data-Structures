#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <algorithm>  
using namespace std;

struct Node {
    int score;
    string playerName;
    vector<Node*> forward;
    Node(int score, string playerName, int level)
        : score(score), playerName(playerName), forward(level + 1, nullptr) {}
};

class SkipList {
    int maxLevel;
    float probability;
    Node* head;

    int randomLevel() {
        int level = 0;
        while ((rand() / double(RAND_MAX)) < probability && level < maxLevel)
            level++;
        return level;
    }

public:
    SkipList(int maxLevel, float probability)
        : maxLevel(maxLevel), probability(probability) {
        head = new Node(-1, "", maxLevel);
        srand(time(0));
    }


    void insert(int score, string playerName) {
        vector<Node*> update(maxLevel + 1, nullptr);
        Node* current = head;

        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->score < score)
                current = current->forward[i];
            update[i] = current;
        }

        int level = randomLevel();
        Node* newNode = new Node(score, playerName, level);


        for (int i = 0; i <= level; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }

        cout << "Player " << playerName << " added with score " << score << "." << endl;
    }


    void remove(int score) {
        vector<Node*> update(maxLevel + 1, nullptr);
        Node* current = head;

        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->score < score)
                current = current->forward[i];
            update[i] = current;
        }

        Node* target = current->forward[0];
        if (target && target->score == score) {
            for (int i = 0; i <= maxLevel && update[i]->forward[i] == target; i++) {
                update[i]->forward[i] = target->forward[i];
            }
            delete target;
            cout << "Player with score " << score << " removed." << endl;
        }
        else {
            cout << "Player with score " << score << " not found!" << endl;
        }
    }


    Node* search(int score) {
        Node* current = head;
        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->score < score)
                current = current->forward[i];
        }
        current = current->forward[0];
        return (current && current->score == score) ? current : nullptr;
    }


    void getTopPlayers(int N) {
        vector<Node*> players;


        Node* current = head->forward[0];
        while (current) {
            players.push_back(current);
            current = current->forward[0];
        }


        sort(players.begin(), players.end(), [](Node* a, Node* b) {
            return a->score > b->score;
            });


        cout << "Top " << N << " Players:" << endl;
        int count = 0;
        for (auto& player : players) {
            if (count++ == N) break;
            cout << player->playerName << " - Score: " << player->score << endl;
        }
    }

    void loadPlayersFromFile(const string& filename) {
        ifstream file(filename);
        string name;
        int score;

        while (file >> name >> score) {
            insert(score, name);
        }
        file.close();
    }


    void savePlayersToFile(const string& filename) {
        ofstream file(filename);
        Node* current = head->forward[0];

        while (current) {
            file << current->playerName << " " << current->score << endl;
            current = current->forward[0];
        }
        file.close();
    }

    void updateScore(int oldScore, int newScore) {
        Node* current = head;
        bool found = false;

        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->score < oldScore)
                current = current->forward[i];
        }
        current = current->forward[0];

        if (current && current->score == oldScore) {
            current->score = newScore;
            found = true;
            cout << "Player " << current->playerName << " score updated to " << newScore << "." << endl;
        }

        if (!found) {
            cout << "Player with score " << oldScore << " not found!" << endl;
        }
    }
};

int main() {
    int maxLevel = 4;
    float probability = 0.5;
    SkipList skipList(maxLevel, probability);


    skipList.loadPlayersFromFile("Players.txt");

    int choice;
    do {
        cout << "\n===== Menu =====\n";
        cout << "1. Add Player\n";
        cout << "2. Update Player Score\n";
        cout << "3. Remove Player\n";
        cout << "4. Search Player\n";
        cout << "5. Display Top N Players\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int score;
            cout << "Enter player name: ";
            cin >> name;
            cout << "Enter player score: ";
            cin >> score;
            skipList.insert(score, name);
            skipList.savePlayersToFile("Players.txt");
            break;
        }
        case 2: {
            string name;
            int oldScore, newScore;
            cout << "Enter player's current score: ";
            cin >> oldScore;
            cout << "Enter player's new score: ";
            cin >> newScore;
            skipList.updateScore(oldScore, newScore);
            skipList.savePlayersToFile("Players.txt");
            break;
        }
        case 3: {
            int score;
            cout << "Enter player score to remove: ";
            cin >> score;
            skipList.remove(score);
            skipList.savePlayersToFile("Players.txt");
            break;
        }
        case 4: {
            int score;
            cout << "Enter player score to search: ";
            cin >> score;
            auto player = skipList.search(score);
            if (player) {
                cout << "Found: " << player->playerName << " - Score: " << player->score << endl;
            }
            else {
                cout << "Player not found!" << endl;
            }
            break;
        }
        case 5: {
            int N;
            cout << "Enter number of top players to display: ";
            cin >> N;
            skipList.getTopPlayers(N);
            break;
        }
        case 6:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 6);

    return 0;
}