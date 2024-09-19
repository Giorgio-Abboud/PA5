#include "solver.h"
hashset set;
hashset found;
tnode* root = NULL;
int sorted;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* solve(void* arg){
	//your code here
	//fprintf(stderr, "solver thread: %s\n", (char*)arg);
	info* arguments = (info*)arg;

	char** subpuzzle = arguments->subpuzzle;
    int min_len = arguments->min_len;
    int max_len = arguments->max_len;
    int line = arguments->line;
    int col = arguments->col;
    int subpuzzle_lines = arguments->subpuzzle_lines;
    int subpuzzle_cols = arguments->subpuzzle_cols;
    int t_id = arguments->t_id;

	//char *temp = (char*)malloc((max_len + 1) * sizeof(char));
	char temp[max_len+1];
	for(int len = min_len; len <= max_len; len++){
		temp[len] = '\0';
		for(int line = 0; line < subpuzzle_lines; line++){
			for(int col = 0; col < subpuzzle_cols; col++){

				if(col + len <= subpuzzle_cols){ //East
					for(int i = 0; i < len; i++){
						temp[i] = subpuzzle[line][col+i];
					}
					if(search(set, temp)){
						if(sorted){
							pthread_mutex_lock(&lock); //Lock
							bst_insert(&root, temp); //BST
							pthread_mutex_unlock(&lock); //Unlock
						}else{
							if(!search(found, temp)){
								printf("%s\t%d\t%d:%d\t%d:%d\n", temp, t_id, line+1, line+1, col+1, col+len);
								insert(&found, temp);
							}
							//printf("EAST");
						}
					}
				}

				if(col - len >= 0){ //West
					for(int i = len - 1; i >= 0; i--){
						temp[i] = subpuzzle[line][col-i];
					}
					if(search(set, temp)){
						if(sorted){
							pthread_mutex_lock(&lock); //Lock
							bst_insert(&root, temp); //BST
							pthread_mutex_unlock(&lock); //Unlock
						}else{
							if(!search(found, temp)){
								printf("%s\t%d\t%d:%d\t%d:%d\n", temp, t_id, line+1, line+1, col+1, col-len);
								insert(&found, temp);
							}
							//printf("WEST");
						}
					}
				}

				if(line + len <= subpuzzle_lines){ //South
					for(int i = 0; i < len; i++){
						temp[i] = subpuzzle[line+i][col];
					}
					if(search(set, temp)){
						if(sorted){
							pthread_mutex_lock(&lock); //Lock
							bst_insert(&root, temp); //BST
							pthread_mutex_unlock(&lock); //Unlock
						}else{
							if(!search(found, temp)){
								printf("%s\t%d\t%d:%d\t%d:%d\n", temp, t_id, line+1, line+len, col+1, col+1);
								insert(&found, temp);
							}
							//printf("SOUTH");
						}
					}
				}

				if(line - len >= 0){ //North
					for(int i = len - 1; i >= 0; i--){
						temp[i] = subpuzzle[line-i][col];
					}
					if(search(set, temp)){
						if(sorted){
							pthread_mutex_lock(&lock); //Lock
							bst_insert(&root, temp); //BST
							pthread_mutex_unlock(&lock); //Unlock
						}else{
							if(!search(found, temp)){
								printf("%s\t%d\t%d:%d\t%d:%d\n", temp, t_id, line+1, line-len, col+1, col+1);
								insert(&found, temp);
							}
							//printf("NORTH");
						}
					}
				}

				if(line + len <= subpuzzle_lines && col + len <= subpuzzle_cols){ //South East
					for(int i = 0; i < len; i++){
						temp[i] = subpuzzle[line+i][col+i];
					}
					if(search(set, temp)){
						if(sorted){
							pthread_mutex_lock(&lock); //Lock
							bst_insert(&root, temp); //BST
							pthread_mutex_unlock(&lock); //Unlock
						}else{
							if(!search(found, temp)){
								printf("%s\t%d\t%d:%d\t%d:%d\n", temp, t_id, line+1, line+len, col+1, col+len);
								insert(&found, temp);
							}
							//printf("SOUTH EAST");
						}
					}
				}

				if(line + len <= subpuzzle_lines && col - len >= 0){ //South West
					for(int i = len - 1; i >= 0; i--){
						temp[i] = subpuzzle[line+i][col-i];
					}
					if(search(set, temp)){
						if(sorted){
							pthread_mutex_lock(&lock); //Lock
							bst_insert(&root, temp); //BST
							pthread_mutex_unlock(&lock); //Unlock
						}else{
							if(!search(found, temp)){
								printf("%s\t%d\t%d:%d\t%d:%d\n", temp, t_id, line+1, line+len, col+1, col-len);
								insert(&found, temp);
							}
							//printf("SOUTH WEST");
						}
					}
				}

				if(line - len >= 0 && col + len <= subpuzzle_cols){ //North East
					for(int i = 0; i < len; i++){
						temp[i] = subpuzzle[line-i][col+i];
					}
					if(search(set, temp)){
						if(sorted){
							pthread_mutex_lock(&lock); //Lock
							bst_insert(&root, temp); //BST
							pthread_mutex_unlock(&lock); //Unlock
						}else{
							if(!search(found, temp)){
								printf("%s\t%d\t%d:%d\t%d:%d\n", temp, t_id, line+1, line-len, col+1, col+len);
								insert(&found, temp);
							}
							//printf("NORTH EAST");
						}
					}
				}

				if(line - len >= 0 && col - len >= 0){ //North West
					for(int i = len - 1; i >= 0; i--){
						temp[i] = subpuzzle[line-i][col-i];
					}
					if(search(set, temp)){
						if(sorted){
							pthread_mutex_lock(&lock); //Lock
							bst_insert(&root, temp); //BST
							pthread_mutex_unlock(&lock); //Unlock
						}else{
							if(!search(found, temp)){
								printf("%s\t%d\t%d:%d\t%d:%d\n", temp, t_id, line+1, line-len, col+1, col-len);
								insert(&found, temp);
							}
							//printf("NORTH WEST");
						}
					}
				}

			}
		}
	}
	return 0;
}

void print_buffer(char** sub_puzzle, int subpuzzle_rows, int subpuzzle_cols){
	//this function is used for printing the content of each buffer cell.
	//do NOT call this function anywhere in your final submission.
	printf("%d by %d\n", subpuzzle_rows, subpuzzle_cols);
	for(int i = 0; i < subpuzzle_rows;i++)
		for(int j = 0; j < subpuzzle_cols;j++)
			printf("%c%s", sub_puzzle[i][j], j == subpuzzle_cols - 1?"\n":"");
}
int main(int argc, char** argv){
	if (argc < 11)
		error("Fatal Error. Usage: solve -dict dict.txt -input puzzle1mb.txt -size 1000 -nbuffer 64 -len 4:7 [-s]", 1);
	int puzzle_size = 0, buf_cells = 0, i = 0,j, fd, min_len = 0, max_len = 0, sorted = 0, buf_dimension;
	char* filename = NULL;
	FILE* dictionary_file;
	char*** buffer;
	while(++i < argc){
		if(argv[i][0] != '-')
			error("Fatal Error. Invalid CLA", 2);
		if(!strcmp(argv[i], "-size")){
			puzzle_size = atoi(argv[++i]);
			if(puzzle_size < 15 || puzzle_size > 46340)
				error("Fatal Error. Illegal value passed after -size",3);
		}
		else if(!strcmp(argv[i], "-nbuffer")){
			buf_cells = atoi(argv[++i]);
			if(buf_cells != 1 && buf_cells != 4 && buf_cells != 16
				&& buf_cells != 64)
				error("Fatal Error. Illegal value passed after -nbuffer",4);
			buf_dimension = (int)sqrt(MEM_LIMIT / buf_cells);
			//buf_cells = 1 -> buf_dimension = 8000
			//buf_cells = 4 -> buf_dimension = 4000
			//buf_cells = 16 -> buf_dimension = 2000
			//buf_cells = 64 -> buf_dimension = 1000
		}
		else if(!strcmp(argv[i], "-input")){
			filename = strdup(argv[++i]);
			fd = open(filename, O_RDONLY, 0);
			if(fd < 0)
				error("Fatal Error. Illegal value passed after -input",5);
		}else if(!strcmp(argv[i], "-dict")){
			dictionary_file = fopen(argv[++i], "r");
			if(!dictionary_file)
				error("Fatal Error. Illegal value passed after -dict",6);
		}else if(!strcmp(argv[i], "-len")){
			char* min_max = strdup(argv[++i]);
			char* max_str;
			if(strrchr(min_max, ':') != (max_str = strchr(min_max, ':'))
				|| !strchr(min_max, ':'))
				error("Fatal Error. Illegal value passed after -len",7);
			max_len = atoi(max_str+1);
			min_max[max_str - min_max] = '\0';
			min_len = atoi(min_max);
			if(min_len < 3 || max_len > 14 || min_len > max_len)
				error("Fatal Error. Illegal value passed after -len",7);
		}else if(!strcmp(argv[i], "-s"))
			sorted = 1;
		else{
			error("Fatal Error. Usage: solve -dict dict.txt -input puzzle1mb.txt -size 1000 -nbuffer 64 -len 4:7 [-s]", 1);
			break;
		}
	}
	//Read and move all words from dictionary_file to a new hash table (hashset)
	//Your code here...
	set = set_init();
	found = set_init();
	//FILE *words_file = fopen(dictionary_file, "r");
    char bufferWrd[100];
    while (fgets(bufferWrd, 100, dictionary_file))
    {
        int len = strlen(bufferWrd);
        if (bufferWrd[len - 1] == '\n')
            bufferWrd[len - 1] = '\0';
        insert(&set, bufferWrd);
		//printf("%s", bufferWrd);
    }
    fclose(dictionary_file);
	
	//allocate 64MB of buffer in the heap
	//buffer is a 3D array
	//on the outermost dimension, we have buf_cells elements
	//each element is given to one consumer thread
	//each element is going to store a (square-shape) sub-puzzle
	//each element is a square-shape 2D array of characters
	//dimension of this square-shape array is buf_dimension by buf_dimension
	buffer = (char***)malloc(buf_cells * sizeof(char**));
	for(i = 0;i < buf_cells;i++){
		buffer[i] = (char**)malloc(buf_dimension * sizeof(char*));
		for(j = 0; j < buf_dimension;j++)
			buffer[i][j] = (char*) malloc(buf_dimension);
	}

	printf("word\tTID\tLnSpan\tColSpan\n");

	int buf_index = 0;
	pthread_t t_id[buf_cells];
	for(i = 0; i < buf_cells;i++)
		t_id[i] = NULL;
	for(int row = 0; row + max_len - 1 < puzzle_size; row += (buf_dimension - max_len + 1)){
		int subpuzzle_rows = (row + buf_dimension <= puzzle_size)?
				 buf_dimension:	puzzle_size - row;
		for(int column = 0; column + max_len - 1 < puzzle_size;column += (buf_dimension - max_len + 1)){
			long start = (long)row * (puzzle_size+1) + column;
			lseek(fd,start,SEEK_SET);
			int subpuzzle_cols = (column + buf_dimension <= puzzle_size)?
				 buf_dimension:	puzzle_size - column;
			if(t_id[buf_index])//if there is a busy consumer/solver, 
				pthread_join(t_id[buf_index], NULL);//wait for it to finish the job before manipulating the buffer[buffer_index]
			for(i = 0; i < subpuzzle_rows;i++){
				int n_read = read(fd, buffer[buf_index][i], subpuzzle_cols);
				if(n_read < subpuzzle_cols)
					error("Fatal Error. Bad read from input file", 10);
				if(subpuzzle_cols < buf_dimension)
					buffer[buf_index][i][subpuzzle_cols] = '\0';
				lseek(fd, puzzle_size-subpuzzle_cols+1, SEEK_CUR);
			}
			if(subpuzzle_rows < buf_dimension)
				buffer[buf_index][subpuzzle_rows] = NULL;

			info thread_info;
			thread_info.min_len = min_len;
			thread_info.max_len = max_len;
			thread_info.subpuzzle = buffer[buf_index];
			thread_info.t_id = buf_index;
			thread_info.line = row;
			thread_info.col = column;
			thread_info.subpuzzle_lines = subpuzzle_rows;
			thread_info.subpuzzle_cols = subpuzzle_cols;
			
			//modify these lines so that you can create and start a solver thread
			while(pthread_create(t_id + buf_index, NULL, solve, &thread_info));
			//pthread_create(t_id + buf_index, NULL, solve, &thread_info);
			
			// //after passing the right information to it...
			// fprintf(stderr, "Consuming buffer #%d\n", buf_index);
			// char* message = (char*) malloc(1000);
			//sprintf(message, "solving sub-puzzle of dimensions %d by %d located at index (%d,%d).",
			// subpuzzle_rows, subpuzzle_cols, row, column);
			// pthread_create(t_id + buf_index, NULL, solve, message);
			// //print_buffer(buffer[buf_index], subpuzzle_rows, subpuzzle_cols);
			
			// //end of modification
			buf_index = (buf_index == buf_cells - 1)?0: buf_index + 1;
		}
	}
	for(i = 0; i < buf_cells;i++)
		if(t_id[i])
			pthread_join(t_id[i], NULL);
	
	if(sorted){
		//print the binary search tree using in-order traversal...
		//your code here...
		inorder_print(root);
	}

}