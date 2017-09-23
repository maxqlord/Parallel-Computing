// C program for Huffman Coding
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
// This constant can be avoided by explicitly calculating height of Huffman Tree
#define MAX_TREE_HT 100

// A Huffman tree node
struct MinHeapNode
{
    char data;  // One of the input characters
    unsigned freq;  // Frequency of the character
    struct MinHeapNode *left, *right; // Left and right child of this node
};

// A Min Heap:  Collection of min heap (or Hufmman tree) nodes
struct MinHeap
{
    unsigned size;    // Current size of min heap
    unsigned capacity;   // capacity of min heap
    struct MinHeapNode **array;  // Attay of minheap node pointers
};

// A utility function allocate a new min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp =
            (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// A utility function to create a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap =
            (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;  // current size is 0
    minHeap->capacity = capacity;
    minHeap->array =
            (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// A utility function to swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void tobin(int value, char* output)
{
    int i;
    output[5] = '\0';
    for (i = 4; i >= 0; --i, value >>= 1)
    {
        output[i] = (value & 1) + '0';
    }
}
// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap)
{
    return (minHeap->size == 1);
}

// A standard function to extract minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// A utility function to insert a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1)/2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2;
    }
    minHeap->array[i] = minHeapNode;
}

// A standard funvtion to build min heap
void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// A utility function to print an array of size n
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

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)
{
    return !(root->left) && !(root->right) ;
}

// Creates a min heap of capacity equal to size and inserts all character of
// data[] in min heap. Initially size of min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity equal to size.  Initially, there are
    // modes equal to size.
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap))
    {
        // Step 2: Extract the two minimum freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3:  Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two extracted node as
        // left and right children of this new node. Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the root node and the tree is complete.
    return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.  It uses arr[] to
// store codes
void printCodes(struct MinHeapNode* root, int arr[], int top, FILE* file)
{
    // Assign 0 to left edge and recur


    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1, file);
    }

    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1, file);
    }

    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
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
    //  Construct Huffman Tree
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

    // Print Huffman codes using the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;
    char ch, key;
    char code[200];
    char binval[200][10];

    printCodes(root, arr, top, f);

    fclose(f);

    FILE *fin = fopen("output.txt", "r");
    int n = 28; //num of lines

    //read in # of lines value
    while(1) {
        fread(&ch, sizeof(char), 1, fin);
        //
        if (ch == '\n')
            break;
    }

    //create key

    for(int k = 0; k < n; k++) //for each line of key
    {
        char bin[10];
        for(int i = 0; i < 10; i++) {
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
        for(int x = 0; x < 10; x++) {
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
        for(int n = 0; n < 28; n++) {
            if(message[m] == code[n]) {
                //printf("%c\n",message[m]);
                //char s[6];
                //tobin(n, s);
                for(int v = 0; v < 10; v++) {
                    if(binval[n][v] != '\0') {
                        fprintf(outmessage, "%c", binval[n][v]);
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
    FILE *filein = fopen("message.txt", "r");
    FILE *out; //output file
    out = fopen("output.txt", "w"); //open stream
    char ch;
    char array[1000];

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
    struct MinHeapNode *tree[total]; //create node tree for length of message
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
                struct MinHeapNode* temp; //temp node
                temp = (struct MinHeapNode*)malloc(sizeof(struct minHeadNode*)); //create memory for node
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
    HuffmanCodes(arr, freq, size, out, message, total);
    return 0;
}