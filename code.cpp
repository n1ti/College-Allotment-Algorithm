// Niti Shyamsukha 2021csb118
// Rhitvik Anand 2021csb1127
// Ihita Sinha 2021csb1095
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;
int mytree_universe_size; //setting size of vEB tree.
string blank="\n";
struct student_data {
  int roll_number;
  char name[20];
  // college preference data
  vector<int> preference;
  int college_allotted;
};
typedef struct student_data *studentptr;
struct college_data
{
  int seats;
  char name[20];
};
typedef struct college_data *collegeptr;
// veb tree define
class vebtree 
{
  public:
    int u;
    int min;
    studentptr min_student;
    int max;
    studentptr max_student;
    vebtree *summary;
    vector<vebtree *> cluster;
    vebtree(int size) 
    {
      u = size;
      min = -1;
      max = -1;
      // base size 2 vebtree
      if (size <= 2) 
      {
        summary = NULL;
        cluster = vector<vebtree *>(0, NULL);
      } 
      else 
      {
        int lower_root_u = pow(2, floor((log2(u)) / 2));
        int upper_root_u = pow(2, ceil((log2(u)) / 2));
        /* summary will point to one veb tree with universe size upper_root_u. */
        summary = new vebtree(upper_root_u);

        /* cluster will point to (upper_root_u) number of veb trees
  with universe size lower_root_u. */
        cluster = vector<vebtree *>(upper_root_u, NULL);
        for (int i = 0; i < upper_root_u; i++) 
        {
          cluster[i] = new vebtree(lower_root_u);
        }
      }
    }
};
// FUNCTIONS
// 1. Function to return cluster number in which k is present.
int high(int x, int big_u) 
{
    int lower_root_u = pow(2, floor((log2(big_u)) / 2));
    return floor((x/lower_root_u));
}
// 2. Function to return position of x in cluster
int low(int x, int big_u) 
{
    int lower_root_u = pow(2, floor((log2(big_u)) / 2));
    return (x%lower_root_u);
}
// 3. Function to return the index from cluster number & index.
int idx(int x, int y, int big_u) 
{
    int lower_root_u = pow(2, floor((log2(big_u)) / 2));
    return (x*lower_root_u + y);
}
// 4. VEB Minimum
int veb_minimum(vebtree *V) 
{ 
  return V->min; 
}
// 5. VEB Maximum
int veb_maximum(vebtree *V)
{
  return V->max;
}
// 6. Function to insert an element into the veb tree.
void insert(vebtree *V, int k, studentptr person1) 
{
    if (V->min == -1) 
    {
        V->min = k;
        V->min_student = person1;
        V->max = k;
        V->max_student = person1;
    }
    else
    {
        if (k < V->min) 
        {
            int temp = k;
            k = V->min;
            V->min = temp;
            studentptr tempstudent = person1;
            person1 = V->min_student;
            V->min_student = tempstudent;
        }
        if(V->u > 2) 
        {
            if (veb_minimum(V->cluster[high(k, V->u)]) == -1) 
            {
                insert(V->summary, high(k, V->u), person1);
                V->cluster[high(k, V->u)]->min = low(k, V->u);
                V->cluster[high(k, V->u)]->max = low(k, V->u);
                V->cluster[high(k, V->u)]->min_student = person1;
                V->cluster[high(k, V->u)]->max_student = person1;
            }
            else
            {
                insert(V->cluster[high(k, V->u)], low(k, V->u), person1);
            }
        }
        if (k > V->max){
            V->max = k;
            V->max_student = person1;
        }
    }
}
// 7. Is element 'x' present in veb tree? If yes, what data does it have?
int veb_members_check(vebtree *A, int x) 
{
    if (x == A->min) 
    {
      cout<<"Student Name: "<<A->min_student->name;
      cout<<"Student Roll Number: "<<A->min_student->roll_number<<'\n';
      if ((A->min_student->college_allotted)==-1)
      {
        printf("No college allotted.\n");
      }
      else printf("Code of College and Course Allotted: %d.\n", A->min_student->college_allotted);
      return 1;
    } 
    else if (x == A->max)
    { 
      cout<<"Student Name: "<<A->max_student->name;
      cout<<"Student Roll Number: "<<A->max_student->roll_number<<'\n';
      if ((A->max_student->college_allotted)==-1)
      {
        printf("No college allotted.\n");
      }
      else printf("Code of College and Course Allotted: %d.\n", A->max_student->college_allotted);
      return 1;
    }
    else if (A->u == 2) 
    {
      return 0;
    }
    else 
    {
      return veb_members_check(A->cluster[high(x, A->u)], low(x, A->u));
    }
}
// 8. Successor of element 'x' in vEB tree.
int veb_tree_successor(vebtree *V, int x)
{
  if (V->u==2)
  {
    if (x==0 && V->max==1)
    {
      return 1;
    }
    else return -1;
  }
  else if ((V->min!=-1) && (x<V->min))
  {
    return V->min;
  }
  else
  {
    int max_in_cluster=veb_maximum(V->cluster[high(x,V->u)]);
    if (max_in_cluster!=-1 && low(x, V->u)<max_in_cluster)
    {
      int offset=veb_tree_successor(V->cluster[high(x,V->u)], low(x, V->u));
      return idx(high(x, V->u), offset, mytree_universe_size);
    }
    else
    {
      int successor_cluster=veb_tree_successor(V->summary, high(x, V->u));
      if (successor_cluster==-1)
      {
        return -1;
      }
      else
      {
        int offset=veb_minimum(V->cluster[successor_cluster]);
        return idx(successor_cluster, offset, mytree_universe_size);
      }
    }
  }
}
// 9. Reading until comma from the file
string reader(FILE *input)
{
    string answer;
    char c;
    c=fgetc(input);
    while ((c!=',') && (c!='\n'))
    {
      answer.push_back(c);
      c=fgetc(input);
    }
    answer.push_back('\n');
    return answer;
}
// 10. Read the whole remaining line from file
void readline(FILE *input)
{
  char c;
  c=fgetc(input);
  while (c!='\n')
  {
    c=fgetc(input);

  }
  return;
}
// 11. Convert string to an integer
int stringtoint(string s)
{
  int answer=0;
  int temp=0;
  for (int i=0; s[i]!='\n'; i++)
  {
    temp = s[i]-'0';
    answer=answer*10+temp;
  }
  return answer;
}
// 12. Print student data
void printer_student(studentptr person, struct college_data C[])
{
  cout<<"Student Name: "<<person->name;
  cout<<"Student Roll No.: "<<person->roll_number<<'\n';
  cout<<"College Allotted: ";
  if (person->college_allotted!=-1)
  {
    cout<<C[person->college_allotted].name;
  }
  else cout<<"None.\n";
  return;
}
// 13. Function that gives a student pointer of the index entered.
studentptr veb_tree_student_pointer(vebtree *A, int x)
{ 
    if (x == A->min) 
    {
      return A->min_student;
    } 
    else if (x == A->max)
    { 
      return A->max_student;
    }
    else if (A->u == 2) 
    {
      return NULL;
    }
    else 
    {
      return veb_tree_student_pointer(A->cluster[high(x, A->u)], low(x, A->u));
    }
}
// 14. Function that allots colleges to students.
void college_allotter(studentptr S, struct college_data C[])
{
  int number_of_preferences=(S->preference).size();
  for (int i=0; i<number_of_preferences; i++)
  { 
    int collegecode=(S->preference)[i];
    if ((C[collegecode].seats)!=0)
    {
      (C[collegecode].seats)--;
      S->college_allotted=collegecode;
      return;
    }
  }
  return;
}
// End of Functions
int main() 
{   
    FILE *inputfile;
    FILE *college_listfile;
    FILE *outputfile;
    char buffer[255];
    inputfile=fopen("sample-student-data.txt", "r");
    outputfile=fopen("output.txt", "a");
    if (inputfile==NULL)
    {
        printf("File containing input cannot be opened.\n");
        exit(0);
    }
    //max marks
    string read;
    read=reader(inputfile); //read "Maximum Marks"
    read=reader(inputfile); //read the integer value
    int max_marks=stringtoint(read);
    fscanf(inputfile, "%s", buffer); //read the commas
    fseek(inputfile, 2, SEEK_CUR); // seek to ignore \n
    //max students input
    read=reader(inputfile); //read "Total Students"
    read=reader(inputfile); //read the integer value
    mytree_universe_size=stringtoint(read);
    fscanf(inputfile, "%s", buffer); //read the commas
    fseek(inputfile, 2, SEEK_CUR); // seek to ignore \n
    //make marks array
    vebtree* Score[max_marks+1];
    for (int i=0; i<max_marks+1; i++)
    {
      Score[i]=new vebtree(mytree_universe_size);
    }
  
    //each student input
    for (int j=0; j<mytree_universe_size; j++)
    {
      readline(inputfile);
      studentptr temp_student=new struct student_data;
      // student marks
      read=reader(inputfile); //read the integer value
      int person_marks=stringtoint(read);
      // student name
      read=reader(inputfile);
      for (int i=0; i<20; i++)
      {
        temp_student->name[i]=read[i];
      }
      // student roll number
      read=reader(inputfile);
      temp_student->roll_number=stringtoint(read);
      // student college choice data
      while ((read=reader(inputfile))!=blank)
      {
        (temp_student->preference).push_back(stringtoint(read));
      }
      // student college allotted
      temp_student->college_allotted=-1;
      //append student to respective veb tree
      insert(Score[person_marks], temp_student->roll_number, temp_student);
    }
    printf("Insertion to vEB trees complete.\n");
    // COLLEGE LIST INPUT
    college_listfile=fopen("sample-college-data.txt", "r");
    if (college_listfile==NULL)
    {
        printf("File containing colleges cannot be opened.\n");
        exit(0);
    }
    read=reader(college_listfile); //read "Total Courses"
    read=reader(college_listfile); //read the integer value
    int number_of_courses=stringtoint(read);
    fscanf(college_listfile, "%s", buffer); //read the commas
    fseek(college_listfile, 2, SEEK_CUR); // seek to ignore \n
    // initialize all colleges to a pointer.
    struct college_data colleges[number_of_courses+1];
    // store data of all colleges
    for (int i=1; i<number_of_courses+1; i++)
    { 
      readline(college_listfile);
      read=reader(college_listfile); //read the integer value
      int use_key=stringtoint(read);
      // college + course name
      read=reader(college_listfile);
        for (int i=0; i<20; i++)
        {
          colleges[use_key].name[i]=read[i];
        }
      // college seats
      read=reader(college_listfile);
      colleges[use_key].seats=stringtoint(read);
      //readline(college_listfile);
    }
    // use successor logic to find out next rank and allot college based on preference.
    int previous_roll=0;
    for (int i=max_marks; i>=0;)
    { 
      int next_roll=veb_tree_successor(Score[i], previous_roll);
      while (next_roll!=-1)
      {
        studentptr human=veb_tree_student_pointer(Score[i],next_roll);
        college_allotter(human, colleges);
        previous_roll=next_roll;
        next_roll=veb_tree_successor(Score[i], previous_roll);
        printer_student(human, colleges);
      }
      i--;
      previous_roll=0;
    }
    // output the allotted colleges.
    printf("Successful execution!\n");
    return 0;
}
  

