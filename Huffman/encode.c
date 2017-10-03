// Max Lord
// Period 7
// 9/28/17
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
// This constant can be avoided by explicitly calculating height of Huffman Tree
#define TREE_HT 100

// Node struct
struct TreeNode
{
    char data;  // symbol
    int freq;  // frequency
    struct TreeNode *left, *right; // left and right child
};

// Collection of TreeNodes
struct Tree
{
    int size;    // Nodes in tree
    int capacity;   // Capacity of tree
    struct TreeNode **array;  // Array of TreeNode pointers
};

// create new node
struct TreeNode* newNode(char data, int freq)
{
    struct TreeNode* temp = (struct TreeNode*) malloc(sizeof(struct TreeNode)); //set memory
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// create tree
struct Tree* createTree(int capacity)
{
    struct Tree* tree = (struct Tree*) malloc(sizeof(struct Tree));
    tree->size = 0;  // current size is 0
    tree->capacity = capacity;
    tree->array =
            (struct TreeNode**)malloc(tree->capacity * sizeof(struct TreeNode*));
    return tree;
}

// swap nodes
void swapTreeNode(struct TreeNode** a, struct TreeNode** b)
{
    struct TreeNode* t = *a;
    *a = *b;
    *b = t;
}
//convert char to binary- doesn't work
void tobin(int value, char* output)
{
    int i;
    output[5] = '\0';
    for (i = 4; i >= 0; --i, value >>= 1)
    {
        output[i] = (value & 1) + '0';
    }
}
// build tree
void Treeify(struct Tree* Tree, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < Tree->size && Tree->array[left]->freq < Tree->array[smallest]->freq) {
        smallest = left;
    }
    if (right < Tree->size && Tree->array[right]->freq < Tree->array[smallest]->freq) {
        smallest = right;
    }
    if (smallest != idx) {
        swapTreeNode(&Tree->array[smallest], &Tree->array[idx]);
        Treeify(Tree, smallest);
    }
}
struct TreeNode* extractMin(struct Tree* Tree)
{
    struct TreeNode* temp = Tree->array[0];
    Tree->array[0] = Tree->array[Tree->size - 1];
    --Tree->size;
    Treeify(Tree, 0);
    return temp;
}


// if tree size is one
int isSizeOne(struct Tree* Tree)
{
    return (Tree->size == 1);
}
// print array
void printArr(int arr[], int n, FILE* file)
{
    int i;
    for (i = 0; i < n; ++i) {
        fprintf(file, "%d", arr[i]);
        printf("%d", arr[i]);
    }
    fprintf(file,"%s","\n");
    printf("%s","\n");
}

// find min value in tree




// if node is leaf
int isLeaf(struct TreeNode* root)
{
    return !(root->left) && !(root->right) ;
}

// insert tree node
void insertTree(struct Tree* Tree, struct TreeNode* TreeNode)
{
    ++Tree->size;
    int i = Tree->size - 1;
    while (i && TreeNode->freq < Tree->array[(i - 1)/2]->freq)
    {
        Tree->array[i] = Tree->array[(i - 1)/2];
        i = (i - 1)/2;
    }
    Tree->array[i] = TreeNode;
}

// build tree
void buildTree(struct Tree* Tree)
{
    int n = Tree->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        Treeify(Tree, i);
}

struct Tree* createAndBuildTree(char data[], int freq[], int size)
{
    struct Tree* Tree = createTree(size);
    for (int i = 0; i < size; ++i)
        Tree->array[i] = newNode(data[i], freq[i]);
    Tree->size = size;
    buildTree(Tree);
    return Tree;
}

// The main function that builds Huffman tree
struct TreeNode* buildHuffmanTree(char data[], int freq[], int size)
{
    struct TreeNode *left, *right, *top;


    struct Tree* Tree = createAndBuildTree(data, freq, size);


    while (!isSizeOne(Tree))
    {

        left = extractMin(Tree);
        right = extractMin(Tree);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertTree(Tree, top);
    }

    return extractMin(Tree);
}

void printCodes(struct TreeNode* root, int arr[], int top, FILE* file)
{



    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1, file);
    }

    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1, file);
    }


    if (isLeaf(root))
    {
        fprintf(file, "%c", root->data);
        printf("%c", root->data);
        printArr(arr, top, file);

    }



}

// The main function that builds a Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size, FILE* f, char* message, int total)
{
    //  build tree
    struct TreeNode* root = buildHuffmanTree(data, freq, size);

    // print codes
    int arr[TREE_HT], top = 0;
    char ch, key;

    int size1 = 256;
    int size2 = 30;
    char code[size1];
    int n;
    char binval[size1][size2];

    printCodes(root, arr, top, f);

    fclose(f);

    FILE *fin = fopen("output.txt", "r");


    //read in # of lines value
    while(1) {
        fread(&ch, sizeof(char), 1, fin);
        //
        if (ch == '\n')
            break;
        n = (int)ch;
    }

    //create key

    for(int k = 0; k < n; k++) //for each line of key
    {
        char bin[size2];
        for(int i = 0; i < size2; i++) {
            bin[i] = '\0';
        }
        fread(&key, sizeof(char), 1, fin); //read in letter
        int index = 0;
        while(1)
        {
            fread(&ch, sizeof(char), 1, fin); //read in next binary
            if(ch == '\n') //if endline char
                break;
            bin[index] = ch;
            index++;



        }
        char *longbin = &bin[0];
        for(int x = 0; x < size2; x++) {
            binval[k][x] = longbin[x];
        }
        code[k] = key;

        //%d = int %c = interpret as char
        //printf("index=%d\t", index);
        //printf("key=%c\n", key);

    }

    /*for(int u = 0; u < 28; u++) {
        printf("%c",code[u]);
        for(int v = 0; v < 10; v++) {
            printf("%c", binval[u][v]);
        }
        printf("\n");

    }*/

    //printf("%c%s", code[0],"test");
    fclose(fin);

    FILE *outmessage = fopen("outmessage.txt", "w");
    for (int m = 0; m < total; m++) {
        for(int p = 0; p < n; p++) {
            if(message[m] == code[p]) {
                //printf("%c\n",message[m]);
                //char s[6];
                //tobin(n, s);
                for(int v = 0; v < size2; v++) {
                    if(binval[p][v] != '\0') {
                        fprintf(outmessage, "%c", binval[p][v]);
                    }
                    else {
                        break;
                    }

                }
                //fprintf(outmessage, "\n");

                //printf("%s", "found");
                break;
            }
        }
    }
    fclose(outmessage);

    FILE *fp1 = fopen("output.txt", "r");
    FILE *fp2 = fopen("outmessage.txt", "r");

    // Open file to store the result
    FILE *fp3 = fopen("decodeME.txt", "w");
    char c;

    if (fp1 == NULL || fp2 == NULL || fp3 == NULL)
    {
        puts("Could not open files");
        exit(0);
    }

    // Copy contents of first file to file3.txt
    while ((c = fgetc(fp1)) != EOF)
        fputc(c, fp3);

    // Copy contents of second file to file3.txt
    while ((c = fgetc(fp2)) != EOF)
        fputc(c, fp3);


    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}

// Driver program to test above functions
int main() {
    int i, total;
    FILE *filein = fopen("moby2.txt", "r");
    FILE *out; //output file
    out = fopen("output.txt", "w"); //open stream
    char ch;
    char array[80000];

    /*if(arr < 2)
    {
        printf("Enter message\n");
        return 0;
    }*/
    int arr_index = 0;
    while (!feof(filein)) {
        fread(&ch, sizeof(char), 1, filein); //read in next binary
        array[arr_index] = ch;
        arr_index++;
    }
    array[arr_index - 1] = '\0'; //undoes double

    char *message = &array[0];
    total = (int) strlen(message); //length of message
    struct TreeNode *tree[total]; //create node tree for length of message
    for (i = 0; i < total; i++) {//for each index in tree array
        //printf("%c", message[i]);
        tree[i] = NULL; //set each index null
    }
    //printf("total=%i\n", total);  //print message length
    int count, count2; //both count number of nodes but count will be changed
    count = count2 = 0;
    //fill tree
    for(i = 0; i < total; i++) //for each index in message
    {
        if(message[i] != '\0') //if message char at index is not null
        {
            int z; //index of tree array
            int q; //whether or not message[i] has a node- q==0 means message[i] symbol has no node
            q = 0;
            //check if
            for(z = 0; z < total; z++) //for each index in tree array
            {
                if(tree[z] != NULL) //if tree index is not null- add to frequency
                {
                    if(tree[z] ->data == message[i]) //treenode symbol is current message index
                    {
                        //printf("%c", tree[z] -> data);
                        //printf("%d", tree[z] ->freq);
                        tree[z]->freq += 1; //add one to frequency
                        //printf("%d", tree[z] ->freq);
                        //printf("\n");
                        q = 1; //message[i] symbol has a node
                    }
                }
            }
            if(tree[i] == NULL && q == 0)  //if current treenode is empty and message[i] symbol has no node
            {
                struct TreeNode* temp; //temp node
                temp = (struct TreeNode*)malloc(sizeof(struct TreeNode*)); //create memory for node
                temp -> data = message[i]; //symbol = current message index
                //printf("%c", temp -> data);
                temp -> freq = 1; //instantiate frequency as 1
                //printf("%d\n", temp -> freq);
                temp -> left = NULL; //no left child
                temp -> right = NULL; //no right child
                tree[i] = temp; //add node to tree array
                count++; //new treenode created
                count2++;
            }
        }

    }
    //types
    int counter = 0;
    for(int i = 0; i < total; i++) {
        if(tree[i] != NULL) {
            counter++;
            //printf("%c", tree[i] -> data);
            //printf("%d", tree[i] -> freq);
            //printf("\n");
        }
    }

    char arr[counter];
    int freq[counter];

    int next_index = 0;
    for(int j = 0; j < total; j++) {
        if(tree[j] != NULL) {
            arr[next_index] = tree[j]->data;
            freq[next_index] = tree[j]->freq;
            next_index++;
        }
    }




    int size = sizeof(arr)/sizeof(arr[0]);
    fprintf(out, "%d\n", size);

    for(int z = 0; z < (sizeof(arr)/ sizeof(arr[0])); z++) {
        printf("%c\n", arr[z]);
    }
    HuffmanCodes(arr, freq, size, out, message, total);
    return 0;
}
/*
13
m0000
w0001
e0010
d0011
r010
M0110
f0111
a1000
H10010
x10011
 101
o110
l111
10010001011111111010100011100101110011101011101011000001010110100010011
 */