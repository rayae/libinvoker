#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#define BUFFER_SIZE 4


int getStringLength(char *string){
    int i=0;
    char ch=NULL;
    while ( (ch = *(string + i)) != '\xFF' ) {
        i++;
    }
    return i;
}
int split_app_usage(){
   printf("split_app <UPDATE.APP>\n");
   return 1;
}
int split_app_main(int argc, char *argv[])
{
    FILE *fp,*fd;
    unsigned int tmp;
    unsigned int magic=0xa55aaa55;
    unsigned int packet_size=0;
    unsigned int flag=1;
    unsigned char  hwid[8]="";
    unsigned int filetype=0;
    unsigned int data_size=0;
    unsigned char  date[16]="";
    unsigned char  time[16]="";
    unsigned char  filename[32]="";
    int other_size=0;
    int number=1;
    char basename[32]="";
    char basehwid[8]="";
    int fp_start=0;
    int fp_local=0;
    int i=0,count=0,counts=0;
    int end_point=0;
    const char *file;
    const char *dir;
    if(!argv[1]){
    	split_app_usage();
    	return 1;
    } else {
    	file = argv[1];
    }if(!argv[2]){
    	split_app_usage();
    	return 1;
    } else {
    	dir = argv[2];
    }
    mkdir(dir, 0777);
    chdir(dir);
    if ( (fp=fopen(file,"rb")) == NULL) {
        return split_app_usage();
    }
    while (!feof(fp)) {
        fscanf(fp, "%4c", &tmp);
        if (tmp == magic) {
            fp_start=(ftell(fp)-4);
            fscanf(fp, "%4c",&packet_size);
            fscanf(fp, "%4c",&flag);
            fscanf(fp, "%8c",&hwid);
            fscanf(fp, "%4c",&filetype);
            fscanf(fp, "%4c",&data_size);
            fscanf(fp, "%16c",&date);
            fscanf(fp, "%16c",&time);
            fscanf(fp, "%32c",&filename);
            other_size=( packet_size - 92 );
            fseek(fp, other_size, SEEK_CUR);
            if ( strcmp(filename,"INPUT") == 0 ) {
                sprintf(basename, "output_%02d.img", number);
                strncpy(filename, basename, sizeof(filename));
                number++;
            }
            strncpy(basehwid, hwid , getStringLength(hwid));
            if ((fd=fopen(filename,"wb"))==NULL) {
                fseek(fp, 88, SEEK_CUR);
                continue;
            }
            unsigned char buffer[BUFFER_SIZE];
            counts = 0;
            while ( counts < data_size ){
                if (feof(fp)) {
                    break;
                }
                count = fread(buffer, 1, BUFFER_SIZE, fp);
                fwrite(buffer, 1 , BUFFER_SIZE, fd);
                counts+=count;
            } 
            fclose(fd);
            fseek(fp, ( fp_start + 92 ) , SEEK_SET);
        }
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
