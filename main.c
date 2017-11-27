#define FUSE_USE_VERSION 26
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fuse.h>
#include <fcntl.h>

char csvdir[50]="";
typedef struct data data;
struct data{
    char *code;
    char *neighborhood;
    char *city;
    char *district;
    char *latitude;
    char *longitude;
    struct data *next;
};
struct List{
	struct data *head;
	struct data *tail;
};
struct Unique_val{
	char *veri;
	struct Unique_val *next;
};

struct data* readFile(){
	
	struct List temp;
    temp.head = NULL;
    temp.tail = NULL;
    FILE *file;
    file = fopen("/home/rumeysa/Documents/Project3/postal-codes.csv", "r");
    
    if(file != NULL){
        printf("File is opened\n");
        char *token;
        char *string = NULL;
        char *line = NULL;
        size_t size = 0;
        
        while (getline(&line, &size, file) != -1) {
			struct data *veri = malloc(sizeof(struct data));
			
			
            string = strdup(line);
            int count = 0;
            token = strsep(&string, "\t");
            veri->code = token;
            
            token = strsep(&string, "\t");
            veri->neighborhood = token;
            
            token = strsep(&string, "\t");
            veri->city = token;
            
            token = strsep(&string, "\t");
            veri->district = token;
            
            token = strsep(&string, "\t");
            veri->latitude = token;
            
            token = strsep(&string, "\t");
            veri->longitude = token;
            
            veri->next = NULL;
			
			if(temp.head == NULL){
				temp.head = veri;
			}
			else{
				temp.tail->next = veri;
			}
			
			temp.tail = veri;
        }
        
    }
    else{
        printf("File is not opened.\n");
    }
    
    fclose(file);
    return temp.head;
}

struct Unique_val* get_unique_city(){
	
	struct data* dHead = readFile();
	struct data* traverse = dHead;
	struct Unique_val *city = NULL, *city_trav;
	
	struct Unique_val *temp_city;

	while(dHead){

		if(city == NULL){
			city = malloc(sizeof(struct Unique_val));
		    city->veri = strdup(dHead->city);
		    city->next = NULL;
		    city_trav = city;
		}
		else {
			
			temp_city = city;
			int find = 0;
			
			while(temp_city){
				
				if(strcmp(temp_city->veri,dHead->city) == 0){
					find = 1;
					break;
				}
				
				temp_city = temp_city->next;
			}
			
			if(find == 0){
				struct Unique_val * t =  malloc(sizeof(struct Unique_val));
				t->veri = strdup(dHead->city);
				t->next = NULL;
				city_trav->next = t;
				city_trav = city_trav->next;
				
			}
		}
		
		dHead = dHead->next;
	}
	struct data* temp;
	while(traverse){
		free(traverse->code);
		temp = traverse;
		traverse = traverse->next;
		free(temp);
	}
	return city;
}


struct Unique_val* get_unique_district(char* city_param){
	
	struct data* dHead = readFile();
	struct data* traverse = dHead;
	struct Unique_val *city = NULL, *city_trav;
	
	struct Unique_val *temp_city;

	while(dHead){
		
		if(strcmp(dHead->city, city_param) == 0)
		{
			if(city == NULL){
				city = malloc(sizeof(struct Unique_val));
				city->veri = strdup(dHead->district);
				city->next = NULL;
				city_trav = city;
			}
			else {
				
				temp_city = city;
				int find = 0;
				while(temp_city){
					
					if(strcmp(temp_city->veri,dHead->district) == 0){
						
						find = 1;
						break;
					}
					
					temp_city = temp_city->next;
				}
				
				if(find == 0){
					struct Unique_val * t =  malloc(sizeof(struct Unique_val));
					t->veri = strdup(dHead->district);
					t->next = NULL;
					city_trav->next = t;
					city_trav = city_trav->next;
					
				}
			}	
		}
		
		
		dHead = dHead->next;
	}
	struct data* temp;
	while(traverse){
		free(traverse->code);
		temp = traverse;
		traverse = traverse->next;
		free(temp);
	}
	return city;
}

struct Unique_val* get_postal_code() {
	
	struct data* dHead = readFile();
	struct data* traverse = dHead;
	struct Unique_val *city = NULL, *city_trav;
	char *temp;
	struct Unique_val *temp_city;

	while(dHead){

		if(city == NULL){
			
			city = malloc(sizeof(struct Unique_val));
			city->veri = strndup(dHead->code, 2);  
		    city->next = NULL;
		    city_trav = city;
		}
		else {
			
			temp_city = city;
			int find = 0;
			
			while(temp_city){
				
				if(strncmp(temp_city->veri,dHead->code, 2) == 0){
					find = 1;
					break;
				}
				
				temp_city = temp_city->next;
			}
			
			if(find == 0){
				struct Unique_val * t =  malloc(sizeof(struct Unique_val));
				t->veri = strndup(dHead->code, 2);
				t->next = NULL;
				city_trav->next = t;
				city_trav = city_trav->next;
				
			}
		}
		
		dHead = dHead->next;
	}
	struct data* temp2;
	while(traverse){
		free(traverse->code);
		temp2 = traverse;
		traverse = traverse->next;
		free(temp2);
	}
	return city;

}

struct Unique_val* get_neighborhood(char* city_param, char* district_param){
	struct data* dHead = readFile();
	struct data* traverse = dHead;
	struct Unique_val *city = NULL, *city_trav;
	
	struct Unique_val *temp_city;

	while(dHead){
		if(strcmp(dHead->city, city_param) == 0 && strcmp(dHead->district, district_param) == 0)
		{
			if(city == NULL){
				city = malloc(sizeof(struct Unique_val));
				city->veri = strdup(dHead->neighborhood);
				city->next = NULL;
				city_trav = city;
			
			}
			else {
				struct Unique_val * t =  malloc(sizeof(struct Unique_val));
				t->veri = strdup(dHead->neighborhood);
				t->next = NULL;
				city_trav->next = t;
				city_trav = city_trav->next;
			}	
		}
		
		dHead = dHead->next;
	}
	struct data* temp;
	while(traverse){
		free(traverse->code);
		temp = traverse;
		traverse = traverse->next;
		free(temp);
	}
	return city;
}
struct Unique_val* get_postal_code_full(char *code){
	struct data* dHead = readFile();
	struct data* traverse = dHead;
	struct Unique_val *city = NULL, *city_trav;
	char *temp;
	struct Unique_val *temp_city;
	while(dHead){
		if(strncmp(dHead->code,code,2)==0){
	
		if(city == NULL){
			
			city = malloc(sizeof(struct Unique_val));
			city->veri = strdup(dHead->code);  
		    city->next = NULL;
		    city_trav = city;
		}
		else {
			
			temp_city = city;
			int find = 0;
			
			while(temp_city){
				
				if(strcmp(temp_city->veri,dHead->code) == 0){
					find = 1;
					break;
				}
				
				temp_city = temp_city->next;
			}
			
			if(find == 0){
				struct Unique_val * t =  malloc(sizeof(struct Unique_val));
				t->veri = strdup(dHead->code);
				t->next = NULL;
				city_trav->next = t;
				city_trav = city_trav->next;
				
			}
		}
	
	}
		
		dHead = dHead->next;
	}
	struct data* temp2;
	while(traverse){
		free(traverse->code);
		temp2 = traverse;
		traverse = traverse->next;
		free(temp2);
	}
	return city;
}
int occurence(char *ptr){
	int i = 0;
	int number = 0;
	for(i = 0; ptr[i] != '\0'; i++){
		if(ptr[i] == '/')
			number++;
	}
	return number;
}


static int sys_getattr(const char *path, struct stat *stbuf){
	int res = 0;

    memset(stbuf, 0, sizeof(struct stat));
    
    if(strstr(path, ".txt") != NULL)
    {
		stbuf->st_mode = S_IFREG | 0755;
		stbuf->st_nlink = 1;
	}
	else
	{
		stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
	}
	
    return res;
}





static int sys_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi)
{

    (void) offset;
    (void) fi;
	int i;
	
        
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
	if(strcmp(path, "/") == 0)
	{

		filler(buf, "NAMES", NULL, 0);
		filler(buf, "CODES", NULL, 0);
	}
	else if (strcmp(path, "/NAMES") == 0)		//şehirleri oluşturuyor
	{
		struct Unique_val *create_city = get_unique_city();
		struct Unique_val * traverse = create_city;
		while(create_city){
						
			filler(buf,create_city->veri,NULL,0);
			create_city=create_city->next;
		}
		
		struct Unique_val* temp = NULL;

		while(traverse)
		{
			free(traverse->veri);
			temp = traverse;
			traverse = traverse->next;
			free(temp);
		}

	}
	else if(strcmp(path,"/CODES")==0){  	// CODES'un altında şehir kodlarını oluşturuyor

		struct Unique_val *create_code = get_postal_code();
		struct Unique_val * traverse = create_code;
		while(create_code){
						
			filler(buf,create_code->veri,NULL,0);
			create_code=create_code->next;
		}
		
		struct Unique_val* temp = NULL;

		while(traverse)
		{
			free(traverse->veri);
			temp = traverse;
			traverse = traverse->next;
			free(temp);
		}

	}
	else if(occurence(path) == 2)	// İlçeleri oluşturuyor
	{
		char* type = strtok(path, "/");
		
		if(strcmp(type, "NAMES") == 0){
			char* city = strtok(NULL, "/");

			struct Unique_val *create_city = get_unique_district(city);
			struct Unique_val * traverse = create_city;
			while(create_city){
							
				filler(buf,create_city->veri,NULL,0);
				create_city = create_city->next;
			}
				
			struct Unique_val* temp = NULL;

			while(traverse)
			{
				free(traverse->veri);
				temp = traverse;
				traverse = traverse->next;
				free(temp);
			}			
		}
		else if(strcmp(type,"CODES")==0){
			char *code=strtok(NULL,"/");
			struct Unique_val *create_codeFile=get_postal_code_full(code);
			struct Unique_val * traverse = create_codeFile;
			char temp_str[15];
			
			while(create_codeFile){
				strcpy(temp_str,create_codeFile->veri);
				strcat(temp_str,".txt");		
				filler(buf,temp_str,NULL,0);
				create_codeFile = create_codeFile->next;
			}
				
			struct Unique_val* temp = NULL;
			while(traverse)
			{
				free(traverse->veri);
				temp = traverse;
				traverse = traverse->next;
				free(temp);
			}			
		}
		
	}
	
	else {  		// path'te 3 tane '/' var, ilçeler oluşturulmuş. neighborhood.txt ler oluşturulacak
		
		char* type = strtok(path, "/");
		
		if(strcmp(type, "NAMES") == 0){
			char* city = strtok(NULL, "/");
			char *district = strtok(NULL, "/");
			
			struct Unique_val *create_neighborhood = get_neighborhood(city, district);
			struct Unique_val *traverse = create_neighborhood;
			char temp_str[20];
			
			while(create_neighborhood){				
				strcpy(temp_str,create_neighborhood->veri );
				strcat(temp_str, ".txt");
				filler(buf, temp_str, NULL, 0);
				create_neighborhood = create_neighborhood->next;
			}
			
			struct Unique_val *temp = NULL;

			while(traverse){
				free(traverse->veri);
				temp = traverse;
				traverse = traverse->next;
				free(temp);
			}
		}	
	}

    return 0;
}
static struct fuse_operations sys_oper = {
    .getattr	= sys_getattr,
    .readdir	= sys_readdir,
//    .open	= sys_open,
//    .read	= sys_read,
};
int main(int argc, char *argv[]){
    return fuse_main(argc, argv, &sys_oper, NULL);
}
