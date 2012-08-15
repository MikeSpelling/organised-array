// Source: "Software Design ...", John A Robinson, Newnes, 2004, page 217.
// Updated by Michael R Spelling, 2008.
//
// C++ Program to implement ADT table of pairs
// Using ordered array
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
struct ipair{
int key;
int other_stuff;};
class table_of_pairs
{
int table_size;
ipair *ptable;
int num_in_table;
public:
table_of_pairs(const int size){
num_in_table = 0;
ptable = new ipair[(table_size = size)+1];};
// Set up an array of the requested size
~table_of_pairs(){
delete [] ptable;};
// ****** NEW CODE ****** //
int search(const int key, const char control);
// ***** OLD CODE ***** //
int add_to_table(const int, const int);
int remove_from_table(const int);
int get_other_stuff(const int);
int number_in() const{
return(num_in_table);};
void print_table() const;
};
// Methods for the class table_of_pairs follow
int table_of_pairs::add_to_table(const int key, const int other)
{
// ***** NEW CODE ***** //
int end = num_in_table - 1;
int place = search(key, 'a'); // Search for the key or middle point where key needs to go
if(ptable[place].key == key) // If key is found overwrite existing entry
ptable[place].other_stuff = other;
else
{
// ***** OLD CODE ***** //
if(num_in_table == table_size)
return(-1); // table is full
// ***** NEW CODE ***** //
if(ptable[place].key < -800000000){ // If key is empty a large negative number is in the array
ptable[place].key = key; // In which case the place is free to enter the new details
ptable[place].other_stuff = other;
num_in_table++;}
else
{
if(ptable[place].key > key)
{
while(end >= place){ // If key to enter is smaller than existing key shift all keys
// above up by one
ptable[end + 1] = ptable[end];
end--;}
ptable[place].key = key;
ptable[place].other_stuff = other;
num_in_table++;
}
else
{
place++; // Key to enter is larger than current key so place it one higher in array
while(end >= place){
ptable[end + 1] = ptable[end]; // Shift all keys above up by one
end--;}
ptable[place].key = key;
ptable[place].other_stuff = other;
num_in_table++;
}
}
}
// ***** OLD CODE ***** //
return(0);
}
int table_of_pairs::remove_from_table(const int member)
{
// ***** NEW CODE ***** //
int place = search(member, 'r'); // Find key
if(place != -1)
{
while(place < (num_in_table - 1)){ // If not error shift all keys above the one to remove
// down by one
ptable[place] = ptable[place + 1];
place++;}
num_in_table--;
}
// ***** OLD CODE ***** //
return(0);
}
// ***** NEW CODE ***** //
int table_of_pairs::get_other_stuff(const int member)
{
int place = search(member, 'g'); // Find key
if(place != -1)
return(ptable[place].other_stuff); // If not error return other_stuff
return(-1);
// ***** OLD CODE ***** //
}
void table_of_pairs::print_table() const
{
int offset;
for(offset = 0; offset < num_in_table; offset++)
cout << ptable[offset].key << "," << ptable[offset].other_stuff << " ";
cout << "\n";
}
// ***** NEW CODE ***** //
// Binary search function to find key
int table_of_pairs::search(const int key, const char control) // Control checks where
{ // search called from: 'a' - add_to_table; 'r' - remove_from_table; 'g' - get_other_stuff
int middle; int start = 0; int end = num_in_table - 1;
while(start <= end)
{
middle = (start + end) / 2; // Find middle point
if(ptable[middle].key == key) // If key found return 'middle'
return(middle);
if(control == 'a' && ((ptable[middle + 1].key > key || (middle + 1) == num_in_table) &&
(ptable[middle - 1].key < key || (middle - 1) < 0)))
return(middle); // If called by add function return 'middle' if key is
// smaller than one above it and larger than one below it
if(ptable[middle].key < key)
start = middle + 1;
else
end = middle - 1;
}
if(control == 'r' || control == 'g') // If key not found return '-1' to remove and get functions
return(-1);
else // Otherwise if key not found return '0' to add function
return(0);
}
// ***** OLD CODE ***** //
// The main program here is just a simple test loop
// The commands q, a, r, c, p are available, to quit, add element,
// remove element, check for element, and print table repectively.
int main()
{
char c;
int key, other;
table_of_pairs mytable(8);
// Here saying that 8 is max num of elements I will use in
// any run of this test program (A bit restrictive).
while(1)
{
cout << ": "; // Prompt
cin >> c;
switch(c)
{
case 'q':
return 0;
case 'a':
cin >> key >> other;
mytable.add_to_table(key, other);
break;
case 'r':
cin >> key;
mytable.remove_from_table(key);
break;
case 'c':
cin >> key;
// ***** NEW CODE ***** //
other = mytable.get_other_stuff(key); // Find other and check for errors
if(other != -1)
// ***** OLD CODE ***** //
cout << "Item labelled " << key << " has value " << other << " in mytable\n";
else
cout << "There is no item labelled " << key << " in mytable\n";
break;
case 'p':
mytable.print_table();
break;
// ***** NEW CODE ***** //
case 't': // Test case
mytable.add_to_table(55, 66);
mytable.add_to_table(88, 99);
mytable.add_to_table(22, 33);
mytable.add_to_table(77, 88);
mytable.add_to_table(13, 14);
mytable.add_to_table(4, 4);
mytable.add_to_table(5, 6);
mytable.add_to_table(1, 2); // Add 8 random values
mytable.print_table();
mytable.remove_from_table(1);
mytable.remove_from_table(13); // Remove items with keys 1 and 13
mytable.print_table();
break;
// The program was run and 't' was entered to run the test
// The following was outputted:
//
// 1,2 4,4 5,6 13,14 22,33 55,66 77,88 88,99
// 4,4 5,6 22,33 55,66 77,88 88,99
// 6 items in table
//
// The first line shows the correct operation of add_to_table
// All keys are put in numeric order
// The second line shows the correct operation of remove_from_table
// 'c' was pressed followed by 77, the output was:
//
// Item labelled 77 has value 88 in mytable
// 6 items in table
//
// This confirms the correct operation of get_other_stuff
// The key was found and correct other_stuff outputted
// Various inputs were also tried and all confirmed correct operation
// ***** OLD CODE ***** //
default:
cout << "Use q, a, r, c or p only\n";
break;
}
cout << mytable.number_in() << " items in table\n";
}
}