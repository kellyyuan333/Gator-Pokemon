//Group Members: Kelly Yuan, Arisha Haque, Jingxuan 
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <list>
#include <queue>
#include <cmath>
#include <algorithm>
#include <time.h>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
using namespace std;

//Pokemon and its attributes
struct Pokemon {
    int index;
    string name;
    string variation = "";
    string type1 = ""; 
    string type2 = ""; 
    int total;
    int hp;
    int attack;
    int defense;
    int spattack;
    int spdef;
    int speed;
};

class HashMap {
private:
    struct Entry {
        std::string key;
        vector<Pokemon> values;

        //key and value pair
        Entry(const std::string& k, const vector<Pokemon>& v) : key(k), values(v) {}
    };

    //for chaining
    std::vector<std::list<Entry>> table;
    //for hashcode
    std::hash<std::string> hash;
    // Number of elements in the table
    size_t elementCount;

    // Function to check and resize the table if needed
    void checkAndResize() {
        double loadFactor = static_cast<double>(elementCount) / table.size();

        if (loadFactor >= 0.8) {
            size_t newSize = table.size() * 2;
            rehash(newSize);
        }
    }

    // Rehash the table with the new size
    void rehash(size_t newSize) {
        std::vector<std::list<Entry>> newTable(newSize);

        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                size_t index = hash(entry.key) % newSize;
                newTable[index].emplace_back(entry);
            }
        }
        //update the table
        table = newTable;
    }

public:
    // initialization
    HashMap() : table(10), elementCount(0) {}

    bool check(const std::string var, const std::vector<Pokemon> vec) {
        for (Pokemon p : vec) {
            if (p.variation == var) {
                return false;
            }
        }
        return true;
    }

    bool insert(const std::string& key, const Pokemon& value) {
        checkAndResize();
        size_t index = hash(key) % table.size();

        // Check if the key already exists in the table
        for (auto& entry : table[index]) {
            if (entry.key == key) {
                //add to the corresponding vector
                if (check(value.variation, entry.values)) {
                    entry.values.push_back(value);
                    return true;
                }
                else {
                    return false;
                }
            }
        }

        // If key does not exist, create a new entry and add new pokemon
        std::vector<Pokemon> newVec;
        newVec.push_back(value);
        table[index].emplace_back(key, newVec);
        // Increment the element count
        ++elementCount;
        return true;
    }

    Pokemon search(const std::string& name, const std::string& variation) const {
        // Find the index
        size_t index = hash(name) % table.size();

        // Search through the list at the computed index
        for (const auto& entry : table[index]) {
            if (entry.key == name) {
                for (const auto& value : entry.values) {
                    if (value.variation == variation) {
                        return value;
                    }
                }
            }
        }
        // Name not found, return a default-constructed Pokemon
        return Pokemon{ -1, "", "", "", "", 0, 0, 0, 0, 0, 0, 0 };
    }

    Pokemon searchPrint(const std::string& name, const std::string& variation) const {
        // Find the index
        size_t index = hash(name) % table.size();

        // Search through the list at the computed index
        for (const auto& entry : table[index]) {
            if (entry.key == name) {
                for (const auto& value : entry.values) {
                    if (value.variation == variation) {
                        return value;
                    }
                }
            }
        }
        // Name not found, return a default-constructed Pokemon
        cout << endl;
        cout << "No pokemon with name " << name << " and variation " << variation << " found!" << endl;
        return Pokemon{ -1, "", "", "", "", 0, 0, 0, 0, 0, 0, 0 };
    }

    //Randomly generate new Pokemon
    Pokemon create_new() {
        Pokemon p;

        int curr = rand() % 200 + 1;
        p.name = to_string(curr);
        p.index = curr;

        vector<string> types1 = { "Grass", "Water", "Bug", "Normal", "Dark", "Poison", "Electric", "Ground", "Ice", "Fairy", "Fighting", "Psychic", "Rock", "Fire", "Dragon", "Steel", "Ghost" };
        vector<string> types2 = { "Grass", "Water", "Bug", "Normal", "Dark", "Poison", "Electric", "Ground", "Ice", "Fairy", "Fighting", "Psychic", "Rock", "Fire", "Dragon", "Steel", "Ghost", "N/A" };

        for (int i = 0; i < 6; i++) {
            if (i == 0) {
                int num = rand() % 200 + 1;
                p.attack = num;
            }
            if (i == 1) {
                int num = rand() % 200 + 1;
                p.defense = num;
            }
            if (i == 2) {
                int num = rand() % 100 + 1;
                p.hp = num;
            }
            if (i == 3) {
                int num = rand() % 200 + 1;
                p.spattack = num;
            }
            if (i == 4) {
                int num = rand() % 200 + 1;
                p.spdef = num;
            }
            if (i == 5) {
                int num = rand() % 200 + 1;
                p.speed = num;
            }
        }
        p.total = p.hp + p.attack + p.defense + p.spattack + p.spdef + p.speed;

        int num = rand() % (types1.size() - 1) + 1;

        int num2 = rand() % (types2.size() - 1) + 1;
        p.type1 = types1[num];
        p.type2 = types2[num2];
        vector<string> v = { "Mega Blastoise", "Mega Alakazam", "Mega Pinsir", "Mega Charizard X", "Mega Ampharos", "Mega Beedrill", "Mega Aerodactyl", "Mega Gardevoir", "Mega Slowbro","Alolan Rattata", "Partner Pikachu", "Alolan Raichu", "Alolan Sandlash", "Alolan Vulpix" };

        int num3 = rand() % (v.size() - 1) + 1;
        p.variation = v[num3];
        return p;
    }

    //Print pokemon's attributes
    void print_pokemon(Pokemon p) {
        cout << "Name: " << p.name << endl;
        cout << "Variation: " << p.variation << endl;
        cout << "Type 1: " << p.type1 << endl;
        cout << "Type 2: " << p.type2 << endl;
        cout << "Total: " << p.total << endl;
        cout << "Attack: " << p.attack << endl;
        cout << "Defense: " << p.defense << endl;
        cout << "Speed: " << p.speed << endl;
        cout << "Special Attack: " << p.spattack << endl;
        cout << "Special Defense: " << p.spdef << endl;
        cout << "HP: " << p.hp << endl;
    }

    //Compare two pokemon's total statistics
    string battlePokemon(Pokemon pokemon1, Pokemon pokemon2) {
        int total1 = pokemon1.total;
        int total2 = pokemon2.total;
        if (total1 == total2) {
            return " "; //it's a tie
        }
        return total1 > total2 ? pokemon1.name : pokemon2.name;
    }

    void filter(const string category, const string wordType, const int numType) {
        //store the names of the pokemon with desired attribute
        vector<string> nameList;
        //iterate through hashmap
        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                for (const auto& poke : entry.values) {
                    if (category == "variation") {
                        if (poke.variation == wordType) {
                            //insert the name of the pokemon into nameList
                            nameList.push_back(poke.name);
                        }
                    }
                    else if (category == "type 1") {
                        if (poke.type1 == wordType) {
                            nameList.push_back(poke.name);
                        }
                    }
                    else if (category == "type 2") {
                        if (poke.type2 == wordType) {
                            nameList.push_back(poke.name);
                        }
                    }
                    else if (category == "total statistics") {
                        if (poke.total == numType) {
                            nameList.push_back(poke.name);
                        }
                    }
                    else if (category == "hit points") {
                        if (poke.hp == numType) {
                            nameList.push_back(poke.name);
                        }
                    }
                    else if (category == "attack") {
                        if (poke.attack == numType) {
                            nameList.push_back(poke.name);
                        }
                    }
                    else if (category == "defense") {
                        if (poke.defense == numType) {
                            nameList.push_back(poke.name);
                        }
                    }
                    else if (category == "special attack") {
                        if (poke.spattack == numType) {
                            nameList.push_back(poke.name);
                        }
                    }
                    else if (category == "special defense") {
                        if (poke.spdef == numType) {
                            nameList.push_back(poke.name);
                        }
                    }
                    else if (category == "speed") {
                        if (poke.speed == numType) {
                            nameList.push_back(poke.name);
                        }
                    }
                }
            }
        }
        if (nameList.size() == 0) {
            cout << "No Pokemon with desired attribute" << endl;
        }
        else {
            //print elements in nameList
            for (int i = 0; i < nameList.size() - 1; i++) {
                cout << nameList[i] << ", ";
            }
            //print last element without following comma
            cout << nameList.back() << endl;
        }
    }
};

class Bnode { //Bnode is a node that has the following variables an arr that has keys in it, a pointer to its parent Bnode, and a vector full of its children Bnodes
public:
    vector<Pokemon> arr;
    Bnode* parent = nullptr;
    vector<Bnode*> children;

};
struct Btree { //Btree stores all of the Bnodes
    
    Bnode* rootactual = nullptr; //root of the entire tree
    
    int max_n = 3; //max number of children
    int max_l = 2; //max number of keys that a leaf node can have NOTE: non-leaf nodes have max number of child - 1 keys (max_n - 1)
    vector<string> names; //not used currently lol
    bool is_visited(Bnode* node, vector<Bnode*> vis) { //function that checks if a node is in the visited vector (or if the node has been visited)
        if (vis.size() == 0) {
            return false;
        }
        else {
            for (int i = 0; i < vis.size(); i++) {
                if (node == vis.at(i)) {
                    return true;
                }
            }
            return false;
        }
    }
    bool is_leaf(Bnode* node) { //function that checks if the node has any children or is a leaf
        if (node->children.size() == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    void sort_vec(vector<Pokemon>& vec) { //sorts the Node's arr vector or its pokemon by index
        if (vec.size() > 1) {
            vector<int> ind;
            for (int i = 0; i < vec.size(); i++) {
                ind.push_back(vec[i].index);
            }
            sort(ind.begin(), ind.end());
            vector<Pokemon> newvec;
            for (int i = 0; i < ind.size(); i++) {
                for (int j = 0; j < vec.size(); j++) {
                    if (vec.at(j).index == ind.at(i)) {
                        newvec.push_back(vec.at(j));
                    }
                }
            }
            vec = newvec;
        }
    }
    void sort_children(vector<Bnode*>& c) { //sorts the children by the first index in the child's array 
        if (c.size() > 1) {
            vector<int> ind;
            for (int i = 0; i < c.size(); i++) {
                ind.push_back(c[i]->arr.at(0).index);
            }
            sort(ind.begin(), ind.end());
            vector<Bnode*> newvec;
            for (int i = 0; i < ind.size(); i++) {
                for (int j = 0; j < c.size(); j++) {
                    if (c[j]->arr.at(0).index == ind.at(i)) {
                        newvec.push_back(c.at(j));
                    }
                }
            }
            c = newvec;
        }
    }
    Pokemon split(Bnode* node, vector<Pokemon> vec) { //splits the node
        sort_vec(vec); //sort the vec first
        int mid = floor(vec.size() / 2); //find the mid index of the vec
        Pokemon midp = vec[mid]; //find the pokemon that is in the mid index
        sort_vec(node->parent->arr); //sort the parent's arr

        //updating the node's parent's children (splitting the actual node)
        Bnode* curr_parent = node->parent;

        Bnode* child1 = new Bnode;
        Bnode* child2 = new Bnode;
        child1->parent = node->parent;
        child2->parent = node->parent;
        for (int i = 0; i < mid; i++) { //takes all the keys up until the mid index and puts it in the child1's arr
            child1->arr.push_back(node->arr.at(i));
        }
        if (floor(node->arr.size() / 2) < 2) { //checks if there is only one other key after mid key and just puts it in child2's arr

            child2->arr.push_back(node->arr.at(node->arr.size() - 1));
        }
        else {
            for (int i = mid + 1; i < node->arr.size(); i++) { //if there is more than one key after mid key then it puts all the other keys in child2's arr

                child2->arr.push_back(node->arr.at(i));
            }
        }

        //updating child1's children and child2's children (the node might have children so you have to reassign those children to child1 and child2)
        if (node->children.size() != 0) {

            vector<Bnode*> all;
            int mid2 = 0;
            for (int i = 0; i < node->children.size(); i++) {
                all.push_back(node->children.at(i));
            }
            mid2 = floor(all.size() / 2);
            for (int i = 0; i < mid2; i++) {
                child1->children.push_back(all[i]);
                all[i]->parent = child1;
            }
            if (floor(all.size()) / 2 < 2) {
                child2->children.push_back(all[all.size() - 1]);
                all[all.size() - 1]->parent = child2;
            }
            else {
                for (int i = mid2; i < all.size(); i++) {
                    child2->children.push_back(all[i]);
                    all[i]->parent = child2;
                }
            }
        }

        //erasing the old node
        vector<Bnode*> newvec;
        for (int i = 0; i < node->parent->children.size(); i++) {
            if (node == node->parent->children.at(i)) {
                node->parent->children.erase(node->parent->children.begin() + i);
                break;
            }
        }
        delete node;

        //setting the curr_parent's children && visited nodes
        curr_parent->children.push_back(child1);
        curr_parent->children.push_back(child2);

        visited.push_back(child1);
        visited.push_back(child2);

        //sort the curr_parent's children and child1 and child2's children
        sort_children(curr_parent->children);
        sort_children(child1->children);
        sort_children(child2->children);
        return midp;
    }
    bool find_pokemon_no_print(string n, string v, vector<Pokemon> vec) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].name == n && vec[i].variation == v) {
                return true;
            }
        }
        return false;
    }
    bool find_pokemon(string n, string v, vector<Pokemon> vec) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].name == n && vec[i].variation == v) {
                print_pokemon(vec[i]);
                return true;
            }
        }
        return false;
    }
    Pokemon find_pokemon_return(string n, string v, vector<Pokemon> vec) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].name == n && vec[i].variation == v) {
                return vec[i];
            }
        }
        return Pokemon{ -1, "", "", "", "", 0, 0, 0, 0, 0, 0, 0 };
    }


public:
	int curr = 0; //number of nodes currently in the tree
    
    vector<Bnode*> visited; //vector of visited nodes when traversing through the tree
    void insert(Bnode* root, Pokemon p) {
        if (root == nullptr) { //if root is equal to nullptr
            Bnode* newnode = new Bnode;
            newnode->arr.push_back(p);
            if (rootactual == nullptr) {
                rootactual = newnode;
            }
        }
        else if (is_leaf(root) == true) {// if root is equal to a leaf (or it has no children)
            sort_vec(root->arr);
            if (root->arr.size() == max_l) { //if the leaf is full
                if (root->parent == nullptr) { //if the current root actual is full then we have to create a new root!
                    Bnode* newroot = new Bnode;
                    root->parent = newroot;
                    newroot->children.push_back(root);
                    root->arr.push_back(p);
                    Pokemon s;
                    s = split(root, root->arr);
                    newroot->arr.push_back(s);
                    rootactual = newroot;
                    visited.clear();
                }
                else { //if the root has a parent then just split the root and then insert the parent back into the function to see if its full
                    Bnode* parentnode = root->parent;

                    root->arr.push_back(p);
                    Pokemon s;

                    s = split(root, root->arr);

                    if (parentnode->arr.size() < max_n - 1) {
                        parentnode->arr.push_back(s);
                    }
                    else {
                        insert(parentnode, s); //if its full
                    }
                }
            }
            else if (root->arr.size() != max_l) { //if the leaf is not full
                //inserting the pokemon into a sorted array if leaf is not full
                sort_vec(root->arr);
                root->arr.push_back(p);
                sort_vec(root->arr);
            }
        }
        else if (is_leaf(root) == false) { //if the root is not a leaf 
            int index = 1;

            for (int i = 0; i < root->arr.size(); i++) { //finds the index that p will be inserted to
                if (root->arr[i].index < p.index) {
                    index++;
                }
                else {
                    break;
                }
            }

            if (root->children.size() < max_n) {
                if (index >= root->children.size()) {
                    if (is_visited(root->children[root->children.size() - 1], visited) == false) {
                        insert(root->children[root->children.size() - 1], p);
                    }
                    else if (root->arr.size() < max_n - 1) {
                        root->arr.push_back(p);
                    }
                    else if (root->parent == nullptr) {
                        Bnode* newroot = new Bnode;
                        root->parent = newroot;
                        newroot->children.push_back(root);
                        root->arr.push_back(p);
                        Pokemon s;
                        s = split(root, root->arr); //push the p into the root first, then split the root, then put the midp index into the new root
                        newroot->arr.push_back(s);
                        rootactual = newroot;
                        visited.clear();
                    }
                    else if (root->parent != nullptr) {
                        
                        Pokemon s;
                        s = split(root, root->arr);
                        insert(root->parent, s);
                    }
                }
                else {
                    if (is_visited(root->children[index], visited) == false) {
                        insert(root->children[index], p);
                    }
                    else if (root->arr.size() < max_n - 1) {
                        root->arr.push_back(p);
                    }
                    else if (root->parent == nullptr) {
                        Bnode* newroot = new Bnode;
                        root->parent = newroot;
                        newroot->children.push_back(root);
                        root->arr.push_back(p);
                        Pokemon s;
                        s = split(root, root->arr); //push the p into the root first, then split the root, then put the midp index into the new root
                        newroot->arr.push_back(s);
                        rootactual = newroot;
                        visited.clear();
                    }
                    else if (root->parent != nullptr) {
                        
                        Pokemon s;
                        s = split(root, root->arr);
                        insert(root->parent, s);
                    }
                }
            }
            else if (root->children.size() == max_n) {
                sort_vec(root->arr);

                if (index >= root->children.size()) {
                    if (is_visited(root->children[root->children.size() - 1], visited) == false) {
                        insert(root->children[root->children.size() - 1], p);
                    }
                }

                else if (index < root->children.size()) {
                    if (is_visited(root->children[index], visited) == false) {
                        insert(root->children[index], p);
                    }
                }
            }
            else if (root->children.size() > max_n) {
                Bnode* parentnode = root->parent;

                if (parentnode == nullptr) {
                    Bnode* newroot = new Bnode;
                    root->parent = newroot;
                    newroot->children.push_back(root);
                    root->arr.push_back(p);
                    Pokemon s;
                    s = split(root, root->arr);
                    newroot->arr.push_back(s);
                    rootactual = newroot;
                    visited.clear();
                }
                else {
                    Bnode* parentnode = root->parent;

                    root->arr.push_back(p);
                    Pokemon s;

                    s = split(root, root->arr);

                    if (parentnode->arr.size() < max_n - 1) {
                        parentnode->arr.push_back(s);
                    }
                    else {
                        insert(parentnode, s); //if its full
                    }
                }
            }
        }
    }

    //Randomly generate new Pokemon
    Pokemon create_new() {
        curr = curr + 1;
        Pokemon p;

        p.name = to_string(curr);
        p.index = curr;

        vector<string> types1 = { "Grass", "Water", "Bug", "Normal", "Dark", "Poison", "Electric", "Ground", "Ice", "Fairy", "Fighting", "Psychic", "Rock", "Fire", "Dragon", "Steel", "Ghost" };
        vector<string> types2 = { "Grass", "Water", "Bug", "Normal", "Dark", "Poison", "Electric", "Ground", "Ice", "Fairy", "Fighting", "Psychic", "Rock", "Fire", "Dragon", "Steel", "Ghost", "N/A" };

        for (int i = 0; i < 6; i++) {
            if (i == 0) {
                int num = rand() % 200 + 1;
                p.attack = num;
            }
            if (i == 1) {

                int num = rand() % 200 + 1;
                p.defense = num;
            }
            if (i == 2) {

                int num = rand() % 100 + 1;
                p.hp = num;
            }
            if (i == 3) {

                int num = rand() % 200 + 1;
                p.spattack = num;
            }
            if (i == 4) {

                int num = rand() % 200 + 1;
                p.spdef = num;
            }
            if (i == 5) {

                int num = rand() % 200 + 1;
                p.speed = num;
            }
        }
        p.total = p.hp + p.attack + p.defense + p.spattack + p.spdef + p.speed;

        int num = rand() % (types1.size() - 1) + 1;

        int num2 = rand() % (types2.size() - 1) + 1;
        p.type1 = types1[num];
        p.type2 = types2[num2];
        vector<string> v = { "Mega Blastoise", "Mega Alakazam", "Mega Pinsir", "Mega Charizard X", "Mega Ampharos", "Mega Beedrill", "Mega Aerodactyl", "Mega Gardevoir", "Mega Slowbro","Alolan Rattata", "Partner Pikachu", "Alolan Raichu", "Alolan Sandlash", "Alolan Vulpix" };

        int num3 = rand() % (v.size() - 1) + 1;
        p.variation = v[num3];
        return p;
    }

    //Print pokemon's attributes
    void print_pokemon(Pokemon p) {
        cout << "Name: " << p.name << endl;
        cout << "Index: " << p.index << endl;
        cout << "Variation: " << p.variation << endl;
        cout << "Type 1: " << p.type1 << endl;
        cout << "Type 2: " << p.type2 << endl;
        cout << "Total: " << p.total << endl;
        cout << "Attack: " << p.attack << endl;
        cout << "Defense: " << p.defense << endl;
        cout << "Speed: " << p.speed << endl;
        cout << "Special Attack: " << p.spattack << endl;
        cout << "Special Defense: " << p.spdef << endl;
        cout << "HP: " << p.hp << endl;
    }

     //this function uses BFS algorithm which is given by Prof. Aman in the Graph 8a Powerpoint slide 63
    
    int num_keys() {
        vector<Bnode*> visited2;
        if (rootactual == nullptr) {
            return 0;
        }

        int count = 0;
        queue<Bnode*> q;
        q.push(rootactual);
        visited2.push_back(rootactual);

        while (!q.empty()) {
            Bnode* current = q.front();
            q.pop();

            count += current->arr.size();
            for (int i = 0; i < current->children.size(); i++) {
                if (is_visited(current->children[i], visited2) == false) {
                    visited2.push_back(current->children[i]);
                    q.push(current->children[i]);
                }
            }
        }
        return count;
    }

    //this function uses BFS algorithm which is given by Prof. Aman in the Graph 8a Powerpoint slide 63
    void bfs_print() {
        vector<Bnode*> visited6;
        if (rootactual == nullptr) {
            cout << "";
        }

        int count = 0;
        queue<Bnode*> q;
        q.push(rootactual);
        visited6.push_back(rootactual);

        while (!q.empty()) {
            Bnode* current = q.front();
            for (int i = 0; i < q.front()->arr.size(); i++) {
                cout << q.front()->arr[i].index << " ";
            }
            q.pop();
            for (int i = 0; i < current->children.size(); i++) {
                if (is_visited(current->children[i], visited6) == false) {
                    visited6.push_back(current->children[i]);
                    q.push(current->children[i]);
                }
            }
        }
    }

     //this function uses BFS algorithm which is given by Prof. Aman in the Graph 8a Powerpoint slide 63
    bool search_no_print(string n, string v) {
        vector<Bnode*> visited3;
        if (rootactual == nullptr) {
            return false;
        }
        bool stop = false;
        int count = 0;
        queue<Bnode*> q;
        q.push(rootactual);
        visited3.push_back(rootactual);

        while (!q.empty() && stop == false) {
            Bnode* current = q.front();
            q.pop();
            if (find_pokemon_no_print(n, v, current->arr) == true) {
                stop = true;
                return true;
            }

            count += current->arr.size();
            for (int i = 0; i < current->children.size(); i++) {
                if (is_visited(current->children[i], visited3) == false) {
                    visited3.push_back(current->children[i]);
                    q.push(current->children[i]);
                }
            }
        }
        return false;
    }

    void filter(const string category, const string wordType, const int numType) {
        vector<Bnode*> visited12;
        //store the names of the pokemon with desired attribute
        vector<string> nameList;
        //iterate through hashmap

        visited12.clear();
        if (rootactual == nullptr) {
            cout << "";
        }
        int count = 0;
        queue<Bnode*> q;
        q.push(rootactual);
        visited12.push_back(rootactual);
        while (!q.empty()) {
            Bnode* current = q.front();
            for (int i = 0; i < q.front()->arr.size(); i++) {
                if (category == "variation") {
                    if (current->arr[i].variation == wordType) {
                        //insert the name of the pokemon into nameList
                        nameList.push_back(current->arr[i].name);
                    }
                }
                else if (category == "type 1") {
                    if (current->arr[i].type1 == wordType) {
                        nameList.push_back(current->arr[i].name);
                    }
                }
                else if (category == "type 2") {
                    if (current->arr[i].type2 == wordType) {
                        nameList.push_back(current->arr[i].name);
                    }
                }
                else if (category == "total statistics") {
                    if (current->arr[i].total == numType) {
                        nameList.push_back(current->arr[i].name);
                    }
                }
                else if (category == "hit points") {
                    if (current->arr[i].hp == numType) {
                        nameList.push_back(current->arr[i].name);
                    }
                }
                else if (category == "attack") {
                    if (current->arr[i].attack == numType) {
                        nameList.push_back(current->arr[i].name);
                    }
                }
                else if (category == "defense") {
                    if (current->arr[i].defense == numType) {
                        nameList.push_back(current->arr[i].name);
                    }
                }
                else if (category == "special attack") {
                    if (current->arr[i].spattack == numType) {
                        nameList.push_back(current->arr[i].name);
                    }
                }
                else if (category == "special defense") {
                    if (current->arr[i].spdef == numType) {
                        nameList.push_back(current->arr[i].name);
                    }
                }
                else if (category == "speed") {
                    if (current->arr[i].speed == numType) {
                        nameList.push_back(current->arr[i].name);
                    }
                }
            }
            q.pop();
            for (int i = 0; i < current->children.size(); i++) {
                if (is_visited(current->children[i], visited12) == false) {
                    visited12.push_back(current->children[i]);
                    q.push(current->children[i]);
                }
            }
        }
        if (nameList.size() == 0) {
            cout << "No Pokemon with desired attribute" << endl;
        }
        else {
            //print elements in nameList
            for (int i = 0; i < nameList.size() - 1; i++) {
                cout << nameList[i] << ", ";
            }
            //print last element without following comma
            cout << nameList.back() << endl;
        }
    }
		   //this function uses BFS algorithm which is given by Prof. Aman in the Graph 8a Powerpoint slide 63
    bool search(string n, string v) {
        vector<Bnode*> visited3;
        if (rootactual == nullptr) {
            cout << "No pokemon with name " << n << " and variation " << v << " found!" << endl;
        }
        bool stop = false;
        int count = 0;
        queue<Bnode*> q;
        q.push(rootactual);
        visited3.push_back(rootactual);

        while (!q.empty() && stop == false) {
            Bnode* current = q.front();
            q.pop();
            if (find_pokemon(n, v, current->arr) == true) {
                stop = true;
                return true;
            }

            count += current->arr.size();
            for (int i = 0; i < current->children.size(); i++) {
                if (is_visited(current->children[i], visited3) == false) {
                    visited3.push_back(current->children[i]);
                    q.push(current->children[i]);
                }
            }
        }
        if (count == curr) {
            cout << "No pokemon with name " << n << " and variation " << v << " found!" << endl;
        }
        return false;
    }
		   //this function uses BFS algorithm which is given by Prof. Aman in the Graph 8a Powerpoint slide 63
    Pokemon find_in_btree(string n, string v) {
        vector<Bnode*> visited3;
        if (rootactual == nullptr) {
            cout << "";
        }
        bool stop = false;
        int count = 0;
        queue<Bnode*> q;
        q.push(rootactual);
        visited3.push_back(rootactual);

        while (!q.empty() && stop == false) {
            Bnode* current = q.front();
            q.pop();
            if (find_pokemon_no_print(n, v, current->arr) == true) {
                return find_pokemon_return(n, v, current->arr);
            }

            count += current->arr.size();
            for (int i = 0; i < current->children.size(); i++) {
                if (is_visited(current->children[i], visited3) == false) {
                    visited3.push_back(current->children[i]);
                    q.push(current->children[i]);
                }
            }
        }
        return Pokemon{ -1, "", "", "", "", 0, 0, 0, 0, 0, 0, 0 };
    }

    bool check_if_there(string n, string v) { //check if pokemon in tree already
        if (search_no_print(n, v) == true) {
            return true;
        }
        else {
            return false;
        }
    }

    //Compare two pokemon's total statistics
    string battle(Pokemon p1, Pokemon p2) {
        if (p1.total > p2.total) {
            string p1s = p1.name + " wins!";
            return p1s;
        }
        else if (p1.total < p2.total) {
            string p2s = p2.name + " wins!";
            return p2s;
        }
        else {
            string tie = "Its a tie!";
            return tie;
        }
    }
};

// Function to display the menu
void displayMenu() {
    std::cout << "\nGator Pokemon\n"
        << "1. Search Pokemon\n"
        << "2. Filter by Attribute\n"
        << "3. Insert Pokemon\n"
        << "4. Battle Pokemon\n"
        << "5. Exit\n\n";
}

// Function to validate input for non-negative integers
int getNonNegativeInt() {
    int num;
    while (true) {
        cin >> num;
        if (num >= 0) {
            break;
        }
        else {
            cout << "Please enter a non-negative integer: ";
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
        }
    }
    return num;
}

int main() {

    //hashmap init
    HashMap map;

    //Btree init
    Btree b;

    //insert pokemon from the database
    // Open the CSV file
    //ifstream inputFile("C:/Users/XJXUA/Downloads/PokemonDB.csv");

    //Display Memu
    int choice;
    string name;
    string DS;
    string attribute;
    string word;
    int num;
    bool mode = true; // true: hashmap; false: b tree
    Pokemon newPokemon;

    //battle
    string name1;
    string name2;

    string variation;
    string variation1;
    string variation2;

    //data structure
    do {
        // Prompt the user to choose between a B Tree and a HashMap
        cout << "B Tree or HashMap?\n"
            << "Enter 'B' for B Tree or 'H' for HashMap: ";
        cin >> DS;

        if (DS == "B" || DS == "b") {
            //b init
            //insert pokemon from the database
            // Open the CSV file
            ifstream inputFile("PokemonDB.csv");

            if (!inputFile.is_open()) {
                cerr << "Error opening the file." << endl;
                return 1;
            }

            auto start = high_resolution_clock::now();
            string line;
            getline(inputFile, line); // Read and discard the header line
            int index = 0; //test
            int i = 0;
            // Read data line by line
            while (getline(inputFile, line)) {
                stringstream ss(line);
                Pokemon pokemon;
                b.curr++;
                // Read each column from the CSV
                char comma; // To handle the comma between fields
                ss >> index >> comma; // Read the index and the following comma
                pokemon.index = b.curr;
         
                getline(ss, pokemon.name, ','); // Read the name until the next comma
                getline(ss, pokemon.variation, ',');
                getline(ss, pokemon.type1, ',');
                getline(ss, pokemon.type2, ',');
                ss >> pokemon.total >> comma;
                ss >> pokemon.hp >> comma;
                ss >> pokemon.attack >> comma;
                ss >> pokemon.defense >> comma;
                ss >> pokemon.spattack >> comma;
                ss >> pokemon.spdef >> comma;
                ss >> pokemon.speed >> comma;
				b.visited.clear(); 
                b.insert(b.rootactual, pokemon);
              	b.visited.clear(); 
            } 

            // Close the file
            inputFile.close();

            //Randomly Generate 8,500 Pokemon
			for (int i = 0; i < 8500; i++) {
                bool stop = false;
                Pokemon p;
                p = b.create_new();
                b.visited.clear();
                b.insert(b.rootactual, p);
                b.visited.clear();
            }
            
            mode = false;
            auto end = high_resolution_clock::now();
            duration<double, std::milli> duration = end - start;
            cout << "The runtime for inserting 100,000 data points in B Tree is: " << duration.count() << endl;
        }

        else if (DS == "H" || DS == "h") {
            //hash map init
            //insert pokemon from the database
            // Open the CSV file
            ifstream inputFile("PokemonDB.csv");

            if (!inputFile.is_open()) {
                cerr << "Error opening the file." << endl;
                return 1;
            }

            auto start = high_resolution_clock::now();
            string line;
            getline(inputFile, line); // Read and discard the header line
            int index = 0; //test
            // Read data line by line
            while (getline(inputFile, line)) {
                stringstream ss(line);
                Pokemon pokemon;

                // Read each column from the CSV
                char comma; // To handle the comma between fields
                ss >> pokemon.index >> comma; // Read the index and the following comma
                getline(ss, pokemon.name, ','); // Read the name until the next comma
                getline(ss, pokemon.variation, ',');
                getline(ss, pokemon.type1, ',');
                getline(ss, pokemon.type2, ',');
                ss >> pokemon.total >> comma;
                ss >> pokemon.hp >> comma;
                ss >> pokemon.attack >> comma;
                ss >> pokemon.defense >> comma;
                ss >> pokemon.spattack >> comma;
                ss >> pokemon.spdef >> comma;
                ss >> pokemon.speed >> comma;
                map.insert(pokemon.name, pokemon);
            }

            // Close the file
            inputFile.close();
            for (int i = 0; i < 8500; i++) {
                bool stop = false;
                Pokemon p = map.create_new(); 
                map.insert(p.name, p);
            }
            mode = true;
            auto end = high_resolution_clock::now();
            duration<double, std::milli> duration = end - start;
            cout << "The runtime for inserting 100,000 data points in Hash Map is: " << duration.count() << endl;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (DS != "B" && DS != "b" && DS != "H" && DS != "h");

    do {
        displayMenu();
        std::cout << "Enter your choice: ";

        // Check if the input is a valid integer
        if (!(std::cin >> choice)) {
            std::cin.clear();  // Clear the fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1: //Search Pokemon
            std::cout << "Enter Pokemon name to search: ";
            std::cin >> name;
            
            cout << "Type in variation: ";

            cin.ignore(); // Clear the newline character from the buffer
            std::getline(cin, variation);

            //hash map
            if (mode) {
                auto start = high_resolution_clock::now();
                Pokemon p = map.searchPrint(name, variation);
                if (p.index != -1) {
                    cout << endl;
                    map.print_pokemon(p);
                }
                auto end = high_resolution_clock::now();
                duration<double, std::milli> duration = end - start;
                cout << endl;
                cout << "The runtime for searching Pokemon in Hash Map is: " << duration.count() << endl;
            }
            //b tree
            else {
                auto start = high_resolution_clock::now();
                cout << endl;
                b.search(name, variation);
                auto end = high_resolution_clock::now();
                duration<double, std::milli> duration = end - start;
                cout << endl;
                cout << "The runtime for searching Pokemon in B Tree is: " << duration.count() << endl;
            }

            break;

        case 2: //Filter by Attribute
            cin.ignore();
            std::cout << "Enter attribute category to filter: (variation, type 1, type 2, total statistics, hit points, attack, defense, special attack, special defense, speed): ";
            std::getline(cin, attribute);
            if (attribute == "variation" || attribute == "type 1" || attribute == "type 2") {
                num = 0;
                std::cout << "Enter specific attribute: ";
                std::getline(cin, word);
            }
            else if (attribute == "total statistics" || attribute == "hit points" || attribute == "attack" || attribute == "defense" || attribute == "special attack" || attribute == "special defense" || attribute == "speed") {
                word = "";
                std::cout << "Enter specific attribute: ";
                std::cin >> num;
            }
            else {
                cout << endl;
                cout << "Invalid input choose from (variation, type 1, type 2, total statistics, hit points, attack, defense, special attack, special defense, speed)" << endl;
                break;
            }
            //hash map
            if (mode) {
                auto start = high_resolution_clock::now();
                cout << endl;
                map.filter(attribute, word, num);
                auto end = high_resolution_clock::now();
                duration<double, std::milli> duration = end - start;
                cout << endl;
                cout << "The runtime for filtering Pokemon in Hash Map is: " << duration.count() << endl;
            }
            //b tree
            else {
                auto start = high_resolution_clock::now();
                cout << endl;
                b.filter(attribute, word, num);
                auto end = high_resolution_clock::now();
                duration<double, std::milli> duration = end - start;
                cout << endl;
                cout << "The runtime for filtering Pokemon in B Tree is: " << duration.count() << endl;
            }

            break;

        case 3: //Insert Pokemon

            // Prompt the user to enter information for the Pokemon
            cout << "Enter Pokemon Information:\n";

            //store global index++ to pokemon index

            cout << "Name: ";
            cin.ignore();
            getline(cin, newPokemon.name);

            cout << "Variation: ";
            getline(cin, newPokemon.variation);

            cout << "Type 1: ";
            getline(cin, newPokemon.type1);

            cout << "Type 2: ";
            getline(cin, newPokemon.type2);

            cout << "Total: ";
            newPokemon.total = getNonNegativeInt();

            cout << "HP: ";
            newPokemon.hp = getNonNegativeInt();

            cout << "Attack: ";
            newPokemon.attack = getNonNegativeInt();

            cout << "Defense: ";
            newPokemon.defense = getNonNegativeInt();

            cout << "Special Attack: ";
            newPokemon.spattack = getNonNegativeInt();

            cout << "Special Defense: ";
            newPokemon.spdef = getNonNegativeInt();

            cout << "Speed: ";
            newPokemon.speed = getNonNegativeInt();

            // Display the entered information
            cout << "\nEntered Pokemon Information:\n";
            map.print_pokemon(newPokemon);

            //hash map
            if (mode) {
                auto start = high_resolution_clock::now();
                //insert new pokemon
                bool temp = map.insert(newPokemon.name, newPokemon);
                if (!temp) {
                    cout << endl;
                    cout << "Insertion unsuccessful." << endl; 
                }
                else {
                    auto end = high_resolution_clock::now();
                    duration<double, std::milli> duration = end - start;
                    cout << endl;
                    cout << "Insertion successful!" << endl;
                    cout << endl;
                    cout << "The runtime for inserting Pokemon in Hash Map is: " << duration.count() << endl;
                }
            }
            //b tree
            else {
                bool nope; 
                nope = b.check_if_there(newPokemon.name, newPokemon.variation); 
                if (nope == true) { 
                    cout << endl;
                    cout << "Insertion unsuccessful." << endl; 
                }
                else {
                    auto start = high_resolution_clock::now();
                    b.visited.clear(); 
                    b.curr++; 
                    newPokemon.index = b.curr;
                    b.insert(b.rootactual, newPokemon); 
                    b.visited.clear(); 
                    auto end = high_resolution_clock::now();
                    duration<double, std::milli> duration = end - start;
                    cout << endl;
                    cout << "Insertion successful!" << endl;
                    cout << endl;
                    cout << "The runtime for inserting Pokemon in B Tree is: " << duration.count() << endl;
                }
            }

            break;

        case 4: //Battle Pokemon
            //hash map
            if (mode) {

                Pokemon pokemon1;
                Pokemon pokemon2;
                std::cout << "Enter First Pokemon: ";
                std::cin >> name1;

                cout << "Type in variation: ";
                cin.ignore(); // Clear the newline character from the buffer
                std::getline(cin, variation1);

                if (map.search(name1, variation1).index == -1) {
                    cout << endl;
                    cout << "No Pokemon with name " << name1 << " found!" << endl;
                    break;
                }
                else {
                    pokemon1 = map.search(name1, variation1);
                    cout << endl;
                    map.print_pokemon(pokemon1);
                    cout << endl;
                }

                std::cout << "Enter Second Pokemon: ";
                std::cin >> name2;

                cout << "Type in variation: ";
                cin.ignore(); // Clear the newline character from the buffer
                std::getline(cin, variation2);

                if (map.search(name2, variation2).index == -1) {
                    cout << endl;
                    cout << "No Pokemon with name " << name2 << " found!" << endl;
                    break;
                }
                else {
                    pokemon2 = map.search(name2, variation2);
                    cout << endl;
                    map.print_pokemon(pokemon2);
                    cout << endl;
                }

                auto start = high_resolution_clock::now();
                string temp = map.battlePokemon(pokemon1, pokemon2);
                if (temp == " ") {
                    cout << "It's a tie!" << endl << endl;
                }
                else {
                    cout << temp << " wins!" << endl << endl;
                }
                auto end = high_resolution_clock::now();
                duration<double, std::milli> duration = end - start;
                cout << "The runtime for battling Pokemon in Hash Map is: " << duration.count() << endl;
            }

            //b tree
            else {
                Pokemon pokemon1;
                Pokemon pokemon2;
                std::cout << "Enter First Pokemon: ";
                std::cin >> name1;

                cout << "Type in variation: ";
                cin.ignore(); // Clear the newline character from the buffer
                std::getline(cin, variation1);

                if (b.find_in_btree(name1, variation1).index == -1) {
                    cout << endl;
                    cout << "No Pokemon with name " << name1 << " found!"<< endl;
                    break;
                }
                else {
                    pokemon1 = b.find_in_btree(name1, variation1);
                    cout << endl;
                    b.print_pokemon(pokemon1);
                    cout << endl;
                }

                std::cout << "Enter Second Pokemon: ";
                std::cin >> name2;

                cout << "Type in variation: ";
                cin.ignore(); // Clear the newline character from the buffer
                std::getline(cin, variation2);

                if (b.find_in_btree(name2, variation2).index == -1) {
                    cout << "No Pokemon with name " << name2 << " found!" << endl;
                    break;
                }
                else {
                    pokemon2 = b.find_in_btree(name2, variation2);
                    cout << endl;
                    b.print_pokemon(pokemon2);
                    cout << endl;
                }

                auto start = high_resolution_clock::now();
                string print;
                print = b.battle(pokemon1, pokemon2);
                cout << print << endl << endl;
                auto end = high_resolution_clock::now();
                duration<double, std::milli> duration = end - start;
                cout << "The runtime for battling Pokemon in B Tree is: " << duration.count() << endl;
            }
            break;

        case 5: //Exit
            std::cout << "Exiting program.\n";
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != 5);

    return 0;
}
