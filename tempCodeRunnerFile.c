int main()
{
    //char *filename = "MessageSecret.txt";
    char *filename = "message.txt";
    FILE *fp = fopen(filename, "r");

    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, fp))
    {
        afficher_txt_decodage(buffer,5);
    }

    fclose(fp);

    return 0;
}