#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool find_signature(char* data)
{
    if((int)data[0] == -1 && (int)data[1] == -40 && (int)data[2] == -1)
    {
        for(int i = 0; i < 16; i++)
        {
            if((int)data[3] == -32 + i)
            {
                return true;
            }
        }
    }
    return false;
}

void change_num(char* num)
{
    int i = 2;
    while(num[i] == '9' && i >= 0)
    {
        num[i] = '0';
        i--;
    }
    if(i >= 0)
    {
        num[i]++;
    }
    return;
}
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("./recover image_name\n");
        return 1;
    }
    FILE* f = fopen(argv[1], "r");
    char num[8] = {'0', '0', '0','.','j','p','g'};
    FILE* g = NULL;
    if(f != NULL)
    {
        char data[513];
        while(fread(&data, sizeof(char), 512, f))
        {
            data[512] = '\n';
            if(find_signature(data))
            {
                if(g == NULL)
                {
                    g = fopen(num, "w");
                }
                else
                {
                    fclose(g);
                    change_num(num);
                    g = fopen(num, "w");
                }
                fwrite(&data, sizeof(char), 512, g);
            }
            else if(g != NULL)
            {
                fwrite(&data, sizeof(char), 512, g);
            }
        }
        fclose(f);
        fclose(g);
    }
    else
    {
        printf("Can't open the file\n");
        return 1;
    }

}
