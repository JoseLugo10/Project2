// Created by Jose Lugo
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#define CAT_NAME_LEN 25
#define APP_NAME_LEN 50
#define VERSION_LEN 10
#define UNIT_SIZE 3

// A struct of app_info type
struct app_info
{
    char category[CAT_NAME_LEN];
    char app_name[APP_NAME_LEN];
    char version[ VERSION_LEN ];
    float size;
    char units[UNIT_SIZE];
    float price;
};

// A struct of tree type
struct tree
{
    struct app_info record;
    struct tree *left;
    struct tree *right;
};

// A struct of categories type
struct categories
{
    char category[CAT_NAME_LEN];
    struct tree *root;
};

// A struct of hash_table_entry type
struct hash_table_entry
{
    char app_name[APP_NAME_LEN];
    struct tree *app_node;
    struct hash_table_entry *next;
};

// This recursive function takes in 2 tree objects, and inserts them into the binary search tree.
struct tree* insert(struct tree *tree, struct tree *leaf)
{
    // The app_name from the leaf is generated.
    string leafName = "";
    for(int i = 0; i < strlen(leaf->record.app_name); i++)
    {
        leafName += leaf->record.app_name[i];
    }

    // If the tree leaf leads to nullptr, it returns the leaf.
    if(tree == nullptr)
    {
        return leaf;
    }
    else
    {
        // The name of the app from the root is generated.
        string rootName = "";
        for(int i = 0; i < strlen(tree->record.app_name); i++)
        {
            rootName += tree->record.app_name[i];
        }

        // Depending on the ASCII values of the names, they will be inserted either on the left or right side of the root.
        if(leafName < rootName)
        {
            tree->left = insert(tree->left, leaf);
        }
        else if(leafName > rootName)
        {
            tree->right = insert(tree->right, leaf);
        }
    }

    // The tree object is returned.
    return tree;
}

// Although this function is not needed by the program, I made it so i could test out the accuracy of my binary seach tree.
void inorder(struct tree *tree)
{
    if(tree != nullptr)
    {
        inorder(tree->left);
        string name;
        for(int i = 0; i < strlen(tree->record.app_name); i++)
        {
            name += tree->record.app_name[i];
        }
        cout << tree->record.app_name << endl;
        name = "";
        inorder(tree->right);
    }
}

// This function will return true or false whenever a given integer is put in, depending if the number is prime or not.
bool testForPrime(int val)
{
    int limit;
    int factor = 2;

    limit = (long)( sqrtf( (float) val ) + 0.5f );
    while( (factor <= limit) && (val % factor) )
        factor++;

    return(factor > limit);
}

int main(int argc, char* argv[])
{
    // These strings will contain the amount of categories, the category names, and the amount of apps respectively.
    string cats;
    string topic;
    string apps;

    // The amount of app categories is captured and a struct array of categories is dynamically allocated based off the amount of categories.
    getline(cin, cats);
    int n = stoi(cats);
    struct categories *appCategories = new categories[n];
    for(int i = 0; i < n; i++)
    {
        appCategories[i].root = nullptr;
    }

    // A pointer array of tree structs is created based off the amount of categories that exist.
    struct tree *roots = new tree[n];

    // Each line that is captured will contain the category name, so each element in the appCategories array contains a category name.
    for(int i = 0; i < n; i++)
    {
        getline(cin, topic);
        // Because the category variable in the categories struct is a character array, we must go through all elements in each string.
        for(int j = 0; j < topic.length(); j++)
        {
            appCategories[i].category[j] = topic[j];
        }
    }

    // The amount of apps being read is captured from the next line in the inputted file.
    getline(cin, apps);
    int numApps = stoi(apps);

    // Placeholder strings are created to contain each read line from the inputted file.
    string category;
    string name;
    string ver;
    string mem;
    string uni;
    string cost;

    struct tree *trees = new tree[numApps];
    for(int i = 0; i < numApps; i++)
    {
        trees[i].left = nullptr;
        trees[i].right = nullptr;
    }

    // A for loop will go through 6 * numApps of lines in the file in order to get values for each category in the app_info struct.
    for(int i = 0; i < numApps; i++)
    {
        // The category variable is filled.
        getline(cin, category);
        for(int j = 0; j < category.length(); j++)
        {
            trees[i].record.category[j] = category[j];
        }

        // The app_name variable is filled.
        getline(cin, name);
        for(int j = 0; j < name.length(); j++)
        {
            trees[i].record.app_name[j] = name[j];
        }

        // The version variable is filled.
        getline(cin, ver);
        for(int j = 0; j < ver.length(); j++)
        {
            trees[i].record.version[j] = ver[j];
        }

        // The size variable is filled, but the string is parsed from a string to a float before.
        getline(cin, mem);
        float memf = stof(mem);
        trees[i].record.size = memf;

        // The units variable is filled.
        getline(cin, uni);
        for(int j = 0; j < uni.length(); j++)
        {
            trees[i].record.units[j] = uni[j];
        }

        // The price variable is filled, but the string is parsed from a string to a float before.
        getline(cin, cost);
        float costs = stof(cost);
        trees[i].record.price = costs;
    }

    // The categories array will be filled with the first entries of the apps that have that same category.
    int fill = 0;
    string category1;
    string category2;
    for(int i = 0; i < numApps; i++)
    {
        // category1 contains the category of the app
        for(int k = 0; k < strlen(trees[i].record.category); k++)
        {
            category1 += trees[i].record.category[k];
        }

        for(int j = 0; j < n; j++)
        {
            // category2 contains the category of the categories array
            for(int k = 0; k < strlen(appCategories[j].category); k++)
            {
                category2 += appCategories[j].category[k];
            }

            // If they are the same, that app will be inserted into the root.
            if(category1 == category2 && appCategories[j].root == nullptr)
            {
                appCategories[j].root = &trees[i];
            }

            category2 = "";
        }

        // This loop will count the amount of times a nullptr exists, to determine of all of the roots for the categories have been filled.
        for(int k = 0; k < n; k++)
        {
            if(appCategories[k].root == nullptr)
            {
                fill++;
            }
        }

        // If all of the categories have been filled with a root, then we exit out of the for loop.
        if(fill == 0)
        {
            break;
        }

        fill = 0;
        category1 = "";
    }

    category1 = "";
    category2 = "";

    // These strings will contain the names of the root and the app.
    string aname = "";
    string rname = "";

    // With this nested for loop, we will be able to insert all of the apps into the binary search tree.
    for(int i = 0; i < n; i++)
    {
        // categpory1 contains the category from the categories array.
        for(int k = 0; k < strlen(appCategories[i].category); k++)
        {
            category1 += appCategories[i].category[k];
        }

        if(appCategories[i].root == nullptr)
        {

        }
        else
        {
            for(int j = 0; j < numApps; j++)
            {
                // category2 contains the category of the app.
                for(int k = 0; k < strlen(trees[j].record.category); k++)
                {
                    category2 += trees[j].record.category[k];
                }

                // The name of the app is put into the string aname.
                for(int v = 0; v < strlen(trees[j].record.app_name); v++)
                {
                    aname += trees[j].record.app_name[v];
                }

                // The name of the app from the root of the category is put into the string rname.
                for(int v = 0; v < strlen(appCategories[i].root->record.app_name); v++)
                {
                    rname += appCategories[i].root->record.app_name[v];
                }

                if(category1 == category2 && aname == rname)
                {

                }

                // If the categories match and the names are not the same, then it will be inserted into the binary search tree.
                if(category1 == category2 && aname != rname)
                {
                    // The recursive function insert is used to place elements in the binary search tree.
                    insert(appCategories[i].root, &trees[j]) ;
                }

                category2 = "";
                rname = "";
                aname = "";
            }
        }

        category1 = "";
    }

    //inorder(appCategories[0].root);

    // The hash table size is generated by taking the number of apps multiplied by 2, and we then use the testForPrime function to find the nearest prime number.
    int m = 2 * numApps;
    while(testForPrime(m) == false)
    {
        m++;
    }

    // An array of hash_table_entry is created with size m
    struct hash_table_entry *hash_table = new hash_table_entry[m];
    for(int i = 0; i < m; i++)
    {
        hash_table[i].app_node = nullptr;
        hash_table[i].next = nullptr;
    }


    // These variables will be used in calculating the key the apps hash to.
    int key = 0;
    int keyMod;
    for(int i = 0; i < numApps; i++)
    {
        // The sum of all of the ASCII values from the app name is summed up.
        for(int j = 0; j < strlen(trees[i].record.app_name); j++)
        {
            key += int(trees[i].record.app_name[j]);
        }

        // When then find the value the name hashes to by computing key mod m, the prime number we calculated.
        keyMod = (key % m);

        // If the key the values hases to is null, then it is the first entry into that has value.
        if(hash_table[keyMod].app_node == nullptr)
        {
            // The name is set and the app_node is set to the app.
            for(int j = 0; j < strlen(trees[i].record.app_name); j++)
            {
                hash_table[keyMod].app_name[j] = trees[i].record.app_name[j];
            }

            hash_table[keyMod].app_node = &trees[i];
        }
        else
        {
            // If the key the app hashes to is already taken, we add the app from the head of the hash table.
            struct hash_table_entry *temp = new hash_table_entry;
            temp->app_node = &trees[i];

            for(int k = 0; k < strlen(trees[i].record.app_name); k++)
            {
                temp->app_name[k] = trees[i].record.app_name[k];
            }

            temp->next = &hash_table[keyMod];
            cout << temp->next->app_name << endl;
            cout << temp->next->app_node->record.version << endl;
            cout << temp->app_name << endl;
            cout << temp->app_node->record.version << endl;
            hash_table[keyMod] = *temp;
        }
    }

    cout << "Node: " << hash_table[8].app_node->record.version<< endl;
    cout << "Node next: " << hash_table[8].next->app_node->record.version << endl;


    // Variables used to capture how many queries are being made.
    string q;
    getline(cin, q);
    int qs = stoi(q);

    // Based on the amount of queries, a for loop will iterate a qs amount of times.
    for(int i = 0; i < qs; i++)
    {
        // These strings are set to be the input, the command, and the app that is being searched for.
        string operation = "";
        string pick = "";
        string decision;

        getline(cin, decision);

        // Strings operation and pick are set by splitting the decision string.
        for(int j = 0; j < 8; j++)
        {
            operation += decision[j];
        }

        for(int j = 9; j < decision.length(); j++)
        {
            pick += decision[j];
        }

        // The integer ping is used for when an app is found.
        int ping = 0;

        // If the input is find app <app>, then it will enter this if statement.
        if(operation == "find app")
        {
            // The for loop iterates through all of the nodes in the hash table.
            for(int j = 0; j < m; j++)
            {
                if(hash_table[j].app_node == nullptr)
                {

                }
                else
                {
                    string same;
                    for(int k = 0; k < strlen(hash_table[j].app_name); k++)
                    {
                        same += hash_table[j].app_name[k];
                    }

                    // If there is a match, the details are printed and ping is set to 1.
                    if(same == pick)
                    {
                        cout << "Found Application: " << pick << endl;
                        cout << "   Category: " << hash_table[j].app_node->record.category << endl;
                        cout << "   Application Name: " << hash_table[j].app_node->record.app_name << endl;
                        cout << "   Version: " << hash_table[j].app_node->record.version << endl;
                        cout << "   Size: " << hash_table[j].app_node->record.size << endl;
                        cout << "   Units: " << hash_table[j].app_node->record.units << endl;
                        cout << "   Price: $" << hash_table[j].app_node->record.price << endl;
                        ping = 1;
                        break;
                    }
                }
            }

            // If ping ends up being 0, that means that the app could have not been found, a message is printed.
            if(ping != 1)
            {
                cout << "Application " << pick << " not found" << endl;
            }
        }
        if(operation == "find category")
        {
            // Coming soon
        }
        if(operation == "find price free")
        {
            // Coming soon
        }
        if(operation == "range ")
        {
            // Coming soon
        }

        cout << endl;
    }

    // All dynamically allocated memory for the data structures is deleted.
    delete[] hash_table;
    delete[] trees;
    delete[] roots;
    delete[] appCategories;

    return 0;
}