#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

void writeBigEndian(FILE *outputFile, int value, size_t size)
{
    for (int i = size - 1; i >= 0; --i)
    {
        unsigned char byte = (value >> (8 * i)) & 0xFF;
        if (fwrite(&byte, 1, 1, outputFile) != 1)
        {
            fclose(outputFile);
        }
    }
}

int checkOpcode(char *line, regex_t *regexArray, int regexSize)
{
    regmatch_t match;
    for (int i = 0; i < regexSize; i++)
    {
        if (regexec(&regexArray[i], line, 1, &match, 0) == 0)
        {
            return i; // return the opcode if matched regex
        }
    }
    return -1;
}

int isWithinBounds_8bit(char *strValue, int8_t dataValue)
{
    if (strValue == NULL)
    {
        return 0;
    }

    size_t len = strlen(strValue);

    while (len > 0 && strValue[0] == ' ')
    {
        strValue++;
        len--;
    }

    while (len > 0 && strValue[len - 1] == ' ')
    {
        strValue[len - 1] = '\0';
        len--;
    }

    char *endptr;
    long strToInt = strtol(strValue, &endptr, 10);

    if (*endptr != '\0')
    {
        return 0;
    }

    return strToInt == dataValue;
}

int isWithinBounds_16bit(char *strValue, int16_t dataValue)
{
    if (strValue == NULL)
    {
        return 0;
    }

    size_t len = strlen(strValue);

    while (len > 0 && strValue[0] == ' ')
    {
        strValue++;
        len--;
    }

    while (len > 0 && strValue[len - 1] == ' ')
    {
        strValue[len - 1] = '\0';
        len--;
    }

    char *endptr;
    long strToInt = strtol(strValue, &endptr, 10);

    if (*endptr != '\0')
    {
        return 0;
    }

    return strToInt == dataValue;
}

int isWithinBounds_32bit(char *strValue, int32_t dataValue)
{
    if (strValue == NULL)
    {
        return 0;
    }

    size_t len = strlen(strValue);

    while (len > 0 && strValue[0] == ' ')
    {
        strValue++;
        len--;
    }

    while (len > 0 && strValue[len - 1] == ' ')
    {
        strValue[len - 1] = '\0';
        len--;
    }

    char *endptr;
    long strToInt = strtol(strValue, &endptr, 10);

    if (*endptr != '\0')
    {
        return 0;
    }

    return strToInt == dataValue;
}

int isWithinBounds_64bit(char *strValue, int64_t dataValue)
{
    if (strValue == NULL)
    {
        return 0;
    }

    size_t len = strlen(strValue);

    while (len > 0 && strValue[0] == ' ')
    {
        strValue++;
        len--;
    }

    while (len > 0 && strValue[len - 1] == ' ')
    {
        strValue[len - 1] = '\0';
        len--;
    }

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%" PRId64, dataValue);

    return strcmp(strValue, buffer) == 0;
}

bool removeFile(const char *filename)
{
    if (remove(filename) == 0)
    {
        // printf("Removed file: %s\n", filename);
        return true;
    }
    else
    {
        // printf("Failed to remove file: %s\n", filename);
        return false;
    }
}

int handleMissingCodeSection(FILE *output, const char *outputFile)
{
    // fprintf(stderr, "Error: No code section found in the input file.\n");
    fclose(output);
    if (!removeFile(outputFile))
    {
        return -1;
    }
    return -1;
}

int main(int argc, char **argv)
{

    // 2 arguments must be passed
    if (argc != 2)
    {
        fprintf(stderr, "Invalid slinker filepath\n");
        return 1;
    }

    // checks to see if first argument is NULL or not
    if (argv[1] == NULL)
    {
        fprintf(stderr, "Invalid slinker filepath\n");
        return 1;
    }

    char *path = argv[1];
    FILE *fptr = fopen(path, "r");
    // checks to see if file is NULL or not
    if (fptr == NULL)
    {
        fprintf(stderr, "Invalid slinker filepath\n");
        return 1;
    }

    // checks to see if the second argument ends in a slk
    char *extension = strrchr(argv[1], '.');
    if (extension == NULL || strcmp(extension, ".slk") != 0)
    {
        fprintf(stderr, "Invalid slinker filepath\n");
        return 1;
    }

    // get output file name and make output file
    char *outputFile = malloc(strlen(argv[1]) + 2);
    strcpy(outputFile, argv[1]);
    strcat(outputFile, "o");
    FILE *output = fopen(outputFile, "wb");

    // printf("the output file name is: %s\n", outputFile);

    /*checks to see if output is NULL
    if (output == NULL)
    {
        fprintf(stderr, "Failed to create output file\n");
        fclose(fptr);
        return 1;
    }


    // reading file and putting it in a character array!
    fseek(fptr, 0L, SEEK_END);
    long fileSize = ftell(fptr);
    char *buffer = (char *)malloc(fileSize * sizeof(char) + 1);
    buffer[fileSize] = '\0';
    rewind(fptr);


    size_t bytesRead = fread(buffer, 1, fileSize, fptr);
    char split[] = "\n";
    int numberOfLines = 1;


    counting number of lines
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == '\n')
        {
            numberOfLines++;
        }
    }
    printf("lines: %d\n", numberOfLines);


    printing each line
    char *splitter[numberOfLines];
    splitter[0] = strtok(buffer, "\n");
    for (int i = 1; i < numberOfLines; i++)
    {
        splitter[i] = strtok(NULL, "\n");
        if (splitter[i] == NULL)
        {
            fprintf(stderr, "Error: Failed to tokenize line %d\n", i);
        }
        else
        {
            printf("%s\n", splitter[i]);
        }
    }


    counting number of colons
    int j = 0;
    int numberOfColons = 0;
    while (j < numberOfLines)
    {
        if (splitter[j][0] == ':')
        {
            numberOfColons++;
        }
        j++;
    }
    printf("Number of colons: %d\n", numberOfColons);
    */

    regex_t opcodeRegexArray[143]; // array stores regex for opcodes

    // initialize regex patterns for opcodes
    const char *opcodePatterns[] = {
        "^\tpushb (-?[0-9]+)$", // pushb value >> 8-bit // 0
        "^\tpushs (-?[0-9]+)$", // pushs value >> 16-bit // 1
        "^\tpushi (-?[0-9]+)$", // pushi value >> 32-bit // 2
        "^\tpushl (-?[0-9]+)$", // pushl value >> 64-bit // 3
        "^\tpushf (-?[0-9]+)$", // pushf value >> 32-bit // 4
        "^\tpushd (-?[0-9]+)$", // pushd value >> 64-bit // 5
        "^\tpushbm (:[a-zA-Z0-9_]+|:[a-zA-Z0-9_]+([-+][0-9]+)?|[0-9]+)$"
        "^\tpushsm (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",          // pushsm address // 7
        "^\tpushim (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",          // pushim address // 8
        "^\tpushlm (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",          // pushlm address // 9
        "^\tpushfm (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",          // pushdm address // 10
        "^\tpushdm (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",          // pushdm address // 11
        "^\tpushmm (:[a-zA-Z0-9_]+)(([-+][0-9]+))? ([0-9]+)$", // pushmm address items // 12
        "^\tdupb$",                                            // dupb // 13
        "^\tdups$",                                            // dups // 14
        "^\tdupi$",                                            // dupi // 15
        "^\tdupl$",                                            // dupl // 16
        "^\tdupf$",                                            // dupf // 17
        "^\tdupd$",                                            // dupd // 18
        "^\tpopb$",                                            // popb // 19
        "^\tpops$",                                            // pops // 20
        "^\tpopi$",                                            // popi // 21
        "^\tpopl$",                                            // popl // 22
        "^\tpopf$",                                            // popf // 23
        "^\tpopd$",                                            // popd // 24
        "^\tpopbm (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",           // popbm address // 25
        "^\tpopsm (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",           // popsm address // 26
        "^\tpopim (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",           // popim address // 27
        "^\tpoplm (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",           // poplm address // 28
        "^\tpopfm (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",           // popfm address // 29
        "^\tpopdm (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",           // popdm address // 30
        "^\tpopmm (:[a-zA-Z0-9_]+)(([-+][0-9]+))? ([0-9]+)$",  // popmm address items // 31
        "^\tswapb$",                                           // swapb // 32
        "^\tswaps$",                                           // swaps // 33
        "^\tswapi$",                                           // swapi // 34
        "^\tswapl$",                                           // swapl // 35
        "^\tswapf$",                                           // swapf // 36
        "^\tswapd$",                                           // swapd // 37
        "^\tconvbs$",                                          // convbs // 38
        "^\tconvbi$",                                          // convbi // 39
        "^\tconvbl$",                                          // convbl // 40
        "^\tconvbf$",                                          // convbf // 41
        "^\tconvbd$",                                          // convbd // 42
        "^\tconvsb$",                                          // convsb // 43
        "^\tconvsi$",                                          // convsi // 44
        "^\tconvsl$",                                          // convsl // 45
        "^\tconvsf$",                                          // convsf // 46
        "^\tconvsd$",                                          // convsd // 47
        "^\tconvib$",                                          // convib // 48
        "^\tconvis$",                                          // convis // 49
        "^\tconvil$",                                          // convil // 50
        "^\tconvif$",                                          // convif // 51
        "^\tconvid$",                                          // convid // 52
        "^\tconvlb$",                                          // convlb // 53
        "^\tconvls$",                                          // convls // 54
        "^\tconvli$",                                          // convli // 55
        "^\topcode 0x38 is skipped$",                          // opcode 0x38 is skipped // 56
        "^\tconvlf$",                                          // convlf // 57
        "^\tconvld$",                                          // convld // 58
        "^\tconvfb$",                                          // convfb // 59
        "^\tconvfs$",                                          // convfs // 60
        "^\tconvfi$",                                          // convfi // 61
        "^\tconvfl$",                                          // convfl // 62
        "^\tconvfd$",                                          // convfd // 63
        "^\tconvdb$",                                          // convdb // 64
        "^\tconvds$",                                          // convds // 65
        "^\tconvdi$",                                          // convdi // 66
        "^\tconvdl$",                                          // convdl // 67
        "^\tconvdf$",                                          // convdf // 68
        "^\tinch$",                                            // inch // 69
        "^\tinb$",                                             // inb // 70
        "^\tins$",                                             // ins // 71
        "^\tini$",                                             // ini // 72
        "^\tinl$",                                             // inl // 73
        "^\tinf$",                                             // inf // 74
        "^\tind$",                                             // ind // 75
        "^\toutch$",                                           // outch // 76
        "^\toutb$",                                            // outb // 77
        "^\touts$",                                            // outs // 78
        "^\touti$",                                            // outi // 79
        "^\toutl$",                                            // outl // 80
        "^\toutf$",                                            // outf // 81
        "^\toutd$",                                            // outd // 82
        "^\taddb$",                                            // addb // 83
        "^\tadds$",                                            // adds // 84
        "^\taddi$",                                            // addi // 85
        "^\taddl$",                                            // addl // 86
        "^\taddf$",                                            // addf // 87
        "^\taddd$",                                            // addd // 88
        "^\tsubb$",                                            // subb // 89
        "^\tsubs$",                                            // subs // 90
        "^\tsubi$",                                            // subi // 91
        "^\tsubl$",                                            // subl // 92
        "^\tsubf$",                                            // subf // 93
        "^\tsubd$",                                            // subd // 94
        "^\tmulb$",                                            // mulb // 95
        "^\tmuls$",                                            // muls // 96
        "^\tmuli$",                                            // muli // 97
        "^\tmull$",                                            // mull // 98
        "^\tmulf$",                                            // mulf // 99
        "^\tmuld$",                                            // muld // 100
        "^\tdivb$",                                            // divb // 101
        "^\tdivs$",                                            // divs // 102
        "^\tdivi$",                                            // divi // 103
        "^\tdivl$",                                            // divl // 104
        "^\tdivf$",                                            // divf // 105
        "^\tdivd$",                                            // divd // 106
        "^\tand8$",                                            // and8 // 107
        "^\tand16$",                                           // and16 // 108
        "^\tand32$",                                           // and32 // 109
        "^\tand64$",                                           // and64 // 110
        "^\tor8$",                                             // or8 // 111
        "^\tor16$",                                            // or16 // 112
        "^\tor32$",                                            // or32 // 113
        "^\txor64$",                                           // or64 // 114
        "^\txor8$",                                            // xor8 // 115
        "^\txor16$",                                           // xor16 // 116
        "^\txor32$",                                           // xor32 // 117
        "^\txor64$",                                           // xor64 // 118
        "^\tnot8$",                                            // not8 // 119
        "^\tnot16$",                                           // not16 // 120
        "^\tnot32$",                                           // not32 // 121
        "^\tnot64$",                                           // not64 // 122
        "^\tshftrb (-?[0-9]+)$",                               // shftrb value >> 8-bit // 123
        "^\tshftrs (-?[0-9]+)$",                               // shftrs value >> 8-bit // 124
        "^\tshftri (-?[0-9]+)$",                               // shftri value >> 8-bit // 125
        "^\tshftrl (-?[0-9]+)$",                               // shftrl value >> 8-bit // 126
        "^\tshftlb (-?[0-9]+)$",                               // shftlb value >> 8-bit // 127
        "^\tshftls (-?[0-9]+)$",                               // shftls value >> 8-bit // 128
        "^\tshftli (-?[0-9]+)$",                               // shftli value >> 8-bit // 129
        "^\tshftll (-?[0-9]+)$",                               // shftll value >> 8-bit // 130
        "^\tjmp (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",             // jmp address // 131
        "^\tjrpc (-?[0-9]+)$",                                 // jrpc offset // 132
        "^\tjind$",                                            // jind // 133
        "^\tjz (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",              // jz address // 134
        "^\tjnz (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",             // jnz address // 135
        "^\tjgt (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",             // jgt address // 136
        "^\tjlt (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",             // jlt address // 137
        "^\tjge (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",             // jge address // 138
        "^\tjle (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",             // jle address // 139
        "^\tcall (:[a-zA-Z0-9_]+)(([-+][0-9]+))?$",            // call address // 140
        "^\treturn$",                                          // return // 141
        "^\thalt$"                                             // halt // 142
    };

    // compile regex patterns
    for (int i = 0; i < 143; i++)
    {
        if (regcomp(&opcodeRegexArray[i], opcodePatterns[i], REG_EXTENDED | REG_NOSUB) != 0)
        {
            fclose(fptr);
            remove(outputFile);
            exit(EXIT_FAILURE);
            return 1;
        }
    }

    char fileLine[256];
    int lineNumber, codeNumberCount, codeLines, codeOffsetNumber = 0;
    bool codeSection;

    while (fgets(fileLine, sizeof(fileLine), fptr) != NULL)
    {
        lineNumber++;

        if (fileLine[0] == ';')
        {
            // printf("%s\n", fileLine);
            continue;
        }

        if (strncmp(fileLine, ".code", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeNumberCount++;
            codeSection = true;
            codeOffsetNumber = 8;

            if (codeNumberCount == 1)
            {
                // printf("the code offset is: %d\n", codeOffsetNumber);
                writeBigEndian(output, codeOffsetNumber, sizeof(int));
            }
        }

        if (fileLine[0] == '.' && strncmp(fileLine, ".code", 5) != 0)
        {
            // printf("%s\n", fileLine);
            codeSection = false;
            break;
        }

        int whitespace = 0;
        while (isspace(fileLine[whitespace]))
            whitespace++;
        if (codeSection && whitespace > 0)
        {
            // printf("%s\n", fileLine);
        }
    }

    // checks to see if there is a .code section
    if (codeNumberCount == 0)
    {
        remove(outputFile);
        exit(EXIT_FAILURE);
        return 1;
    }

    rewind(fptr);
    lineNumber = 0;
    int dataOffsetNumber = codeOffsetNumber;
    bool dataSection, byteSection, doubleSection, longSection, asciiSection, shortSection, intSection, floatSection;

    while (fgets(fileLine, sizeof(fileLine), fptr) != NULL)
    {
        lineNumber++;
        size_t length = strlen(fileLine);
        if (fileLine[length - 1] == '\n')
        {
            fileLine[length - 1] = '\0';
        }
        if (fileLine[0] == ';')
        {
            // printf("%s\n", fileLine);
            continue;
        }
        if (fileLine[0] == ':')
        {
            // printf("%s\n", fileLine);
            codeSection, dataSection, byteSection, doubleSection, longSection, asciiSection, shortSection, intSection, floatSection = false;
        }
        if (strncmp(fileLine, ".code", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection = true;
            dataSection, byteSection, doubleSection, longSection, asciiSection, shortSection, intSection, floatSection = false;
            continue;
        }

        if (strncmp(fileLine, ".data", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, byteSection, doubleSection, longSection, asciiSection, shortSection, intSection, floatSection = false;
            dataSection = true;
            continue;
        }
        if (strncmp(fileLine, ".byte", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, dataSection, doubleSection, longSection, asciiSection, shortSection, intSection, floatSection = false;
            byteSection = true;
            continue;
        }
        if (strncmp(fileLine, ".ascii", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, dataSection, doubleSection, longSection, byteSection, shortSection, intSection, floatSection = false;
            asciiSection = true;
            continue;
        }
        if (strncmp(fileLine, ".short", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, dataSection, doubleSection, longSection, byteSection, asciiSection, intSection, floatSection = false;
            shortSection = true;
            continue;
        }
        if (strncmp(fileLine, ".int", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, dataSection, doubleSection, longSection, byteSection, asciiSection, shortSection, floatSection = false;
            intSection = true;
            continue;
        }
        if (strncmp(fileLine, ".long", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, dataSection, doubleSection, intSection, byteSection, asciiSection, shortSection, floatSection = false;
            longSection = true;
            continue;
        }
        if (strncmp(fileLine, ".float", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, dataSection, doubleSection, intSection, byteSection, asciiSection, shortSection, longSection = false;
            floatSection = true;
            continue;
        }
        if (strncmp(fileLine, ".double", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, dataSection, floatSection, intSection, byteSection, asciiSection, shortSection, longSection = false;
            doubleSection = true;
            continue;
        }
        if (dataSection)
        {
            // printf("i'm in the data section! \n");
            /*int instructions = 0;
            while (isspace(fileLine[instructions]))
            {
                instructions++;
            }
            if (instructions > 0)
            {
                printf("%s\n", fileLine);
            }*/
        }
        if (byteSection)
        {
            // printf("i'm in the byte section! \n");
            int instructions = 0;
            while (isspace(fileLine[instructions]))
            {
                instructions++;
            }
            if (instructions > 0)
            {
                uint8_t numberOfBytes;
                sscanf(fileLine + instructions, "%hhd", &numberOfBytes);
                dataOffsetNumber += numberOfBytes;
                // printf("the number of bytes is: %d\n", numberOfBytes);
            }
        }
        if (asciiSection)
        {
            // printf("i'm in the ascii section! \n");

            int instructions = 0;
            while (isspace(fileLine[instructions]))
            {
                instructions++;
            }
            if (instructions > 0)
            {
                int numberOfAscii = fileLine[instructions];
                dataOffsetNumber += numberOfAscii;
                // printf("%s\n", fileLine);
            }
        }
        if (shortSection)
        {
            // printf("i'm in the short section! \n");

            int instructions = 0;
            while (isspace(fileLine[instructions]))
            {
                instructions++;
            }
            if (instructions > 0)
            {
                short numberOfShort;
                sscanf(fileLine + instructions, "%hd", &numberOfShort);
                dataOffsetNumber += numberOfShort;
            }
        }
        if (intSection)
        {
            // printf("i'm in the int section! \n");
            int instructions = 0;
            while (isspace(fileLine[instructions]))
            {
                instructions++;
            }
            if (instructions > 0)
            {
                int numberOfInt;
                sscanf(fileLine + instructions, "%d", &numberOfInt);
                dataOffsetNumber += numberOfInt;
            }
        }
        if (longSection)
        {
            // printf("i'm in the long section \n");

            int instructions = 0;
            while (isspace(fileLine[instructions]))
            {
                instructions++;
            }
            if (instructions > 0)
            {
                long numberOfLong;
                sscanf(fileLine + instructions, "%ld", &numberOfLong);
                dataOffsetNumber += numberOfLong;
            }
        }
        if (floatSection)
        {
            // printf("i'm in the float section! \n");
            int instructions = 0;
            while (isspace(fileLine[instructions]))
            {
                instructions++;
            }
            if (instructions > 0)
            {
                float numberOfFloat;
                sscanf(fileLine + instructions, "%f", &numberOfFloat);
                dataOffsetNumber += numberOfFloat;
            }
        }
        if (doubleSection)
        {
            // printf("i'm in the double section! \n");

            int instructions = 0;
            while (isspace(fileLine[instructions]))
            {
                instructions++;
            }
            if (instructions > 0)
            {
                double numberOfDouble;
                sscanf(fileLine + instructions, "%lf", &numberOfDouble);
                dataOffsetNumber += numberOfDouble;
            }
        }
        int white = 0;
        while (isspace(fileLine[white]))
        {
            white++;
        }
        if (codeSection && white > 0)
        {
            // printf("%s\n", fileLine);
            int opcode = checkOpcode(fileLine, opcodeRegexArray, 143);
            

            if (opcode == 0 || opcode == 123 || opcode == 124 || opcode == 125 || opcode == 126 || opcode == 127 ||
                opcode == 128 || opcode == 129 || opcode == 130)
            {
                dataOffsetNumber += 2;
            }
            else if (opcode == 1)
            {
                dataOffsetNumber += 3;
            }
            else if (opcode == 2)
            {
                dataOffsetNumber += 4;
            }
            else if (opcode == 3)
            {
                dataOffsetNumber += 5;
            }
            else if (opcode == 4)
            {
                dataOffsetNumber += 4;
            }
            else if (opcode == 5)
            {
                dataOffsetNumber += 5;
            }
            else if (opcode == 6 || opcode == 7 || opcode == 8 || opcode == 9 || opcode == 10 || opcode == 11 ||
                     opcode == 25 || opcode == 26 || opcode == 27 || opcode == 28 || opcode == 29 || opcode == 30 ||
                     opcode == 131 || opcode == 134 || opcode == 135 || opcode == 136 || opcode == 137 || opcode == 138 ||
                     opcode == 139 || opcode == 140)
            {
                // skip
            }
            else if (opcode == 12 || opcode == 31)
            {
                // skip
            }
            else if (opcode >= 13 && opcode <= 95)
            {
                dataOffsetNumber += 1;
            }
            else if (opcode == 96)
            {
                // skip
            }
            else if (opcode == 97 || opcode == 98 || opcode == 99 || opcode == 100 || opcode == 101 || opcode == 102 ||
                     opcode == 103 || opcode == 104 || opcode == 105 || opcode == 106 || opcode == 107 || opcode == 108 ||
                     opcode == 109 || opcode == 110 || opcode == 111 || opcode == 112 || opcode == 113 || opcode == 114 ||
                     opcode == 115 || opcode == 116 || opcode == 117 || opcode == 118 || opcode == 119 || opcode == 120 ||
                     opcode == 121 || opcode == 122 || opcode == 133 || opcode == 141 || opcode == 142)
            {
                dataOffsetNumber += 1;
            }
            else if (opcode == 132)
            {
                const char *pattern = opcodePatterns[132];
                // compile all of the regex patterns
                regex_t regex;
                if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
                {
                    fprintf(stderr, "Error on line %d\n", lineNumber);
                    // fprintf(stderr, "%s\n", fileLine);
                    fclose(fptr);
                    remove(outputFile);
                    exit(EXIT_FAILURE);
                    return 1;
                }
                // match the specific regex pattern against line
                regmatch_t matches[2];
                if (regexec(&regex, fileLine, 2, matches, 0) == 0)
                {
                    char temp[100];
                    sscanf(fileLine + matches[1].rm_so, "%s", temp);
                    int8_t value;
                    sscanf(temp, "%hhd", &value);
                    int withinBounds = isWithinBounds_8bit(temp, value);
                    if (withinBounds == 0)
                    {
                        fprintf(stderr, "Error on line %d\n", lineNumber);
                        fclose(fptr);
                        remove(outputFile);
                        exit(EXIT_FAILURE);
                        return 1;
                    }
                    dataOffsetNumber += value;
                    // free the regex resources
                    regfree(&regex);
                }
                else
                {
                    fprintf(stderr, "Error on line %d\n", lineNumber);
                    fclose(fptr);
                    remove(outputFile);
                    exit(EXIT_FAILURE);
                    return 1;
                }
            }
            else
            {
                // skip bc default
            }
        }
    }

    //printf("the data offset value is: %d\n", dataOffsetNumber);
    writeBigEndian(output, dataOffsetNumber, sizeof(int));
    rewind(fptr);
    lineNumber = 0;

    while (fgets(fileLine, sizeof(fileLine), fptr) != NULL)
    {
        lineNumber++;
        size_t length = strlen(fileLine);
        if (fileLine[length - 1] == '\n')
        {
            fileLine[length - 1] = '\0';
        }

        if (fileLine[0] == ';')
        {
            continue;
        }
        if (fileLine[0] == ':')
        {
            codeSection = false;
        }
        if (strncmp(fileLine, ".code", 5) == 0)
        {
            codeSection = true;
            continue;
        }
        if (strncmp(fileLine, ".data", 5) == 0)
        {
            codeSection = false;
            continue;
        }
        if (strncmp(fileLine, ".byte", 5) == 0)
        {
            codeSection = false;
            continue;
        }
        if (strncmp(fileLine, ".ascii", 5) == 0)
        {
            codeSection = false;
            continue;
        }
        if (strncmp(fileLine, ".short", 5) == 0)
        {
            codeSection = false;
            continue;
        }
        if (strncmp(fileLine, ".int", 5) == 0)
        {
            codeSection = false;
            continue;
        }
        if (strncmp(fileLine, ".long", 5) == 0)
        {
            codeSection = false;
            continue;
        }
        if (strncmp(fileLine, ".float", 5) == 0)
        {
            codeSection = false;
            continue;
        }
        if (strncmp(fileLine, ".double", 5) == 0)
        {
            codeSection = false;
            continue;
        }

        int white = 0;
        while (isspace(fileLine[white]))
        {
            white++;
        }

        if (codeSection && white > 0)
        {
            codeLines++;

            int opcode = checkOpcode(fileLine, opcodeRegexArray, 143);
            //printf("this opcode is: %d\n", opcode);

            // define a regex pattern to match instruction
            const char *pattern = opcodePatterns[opcode];

            // compile regex pattern
            regex_t regex;
            if (opcode = -1)
            {
                fprintf(stderr, "Error on line %d\n", lineNumber);
                fclose(fptr);
                remove(outputFile);
                exit(EXIT_FAILURE);
                return 1;
            }
            // if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
            // {
            //     fprintf(stderr, "Error on line %d\n", lineNumber);
            //     fclose(fptr);
            //     remove(outputFile);
            //     exit(EXIT_FAILURE);
            //     return 1;
            // }

            writeBigEndian(output, opcode, sizeof(u_int8_t));

            switch (opcode)
            {
            case 0:
            case 123:
            case 124:
            case 125:
            case 126:
            case 127:
            case 128:
            case 129:
            case 130:
            {
                opcode = 0x00;
                //printf("fuck this fr >> %d\n", opcode);

                dataOffsetNumber += 2;

                // match regex pattern against line
                regmatch_t matches[2];
                if (regexec(&regex, fileLine, 2, matches, 0) == 0)
                {
                    char name[100];
                    sscanf(fileLine + matches[0].rm_so, "%s", name);

                    char temp[100];
                    sscanf(fileLine + matches[1].rm_so, "%s", temp);

                    int8_t value;
                    sscanf(temp, "%hhd", &value);

                    int withinBounds = isWithinBounds_8bit(temp, value);

                    if (withinBounds == 0)
                    {
                        fprintf(stderr, "Error on line %d\n", lineNumber);
                        fclose(fptr);
                        remove(outputFile);
                        exit(EXIT_FAILURE);
                        return 1;
                    }

                    writeBigEndian(output, value, sizeof(int8_t));

                    // free regex resources
                    regfree(&regex);
                }
                else
                {
                    fprintf(stderr, "Error on line %d\n", lineNumber);
                    fclose(fptr);
                    remove(outputFile);
                    exit(EXIT_FAILURE);
                    return 1;
                }

                break;
            }

            case 1: // pushs value >> 16-bit integer
            {
                opcode = 0x01;
                //printf("case 1 MY ASS >> %d\n", opcode);

                dataOffsetNumber += 3;

                // match regex pattern against line
                regmatch_t matches[2];
                if (regexec(&regex, fileLine, 2, matches, 0) == 0)
                {
                    char name[100];
                    sscanf(fileLine + matches[0].rm_so, "%s", name);

                    char temp[100];
                    sscanf(fileLine + matches[1].rm_so, "%s", temp);

                    int16_t value;
                    sscanf(temp, "%hd", &value);

                    int withinBounds = isWithinBounds_16bit(temp, value);

                    if (withinBounds == 0)
                    {
                        fprintf(stderr, "Error on line %d\n", lineNumber);
                        fclose(fptr);
                        remove(outputFile);
                        exit(EXIT_FAILURE);
                        return 1;
                    }

                    writeBigEndian(output, value, sizeof(int16_t));

                    // free regex resources
                    regfree(&regex);
                }
                else
                {
                    fprintf(stderr, "Error on line %d\n", lineNumber);
                    fclose(fptr);
                    remove(outputFile);
                    exit(EXIT_FAILURE);
                    return 1;
                }

                break;
            }

            case 2: // pushi value >> 32-bit integer
            {
                opcode = 0x02;
                //printf("case 2 >> %d\n", opcode);

                dataOffsetNumber += 4;

                // match regex pattern against line
                regmatch_t matches[2];
                if (regexec(&regex, fileLine, 2, matches, 0) == 0)
                {
                    char name[100];
                    sscanf(fileLine + matches[0].rm_so, "%s", name);
                    char temp[100];
                    sscanf(fileLine + matches[1].rm_so, "%s", temp);

                    int32_t value;
                    sscanf(temp, "%d", &value);

                    int withinBounds = isWithinBounds_32bit(temp, value);

                    if (withinBounds == 0)
                    {
                        fprintf(stderr, "Error on line %d\n", lineNumber);
                        fclose(fptr);
                        remove(outputFile);
                        exit(EXIT_FAILURE);
                        return 1;
                    }

                    writeBigEndian(output, value, sizeof(int32_t));

                    // free regex resources
                    regfree(&regex);
                }
                else
                {
                    fprintf(stderr, "Error on line %d\n", lineNumber);
                    fclose(fptr);
                    remove(outputFile);
                    exit(EXIT_FAILURE);
                    return 1;
                }

                break;
            }

            case 3: // pushl value >> 64-bit integer
            {
                opcode = 0x03;
                //printf("the  >> %d\n", opcode);

                dataOffsetNumber += 5;

                // match regex pattern against line
                regmatch_t matches[2];
                if (regexec(&regex, fileLine, 2, matches, 0) == 0)
                {
                    char name[100];
                    sscanf(fileLine + matches[0].rm_so, "%s", name);

                    char temp[100];
                    sscanf(fileLine + matches[1].rm_so, "%s", temp);

                    int64_t value;
                    sscanf(temp, "%ld", &value);

                    int withinBounds = isWithinBounds_64bit(temp, value);

                    if (withinBounds == 0)
                    {
                        fprintf(stderr, "Error on line %d\n", lineNumber);
                        fclose(fptr);
                        remove(outputFile);
                        exit(EXIT_FAILURE);
                        return 1;
                    }

                    writeBigEndian(output, value, sizeof(int64_t));

                    // free regex resources
                    regfree(&regex);
                }
                else
                {
                    fprintf(stderr, "Error on line %d\n", lineNumber);
                    fclose(fptr);
                    remove(outputFile);
                    exit(EXIT_FAILURE);
                    return 1;
                }

                break;
            }

            case 4: // pushf value >> 32-bit integer
            {
                opcode = 0x04;
                //printf("yooo  >> %d\n", opcode);

                dataOffsetNumber += 4;

                // match regex pattern against line
                regmatch_t matches[2];
                if (regexec(&regex, fileLine, 2, matches, 0) == 0)
                {
                    char name[100];
                    sscanf(fileLine + matches[0].rm_so, "%s", name);

                    char temp[100];
                    sscanf(fileLine + matches[1].rm_so, "%s", temp);

                    int32_t value;
                    sscanf(temp, "%d", &value);

                    int withinBounds = isWithinBounds_32bit(temp, value);

                    if (withinBounds == 0)
                    {
                        fprintf(stderr, "Error on line %d\n", lineNumber);
                        fclose(fptr);
                        remove(outputFile);
                        exit(EXIT_FAILURE);
                        return 1;
                    }

                    writeBigEndian(output, value, sizeof(int32_t));

                    // free regex resources
                    regfree(&regex);
                }
                else
                {
                    fprintf(stderr, "Error on line %d\n", lineNumber);
                    fclose(fptr);
                    remove(outputFile);
                    exit(EXIT_FAILURE);
                    return 1;
                }

                break;
            }

            case 5: // pushd value >> 64-bit integer
            {
                opcode = 0x05;
                //printf("the opcode is > %d\n", opcode);

                dataOffsetNumber += 5;

                // match regex pattern against line
                regmatch_t matches[2];
                if (regexec(&regex, fileLine, 2, matches, 0) == 0)
                {
                    char name[100];
                    sscanf(fileLine + matches[0].rm_so, "%s", name);

                    char temp[100];
                    sscanf(fileLine + matches[1].rm_so, "%s", temp);

                    int64_t value;
                    sscanf(temp, "%ld", &value);

                    int withinBounds = isWithinBounds_64bit(temp, value);

                    if (withinBounds == 0)
                    {
                        fprintf(stderr, "Error on line %d\n", lineNumber);
                        fclose(fptr);
                        remove(outputFile);
                        exit(EXIT_FAILURE);
                        return 1;
                    }

                    writeBigEndian(output, value, sizeof(int64_t));

                    // free regex resources
                    regfree(&regex);
                }
                else
                {
                    fprintf(stderr, "Error on line %d\n", lineNumber);
                    fclose(fptr);
                    remove(outputFile);
                    exit(EXIT_FAILURE);
                    return 1;
                }

                break;
            }

            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 131:
            case 134:
            case 135:
            case 136:
            case 137:
            case 138:
            case 139:
            case 140:
            {

                // match regex pattern against line
                regmatch_t matches[2];
                if (regexec(&regex, fileLine, 2, matches, 0) == 0)
                {
                    char name[100];
                    sscanf(fileLine + matches[0].rm_so, "%s", name);

                    char address[100];
                    sscanf(fileLine + matches[1].rm_so, "%s", address);

                    // free regex resources
                    regfree(&regex);
                }
                else
                {
                    fprintf(stderr, "Error on line %d\n", lineNumber);
                    fclose(fptr);
                    remove(outputFile);
                    exit(EXIT_FAILURE);
                    return 1;
                }

                break;
            }

            case 12:
            case 31:
            {
                opcode = 0x0c;

                // match regex pattern against line
                regmatch_t matches[3];
                if (regexec(&regex, fileLine, 3, matches, 0) == 0)
                {
                    char name[100];
                    sscanf(fileLine + matches[0].rm_so, "%s", name);

                    char address[100];
                    sscanf(fileLine + matches[1].rm_so, "%s", address);

                    int items;
                    sscanf(fileLine + matches[2].rm_so, "%d", &items);

                    // free regex resources
                    regfree(&regex);
                }
                else
                {
                    fprintf(stderr, "Error on line %d\n", lineNumber);
                    fclose(fptr);
                    remove(outputFile);
                    exit(EXIT_FAILURE);
                    return 1;
                }

                break;
            }

            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 32:
            case 33:
            case 34:
            case 35:
            case 36:
            case 37:
            case 38:
            case 39:
            case 40:
            case 41:
            case 42:
            case 43:
            case 44:
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
            case 57:
            case 58:
            case 59:
            case 60:
            case 61:
            case 62:
            case 63:
            case 64:
            case 65:
            case 66:
            case 67:
            case 68:
            case 69:
            case 70:
            case 71:
            case 72:
            case 73:
            case 74:
            case 75:
            case 76:
            case 77:
            case 78:
            case 79:
            case 80:
            case 81:
            case 82:
            case 83:
            case 84:
            case 85:
            case 86:
            case 87:
            case 88:
            case 89:
            case 90:
            case 91:
            case 92:
            case 93:
            case 94:
            case 95:
            case 96:
            case 97:
            case 98:
            case 99:
            case 100:
            case 101:
            case 102:
            case 103:
            case 104:
            case 105:
            case 106:
            case 107:
            case 108:
            case 109:
            case 110:
            case 111:
            case 112:
            case 113:
            case 114:
            case 115:
            case 116:
            case 117:
            case 118:
            case 119:
            case 120:
            case 121:
            case 122:
            case 133:
            case 141:
            case 142:
            {

                // match regex pattern against line
                regmatch_t matches[1];
                if (regexec(&regex, fileLine, 2, matches, 0) == 0)
                {
                    char name[100];
                    sscanf(fileLine + matches[0].rm_so, "%s", name);

                    // free regex resources
                    regfree(&regex);
                }
                else
                {
                    fprintf(stderr, "Error on line %d\n", lineNumber);
                    fclose(fptr);
                    remove(outputFile);
                    exit(EXIT_FAILURE);
                    return 1;
                }

                break;
            }

            case 132: // jrpc offset
            {

                // match regex pattern against line
                regmatch_t matches[2];
                if (regexec(&regex, fileLine, 2, matches, 0) == 0)
                {
                    char name[100];
                    sscanf(fileLine + matches[0].rm_so, "%s", name);

                    char temp[100];
                    sscanf(fileLine + matches[1].rm_so, "%s", temp);

                    int8_t value;
                    sscanf(temp, "%hhd", &value);

                    int withinBounds = isWithinBounds_8bit(temp, value);

                    if (withinBounds == 0)
                    {
                        fprintf(stderr, "Error on line %d\n", lineNumber);
                        fclose(fptr);
                        remove(outputFile);
                        exit(EXIT_FAILURE);
                        return 1;
                    }

                    writeBigEndian(output, value, sizeof(int8_t));

                    // free regex resources
                    regfree(&regex);
                }
                else
                {
                    fprintf(stderr, "Error on line %d\n", lineNumber);
                    fclose(fptr);
                    remove(outputFile);
                    exit(EXIT_FAILURE);
                    return 1;
                }

                break;
            }

            default:
            {
                break;
            }
            }
        }
    }

    rewind(fptr);
    lineNumber = 0;

    while (fgets(fileLine, sizeof(fileLine), fptr) != NULL)
    {
        lineNumber++;

        size_t length = strlen(fileLine);
        if (fileLine[length - 1] == '\n')
        {
            fileLine[length - 1] = '\0';
        }
        if (fileLine[0] == ';')
        {
            // printf("%s\n", fileLine);
            continue;
        }
        if (fileLine[0] == ':')
        {
            // printf("%s\n", fileLine);
            codeSection, dataSection, doubleSection, longSection, byteSection, asciiSection, intSection, floatSection, shortSection = false;
            continue;
        }
        if (strncmp(fileLine, ".code", 5) == 0)
        {
            // printf("%s\n", fileLine);
            dataSection, doubleSection, longSection, byteSection, asciiSection, intSection, floatSection, shortSection = false;
            codeSection = true;
            continue;
        }
        if (strncmp(fileLine, ".data", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, doubleSection, longSection, byteSection, asciiSection, intSection, floatSection, shortSection = false;
            dataSection = true;
            continue;
        }
        if (strncmp(fileLine, ".byte", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, doubleSection, longSection, dataSection, asciiSection, intSection, floatSection, shortSection = false;
            byteSection = true;
            continue;
        }
        if (strncmp(fileLine, ".ascii", 5) == 0)
        {
            codeSection, doubleSection, longSection, dataSection, byteSection, intSection, floatSection, shortSection = false;
            asciiSection = true;
            continue;
        }
        if (strncmp(fileLine, ".short", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, doubleSection, longSection, dataSection, byteSection, intSection, floatSection, asciiSection = false;
            shortSection = true;
            continue;
        }
        if (strncmp(fileLine, ".int", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, doubleSection, longSection, dataSection, byteSection, shortSection, floatSection, asciiSection = false;
            intSection = true;
            continue;
        }
        if (strncmp(fileLine, ".long", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, doubleSection, intSection, dataSection, byteSection, shortSection, floatSection, asciiSection = false;
            longSection = true;
            continue;
        }
        if (strncmp(fileLine, ".float", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, doubleSection, intSection, dataSection, byteSection, shortSection, longSection, asciiSection = false;
            floatSection = true;
            continue;
        }
        if (strncmp(fileLine, ".double", 5) == 0)
        {
            // printf("%s\n", fileLine);
            codeSection, floatSection, intSection, dataSection, byteSection, shortSection, longSection, asciiSection = false;
            doubleSection = true;
            continue;
        }
        if (dataSection)
        {
            int white = 0;
            while (isspace(fileLine[white]))
            {
                white++;
            }
            if (white > 0)
            {
                //printf("%s\n", fileLine);
            }
        }
        if (byteSection)
        {
            int white = 0;
            while (isspace(fileLine[white]))
            {
                white++;
            }
            if (white > 0)
            {
                uint8_t numberOfBytes;
                sscanf(fileLine + white, "%hhd", &numberOfBytes);
                writeBigEndian(output, numberOfBytes, sizeof(int8_t));
            }
        }

        if (asciiSection)
        {
            int white = 0;
            while (isspace(fileLine[white]))
            {
                white++;
            }
            if (white > 0)
            {
                //printf("%s\n", fileLine);
            }
        }

        if (shortSection)
        {
            int white = 0;
            while (isspace(fileLine[white]))
            {
                white++;
            }
            if (white > 0)
            {
                short numberOfShort;
                sscanf(fileLine + white, "%hd", &numberOfShort);
                writeBigEndian(output, numberOfShort, sizeof(int16_t));
            }
        }
        if (intSection)
        {
            int white = 0;
            while (isspace(fileLine[white]))
            {
                white++;
            }
            if (white > 0)
            {
                int numberOfInt;
                sscanf(fileLine + white, "%d", &numberOfInt);
                writeBigEndian(output, numberOfInt, sizeof(int));
            }
        }

        if (longSection)
        {
            int white = 0;
            while (isspace(fileLine[white]))
            {
                white++;
            }
            if (white > 0)
            {
                long numberOfLong;
                sscanf(fileLine + white, "%ld", &numberOfLong);
                writeBigEndian(output, numberOfLong, sizeof(long));
            }
        }

        if (floatSection)
        {
            int white = 0;
            while (isspace(fileLine[white]))
            {
                white++;
            }
            if (white > 0)
            {
                float numberOfFloat;
                sscanf(fileLine + white, "%f", &numberOfFloat);
                uint32_t floatBytes;
                memcpy(&floatBytes, &numberOfFloat, sizeof(float));
                writeBigEndian(output, floatBytes, sizeof(uint32_t));
            }
        }

        if (doubleSection)
        {
            int white = 0;
            while (isspace(fileLine[white]))
            {
                white++;
            }
            if (white > 0)
            {
                double numberOfDouble;
                sscanf(fileLine + white, "%lf", &numberOfDouble);

                uint64_t doubleBytes;
                memcpy(&doubleBytes, &numberOfDouble, sizeof(double));

                writeBigEndian(output, doubleBytes, sizeof(uint64_t));
            }
        }
    }

    free(outputFile);
    fclose(fptr);
    fclose(output);
    return 0;
}
