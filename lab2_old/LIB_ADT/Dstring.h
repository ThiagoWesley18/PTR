#ifndef DSTRING_H
#define DSTRING_H
#define $(str) (ConverteToDstring(str)) 
#define ConverteToDstring(num) _Generic((num), \
    float: floatToString,                      \
    long: longToString,                        \
    double: floatToString,                     \
    char: charToString,                        \
    int: intToString,                          \
    char *: newDstring                         \
    )(num)

typedef struct string Dstring;
struct string{
    char *string;
};

Dstring newDstring(char *string);
Dstring intToString(int num);
Dstring floatToString(float num);
Dstring longToString(long num);
Dstring charToString(char caractere);
Dstring concat(Dstring str1, ...);
int tamanho(Dstring str);
char *dstringToChar(Dstring str);
void freeDstring(Dstring str, ...);


#endif
