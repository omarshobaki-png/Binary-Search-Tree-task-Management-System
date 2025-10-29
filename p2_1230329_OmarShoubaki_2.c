//Omar Shoubaki 1230329 section 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define name_Len 50
#define date_Len 20


typedef struct Task {
    int id;
    char name[name_Len];
    char date[date_Len];
    double duration;
    int performed;
    struct Task* left;
    struct Task* right;
} Task;
Task* root = NULL;
int sortedById=1;
void loadTasks();
void addTask();
Task* deleteTask(int, Task*);
void searchForaTask();
void performTask();
void viewUnperformedTasks();
void viewPerformedTasks();
void restructure();
void viewTasksBSTInfo();
void insertTask(Task* newTask);
int isDuplicateName(Task*, char*);
Task* findMin(Task*);
void toLowerCase(char* input);
void searchForaTaskHelper(Task*, char[], int*);
void viewPerformedTasksHelper(Task*, int*);
Task* restructureHelper(Task*, Task*, int);
int getTreeHeight(Task*);
int getTreeSize(Task*);
int getLeafCount(Task*);
int getInternalNodeCount(Task*);
Task* insertByName(Task*, Task*);
Task* getUnperformedTasks(Task*, Task*);
Task* insertByDate(Task*, Task*);
Task* insertByDuration(Task*, Task*);
Task* rebuildById(Task*, Task*);
Task* insertTaskWithId(Task*, Task*);
void nameBSTprinting(Task*);


int main(){
    printf("Welcome to your task management system! \n");
    int x=0;
    while(x!=10){
        printf("\nSelect an operation 1-10\n");
        printf("1- Load tasks from file \n");
        printf("2- Add a new task \n");
        printf("3- Delete a task \n");
        printf("4- Search for a task \n");
        printf("5- Perform a task \n");
        printf("6- View unperformed tasks \n");
        printf("7- View performed tasks \n");
        printf("8- Restructure the Tasks BST \n");
        printf("9- View the tasks BST info \n");
        printf("10- Exit program \n");
        printf("Enter your choice: ");
        scanf("%d",&x);
        switch(x){
            case 1: loadTasks();
            break;
            case 2: addTask();
            break;
            case 3:{
            int id;
            printf("\nEnter the id of the task you wish to delete: ");
            scanf("%d",&id);
            root= deleteTask(id, root);
            break;}
            case 4: searchForaTask();
            break;
            case 5: performTask();
            break;
            case 6: viewUnperformedTasks();
            break;
            case 7: viewPerformedTasks();
            break;
            case 8: restructure();
            break;
            case 9: viewTasksBSTInfo();
            break;
            case 10: printf("\nThanks for using my task management system ");
            break;
            default: printf("\nPlease enter a number 1-10\n");
        }

    }


}
void loadTasks(){
    FILE* file = fopen("tasks.txt", "r");
    if(!file){
        printf("\nCould not open tasks.txt \n");
        return;
    }
    char line[200];
    while(fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        Task* newTask = malloc(sizeof(Task));
        char *idToken = strtok(line, "#");
        char *nameToken = strtok(NULL, "#");
        char *dateToken = strtok(NULL, "#");
        char *durationToken = strtok(NULL, "#");
        newTask->id = atoi(idToken);
        strcpy(newTask->name, nameToken);
        strcpy(newTask->date, dateToken);
        newTask->duration = atof(durationToken);
        newTask->performed = 0;
        newTask->left = newTask->right = NULL;
        insertTask(newTask);

}
     fclose(file);
     printf("\nTasks loaded successfully\n");
}

void addTask(){
    if (!sortedById) {
    Task* temp = root;
    root = NULL;
    root = rebuildById(temp, root);
    sortedById = 1;
}
    Task* newTask= malloc(sizeof(Task));
    printf("\nEnter task ID: ");
    scanf("%d", &newTask->id);
    Task* temp = root;
    while(temp!=NULL){
            if(newTask->id==temp->id){
                printf("\nAnother task with the same id already exists\n");
                free(newTask);
                return;
            }
            else if(newTask->id<temp->id){
                temp =temp->left;
            }
            else{
                temp= temp->right;
            }
    }
    printf("\nEnter task name: ");
    scanf(" %[^\n]", newTask->name);
    if (isDuplicateName(root, newTask->name)) {
    printf("\nA task with the same name already exists\n");
    free(newTask);
    return;
}
    printf("\nEnter task due date: ");
    scanf(" %[^\n]", newTask->date);
    printf("\nEnter the duration of the task: ");
    scanf("%lf", &newTask->duration);
    newTask->performed=0;
    newTask->left= NULL;
    newTask->right= NULL;
    insertTask(newTask);
    printf("\nTask added successfully\n");


}
Task* deleteTask(int id, Task* t){
    if (!sortedById) {
    Task* temp = root;
    root = NULL;
    root = rebuildById(temp, root);
    sortedById = 1;
}
    Task* temp;
    if(t==NULL){
        printf("\nTask not found\n");
        return NULL;
        }
    else if(id<t->id){
        t->left= deleteTask(id,t->left);
    }
    else if(id>t->id){
        t->right= deleteTask(id,t->right);
    }
    else{
        if(t->left&&t->right){
            temp= findMin(t->right);
            t->id= temp->id;
            strcpy(t->name,temp->name);
            strcpy(t->date,temp->date);
            t->duration= temp->duration;
            t->performed= temp->performed;
            t->right = deleteTask(temp->id, t->right);

        }
        else{
            temp= t;
            if(t->left==NULL){
                t= t->right;
            }
            else if(t->right==NULL){
                t= t->left;
            }
            printf("\nTask with ID %d has been deleted\n", temp->id);
            free(temp);
        }



    }
    return t;



}
void searchForaTask(){
    if(root==NULL){
        printf("\nNo tasks found\n");
        return;
    }
    char ogname[name_Len];//just to protect capitalization while printing
    char name[name_Len];
    getchar();
    printf("\nEnter the name of the task ur searching for: ");
    scanf("%[^\n]", ogname);
    strcpy(name,ogname);
    toLowerCase(name);
    int found=0;
    searchForaTaskHelper(root,name,&found);// found is a pointer because we are acting on its value and sending it back
    if(!found){
        printf("\nTask with name %s was not found\n", ogname);
    }

}
void performTask(){
    if (!sortedById) {
    Task* temp = root;
    root = NULL;
    root = rebuildById(temp, root);
    sortedById = 1;
}
    if(root==NULL){
        printf("\nNo tasks to perform\n");
        return;
    }
    int id;
    printf("\nEnter the id of the task you wish to perform: ");
    scanf("%d", &id);
    Task* temp = root;
    while(temp!=NULL){
        if(id== temp->id){
            if(temp->performed==1){
                printf("\nThe task was already performed\n");
                }
                else{
                    temp->performed=1;
                    printf("\nTask with ID %d has been marked as performed\n", temp->id);
                }
                return;

        }
        else if(id<temp->id){
            temp= temp->left;

        }
        else{
            temp= temp->right;
        }
    }
        printf("\nTask not found\n");





}
void viewUnperformedTasks(){
    if(root==NULL){
        printf("\nNo tasks\n");
        return;
    }
    Task* nameBST= NULL;
    nameBST=getUnperformedTasks(root,nameBST);
    if(nameBST==NULL){
        printf("\nAll tasks were performed");
        return;
    }
    printf("\nList of unperformed tasks listed by their name alphabetically: \n");
    nameBSTprinting(nameBST);



}


void viewPerformedTasks() {
    if (root == NULL) {
        printf("\nNo tasks in the system\n");
        return;
    }

    int counter = 0;
     printf("\nList of performed tasks:\n");
    viewPerformedTasksHelper(root, &counter);

    if (counter == 0) {
        printf("\nNo tasks were performed\n");
    }
}
void restructure(){
    if(root==NULL){
        printf("\nOriginal BST is empty\n");
        return;
    }
    int choice;
    printf("\nHow do you want to restructure the tree: \n");
    printf("1) using task name\n");
    printf("2) using tasks due dates\n");
    printf("3) using task duration\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > 3) {
        printf("\nPlease enter a number 1-3\n");
        return;
    }
    Task* newRoot= NULL;
    newRoot = restructureHelper(root, newRoot, choice);
    root= newRoot;
    sortedById = 0;
    if (choice == 1) {
        printf("\nRestructuring complete based on task name\n");
    }
    else if (choice == 2) {
        printf("\nRestructuring complete based on task date\n");
    }
    else if (choice == 3) {
        printf("\nRestructuring complete based on task Duration\n");
    }

}


void viewTasksBSTInfo() {
    if (root == NULL) {
        printf("\nThe task tree is empty.\n");
        return;
    }

    int height = getTreeHeight(root);
    int size = getTreeSize(root);
    int leaves = getLeafCount(root);
    int internal = getInternalNodeCount(root);
    printf("\nStats for the BST: \n");
    printf("Tree height: %d", height);
    printf("\nTree size: %d", size);
    printf("\nTree leaves: %d", leaves);
    printf("\nTree internal nodes : %d\n", internal);
    }

//helper functions
void insertTask(Task * newTask){
    if(root==NULL){
        root = newTask;
        return;
    }
    Task* temp =root;
    while(1){
        if(newTask->id<temp->id){
            if(temp->left==NULL){
                temp->left= newTask;
                return;
            }
            temp= temp->left;
        }
        else{
            if(temp->right==NULL){
                temp->right= newTask;
                return;
            }
            temp= temp->right;
        }



    }}
int isDuplicateName(Task* root, char* newName) {
    if (root == NULL){
        return 0;
    }

    char lowerRootName[name_Len], lowerNewName[name_Len];
    strcpy(lowerRootName, root->name);
    strcpy(lowerNewName, newName);
    toLowerCase(lowerRootName);
    toLowerCase(lowerNewName);

    if (strcmp(lowerRootName, lowerNewName) == 0){
        return 1;
    }

    return isDuplicateName(root->left, newName) || isDuplicateName(root->right, newName);
}



Task* findMin(Task* node){//could be done recursively but doing it like this requires less memory

   if (node == NULL) return NULL;
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}
void toLowerCase(char* input) {
    for (int i = 0; input[i]; i++) {
        input[i] = tolower(input[i]);
    }
}
void searchForaTaskHelper(Task* temp, char searchName[], int* found) {
    if (temp == NULL || *found) {
            return;
    }
    if(!*found){
    searchForaTaskHelper(temp->left, searchName, found);
    }
    if(!*found){
    char tempName[name_Len];
    strcpy(tempName, temp->name);
    toLowerCase(tempName);

    if (strcmp(searchName, tempName) == 0) {
        printf("\nTask found:\n");
        printf("\n%d %s %s %.1lf hours\n", temp->id, temp->name, temp->date, temp->duration);
        *found = 1;
        return;
    }
    }

    if(!*found){
        searchForaTaskHelper(temp->right, searchName, found);
}
}
void viewPerformedTasksHelper(Task* root, int* counter) {
    if (root == NULL) return;

    viewPerformedTasksHelper(root->left, counter);

    if (root->performed == 1) {
        printf("\n%d %s %s %.1lf hours\n", root->id, root->name, root->date, root->duration);
        *counter = 1;
    }

    viewPerformedTasksHelper(root->right, counter);
}
int getTreeHeight(Task* Node) {
    if (Node == NULL) return 0;

    int leftHeight = getTreeHeight(Node->left);
    int rightHeight = getTreeHeight(Node->right);
    int max;

    if (leftHeight > rightHeight){
        max = leftHeight;}
    else{
        max = rightHeight;
    }
    return 1 + max;
}
int getTreeSize(Task* Node) {
    if (Node == NULL) {
            return 0;
    }
    return 1 + getTreeSize(Node->left) + getTreeSize(Node->right);
}
int getLeafCount(Task* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return getLeafCount(root->left) + getLeafCount(root->right);
}
int getInternalNodeCount(Task* root) {
    if (root == NULL || (root->left == NULL && root->right == NULL)){
        return 0;}
    return 1 + getInternalNodeCount(root->left) + getInternalNodeCount(root->right);
}
Task* insertByName(Task* nameRoot, Task* newTask) {
    if (nameRoot == NULL){
     return newTask;
    }
    int cmp = strcmp(newTask->name,nameRoot->name);
    if (cmp<0){
            nameRoot->left= insertByName(nameRoot->left,newTask);

    }
    else{
        nameRoot->right= insertByName(nameRoot->right,newTask);
    }
    return nameRoot;
    }

Task* getUnperformedTasks(Task* og, Task* nameBST){
    if(og==NULL){
        return nameBST;
    }
    nameBST= getUnperformedTasks(og->left,nameBST);
    if(og->performed==0){
        Task* copy = malloc(sizeof(Task));
        *copy= *og;
        copy->left= NULL;
        copy->right=NULL;
        nameBST=insertByName(nameBST,copy);

    }
    nameBST= getUnperformedTasks(og->right,nameBST);
    return nameBST;



}
Task* restructureHelper( Task* current, Task* newRoot, int sel){
    if(current==NULL){
        return newRoot;
    }
    newRoot= restructureHelper(current->left,newRoot, sel);
    Task* copy= malloc(sizeof(Task));
    *copy= * current;
    copy->left= NULL;
    copy->right=NULL;
    if (sel == 1) {
        newRoot = insertByName(newRoot, copy);
    }
    else if (sel == 2) {
        newRoot = insertByDate(newRoot, copy);
    }
    else if (sel == 3) {
        newRoot = insertByDuration(newRoot, copy);
    }

    newRoot = restructureHelper(current->right, newRoot, sel);
    return newRoot;
}


Task* insertByDate(Task* dateRoot, Task* newTask) {
    if (dateRoot == NULL){
        return newTask;
    }
    int cmp = strcmp(newTask->date, dateRoot->date);
    if (cmp < 0) {
        dateRoot->left = insertByDate(dateRoot->left, newTask);
    } else {
        dateRoot->right = insertByDate(dateRoot->right, newTask);
    }
    return dateRoot;
}
Task* insertByDuration(Task* durationRoot, Task* newTask){
    if(durationRoot==NULL){
        return newTask;
    }
    if(newTask->duration<durationRoot->duration){
        durationRoot->left= insertByDuration(durationRoot->left,newTask);
    }
    else{
        durationRoot->right= insertByDuration(durationRoot->right,newTask);
    }
    return durationRoot;

}
Task* rebuildById(Task* current, Task* newRoot) {
    if (current == NULL) return newRoot;

    newRoot = rebuildById(current->left, newRoot);

    Task* copy = malloc(sizeof(Task));
    *copy = *current;
    copy->left = copy->right = NULL;

    newRoot = insertTaskWithId(newRoot, copy);

    newRoot = rebuildById(current->right, newRoot);
    return newRoot;
}
Task* insertTaskWithId(Task* root, Task* newTask) {
    if (root == NULL) {
            return newTask;
    }

    if (newTask->id < root->id) {
        root->left = insertTaskWithId(root->left, newTask);
    }
    else {
        root->right = insertTaskWithId(root->right, newTask);
    }

    return root;
}
void nameBSTprinting(Task* nameRoot){// this follows the inorder implementation as the name most on the left is the first alphabatically and has the least ascii code value
    if (nameRoot==NULL){
        return;
    }
    nameBSTprinting(nameRoot->left);
    printf("%d %s %s %.1lf hours\n", nameRoot->id, nameRoot->name, nameRoot->date, nameRoot->duration);
    nameBSTprinting(nameRoot->right);
}






