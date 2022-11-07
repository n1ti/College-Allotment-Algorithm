#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
using namespace std;

struct student_data {
  int roll_number;
  char name[20];
  // college preference data
  int *preference;
};
typedef struct student_data *studentptr;
// veb tree define
class vebtree {
public:
  int u;
  int min;
  studentptr min_student;
  int max;
  studentptr max_student;
  vebtree *summary;
  vector<vebtree *> cluster;
  vebtree(int size) {
    u = size;
    min = -1;
    max = -1;
    // base size 2 vebtree
    if (size <= 2) {
      summary = NULL;
      cluster = vector<vebtree *>(0, NULL);
    } else {
      int lower_root_u = pow(2, floor((log2(u)) / 2));
      int upper_root_u = pow(2, ceil((log2(u)) / 2));
      /* summary will point to one veb tree with universe size upper_root_u. */
      summary = new vebtree(upper_root_u);

      /* cluster will point to (upper_root_u) number of veb trees
with universe size lower_root_u. */
      cluster = vector<vebtree *>(upper_root_u, NULL);
      for (int i = 0; i < upper_root_u; i++) {
        cluster[i] = new vebtree(lower_root_u);
      }
    }
  }
};
// FUNCTIONS
// 1. Function to return cluster number in which k is present.
int high(int x, int big_u) {
    int div = ceil(sqrt(big_u));
    return x / div;
}
// 2. Function to return position of x in cluster
int low(int x, int big_u) {
    int mod = ceil(sqrt(big_u));
    return x % mod;
}
// 3. Function to return the index from cluster number & index.
int idx(int x, int y, int big_u) {
    int u = ceil(sqrt(big_u));
    return x * u + y;
}
// 4. VEB Minimum
int veb_minimum(vebtree *V) { return V->min; }
// 5. Function to insert an element into the veb tree.
void insert(vebtree *V, int k, studentptr person1) {
    if (V->min == -1) {
        V->min = k;
        V->min_student = person1;
        V->max = k;
        V->max_student = person1;
    }else{
        if (k < V->min) {
            int temp = k;
            k = V->min;
            V->min = temp;
            studentptr tempstudent = person1;
            person1 = V->min_student;
            V->min_student = tempstudent;
        }
        if(V->u >= 2) {
            if (veb_minimum(V->cluster[high(k, V->u)]) == -1) {
                insert(V->summary, high(k, V->u), person1);
                V->cluster[high(k, V->u)]->min = low(k, V->u);
                V->cluster[high(k, V->u)]->max = low(k, V->u);
                V->cluster[high(k, V->u)]->min_student = person1;
                V->cluster[high(k, V->u)]->max_student = person1;
            }else{
                insert(V->cluster[high(k, V->u)], low(k, V->u), person1);
            }
        }
        if (k > V->max){
            V->max = k;
            V->max_student = person1;
        }
    }
}
// 6. Is element 'x' present in veb tree?
int veb_members_check(vebtree *A, int x) {
    if (x == A->min || x == A->max) {
      return 1;
    } else if (A->u == 2) {
      return 0;
    } else {
      return veb_members_check(A->cluster[high(x, A->u)], low(x, A->u));
    }
}
// 7. Reading until comma from the file
void reader(FILE *input, char *a)
{
    char c;
    c=fgetc(input);
    int i=0;
    while (c!=',' || c!='\n')
    {
        a[i]=c;
        i++;
    }
    a[i]='\n';
    return;
}
// End of Functions
int main() 
{
    FILE *inputfile;
    FILE *outputfile;
    inputfile=fopen("smallsample-cs201-student-data.csv", "r");
    outputfile=fopen("output.txt", "a");
    if (inputfile==NULL)
    {
        printf("File containing input cannot be opened.\n");
        exit(0);
    }
    int mytree_universe_size = 4; //max marks
    // student input
    //make marks array
    //take student data
    //append student to respective veb tree
    //use successor logic to find out next rank and allot college based on preference.
    //skipping the column names
    char buffer[255];
    vebtree* marks[2];
    int tempmarks=0;
    marks[0]=new vebtree(mytree_universe_size);
    printf("Empty vEB Tree of universe size %d has been generated.\n", mytree_universe_size);
    struct student_data person[4];
    /*
    fscanf(inputfile, "%s", buffer);
    for (int i=0; i<4; i++)
    {   
        printf("ok0 ");
        //reader(inputfile, buffer);
        fscanf(inputfile, "%s", buffer);
        printf("ok1 ");
        tempmarks=atoi(buffer);
        printf("ok2 ");
        //reader(inputfile, buffer);
        fscanf(inputfile, "%s", buffer);
        strcpy(person[i].name,buffer);
        //reader(inputfile, buffer);
        fscanf(inputfile, "%s", buffer);
        person[i].roll_number=atoi(buffer);
        //fscanf(inputfile, "%s", buffer);
        insert(marks[tempmarks], person[i].roll_number, &person[i]);
    }
    */
    // college key input
    return 0;
}
  

