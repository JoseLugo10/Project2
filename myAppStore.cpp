// Created by Jose Lugo
#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
#include <cstring> // Not used in project, only exists to run on server.

using namespace std;

#define CAT_NAME_LEN 25
#define APP_NAME_LEN 50
#define VERSION_LEN 10
#define UNIT_SIZE 3

// A struct to contain information about each app.
struct app_info
{
    char category[CAT_NAME_LEN];
    char app_name[APP_NAME_LEN];
    char version[ VERSION_LEN ];
    float size;
    char units[UNIT_SIZE];
    float price;
};

// A struct for a tree node in binary search trees.
struct tree
{
    struct app_info record;
    struct tree *left;
    struct tree *right;
};

// A struct which contains a category name, and a pointer to a BST.
struct categories
{
    char category[CAT_NAME_LEN];
    struct tree *root;
};

// A struct which contains a hash table entry.
struct hash_table_entry
{
    char app_name[APP_NAME_LEN];
    struct tree *app_node;
    struct hash_table_entry *next;
};

// This function will find the instance where an inputted name is found in a hash table, and return 1 if it has been found.
void searchHashName(hash_table_entry *hash, string name, int &num)
{
    // A temporary hash table object is created.
    struct hash_table_entry *ht = new hash_table_entry();
    ht = hash;
    string hashing;

    // Will only go here if the hash table isn't null.
    while(ht != NULL)
    {
        // Ths tring hashing will contain the app name inside the hash table entry.
        for(int i = 0; i < strlen(hash->app_name); i++)
        {
            hashing += hash->app_name[i];
        }

        // If the hashing string is equal to the inputted name, then we have successfully found the application.
        if(hashing == name)
        {
            cout << "Found Application: " << hashing << endl;
            cout << "\t\tCategory: " << ht->app_node->record.category << endl;
            cout << "\t\tApplication Name: " << ht->app_node->record.app_name <<endl;
            cout << "\t\tVersion: " << ht->app_node->record.version << endl;
            cout << "\t\tSize: " << ht->app_node->record.size << endl;
            cout << "\t\tUnits: " << ht->app_node->record.units << endl;
            cout << "\t\tPrice: $";

            // Fixed and setprecision are used to format the float to contain 0s after the decimal point.
            cout << fixed;
            cout << setprecision(2);
            cout << ht->app_node->record.price << endl;
            cout << endl;
            num++;
            break;
        }

        // We iterate through the next hash table entry.
        ht = ht->next;
    }
}

// The getNode function is an easy way to create a new node for a BST.
struct tree* getNode(struct app_info info)
{
    // Creates the tree object, sets the record to the input, and sets the children nodes to null.
    struct tree *node = new tree();
    node->record = info;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// the insertBST allows for us to insert a node into a BST.
struct tree* insertBST(struct tree *bst, struct app_info info)
{
    // The base case will occur if the BST is set to null.
    if(bst == NULL)
    {
        bst = getNode(info);
    }
    // We recursively call the insertBST function depending on whichever name has a greater or lower ASCII value.
    else if(bst->record.app_name[0] >= info.app_name[0])
    {
        bst->left = insertBST(bst->left, info);
    }
    else
    {
        bst->right = insertBST(bst->right, info);
    }
    return bst;
}

// The searchBST function will go through a BST to find a specific node, and will return that node if it is found.
struct tree* searchBST(struct tree *bst, app_info info)
{
    // The app names from the input and the BST are generated.
    string name1 = "";
    string name2 = "";
    for(int i = 0; i < strlen(bst->record.app_name); i++)
    {
        name1 += bst->record.app_name[i];
    }
    for(int i = 0; i < strlen(info.app_name); i++)
    {
        name2 += info.app_name[i];
    }

    // Base case where the BST is equal to null.
    if(bst == NULL || name1 == name2)
    {
        return bst;
    }

    if(name1 < name2)
    {
        return searchBST(bst->right, info);
    }

    return searchBST(bst->left, info);
}

// This function was mainly used to check the correctness of the BST.
void inorder(struct tree *bst)
{
    // We iterate through the entire BST and the apps are printed.
    if(bst != NULL)
    {
        inorder(bst->left);
        cout << "\t\t" << bst->record.app_name << endl;
        inorder(bst->right);
    }
}

// Thr inorderFree function was used to check which apps were free in each BST.
void inorderFree(struct tree *bst, int &amount)
{
    // The code itself is very similar ti the inorder function, because they can be applied the same way.
    if(bst != NULL)
    {
        inorderFree(bst->left, amount);
        if(bst->record.price == 0.00)
        {
            cout << "\t\t" << bst->record.app_name << endl;

            // Since amount is incremented, that means that back in the main function, we will know that at least one app is considered free.
            amount++;
        }
        inorderFree(bst->right, amount);
    }
}

// The inorderRange function was used to check which apps were within a certain price range.
void inorderRange(struct tree *bst, float f1, float f2, int &amount)
{
    // The code itself is very similar ti the inorder function, because they can be applied the same way.
    if(bst != NULL)
    {
        inorderRange(bst->left, f1, f2, amount);
        if(bst->record.price >= f1 && bst->record.price <= f2)
        {
            cout << "\t\t" << bst->record.app_name << endl;

            // Since amount is set to 1, this means that we have found at least one app that is within this price range.
            amount = 1;
        }
        inorderRange(bst->right, f1, f2, amount);
    }
}

// The inorderLetters function was used to check which apps were within a certain range of letters.
void inorderLetters(struct tree *bst, string s1, string s2, int &amount)
{
    // The code itself is very similar ti the inorder function, because they can be applied the same way.
    if(bst != NULL)
    {
        inorderLetters(bst->left, s1, s2, amount);
        if(bst->record.app_name[0] >= s1[0] && bst->record.app_name[0] <= s2[0])
        {
            cout << "\t\t" << bst->record.app_name << endl;

            // Since the amount is set to one, this means that we have found at least one app that is within the letter range we have inputted.
            amount = 1;
        }
        inorderLetters(bst->right, s1, s2, amount);
    }
}

// The insertAtHeadHash function is used to insert a data into the hash table we have created.
void insertAtHeadHash(hash_table_entry *hash, app_info info)
{
    // A new hash table entry object is created, and we set the data equal to out inputted hash table.
    hash_table_entry *hasht = new hash_table_entry();
    for(int i = 0; i < strlen(info.app_name); i++)
    {
        hasht->app_name[i] = info.app_name[i];
    }
    hasht->app_node = hash->app_node;
    hasht->next = hash;
    hash = hasht;
}

void deleteHash(hash_table_entry *hash, string name)
{
    if(hash != NULL)
    {

    }
}

// The printListHash function was mainly used to check to see the accuracy of my hash table. This is not actually used in the project.
void printListHash(hash_table_entry *table)
{
    while(table != NULL)
    {
        cout << table->app_name << " ";
        table = table->next;
    }
    cout << endl;
}

// The testForPrime function is a boolean function which will return true if the inputted integer is a prime number.
bool testForPrime(int val)
{
    int limit;
    int factor = 2;

    limit = (long)( sqrtf( (float) val ) + 0.5f );
    while( (factor <= limit) && (val % factor) )
        factor++;

    return(factor > limit);
}
/*
struct tree* minVal(struct tree *bst)
{
    struct tree *bst1 = bst;
    while(bst1 != NULL && bst1->left != NULL)
    {
        bst1 = bst1->left;
    }
    return bst1;
}
*/
/*struct tree* deleteBST(struct tree *bst, string name)
{
    if(bst == NULL)
    {
        return bst;
    }

    string bstName = "";
    for(int i = 0; i < strlen(bst->record.app_name); i++)
    {
        bstName += bst->record.app_name[i];
    }

    if(name < bstName)
    {
        bst->left = deleteBST(bst->left, name);
    }
    else if(name > bstName)
    {
        bst->right = deleteBST(bst->right, name);
    }
    else
    {
        if(bst->left == NULL)
        {
            struct tree *temp = bst->right;
            free(bst);
            return temp;
        }
        else if(bst->right == NULL)
        {
            struct tree *temp = bst->left;
            free(bst);
            return temp;
        }

        struct tree* temp = minVal(bst->right);
        string s1 = "";
        string s2 = "";
        for(int i = 0; i < strlen(bst->record.app_name); i++)
        {
            s1 += bst->record.app_name[i];
        }
        for(int i = 0; i < strlen(temp->record.app_name); i++)
        {
            s2 += temp->record.app_name[i];
        }

        bst->record = temp->record;
        bst->right = deleteBST(bst->right, s2);
    }
    return bst;
}
*/


int main(int argc, char* argv[])
{
    // These string variables will contain information about the apps we are inputting.
    string cats;
    string topic;
    string apps;

    // While loop will go until we have reached the end of the file.
    while(!cin.eof())
    {
        // We receive and convert into an integer the amount of categories in the file.
        getline(cin, cats);
        int n = stoi(cats);

        // We create an array of appCategories which will contain all of the categories that we will have in the app store.
        struct categories *appCategories = new categories[n];
        for(int i = 0; i < n; i++)
        {
            appCategories[i].root = NULL;
            getline(cin, topic);
            for(int j = 0; j < topic.length(); j++)
            {
                appCategories[i].category[j] = topic[j];
            }
        }

        // We receive and convert into an integer the number of apps within the app store.
        getline(cin, apps);
        int numApps = stoi(apps);

        // Multiple string variables are created which will contain all of the information about the apps we are inserting into the data structures.
        string category;
        string name;
        string ver;
        string mem;
        string uni;
        string cost;

        // We create an array of tree objects which will act as BSTs for each individual category.
        struct tree **bst;
        bst = new tree*[n];
        for(int i = 0; i < n; i++)
        {
            bst[i] = NULL;
        }

        // Using the testForPrime function, we will be able to generate a prime number based off the amount of apps we have.
        int m = 2 * numApps;
        while(testForPrime(m) == false)
        {
            m++;
        }

        // With out prime number m, we can now make a hash table that contains m keys.
        struct hash_table_entry **hashT;
        hashT = new hash_table_entry*[m];
        for(int i = 0; i < m; i++)
        {
            hashT[i] = NULL;
        }

        // Variables key and keyMod will be used in the implementation of our hash table.
        int key = 0;
        int keyMod;

        // The for loop will iterate through the amount of apps that we are inserting into the app store.
        for(int i = 0; i < numApps; i++)
        {
            // The apps struct will contain all the information about each app that we are inserting.
            struct app_info *apps = new app_info;

            // The category for the app is captured.
            getline(cin, category);
            for(int j = 0; j < category.length(); j++)
            {
                apps->category[j] = category[j];
            }

            // The name of the app is captured.
            getline(cin, name);
            for(int j = 0; j < name.length(); j++)
            {
                apps->app_name[j] = name[j];
            }

            // Th version of the app is captured.
            getline(cin, ver);
            for(int j = 0; j < ver.length(); j++)
            {
                apps->version[j] = ver[j];
            }

            // The memory of the app is captured and converted into a float.
            getline(cin, mem);
            float storage = stof(mem);
            apps->size = storage;

            // The units of the app is captured.
            getline(cin, uni);
            for(int j = 0; j < uni.length(); j++)
            {
                apps->units[j] = uni[j];
            }

            // The price of the app is captured and converted into a float.
            getline(cin, cost);
            float costs = stof(cost);
            apps->price = costs;

            // The for loop will go through all of the appCategories to set their roots, and insert into the BSTs.
            for(int k = 0; k < n; k++)
            {
                string first = "";
                for(int q = 0; q < strlen(apps->category); q++)
                {
                    first += apps->category[q];
                }
                string second = "";
                for(int q = 0; q < strlen(appCategories[k].category); q++)
                {
                    second += appCategories[k].category[q];
                }

                // If the two categories match, then we will insert into the BST.
                if(first == second)
                {
                    bst[k] = insertBST(bst[k], *apps);
                }

                // If the pointer to the root is empty for a specific category, it will be set here.
                if(appCategories[k].root == NULL)
                {
                    appCategories[k].root = bst[k];
                }
            }

            // The sum of the ASCII values for each app is calculated here.
            for(int j = 0; j < strlen(apps->app_name); j++)
            {
                key += int(apps->app_name[j]);
            }

            // The values for which the app will hash to on the hash table is calculated.
            keyMod = key % m;
            key = 0;

            // If the key to the hash table is empty, then whatever app that is being iterated through will be the first one in the hash table.
            if(hashT[keyMod] == NULL)
            {
                // A new hash table entry object is created and we set all of the data for that hash table entry.
                hashT[keyMod] = new hash_table_entry();
                for(int j = 0; j < strlen(apps->app_name); j++)
                {
                    hashT[keyMod]->app_name[j] = apps->app_name[j];
                }

                for(int j = 0; j < n; j++)
                {
                    string c1 = "";
                    string c2 = "";
                    for(int k = 0; k < strlen(appCategories[j].category); k++)
                    {
                        c1 += appCategories[j].category[k];
                    }

                    for(int k = 0; k < strlen(apps->category); k++)
                    {
                        c2 += apps->category[k];
                    }

                    if(c1== c2)
                    {
                        hashT[keyMod]->app_node = searchBST(bst[j], *apps);
                        break;
                    }
                }

                hashT[keyMod]->next = NULL;
            }
            // If a specific key to a hash is already filled, then we will use the insertAtHeadHash function to insert at the head of the hash table.
            else
            {
                insertAtHeadHash(hashT[keyMod], *apps);
            }
        }

        // We capture and convert into an integer the amount of queries that we will have to conduct.
        string queries;
        getline(cin, queries);
        int number = stoi(queries);

        // We will iterate through all of the apps we have inserted.
        for(int i = 0; i < number; i++)
        {
            // These strings will have multiple uses depending on what query is chosen.
            string holder;
            string s1;
            string s2;
            string s3;
            string s4;
            string s5;

            // The integers are used to determine when quotation marks ans spaces occur. This is useful in determining heat command the user has chosen.
            int quotes = 0;
            int spaces = 0;
            int mod = 0;

            getline(cin, holder);

            // The amount of spaces outside of quotations and the amount of quotation marks are calculated.
            for(int i = 0; i < holder.length(); i++)
            {
                if(holder[i] == '"')
                {
                    quotes++;
                    mod++;
                }
                if(holder[i] == ' ' && mod % 2 == 0)
                {
                    spaces++;
                }
            }

            // If there were no quotes within the holder string, then that means we are using the find price free query.
            if(quotes == 0)
            {
                // We go thorugh each category to find any apps that are free. If none are found, the program will let the user know.
                for(int j = 0; j < n; j++)
                {
                    cout << "Free Applications in Category: " << appCategories[j].category << endl;
                    int instance = 0;
                    inorderFree(appCategories[j].root, instance);
                    if(instance == 0)
                    {
                        cout << "\t\tNo free applications found" << endl;
                    }
                    cout << endl;
                }
            }

            // The program will go here whenever the find app or find category query is called.
            if(spaces == 2 && quotes == 2)
            {
                // Each number string that is being calculated is either a command, or an app name/category.
                int stop;

                // s1 contains the command
                for(int j = 0; j < holder.length(); j++)
                {
                    if(holder[j] == '"')
                    {
                        stop = j;
                        break;
                    }
                    s1 += holder[j];
                }

                // s2 contains the app name or category
                for(int j = stop + 1; j < holder.length(); j++)
                {
                    if(holder[j] == '"')
                    {
                        break;
                    }
                    s2 += holder[j];
                }

                int found = 0;

                // If find app is chosen, the program will use the searchHashName function to find if the inputted app exists within the hash table.
                if(s1 == "find app ")
                {
                    for(int k = 0; k < m; k++)
                    {
                        searchHashName(hashT[k], s2, found);

                        // Since it has been found already, there is no need to keep going through the hash table.
                        if(found == 1)
                        {
                            break;
                        }
                    }
                }
                // If the program goes here, that means that the find category command was chosen.
                else
                {
                    // The variable foundIt will be used to diplay 3 different message depending on whether or not a category exists, or if it has any apps.
                    int foundIt = 1;
                    for(int k = 0; k < n; k++)
                    {
                        string category2 = "";
                        for(int q = 0; q < strlen(appCategories[k].category); q++)
                        {
                            category2 += appCategories[k].category[q];
                        }

                        // If the category exists and there are nodes in the BST, then all of the apps in that category are printed.
                        if(category2 == s2 && bst[k] != NULL)
                        {
                            cout << "Category: " << appCategories[k].category << endl;
                            inorder(bst[k]);
                            cout << endl;
                            break;
                        }
                        else if(category2 == s2 && bst[k] == NULL)
                        {
                            // By setting the value to 2, we know that the category exists, but does not contain any nodes.
                            foundIt = 2;
                            break;
                        }
                        else if(category2 != s2)
                        {
                            // By setting the value to 0, we know that not only does the category not have nodes, but it also isn't a valid category.
                            foundIt = 0;
                        }
                    }

                    // Depending on what the value for foundIt was, a different message is printed.
                    if(foundIt == 0)
                    {
                        cout << "Category " << s2 << " not found." << endl;
                        cout << endl;
                    }
                    if(foundIt == 2)
                    {
                        cout << "Category " << s2 << " no apps found." << endl;
                        cout << endl;
                    }

                }
            }

            // If the program goes here, that means that the alphabetical range query was chosen.
            if(spaces == 4 && quotes == 6)
            {
                // Strings are captured which will contain the command, category, and letters we are checking range from.
                int place;

                // The command is captured here.
                for(int j = 0; j < holder.length(); j++)
                {
                    if(holder[j] == '"')
                    {
                        place = j;
                        break;
                    }
                    s1 += holder[j];
                }

                // The category name is captured here.
                for(int j = place + 1; j < holder.length(); j++)
                {
                    if(holder[j] == '"')
                    {
                        place = j;
                        break;
                    }
                    s2 += holder[j];
                }

                for(int j = place + 2; j < place + 5; j++)
                {
                    s3 += holder[j];
                }

                // Since we know we are checking for letter ranges, we can simply calculate the letters right here.
                s4 += holder[place + 7];
                s5 += holder[place + 11];

                int ran = 0;

                // If we find an existing category, we will attempt to find apps that are within that alphabetical range.
                for(int q = 0; q < n; q++)
                {
                    string select = "";
                    for(int y = 0; y < strlen(appCategories[q].category); y++)
                    {
                        select += appCategories[q].category[y];
                    }

                    // We print any existing apps within the range by using the inorderLetters function.
                    if(select == s2)
                    {
                        cout << "Applications in Range (" << s4 << "," << s5 << ") in Category: " << appCategories[q].category << endl;
                        inorderLetters(bst[q], s4, s5, ran);
                        cout << endl;
                        break;
                    }
                }

                // If we found no apps that were within the range, then we will print the result.
                if(ran == 0)
                {
                    cout << "No applications found between " << s4 << " and " << s5 << endl;
                    cout << endl;
                }
            }
            // If the program goes here, then the range of prices query is called.
            if(spaces == 4 && quotes == 2)
            {
                // Much of this code acts very similar to the range between letters query.
                int place;
                for(int j = 0; j < holder.length(); j++)
                {
                    if(holder[j] == '"')
                    {
                        place = j;
                        break;
                    }
                    s1 += holder[j];
                }

                for(int j = place + 1; j < holder.length(); j++)
                {
                    if(holder[j] == '"')
                    {
                        place = j;
                        break;
                    }
                    s2 += holder[j];
                }

                for(int j = place + 2; j < place + 7; j++)
                {
                    s3 += holder[j];
                }

                for(int j = place + 8; j < place + 12; j++)
                {
                    s4 += holder[j];
                }

                for(int j = place + 13; j < place + 18; j++)
                {
                    s5 += holder[j];
                }

                // Instead of using a letter range, we are using a price range given by these floats we convert.
                float n1 = stof(s4);
                float n2 = stof(s5);
                int ran = 0;

                // We go through to find if we have been given an appropriate category.
                for(int q = 0; q < n; q++)
                {
                    string select = "";
                    for(int y = 0; y < strlen(appCategories[q].category); y++)
                    {
                        select += appCategories[q].category[y];
                    }

                    // If there exits apps within the price range, then they will be printed using the inorderRange function.
                    if(select == s2)
                    {
                        cout << "Applications in Price Range ($";
                        cout << fixed;
                        cout << setprecision(2);
                        cout << n1;
                        cout << ",$";
                        cout << fixed;
                        cout << setprecision(2);
                        cout << n2;
                        cout << ") in Category: " << appCategories[q].category << endl;
                        inorderRange(bst[q], n1, n2, ran);
                        cout << endl;
                        break;
                    }
                }

                // If none of the apps were within the range, then the result is printed.
                if(ran == 0)
                {
                    cout << "No free applications found." << endl;
                    cout << endl;
                }

            }
            // If the program goes here, then we are deleting an app from the store.s
            if(spaces == 2 && quotes == 4)
            {
                // We use a similar process to the other queries to find string for the command.
                int stop;
                for(int q = 0; q < holder.length(); q++)
                {
                    if(holder[q] == '"')
                    {
                        stop = q;
                        break;
                    }
                    s1 += holder[q];
                }

                for(int q = stop + 1; q < holder.length(); q++)
                {
                    if(holder[q] == '"')
                    {
                        stop = q;
                        break;
                    }
                    s2 += holder[q];
                }

                for(int q = stop + 3; q < holder.length(); q++)
                {
                    if(holder[q] == '"')
                    {
                        stop = q;
                        break;
                    }
                    s3 += holder[q];
                }

                // We iterate through the categories to find the approriate category.
                for(int q = 0; q < n; q++)
                {
                    string catNew = "";
                    for(int y = 0; y < strlen(appCategories[q].category); y++)
                    {
                        catNew += appCategories[q].category[y];
                    }

                    if(catNew == s2)
                    {
                        // We try to find the specified app.
                        int found = 0;
                        for(int k = 0; k < m; k++)
                        {
                            searchHashName(hashT[k], s3, found);
                        }

                        // If it is found, it will be deleted.
                        if(found == 1)
                        {
                            //deleteBST(bst[q], s3);
                            //inorder(bst[q]);
                            cout << "Application " << s3 << " from Category " << s2 <<" successfully deleted." << endl;
                            cout << endl;
                        }
                        // If it does not exit, then we will print a statement saying that it could not be found.
                        else
                        {
                            cout << "Application " << s3 << " not found in category " << s2 << "; unable to delete." << endl;
                            cout << endl;
                            break;
                        }
                    }
                }

            }
        }

        // Extra getlines to exit the program.
        string report;
        getline(cin, report);
        getline(cin, report);
    }

    return 0;
}