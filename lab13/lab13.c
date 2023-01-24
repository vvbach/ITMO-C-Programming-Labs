#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct Header {
    char ID3[3];
    char version[2];
    char flag;
    char size[4];
} Header;

typedef struct FrameHeader{
    char frameID[4];
    char size[4];
    char flag[2];
} FrameHeader;

unsigned int hexToDecimal(char* size){
    unsigned int n = 0;
    for (int i = 0; i < 4; i++){
        n = n | (size[i] << (3 - i) * 7);
    }
    return n;
}

char* decimalToHex(unsigned int x){
    char *ans = (char*)malloc(4 * sizeof(char));
    for (int i = 3; i >= 0; i--){
        ans[i] = x & 0x7f;
        x >>= 7;
    }
    return ans;
}

int checkFrameID(char *frameID){
    for (int i = 0; i < 4; i++){
        if (!((frameID[i] >= 'A' && frameID[i] <= 'Z') 
        || (frameID[i] >= '0' && frameID[i] <= '9'))){
            return 0;
        }
    }
    return 1;
}

void show(unsigned char *fileName){
    FILE *f = fopen(fileName, "rb");
    if (f == NULL) {
        printf("File not found !");
        return;
    }
    Header tagHeader;
    fseek(f, 0, SEEK_SET);
    fread(&tagHeader, sizeof(Header), 1, f);

    if(tagHeader.flag >> 6){ // if extented header exists, move 6 bytes forward
        fseek(f, 6, SEEK_CUR);
    }

    unsigned int tagSize = hexToDecimal(tagHeader.size);

    int counter = 0;
    while (counter < tagSize)
    {
        // read 10 bytes of the header
        counter += 10;
        FrameHeader frameHeader;
        fread(&frameHeader, sizeof(FrameHeader), 1 ,f);
        unsigned int frameSize = hexToDecimal(frameHeader.size);
        if (!checkFrameID(frameHeader.frameID)){
            break;
        }

        // read data of the frame
        counter += frameSize;
        printf("%s      ", frameHeader.frameID);
        while(frameSize){
            char c = fgetc(f);
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')){
                printf("%c", c);
            }
            frameSize--;
        }
        printf("\n");
    }
    
}

void get(unsigned char *fileName, unsigned char *frameName){
    FILE *f = fopen(fileName, "rb");
    if (f == NULL) {
        printf("File not found !");
        return;
    }
    Header tagHeader;
    fseek(f, 0, SEEK_SET);
    fread(&tagHeader, sizeof(Header), 1, f);

    if(tagHeader.flag >> 6){ // if extented header exists, move 6 bytes forward
        fseek(f, 6, SEEK_CUR);
    }

    unsigned int tagSize = hexToDecimal(tagHeader.size);

    int counter = 0;
    int frameFound = 0;

    while (counter < tagSize)
    {
        // read 10 bytes of the header
        counter += 10;
        FrameHeader frameHeader;
        fread(&frameHeader, sizeof(FrameHeader), 1 ,f);
        unsigned int frameSize = hexToDecimal(frameHeader.size);
        if (!checkFrameID(frameHeader.frameID)){
            break;
        }

        // read data of the frame
        counter += frameSize;
        if(strcmp(frameHeader.frameID, frameName) == 0){
            frameFound = 1;
            printf("%s      ", frameHeader.frameID);
            while(frameSize){
                char c = fgetc(f);
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')){
                    printf("%c", c);
                }
                frameSize--;
            }
            break;
        }
        else {
            while(frameSize){
                char c = fgetc(f);
                frameSize--;
            }
        }
    }
    if (!frameFound) printf("Frame not found !");
    fclose(f);
}

void set(unsigned char *fileName, unsigned char *frameName, unsigned char *value){
    FILE *f = fopen(fileName, "rb");
    if (f == NULL) {
        printf("File not found !");
        return;
    }
    FILE *temp = fopen("temp.mp3", "w+b");
    FILE *temp2 = fopen("temp2.mp3", "w+b");

    Header tagHeader;
    fseek(f, 0, SEEK_SET);
    fread(&tagHeader, sizeof(Header), 1, f);

    if(tagHeader.flag >> 6){ // if extented header exists, move 6 bytes forward
        fseek(f, 6, SEEK_CUR);
    }

    unsigned int tagSize = hexToDecimal(tagHeader.size);

    int counter = 0;
    int frameFound = 0;

    while (counter < tagSize)
    {
        // read 10 bytes of the header
        counter += 10;
        FrameHeader frameHeader;
        fread(&frameHeader, sizeof(FrameHeader), 1 ,f);
        unsigned int frameSize = hexToDecimal(frameHeader.size);
        if (!checkFrameID(frameHeader.frameID)){
            break;
        }

        // read data of the frame
        counter += frameSize;
        if(strcmp(frameHeader.frameID, frameName) == 0){
            frameFound = 1;
            fwrite(frameHeader.frameID, sizeof(frameHeader.frameID), 1, temp);
            char *size = decimalToHex(strlen(value));
            fwrite(size, 4, 1, temp);
            fwrite(frameHeader.flag, sizeof(frameHeader.flag), 1, temp);
            fwrite(value, strlen(value), 1, temp);

            unsigned int frSize = frameSize; 
            while(frSize){ // ignore the current content of the frame
                char c = fgetc(f);
                frSize--;
            } 
            while (1){ // copy the rest into a temp file
                char c = fgetc(f);
                if (feof(f)){
                    break;
                }
                fputc(c, temp);
            }

            fseek(f, 0, SEEK_SET); // return to begin of the file and copy until reach the frame, this temp2 will be renamed as the new original file
            int p = 0;
            unsigned int frSize2 = frameSize;
            while (p < counter + 10 - 10 - frSize2 + ((tagHeader.flag >> 6) ? 6 : 0)){ // counter + 10 = size of tag header (10) + number of bytes have been read in "counter"
                char c = fgetc(f);
                fputc(c, temp2);
                p++;
            }

            fseek(temp, 0, SEEK_SET);
            while (1){ // copy the rest into a new original file
                char c = fgetc(temp);
                if (feof(temp)){
                    break;
                }
                fputc(c, temp2);
            }
            break; 
        }
        else {
            while(frameSize){
                char c = fgetc(f);
                frameSize--;
            }
        }
    }
    fclose(f);
    fclose(temp);
    fclose(temp2);
    
    remove("temp.mp3");
    if (!frameFound){
        printf("Frame not found !");
        remove("temp2.mp3");
    }
    else {
        remove(fileName);
        rename("temp2.mp3", fileName);
    }
}

int main(int argc, char* argv[]){
    unsigned char *fileName, *frameName, *value;
    for (int i = 1; i < argc; i++){
        if (strstr(argv[i], "--filepath")){
            fileName = strpbrk(argv[i], "=") + 1;
        }
        else if (strstr(argv[i], "--show")){
            show(fileName);
        }
        else if (strstr(argv[i], "--get")){
            frameName = strpbrk(argv[i], "=") + 1;
            get(fileName, frameName);
        }
        else if (strstr(argv[i], "--set")){
            frameName = strpbrk(argv[i], "=") + 1;
        }
        else if (strstr(argv[i], "--value")){
            value = strpbrk(argv[i], "=") + 1;
            set(fileName, frameName, value);
        }
    }
    
}