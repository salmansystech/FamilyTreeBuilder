#include "familytree.hh"
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <queue>

using namespace std;

// Helper functions declaration, these help in finding the tallest and shortest persons in the family tree.
Person* findTallest(Person* p);
Person* findShortest(Person* p);


// Constructor for the Familytree class. Initializes an empty family tree.
Familytree::Familytree() {
    // No specific initialization required.
}

/**
* @brief: Adds a new person to the family tree.
* @param  id: The unique name/ID of the person.
* @param  height: The height of the person.
* @param  output (A stream to print out errors or confirmations).
*/
void Familytree::addNewPerson(const string& id, int height, ostream &output) {
    // Check if the person is already in the tree using the getPointer function.
    if (getPointer(id) != nullptr) {
        output << ALREADY_ADDED << endl; // If already added, print error and return.
        return;
    }

    // Create a new person and assign the provided id and height.
    Person* new_person = new Person;
    new_person->id_ = id;
    new_person->height_ = height;

    // Add the new person to the family tree (vector of persons).
    persons_.push_back(new_person);
}

/**
* @brief: This function establishes a parent-child relationship between people in the family tree.
* @param child_id: The name of the child.
* @param parents: A list of parent names (up to two).
* @param output (A stream to print out errors if needed).
*/
void Familytree::addRelation(const string& child_id, const vector<string>& parents, ostream& output) {
    // Look for the child in the family tree.
    Person* child = getPointer(child_id);

    // If the child doesn't exist, print an error and return.
    if (child == nullptr) {
        printNotFound(child_id, output);
        return;
    }

    // Loop through the parents and connect them to the child.
    for (size_t i = 0; i < parents.size(); ++i) {
        if (parents[i] != "-") { // If parent is valid (not "-").
            // Find the parent in the family tree.
            Person* parent = getPointer(parents[i]);
            if (parent != nullptr) {
                // Assign the parent to the child's parent list.
                child->parents_.at(i) = parent;
                // Add the child to the parent's list of children.
                parent->children_.push_back(child);
            }
        }
    }
}

/**
* @brief:Prints all the people in the family tree in alphabetical order by their ID.
* @param output (The stream where the list of people is printed).
 */
void Familytree::printPersons(Params, ostream& output) const {
    // Sort the people by their IDs in alphabetical order.
    vector<Person*> sorted_persons = persons_;
    sort(sorted_persons.begin(), sorted_persons.end(),
        [](Person* a, Person* b) {
            return a->id_ < b->id_;
        });

    // Print each person's ID and height.
    for (const auto& person : sorted_persons) {
        output << person->id_ << ", " << person->height_ << endl;
    }
}

/**
* @brief: Prints all children of a given person in the family tree.
* @param A list where params[0] is the person's name.
* @param output (The stream to print the list of children).
*/
void Familytree::printChildren(Params params, ostream& output) const {
    // Find the person using their name (ID).
    Person* person = getPointer(params.at(0));
    if (person == nullptr) {
        printNotFound(params.at(0), output); // If not found, print error and return.
        return;
    }

    // Check if the person has children.
    if (person->children_.empty()) {
        output << person->id_ << " has no children." << endl;
    } else {
        // Convert the list of children to a set of their IDs and print them.
        IdSet children_set = vectorToIdSet(person->children_);
        printGroup(person->id_, "children", children_set, output);
    }
}

/**
* @brief: Prints all parents of a given person in the family tree.
* @param A list where params[0] is the person's name.
* @param output (The stream to print the list of parents).
*/
void Familytree::printParents(Params params, ostream& output) const {
    // Find the person using their name (ID).
    Person* person = getPointer(params.at(0));
    if (person == nullptr) {
        printNotFound(params.at(0), output); // If not found, print error and return.
        return;
    }

    // Get the person's parents and print them.
    vector<Person*> parents = person->parents_;
    IdSet parents_set = vectorToIdSet(parents);
    if (parents_set.empty()) {
        output << person->id_ << " has no parents." << endl;
    } else {
        printGroup(person->id_, "parents", parents_set, output);
    }
}

/**
* @brief: Prints all siblings of a given person in the family tree.
* @param: A list where params[0] is the person's name.
* @param output (The stream to print the list of siblings).
*/
void Familytree::printSiblings(Params params, ostream& output) const {
    // Find the person using their name (ID).
    Person* person = getPointer(params.at(0));
    if (person == nullptr) {
        printNotFound(params.at(0), output); // If not found, print error and return.
        return;
    }

    // Find siblings by looking at the parents' other children.
    IdSet sibling_set;
    for (Person* parent : person->parents_) {
        if (parent != nullptr) {
            for (Person* sibling : parent->children_) {
                if (sibling->id_ != person->id_) {
                    sibling_set.insert(sibling->id_);
                }
            }
        }
    }

    // Print the siblings, or show that none exist.
    if (sibling_set.empty()) {
        output << person->id_ << " has no siblings." << endl;
    } else {
        printGroup(person->id_, "siblings", sibling_set, output);
    }
}

/**
* @brief: Prints all cousins of a given person in the family tree.
* @param: A list where params[0] is the person's name.
* @param: output (The stream to print the list of cousins).
*/
void Familytree::printCousins(Params params, ostream& output) const {
    // Find the person using their name (ID).
    Person* person = getPointer(params.at(0));
    if (person == nullptr) {
        printNotFound(params.at(0), output); // If not found, print error and return.
        return;
    }

    // Find cousins by checking parents' siblings' children.
    IdSet cousin_set;
    for (Person* parent : person->parents_) {
        if (parent != nullptr) {
            for (Person* grandparent : parent->parents_) {
                if (grandparent != nullptr) {
                    for (Person* uncle_aunt : grandparent->children_) {
                        if (uncle_aunt->id_ != parent->id_) {
                            for (Person* cousin : uncle_aunt->children_) {
                                cousin_set.insert(cousin->id_);
                            }
                        }
                    }
                }
            }
        }
    }

    // Print the cousins, or show that none exist.
    if (cousin_set.empty()) {
        output << person->id_ << " has no cousins." << endl;
    } else {
        printGroup(person->id_, "cousins", cousin_set, output);
    }
}

/**
* @brief: Prints the grandchildren of a person up to a given level (generation).
* @param: A list where params[0] is the person's name and params[1] is the level.
* @param: output (The stream to print the list of grandchildren).
*/
void Familytree::printGrandChildrenN(Params params, ostream& output) const {
    // Check if two parameters are provided.
    if (params.size() != 2) {
        output << "Wrong amount of parameters." << endl;
        return;
    }

    const std::string& id = params.at(0);
    int generationLevel = std::stoi(params.at(1));

    // Error for invalid level.
    if (generationLevel < 1) {
        output << "Error. Level can't be less than 1." << endl;
        return;
    }

    // Find the person using their name (ID).
    Person* person = getPointer(id);
    if (person == nullptr) {
        printNotFound(id, output);
        return;
    }

    IdSet grandchildren_ids;

    // Handle level 1 (direct grandchildren).
    if (generationLevel == 1) {
        for (Person* child : person->children_) {
            for (Person* grandchild : child->children_) {
                grandchildren_ids.insert(grandchild->id_);
            }
        }

        // Print the grandchildren or show that none exist.
        if (!grandchildren_ids.empty()) {
            output << id << " has " << grandchildren_ids.size() << " grandchildren:" << endl;
            for (const auto& grandchild_id : grandchildren_ids) {
                output << grandchild_id << endl;
            }
        } else {
            output << id << " has no grandchildren." << endl;
        }
    }
    // Handle level 2 (great-grandchildren).
    else if (generationLevel == 2) {
        for (Person* child : person->children_) {
            for (Person* grandchild : child->children_) {
                for (Person* greatGrandchild : grandchild->children_) {
                    grandchildren_ids.insert(greatGrandchild->id_);
                }
            }
        }

        // Print the great-grandchildren or show that none exist.
        if (!grandchildren_ids.empty()) {
            output << id << " has " << grandchildren_ids.size() << " great-grandchildren:" << endl;
            for (const auto& greatGrandchild_id : grandchildren_ids) {
                output << greatGrandchild_id << endl;
            }
        } else {
            output << id << " has no great-grandchildren." << endl;
        }
    }
    // Handle levels greater than 2.
    else {
        if (grandchildren_ids.empty()) {
            output << id << " has no ";
            for (int i = 2; i <= generationLevel; ++i) {
                output << "great-";
            }
            output << "grandchildren." << endl;
        }
    }
}

/**
* @brief: Prints all the grandparents of a person up to a given generation.
* @param: A list where params[0] is the person's name and params[1] is the level.
* @param: output (The stream to print the list of grandparents).
*/
void Familytree::printGrandParentsN(Params params, std::ostream& output) const {
    // Check if two parameters are provided.
    if (params.size() != 2) {
        output << "Wrong amount of parameters." << endl;
        return;
    }

    const std::string& id = params.at(0);
    int N = std::stoi(params.at(1));

    // Error for invalid level.
    if (N < 1) {
        output << "Error. Level can't be less than 1." << endl;
        return;
    }

    // Find the person using their name (ID).
    Person* person = getPointer(id);
    if (person == nullptr) {
        printNotFound(id, output);
        return;
    }

    // Use a queue to perform a breadth-first search for grandparents up to level N.
    std::queue<std::pair<Person*, int>> queue;
    queue.push({person, 0});
    IdSet grandparents;

    while (!queue.empty()) {
        Person* current = queue.front().first;
        int depth = queue.front().second;
        queue.pop();

        if (depth == N) {
            grandparents.merge(vectorToIdSet(current->parents_));
        } else if (depth < N) {
            for (Person* parent : current->parents_) {
                if (parent != nullptr) {
                    queue.push({parent, depth + 1});
                }
            }
        }
    }

    // Print the grandparents or show that none exist.
    if (!grandparents.empty()) {
        output << id << " has " << grandparents.size();
        if (N == 1) {
            output << " grandparents:" << endl;
        } else {
            output << " great-";
            for (int i = 2; i < N; ++i) {
                output << "great-";
            }
            output << "grandparents:" << endl;
        }

        for (const auto& grandparent_id : grandparents) {
            output << grandparent_id << endl;
        }
    } else {
        output << id << " has no ";
        if (N == 1) {
            output << "grandparents." << endl;
        } else {
            output << "great-";
            for (int i = 2; i < N; ++i) {
                output << "great-";
            }
            output << "grandparents." << endl;
        }
    }
}

/**
* @brief: Finds and prints the tallest person in a given person's lineage.
* @param: A list where params[0] is the person's name.
* @param: output (The stream to print the result).
*/
void Familytree::printTallestInLineage(Params params, ostream& output) const {
    // Find the person using their name (ID).
    Person* person = getPointer(params.at(0));
    if (person == nullptr) {
        printNotFound(params.at(0), output); // If not found, print error and return.
        return;
    }

    // Find the tallest person in their lineage.
    Person* tallest = findTallest(person);
    if (tallest != nullptr) {
        if (tallest == person) {
            // Print if the person themselves is the tallest.
            output << "With the height of " << tallest->height_ << ", "
                   << tallest->id_ << " is the tallest person in his/her lineage." << endl;
        } else {
            // Print if someone else in the lineage is taller.
            output << "With the height of " << tallest->height_ << ", "
                   << tallest->id_ << " is the tallest person in "
                   << person->id_ << "'s lineage." << endl;
        }
    }
}

/**
* @brief: This is helper function to find the tallest person in a person's lineage used in previous fucntion
* @param: A pointer to the person to start searching from.
* Returns a pointer to the tallest person found.
*/
Person* findTallest(Person* p) {
    if (!p) return nullptr;

    Person* tallest = p;
    for (Person* child : p->children_) {
        Person* tallest_descendant = findTallest(child);
        if (tallest_descendant && tallest_descendant->height_ > tallest->height_) {
            tallest = tallest_descendant;
        }
    }
    return tallest;
}

/**
* @brief: Finds and prints the shortest person in a given person's lineage.
* @param: A list where params[0] is the person's name.
* @param: output (The stream to print the result).
*/
void Familytree::printShortestInLineage(Params params, ostream& output) const {
    // Find the person using their name (ID).
    Person* person = getPointer(params.at(0));
    if (person == nullptr) {
        printNotFound(params.at(0), output); // If not found, print error and return.
        return;
    }

    // Find the shortest person in their lineage.
    Person* shortest = findShortest(person);
    if (shortest != nullptr) {
        output << "With the height of " << shortest->height_ << ", "
               << shortest->id_ << " is the shortest person in his/her lineage." << endl;
    }
}

/**
* @brief: This is helper function to find the shortest person in a person's lineage used in previous fucntion.
* @param: A pointer to the person to start searching from.
* Returns a pointer to the shortest person found.
*/
Person* findShortest(Person* p) {
    if (!p) return nullptr;

    Person* shortest = p;
    for (Person* child : p->children_) {
        Person* shortest_descendant = findShortest(child);
        if (shortest_descendant && shortest_descendant->height_ < shortest->height_) {
            shortest = shortest_descendant;
        }
    }
    return shortest;
}

//UTILITY FUNCTIONS BELOW

/**
* @brief: Searches for a person in the family tree by their ID.
* @param: id which is The person's name/ID.
* Returns a pointer to the person if found, or nullptr if not found.
*/
Person* Familytree::getPointer(const string& id) const {
    for (const auto& person : persons_) {
        if (person->id_ == id) {
            return person;
        }
    }
    return nullptr;
}

/**
* @brief: Prints an error message if the person with the given ID is not found.
* @param: id: The person's ID that couldn't be found.
* @param: output (The stream to print the result).
*/
void Familytree::printNotFound(const string& id, ostream& output) const {
    output << "Error. " << id << " not found." << endl;
}

/**
* @brief: Function to print a group of people (e.g., children, siblings, etc.)
* @param: id: The person's name or ID.
* @param: group: The group being printed (e.g., "children", "siblings").
* @param: container: A set of person IDs to be printed.
* @param: output (The stream to print the result).
*/
void Familytree::printGroup(const string& id, const string& group, const IdSet& container, ostream& output) const {
    // If the container is empty, the person has no members in the specified group.
    if (container.empty()) {
        output << id << " has no " << group << "." << endl;
    } else {
        // Print the number of people in the group and list them.
        output << id << " has " << container.size() << " " << group << ":" << endl;
        for (const auto& member : container) {
            output << member << endl;
        }
    }
}

/**
* @brief: Converts a vector of Person pointers to a set of their IDs.
* @param: container: A vector of Person pointers.
* Returns a set of their IDs.
*/
IdSet Familytree::vectorToIdSet(const vector<Person*>& container) const {
    IdSet id_set;
    for (const auto& person : container) {
        if (person != nullptr) {
            id_set.insert(person->id_);
        }
    }
    return id_set;
}

